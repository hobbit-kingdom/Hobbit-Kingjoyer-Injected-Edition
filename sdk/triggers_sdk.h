// ============================================================================
//  triggers_sdk.h  —  TRIGGERS / SWITCHES SDK for THE HOBBIT (2003) PC build
//  Entropy engine, MSVC, 32-bit (Meridian.exe, preferred base 0x00400000, ASLR off).
//
//  Reverse-engineered modding / trainer SDK. All addresses are absolute PC
//  virtual addresses; resolve them at runtime with meridian::rebase(0xADDR),
//  which applies the current module-base delta vs the analyzed image base.
//
//  This subsystem is the engine's event-detection-and-dispatch layer:
//    * volume          — oriented bounding-box base (derives from object). Per-
//                        frame point-in-volume test; the geometry under every
//                        volume-based trigger.
//    * trigger         — volume-based event trigger (object::type 0x35). Detects
//                        objects entering/exiting/using the volume and fires the
//                        scripted response (OnEnter/OnExit/OnUse/OnPressB/OnPain/
//                        OnActivate) via object::ExecuteScript.
//    * load_trigger    — level-streaming trigger (load/unload layers, teleport).
//    * music_trigger /
//      ambient_audio_trigger — audio-zone triggers. On listener enter
//                        (OnTriggerRedToGreen) / exit (OnTriggerGreenToRed) they
//                        drive AmbientAudioMgr (set next track / volume target).
//    * fog_volume      — volumetric particle fog volume (reuses water particle
//                        spacing). Cell grid + particle array + Displace force.
//    * Switch          — player-activated lever / pressure plate. Toggle flips an
//                        on/off bit, fires OnSwitched, posts a MineTrackLever
//                        event, and propagates the state to target rigid
//                        instances (doors / mechanisms).
//    * AITrigger + concrete Trigger* subclasses — editor-authored condition
//                        nodes ("AIManager\Triggers\Trigger %d") that Test() a
//                        world condition and latch a fired bit.
//    * bilbo (BilboSwitches) — player glue: per-frame proximity scan, context
//                        use-icon, and B-button activation dispatch.
//
//  Field offsets are CONSOLIDATED from the per-chunk analyses
//  (triggers__00..05.json). Offsets marked "?" are lower confidence. Only well-
//  evidenced fields are named; the rest is explicit padding so named members land
//  at their true byte offsets. These structs are NOT meant to be instantiated —
//  only reinterpret_cast onto a live engine object obtained from a GUID/obj_mgr
//  slot.
//
//  ---- USAGE / RECIPE ------------------------------------------------------
//    using namespace triggers_sdk;
//
//    // Force-fire a trigger you have a slot pointer to (run its OnActivate VM script):
//    Trigger* t = reinterpret_cast<Trigger*>(slotPtr);
//    fn::Trigger_Enable(t, 1);          // make sure it is enabled (flag bit3)
//    fn::Trigger_SetTriggered(t, 1);    // mark triggered
//    fn::Trigger_OnActivate(t);         // fires the "OnActivate" XScript method
//
//    // Flip a switch (drives its target doors/mechanisms):
//    SwitchObj* sw = reinterpret_cast<SwitchObj*>(switchSlotPtr);
//    fn::Switch_Toggle(sw);             // OnSwitched + propagate to all targets
//    // or set an explicit on/off state:
//    fn::Switch_SetOn(sw, 1);
//    bool isOn = fn::Switch_GetOn(sw) != 0;
//
//    // Test whether a point is inside a trigger volume:
//    vector3 p = { x, y, z };
//    bool inside = fn::Volume_IsPointInside(reinterpret_cast<Volume*>(slotPtr), p) != 0;
//
//  __thiscall wrappers take the object pointer as the FIRST argument.
//  Statics / script callbacks are __cdecl. Any method taking an INCOMPLETE engine
//  type BY VALUE, or returning a large aggregate via hidden sret, exposes an
//  address accessor (*_at) with the raw signature in a comment instead of a typed
//  wrapper. xstring/vector3/radian3/bbox ARE complete (meridian_types.h), so their
//  by-value signatures are ABI-safe.
//
//  NAMING NOTE: the engine class is literally named `Switch`, which is a C++
//  keyword-adjacent collision risk; here it is modeled as `SwitchObj`. Engine type
//  names that collide with the std namespace (internal/system/map) are written
//  global-qualified (::internal, ...) so the header stays correct under
//  `using namespace std;`.
// ============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/radian3/bbox, xstring, property, xarray<T>, and trigger/volume/Switch/... fwd-decls

// ---- Forward declarations for engine types we reference but don't model -----
// (Most are already declared globally in meridian_types.h; re-declaring a struct
//  name is harmless and keeps this header readable standalone.)
struct object;            // base of volume / AITrigger
struct rigid_instance;    // base of Switch
struct bin_in;            // OnImport stream
struct bin_out;           // OnExport stream
struct bilbo;             // player object (BilboSwitches methods)
struct obj_mgr;
struct AmbientAudioMgr;   // driven by audio-zone triggers
struct property;          // complete in meridian_types.h (blob 0x258)

