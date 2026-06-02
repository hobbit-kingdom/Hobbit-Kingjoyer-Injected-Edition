// =============================================================================
// levels_sdk.h  —  THE HOBBIT (2003) PC build, Entropy engine (MSVC, 32-bit)
//
// Reverse-engineered SDK wrappers for the "levels" / world-flow subsystem:
//   - level (abstract base) + per-chapter subclasses (hobbiton, laketown,
//     lonelymountain, smaug, overhill, roastmutton, swordlight, mirkwood,
//     cloudsburst, ...) and the LevelCreate / LevelDestroy factory
//   - LevelLoader (streaming pipeline open/close + manual resource list)
//   - LevelSelect (LS_LevelSelect / LS_DisplayMenu) and the dlg_LevelMap book
//   - LoadScreen, load_trigger (streaming/teleport volumes)
//   - Save system: level::SaveState/RestoreState (checkpoint anchor),
//     save_pedestal, save_mgr, LoadSaveMgr_PC
//   - rsc_mgr / obj_mgr helpers leaned on by level init & streaming
//
// Legitimate RE of the user's own game for a modding / trainer SDK.
//
// All addresses are PREFERRED-base (image base 0x00400000, ASLR off). Resolve at
// runtime with meridian::rebase(0xADDR); set meridian::g_delta once at init if
// the image is loaded at a non-preferred base. Calling convention is __thiscall
// (this in ECX, first wrapper arg) unless a typedef says __cdecl.
//
// Struct layouts are CONSOLIDATED from the per-chunk analyses (levels__00..03).
// Only well-evidenced fields are named; everything else is byte-accurate padding
// so named members land at their true offsets. Offsets marked "?" are lower
// confidence. These structs are NOT meant to be instantiated — reinterpret_cast
// them onto a live engine object (e.g. the slot resolved from a level/object GUID).
//
// NOTE ON NAME COLLISIONS: the engine type "level" is global-qualified as ::level
// inside wrappers so that this header is immune to `using namespace std;`.
// =============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/bbox/xstring/xarray<T>, level, ...

// ---- Forward declarations for types meridian_types.h does not already cover --
// (level, level_*, load_trigger, save_pedestal, save_mgr, rsc_mgr, obj_mgr,
//  object, bilbo, bitstream, bin_in, bin_out, ui_win, ui_manager, dlg_LevelMap,
//  catapult, mine_cart_ride, irect, dialog_tem are already forward-declared
//  in meridian_types.h; we add only what it omits.)
struct LoadSaveMgr_PC;            // PC save-slot file loader
struct static_textin_loader;      // declared in meridian_types.h, kept here for clarity

