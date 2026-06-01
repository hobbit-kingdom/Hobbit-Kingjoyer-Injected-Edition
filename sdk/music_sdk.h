// =============================================================================
// music_sdk.h  —  THE HOBBIT (2003) PC build, Entropy engine (MSVC, 32-bit)
//
// Reverse-engineered SDK wrappers for the "music" / dynamic-audio subsystem:
//   - MusicLogic           : adaptive-music state machine (combat/ambient/boss/
//                            victory/loss/silence), combat-intensity & NPC-threat
//                            math, suite/track selection, stingers, transitions.
//   - music_mgr (MusicManager) : low-level track/suite owner + cross-fade switch,
//                            exposed via the music_* C-style facade.
//   - AmbientAudioMgr      : looping ambience manager with its own volume ramp.
//   - music_trigger / ambient_audio_trigger : volume zones that drive the above
//                            on listener enter (RedToGreen) / exit (GreenToRed).
//
// Legitimate RE of the user's own game for a modding / trainer SDK.
//
// All addresses are PREFERRED-base (image base 0x00400000, ASLR off). Resolve at
// runtime with meridian::rebase(0xADDR); set meridian::g_delta once at init if the
// image loads at a non-preferred base. Calling convention is __thiscall (this in
// ECX) unless a typedef says __cdecl.
//
// Struct offsets are CONSOLIDATED across the per-chunk analyses (music__00/01/02).
// Layouts are partial: only well-evidenced fields are named; the rest is byte-
// accurate padding so named members land at their true offsets. Offsets marked
// "?" are lower confidence. These structs are NOT meant to be instantiated —
// reinterpret_cast them onto a live engine object.
// =============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/radian3/bbox, xstring, property, xarray<T>, MusicLogic/AmbientAudioMgr/music_mgr/music_trigger/ambient_audio_trigger fwd-decls

// ---- Forward declarations ---------------------------------------------------
// MusicLogic, AmbientAudioMgr, music_mgr, music_trigger, ambient_audio_trigger,
// audio_mgr, audio_package, uncompressed_parameters, object, bin_in, bin_out are
// all already forward-declared in meridian_types.h — nothing extra needed here.

