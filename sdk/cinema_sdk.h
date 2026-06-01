// =============================================================================
// cinema_sdk.h  —  THE HOBBIT (2003) PC build, Entropy engine (MSVC, 32-bit)
//
// Reverse-engineered SDK wrappers for the "cinema" / cutscene subsystem:
//   - cinema             : the cutscene driver (shots, cameras, anims, fx, queue)
//   - cinema_action + subclasses (camera/dialog/anim/fx/popto/script/ai/audio/...)
//   - ConversationMgr    : in-game dialog / conversation playback manager
//
// Legitimate RE of the user's own game for a modding / trainer SDK.
//
// All addresses are PREFERRED-base (image base 0x00400000, ASLR off). Resolve at
// runtime with meridian::rebase(0xADDR); set meridian::g_delta once at init if
// the image is loaded at a non-preferred base. Calling convention is __thiscall
// (this in ECX) unless the typedef says __cdecl.
//
// Struct offsets are CONSOLIDATED across the per-chunk analyses (cinema__00/01/02)
// and documented as field-offset comments. Layouts are partial: only fields with
// real evidence are named; everything else is byte-accurate padding so named
// members land at their true offsets. Offsets marked "?" are lower confidence.
// These structs are NOT meant to be instantiated — reinterpret_cast them onto a
// live engine object (e.g. the slot resolved from a cinema GUID).
// =============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/radian3/bbox, xarray<T>, property, ...

// ---- Forward declarations for opaque / cross-subsystem types ----------------
// (cinema, cinema_action, cinema_camera, ConversationMgr, etc. are already
//  forward-declared in meridian_types.h; we add only ones it does not cover.)
struct object;            // base of cinema / cinema_action / ConversationMgr
struct bin_in;            // import stream
struct bin_out;           // export stream
struct MessageInfo;       // HandleMessage payload
struct cinema_audio;      // audio action (forward-declared here)
struct cinema_music;      // music action
struct cinema_ai;         // ai action
struct cinema_ai_trigger; // ai-trigger action
struct cinema_dialog;     // dialog action