namespace levels_sdk {

// =============================================================================
// 1. Enums / constants
// =============================================================================

// level_lonelymountain::roomStateBits — packed bitfield at +0x1630.
// (SetTreasuryActive / SetGearRoomActive / SetForgeBellowsActive / SaveState)
enum LonelyMountainRoomBit : std::uint32_t {
    LM_BELLOWS_ACTIVE        = 0x00000020, // forge bellows water section active
    LM_FORGE_WATER_ACTIVE    = 0x00000040, // forge water section active
    LM_GEAR_ROOM_ACTIVE      = 0x00000080, // gear-room water section active
    LM_TREASURY_ACTIVE       = 0x00000100, // treasury room active
    LM_TREASURY_PHASE        = 0x00002000, // treasury puzzle phase bit
    LM_TREASURY_INTRO_PLAYED = 0x00008000, // treasury intro cinema played (one-shot)
    LM_SECRET_WATER_DOORS    = 0x00020000, // secret water doors active
    LM_ROPE_RIVER_PHASE      = 0x000C0000, // rope-river phase (2 bits)
    LM_TREASURY_REWARD_GIVEN = 0x00100000, // treasury courage reward given (one-shot)
    LM_BELLOWS_COURAGE_DONE  = 0x00200000, // bellows courage pickups spawned (one-shot)
};

// level_hobbiton door/gate FSM states (LogGateState / state handlers).
enum HobbitonGateState : std::int32_t {
    GATE_CLOSED_IDLE   = 0,
    GATE_CLOSED_IMPACT = 1,
    GATE_OPEN_IDLE     = 2,
    GATE_OPEN_IMPACT   = 3,
    GATE_CLOSING       = 4,
};

// level_overhill rock-fall mode (rockFallMode @ +0x104).
enum OverhillRockFallMode : std::int32_t {
    ROCKFALL_NONE   = 0,
    ROCKFALL_LIGHT  = 1,
    ROCKFALL_MEDIUM = 2,
};

// level_laketown::SetDoorState — door animation state arg.
enum LaketownDoorState : std::int32_t {
    LT_DOOR_CLOSING      = 0,
    LT_DOOR_PARTLY_OPEN  = 1,
    LT_DOOR_OPEN         = 2,
};

// =============================================================================
// 2. Recovered struct layouts
//
// Packed to 1 byte so every named member lands at exactly the documented byte
// offset (the engine objects are MSVC 32-bit and not naturally aligned for our
// reordered uint64 GUID fields). These are reinterpret_cast views, never owned.
// =============================================================================
#pragma pack(push, 1)

// level — abstract base. Base size ~0x104 (LevelCreate default subclass size).
// Subclass-specific state begins after this (typically +0x104 / +0x108).
struct level_layout {
    /* 0x000 */ std::uint32_t vtable;   // void** (ptr32) virtual Init/Kill/AdvanceLogic/Save/Restore
    /* 0x004 */ xstring  levelName;  // set via FUN_00647d10(this+4, "Ch01_Hobbiton" / "Overhill")
    /* 0x030 */ std::uint8_t _pad030[0x104 - 0x30]; // remainder of base (opaque)
};

// level_hobbiton (Ch01) — size 0x270.
struct level_hobbiton_layout {
    /* 0x000 */ std::uint8_t _base[0x120];           // level base + early fields
    /* 0x120 */ std::uint64_t doorGuid[3];           // 3 door GUIDs (+0x120/0x128/0x130)
    /* 0x138 */ std::uint8_t _pad138[0x168 - 0x138];
    /* 0x168 */ float        lilyStateTimer;         // per-state elapsed timer (Lily actors)
    /* 0x16c */ std::uint32_t doorOpenMask;           // runtime door-open bitmask
    /* 0x170 */ std::uint32_t doorOpenMaskSaved;      // SaveState; RestoreState stores cursor
    /* 0x174 */ std::uint8_t _pad174[0x190 - 0x174];
    /* 0x190 */ std::uint8_t lilyStates[7 * 4];       // stride 4: +0x00 cur, +0x1c next, -0x1c prev
    /* 0x1ac */ float        gateStates[8];           // per-channel gate FSM state (idx*4) [?]
    /* 0x1cc */ std::uint8_t _pad1cc[0x264 - 0x1cc];
    /* 0x264 */ std::int16_t doorState0;              // door FSM state (stride 0x10)
    /* 0x266 */ std::uint8_t _pad266[0x274 - 0x266];
    /* 0x274 */ std::int16_t doorState1;
    /* 0x276 */ std::uint8_t _pad276[0x284 - 0x276];
    /* 0x284 */ std::int16_t doorState2;
};

// level_roastmutton (Ch02) — size 0x1b8.
struct level_roastmutton_layout {
    /* 0x000 */ std::uint8_t _base[0x108];
    /* 0x108 */ std::uint32_t landslideTriggerGuidLo;
    /* 0x10c */ std::uint32_t landslideTriggerGuidHi;
    /* 0x110 */ std::int32_t  startedFlag;            // set 1 once landslide trigger fires
    /* 0x114 */ std::int32_t  activeFlag;             // gates the 20s timed sequence
    /* 0x118 */ float         startTime;              // game-clock at sequence start
    /* 0x11c */ std::uint8_t  _pad11c[0x150 - 0x11c];
    /* 0x150 */ std::uint32_t effectArray0;           // xstring* arrays freed in DisableEffects (ptr32)
    /* 0x154 */ std::uint32_t effectArray1;
    /* 0x158 */ std::uint32_t effectArray2;
    /* 0x15c */ std::uint8_t  _pad15c[0x17c - 0x15c];
    /* 0x17c */ std::int32_t  cicadaLoopSoundHandle;  // CicadaChorus_Loop handle
};

// level_overhill (Ch04).
struct level_overhill_layout {
    /* 0x000 */ std::uint8_t  _base[0x104];
    /* 0x104 */ std::int32_t  rockFallMode;           // OverhillRockFallMode
    /* 0x108 */ std::uint8_t  _pad108[0x110 - 0x108];
    /* 0x110 */ std::int32_t  stopTriggerCount;
    /* 0x114 */ std::uint8_t  _pad114[0x148 - 0x114];
    /* 0x148 */ std::int32_t  mediumTriggerCount;
    /* 0x14c */ std::uint8_t  _pad14c[0x164 - 0x14c];
    /* 0x164 */ std::int32_t  rockPointCount;
    /* 0x168 */ std::uint32_t rockPointGuids;         // uint64* base of rock-point GUID array (ptr32)
};

// level_swordlight (Ch05). Mine-cart-ride save state lives in &DAT_0075b318.
struct level_swordlight_layout {
    /* 0x000 */ std::uint8_t  _base[0x108];
    /* 0x108 */ std::uint64_t mineCartA_Guid;
    /* 0x110 */ std::uint64_t mineCartA002_Guid;
    /* 0x118 */ std::uint64_t mineCartA1_Guid;
    /* 0x120 */ std::uint8_t  _pad120[0x150 - 0x120];
    /* 0x150 */ std::uint64_t gateGuids[7];           // CheckGate reads +param*8
    /* 0x188 */ float         gateCooldownTimers[7];  // CheckGate gate '5.0 < timer'
};

// level_laketown::gas_pipe — element of the gas-pipe xarray (size 0x58).
struct laketown_gas_pipe_layout {
    /* 0x00 */ char         name[0x20];
    /* 0x20 */ std::int32_t gridX;
    /* 0x24 */ std::int32_t gridY;
    /* 0x28 */ float        curCoord;     // decremented as a timer in AdvanceGasPuzzle
    /* 0x2c */ float        fireCount;
    /* 0x30 */ vector3      endA;         // line endpoint from object getter
    /* 0x3c */ vector3      endB;
    /* 0x48 */ std::uint64_t fxModelGuid;
    /* 0x50 */ std::int32_t baseCount;
    /* 0x54 */ std::int32_t activeFxHandle; // GasTrap FX handle
};

// level_laketown — large; only the puzzle blocks are mapped. Some offsets are
// aliased between the pressure-plate, gas, and door-switch puzzles.
struct level_laketown_layout {
    /* 0x000 */ std::uint8_t  _base[0x2a8];
    /* 0x2a8 */ std::uint32_t saveScalar0;
    /* 0x2ac */ std::int32_t  ppPuzzleState[7];        // also doorSwitchGuid[4] (0x20-bit in save)
    /* 0x2c8 */ std::uint64_t barrelLiteGuid;          // / waterVolumeGuidA
    /* 0x2d0 */ std::uint64_t barrelMedGuid;           // / waterVolumeGuidB
    /* 0x2d8 */ std::uint64_t barrelHvyGuid;           // / waterVolumeGuidC
    /* 0x2e0 */ std::uint8_t  _pad2e0[0x2f0 - 0x2e0];
    /* 0x2f0 */ std::uint8_t  torchRecords[2 * 0x40];  // stride 0x40; GUID keys at +0,+0x10,-0x10
    /* 0x370 */ std::uint8_t  _pad370[0x408 - 0x370];
    /* 0x408 */ std::uint64_t gasEntrySwitchGuid;
    /* 0x410 */ std::uint64_t gasExitSwitchGuid;
    /* 0x418 */ std::uint64_t gasToggleSwitchGuid;
    /* 0x420 */ std::int32_t  gasPuzzleActive;         // set 1 after pipes built
    /* 0x424 */ std::int32_t  gasPuzzleEnabled;
    /* 0x428 */ std::int32_t  gasEntrySwitchLast;
    /* 0x42c */ std::int32_t  gasExitSwitchLast;
    /* 0x430 */ std::int32_t  gasToggleSwitchLast;
    /* 0x434 */ float         gasHitCooldown;          // sentinel -1.0 (0xbf800000)
    /* 0x438 */ float         gasFillLevel;            // 2.5f when toggle on
    /* 0x43c */ std::uint8_t  gasPipesHdr[8];          // xarray<gas_pipe> header (+0x08 size)
    /* 0x444 */ std::int32_t  gasPipeCount;
    /* 0x448 */ std::uint32_t gasPipeArray;             // laketown_gas_pipe_layout* (ptr32)
    /* 0x44c */ std::uint8_t  _pad44c[0x450 - 0x44c];
    /* 0x450 */ std::int32_t  gasPipeOwnsArray;
    /* 0x454 */ std::uint8_t  _pad454[0x458 - 0x454];
    /* 0x458 */ std::uint64_t wallSwitchGuid[4];       // also doorSwitchPuzzles[3] (stride 0x20)
    /* 0x478 */ std::uint64_t wh2DoorGuid[2];          // door rigid_instance GUIDs
    /* 0x488 */ std::uint8_t  _pad488[0x4b8 - 0x488];
    /* 0x4b8 */ std::uint64_t doorCamGuid[2];
};

// level_lonelymountain — very large; sub-puzzle objects embedded by value.
struct level_lonelymountain_layout {
    /* 0x000 */ std::uint8_t  _base[0x108];
    /* 0x108 */ std::uint8_t  tilePuzzle[0x178 - 0x108];   // tile_puzzle (embedded)
    /* 0x178 */ std::uint8_t  forgePuzzle[0x260 - 0x178];  // forge_puzzle (embedded)
    /* 0x260 */ std::uint64_t bellowsCinemaGuid;
    /* 0x268 */ std::uint64_t coolerCinemaGuid;
    /* 0x270 */ std::uint8_t  fx[0x2a0 - 0x270];           // lonely_mountain_fx (embedded)
    /* 0x2a0 */ std::uint64_t checkpointTriggerGuids[4];
    /* 0x2c0 */ std::uint8_t  _pad2c0[0x2d0 - 0x2c0];
    /* 0x2d0 */ std::int32_t  failedTriggerIndex;
    /* 0x2d4 */ std::uint8_t  _pad2d4[0x2d8 - 0x2d4];
    /* 0x2d8 */ std::uint8_t  waterPuzzleA[0xc18 - 0x2d8]; // water_puzzle (embedded)
    /* 0xc18 */ std::uint8_t  waterPuzzleB[0x1560 - 0xc18];// water_puzzle (embedded)
    /* 0x1560 */ std::uint64_t secretCanalLoadTriggerGuid;
    /* 0x1568 */ std::uint64_t gearRoomOffCinemaGuid;
    /* 0x1570 */ std::uint64_t gearRoomOnCinemaGuid;
    /* 0x1578 */ std::uint64_t treasuryItemTriggerGuid;    // compared to "Chain"
    /* 0x1580 */ std::uint8_t  _pad1580[0x15a0 - 0x1580];
    /* 0x15a0 */ std::uint64_t treasuryAuxGuid;
    /* 0x15a8 */ std::uint16_t saveField15a8;
    /* 0x15aa */ std::uint8_t  _pad15aa[0x15c8 - 0x15aa];
    /* 0x15c8 */ std::uint16_t treasurySubState;           // ==2 path in SetTreasuryActive
    /* 0x15ca */ std::uint8_t  _pad15ca[0x15e8 - 0x15ca];
    /* 0x15e8 */ std::uint64_t treasuryCinemaGuidA;
    /* 0x15f0 */ std::uint64_t treasuryCinemaGuidB;
    /* 0x15f8 */ std::int32_t  stonePillarLoopSoundHandle;
    /* 0x15fc */ std::uint8_t  _pad15fc[0x1600 - 0x15fc];
    /* 0x1600 */ std::uint64_t bellowsLoadTriggerGuid;
    /* 0x1608 */ std::uint8_t  _pad1608[0x1630 - 0x1608];
    /* 0x1630 */ std::uint32_t roomStateBits;              // LonelyMountainRoomBit
    /* 0x1634 */ std::int32_t  savedDwordsA[2];
    /* 0x163c */ std::int32_t  secretCanalDone[2];
    /* 0x1644 */ std::uint8_t  _pad1644[0x164c - 0x1644];
    /* 0x164c */ std::int32_t  secretCanalActive[2][4];
};

// level_smaug.
struct level_smaug_layout {
    /* 0x000 */ std::uint8_t  _base[0x108];
    /* 0x108 */ std::uint8_t  triggerGuidLo[5];   // CONCAT5 with +0x10c -> 64-bit GUID
    /* 0x10d */ std::uint8_t  _pad10d[3];
    /* 0x110 */ std::int32_t  endSequenceDone;
    /* 0x114 */ std::int32_t  goldCinemaDone;
};

// level_mirkwood.
struct level_mirkwood_layout {
    /* 0x000 */ std::uint8_t  _base[0x108];
    /* 0x108 */ std::int32_t  sequenceEnabled;
    /* 0x10c */ std::int32_t  stateIndex;          // switch cases 0,1,2,4,6,8,9
    /* 0x110 */ float         stateTimer;          // 5.0f gate
};

// level_cloudsburst (Ch11).
struct level_cloudsburst_layout {
    /* 0x000 */ std::uint8_t  _base[0x104];
    /* 0x104 */ std::uint32_t catapultPtr;         // catapult* heap-allocated (0x88) (ptr32)
};

// load_trigger (extends volume). Editor (OnExport) view; some offsets alias the
// runtime (OnImport) layer-list fields — see the docs for the full overlap.
struct load_trigger_layout {
    /* 0x000 */ std::uint8_t  _baseVolume[0x7a];
    /* 0x07a */ std::uint16_t volumeFlags;          // OnImport |= 1
    /* 0x07c */ std::uint8_t  _pad07c[0x100 - 0x7c];
    /* 0x100 */ float         cellSize;
    /* 0x104 */ std::int32_t  nXCells;
    /* 0x108 */ std::int32_t  nZCells;              // also LoadObjects layer-list count
    /* 0x10c */ std::uint32_t loadLayers;           // xarray* (runtime) / particleArray0 (editor) (ptr32)
    /* 0x110 */ std::int32_t  loadLayerCount;
    /* 0x114 */ std::int32_t  loadLayerMarker;      // xarray own-flag (!=2 owned)
    /* 0x118 */ std::uint8_t  minAlpha;
    /* 0x119 */ std::uint8_t  maxAlpha;
    /* 0x11a */ std::uint8_t  _pad11a[2];
    /* 0x11c */ float         pushScale;            // editor; unloadLayers xarray at runtime
    /* 0x120 */ float         pullScale;
    /* 0x124 */ float         forceScalar;          // editor; unloadLayerCount at runtime
    /* 0x128 */ float         viscosity;
    /* 0x12c */ float         sleepDist;
    /* 0x130 */ std::int32_t  moveMode;
    /* 0x134 */ std::int32_t  boundMode;
    /* 0x138 */ vector3       moveVec;              // editor; teleportTarget xstring at runtime
    /* 0x144 */ float         moveScale;
    /* 0x148 */ float         vDamp;
    /* 0x14c */ std::int32_t  threshold;
    /* 0x150 */ std::uint32_t color;                // color32
    /* 0x154 */ std::int32_t  painType;
    /* 0x158 */ float         painFreq;
    /* 0x15c */ float         poisonDur;
    /* 0x160 */ float         painAmt;
    /* 0x164 */ std::uint8_t  _pad164[0x170 - 0x164];
    /* 0x170 */ std::uint32_t particleArray3;       // xarray* (ptr32)
};

// save_pedestal (extends prop/object).
struct save_pedestal_layout {
    /* 0x000 */ std::uint8_t  _base[0x08];
    /* 0x008 */ std::uint64_t selfGuid;
    /* 0x010 */ std::uint8_t  _pad010[0x160 - 0x10];
    /* 0x160 */ std::uint32_t hasSave;
    /* 0x164 */ vector3       respawnPos;
    /* 0x170 */ float         respawnHeading;
    /* 0x174 */ float         saveTimestamp;
    /* 0x178 */ std::uint8_t  _pad178[0x180 - 0x178];
    /* 0x180 */ std::uint64_t fxHandle;             // aura/sound FX (OnObjectDeactivate releases)
    /* 0x188 */ std::uint64_t lockedObjectGuid;     // / auraFxHandle
};

// save_mgr — save-blob serializer. Pointer fields are stored as target-width
// 32-bit (ptr32) so offsets stay byte-exact on a 64-bit host build too.
struct save_mgr_layout {
    /* 0x00 */ std::uint32_t   buffer;             // char*  (target ptr32)
    /* 0x04 */ std::int32_t    usedBytes;
    /* 0x08 */ std::int32_t    capacity;
    /* 0x0c */ std::int32_t    recordCount;
    /* 0x10 */ std::uint8_t    _pad10[0x1c - 0x10];
    /* 0x1c */ std::uint32_t   keyTableA;          // uint16* (target ptr32)
    /* 0x20 */ std::uint8_t    _pad20[0x38 - 0x20];
    /* 0x38 */ std::uint32_t   keyTableB;          // uint16* (target ptr32)
    /* 0x3c */ std::uint8_t    _pad3c[0x50 - 0x3c];
    /* 0x50 */ std::int32_t    entryCount;
    /* 0x54 */ std::uint32_t   entryTable;         // uint16* — 4-byte records (u16 key, u16 count)
    /* 0x58 */ std::uint8_t    _pad58[0x88 - 0x58];
    /* 0x88 */ std::int32_t    pairCount;
    /* 0x8c */ std::uint32_t   pairTable;          // pair* — 8-byte records (u32 key, u32 val)
};

// LevelSelect control block (global DAT_0075f930). Element stride 0xa4.
struct level_select_ctx_layout {
    /* 0x00 */ std::int32_t   elementCount;
    /* 0x04 */ std::uint32_t  elements;             // ptr32; stride 0xa4 (thumbnail +0x80, locked +0xa0)
    /* 0x08 */ std::uint8_t   _pad08[0x14 - 0x08];
    /* 0x14 */ std::uint8_t   window[0x10];         // ui_win member (opaque)
};

// dlg_LevelMap — page-turn book dialog (size 0x1c4).
struct dlg_LevelMap_layout {
    /* 0x000 */ std::uint8_t  _base[0x158];
    /* 0x158 */ std::uint32_t pageNodeWidgets[(0x18c - 0x158) / 4 + 1]; // ui_win* per page node (ptr32)
    /* 0x190 */ std::uint8_t  _pad190[0x1bc - 0x190];
    /* 0x1bc */ std::uint32_t extraNode;            // ui_win* (still triggers UpdateAfterLevel) (ptr32)
    /* 0x1c0 */ std::uint32_t backButton;           // ui_win* (dismiss) (ptr32)
};

#pragma pack(pop)

// =============================================================================
// 3. Function wrappers, grouped by class
//
//   __thiscall methods take the object pointer as the FIRST argument.
//   Incomplete-by-value engine types are passed by pointer; where a value-return
//   is involved we expose the raw signature in a comment.
// =============================================================================

// ----------------------------- level factory (__cdecl) ----------------------
namespace level_factory {
    // LevelCreate — chapter name -> new subclass with vtable. 0x004196a0
    using LevelCreate_t = ::level*(__cdecl*)(const char* chapterName);
    inline ::level* LevelCreate(const char* chapterName) {
        return reinterpret_cast<LevelCreate_t>(meridian::rebase(0x004196a0))(chapterName);
    }