namespace music_sdk {

// =============================================================================
// 1. Enums recovered from the analyses
// =============================================================================

// MusicLogic state ids — written to MusicLogic+0x24c (currentState); dispatched by
// AdvanceStateMachine and produced by ChangeState. (ChangeState 0x00534f30)
enum MusicState : std::int32_t {
    MUSIC_STATE_AMBIENT_OUTDOOR   = 1,  // STATE_AMBIENT — idle/default
    MUSIC_STATE_SILENCE           = 2,  // MUSIC_Silence sentinel
    MUSIC_STATE_COMBAT            = 3,
    MUSIC_STATE_SILENCE_SECONDARY = 4,  // boss-climax / cooldown silence
    MUSIC_STATE_BOSS_COMBAT       = 5,
    MUSIC_STATE_COMBAT_VICTORY    = 6,  // gated by MinCombatTimeForStinger
    MUSIC_STATE_BOSS_VICTORY      = 7,
    MUSIC_STATE_COMBAT_LOSS       = 9,
    MUSIC_STATE_POST_LOSS         = 10, // stop/cleanup
};

// SWITCHTYPE — track-switch timing (music_mgr::SWITCHTYPE / AmbientAudioMgr::
// SWITCHTYPE). Populated by InitializeTriggerSwitchTypeList. NOTE: meridian_types.h
// forward-declares `struct SWITCHTYPE`; engine signatures pass it as a 32-bit enum,
// so wrappers below take it as `int` (SwitchType) to stay ABI-correct.
enum SwitchType : std::int32_t {
    SWITCH_NORMAL           = 0,
    SWITCH_AT_BREAK         = 1,
    SWITCH_WITH_VOLUME_FADE = 2,
    SWITCH_IMMEDIATE        = 3,
};

// Trigger action type — RedToGreen/GreenToRed action selector (trigger+0x1b4 /
// +0x2ac). (OnTriggerRedToGreen / OnTriggerGreenToRed)
enum TriggerActionType : std::int32_t {
    TRIGGER_ACTION_PLAY_TRACK = 0,
    TRIGGER_ACTION_SET_VOLUME = 6,
};

// AmbientAudioMgr volume-ramp mode (AmbientAudioMgr+0x2fc). (SetVolumeTarget)
enum VolumeRampMode : std::int32_t {
    VOLUME_RAMP_IDLE = 0,
    VOLUME_RAMP_DOWN = 1,
    VOLUME_RAMP_UP   = 2,
};

// =============================================================================
// 2. Recovered struct layouts
// =============================================================================

// One per-track mixer slot inside MusicLogic / music_mgr (stride 0x30; array of 2
// at +0x14c). Only the default-gain field is evidenced. (music_mgr::music_mgr)
struct MusicSlot {
    /* 0x00 */ std::uint8_t  _pad00[0x14];
    /* 0x14 */ float         gain;          // default 1.5f
    /* 0x18 */ std::uint8_t  _pad18[0x18];
};

// MusicLogic — the adaptive-music state machine (extends object). Consolidated.
struct MusicLogic_layout {
    /* 0x000 */ std::uint8_t  _pad000[0x7f];
    /* 0x07f */ std::uint8_t  flags;               // bit0 initialized; bit0x10 actor gate
    /* 0x080 */ std::uint8_t  _pad080[0x28];
    /* 0x0a8 */ std::int32_t  bossPresent;         // !=0 => force BOSS_COMBAT (ScanForCombat)
    /* 0x0ac */ std::uint8_t  _pad0ac[0x10];
    /* 0x0bc */ std::int32_t  packageCount;        // PlayDescriptorByName loop bound
    /* 0x0c0 */ std::uint32_t packageArray;        // 32-bit void** descriptor-package array
    /* 0x0c4 */ std::uint8_t  _pad0c4[4];
    /* 0x0c8 */ std::uint8_t  musicLevelFile[0x2c];// embedded xstring (MusicLevelFile)
    /* 0x0f4 */ std::uint8_t  musicLevelName[0x2c];// embedded xstring (MusicLevelName)
    /* 0x120 */ std::int32_t  audioPackageCount;   // export AudioPackageCount
    /* 0x124 */ std::uint8_t  _pad124[8];
    /* 0x12c */ std::int32_t  audioPackageLiveCount;
    /* 0x130 */ std::uint32_t audioPackageArray;   // 32-bit void*, stride 0x2c records
    /* 0x134 */ std::int32_t  audioPackageCapacity;
    /* 0x138 */ std::uint8_t  _pad138[0x14];
    // trackSlots: 2 x MusicSlot (0x30 each) begin at +0x14c, but the named scalar
    // fields below (dirty/defaultSuite/...) and activeSlotIndex@+0x1ac fall INSIDE
    // that 0x60-byte span in the real object, so we expose the scalars instead of
    // the array. Use trackSlot_at()/activeSlotIndex_at() accessors for the slots.
    /* 0x14c */ std::uint8_t  _pad14c[0x10];
    /* 0x15c */ std::int32_t  dirty;               // set with refreshState=0 to refresh
    /* 0x160 */ std::int32_t  refreshState;
    /* 0x164 */ std::uint8_t  defaultSuite[0x2c];  // embedded xstring (DefaultSuite)
    /* 0x190 */ std::uint8_t  defaultTrack[0x2c];  // embedded xstring (DefaultTrack)
    /* 0x1bc */ std::uint8_t  compareDescriptor[0x2c]; // embedded xstring (vs MUSIC_Silence)
    /* 0x1e8 */ std::uint8_t  _pad1e8[0x2c];       // includes activeSlotIndex@+0x1ac region
    /* 0x214 */ std::uint8_t  expectedDescriptor[0x2c]; // embedded xstring (track-change detect)
    /* 0x240 */ std::int32_t  transitionActive;    // also combatActive (PlayCombatDescriptor)
    /* 0x244 */ std::int32_t  transitionKind;      // =3 on transition / default music type
    /* 0x248 */ std::int32_t  activeIntensity;     // SetIntensity store; activeAmbientSuite
    /* 0x24c */ std::int32_t  currentState;        // MusicState; AdvanceStateMachine switch
    /* 0x250 */ std::int32_t  previousState;       // also redToGreenDefaultState
    /* 0x254 */ float         frameDt;             // dt passed to UpDateBossCombat
    /* 0x258 */ float         bossRadius;          // boss scan radius
    /* 0x25c */ std::uint8_t  _pad25c[4];
    /* 0x260 */ float         threatVerticalRange; // |dy| gate
    /* 0x264 */ std::int32_t  desiredAmbientSuite; // appliedIntensity when mode==1
    /* 0x268 */ std::int32_t  combatIntensity;     // current combat suite/intensity
    /* 0x26c */ std::int32_t  peakCombatIntensity; // running max of combatIntensity
    /* 0x270 */ float         stateElapsedTimer;   // per-state timer (0.5/2/5/8/12 gates)
    /* 0x274 */ float         reevalTimer;         // 7.5s reeval cadence (ChangeState=60.0)
    /* 0x278 */ float         minSilenceTime;      // export MinSilenceTime (init 15.0)
    /* 0x27c */ float         maxSilenceTime;      // export MaxSilenceTime (init 30.0)
    /* 0x280 */ float         volumeFadeTime;      // export VolumeFadeTime (init 4.0; combatHoldTime)
    /* 0x284 */ float         effectiveFadeTime;   // OnImport copies volumeFadeTime
    /* 0x288 */ float         combatToSilenceTimeout; // holdDuration (init 5.0)
    /* 0x28c */ std::int32_t  stingerFiredFlag;    // one-shot stinger latch (cleared by ChangeState 6/7/10)
    /* 0x290 */ std::int32_t  transitionPending;   // set on descriptor mismatch
    /* 0x294 */ std::int32_t  greenToRedPending;   // trackElapsed / GreenToRed-pending
    /* 0x298 */ std::int32_t  defaultState;        // export DefaultState; ChangeState target
    /* 0x29c */ std::uint8_t  defaultStateName[0x2c]; // embedded xstring (DefaultStateName)
    /* 0x2c8 */ std::uint8_t  currentDescriptor[0x2c]; // embedded xstring (now-playing)
    /* 0x2f4 */ float         minCombatThreshold;  // export m_MinCombatThreshold (vs currentThreat)
    /* 0x2f8 */ float         maxCombatThreshold;  // export m_MaxCombatThreshold
    /* 0x2fc */ float         minCombatTimeForStinger; // export m_MinCombatTimeForStinger
    /* 0x300 */ float         currentThreat;       // accumulated NPC threat (vs minCombatThreshold)
    /* 0x304 */ float         peakThreat;          // running max of currentThreat