namespace triggers_sdk {

// ===========================================================================
//  0. Enums / constants recovered from the disassembly
// ===========================================================================

// trigger flags word @ trigger+0x120. Bit meanings consolidated across the
// OnImport/OnExport and accessor paths (some bits carry two readings across
// import vs. accessor code; the dominant accessor reading is used here).
enum TriggerFlag : uint32_t {
    TRIGGER_RESET             = 0x00000001, // bit0  reset pending
    TRIGGER_TRIGGERED         = 0x00000004, // bit2  IsTriggered
    TRIGGER_ENABLED           = 0x00000008, // bit3  Enable/IsEnabled; gates fire paths; DrawIndicator gate
    TRIGGER_WAS_TRIGGERED     = 0x00000010, // bit4  GetWasTriggered/SetTriggered
    TRIGGER_SAVE_INSIDE       = 0x00000020, // bit5  SaveInside (OneTimeShot on import path)
    TRIGGER_USES_INVENTORY    = 0x00000040, // bit6  UsesInventory
    TRIGGER_USE_B_BUTTON      = 0x00000080, // bit7  UsesBButton / GetUseInventory
    TRIGGER_ONE_DIRECTIONAL   = 0x00000200, // bit9
    TRIGGER_ORDER_IRRELEVANT  = 0x00000400, // bit10 unordered set match
    TRIGGER_MULT_ITEMS        = 0x00000800, // bit11 MultItemsCanActivate / single-item path
    TRIGGER_DISABLE_ON_FULL   = 0x00001000, // bit12
    TRIGGER_PENDING           = 0x00002000, // bit13 cleared on trigger
    TRIGGER_CALL_UPDATE_INSIDE= 0x00004000, // bit14
    TRIGGER_ONINIT_PENDING    = 0x00008000, // bit15
    TRIGGER_FORCE_CHECK_ENTER = 0x00010000, // bit16
    TRIGGER_PLAYER_ONLY       = 0x00040000, // bit18
    TRIGGER_ONE_TIME_SHOT     = 0x00080000, // bit19
};

// Switch state/config flags word @ Switch+0x160.
enum SwitchFlag : uint32_t {
    SWITCH_ON                 = 0x00000002, // bit1  on/activated state (GetOn)
    SWITCH_ROCK_CAN_TRIGGER   = 0x00000004, // bit2  a rolling rock may activate (GetRockCanTrigger)
    SWITCH_REVERSE_ANIM_OFF   = 0x00000008, // bit3  ReverseAnimForOff
    SWITCH_TARGET_LOOPS       = 0x00000010, // bit4  TargetLoops
};

// Audio-zone trigger action type @ trigger+0x1b4 (RedToGreen) / +0x2ac (GreenToRed).
enum TriggerActionType : int32_t {
    TRIGGER_ACTION_PLAY_TRACK = 0,  // SetDesiredNextTrackByNameFromTrigger
    TRIGGER_ACTION_SET_VOLUME = 6,  // SetVolumeTarget
};

// SWITCHTYPE — track-switch timing, from InitializeTriggerActionTypeList.
enum SwitchType : int32_t {
    SWITCH_NORMAL           = 0,
    SWITCH_AT_BREAK         = 1,
    SWITCH_WITH_VOLUME_FADE = 2,
    SWITCH_IMMEDIATE        = 3,
};

// object::type tag @ object+0x7c (activation routing in bilbo::CheckForActivate).
enum ObjectTypeTag : uint8_t {
    OBJTYPE_HOIST_SWITCH = 0x05,
    OBJTYPE_NPC          = 0x1c,
    OBJTYPE_CHEST        = 0x24,
    OBJTYPE_SWITCH       = 0x31,
    OBJTYPE_USABLE       = 0x33,
    OBJTYPE_TRIGGER      = 0x35,
};

// ===========================================================================
//  1. Volume — oriented bounding-box base (derives from object)
//     Cast a live slot pointer to Volume*. Do NOT instantiate.
// ===========================================================================
#pragma pack(push, 1)
struct Volume {
    void*    vtable;                   // 0x000
    uint8_t  _pad004[0x10 - 0x04];     // 0x004  object header
    uint32_t objFlags;                 // 0x010  object base flag mask
    float    posX;                     // 0x014  world position X
    float    posY;                     // 0x018
    float    posZ;                     // 0x01c
    uint8_t  _pad020[0x2c - 0x20];     // 0x020
    float    localBBoxMin[3];          // 0x02c  local AABB min (from -halfDims)
    float    localBBoxMax[3];          // 0x038  local AABB max (from +halfDims)
    float    worldBBox[6];             // 0x044  world AABB: min vec3 @0x44, max vec3 @0x50 (IsPointInside)
    uint8_t  _pad05c[0x68 - 0x5c];     // 0x05c
    radian3  orient;                   // 0x068  Euler rotation; all-zero => unrotated fast path
    uint8_t  _pad074[0x7c - 0x74];     // 0x074
    uint8_t  typeTag;                  // 0x07c  object::type (ObjectTypeTag)
    uint8_t  _pad07d[0x7f - 0x7d];     // 0x07d
    uint8_t  stateFlags;               // 0x07f  bit4(0x10)=live; render-state bit0
    uint8_t  _pad080[0xac - 0x80];     // 0x080
    float    halfDimX;                 // 0x0ac  half-dimensions (Dimensions = 2x; scaled by Scale)
    float    halfDimY;                 // 0x0b0
    float    halfDimZ;                 // 0x0b4
    uint8_t  usingOnlyBBox;            // 0x0b8  serialized "Using Only BBox" bool
    uint8_t  _pad0b9[0xe4 - 0xb9];     // 0x0b9
    uint32_t bNoRecompute;             // 0x0e4  lock flag; OnRotate skips SetPoints when set
};                                     // size >= 0xe8
#pragma pack(pop)

// ===========================================================================
//  2. Trigger — volume-based event trigger (derives from Volume)
//     Cast a live slot pointer to Trigger*. Do NOT instantiate.
// ===========================================================================
#pragma pack(push, 1)
struct Trigger {
    uint8_t  _pad000[0x108 - 0x00];    // 0x000  inherited Volume region
    int32_t  insideCount;              // 0x108  "currently inside" GUID list count
    uint64_t* insideList;              // 0x10c  GUID array (stride 2 dwords)
    uint8_t  _pad110[0x11c - 0x110];   // 0x110
    uint32_t attrMask;                 // 0x11c  SetAttrMask whole-word attribute/category mask
    uint32_t flags;                    // 0x120  TriggerFlag bitfield
    uint8_t  forceScriptDriven;        // 0x122  bit0 forces script-driven / enter state
    uint8_t  _pad123[0x138 - 0x123];   // 0x123
    int32_t  requiredItemCount;        // 0x138  required item-type slot count
    int32_t* requiredItemList;         // 0x13c  item-type ids (-1 = empty slot)
    int32_t  itemCapacity;             // 0x140  runtime item-id array capacity
    int32_t  itemArrayStaticFlag;      // 0x144  0 = owned dynamic (frees/realloc)
    int32_t  itemGrowChunk;            // 0x148  grow increment (0 = doubling heuristic)
    int32_t  maxItemCount;             // 0x14c  IsFull compares; serialized "MaxItems"
    int32_t  nActivators;              // 0x150  serialized "nActivators"
    int32_t  scriptMethodState;        // 0x154  0 unknown / 1 has methods / 2 none; enterCheckState
    uint8_t  _pad158[0x160 - 0x158];   // 0x158
    int32_t  suppliedItemCount;        // 0x160  UseItems player-supplied set count
    int32_t* suppliedItemList;         // 0x164  player-supplied item ids
    uint8_t  _pad168[0x19c - 0x168];   // 0x168
    void*    questItemReqTable;        // 0x19c  stride 0x1c: [+8]=count, [+0xc]=accepted id list ptr
    uint8_t  _pad1a0[0x1ac - 0x1a0];   // 0x1a0
    int32_t  timerActive;              // 0x1ac  re-arm/cooldown timer active flag
    float    timerRemaining;           // 0x1b0  "TimerRunning"; -= dt each frame
};                                     // size >= 0x1b4
#pragma pack(pop)

// ===========================================================================
//  3. LoadTrigger — level-streaming trigger (derives from Trigger)
// ===========================================================================
#pragma pack(push, 1)
struct LoadTrigger {
    uint8_t  _pad000[0x7a - 0x00];     // 0x000  inherited region
    uint16_t volumeFlags;              // 0x07a  bit0 forces volume re-init on load
    uint8_t  _pad07c[0x100 - 0x7c];    // 0x07c
    // 0x100  xarray<xstring> "LoadLayers"/"Layer": data ptr @0x100, count @0x108, cap @0x110 (stride 0x2c)
    uint8_t  loadLayers[0x11c - 0x100];// 0x100  (0x1c-byte xarray header region)
    // 0x11c  xarray<xstring> "UnloadLayer": data ptr @0x11c, count @0x124, cap @0x12c (stride 0x2c)
    uint8_t  unloadLayers[0x150 - 0x11c]; // 0x11c (xarray header region; overlaps PainFreq/PoisonDur in the shared serialized block "?")
    uint32_t color;                    // 0x150  "Color" rgba
    int32_t  painType;                 // 0x154  "PainType"
};                                     // size >= 0x158  (offsets around the xarray headers "?")
#pragma pack(pop)

// ===========================================================================
//  4. SwitchObj — player-activated lever/pressure plate (engine class `Switch`,
//     derives from rigid_instance). Renamed to avoid the `switch` keyword clash.
// ===========================================================================
#pragma pack(push, 1)
struct SwitchObj {
    uint8_t  _pad000[0x7f - 0x00];     // 0x000  inherited object/rigid_instance region
    uint8_t  byteFlags;                // 0x07f  Init sets bit0
    uint8_t  _pad080[0xac - 0x80];     // 0x080
    int32_t  linkedCount;              // 0x0ac  Activate linked-target count
    uint64_t* linkedTargets;           // 0x0b0  Activate target GUID array (stride 8)
    uint8_t  _pad0b8[0x160 - 0xb8];    // 0x0b8
    uint32_t stateFlags;               // 0x160  SwitchFlag bitfield (bit1=on, bit2=rockCanTrigger, ...)
    float    toggleDelay;              // 0x164  default 1.0; -4.0 sentinel
    float    animTimeline;             // 0x168  reset on toggle (-1.0 when ToggleDelay==-4.0)
    int32_t  toggleCount;              // 0x16c  bumped per toggle
    int32_t  targetGuidCount;          // 0x170  Toggle target count (Init = -1 / none)
    uint64_t* targetGuids;             // 0x174  Toggle target GUID array (stride 8)
};                                     // size >= 0x17c
#pragma pack(pop)

// ===========================================================================
//  5. FogVolume — volumetric particle fog (derives from Volume)
// ===========================================================================
#pragma pack(push, 1)
struct FogVolume {
    uint8_t  _pad000[0x100 - 0x00];    // 0x000  inherited Volume region
    float    cellSize;                 // 0x100  per-cell world size
    int32_t  nXCells;                  // 0x104  grid columns / X cell clamp
    int32_t  nZCells;                  // 0x108  grid rows / Z cell clamp
    int32_t  nParticles;               // 0x10c  particle count
    uint8_t  _pad110[0x114 - 0x110];   // 0x110
    float    particleSize;             // 0x114
    uint8_t  minAlpha;                 // 0x118
    uint8_t  maxAlpha;                 // 0x119
    uint8_t  _pad11a[0x11c - 0x11a];   // 0x11a
    float    pushScale;                // 0x11c
    float    pullScale;                // 0x120
    float    forceScalar;              // 0x124
    float    viscosity;                // 0x128
    uint8_t  _pad12c[0x138 - 0x12c];   // 0x12c
    vector3  moveVec;                  // 0x138
    uint8_t  _pad144[0x164 - 0x144];   // 0x144
    int32_t  cellCount;                // 0x164  rows*cols
    void*    cells;                    // 0x168  cell array (stride 0x30); freed on deactivate
    void*    particleArray;            // 0x16c  particle array (stride 0x48); freed on deactivate
    float    halfCellSize;             // 0x170  cellSize * 0.5
    float    extentX;                  // 0x174  nXCells * cellSize
    float    extentZ;                  // 0x178  nZCells * cellSize
};                                     // size >= 0x17c
#pragma pack(pop)

// ===========================================================================
//  6. AmbientAudioTrigger — audio-zone trigger (engine ambient_audio_trigger /
//     music_trigger share this layout; both derive from Volume).
// ===========================================================================
#pragma pack(push, 1)
struct AmbientAudioTrigger {
    uint8_t  _pad000[0x7a - 0x00];     // 0x000  inherited region
    uint8_t  stateFlags;               // 0x07a  bit0 active/dirty
    uint8_t  _pad07b[0x100 - 0x7b];    // 0x07b
    float    blendFactor;              // 0x100  OnTrigger* sets 0.5
    uint8_t  _pad104[0x120 - 0x104];   // 0x104
    int32_t  singleShot;               // 0x120  "SingleShot"
    int32_t  bIsCinematic;             // 0x124  "bIsCinematic"
    int32_t  crossingGuard;            // 0x128  CheckForCrossing runs only when 0; also hasFired latch
    uint8_t  _pad12c[0x184 - 0x12c];   // 0x12c
    uint8_t  trackR2G[0x2c];           // 0x184  xstring RedToGreen track name
    uint8_t  _pad1b0[0x1b0 - (0x184 + 0x2c)]; // 0x1b0 region after the 0x2c-byte xstring
    int32_t  cueA_intensity;           // 0x1b0  DesiredIntensity (RedToGreen)
    int32_t  cueA_actionType;          // 0x1b4  TriggerActionType (RedToGreen)
    int32_t  cueA_switchType;          // 0x1b8  SwitchType (RedToGreen)
    int32_t  cueA_useAsDefault;        // 0x1bc  UseAsDefault (RedToGreen)
    float    cueA_fadeOutTime;         // 0x1c0
    float    cueA_fadeInTime;          // 0x1c4
    int32_t  cueA_maxLoopCount;        // 0x1c8
    uint8_t  _pad1cc[0x224 - 0x1cc];   // 0x1cc
    uint8_t  trackG2R[0x2c];           // 0x224  xstring GreenToRed track name
    uint8_t  _pad250[0x2a8 - (0x224 + 0x2c)]; // 0x250 region after the 0x2c-byte xstring
    int32_t  cueB_intensity;           // 0x2a8  DesiredIntensity (GreenToRed)
    int32_t  cueB_actionType;          // 0x2ac  TriggerActionType (GreenToRed)
    int32_t  cueB_switchType;          // 0x2b0  SwitchType (GreenToRed)
    int32_t  cueB_useAsDefault;        // 0x2b4
    float    cueB_fadeOutTime;         // 0x2b8
    float    cueB_fadeInTime;          // 0x2bc
    int32_t  cueB_maxLoopCount;        // 0x2c0
    float    cueA_gain;                // 0x2c4  RedToGreen target volume / default gain 1.0
    float    cueB_gain;                // 0x2c8  GreenToRed target volume / default gain 1.0
};                                     // size >= 0x2cc
#pragma pack(pop)

// ===========================================================================
//  7. AITriggerBase — editor condition node base (engine AITrigger, derives from
//     object). Concrete Trigger* subclasses extend it (only the shared base
//     fields are evidenced; cast a live condition node to this).
// ===========================================================================
#pragma pack(push, 1)
struct AITriggerBase {
    uint8_t  _pad000[0x04 - 0x00];     // 0x000
    int32_t  triggerIndex;             // 0x004  "AIManager\Triggers\Trigger %d" index
    uint32_t conditionFlags;           // 0x008  IsTriggered=bit0, StaysTrue=bit1, TriggersOnValue=bit2; bit0|=1 = fired
    int32_t  goldAmount;               // 0x00c  GoldAmount / useAllCharacters (per subclass)
    uint64_t primaryGuid;              // 0x010  NPC/Character/Switch/Cinema/RigidInstance ref
    uint64_t secondaryGuid;            // 0x018  Volume / CharacterSensed ref
    int32_t  triggersOnce;             // 0x020  TriggersOnce config
    int32_t  alreadyFiredLatch;        // 0x024  once-only fired latch
};                                     // size >= 0x28
#pragma pack(pop)

// ===========================================================================
//  8. Typed call wrappers
//     __thiscall: object pointer is the FIRST argument.
// ===========================================================================
namespace fn {

// ---- Volume ----------------------------------------------------------------
// volume::Init(center, dimX, dimY, dimZ) — build box from full dimensions.
inline void Volume_Init(Volume* v, const vector3& center, float dimX, float dimY, float dimZ) {
    using F = void(__thiscall*)(Volume*, const vector3&, float, float, float);
    reinterpret_cast<F>(meridian::rebase(0x004e1e70))(v, center, dimX, dimY, dimZ);
}
// volume::Init(center, halfExtents, orient) — build box from half-extents + rotation.
inline void Volume_InitOriented(Volume* v, const vector3& center, const vector3& halfExtents,
                                const radian3& orient) {
    using F = void(__thiscall*)(Volume*, const vector3&, const vector3&, const radian3&);
    reinterpret_cast<F>(meridian::rebase(0x004e2000))(v, center, halfExtents, orient);
}
// virtual volume::OnInit(void) — default 100x100x100 box at origin.
inline void Volume_OnInit(Volume* v) {
    using F = void(__thiscall*)(Volume*);
    reinterpret_cast<F>(meridian::rebase(0x004e2050))(v);
}
// volume::SetPoints(void) — rebuild oriented bbox corners.
inline void Volume_SetPoints(Volume* v) {
    using F = void(__thiscall*)(Volume*);
    reinterpret_cast<F>(meridian::rebase(0x004e2630))(v);
}
// volume::IsPointInside(const vector3&) -> int  (the per-frame overlap test).
inline int Volume_IsPointInside(Volume* v, const vector3& pt) {
    using F = int(__thiscall*)(Volume*, const vector3&);
    return reinterpret_cast<F>(meridian::rebase(0x004e2330))(v, pt);
}
// virtual volume::OnRotate(const radian3&)
inline void Volume_OnRotate(Volume* v, const radian3& rot) {
    using F = void(__thiscall*)(Volume*, const radian3&);
    reinterpret_cast<F>(meridian::rebase(0x004e30c0))(v, rot);
}
// virtual volume::OnImport(bin_in&)
inline void Volume_OnImport(Volume* v, bin_in* s) {
    using F = void(__thiscall*)(Volume*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x004e2c00))(v, s);
}
// virtual volume::OnExport(bin_out&)
inline void Volume_OnExport(Volume* v, bin_out* s) {
    using F = void(__thiscall*)(Volume*, bin_out*);
    reinterpret_cast<F>(meridian::rebase(0x004e2b70))(v, s);
}
// virtual volume::SetProperty(const char*, const property&) -> int
inline int Volume_SetProperty(Volume* v, const char* key, const property& val) {
    using F = int(__thiscall*)(Volume*, const char*, const property&);
    return reinterpret_cast<F>(meridian::rebase(0x004e3380))(v, key, val);
}
// virtual volume::GetProperty(const char*) -> property (by value, hidden sret).
//   Raw sig: property __thiscall volume::GetProperty(volume*, const char*)
inline void* Volume_GetProperty_at() { return meridian::rebase(0x004e37d0); }
// virtual volume::EnumerateProperties(xarray<property_desc>&)
//   Raw sig: void __thiscall volume::EnumerateProperties(volume*, xarray<property_desc>&)
inline void* Volume_EnumerateProperties_at() { return meridian::rebase(0x004e30f0); }

// ---- Trigger: per-frame / lifecycle / fire ---------------------------------
// virtual trigger::OnAdvanceLogic(float dt) — enter/exit/use detection + fire.
inline void Trigger_OnAdvanceLogic(Trigger* t, float dt) {
    using F = void(__thiscall*)(Trigger*, float);
    reinterpret_cast<F>(meridian::rebase(0x004dd480))(t, dt);
}
// virtual trigger::OnReset(void) — clear flags, (re)alloc item array, fire OnInit.
inline void Trigger_OnReset(Trigger* t) {
    using F = void(__thiscall*)(Trigger*);
    reinterpret_cast<F>(meridian::rebase(0x004dcd80))(t);
}
// virtual trigger::OnObjectActivate(void) — one-shot OnInit on first activate.
inline void Trigger_OnObjectActivate(Trigger* t) {
    using F = void(__thiscall*)(Trigger*);
    reinterpret_cast<F>(meridian::rebase(0x004e1a60))(t);
}
// trigger::OnUse(int item) — validate used item vs quest list, fire OnUse.
inline void Trigger_OnUse(Trigger* t, int item) {
    using F = void(__thiscall*)(Trigger*, int);
    reinterpret_cast<F>(meridian::rebase(0x004dcef0))(t, item);
}
// protected trigger::UseItems(void) — set-match → OnActivate / OnFailedActivate.
inline void Trigger_UseItems(Trigger* t) {
    using F = void(__thiscall*)(Trigger*);
    reinterpret_cast<F>(meridian::rebase(0x004dd060))(t);
}
// trigger::EjectItems(void) — return held items to inventory, fire OnEject.
inline void Trigger_EjectItems(Trigger* t) {
    using F = void(__thiscall*)(Trigger*);
    reinterpret_cast<F>(meridian::rebase(0x004dd1b0))(t);
}
// trigger::OnActivate(void) — fire the "OnActivate" XScript method (gated).
inline void Trigger_OnActivate(Trigger* t) {
    using F = void(__thiscall*)(Trigger*);
    reinterpret_cast<F>(meridian::rebase(0x004de300))(t);
}
// trigger::OnPressB(void) — fire "OnPressB" (gated by enabled + once-guard).
inline void Trigger_OnPressB(Trigger* t) {
    using F = void(__thiscall*)(Trigger*);
    reinterpret_cast<F>(meridian::rebase(0x004dd2d0))(t);
}
// trigger::OnPain(uint64 srcGuid, const vector3& at, float, float, float, int painType)
inline void Trigger_OnPain(Trigger* t, uint64_t srcGuid, const vector3& at,
                           float a, float b, float c, int painType) {
    using F = void(__thiscall*)(Trigger*, uint64_t, const vector3&, float, float, float, int);
    reinterpret_cast<F>(meridian::rebase(0x004de270))(t, srcGuid, at, a, b, c, painType);
}
// trigger::DrawIndicator(const vector3& worldOffset) -> int (should-draw predicate).
inline int Trigger_DrawIndicator(Trigger* t, const vector3& worldOffset) {
    using F = int(__thiscall*)(Trigger*, const vector3&);
    return reinterpret_cast<F>(meridian::rebase(0x004df1c0))(t, worldOffset);
}
// trigger::IsInside(const uint64& guid) -> int
inline int Trigger_IsInside(Trigger* t, const uint64_t& guid) {
    using F = int(__thiscall*)(Trigger*, const uint64_t&);
    return reinterpret_cast<F>(meridian::rebase(0x004e19b0))(t, guid);
}
// trigger::ForceCheckEnter(int) — set bit16 + force enter-state.
inline void Trigger_ForceCheckEnter(Trigger* t, int b) {
    using F = void(__thiscall*)(Trigger*, int);
    reinterpret_cast<F>(meridian::rebase(0x004e1a10))(t, b);
}

// ---- Trigger: serialization ------------------------------------------------
inline void Trigger_OnImport(Trigger* t, bin_in* s) {
    using F = void(__thiscall*)(Trigger*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x004de9e0))(t, s);
}
inline void Trigger_OnExport(Trigger* t, bin_out* s) {
    using F = void(__thiscall*)(Trigger*, bin_out*);
    reinterpret_cast<F>(meridian::rebase(0x004de760))(t, s);
}