namespace cinema_sdk {

// =============================================================================
// 1. cinema state flags  (bitfield at cinema+0x194, consolidated from
//    Start/Shutdown/End/OnAdvanceLogic/IsSkippable/IsCinemaLowPriority/etc.)
// =============================================================================
enum CinemaFlag : std::uint32_t {
    CINEMA_REPEATABLE        = 0x00000001, // bit0  loop / can replay
    CINEMA_FINISHED          = 0x00000002, // bit1  IsFinished() / OnReset clears
    CINEMA_ACTIVE            = 0x00000004, // bit2  playing (OnObjectDeactivate gate)
    CINEMA_POP_AT_END        = 0x00000008, // bit3  pop player state when done
    CINEMA_CINEMATIC         = 0x00000010, // bit4  IsCinematic(): full cinematic mode
    CINEMA_BILBO_INVISIBLE   = 0x00000040, // bit6  hide Bilbo during cinema
    CINEMA_HAS_POST_TRANS    = 0x00000100, // bit8  has post-cinematic transition fx
    CINEMA_RING_STATE        = 0x00000400, // bit10 cached ring-equipped state
    CINEMA_DEATH_CINEMA      = 0x00000800, // bit11 death cutscene -> bilbo::Reset
    CINEMA_PENDING_START     = 0x00000020, // bit5  deferred Start (cleared 1st tick)
    CINEMA_SKIPPABLE_NOW     = 0x00000200, // bit9  currently-skippable/started gate
    CINEMA_BYPASS_QUEUE      = 0x00100000, // bit20 BypassQueue (skip the queue)
    CINEMA_LOW_PRIORITY      = 0x00100000, // alias: low-priority bit (bit20 region)
    CINEMA_RUNTIME_UPDATED   = 0x00800000, // bit23 RuntimeUpdateAll one-time guard
    CINEMA_HAS_TRANSITION    = 0x80000000, // bit31 has pre-cinema transition fx
    // 0x20000/0x40000/0x80000/0x200000 = skip/finish runtime-state bits (recomputed)
};

// cinema_action::CINEMA_ACTION_TYPE — runtime type tag at cinema_action+0x00.
// 4 = camera, 9 = surface/fxobj hide action (from UpdateCameras / AdvanceShot).
enum CinemaActionType : std::int32_t {
    CINEMA_ACTION_CAMERA = 4,   // cinema_camera node
    CINEMA_ACTION_FXOBJ  = 9,   // surface / fxobj-emitting node
};

// cinema_camera CameraType combo (from cinema_camera::EnumerateProperties).
enum CinemaCameraType : std::int32_t {
    CAM_PROGRAMMATIC        = 0,
    CAM_CUSTOM              = 1,
    CAM_MID_SHOT            = 2,
    CAM_CLOSE_UP            = 3,
    CAM_OVER_LEFT_SHOULDER  = 4,
    CAM_OVER_RIGHT_SHOULDER = 5,
};

// =============================================================================
// 2. Recovered struct layouts
// =============================================================================

// cinema_fx — embedded transition-fx action (0x38+ bytes). The cinema owns two:
// preTransitionFx @cinema+0x118 and postTransitionFx @cinema+0x150. ctor seeds
// intensity=1.0, near=0.15, far=20.0, RGBA=(0,0,0,255). (cinema_fx::cinema_fx)
struct cinema_fx_layout {
    /* 0x00 */ void**        vtable;     // &PTR_FUN_006ed0d4
    /* 0x04 */ std::int32_t  field_04;   // 0
    /* 0x08 */ float         intensity;  // 1.0f default
    /* 0x0c */ std::int16_t  shotIndex;
    /* 0x0e */ std::int16_t  animIndex;
    /* 0x10 */ std::uint8_t  flags;      // low 3 bits = begun/finished state
    /* 0x11 */ std::uint8_t  _pad11[3];
    /* 0x14 */ std::int32_t  field_14;   // 0
    /* 0x18 */ std::int32_t  field_18;   // 0
    /* 0x1c */ std::int32_t  mode;       // 1 default (mode/count)
    /* 0x20 */ float         nearParam;  // 0.15f default (fade-in / near)
    /* 0x24 */ float         farParam;   // 20.0f default (fade-out / far)
    /* 0x28 */ std::int32_t  field_28;   // 0
    /* 0x2c */ std::int32_t  field_2c;   // 0
    /* 0x30 */ std::int32_t  field_30;   // 0
    /* 0x34 */ std::uint8_t  colorB;     // 0
    /* 0x35 */ std::uint8_t  colorG;     // 0
    /* 0x36 */ std::uint8_t  colorR;     // 0
    /* 0x37 */ std::uint8_t  colorA;     // 0xff (opaque)
};

// cinema_action — base class of every cinema action node (virtual, ~0x34 bytes,
// matches operator_new(0x34) in SetActionCount). Subclasses extend it.
// (cinema_action::OnExport / cinema::SetActionCount)
struct cinema_action_layout {
    /* 0x00 */ std::int32_t  type;          // CinemaActionType (4=camera, 9=fxobj)
    /* 0x04 */ float         offset;        // start offset within shot
    /* 0x08 */ float         duration;      // computed/declared duration
    /* 0x0c */ std::int16_t  syncPoint;     // owning sync-point index
    /* 0x0e */ std::int16_t  shot;          // owning shot index
    /* 0x10 */ std::uint16_t finishShotFlag;// bit0 (1-bit) FinishShot; bit2 ended-suppress
    /* 0x12 */ std::uint8_t  _pad12[6];
    /* 0x18 */ float         defaultLength;
    /* 0x1c */ std::uint8_t  _pad1c[0x14];
    /* 0x30 */ void*         runtimeFx;     // owned runtime fx/object ptr (own vtable)
};

// cinema_camera — camera action (extends cinema_action). (cinema_camera::OnExport)
struct cinema_camera_layout {
    /* 0x00 */ std::uint8_t  _base[0x1c];   // cinema_action base
    /* 0x1c */ std::int32_t  cameraType;    // CinemaCameraType
    /* 0x20 */ std::uint64_t targetGuid;    // Target object GUID
    /* 0x28 */ radian3       startOrient;
    /* 0x34 */ radian3       endOrient;     // (uses start if useStartForEnd==0)
    /* 0x40 */ vector3       startOffset;
    /* 0x4c */ vector3       endOffset;     // (uses start if useStartForEnd set)
    /* 0x58 */ std::uint8_t  _pad58[8];
    /* 0x60 */ std::int32_t  relative;      // bool: offsets relative to target
    /* 0x64 */ std::uint8_t  _pad64[8];
    /* 0x6c */ std::int32_t  useStartForEnd;// selects start-vs-end orient/offset
};

// cinema_anim — character-animation action (extends cinema_action).
// (cinema_anim::OnExport)
struct cinema_anim_layout {
    /* 0x00 */ std::uint8_t  _base[0x20];   // cinema_action base
    /* 0x20 */ std::uint64_t characterGuid; // animated character GUID
    /* 0x28 */ void*         animName;      // xstring handle (anim resource name)
    /* 0x2c */ std::uint8_t  _pad2c[0x2c];
    /* 0x58 */ std::int32_t  animatedInPlace;// bool
    /* 0x5c */ std::int32_t  loops;          // bool
    /* 0x60 */ std::int32_t  length;         // float/int anim length
    /* 0x64 */ std::int32_t  animsToPlay;    // count
};

// cinema_anim_inst — animation-instance action (extends cinema_action).
// (cinema_anim_inst::OnExport)
struct cinema_anim_inst_layout {
    /* 0x00 */ std::uint8_t  _base[0x20];   // cinema_action base
    /* 0x20 */ std::uint64_t objectGuid;
    /* 0x28 */ void*         animName;      // xstring handle
    /* 0x2c */ std::uint8_t  _pad2c[0x28];
    /* 0x54 */ std::uint32_t flags;         // bit0 StartAnimating, bit1 Looping,
                                            // bit2 HideWhenDone, bit3 SetToEndOnSkip
};

// cinema_popto — snap/teleport action (extends cinema_action). (cinema_popto::Execute)
struct cinema_popto_layout {
    /* 0x00 */ std::uint8_t  _base[0x10];   // cinema_action base (+type)
    /* 0x10 */ std::uint8_t  stateFlags;    // |2 marks executed
    /* 0x11 */ std::uint8_t  _pad11[0xf];
    /* 0x20 */ std::uint64_t targetGuidA;   // primary object to reposition
    /* 0x28 */ std::uint64_t targetGuidB;   // secondary object (e.g. Bilbo)
    /* 0x30 */ std::uint8_t  _pad30[0xc];
    /* 0x3c */ float         destTransform[9]; // position/orientation block -> obj+0x114
    /* 0x60 */ std::int32_t  moveTargetFlag; // !=0 => reposition resolved object
};

// cinema_fxobj_trigger — fxobj edge-trigger action (extends cinema_action).
// (cinema_fxobj_trigger::Execute)
struct cinema_fxobj_trigger_layout {
    /* 0x00 */ std::uint8_t  _base[8];      // cinema_action base
    /* 0x08 */ std::uint32_t flags;         // bit0 set on rising trigger edge
    /* 0x0c */ std::uint8_t  _pad0c[4];
    /* 0x10 */ std::uint64_t targetGuid;    // queried object
    /* 0x18 */ std::int32_t  prevState;     // cached vtbl+0x108 query (edge detect)
};

// cinema_shot — one shot record in the shot table (stride 0x40). First 0x2c is an
// embedded xstring name. (xarray<cinema_shot>::Append / SetShotCount / UpdateSyncPoint)
struct cinema_shot_layout {
    /* 0x00 */ std::uint8_t  name[0x2c];    // embedded xstring (name @+0x24 = len/ptr)
    /* 0x2c */ std::int32_t  syncLink;      // dependency-chain next-link / type (==1 action-linked)
    /* 0x30 */ std::int32_t  linkTarget;    // source/action index it is linked to
    /* 0x34 */ float         duration;
    /* 0x38 */ std::int16_t  shotIndex;     // logical shot index
    /* 0x3a */ std::uint16_t flags;         // bit0 sync-reached, bit1 default-set
    /* 0x3c */ float         startTime;     // resolved absolute start time
};

// cinema_syncpoint — one sync-point record (stride 0x3c). First 0x2c is an embedded
// xstring name. (xarray<cinema_syncpoint>::Append / SetSyncCount / UpdateShotTimes)
struct cinema_syncpoint_layout {
    /* 0x00 */ std::uint8_t  name[0x2c];    // embedded xstring ('<RENAME ME>' default)
    /* 0x2c */ std::int32_t  shotIndex;     // owning shot index (self by default)
    /* 0x30 */ std::int32_t  resolvedIndex; // resolved shot index
    /* 0x34 */ float         duration;      // 600.0f default
    /* 0x38 */ float         startTime;     // shot start time (written by UpdateShotTimes)
};

// cinema — the cutscene driver (extends object). Large layout; only well-evidenced
// fields are named, the rest is padding to land named members at true offsets.
// (Consolidated from cinema__00 / cinema__01 / cinema__02.)
struct cinema_layout {
    /* 0x000 */ std::uint8_t  _base[0x08];      // object base (vtable @+0x0)
    /* 0x008 */ std::uint32_t guidLo;           // cinema GUID low (queue key)
    /* 0x00c */ std::uint32_t guidHi;           // cinema GUID high
    /* 0x010 */ std::uint8_t  _pad010[0x98];
    /* 0x0a8 */ std::uint8_t  syncArrayHdr[8];  // xarray<cinema_syncpoint> header
    /* 0x0b0 */ std::int32_t  syncPointCount;   // sync-table element count
    /* 0x0b4 */ void*         syncPointData;    // cinema_syncpoint*, stride 0x3c
    /* 0x0b8 */ std::int32_t  syncPointCapacity;
    /* 0x0bc */ std::int32_t  syncPointOwnFlag; // !=2 => owned/freeable
    /* 0x0c0 */ std::uint8_t  _pad0c0[4];
    /* 0x0c4 */ std::uint8_t  shotArrayHdr[8];  // xarray<cinema_shot> header
    /* 0x0cc */ std::int32_t  shotCount;
    /* 0x0d0 */ void*         shotData;         // cinema_shot*, stride 0x40
    /* 0x0d4 */ std::uint8_t  _pad0d4[4];
    /* 0x0d8 */ std::int32_t  shotOwnFlag;      // !=2 => owned
    /* 0x0dc */ std::uint8_t  _pad0dc[0x0c];
    /* 0x0e8 */ std::int32_t  skipActionCount;  // also iterated as the action array
    /* 0x0ec */ void*         skipActionPtrs;   // cinema_action**, [i*4]
    /* 0x0f0 */ std::int32_t  skipActionCapacity;
    /* 0x0f4 */ std::int32_t  skipActionOwnFlag;
    /* 0x0f8 */ std::int32_t  skipActionGrowHint;
    /* 0x0fc */ std::uint8_t  _pad0fc[8];
    /* 0x104 */ std::int32_t  syncFlagCount;    // RuntimeUpdateAll int array
    /* 0x108 */ std::int32_t* syncFlags;
    /* 0x10c */ std::int32_t  syncFlagCapacity;
    /* 0x110 */ std::int32_t  syncFlagOwnFlag;
    /* 0x114 */ std::int32_t  syncFlagGrowHint;
    /* 0x118 */ cinema_fx_layout preTransitionFx; // embedded pre-cinema transition
    /* 0x150 */ cinema_fx_layout postTransitionFx;// embedded post-cinema transition
    /* 0x188 */ std::uint8_t  _pad188[4];
    /* 0x18c */ std::uint16_t initialShot;      // OnImport stores InitialShot here
    /* 0x18e */ std::int16_t  currentShot;      // current shot index (-1 = none)
    /* 0x190 */ std::int32_t  prevShotIndex;
    /* 0x194 */ std::uint32_t flags;            // CinemaFlag bitfield
    /* 0x198 */ std::uint8_t  _pad198[8];
    /* 0x1a0 */ std::int32_t  actionCount;      // main action array count
    /* 0x1a4 */ void*         actionPtrs;       // cinema_action**, [i*4]
    /* 0x1a8 */ std::int32_t  actionCapacity;
    /* 0x1ac */ std::int32_t  actionOwnFlag;
    /* 0x1b0 */ std::int32_t  actionGrowHint;
    /* 0x1b4 */ float         elapsedTime;      // OnImport field; reset on teardown
    /* 0x1b8 */ float         shotElapsedTime;  // AdvanceShot per-shot accumulator
    /* 0x1bc */ float         duration;         // OnImport 'Duration'
    /* 0x1c0 */ std::uint8_t  _pad1c0[8];
    /* 0x1c8 */ std::int32_t  participantCount;
    /* 0x1cc */ std::uint64_t* participants;    // 8-byte GUID entries
    /* 0x1d4 */ std::int32_t  participantOwnFlag;
    /* 0x1d8 */ std::uint8_t  _pad1d8[0x78];
    /* 0x250 */ std::uint64_t objQueuedCinemaGuid; // resolved-object queued GUID slot
    /* 0x258 */ std::uint64_t queuedCinemaGuid;    // this object's queued/next GUID
};

// ConversationMgr — dialog / conversation playback manager (extends object).
// Owns a dynamic array of 0xA0-byte Conversation records. (ConversationMgr::OnImport /
// SetProperty / GetProperty)
struct ConversationMgr_layout {
    /* 0x00 */ std::uint8_t  _pad00[0x4c];
    /* 0x4c */ std::int32_t  conversationCount;
    /* 0x50 */ std::uint8_t  _pad50[4];
    /* 0x54 */ std::int32_t  conversationCapacity;
};

// Conversation — one conversation record (0xA0 bytes) inside ConversationMgr.
// First member is an xstring Name; DialogCount lives near the tail.
struct Conversation_layout {
    /* 0x00 */ std::uint8_t  name[0x2c];    // embedded xstring (Name)
    /* 0x2c */ std::uint8_t  _pad2c[0x70];
    /* 0x9c */ std::int32_t  dialogCount;   // total record size 0xA0
};

// =============================================================================
// 3. Function wrappers, grouped by class
//
//   __thiscall methods take the object pointer as the FIRST argument.
//   Wrappers that would pass/return an incomplete-by-value engine type instead
//   take/return a pointer, or expose a raw "_at()" address accessor with the
//   true signature in a comment.
// =============================================================================

// ----------------------------- cinema (driver) ------------------------------
namespace cinema_api {
    // cinema::cinema — ctor: zero arrays, build the two cinema_fx subobjects,
    // lazily init the global cinema queue. 0x00469c50
    using ctor_t = void(__thiscall*)(cinema* self);
    inline void ctor(cinema* self) {
        reinterpret_cast<ctor_t>(meridian::rebase(0x00469c50))(self);
    }