    // LevelDestroy — invoke the level's vector deleting dtor (vtable[0], free bit). 0x00419ff0
    using LevelDestroy_t = void(__cdecl*)(::level* self);
    inline void LevelDestroy(::level* self) {
        reinterpret_cast<LevelDestroy_t>(meridian::rebase(0x00419ff0))(self);
    }

    // LevelGetDialogPackage — build "Audio\<region>\<pkg>" path into out. 0x00419620
    // raw: void __cdecl LevelGetDialogPackage(char* out, const char* pkgName)
    using LevelGetDialogPackage_t = void(__cdecl*)(char* out, const char* pkgName);
    inline void LevelGetDialogPackage(char* out, const char* pkgName) {
        reinterpret_cast<LevelGetDialogPackage_t>(meridian::rebase(0x00419620))(out, pkgName);
    }
} // namespace level_factory

// ----------------------------- level (base) ---------------------------------
namespace level_api {
    // level::SaveState — write active save-pedestal GUID (64-bit) checkpoint
    // anchor to the bitstream. 0x0041a060
    using SaveState_t = void(__thiscall*)(::level* self, bitstream* stream);
    inline void SaveState(::level* self, bitstream* stream) {
        reinterpret_cast<SaveState_t>(meridian::rebase(0x0041a060))(self, stream);
    }