// ---- Trigger: flag accessors -----------------------------------------------
inline int  Trigger_GetWasTriggered(Trigger* t) {
    using F = int(__thiscall*)(Trigger*);
    return reinterpret_cast<F>(meridian::rebase(0x004de640))(t);
}
inline void Trigger_SetTriggered(Trigger* t, int b) {
    using F = void(__thiscall*)(Trigger*, int);
    reinterpret_cast<F>(meridian::rebase(0x004de610))(t, b);
}
inline int  Trigger_IsTriggered(Trigger* t) {
    using F = int(__thiscall*)(Trigger*);
    return reinterpret_cast<F>(meridian::rebase(0x004df1b0))(t);
}
inline void Trigger_Enable(Trigger* t, int b) {
    using F = void(__thiscall*)(Trigger*, int);
    reinterpret_cast<F>(meridian::rebase(0x004de6b0))(t, b);
}
inline int  Trigger_IsEnabled(Trigger* t) {
    using F = int(__thiscall*)(Trigger*);
    return reinterpret_cast<F>(meridian::rebase(0x004de6d0))(t);
}
inline void Trigger_SetOneTimeShot(Trigger* t, int b) {
    using F = void(__thiscall*)(Trigger*, int);
    reinterpret_cast<F>(meridian::rebase(0x004e1a90))(t, b);
}
inline int  Trigger_GetUseInventory(Trigger* t) {
    using F = int(__thiscall*)(Trigger*);
    return reinterpret_cast<F>(meridian::rebase(0x004dd2c0))(t);
}
inline void Trigger_SetSaveInside(Trigger* t, int b) {
    using F = void(__thiscall*)(Trigger*, int);
    reinterpret_cast<F>(meridian::rebase(0x004de650))(t, b);
}
// trigger::GetSaveInside(void) -> int  (proposed; mirror of SetSaveInside, bit5).
inline int  Trigger_GetSaveInside(Trigger* t) {
    using F = int(__thiscall*)(Trigger*);
    return reinterpret_cast<F>(meridian::rebase(0x004de670))(t);
}
inline void Trigger_SetAttrMask(Trigger* t, uint32_t mask) {
    using F = void(__thiscall*)(Trigger*, uint32_t);
    reinterpret_cast<F>(meridian::rebase(0x004de5f0))(t, mask);
}