    // cinema::~cinema — destructor: free shots/syncpoints/actions/participants,
    // destruct the two cinema_fx subobjects. 0x00469f30
    using Dtor_t = void(__thiscall*)(cinema* self);
    inline void Destroy(cinema* self) {
        reinterpret_cast<Dtor_t>(meridian::rebase(0x00469f30))(self);
    }

    // cinema::Start — activate this cinema: guard states, set active flags,
    // handle bypass-queue / low-priority, register GUID and kick off playback.
    // 0x0046a550
    using Start_t = void(__thiscall*)(cinema* self);
    inline void Start(cinema* self) {
        reinterpret_cast<Start_t>(meridian::rebase(0x0046a550))(self);
    }

    // cinema::End — begin termination: run post-cinematic transition fx, wait,
    // then Shutdown; handle PopAtEnd / death-cinema Bilbo reset. 0x0046aa20
    using End_t = void(__thiscall*)(cinema* self);
    inline void End(cinema* self) {
        reinterpret_cast<End_t>(meridian::rebase(0x0046aa20))(self);
    }

    // cinema::Shutdown — tear down active cinema, dequeue, chain next queued
    // cinema. advanceQueue = trailing stack bool (1 => walk to next queued).
    // 0x0046ab10  (raw: void __thiscall cinema::Shutdown(cinema*, int advanceQueue))
    using Shutdown_t = void(__thiscall*)(cinema* self, int advanceQueue);
    inline void Shutdown(cinema* self, int advanceQueue) {
        reinterpret_cast<Shutdown_t>(meridian::rebase(0x0046ab10))(self, advanceQueue);
    }