    // level::RestoreState — read 64-bit save-pedestal GUID, install it. 0x0041a080
    using RestoreState_t = void(__thiscall*)(::level* self, bitstream* stream);
    inline void RestoreState(::level* self, bitstream* stream) {
        reinterpret_cast<RestoreState_t>(meridian::rebase(0x0041a080))(self, stream);
    }
} // namespace level_api

// ----------------------------- level_hobbiton -------------------------------
namespace level_hobbiton_api {
    // level_hobbiton::Init — Ch01 init (heap 0xe1000, name, audio, apple GUIDs). 0x00410c80
    using Init_t = void(__thiscall*)(level_hobbiton* self);
    inline void Init(level_hobbiton* self) {
        reinterpret_cast<Init_t>(meridian::rebase(0x00410c80))(self);
    }

    // level_hobbiton::SetGateState — write new gate state at +0x1ac+idx*4 + log.
    // (FUN_004118d0, proposed name, conf 0.6) 0x004118d0
    // raw: void __thiscall (level_hobbiton*, int channelIndex, float state)
    using SetGateState_t = void(__thiscall*)(level_hobbiton* self, int channelIndex, float state);
    inline void SetGateState(level_hobbiton* self, int channelIndex, float state) {
        reinterpret_cast<SetGateState_t>(meridian::rebase(0x004118d0))(self, channelIndex, state);
    }

    // level_hobbiton::LogGateState — state enum -> name string debug log.
    // (mislabeled "AdvanceLogic" in symbol map, conf 0.7) 0x00411c90
    using LogGateState_t = void(__thiscall*)(level_hobbiton* self, int state);
    inline void LogGateState(level_hobbiton* self, int state) {
        reinterpret_cast<LogGateState_t>(meridian::rebase(0x00411c90))(self, state);
    }

    // level_hobbiton::StateAdvanceOPEN_IMPACT — door anim end -> OPEN_IDLE. 0x004119c0
    using StateAdvanceOPEN_IMPACT_t = void(__thiscall*)(level_hobbiton* self, int doorIndex);
    inline void StateAdvanceOPEN_IMPACT(level_hobbiton* self, int doorIndex) {
        reinterpret_cast<StateAdvanceOPEN_IMPACT_t>(meridian::rebase(0x004119c0))(self, doorIndex);
    }

    // level_hobbiton::StateEnterOPEN_IDLE — idle_open anim, set open bit. 0x00411a00
    using StateEnterOPEN_IDLE_t = void(__thiscall*)(level_hobbiton* self, int doorIndex);
    inline void StateEnterOPEN_IDLE(level_hobbiton* self, int doorIndex) {
        reinterpret_cast<StateEnterOPEN_IDLE_t>(meridian::rebase(0x00411a00))(self, doorIndex);
    }

    // level_hobbiton::StateEnterCLOSING — closing anim, clear open bit. 0x00411ae0
    using StateEnterCLOSING_t = void(__thiscall*)(level_hobbiton* self, int doorIndex);
    inline void StateEnterCLOSING(level_hobbiton* self, int doorIndex) {
        reinterpret_cast<StateEnterCLOSING_t>(meridian::rebase(0x00411ae0))(self, doorIndex);
    }

    // level_hobbiton::StateAdvanceCLOSING — closing anim end -> CLOSED. 0x00411b60
    using StateAdvanceCLOSING_t = void(__thiscall*)(level_hobbiton* self, int doorIndex);
    inline void StateAdvanceCLOSING(level_hobbiton* self, int doorIndex) {
        reinterpret_cast<StateAdvanceCLOSING_t>(meridian::rebase(0x00411b60))(self, doorIndex);
    }

    // level_hobbiton::LilyStateAdvance — 7 Lily actors FSM tick. 0x00411ba0
    using LilyStateAdvance_t = void(__thiscall*)(level_hobbiton* self, float dt);
    inline void LilyStateAdvance(level_hobbiton* self, float dt) {
        reinterpret_cast<LilyStateAdvance_t>(meridian::rebase(0x00411ba0))(self, dt);
    }

    // level_hobbiton::SaveState — base + 3 door states + door-open mask. 0x00411d10
    using SaveState_t = void(__thiscall*)(level_hobbiton* self, bitstream* stream);
    inline void SaveState(level_hobbiton* self, bitstream* stream) {
        reinterpret_cast<SaveState_t>(meridian::rebase(0x00411d10))(self, stream);
    }

    // level_hobbiton::RestoreState — base + door states (deferred mask). 0x00411d60
    using RestoreState_t = void(__thiscall*)(level_hobbiton* self, bitstream* stream);
    inline void RestoreState(level_hobbiton* self, bitstream* stream) {
        reinterpret_cast<RestoreState_t>(meridian::rebase(0x00411d60))(self, stream);
    }
} // namespace level_hobbiton_api

// ----------------------------- level_roastmutton ----------------------------
namespace level_roastmutton_api {
    // level_roastmutton::AdvanceLogic — landslide/storm set-piece tick. 0x00407540
    using AdvanceLogic_t = void(__thiscall*)(level_roastmutton* self, float dt);
    inline void AdvanceLogic(level_roastmutton* self, float dt) {
        reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00407540))(self, dt);
    }

    // level_roastmutton::DisableEffects — restore lights, restart cicada. 0x00407e80
    using DisableEffects_t = void(__thiscall*)(level_roastmutton* self);
    inline void DisableEffects(level_roastmutton* self) {
        reinterpret_cast<DisableEffects_t>(meridian::rebase(0x00407e80))(self);
    }
} // namespace level_roastmutton_api