// ---- Trigger: item queries -------------------------------------------------
inline int  Trigger_IsFull(Trigger* t) {
    using F = int(__thiscall*)(Trigger*);
    return reinterpret_cast<F>(meridian::rebase(0x004dd210))(t);
}
// trigger::GetItemName(int) -> const char*
inline const char* Trigger_GetItemName(Trigger* t, int n) {
    using F = const char*(__thiscall*)(Trigger*, int);
    return reinterpret_cast<F>(meridian::rebase(0x004dd230))(t, n);
}
// trigger::GetItemType(int) -> int  (-1 if out of range)
inline int  Trigger_GetItemType(Trigger* t, int n) {
    using F = int(__thiscall*)(Trigger*, int);
    return reinterpret_cast<F>(meridian::rebase(0x004dd290))(t, n);
}

// ---- LoadTrigger -----------------------------------------------------------
// load_trigger::Init(center, bbox) — set control fields + volume::Init.
inline void LoadTrigger_Init(LoadTrigger* lt, const vector3& center, const bbox& box) {
    using F = void(__thiscall*)(LoadTrigger*, const vector3&, const bbox&);
    reinterpret_cast<F>(meridian::rebase(0x00497600))(lt, center, box);
}
inline void LoadTrigger_OnImport(LoadTrigger* lt, bin_in* s) {
    using F = void(__thiscall*)(LoadTrigger*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x00499930))(lt, s);
}
inline void LoadTrigger_OnExport(LoadTrigger* lt, bin_out* s) {
    using F = void(__thiscall*)(LoadTrigger*, bin_out*);
    reinterpret_cast<F>(meridian::rebase(0x004860f0))(lt, s);
}