    // cinema::ShutdownAndAdvance — Shutdown(this,1): end + continue to next queued
    // cinema (analysis FUN_0046aaf0, conf 0.7). 0x0046aaf0
    using ShutdownAndAdvance_t = void(__thiscall*)(cinema* self);
    inline void ShutdownAndAdvance(cinema* self) {
        reinterpret_cast<ShutdownAndAdvance_t>(meridian::rebase(0x0046aaf0))(self);
    }

    // cinema::Skip — fast-forward to the end: fire remaining shot/action callbacks
    // instantly, hide skipped surfaces, reset sync points. 0x00473020
    using Skip_t = void(__thiscall*)(cinema* self);
    inline void Skip(cinema* self) {
        reinterpret_cast<Skip_t>(meridian::rebase(0x00473020))(self);
    }

    // cinema::AdvanceShot — advance to the next shot (delta seconds). 0x00472b60
    using AdvanceShot_t = void(__thiscall*)(cinema* self, float dt);
    inline void AdvanceShot(cinema* self, float dt) {
        reinterpret_cast<AdvanceShot_t>(meridian::rebase(0x00472b60))(self, dt);
    }

    // cinema::OnAdvanceLogic — per-frame tick (deferred Start, transitions, shot
    // timing, skippability). 0x0046a1f0
    using OnAdvanceLogic_t = void(__thiscall*)(cinema* self, float dt);
    inline void OnAdvanceLogic(cinema* self, float dt) {
        reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x0046a1f0))(self, dt);
    }

    // cinema::RuntimeUpdateAll — one-time pre-playback prep (audio lengths, sync
    // points, shot times, cameras). 0x00473410
    using RuntimeUpdateAll_t = void(__thiscall*)(cinema* self);
    inline void RuntimeUpdateAll(cinema* self) {
        reinterpret_cast<RuntimeUpdateAll_t>(meridian::rebase(0x00473410))(self);
    }

    // cinema::IsFinished — bit1 (CINEMA_FINISHED) of flags. 0x0046adc0
    using IsFinished_t = int(__thiscall*)(cinema* self);
    inline int IsFinished(cinema* self) {
        return reinterpret_cast<IsFinished_t>(meridian::rebase(0x0046adc0))(self);
    }

    // cinema::IsSkippable — may this cinema be skipped now? 0x00472f30
    using IsSkippable_t = int(__thiscall*)(cinema* self);
    inline int IsSkippable(cinema* self) {
        return reinterpret_cast<IsSkippable_t>(meridian::rebase(0x00472f30))(self);
    }

    // cinema::EnableConversationMode — enter (nonzero) / exit (0) conversation
    // mode for participants + Bilbo. 0x0046add0
    using EnableConversationMode_t = void(__thiscall*)(cinema* self, int enable);
    inline void EnableConversationMode(cinema* self, int enable) {
        reinterpret_cast<EnableConversationMode_t>(meridian::rebase(0x0046add0))(self, enable);
    }

    // cinema::ResetSyncPoint — clear the 'reached' bit on every shot whose index
    // matches shotIndex. 0x00472b20
    using ResetSyncPoint_t = void(__thiscall*)(cinema* self, int shotIndex);
    inline void ResetSyncPoint(cinema* self, int shotIndex) {
        reinterpret_cast<ResetSyncPoint_t>(meridian::rebase(0x00472b20))(self, shotIndex);
    }

    // cinema::UpdateSyncPoint — recompute one sync point's absolute trigger time.
    // 0x00473650
    using UpdateSyncPoint_t = void(__thiscall*)(cinema* self, int syncIndex);
    inline void UpdateSyncPoint(cinema* self, int syncIndex) {
        reinterpret_cast<UpdateSyncPoint_t>(meridian::rebase(0x00473650))(self, syncIndex);
    }

    // cinema::UpdateSyncPointsFromAction — re-sync shots linked to an action.
    // 0x00473ad0
    using UpdateSyncPointsFromAction_t = void(__thiscall*)(cinema* self, int actionIndex);
    inline void UpdateSyncPointsFromAction(cinema* self, int actionIndex) {
        reinterpret_cast<UpdateSyncPointsFromAction_t>(meridian::rebase(0x00473ad0))(self, actionIndex);
    }

    // cinema::UpdateCameras — recompute every camera action's duration. 0x00473bb0
    using UpdateCameras_t = void(__thiscall*)(cinema* self);
    inline void UpdateCameras(cinema* self) {
        reinterpret_cast<UpdateCameras_t>(meridian::rebase(0x00473bb0))(self);
    }

    // cinema::UpdateShotTimes — write camera start times into the sync table.
    // 0x00473b60
    using UpdateShotTimes_t = void(__thiscall*)(cinema* self);
    inline void UpdateShotTimes(cinema* self) {
        reinterpret_cast<UpdateShotTimes_t>(meridian::rebase(0x00473b60))(self);
    }

    // cinema::GetShotDuration — longest action-relative duration for a shot;
    // outActionIndex receives the winning action. 0x00473c60
    using GetShotDuration_t = float(__thiscall*)(cinema* self, int shotIndex, int* outActionIndex);
    inline float GetShotDuration(cinema* self, int shotIndex, int* outActionIndex) {
        return reinterpret_cast<GetShotDuration_t>(meridian::rebase(0x00473c60))(self, shotIndex, outActionIndex);
    }

    // cinema::SetShotCount — resize the shot table. 0x0046b050
    using SetShotCount_t = void(__thiscall*)(cinema* self, int count, int editorFlag);
    inline void SetShotCount(cinema* self, int count, int editorFlag) {
        reinterpret_cast<SetShotCount_t>(meridian::rebase(0x0046b050))(self, count, editorFlag);
    }

    // cinema::SetSyncCount — resize the sync-point table. 0x0046af70
    using SetSyncCount_t = void(__thiscall*)(cinema* self, int count, int editorFlag);
    inline void SetSyncCount(cinema* self, int count, int editorFlag) {
        reinterpret_cast<SetSyncCount_t>(meridian::rebase(0x0046af70))(self, count, editorFlag);
    }

    // cinema::SetActionCount — resize the main action array. 0x0046b3b0
    using SetActionCount_t = void(__thiscall*)(cinema* self, int count, int editorFlag);
    inline void SetActionCount(cinema* self, int count, int editorFlag) {
        reinterpret_cast<SetActionCount_t>(meridian::rebase(0x0046b3b0))(self, count, editorFlag);
    }

    // cinema::SetSkipActionCount — resize the skip-action array. 0x0046b180
    using SetSkipActionCount_t = void(__thiscall*)(cinema* self, int count, int editorFlag);
    inline void SetSkipActionCount(cinema* self, int count, int editorFlag) {
        reinterpret_cast<SetSkipActionCount_t>(meridian::rebase(0x0046b180))(self, count, editorFlag);
    }

    // cinema::OnReset — virtual reset: skip/end/shutdown if active, clear queue,
    // reset every action + sub-manager. 0x00471f10
    using OnReset_t = void(__thiscall*)(cinema* self);
    inline void OnReset(cinema* self) {
        reinterpret_cast<OnReset_t>(meridian::rebase(0x00471f10))(self);
    }

    // cinema::OnObjectDeactivate — Shutdown then chain object::OnObjectDeactivate.
    // 0x004733f0
    using OnObjectDeactivate_t = void(__thiscall*)(cinema* self);
    inline void OnObjectDeactivate(cinema* self) {
        reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004733f0))(self);
    }

    // cinema::OnImport — deserialize from a bin_in stream. 0x0046be00
    using OnImport_t = void(__thiscall*)(cinema* self, bin_in* in);
    inline void OnImport(cinema* self, bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x0046be00))(self, in);
    }

    // cinema::SetProperty — editor/serialization property setter. 0x0046dbc0
    // Takes 'property' by const& in the original; we pass a pointer (incomplete
    // type, do not pass by value). raw: int(cinema*, const char* name, const property&)
    using SetProperty_t = int(__thiscall*)(cinema* self, const char* name, const property* value);
    inline int SetProperty(cinema* self, const char* name, const property* value) {
        return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0046dbc0))(self, name, value);
    }

    // cinema::GetProperty — editor property getter. 0x0046f5f0
    // The original returns 'property' by value via a hidden first param (sret);
    // we expose it as out-param to avoid an incomplete-by-value return.
    // raw: property __thiscall cinema::GetProperty(cinema*, const char* name)
    using GetProperty_t = property*(__thiscall*)(cinema* self, property* outResult, const char* name);
    inline property* GetProperty(cinema* self, property* outResult, const char* name) {
        return reinterpret_cast<GetProperty_t>(meridian::rebase(0x0046f5f0))(self, outResult, name);
    }

    // cinema_camera type-table address accessor (FUN_0046a510): &records[index]
    // of a fixed 0x40-byte name-slot table. raw: char* __cdecl (int index).
    // (analysis FUN_0046a510 -> cinema::GetShotNameSlot, conf 0.55)
    inline void* ShotNameSlot_at() { return meridian::rebase(0x0046a510); }
} // namespace cinema_api