// ----------------------------- level_overhill -------------------------------
namespace level_overhill_api {
    // level_overhill::Init — Ch04 init (heap 0x4b000, RockFall triggers). 0x00409250
    using Init_t = void(__thiscall*)(level_overhill* self);
    inline void Init(level_overhill* self) {
        reinterpret_cast<Init_t>(meridian::rebase(0x00409250))(self);
    }

    // level_overhill::AdvanceLogic — rock-fall trigger scan + projectile. 0x00409bc0
    using AdvanceLogic_t = void(__thiscall*)(level_overhill* self, float dt);
    inline void AdvanceLogic(level_overhill* self, float dt) {
        reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00409bc0))(self, dt);
    }

    // level_overhill::SetRockPointNear — activate nearest unused rock point.
    // raw: void __thiscall (level_overhill*, vector3& queryPoint, int forceFlag). 0x00409fa0
    using SetRockPointNear_t = void(__thiscall*)(level_overhill* self, vector3* queryPoint, int forceFlag);
    inline void SetRockPointNear(level_overhill* self, vector3* queryPoint, int forceFlag) {
        reinterpret_cast<SetRockPointNear_t>(meridian::rebase(0x00409fa0))(self, queryPoint, forceFlag);
    }
} // namespace level_overhill_api

// ----------------------------- level_swordlight -----------------------------
namespace level_swordlight_api {
    // level_swordlight::CheckGate — gate proximity -> impact FX + push.
    // raw: void __thiscall (level_swordlight*, int gateIndex, const vector3& refPos). 0x004016e0
    using CheckGate_t = void(__thiscall*)(level_swordlight* self, int gateIndex, const vector3* refPos);
    inline void CheckGate(level_swordlight* self, int gateIndex, const vector3* refPos) {
        reinterpret_cast<CheckGate_t>(meridian::rebase(0x004016e0))(self, gateIndex, refPos);
    }

    // level_swordlight::RestoreState — base + mine_cart_ride singleton. 0x00401ee0
    using RestoreState_t = void(__thiscall*)(level_swordlight* self, bitstream* stream);
    inline void RestoreState(level_swordlight* self, bitstream* stream) {
        reinterpret_cast<RestoreState_t>(meridian::rebase(0x00401ee0))(self, stream);
    }
} // namespace level_swordlight_api

// ----------------------------- level_laketown -------------------------------
namespace level_laketown_api {
    // level_laketown::InitPPPuzz — pressure-plate puzzle init. 0x00415070
    using InitPPPuzz_t = void(__thiscall*)(level_laketown* self);
    inline void InitPPPuzz(level_laketown* self) {
        reinterpret_cast<InitPPPuzz_t>(meridian::rebase(0x00415070))(self);
    }

    // level_laketown::AdvancePPPuzz — pressure-plate puzzle tick. 0x004157a0
    using AdvancePPPuzz_t = void(__thiscall*)(level_laketown* self);
    inline void AdvancePPPuzz(level_laketown* self) {
        reinterpret_cast<AdvancePPPuzz_t>(meridian::rebase(0x004157a0))(self);
    }

    // level_laketown::InitDoorSwitchPuzzle — resolve WH2 doors/switches/cams. 0x00414ef0
    using InitDoorSwitchPuzzle_t = void(__thiscall*)(level_laketown* self);
    inline void InitDoorSwitchPuzzle(level_laketown* self) {
        reinterpret_cast<InitDoorSwitchPuzzle_t>(meridian::rebase(0x00414ef0))(self);
    }

    // level_laketown::AdvanceDoorSwitchPuzzle — timed door-switch tick. 0x00416f60
    using AdvanceDoorSwitchPuzzle_t = void(__thiscall*)(level_laketown* self, float dt);
    inline void AdvanceDoorSwitchPuzzle(level_laketown* self, float dt) {
        reinterpret_cast<AdvanceDoorSwitchPuzzle_t>(meridian::rebase(0x00416f60))(self, dt);
    }

    // level_laketown::InitGasPuzzle — build gas-pipe array. 0x00416110
    using InitGasPuzzle_t = void(__thiscall*)(level_laketown* self);
    inline void InitGasPuzzle(level_laketown* self) {
        reinterpret_cast<InitGasPuzzle_t>(meridian::rebase(0x00416110))(self);
    }

    // level_laketown::AdvanceGasPuzzle — gas-pipe tick + GasTrap FX. 0x00416630
    using AdvanceGasPuzzle_t = void(__thiscall*)(level_laketown* self, float dt);
    inline void AdvanceGasPuzzle(level_laketown* self, float dt) {
        reinterpret_cast<AdvanceGasPuzzle_t>(meridian::rebase(0x00416630))(self, dt);
    }

    // level_laketown::UpdateGasPuzzleActivity — entry/exit/toggle FSM. 0x00416870
    using UpdateGasPuzzleActivity_t = void(__thiscall*)(level_laketown* self);
    inline void UpdateGasPuzzleActivity(level_laketown* self) {
        reinterpret_cast<UpdateGasPuzzleActivity_t>(meridian::rebase(0x00416870))(self);
    }

    // level_laketown::SetDoorState — set warehouse-door anim (LaketownDoorState).
    // raw: void __thiscall (level_laketown*, const uint64& doorGuid, int state). 0x00415610
    using SetDoorState_t = void(__thiscall*)(level_laketown* self, const std::uint64_t* doorGuid, int state);
    inline void SetDoorState(level_laketown* self, const std::uint64_t* doorGuid, int state) {
        reinterpret_cast<SetDoorState_t>(meridian::rebase(0x00415610))(self, doorGuid, state);
    }

    // level_laketown::GetMatchingTorch — torch GUID -> companion torch GUID.
    // raw: uint64 __thiscall (level_laketown*, const uint64& torchGuid). 0x00415590
    using GetMatchingTorch_t = std::uint64_t(__thiscall*)(level_laketown* self, const std::uint64_t* torchGuid);
    inline std::uint64_t GetMatchingTorch(level_laketown* self, const std::uint64_t* torchGuid) {
        return reinterpret_cast<GetMatchingTorch_t>(meridian::rebase(0x00415590))(self, torchGuid);
    }

    // level_laketown::SyncBarrelHeights — float barrels to water level. 0x00417340
    using SyncBarrelHeights_t = void(__thiscall*)(level_laketown* self);
    inline void SyncBarrelHeights(level_laketown* self) {
        reinterpret_cast<SyncBarrelHeights_t>(meridian::rebase(0x00417340))(self);
    }

    // level_laketown::SaveState — base + switch/cam GUIDs + scalars + gas pipes. 0x004174d0
    using SaveState_t = void(__thiscall*)(level_laketown* self, bitstream* stream);
    inline void SaveState(level_laketown* self, bitstream* stream) {
        reinterpret_cast<SaveState_t>(meridian::rebase(0x004174d0))(self, stream);
    }

    // level_laketown::RestoreState — base + deferred-read cursors. 0x00417600
    using RestoreState_t = void(__thiscall*)(level_laketown* self, bitstream* stream);
    inline void RestoreState(level_laketown* self, bitstream* stream) {
        reinterpret_cast<RestoreState_t>(meridian::rebase(0x00417600))(self, stream);
    }

    // level_laketown::DestroyObjectByGuid — DestroyObject by GUID + teardown.
    // (FUN_00415550, proposed name, conf 0.55)
    // raw: void __thiscall (level_laketown*, const uint64& guid, int callVirtual). 0x00415550
    using DestroyObjectByGuid_t = void(__thiscall*)(level_laketown* self, const std::uint64_t* guid, int callVirtual);
    inline void DestroyObjectByGuid(level_laketown* self, const std::uint64_t* guid, int callVirtual) {
        reinterpret_cast<DestroyObjectByGuid_t>(meridian::rebase(0x00415550))(self, guid, callVirtual);
    }
} // namespace level_laketown_api