// ---- SwitchObj (engine `Switch`) -------------------------------------------
// Switch::Init(pos, rot, scale, bbox)
inline void Switch_Init(SwitchObj* sw, const vector3& pos, const radian3& rot,
                        const vector3& scale, const bbox& box) {
    using F = void(__thiscall*)(SwitchObj*, const vector3&, const radian3&,
                                const vector3&, const bbox&);
    reinterpret_cast<F>(meridian::rebase(0x004d2610))(sw, pos, rot, scale, box);
}
// Switch::Toggle(void) — flip on/off, fire OnSwitched, propagate to targets.
inline void Switch_Toggle(SwitchObj* sw) {
    using F = void(__thiscall*)(SwitchObj*);
    reinterpret_cast<F>(meridian::rebase(0x004d2f50))(sw);
}
// Switch::SetOn(int) — idempotent set; calls Toggle if state differs.
inline void Switch_SetOn(SwitchObj* sw, int on) {
    using F = void(__thiscall*)(SwitchObj*, int);
    reinterpret_cast<F>(meridian::rebase(0x004d2f20))(sw, on);
}
// Switch::GetOn(void) -> int  (state bit1)
inline int  Switch_GetOn(SwitchObj* sw) {
    using F = int(__thiscall*)(SwitchObj*);
    return reinterpret_cast<F>(meridian::rebase(0x004d2f10))(sw);
}
// Switch::GetRockCanTrigger(void) -> int  (bit2)
inline int  Switch_GetRockCanTrigger(SwitchObj* sw) {
    using F = int(__thiscall*)(SwitchObj*);
    return reinterpret_cast<F>(meridian::rebase(0x004d2f40))(sw);
}
// Switch::GetStateFlags(void) -> uint  (whole +0x160 word; proposed name).
inline unsigned int Switch_GetStateFlags(SwitchObj* sw) {
    using F = unsigned int(__thiscall*)(SwitchObj*);
    return reinterpret_cast<F>(meridian::rebase(0x004d57a0))(sw);
}
// Switch::Activate(void) — dispatch a queued action to each linked target.
inline void Switch_Activate(SwitchObj* sw) {
    using F = void(__thiscall*)(SwitchObj*);
    reinterpret_cast<F>(meridian::rebase(0x0044f030))(sw);
}
inline void Switch_OnImport(SwitchObj* sw, bin_in* s) {
    using F = void(__thiscall*)(SwitchObj*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x004d2d50))(sw, s);
}
inline void Switch_OnExport(SwitchObj* sw, bin_out* s) {
    using F = void(__thiscall*)(SwitchObj*, bin_out*);
    reinterpret_cast<F>(meridian::rebase(0x004d2cc0))(sw, s);
}