// --------------------- cinema global predicates (__cdecl) --------------------
namespace cinema_global {
    // IsCinemaPlaying — any active or queued cinema? 0x00472df0
    using IsCinemaPlaying_t = int(__cdecl*)();
    inline int IsCinemaPlaying() {
        return reinterpret_cast<IsCinemaPlaying_t>(meridian::rebase(0x00472df0))();
    }

    // IsCinemaDisableControl — is the active cinema disabling player control?
    // 0x00472e70
    using IsCinemaDisableControl_t = int(__cdecl*)();
    inline int IsCinemaDisableControl() {
        return reinterpret_cast<IsCinemaDisableControl_t>(meridian::rebase(0x00472e70))();
    }

    // IsCinemaLowPriority — low-priority bit of the active cinema. 0x00472ec0
    using IsCinemaLowPriority_t = int(__cdecl*)();
    inline int IsCinemaLowPriority() {
        return reinterpret_cast<IsCinemaLowPriority_t>(meridian::rebase(0x00472ec0))();
    }

    // WasSkipCinemaPressed — global skip-cinema input latch. 0x00472fa0
    using WasSkipCinemaPressed_t = int(__cdecl*)();
    inline int WasSkipCinemaPressed() {
        return reinterpret_cast<WasSkipCinemaPressed_t>(meridian::rebase(0x00472fa0))();
    }