    // Accessors for fields that overlap the trackSlots span (computed, not members).
    std::int32_t* activeSlotIndex() {              // +0x1ac: selects trackSlots[idx]
        return reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x1ac);
    }
    MusicSlot* trackSlot(int i) {                  // +0x14c + i*0x30
        return reinterpret_cast<MusicSlot*>(reinterpret_cast<std::uint8_t*>(this) + 0x14c + i * 0x30);
    }
};

// AmbientAudioMgr — looping-ambience manager (extends object). Layout mirrors
// MusicLogic from ~0x240 onward. Consolidated.
struct AmbientAudioMgr_layout {
    /* 0x000 */ std::uint8_t  _pad000[0x7f];
    /* 0x07f */ std::uint8_t  importedFlag;        // [0x7f] |= 1 on import/export
    /* 0x080 */ std::uint8_t  _pad080[0x28];
    /* 0x0a8 */ std::int32_t  field_a8;            // Init=0
    /* 0x0ac */ std::uint8_t  _pad0ac[0x74];
    /* 0x120 */ std::int32_t  audioPackageHandle;  // resolved to AudioPackageName
    /* 0x124 */ std::uint8_t  _pad124[0x34];
    /* 0x158 */ std::uint32_t ownedBuffer;         // 32-bit void*, freed in dtor when bufferOwnership!=2
    /* 0x15c */ std::uint8_t  _pad15c[4];
    /* 0x160 */ std::int32_t  bufferOwnership;     // ==2 => not owned
    /* 0x164 */ std::uint8_t  _pad164[0xe4];
    /* 0x248 */ std::int32_t  stateMode;           // Init=1
    /* 0x24c */ std::int32_t  musicType;           // Init=3
    /* 0x250 */ std::int32_t  redToGreenDefaultState; // Init=1
    /* 0x254 */ float         distThreshold1;      // 699.0
    /* 0x258 */ float         distThreshold3;      // 1500.0
    /* 0x25c */ float         distThreshold2;      // 500.0
    /* 0x260 */ float         field_260;           // 400.0
    /* 0x264 */ std::int32_t  appliedIntensity;    // Init=1
    /* 0x268 */ std::int32_t  field_268;           // Init=5
    /* 0x26c */ std::uint8_t  _pad26c[4];
    /* 0x270 */ float         minSilenceTime;      // export MinSilenceTime (15.0)
    /* 0x274 */ float         maxSilenceTime;      // export MaxSilenceTime (30.0)
    /* 0x278 */ float         volumeFadeTime;      // export VolumeFadeTime (4.0; active rate)
    /* 0x27c */ std::uint8_t  _pad27c[0x3c];
    /* 0x2b8 */ float         fadeOutTime;         // 10.0
    /* 0x2bc */ float         fadeMid;             // 50.0
    /* 0x2c0 */ float         fadeInTime;          // 10.0
    /* 0x2c4 */ std::uint8_t  _pad2c4[0xc];
    /* 0x2d0 */ float         volumeScaleA;        // 1.0
    /* 0x2d4 */ std::uint8_t  _pad2d4[4];
    /* 0x2d8 */ float         volumeScaleB;        // 1.0
    /* 0x2dc */ std::uint8_t  _pad2dc[0x14];
    /* 0x2f0 */ float         activeRampRate;      // pendingTargetVolume / chosen ramp rate
    /* 0x2f4 */ float         currentVolume;       // SetVolumeTarget compare
    /* 0x2f8 */ float         targetVolume;        // SetVolumeTarget store
    /* 0x2fc */ std::int32_t  rampMode;            // VolumeRampMode
    /* 0x300 */ std::uint8_t  _pad300[0xa0];
    /* 0x3a0 */ float         crossfadeState[12];  // reset by SetDesiredNextTrackByNameFromTrigger
    /* 0x3d0 */ std::uint8_t  _pad3d0[0x88];
    /* 0x458 */ std::int32_t  switchPending;       // first-request-in-frame guard
};