// ---- FogVolume -------------------------------------------------------------
// fog_volume::RebuildCells(void) — recompute the cell grid + particles.
inline void FogVolume_RebuildCells(FogVolume* fv) {
    using F = void(__thiscall*)(FogVolume*);
    reinterpret_cast<F>(meridian::rebase(0x00485840))(fv);
}
// fog_volume::Displace(const vector3& force, const vector3& at) — push particles.
inline void FogVolume_Displace(FogVolume* fv, const vector3& force, const vector3& at) {
    using F = void(__thiscall*)(FogVolume*, const vector3&, const vector3&);
    reinterpret_cast<F>(meridian::rebase(0x004851f0))(fv, force, at);
}
inline void FogVolume_OnImport(FogVolume* fv, bin_in* s) {
    using F = void(__thiscall*)(FogVolume*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x004862e0))(fv, s);
}
inline void FogVolume_OnObjectActivate(FogVolume* fv) {
    using F = void(__thiscall*)(FogVolume*);
    reinterpret_cast<F>(meridian::rebase(0x004e9d90))(fv);
}
inline void FogVolume_OnObjectDeactivate(FogVolume* fv) {
    using F = void(__thiscall*)(FogVolume*);
    reinterpret_cast<F>(meridian::rebase(0x00486560))(fv);
}