    // ResetSkipCinemaPressed — clear the skip-cinema latch. 0x00472fb0
    using ResetSkipCinemaPressed_t = void(__cdecl*)();
    inline void ResetSkipCinemaPressed() {
        reinterpret_cast<ResetSkipCinemaPressed_t>(meridian::rebase(0x00472fb0))();
    }
} // namespace cinema_global

// ----------------------------- cinema_action --------------------------------
namespace cinema_action_api {
    // cinema_action::OnExport — base serializer (Shot/Offset/Duration/SyncPoint/
    // FinishShot/DefaultLength). 0x00475120
    using OnExport_t = void(__thiscall*)(cinema_action* self, int actionIndex, bin_out* out);
    inline void OnExport(cinema_action* self, int actionIndex, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x00475120))(self, actionIndex, out);
    }
} // namespace cinema_action_api

// ----------------------------- cinema_camera --------------------------------
namespace cinema_camera_api {
    // cinema_camera::OnExport — serialize camera fields. 0x00479c70
    using OnExport_t = void(__thiscall*)(cinema_camera* self, int actionIndex, bin_out* out);
    inline void OnExport(cinema_camera* self, int actionIndex, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x00479c70))(self, actionIndex, out);
    }
} // namespace cinema_camera_api

// ----------------------------- cinema_anim ----------------------------------
namespace cinema_anim_api {
    // cinema_anim::OnExport — serialize anim fields. 0x0047ebb0
    using OnExport_t = void(__thiscall*)(cinema_anim* self, int actionIndex, bin_out* out);
    inline void OnExport(cinema_anim* self, int actionIndex, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x0047ebb0))(self, actionIndex, out);
    }
} // namespace cinema_anim_api