// music_trigger / ambient_audio_trigger — shared transition layout (extends volume).
// music_trigger additionally uses rtgTargetVolume @0x2c4. Consolidated.
struct MusicTrigger_layout {
    /* 0x000 */ std::uint8_t  _pad000[0x7a];
    /* 0x07a */ std::uint16_t dirtyFlags;          // bit0 set by SetProperty / OnImport
    /* 0x07c */ std::uint8_t  _pad07c[0x84];
    /* 0x100 */ float         crossingFraction;    // 0.5
    /* 0x104 */ std::uint8_t  _pad104[0x1c];
    /* 0x120 */ std::int32_t  singleShot;          // fire once
    /* 0x124 */ std::int32_t  armedOrCinematic;    // crossing-test guard / isCinematic
    /* 0x128 */ std::int32_t  triggered;           // set on fire
    /* 0x12c */ std::uint8_t  _pad12c[0x2c];
    /* 0x158 */ std::uint8_t  rtgSuite[0x2c];      // embedded xstring (RedToGreen Suite)
    /* 0x184 */ std::uint8_t  rtgTrack[0x2c];      // embedded xstring (RedToGreen Track)
    /* 0x1b0 */ std::int32_t  rtgDesiredIntensity; // default 1
    /* 0x1b4 */ std::int32_t  rtgTriggerActionType;// TriggerActionType
    /* 0x1b8 */ std::int32_t  rtgSwitchType;       // SwitchType
    /* 0x1bc */ std::int32_t  rtgUseAsDefault;
    /* 0x1c0 */ float         rtgFadeOutTime;
    /* 0x1c4 */ float         rtgFadeInTime;
    /* 0x1c8 */ std::int32_t  rtgMaxLoopCount;
    /* 0x1cc */ std::uint8_t  _pad1cc[0x2c];
    /* 0x1f8 */ std::uint8_t  grSuite[0x2c];       // embedded xstring (GreenToRed Suite)
    /* 0x224 */ std::uint8_t  grTrack[0x2c];       // embedded xstring (GreenToRed Track)
    /* 0x250 */ std::uint8_t  rtgDefaultState[0x2c];// embedded xstring (RedToGreen default state)
    /* 0x27c */ std::uint8_t  grDefaultState[0x2c]; // embedded xstring (GreenToRed default state)
    /* 0x2a8 */ std::int32_t  grDesiredIntensity;  // default 1
    /* 0x2ac */ std::int32_t  grTriggerActionType; // TriggerActionType
    /* 0x2b0 */ std::int32_t  grSwitchType;        // SwitchType
    /* 0x2b4 */ std::int32_t  grUseAsDefault;
    /* 0x2b8 */ float         grFadeOutTime;
    /* 0x2bc */ float         grFadeInTime;
    /* 0x2c0 */ std::int32_t  grMaxLoopCount;
    /* 0x2c4 */ float         rtgTargetVolume;     // music_trigger only
    /* 0x2c8 */ float         grTargetVolume;      // Init 1.0
};

// music_mgr (MusicManager) — low-level track owner. Only evidenced fields named.
struct music_mgr_layout {
    /* 0x000 */ std::uint8_t  _pad000[0x90];
    /* 0x090 */ std::uint8_t  audioHandles[0x74];  // zeroed handle/ptr block (0x90..0x104)
    /* 0x104 */ std::uint8_t  _pad104[0x48];
    /* 0x14c */ MusicSlot     trackSlots[2];       // 2 x 0x30, per-slot gain 1.5f
};

// =============================================================================
// 3. Function wrappers, grouped by class
//
//   __thiscall methods take the object pointer as the FIRST argument.
//   Wrappers that would pass/return an incomplete-by-value engine type instead
//   take/return a pointer (e.g. xstring*, property*), or expose a raw "_at()"
//   address accessor with the true signature in a comment.
// =============================================================================

// ------------------------------- MusicLogic ---------------------------------
namespace music_logic_api {
    // GetMusicLogic — global accessor for the MusicLogic singleton.
    // raw: MusicLogic* __cdecl GetMusicLogic(void)  (see music_api.json)
    // (address not recovered in chunks; resolve via your symbol map / obj_mgr)

    // MusicLogic::MusicLogic — ctor (mislabeled dtor in decomp). Seeds the state
    // config block, STATE_AMBIENT, MUSIC_Silence x3, init bit [0x7f]|=1. 0x005340d0
    using ctor_t = MusicLogic*(__thiscall*)(MusicLogic* self);
    inline MusicLogic* ctor(MusicLogic* self) {
        return reinterpret_cast<ctor_t>(meridian::rebase(0x005340d0))(self);
    }