// ---- AmbientAudioTrigger / MusicTrigger ------------------------------------
// ambient_audio_trigger::Init(const vector3& origin, const bbox& box)
inline void AmbientAudioTrigger_Init(AmbientAudioTrigger* t, const vector3& origin, const bbox& box) {
    using F = void(__thiscall*)(AmbientAudioTrigger*, const vector3&, const bbox&);
    reinterpret_cast<F>(meridian::rebase(0x00454e40))(t, origin, box);
}
// ambient_audio_trigger::CheckForCrossing(vector3 prevPos, vector3 curPos)
//   (both vector3 by value; complete type, so ABI-safe.)
inline void AmbientAudioTrigger_CheckForCrossing(AmbientAudioTrigger* t,
                                                 vector3 prevPos, vector3 curPos) {
    using F = void(__thiscall*)(AmbientAudioTrigger*, vector3, vector3);
    reinterpret_cast<F>(meridian::rebase(0x004551c0))(t, prevPos, curPos);
}
// ambient_audio_trigger::OnTriggerRedToGreen(void) — fire the enter transition.
inline void AmbientAudioTrigger_OnTriggerRedToGreen(AmbientAudioTrigger* t) {
    using F = void(__thiscall*)(AmbientAudioTrigger*);
    reinterpret_cast<F>(meridian::rebase(0x004554a0))(t);
}
// ambient_audio_trigger::OnTriggerGreenToRed(void) — fire the exit transition.
inline void AmbientAudioTrigger_OnTriggerGreenToRed(AmbientAudioTrigger* t) {
    using F = void(__thiscall*)(AmbientAudioTrigger*);
    reinterpret_cast<F>(meridian::rebase(0x00455570))(t);
}
inline void AmbientAudioTrigger_OnImport(AmbientAudioTrigger* t, bin_in* s) {
    using F = void(__thiscall*)(AmbientAudioTrigger*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x0053b1a0))(t, s);
}
inline void AmbientAudioTrigger_OnExport(AmbientAudioTrigger* t, bin_out* s) {
    using F = void(__thiscall*)(AmbientAudioTrigger*, bin_out*);
    reinterpret_cast<F>(meridian::rebase(0x0053aff0))(t, s);
}
inline int  AmbientAudioTrigger_SetProperty(AmbientAudioTrigger* t, const char* key, const property& val) {
    using F = int(__thiscall*)(AmbientAudioTrigger*, const char*, const property&);
    return reinterpret_cast<F>(meridian::rebase(0x00455a20))(t, key, val);
}
// music_trigger::Init(const vector3& origin, const bbox& box)  (proposed; bundle-labeled ~music_trigger)
inline void MusicTrigger_Init(AmbientAudioTrigger* t, const vector3& origin, const bbox& box) {
    using F = void(__thiscall*)(AmbientAudioTrigger*, const vector3&, const bbox&);
    reinterpret_cast<F>(meridian::rebase(0x00538bd0))(t, origin, box);
}
inline void MusicTrigger_OnImport(AmbientAudioTrigger* t, bin_in* s) {
    using F = void(__thiscall*)(AmbientAudioTrigger*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x00456d80))(t, s);
}
inline int  MusicTrigger_SetProperty(AmbientAudioTrigger* t, const char* key, const property& val) {
    using F = int(__thiscall*)(AmbientAudioTrigger*, const char*, const property&);
    return reinterpret_cast<F>(meridian::rebase(0x00539d90))(t, key, val);
}
// ambient_audio_trigger::GetCurrentTrackName(void) -> const char* (proposed).
inline const char* AmbientAudioTrigger_GetCurrentTrackName(AmbientAudioTrigger* t) {
    using F = const char*(__thiscall*)(AmbientAudioTrigger*);
    return reinterpret_cast<F>(meridian::rebase(0x005310a0))(t);
}
// InitializeTriggerActionTypeList(void) — build the SWITCHTYPE name table.
inline void InitializeTriggerActionTypeList() {
    using F = void(__cdecl*)();
    reinterpret_cast<F>(meridian::rebase(0x005385e0))();
}