// --------------------------- cinema_anim_inst -------------------------------
namespace cinema_anim_inst_api {
    // cinema_anim_inst::OnExport — serialize anim-instance fields. 0x00480370
    using OnExport_t = void(__thiscall*)(cinema_anim_inst* self, int actionIndex, bin_out* out);
    inline void OnExport(cinema_anim_inst* self, int actionIndex, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x00480370))(self, actionIndex, out);
    }
} // namespace cinema_anim_inst_api

// ----------------------------- cinema_popto ---------------------------------
namespace cinema_popto_api {
    // cinema_popto::Execute — teleport/reposition target(s) to the stored transform.
    // 0x004754f0
    using Execute_t = void(__thiscall*)(cinema_popto* self);
    inline void Execute(cinema_popto* self) {
        reinterpret_cast<Execute_t>(meridian::rebase(0x004754f0))(self);
    }
} // namespace cinema_popto_api

// ----------------------------- cinema_fx ------------------------------------
namespace cinema_fx_api {
    // cinema_fx::cinema_fx — ctor (intensity 1.0, near 0.15, far 20.0, RGBA black/opaque).
    // 0x0047a3c0
    using ctor_t = void(__thiscall*)(cinema_fx* self);
    inline void ctor(cinema_fx* self) {
        reinterpret_cast<ctor_t>(meridian::rebase(0x0047a3c0))(self);
    }
} // namespace cinema_fx_api