// ----------------------------- level_lonelymountain -------------------------
namespace level_lonelymountain_api {
    // level_lonelymountain::AdvanceLogic — master tick (puzzles, rooms, triggers). 0x0040c130
    using AdvanceLogic_t = void(__thiscall*)(level_lonelymountain* self, float dt);
    inline void AdvanceLogic(level_lonelymountain* self, float dt) {
        reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x0040c130))(self, dt);
    }

    // level_lonelymountain::AdvanceTreasuryPuzzle — chain/cable puzzle tick. 0x0040d560
    using AdvanceTreasuryPuzzle_t = void(__thiscall*)(level_lonelymountain* self);
    inline void AdvanceTreasuryPuzzle(level_lonelymountain* self) {
        reinterpret_cast<AdvanceTreasuryPuzzle_t>(meridian::rebase(0x0040d560))(self);
    }

    // level_lonelymountain::SetGearRoomActive — toggle gear-room (bit 0x80). 0x0040d0e0
    using SetGearRoomActive_t = void(__thiscall*)(level_lonelymountain* self, int active);
    inline void SetGearRoomActive(level_lonelymountain* self, int active) {
        reinterpret_cast<SetGearRoomActive_t>(meridian::rebase(0x0040d0e0))(self, active);
    }

    // level_lonelymountain::SetForgeBellowsActive — toggle bellows (bit 0x20). 0x0040ce00
    using SetForgeBellowsActive_t = void(__thiscall*)(level_lonelymountain* self, int active);
    inline void SetForgeBellowsActive(level_lonelymountain* self, int active) {
        reinterpret_cast<SetForgeBellowsActive_t>(meridian::rebase(0x0040ce00))(self, active);
    }

    // level_lonelymountain::SetTreasuryActive — toggle treasury (bit 0x100). 0x0040d400
    using SetTreasuryActive_t = void(__thiscall*)(level_lonelymountain* self, int active);
    inline void SetTreasuryActive(level_lonelymountain* self, int active) {
        reinterpret_cast<SetTreasuryActive_t>(meridian::rebase(0x0040d400))(self, active);
    }

    // level_lonelymountain::PostHudRender — post-HUD overlay (two passes). 0x0040e010
    using PostHudRender_t = void(__thiscall*)(level_lonelymountain* self);
    inline void PostHudRender(level_lonelymountain* self) {
        reinterpret_cast<PostHudRender_t>(meridian::rebase(0x0040e010))(self);
    }

    // StartGondolas — __cdecl: toggle all 21 "Gondola Car %03d" rigid instances. 0x0040c5e0
    using StartGondolas_t = void(__cdecl*)(int on);
    inline void StartGondolas(int on) {
        reinterpret_cast<StartGondolas_t>(meridian::rebase(0x0040c5e0))(on);
    }
} // namespace level_lonelymountain_api

// ----------------------------- level_mirkwood / smaug / cloudsburst ---------
namespace level_mirkwood_api {
    // level_mirkwood::AdvanceLogic — ring-tutorial FSM tick. 0x00408d10
    using AdvanceLogic_t = void(__thiscall*)(level_mirkwood* self, float dt);
    inline void AdvanceLogic(level_mirkwood* self, float dt) {
        reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00408d10))(self, dt);
    }
} // namespace level_mirkwood_api

namespace level_smaug_api {
    // level_smaug::AdvanceLogic — end-trigger + steps-on-gold cinema. 0x0040a510
    using AdvanceLogic_t = void(__thiscall*)(level_smaug* self, float dt);
    inline void AdvanceLogic(level_smaug* self, float dt) {
        reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x0040a510))(self, dt);
    }

    // level_smaug::RestoreState — bitstream read-back of saved state. 0x0063ce50
    using RestoreState_t = void(__thiscall*)(level_smaug* self, bitstream* stream);
    inline void RestoreState(level_smaug* self, bitstream* stream) {
        reinterpret_cast<RestoreState_t>(meridian::rebase(0x0063ce50))(self, stream);
    }
} // namespace level_smaug_api

namespace level_cloudsburst_api {
    // level_cloudsburst::Init — Ch11 init (heap 0x7d000, catapult sub-object). 0x004134e0
    using Init_t = void(__thiscall*)(level_cloudsburst* self);
    inline void Init(level_cloudsburst* self) {
        reinterpret_cast<Init_t>(meridian::rebase(0x004134e0))(self);
    }
} // namespace level_cloudsburst_api

// ----------------------------- LevelLoader (__cdecl) ------------------------
namespace level_loader_api {
    // LevelLoader_Open — open streaming pipeline (SelectionSets + manual res). 0x004fbe30
    using Open_t = int(__cdecl*)();
    inline int Open() { return reinterpret_cast<Open_t>(meridian::rebase(0x004fbe30))(); }

    // LevelLoader_Close — flush + unload manual resources + free state. 0x004fbf00
    using Close_t = void(__cdecl*)();
    inline void Close() { reinterpret_cast<Close_t>(meridian::rebase(0x004fbf00))(); }

    // LevelLoader_LoadManualResources — read exportres.txt, load .xbmp list. 0x004fb7e0
    using LoadManualResources_t = void(__cdecl*)();
    inline void LoadManualResources() {
        reinterpret_cast<LoadManualResources_t>(meridian::rebase(0x004fb7e0))();
    }

    // LevelLoader_UnloadManualResources — free every manual streamed resource. 0x005c5210
    using UnloadManualResources_t = void(__cdecl*)();
    inline void UnloadManualResources() {
        reinterpret_cast<UnloadManualResources_t>(meridian::rebase(0x005c5210))();
    }
} // namespace level_loader_api

// ----------------------------- LevelSelect (__cdecl) ------------------------
namespace level_select_api {
    // LS_LevelSelect — read LevelList.txt, run selection UI, return chosen level.
    // raw: int __cdecl LS_LevelSelect(char* dir, int mode). 0x004fc380
    using LS_LevelSelect_t = int(__cdecl*)(char* dir, int mode);
    inline int LS_LevelSelect(char* dir, int mode) {
        return reinterpret_cast<LS_LevelSelect_t>(meridian::rebase(0x004fc380))(dir, mode);
    }

    // LS_DisplayMenu — render the level-select thumbnail strip. 0x004fc090
    using LS_DisplayMenu_t = void(__cdecl*)();
    inline void LS_DisplayMenu() {
        reinterpret_cast<LS_DisplayMenu_t>(meridian::rebase(0x004fc090))();
    }
} // namespace level_select_api

// ----------------------------- dlg_LevelMap ---------------------------------
namespace dlg_levelmap_api {
    // dlg_LevelMap::Create — build page-turn book dialog, cache page nodes.
    // raw: int __thiscall Create(dlg_LevelMap*, ui_manager*, dialog_tem*,
    //                            const irect&, ui_win* parent, int, void*). 0x00513770
    using Create_t = int(__thiscall*)(dlg_LevelMap* self, ui_manager* mgr, dialog_tem* tem,
                                      const irect* rect, ui_win* parent, int flags, void* ctx);
    inline int Create(dlg_LevelMap* self, ui_manager* mgr, dialog_tem* tem,
                      const irect* rect, ui_win* parent, int flags, void* ctx) {
        return reinterpret_cast<Create_t>(meridian::rebase(0x00513770))(self, mgr, tem, rect, parent, flags, ctx);
    }