// ---- AITrigger base --------------------------------------------------------
// AITrigger::OnImport(bin_in&) — read GoldAmount%d, delegate to SetProperty.
inline void AITrigger_OnImport(AITriggerBase* t, bin_in* s) {
    using F = void(__thiscall*)(AITriggerBase*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x005f1e70))(t, s);
}
// AITrigger::SetProperty(const char*, const property&) -> int
inline int  AITrigger_SetProperty(AITriggerBase* t, const char* key, const property& val) {
    using F = int(__thiscall*)(AITriggerBase*, const char*, const property&);
    return reinterpret_cast<F>(meridian::rebase(0x005f1cf0))(t, key, val);
}
// TriggerWorldTriggerToggled::Test(uint64* refGuid) -> int  (proposed; shared
// predicate: cinema type 0x11 finished/flag → 1). Bundle-labeled SetProperty.
inline int  TriggerWorldTriggerToggled_Test(AITriggerBase* t, uint64_t* refGuid) {
    using F = int(__thiscall*)(AITriggerBase*, uint64_t*);
    return reinterpret_cast<F>(meridian::rebase(0x00473d60))(t, refGuid);
}

// ---- bilbo: player-side switch/trigger glue (BilboSwitches) ----------------
// bilbo::CheckForActivate(const uint64& guid) -> int — B-button dispatch.
inline int  Bilbo_CheckForActivate(bilbo* self, const uint64_t& guid) {
    using F = int(__thiscall*)(bilbo*, const uint64_t&);
    return reinterpret_cast<F>(meridian::rebase(0x0044cf70))(self, guid);
}
// bilbo::DrawIndicator(const uint64& guid, const vector3& worldOffset)
inline void Bilbo_DrawIndicator(bilbo* self, const uint64_t& guid, const vector3& worldOffset) {
    using F = void(__thiscall*)(bilbo*, const uint64_t&, const vector3&);
    reinterpret_cast<F>(meridian::rebase(0x0044ce60))(self, guid, worldOffset);
}
// bilbo::Triggers_DrawIndicator(void)
inline void Bilbo_Triggers_DrawIndicator(bilbo* self) {
    using F = void(__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x0044d370))(self);
}
// bilbo::Switches_DrawSwitchIndicator(void)
inline void Bilbo_Switches_DrawSwitchIndicator(bilbo* self) {
    using F = void(__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x0044d500))(self);
}
// bilbo::PointInTriggerVolume(const vector3& pt, int useSecondVolume) -> int
inline int  Bilbo_PointInTriggerVolume(bilbo* self, const vector3& pt, int useSecondVolume) {
    using F = int(__thiscall*)(bilbo*, const vector3&, int);
    return reinterpret_cast<F>(meridian::rebase(0x00673520))(self, pt, useSecondVolume);
}

// ---- Trigger script-action statics (C facade / xsc_ callbacks) -------------
// AddInvenItem(const char* name, int amount) — credit global bilboInventory.
inline void AddInvenItem(const char* name, int amount) {
    using F = void(__cdecl*)(const char*, int);
    reinterpret_cast<F>(meridian::rebase(0x004dba10))(name, amount);
}
// HideRigidInstanceByName(const char* name, int hide) — toggle hidden+collision.
inline void HideRigidInstanceByName(const char* name, int hide) {
    using F = void(__cdecl*)(const char*, int);
    reinterpret_cast<F>(meridian::rebase(0x004dbcd0))(name, hide);
}
// xsc_StartMineCartRide(uchar* xscArgs) — XScript callback.
inline void xsc_StartMineCartRide(unsigned char* xscArgs) {
    using F = void(__cdecl*)(unsigned char*);
    reinterpret_cast<F>(meridian::rebase(0x004db990))(xscArgs);
}
// xsc_EnableTriggerByName(uchar* xscAction)
inline void xsc_EnableTriggerByName(unsigned char* xscAction) {
    using F = void(__cdecl*)(unsigned char*);
    reinterpret_cast<F>(meridian::rebase(0x005e05b0))(xscAction);
}
// xsc_EnableFireFXAtVolume(uchar* xscAction)
inline void xsc_EnableFireFXAtVolume(unsigned char* xscAction) {
    using F = void(__cdecl*)(unsigned char*);
    reinterpret_cast<F>(meridian::rebase(0x005e0f30))(xscAction);
}
// xsc_HideRigidInstanceByName(uchar* xscAction) — multi-target hide/show.
inline void xsc_HideRigidInstanceByName(unsigned char* xscAction) {
    using F = void(__cdecl*)(unsigned char*);
    reinterpret_cast<F>(meridian::rebase(0x005da180))(xscAction);
}

} // namespace fn

} // namespace triggers_sdk