    // MusicLogic::OnAdvanceLogic — top-level per-frame tick. 0x00535310
    using OnAdvanceLogic_t = void(__thiscall*)(MusicLogic* self, float dt);
    inline void OnAdvanceLogic(MusicLogic* self, float dt) {
        reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x00535310))(self, dt);
    }

    // MusicLogic::AdvanceStateMachine — advance state timer + dispatch per state. 0x00535200
    using AdvanceStateMachine_t = void(__thiscall*)(MusicLogic* self, float dt);
    inline void AdvanceStateMachine(MusicLogic* self, float dt) {
        reinterpret_cast<AdvanceStateMachine_t>(meridian::rebase(0x00535200))(self, dt);
    }

    // MusicLogic::ChangeState — core transition (resets timers, selects suite/track,
    // kicks the music_mgr switch). 0x00534f30
    using ChangeState_t = void(__thiscall*)(MusicLogic* self, int state);
    inline void ChangeState(MusicLogic* self, int state) {
        reinterpret_cast<ChangeState_t>(meridian::rebase(0x00534f30))(self, state);
    }

    // MusicLogic::SetTrackBySuiteTypeAndIntensity — AMBIENTOUTDOOR tick / track
    // selector (escalates to boss/silence on threat). 0x005346e0
    using SetTrackBySuiteTypeAndIntensity_t = void(__thiscall*)(MusicLogic* self);
    inline void SetTrackBySuiteTypeAndIntensity(MusicLogic* self) {
        reinterpret_cast<SetTrackBySuiteTypeAndIntensity_t>(meridian::rebase(0x005346e0))(self);
    }

    // MusicLogic::UpDateAmbient — ambient-state tick. 0x00534a30
    using UpDateAmbient_t = void(__thiscall*)(MusicLogic* self);
    inline void UpDateAmbient(MusicLogic* self) {
        reinterpret_cast<UpDateAmbient_t>(meridian::rebase(0x00534a30))(self);
    }

    // MusicLogic::UpDatePreCombat — pre-combat tick (5s -> full combat). 0x005347e0
    using UpDatePreCombat_t = void(__thiscall*)(MusicLogic* self);
    inline void UpDatePreCombat(MusicLogic* self) {
        reinterpret_cast<UpDatePreCombat_t>(meridian::rebase(0x005347e0))(self);
    }

    // MusicLogic::UpdateStateCombat — COMBAT tick (intensity re-eval cadence). 0x00534b80
    using UpdateStateCombat_t = void(__thiscall*)(MusicLogic* self);
    inline void UpdateStateCombat(MusicLogic* self) {
        reinterpret_cast<UpdateStateCombat_t>(meridian::rebase(0x00534b80))(self);
    }

    // MusicLogic::UpDateCombat — in-combat tick variant (track-change transition). 0x005345e0
    using UpDateCombat_t = void(__thiscall*)(MusicLogic* self);
    inline void UpDateCombat(MusicLogic* self) {
        reinterpret_cast<UpDateCombat_t>(meridian::rebase(0x005345e0))(self);
    }

    // MusicLogic::UpDateCombatHold — combat tick w/ global hold accumulator. 0x00534870
    // raw: void __thiscall (MusicLogic*, float dt)
    using UpDateCombatHold_t = void(__thiscall*)(MusicLogic* self, float dt);
    inline void UpDateCombatHold(MusicLogic* self, float dt) {
        reinterpret_cast<UpDateCombatHold_t>(meridian::rebase(0x00534870))(self, dt);
    }

    // MusicLogic::UpDatePostCombat — post-combat tick (silence then back-to-combat). 0x00534b00
    using UpDatePostCombat_t = void(__thiscall*)(MusicLogic* self);
    inline void UpDatePostCombat(MusicLogic* self) {
        reinterpret_cast<UpDatePostCombat_t>(meridian::rebase(0x00534b00))(self);
    }

    // MusicLogic::UpDateBossCombatState — boss-combat tick (one-shot boss cue). 0x00534cf0
    using UpDateBossCombatState_t = void(__thiscall*)(MusicLogic* self);
    inline void UpDateBossCombatState(MusicLogic* self) {
        reinterpret_cast<UpDateBossCombatState_t>(meridian::rebase(0x00534cf0))(self);
    }

    // MusicLogic::UpDateStateSilence — boss/silence-eval tick. 0x00534dd0
    using UpDateStateSilence_t = void(__thiscall*)(MusicLogic* self);
    inline void UpDateStateSilence(MusicLogic* self) {
        reinterpret_cast<UpDateStateSilence_t>(meridian::rebase(0x00534dd0))(self);
    }

    // MusicLogic::TickStateSilence — MUSIC_Silence-state tick (2s stinger, 12s->state4). 0x00534d60
    using TickStateSilence_t = void(__thiscall*)(MusicLogic* self);
    inline void TickStateSilence(MusicLogic* self) {
        reinterpret_cast<TickStateSilence_t>(meridian::rebase(0x00534d60))(self);
    }

    // MusicLogic::UpDateBossCombat — accumulate nearby-NPC threat into currentThreat. 0x005342f0
    // raw: void __thiscall (MusicLogic*, float radius)
    using UpDateBossCombat_t = void(__thiscall*)(MusicLogic* self, float radius);
    inline void UpDateBossCombat(MusicLogic* self, float radius) {
        reinterpret_cast<UpDateBossCombat_t>(meridian::rebase(0x005342f0))(self, radius);
    }

    // MusicLogic::ScanForCombat — return 1 if any combatant engaged; set bossPresent
    // when a boss-type actor is found. 0x00534520
    using ScanForCombat_t = int(__thiscall*)(MusicLogic* self);
    inline int ScanForCombat(MusicLogic* self) {
        return reinterpret_cast<ScanForCombat_t>(meridian::rebase(0x00534520))(self);
    }

    // MusicLogic::CollectNPCInfo — sample Bilbo health + derive combat-intensity. 0x005349a0
    // raw: void __thiscall (MusicLogic*, float)  (decomp out-params are spurious locals)
    using CollectNPCInfo_t = void(__thiscall*)(MusicLogic* self, float dt);
    inline void CollectNPCInfo(MusicLogic* self, float dt) {
        reinterpret_cast<CollectNPCInfo_t>(meridian::rebase(0x005349a0))(self, dt);
    }

    // MusicLogic::SetIntensity — resolve track+intensity, mark dirty. 0x00535810
    // raw: int __thiscall (MusicLogic*, undefined4, undefined4, undefined4)
    using SetIntensity_t = int(__thiscall*)(MusicLogic* self, std::uint32_t a, std::uint32_t b, std::uint32_t c);
    inline int SetIntensity(MusicLogic* self, std::uint32_t a, std::uint32_t b, std::uint32_t c) {
        return reinterpret_cast<SetIntensity_t>(meridian::rebase(0x00535810))(self, a, b, c);
    }

    // MusicLogic::GetCurrentTrackName — resolve the active-slot descriptor name
    // (MUSIC_Silence if empty/muted). 0x005310a0
    using GetCurrentTrackName_t = const char*(__thiscall*)(MusicLogic* self);
    inline const char* GetCurrentTrackName(MusicLogic* self) {
        return reinterpret_cast<GetCurrentTrackName_t>(meridian::rebase(0x005310a0))(self);
    }

    // MusicLogic::PlayDescriptorByName — look up descriptor + set as desired track.
    // 0x005323f0  (raw: int __thiscall (MusicLogic*, const xstring& name))
    using PlayDescriptorByName_t = int(__thiscall*)(MusicLogic* self, const xstring* name);
    inline int PlayDescriptorByName(MusicLogic* self, const xstring* name) {
        return reinterpret_cast<PlayDescriptorByName_t>(meridian::rebase(0x005323f0))(self, name);
    }

    // MusicLogic::PlayCombatDescriptor — play descriptor + set combat flag; enable==0
    // forces ChangeState(10)/stop. 0x00535740
    // raw: int __thiscall (MusicLogic*, xstring* descriptor, int enable, u32, u32)
    using PlayCombatDescriptor_t = int(__thiscall*)(MusicLogic* self, xstring* descriptor, int enable, std::uint32_t a, std::uint32_t b);
    inline int PlayCombatDescriptor(MusicLogic* self, xstring* descriptor, int enable, std::uint32_t a, std::uint32_t b) {
        return reinterpret_cast<PlayCombatDescriptor_t>(meridian::rebase(0x00535740))(self, descriptor, enable, a, b);
    }

    // MusicLogic::SetCombatHoldTime — store seconds @+0x280 then recompute. 0x005355f0
    using SetCombatHoldTime_t = void(__thiscall*)(MusicLogic* self, float seconds);
    inline void SetCombatHoldTime(MusicLogic* self, float seconds) {
        reinterpret_cast<SetCombatHoldTime_t>(meridian::rebase(0x005355f0))(self, seconds);
    }

    // MusicLogic::LoadNPCThreatTable — load NPCThreatTable.info into the per-character
    // threat-value table (g_threatValueByCharType @0x00764600). 0x00533f60
    using LoadNPCThreatTable_t = void(__thiscall*)(MusicLogic* self);
    inline void LoadNPCThreatTable(MusicLogic* self) {
        reinterpret_cast<LoadNPCThreatTable_t>(meridian::rebase(0x00533f60))(self);
    }

    // MusicLogic::BuildNPCThreatTable — rebuild the NPC-threat name lookup. 0x00535ae0
    using BuildNPCThreatTable_t = void(__thiscall*)(MusicLogic* self);
    inline void BuildNPCThreatTable(MusicLogic* self) {
        reinterpret_cast<BuildNPCThreatTable_t>(meridian::rebase(0x00535ae0))(self);
    }

    // MusicLogic::ImportThreatValues — reset the global NPC-threat table. 0x005360d0
    using ImportThreatValues_t = void(__thiscall*)(MusicLogic* self, bin_in* in);
    inline void ImportThreatValues(MusicLogic* self, bin_in* in) {
        reinterpret_cast<ImportThreatValues_t>(meridian::rebase(0x005360d0))(self, in);
    }

    // MusicLogic::OnImport — deserialize config + threat table. 0x00536400
    using OnImport_t = void(__thiscall*)(MusicLogic* self, bin_in* in);
    inline void OnImport(MusicLogic* self, bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x00536400))(self, in);
    }

    // MusicLogic::OnExport — serialize full config + threat table (mislabeled
    // ExportThreatValues; mirror of OnImport). 0x00535ec0
    using OnExport_t = void(__thiscall*)(MusicLogic* self, bin_out* out);
    inline void OnExport(MusicLogic* self, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x00535ec0))(self, out);
    }
} // namespace music_logic_api