    // dlg_LevelMap::OnPadSelect — back button dismiss / page node -> narrator. 0x00513ea0
    using OnPadSelect_t = void(__thiscall*)(dlg_LevelMap* self, ui_win* focused);
    inline void OnPadSelect(dlg_LevelMap* self, ui_win* focused) {
        reinterpret_cast<OnPadSelect_t>(meridian::rebase(0x00513ea0))(self, focused);
    }

    // dlg_LevelMap_factory — __cdecl UI factory (operator new 0x1c4 + Create). 0x00513660
    using factory_t = ui_win*(__cdecl*)(int a0, ui_manager* mgr, dialog_tem* tem,
                                        const irect* rect, ui_win* parent, int flags, void* ctx);
    inline ui_win* factory(int a0, ui_manager* mgr, dialog_tem* tem,
                           const irect* rect, ui_win* parent, int flags, void* ctx) {
        return reinterpret_cast<factory_t>(meridian::rebase(0x00513660))(a0, mgr, tem, rect, parent, flags, ctx);
    }

    // dlg_LevelMap_register — __cdecl: register the "level select" template. 0x00513640
    using register_t = void(__cdecl*)(ui_manager* mgr);
    inline void register_template(ui_manager* mgr) {
        reinterpret_cast<register_t>(meridian::rebase(0x00513640))(mgr);
    }
} // namespace dlg_levelmap_api

// ----------------------------- LoadScreen -----------------------------------
namespace load_screen_api {
    // LoadScreen::Init — pick + load level loading-screen bitmap + names. 0x004f9920
    using Init_t = void(__thiscall*)(LoadScreen* self);
    inline void Init(LoadScreen* self) {
        reinterpret_cast<Init_t>(meridian::rebase(0x004f9920))(self);
    }
} // namespace load_screen_api

// ----------------------------- load_trigger ---------------------------------
namespace load_trigger_api {
    // load_trigger::Init — set default flags, init underlying volume.
    // raw: void __thiscall Init(load_trigger*, const vector3& center, const bbox&). 0x00497600
    using Init_t = void(__thiscall*)(load_trigger* self, const vector3* center, const bbox* box);
    inline void Init(load_trigger* self, const vector3* center, const bbox* box) {
        reinterpret_cast<Init_t>(meridian::rebase(0x00497600))(self, center, box);
    }

    // load_trigger::OnImport — deserialize base volume + layer/resource lists. 0x00499930
    using OnImport_t = void(__thiscall*)(load_trigger* self, bin_in* in);
    inline void OnImport(load_trigger* self, bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x00499930))(self, in);
    }

    // load_trigger::OnExport — serialize particle/force/pain fields. 0x004860f0
    using OnExport_t = void(__thiscall*)(load_trigger* self, bin_out* out);
    inline void OnExport(load_trigger* self, bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x004860f0))(self, out);
    }

    // load_trigger::EnumerateProperties — editor property sheet.
    // raw: void __thiscall (load_trigger*, xarray<property_desc>&). 0x00497e30
    using EnumerateProperties_t = void(__thiscall*)(load_trigger* self, xarray<property_desc>* props);
    inline void EnumerateProperties(load_trigger* self, xarray<property_desc>* props) {
        reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00497e30))(self, props);
    }

    // load_trigger::~load_trigger — free owned xarrays, chain volume dtor. 0x004974e0
    using Dtor_t = void(__thiscall*)(load_trigger* self);
    inline void Destroy(load_trigger* self) {
        reinterpret_cast<Dtor_t>(meridian::rebase(0x004974e0))(self);
    }
} // namespace load_trigger_api

// ----------------------------- save_pedestal --------------------------------
namespace save_pedestal_api {
    // save_pedestal::SavePoint — record respawn pos/heading + open SaveKiosk.
    // raw: void __thiscall SavePoint(save_pedestal*, const vector3& pos, float heading). 0x004cda30
    using SavePoint_t = void(__thiscall*)(save_pedestal* self, const vector3* pos, float heading);
    inline void SavePoint(save_pedestal* self, const vector3* pos, float heading) {
        reinterpret_cast<SavePoint_t>(meridian::rebase(0x004cda30))(self, pos, heading);
    }

    // save_pedestal::SetAura — toggle the aura/glow FX (Saveped_active/inactive). 0x004cd880
    using SetAura_t = void(__thiscall*)(save_pedestal* self, int on);
    inline void SetAura(save_pedestal* self, int on) {
        reinterpret_cast<SetAura_t>(meridian::rebase(0x004cd880))(self, on);
    }

    // save_pedestal::OnAdvanceLogic — validate cache, light aura if last-used. 0x004cdaa0
    using OnAdvanceLogic_t = void(__thiscall*)(save_pedestal* self, float dt);
    inline void OnAdvanceLogic(save_pedestal* self, float dt) {
        reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004cdaa0))(self, dt);
    }

    // save_pedestal::OnObjectDeactivate — release FX handle, chain base. 0x004d4300
    using OnObjectDeactivate_t = void(__thiscall*)(save_pedestal* self);
    inline void OnObjectDeactivate(save_pedestal* self) {
        reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004d4300))(self);
    }
} // namespace save_pedestal_api

// -------------------- save-pedestal globals (__cdecl) -----------------------
namespace save_pedestal_global {
    // ActivateSavePedestalFX — light the active pedestal's aura (global GUID). 0x004cdf40
    using ActivateSavePedestalFX_t = void(__cdecl*)();
    inline void ActivateSavePedestalFX() {
        reinterpret_cast<ActivateSavePedestalFX_t>(meridian::rebase(0x004cdf40))();
    }

    // ActivateSavePedestalFXByGuid — light a pedestal aura by GUID (no global set).
    // (mislabeled "SetActiveSavePedestal", conf 0.6)
    // raw: void __cdecl (const unsigned __int64& guid). 0x004cdf70
    using ActivateByGuid_t = void(__cdecl*)(const std::uint64_t* guid);
    inline void ActivateSavePedestalFXByGuid(const std::uint64_t* guid) {
        reinterpret_cast<ActivateByGuid_t>(meridian::rebase(0x004cdf70))(guid);
    }

    // GetActiveSavePedestal — 64-bit GUID of the active save pedestal. 0x004cdfa0
    using GetActiveSavePedestal_t = std::uint64_t(__cdecl*)();
    inline std::uint64_t GetActiveSavePedestal() {
        return reinterpret_cast<GetActiveSavePedestal_t>(meridian::rebase(0x004cdfa0))();
    }

    // RequestLoadLastSave — set DAT_00798548 = 1 (deferred load-from-checkpoint).
    // (mislabeled "GetLastSavePedestal", conf 0.5) 0x004cdf30
    using RequestLoadLastSave_t = void(__cdecl*)();
    inline void RequestLoadLastSave() {
        reinterpret_cast<RequestLoadLastSave_t>(meridian::rebase(0x004cdf30))();
    }
} // namespace save_pedestal_global

// ----------------------------- save_mgr -------------------------------------
namespace save_mgr_api {
    // save_mgr::Import — append a record name into the packed string buffer. 0x0058ee10
    using Import_t = void(__thiscall*)(save_mgr* self, char* name);
    inline void Import(save_mgr* self, char* name) {
        reinterpret_cast<Import_t>(meridian::rebase(0x0058ee10))(self, name);
    }

    // save_mgr::Export — serialize state to a freshly allocated flat buffer.
    // raw: void __thiscall Export(save_mgr*, char*& outBuf, int& outSize). 0x005905f0
    using Export_t = void(__thiscall*)(save_mgr* self, char** outBuf, int* outSize);
    inline void Export(save_mgr* self, char** outBuf, int* outSize) {
        reinterpret_cast<Export_t>(meridian::rebase(0x005905f0))(self, outBuf, outSize);
    }