// ------------------------- cinema_fxobj_trigger -----------------------------
namespace cinema_fxobj_trigger_api {
    // cinema_fxobj_trigger::Execute — edge-triggered fxobj query/fire. 0x00603a70
    using Execute_t = void(__thiscall*)(cinema_fxobj_trigger* self);
    inline void Execute(cinema_fxobj_trigger* self) {
        reinterpret_cast<Execute_t>(meridian::rebase(0x00603a70))(self);
    }
} // namespace cinema_fxobj_trigger_api

// ----------------------------- cinema_script --------------------------------
namespace cinema_script_api {
    // cinema_script::Execute — fire the shared active-cinema trigger helper.
    // 0x00472e20
    using Execute_t = void(__thiscall*)(cinema_script* self);
    inline void Execute(cinema_script* self) {
        reinterpret_cast<Execute_t>(meridian::rebase(0x00472e20))(self);
    }
} // namespace cinema_script_api

// ----------------------------- ConversationMgr ------------------------------
namespace conversation_mgr_api {
    // ConversationMgr::OnImport — deserialize conversations/dialogs. 0x0059d750
    using OnImport_t = void(__thiscall*)(ConversationMgr* self, bin_in* in);
    inline void OnImport(ConversationMgr* self, bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x0059d750))(self, in);
    }

    // ConversationMgr::SetProperty — editor/serialization property setter.
    // raw: int(ConversationMgr*, const char* name, const property&). 0x0059ed80
    using SetProperty_t = int(__thiscall*)(ConversationMgr* self, const char* name, const property* value);
    inline int SetProperty(ConversationMgr* self, const char* name, const property* value) {
        return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0059ed80))(self, name, value);
    }

    // ConversationMgr::GetProperty — property getter; returns 'property' by value
    // via a hidden sret first param. raw: property __thiscall (const char* name).
    // 0x005a0fa0
    using GetProperty_t = property*(__thiscall*)(ConversationMgr* self, property* outResult, const char* name);
    inline property* GetProperty(ConversationMgr* self, property* outResult, const char* name) {
        return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005a0fa0))(self, outResult, name);
    }
} // namespace conversation_mgr_api

// =============================================================================
// 4. Usage recipes (trainer / modding)
// =============================================================================
//
//  --- Skip the current cutscene -------------------------------------------
//    if (cinema_sdk::cinema_global::IsCinemaPlaying()) {
//        // Resolve the live active cinema object (e.g. via your obj_mgr helper
//        // using the active-cinema GUID), reinterpret_cast it, then:
//        cinema* c = /* resolved cinema* */;
//        if (cinema_sdk::cinema_api::IsSkippable(c))
//            cinema_sdk::cinema_api::Skip(c);   // fast-forwards to End()
//    }
//
//  --- Force-end a cutscene now (and advance the queue) --------------------
//    cinema_sdk::cinema_api::ShutdownAndAdvance(c);   // == Shutdown(c, 1)
//
//  --- Query whether player control is locked by a cinema ------------------
//    bool controlLocked = cinema_sdk::cinema_global::IsCinemaDisableControl() != 0;
//
//  --- Inspect cutscene state via the layout (read-only) -------------------
//    auto* L = reinterpret_cast<cinema_sdk::cinema_layout*>(c);
//    bool active   = (L->flags & cinema_sdk::CINEMA_ACTIVE)   != 0;
//    bool finished = (L->flags & cinema_sdk::CINEMA_FINISHED) != 0;
//    short shot    = L->currentShot;     // current shot index (-1 = none)
//
//  --- Simulate a skip-button press (consumed by skip-input handling) ------
//    // Set the latch via the engine's input path; clear it after consumption:
//    cinema_sdk::cinema_global::ResetSkipCinemaPressed();
//
// =============================================================================

} // namespace cinema_sdk