// ----------------------------- music_mgr / facade ---------------------------
namespace music_mgr_api {
    // music_mgr::music_mgr — ctor (build slots, placeholder names, zero handles). 0x00530ce0
    using ctor_t = void(__thiscall*)(music_mgr* self);
    inline void ctor(music_mgr* self) {
        reinterpret_cast<ctor_t>(meridian::rebase(0x00530ce0))(self);
    }

    // music_Kill — tear down active music: clear playing flag, stop/fade the live
    // music voice (0.5s). __cdecl facade. 0x004fb0d0
    using music_Kill_t = void(__cdecl*)();
    inline void music_Kill() {
        reinterpret_cast<music_Kill_t>(meridian::rebase(0x004fb0d0))();
    }
} // namespace music_mgr_api

// ----------------------------- AmbientAudioMgr ------------------------------
namespace ambient_audio_mgr_api {
    // GetAmbientAudioMgr — global accessor (DAT_0075ca60 singleton). 0x00452eb0
    using GetAmbientAudioMgr_t = AmbientAudioMgr*(__cdecl*)();
    inline AmbientAudioMgr* GetAmbientAudioMgr() {
        return reinterpret_cast<GetAmbientAudioMgr_t>(meridian::rebase(0x00452eb0))();
    }

    // AmbientAudioMgr::Init — seed state-machine defaults + reset descriptor array. 0x00453360
    using Init_t = void(__thiscall*)(AmbientAudioMgr* self);
    inline void Init(AmbientAudioMgr* self) {
        reinterpret_cast<Init_t>(meridian::rebase(0x00453360))(self);
    }