    // save_mgr::CloseStream — free buffer/handle, zero leading members.
    // (FUN_0058eef0, proposed name, conf 0.55) 0x0058eef0
    using CloseStream_t = void(__thiscall*)(save_mgr* self);
    inline void CloseStream(save_mgr* self) {
        reinterpret_cast<CloseStream_t>(meridian::rebase(0x0058eef0))(self);
    }
} // namespace save_mgr_api

// ----------------------------- LoadSaveMgr_PC -------------------------------
namespace load_save_mgr_pc_api {
    // LoadSaveMgr_PC::LoadSlot — load/restore one save slot by index.
    // (FUN_0052e630, proposed name, conf 0.55)
    // raw: int __thiscall LoadSlot(LoadSaveMgr_PC*, int slotIndex). 0x0052e630
    using LoadSlot_t = int(__thiscall*)(LoadSaveMgr_PC* self, int slotIndex);
    inline int LoadSlot(LoadSaveMgr_PC* self, int slotIndex) {
        return reinterpret_cast<LoadSlot_t>(meridian::rebase(0x0052e630))(self, slotIndex);
    }
} // namespace load_save_mgr_pc_api

// ----------------------------- rsc_mgr (used by streaming) ------------------
namespace rsc_mgr_api {
    // rsc_mgr::DelRHandle — release a resource handle to the free pool.
    // raw: void __thiscall DelRHandle(rsc_mgr*, rhandle& handle). 0x004258d0
    using DelRHandle_t = void(__thiscall*)(rsc_mgr* self, rhandle* handle);
    inline void DelRHandle(rsc_mgr* self, rhandle* handle) {
        reinterpret_cast<DelRHandle_t>(meridian::rebase(0x004258d0))(self, handle);
    }

    // rsc_mgr::SetOnDemandLoading — register/invoke on-demand bitmap loader. 0x00549c40
    using SetOnDemandLoading_t = void*(__thiscall*)(rsc_mgr* self, const char* path);
    inline void* SetOnDemandLoading(rsc_mgr* self, const char* path) {
        return reinterpret_cast<SetOnDemandLoading_t>(meridian::rebase(0x00549c40))(self, path);
    }

    // rsc_mgr::LoadTextFileOnDemand — on-demand textfile loader -> text buffer.
    // (mislabeled "FixupFilename", conf 0.72) 0x00549d80
    using LoadTextFileOnDemand_t = char*(__thiscall*)(rsc_mgr* self, char* filename, char* displayName);
    inline char* LoadTextFileOnDemand(rsc_mgr* self, char* filename, char* displayName) {
        return reinterpret_cast<LoadTextFileOnDemand_t>(meridian::rebase(0x00549d80))(self, filename, displayName);
    }

    // static_textin_loader::Unload — zero the 0x404 data block, reset handles. 0x005486b0
    using TextinUnload_t = void(__thiscall*)(static_textin_loader* self);
    inline void StaticTextinUnload(static_textin_loader* self) {
        reinterpret_cast<TextinUnload_t>(meridian::rebase(0x005486b0))(self);
    }
} // namespace rsc_mgr_api

// ----------------------------- obj_mgr (GUID resolution) --------------------
namespace obj_mgr_api {
    // obj_mgr::GetSlotFromGuid — resolve a 64-bit GUID to a live object*
    // (0 if not found or alive bit 0x10 clear). Returns the object pointer as int.
    // raw: int __thiscall GetSlotFromGuid(obj_mgr*, unsigned __int64 guid). 0x004021c0
    using GetSlotFromGuid_t = int(__thiscall*)(obj_mgr* self, std::uint64_t guid);
    inline int GetSlotFromGuid(obj_mgr* self, std::uint64_t guid) {
        return reinterpret_cast<GetSlotFromGuid_t>(meridian::rebase(0x004021c0))(self, guid);
    }

    // obj_mgr::LockObject — activate a load-trigger object by GUID (with logging).
    // raw: object* __thiscall LockObject(obj_mgr*, unsigned __int64 guid). 0x004dbd50
    using LockObject_t = object*(__thiscall*)(obj_mgr* self, std::uint64_t guid);
    inline object* LockObject(obj_mgr* self, std::uint64_t guid) {
        return reinterpret_cast<LockObject_t>(meridian::rebase(0x004dbd50))(self, guid);
    }

    // The global obj_mgr instance is &DAT_0076cd88. Address accessor (raw obj_mgr*).
    inline void* GlobalObjMgr_at() { return meridian::rebase(0x0076cd88); }
} // namespace obj_mgr_api

// ----------------------------- math / collision helpers ---------------------
namespace level_math {
    // vector3::GetSqrDistToLineSeg — squared distance from point to segment.
    // raw: float __thiscall (vector3* this, const vector3& segStart, const vector3& segDir).
    // param 1 (out) receives the negated closest-point delta. 0x00402040
    using GetSqrDistToLineSeg_t = float(__thiscall*)(vector3* self, const vector3* segStart, const vector3* segDir);
    inline float GetSqrDistToLineSeg(vector3* self, const vector3* segStart, const vector3* segDir) {
        return reinterpret_cast<GetSqrDistToLineSeg_t>(meridian::rebase(0x00402040))(self, segStart, segDir);
    }

    // BilboIntersectsSphere — __cdecl: Bilbo collision bounds vs a world sphere.
    // raw: int __cdecl (const vector3& center, float radius). 0x00416480
    using BilboIntersectsSphere_t = int(__cdecl*)(const vector3* center, float radius);
    inline int BilboIntersectsSphere(const vector3* center, float radius) {
        return reinterpret_cast<BilboIntersectsSphere_t>(meridian::rebase(0x00416480))(center, radius);
    }
} // namespace level_math

// =============================================================================
// 4. Usage recipes (trainer / modding)
// =============================================================================
//
//  --- Force-load a specific level by chapter name --------------------------
//    ::level* lvl = levels_sdk::level_factory::LevelCreate("Ch01_Hobbiton");
//    // The engine's own state machine then calls lvl->Init() / AdvanceLogic().
//    // To tear it down again:
//    levels_sdk::level_factory::LevelDestroy(lvl);
//
//  --- Read the current level name (read-only) ------------------------------
//    auto* L = reinterpret_cast<levels_sdk::level_layout*>(lvl);
//    // L->levelName is an xstring; decode it with your xstring helper.
//
//  --- Resolve a stored trigger/cinema GUID to a live object ----------------
//    obj_mgr* mgr = reinterpret_cast<obj_mgr*>(levels_sdk::obj_mgr_api::GlobalObjMgr_at());
//    int objPtr   = levels_sdk::obj_mgr_api::GetSlotFromGuid(mgr, someGuid);
//    if (objPtr) { /* valid + alive */ }
//
//  --- Inspect / flip Lonely Mountain room state (read-only example) --------
//    auto* LM = reinterpret_cast<levels_sdk::level_lonelymountain_layout*>(lvl);
//    bool treasuryOpen = (LM->roomStateBits & levels_sdk::LM_TREASURY_ACTIVE) != 0;
//    // To actually toggle (drives water/cinema/reward), call the real method:
//    levels_sdk::level_lonelymountain_api::SetTreasuryActive(
//        reinterpret_cast<level_lonelymountain*>(lvl), 1);
//
//  --- Read the active save-pedestal GUID / request a checkpoint reload ------
//    std::uint64_t saveGuid = levels_sdk::save_pedestal_global::GetActiveSavePedestal();
//    levels_sdk::save_pedestal_global::RequestLoadLastSave(); // deferred respawn flag
//
// =============================================================================

} // namespace levels_sdk