    // AmbientAudioMgr::SetVolumeTarget — begin a volume ramp toward target. 0x00453630
    // raw: void __thiscall (AmbientAudioMgr*, float upRate, float downRate, float target)
    using SetVolumeTarget_t = void(__thiscall*)(AmbientAudioMgr* self, float upRate, float downRate, float target);
    inline void SetVolumeTarget(AmbientAudioMgr* self, float upRate, float downRate, float target) {
        reinterpret_cast<SetVolumeTarget_t>(meridian::rebase(0x00453630))(self, upRate, downRate, target);
    }

    // AmbientAudioMgr::SetDesiredNextTrackByNameFromTrigger — queue next ambient track.
    // 0x00453740  (raw: int __thiscall (AmbientAudioMgr*, xstring& name, int intensity,
    //              int switchType, float fadeIn, float targetVolume))
    using SetDesiredNextTrackByNameFromTrigger_t =
        int(__thiscall*)(AmbientAudioMgr* self, xstring* name, int intensity, int switchType, float fadeIn, float targetVolume);
    inline int SetDesiredNextTrackByNameFromTrigger(AmbientAudioMgr* self, xstring* name, int intensity, int switchType, float fadeIn, float targetVolume) {
        return reinterpret_cast<SetDesiredNextTrackByNameFromTrigger_t>(meridian::rebase(0x00453740))(self, name, intensity, switchType, fadeIn, targetVolume);
    }

    // AmbientAudioMgr::OnExport — serialize silence/fade + AudioPackageName. 0x00454000
    using OnExport_t = void(__thiscall*)(AmbientAudioMgr* self, bin_out* out);
    inline void OnExport(AmbientAudioMgr* self, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x00454000))(self, out);
    }

    // AmbientAudioMgr::OnImport — deserialize silence/fade + load package. 0x004540f0
    using OnImport_t = void(__thiscall*)(AmbientAudioMgr* self, bin_in* in);
    inline void OnImport(AmbientAudioMgr* self, bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x004540f0))(self, in);
    }

    // AmbientAudioMgr::~AmbientAudioMgr — destructor (clears the singleton). 0x004531b0
    using Dtor_t = void(__thiscall*)(AmbientAudioMgr* self);
    inline void Destroy(AmbientAudioMgr* self) {
        reinterpret_cast<Dtor_t>(meridian::rebase(0x004531b0))(self);
    }

    // AmbientAudioMgr::`scalar deleting destructor' — MSVC deleting dtor. 0x00453130
    // raw: void* __thiscall (AmbientAudioMgr*, unsigned int flags)  (flags&1 => free)
    using ScalarDeletingDtor_t = void*(__thiscall*)(AmbientAudioMgr* self, unsigned int flags);
    inline void* ScalarDeletingDtor(AmbientAudioMgr* self, unsigned int flags) {
        return reinterpret_cast<ScalarDeletingDtor_t>(meridian::rebase(0x00453130))(self, flags);
    }
} // namespace ambient_audio_mgr_api

// ------------------------- music_trigger (volume zone) ----------------------
namespace music_trigger_api {
    // music_trigger::Init — init trigger + default both transition blocks (mislabeled
    // dtor in decomp). 0x00538bd0
    using Init_t = void(__thiscall*)(music_trigger* self);
    inline void Init(music_trigger* self) {
        reinterpret_cast<Init_t>(meridian::rebase(0x00538bd0))(self);
    }

    // music_trigger::SetProperty — editor setter (writes both blocks). 0x00539d90
    // raw: int __thiscall (music_trigger*, const char* name, const property& value)
    using SetProperty_t = int(__thiscall*)(music_trigger* self, const char* name, const property* value);
    inline int SetProperty(music_trigger* self, const char* name, const property* value) {
        return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00539d90))(self, name, value);
    }

    // music_trigger::OnExport — serialize both transition blocks. 0x00456bb0
    using OnExport_t = void(__thiscall*)(music_trigger* self, bin_out* out);
    inline void OnExport(music_trigger* self, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x00456bb0))(self, out);
    }

    // music_trigger::OnImport — deserialize both transition blocks. 0x00456d80
    using OnImport_t = void(__thiscall*)(music_trigger* self, bin_in* in);
    inline void OnImport(music_trigger* self, bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x00456d80))(self, in);
    }

    // InitializeTriggerActionTypeList — populate the global SWITCHTYPE/action-type
    // name list. __cdecl. 0x005385e0
    using InitializeTriggerActionTypeList_t = void(__cdecl*)();
    inline void InitializeTriggerActionTypeList() {
        reinterpret_cast<InitializeTriggerActionTypeList_t>(meridian::rebase(0x005385e0))();
    }
} // namespace music_trigger_api

// ----------------------- ambient_audio_trigger (volume zone) ----------------
namespace ambient_audio_trigger_api {
    // ambient_audio_trigger::Init — volume::Init from bbox + default both blocks. 0x00454e40
    // raw: void __thiscall (ambient_audio_trigger*, const vector3& pos, const bbox& box)
    using Init_t = void(__thiscall*)(ambient_audio_trigger* self, const vector3* pos, const bbox* box);
    inline void Init(ambient_audio_trigger* self, const vector3* pos, const bbox* box) {
        reinterpret_cast<Init_t>(meridian::rebase(0x00454e40))(self, pos, box);
    }

    // ambient_audio_trigger::SetProperty — editor setter (writes both blocks). 0x00455a20
    using SetProperty_t = int(__thiscall*)(ambient_audio_trigger* self, const char* name, const property* value);
    inline int SetProperty(ambient_audio_trigger* self, const char* name, const property* value) {
        return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00455a20))(self, name, value);
    }

    // ambient_audio_trigger::OnExport — serialize both blocks (no rtgTargetVolume). 0x0053aff0
    using OnExport_t = void(__thiscall*)(ambient_audio_trigger* self, bin_out* out);
    inline void OnExport(ambient_audio_trigger* self, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x0053aff0))(self, out);
    }

    // ambient_audio_trigger::OnImport — deserialize both blocks. 0x0053b1a0
    using OnImport_t = void(__thiscall*)(ambient_audio_trigger* self, bin_in* in);
    inline void OnImport(ambient_audio_trigger* self, bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x0053b1a0))(self, in);
    }

    // ambient_audio_trigger::CheckForCrossing — test listener segment vs the oriented
    // volume box; fire RedToGreen on enter / GreenToRed on exit. 0x004551c0
    // raw: void __thiscall (ambient_audio_trigger*, vector3 p0, vector3 p1)  — the two
    // vector3 args are passed BY VALUE; pass pointers here and let the ABI lay them out,
    // OR call the raw address directly if you need exact by-value semantics.
    using CheckForCrossing_t = void(__thiscall*)(ambient_audio_trigger* self, const vector3* p0, const vector3* p1);
    inline void CheckForCrossing(ambient_audio_trigger* self, const vector3* p0, const vector3* p1) {
        reinterpret_cast<CheckForCrossing_t>(meridian::rebase(0x004551c0))(self, p0, p1);
    }

    // ambient_audio_trigger::OnTriggerRedToGreen — on listener ENTER. 0x004554a0
    using OnTriggerRedToGreen_t = void(__thiscall*)(ambient_audio_trigger* self);
    inline void OnTriggerRedToGreen(ambient_audio_trigger* self) {
        reinterpret_cast<OnTriggerRedToGreen_t>(meridian::rebase(0x004554a0))(self);
    }

    // ambient_audio_trigger::OnTriggerGreenToRed — on listener EXIT. 0x00455570
    using OnTriggerGreenToRed_t = void(__thiscall*)(ambient_audio_trigger* self);
    inline void OnTriggerGreenToRed(ambient_audio_trigger* self) {
        reinterpret_cast<OnTriggerGreenToRed_t>(meridian::rebase(0x00455570))(self);
    }
} // namespace ambient_audio_trigger_api

// ----------------------------- audio_mgr (context) --------------------------
namespace audio_mgr_api {
    // audio_mgr::GetVoiceParameters / FindMusicPackageParameters — MUSIC_-prefixed
    // package-parameter lookup over the package list. 0x0065af40  (low-confidence rename)
    // raw: void __thiscall (audio_mgr*, uncompressed_parameters* out, unsigned short* p2,
    //                       audio_package* pkg)
    using FindMusicPackageParameters_t =
        void(__thiscall*)(audio_mgr* self, uncompressed_parameters* outParams, unsigned short* p2, audio_package* pkg);
    inline void FindMusicPackageParameters(audio_mgr* self, uncompressed_parameters* outParams, unsigned short* p2, audio_package* pkg) {
        reinterpret_cast<FindMusicPackageParameters_t>(meridian::rebase(0x0065af40))(self, outParams, p2, pkg);
    }
} // namespace audio_mgr_api

// =============================================================================
// 4. Usage recipes (trainer / modding)
// =============================================================================
//
//  --- Read the live music state (read-only) -------------------------------
//    MusicLogic* ml = music_sdk::music_logic_api::ctor /* no: resolve the live
//      singleton via GetMusicLogic in your symbol map; do NOT construct */;
//    auto* L = reinterpret_cast<music_sdk::MusicLogic_layout*>(ml);
//    int   state     = L->currentState;        // music_sdk::MusicState
//    float threat    = L->currentThreat;       // vs L->minCombatThreshold
//    bool  inCombat  = state == music_sdk::MUSIC_STATE_COMBAT
//                   || state == music_sdk::MUSIC_STATE_BOSS_COMBAT;
//
//  --- Force a music state (e.g. drop to silence) ---------------------------
//    music_sdk::music_logic_api::ChangeState(ml, music_sdk::MUSIC_STATE_SILENCE);
//
//  --- Stop all music now ---------------------------------------------------
//    music_sdk::music_mgr_api::music_Kill();   // stops + fades the live voice
//
//  --- Drive ambience volume directly ---------------------------------------
//    AmbientAudioMgr* am = music_sdk::ambient_audio_mgr_api::GetAmbientAudioMgr();
//    if (am) music_sdk::ambient_audio_mgr_api::SetVolumeTarget(am,
//              /*upRate*/ 4.0f, /*downRate*/ 4.0f, /*target*/ 0.0f);  // fade out
//
//  --- Inspect / tweak a placed music_trigger's transition block ------------
//    auto* T = reinterpret_cast<music_sdk::MusicTrigger_layout*>(trigger);
//    T->rtgTargetVolume = 1.0f;
//    int action = T->rtgTriggerActionType;     // music_sdk::TriggerActionType
//
//  NOTE: pass-by-value engine types (xstring/property/vector3) are passed by
//  POINTER in these wrappers to stay ABI-safe with incomplete types; for the few
//  raw by-value calls (e.g. CheckForCrossing's two vector3 args) the raw signature
//  is documented in the comment above the wrapper.
// =============================================================================

} // namespace music_sdk
