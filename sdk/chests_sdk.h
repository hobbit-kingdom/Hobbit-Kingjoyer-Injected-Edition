// ============================================================================
//  chests_sdk.h  —  CHESTS / loot / pickups SDK for THE HOBBIT (2003) PC build
//  Entropy engine, MSVC, 32-bit (Meridian.exe, preferred base 0x00400000, ASLR off).
//
//  Reverse-engineered modding / trainer SDK. All addresses are absolute PC
//  virtual addresses; resolve them at runtime with meridian::rebase(0xADDR),
//  which applies the current module-base delta vs the analyzed image base.
//
//  This subsystem covers the game's loot economy:
//    * treasure_chest  — openable loot containers (gold/items, lid anim, trap,
//                         locked state). On open they dispense ChestContents
//                         reward rows by launching pickups and/or crediting
//                         bilboInventory directly.
//    * ChestContents   — a 0x78-byte reward row (item name, scale, value).
//    * pickup          — collectibles the player walks over (coins / courage
//                         points / health / quest items). The SAME class also
//                         models chest-ejected launched loot and the magnet/
//                         vacuum "chase Bilbo" behaviour, selected by flags.
//    * bilbo::Pickups_*— player-side per-frame proximity scan + grant logic.
//    * lockGadgets + GadgetWackAMole/WackAMole2/Pendulum + dlg_pickLock —
//                         the lockpicking minigame that gates a trapped chest;
//                         on success it calls treasure_chest::Open.
//
//  Field offsets are CONSOLIDATED from the per-chunk analyses
//  (chests__00/01/02.json). Offsets marked "?" are lower confidence. Only
//  well-evidenced fields are named; the rest is explicit padding so named
//  members land at their true byte offsets. These structs are NOT meant to be
//  instantiated — only reinterpret_cast onto live engine objects obtained from
//  a GUID / obj_mgr slot.
//
//  ---- USAGE / RECIPE ------------------------------------------------------
//    using namespace chests_sdk;
//
//    // Force-open the chest you have a slot pointer to (skips the lock minigame):
//    TreasureChest* chest = reinterpret_cast<TreasureChest*>(slotPtr);
//    fn::Chest_Open(chest);                  // dispenses loot immediately
//
//    // Or unlock without picking: clear trap level, then open.
//    if (fn::Chest_IsTrapped(chest)) chest->trapNumGadgets = 0;
//    fn::Chest_Open(chest);
//
//    // Auto-collect a pickup you have a slot pointer to (vacuum it to Bilbo):
//    Pickup* p = reinterpret_cast<Pickup*>(pickupSlotPtr);
//    if (fn::Pickup_IsGetAble(p) && !fn::Pickup_GetPickedUp(p))
//        fn::Pickup_SetupChase(p);           // it will fly to Bilbo and grant
//
//  __thiscall wrappers take the object pointer as the FIRST argument.
//  Statics / creators are __cdecl. Any method taking an INCOMPLETE engine type
//  BY VALUE cannot be a typed wrapper — those expose an address accessor (*_at)
//  with the raw signature in a comment. xstring/vector3/radian3/bbox ARE
//  complete (meridian_types.h), so their by-value signatures are ABI-safe.
// ============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase, vector3, radian3, bbox, xstring, xwstring, property, Ghidra aliases

// ---- Forward declarations for engine types we reference but don't model -----
// (Most are already declared globally in meridian_types.h; re-declaring a
//  struct name is harmless and keeps this header readable standalone.)
// The engine classes treasure_chest / pickup / lockGadgets / ChestContents /
// the gadget classes are forward-declared GLOBALLY in meridian_types.h. We
// model their byte layouts below under DISTINCT chests_sdk names to avoid a
// one-definition clash AND a name-lookup ambiguity with those opaque global
// forward declarations. Where the engine's CamelCase name is IDENTICAL to the
// global forward-decl (ChestContents, GadgetWackAMole, GadgetWackAMole2,
// GadgetPendulum) we suffix the layout type so that callers doing
// `using namespace chests_sdk;` never hit an ambiguous-name error:
//     engine ChestContents    -> chests_sdk::ChestContentsRow
//     engine GadgetWackAMole   -> chests_sdk::WackAMoleGadget
//     engine GadgetWackAMole2  -> chests_sdk::WackAMoleGadget2
//     engine GadgetPendulum    -> chests_sdk::PendulumGadget
// The engine's lowercase/underscore names (treasure_chest, pickup, lockGadgets)
// do not collide with TreasureChest / Pickup / LockGadgets, so those keep their
// natural CamelCase here.
struct object;            // engine base of treasure_chest / pickup (rigid_instance chain)
struct rigid_instance;    // intermediate base
struct bin_in;            // OnImport stream
struct bin_out;           // OnExport stream
struct bilbo;             // player object (Pickups_* methods live here)
struct bilboInventory;    // global item / gold / courage ledger
struct fx_object;         // glow / sparkle / sound FX
struct obj_mgr;
struct ui_win;            // dlg_pickLock base / OnUpdate arg
struct property;          // complete in meridian_types.h
struct chest_type;        // enum treasure_chest::chest_type (SetChestType arg)
struct CPBreakDown;       // pickup::BreakDownCP tally (5 byte counters)

namespace chests_sdk {

// ===========================================================================
//  0. Small enums / constants recovered from the disassembly
// ===========================================================================

// treasure_chest::chest_type — visual variant selected by SetChestType.
enum class eChestType : int32_t {
    Wood  = 0,   // default; chest_wood.rgeom / .anim
    Black = 1,   // chest_black.rgeom / .anim
    Gold  = 2,   // chest_gold.rgeom  / .anim
};

// lockGadgets::Update return code.
enum class eLockResult : int32_t {
    Running = 0,
    Success = 1,   // successFlag set (a gadget returned StopAction==9 -> ChestOpen)
    Failed  = 2,   // failFlag set (timeout or a gadget returned StopAction==8)
};

// pickup +0x16e state-flag bits (uint16). Behaviour is selected by these.
enum PickupFlag : uint16_t {
    PICKUP_ROTATE_SLOWLY = 0x0001,
    PICKUP_BOB_SLOWLY    = 0x0002,
    PICKUP_PICKED_UP     = 0x0004,  // collected; see Pickup_GetPickedUp
    PICKUP_LEAVING       = 0x0008,
    PICKUP_REGENERATES   = 0x0010,
    PICKUP_BEING_LAUNCHED = 0x0020, // arc-eject in progress; see Pickup_IsBeingLaunched
    PICKUP_SETTLED       = 0x0040,  // landed after a launch
    PICKUP_COURAGE       = 0x0080,  // courage-point class
    PICKUP_CHASING       = 0x0100,  // magnet/vacuum toward Bilbo
    PICKUP_VACUUM        = 0x0200,  // eligible for vacuum pickup
    PICKUP_AUTO_ATTRACT  = 0x0400,  // type-derived auto-attract (set in SetupTypeInfo)
    PICKUP_CHEST_SPAWNED = 0x0800,  // ejected from a chest
};

// ===========================================================================
//  1. ChestContentsRow — a single reward row (engine ChestContents, size 0x78)
//     Stored in an xarray<ChestContents> on the chest (base @ TreasureChest+0x234,
//     element stride 0x78). xstring is complete (meridian_types.h, sizeof 0x2c).
// ===========================================================================
#pragma pack(push, 1)
struct ChestContentsRow {
    uint8_t   header[0x14];   // 0x00  5-dword header (copied verbatim by CopyConstruct)
    ::xstring itemName;       // 0x14  inventory item name (sizeof 0x2c -> ends @ 0x40)
    float     scale;          // 0x40  per-item scale (SetElementContentsType writes 1.0)
    ::xstring secondString;   // 0x44  second embedded xstring (sizeof 0x2c -> ends @ 0x70)
    int32_t   value;          // 0x70  gold/score value (0x32/5/0xf/1 by item index)
    uint8_t   _pad74[0x78 - 0x74];          // pad to confirmed sizeof 0x78
};                            // sizeof == 0x78 (element size used by the deleting dtor)
#pragma pack(pop)
static_assert(sizeof(ChestContentsRow) == 0x78, "ChestContentsRow must be 0x78 bytes");

// ===========================================================================
//  2. TreasureChest — main loot container (consolidated layout)
//     Cast a live slot pointer to TreasureChest*. Do NOT instantiate.
//     Leading region (vtable .. ~0x140) is inherited object/rigid_instance.
//     NOTE: offsets 0x160/0x16c/0x188 carry overlapping interpretations
//     depending on the evidencing path (trap vs contents-array header); the
//     names below follow the dominant trap/loot reading.
// ===========================================================================
#pragma pack(push, 1)
struct TreasureChest {
    void*    vtable;                       // 0x000  &PTR_FUN_006ef1d8
    uint8_t  _pad004[0x14 - 0x04];         // 0x004  object header
    float    posX;                         // 0x014  world position X (Init drop-target source)
    float    posY;                         // 0x018  world position Y
    float    posZ;                         // 0x01c  world position Z
    uint8_t  _pad020[0x7b - 0x20];         // 0x020
    uint8_t  flagsByteB;                   // 0x07b  bit3(0x08) = opened/anim-played (Init/OnReset clear)
    uint8_t  _pad07c[0x7f - 0x7c];         // 0x07c
    uint8_t  flagsByteF;                   // 0x07f  bit0 = active/enabled (Init sets)
    uint8_t  _pad080[0x120 - 0x80];        // 0x080
    int32_t  isOpen;                       // 0x120  lid-open boolean (IsOpen returns this)
    uint8_t  _pad124[0x140 - 0x124];       // 0x124
    void*    animController;               // 0x140  anim ctrl (OnReset rewinds +0x10/+0x14/+0x68)
    uint8_t  _pad144[0x160 - 0x144];       // 0x144
    int32_t  contentsValueOrType;          // 0x160  OnImport 'Value'; GetProperty Chest Type enum
    uint8_t  _pad164[0x16c - 0x164];       // 0x164
    int32_t  trapNumGadgets;               // 0x16c  'TrapNumGadgets'; IsTrapped tests >0 (trap level)
    int32_t  trapDifficulty;               // 0x170  'TrapDifficulty' 0-Easy/1-Medium/2-Hard
    float    trapTime;                     // 0x174  'TrapTime'
    int32_t  trapDamageType;               // 0x178  'TrapDamageType' POISON_1..3
    uint8_t  _pad17c[0x180 - 0x17c];       // 0x17c
    uint32_t fxGuidLo;                     // 0x180  spin/glow FX object GUID low
    uint32_t fxGuidHi;                     // 0x184  spin/glow FX object GUID high
    int32_t  contentsValuePerItem;         // 0x188  Open per-item value (also spawn-rotation ptr in Init)
    uint8_t  _pad18c[0x190 - 0x18c];       // 0x18c  (initialRotation lives in this region)
    float    cameraPosX;                   // 0x190  'Camera Position' (vector3, GetProperty enum 0xc)
    float    cameraPosY;                   // 0x194
    float    cameraPosZ;                   // 0x198
    uint8_t  _pad19c[0x1ac - 0x19c];       // 0x19c
    ::xwstring chestTypeName;              // 0x1ac  chest-type name (ctor builds xwstring)
    uint8_t  _pad1d8[0x1f8 - (0x1ac + 0x2c)]; // 0x1d8 region after the 0x2c-byte xwstring
    float    contentsScale;                // 0x1f8  'ContentsScale' (default 1.0)
    ::xstring contentsItemName;            // 0x1fc  contents inventory item name
    uint8_t  _pad228[0x230 - (0x1fc + 0x2c)]; // 0x228 region after the 0x2c-byte xstring
    int32_t  openState;                    // 0x230  Open early-returns if !=0; dispense gate/counter
    ChestContentsRow* contentsArray;       // 0x234  reward rows (element stride 0x78)
    int32_t  contentsCapacity;             // 0x238  xarray<ChestContents> capacity
    int32_t  contentsCount;                // 0x23c  xarray<ChestContents> count
    int32_t  contentsGrowFlag;             // 0x240  xarray fixed-grow override (?)
    int32_t  timer0x244;                   // 0x244  runtime timer (OnReset zeroes) (?)
    float    extentX;                      // 0x248  Init = 50.0
    float    extentY;                      // 0x24c  Init = 300.0
    float    extentZ;                      // 0x250  Init = 300.0
    float    dropTargetX;                  // 0x254  Init copies posX
    float    dropTargetY;                  // 0x258  Init copies posY - 50.0
    float    dropTargetZ;                  // 0x25c  Init copies posZ
    int32_t  field0x260;                   // 0x260  Init zeroes (?)
};                                         // size >= 0x264
#pragma pack(pop)

// ===========================================================================
//  3. Pickup — collectible / launched-loot / vacuum object (consolidated layout)
//     Cast a live slot pointer to Pickup*. Do NOT instantiate.
//     Leading region (vtable .. ~0x126) is inherited object/rigid_ri.
// ===========================================================================
#pragma pack(push, 1)
struct Pickup {
    void*    vtable;                       // 0x000
    uint8_t  _pad004[0x7f - 0x04];         // 0x004  object header
    uint8_t  objectFlags;                  // 0x07f  bit0 = active/visible
    uint8_t  _pad080[0x82 - 0x80];         // 0x080
    uint8_t  tintRGBA[4];                  // 0x082  white (0xff) default tint (Init)
    uint8_t  _pad086[0x126 - 0x86];        // 0x086
    uint8_t  disabledFlags;                // 0x126  bit0 = not-getable (IsGetAble = ~&1)
    uint8_t  _pad127[0x160 - 0x127];       // 0x127
    void*    movingInfo;                   // 0x160  launch/chase helper (0x4c; see PickupMovingInfo)
    void*    glowFX;                       // 0x164  glow/FX object (DestroyGlow)
    int16_t  soundOrFxSlot;                // 0x168  spawned FX object slot / sound handle
    int16_t  amount;                       // 0x16a  quantity/value (GetAmount); Init = 5
    int16_t  typeIndex;                    // 0x16c  inventory item index (GetType/SetupTypeInfo/SetupFX)
    uint16_t stateFlags;                   // 0x16e  PickupFlag bitfield
    uint8_t  behaviorFlags;                // 0x16f  bit0 = chasing-active / award-on-deactivate gate
    int16_t  regenTimer;                   // 0x170  regeneration countdown (seeded from regenTime)
    int16_t  spawnBlinkTimer;              // 0x172  Init = 32000
    int16_t  regenTime;                    // 0x174  Init = 0xea6
    int16_t  settleTimer;                  // 0x176  ages after settling (flag 0x40)
    int16_t  glowOffDist;                  // 0x178  'GlowOffDist'
    int16_t  glowOnDist;                   // 0x17a  'GlowOnDist'
};                                         // size >= 0x17c
#pragma pack(pop)

// ---- Pickup launch/chase movement helper (heap block @ Pickup+0x160, ~0x4c) -
// Two views of the same buffer exist in the disassembly: the chase path uses
// named offsets below; the launch path treats it as float[9] = {start[3],
// target[3], duration, arc, elapsed}. Modeled here per the chase reading.
#pragma pack(push, 1)
struct PickupMovingInfo {
    uint8_t  _pad00[0x24 - 0x00];          // 0x00
    float    elapsed;                      // 0x24  advanced by dt, clamped to duration
    float    duration;                     // 0x28  chase divisor; seeded from random range
    uint8_t  _pad2c[0x38 - 0x2c];          // 0x2c
    float    startX;                       // 0x38  snapshot start position
    float    startY;                       // 0x3c
    float    startZ;                       // 0x40
    float    arcHeight;                    // 0x44  sin(progress*pi)*arcHeight added to Y
    int32_t  fxSlot;                       // 0x48  attached FX object slot
};                                         // sizeof ~0x4c (operator_new(0x4c) in SetupChase)
#pragma pack(pop)

// ===========================================================================
//  4. LockGadgets — lockpicking minigame container (consolidated layout)
//     Children are lockGadget* (GadgetWackAMole / WackAMole2 / Pendulum / ...).
//     Shared gadget vtable: +0x10 Update, +0x18 StopAction(->result code),
//     +0x1c SetCurrentGadget(bool), +0x20 TurnONGadget(bool).
// ===========================================================================
#pragma pack(push, 1)
struct LockGadgets {
    uint8_t  _pad00[0x08 - 0x00];          // 0x00
    int32_t  gadgetCount;                  // 0x08  number of child gadgets
    void**   gadgetArray;                  // 0x0c  lockGadget* array
    uint8_t  _pad10[0x15c - 0x10];         // 0x10
    float    lastTickTime;                 // 0x15c  Render tick/tock SFX gate
    uint8_t  _pad160[0x164 - 0x160];       // 0x160
    int32_t  indicatorX;                   // 0x164  Render progress-bar pixel
    uint8_t  _pad168[0x38c - 0x168];       // 0x168
    int32_t  currentGadgetIndex;           // 0x38c  active tumbler index (Action advances/clamps)
    float    timeRemaining;                // 0x390  Update -= 1/30; <0 -> fail; Action -=0.5 on mistake
    float    progressMax;                  // 0x394  progress-bar denominator
    uint8_t  _pad398[0x39c - 0x398];       // 0x398
    int32_t  successFlag;                  // 0x39c  set on StopAction==9 (ChestOpen) -> Update returns 1
    int32_t  failFlag;                     // 0x3a0  set on StopAction==8 (LockFailure) -> Update returns 2
};                                         // size >= 0x3a4
#pragma pack(pop)

// ===========================================================================
//  5. Lock gadget tumblers (lockGadget subclasses)
//     Only the evidenced fields are modeled; cast a live child gadget to the
//     matching layout. The base lockGadget activeFlag is at +0x18.
// ===========================================================================
#pragma pack(push, 1)
struct WackAMoleGadget {                   // engine GadgetWackAMole
    uint8_t  _pad00[0x18 - 0x00];          // 0x00
    int32_t  activeFlag;                   // 0x18  Update early-out when 0
    uint8_t  _pad1c[0x2dc - 0x1c];         // 0x1c
    char     currentLightIndex;            // 0x2dc wraps 0..5
    uint8_t  displayedLight;               // 0x2dd pattern value or 0xff (off)
    uint8_t  _pad2de[0x2e0 - 0x2de];       // 0x2de
    float    stepAccumulator;              // 0x2e0 += 1/30, reset on step
    char     targetLight;                  // 0x2e4 green-light match
    char     decoyLight;                   // 0x2e5 red-light match
    uint8_t  _pad2e6[0x2e8 - 0x2e6];       // 0x2e6
    float    stepInterval;                 // 0x2e8 step gate
    uint8_t  _pad2ec[0x2f0 - 0x2ec];       // 0x2ec
    float    timer;                        // 0x2f0 countdown 1/30
    int32_t  patternRow;                   // 0x2f4 row*6 into the light-pattern table
};
#pragma pack(pop)

#pragma pack(push, 1)
struct WackAMoleGadget2 {                  // engine GadgetWackAMole2
    uint8_t  _pad00[0x18 - 0x00];          // 0x00
    int32_t  isActive;                     // 0x18  cycling/sound gate
    uint8_t  _pad1c[0x24 - 0x1c];          // 0x1c
    int32_t  patternRow;                   // 0x24  row*6 into the light-pattern table
    uint32_t greenTargetValue;             // 0x28  match -> Chest_GreenLight
    uint32_t redTargetValue;               // 0x2c  match -> Chest_RedLight
    int32_t  stepIndex;                    // 0x30  column 0..5
    uint32_t currentLitIndex;              // 0x34  lit slot or 0xffffffff
    uint8_t  _pad38[0x8d4 - 0x38];         // 0x38
    float    stepInterval;                 // 0x8d4 step gate
    uint8_t  _pad8d8[0x8e0 - 0x8d8];       // 0x8d8
    float    stepAccumulator;              // 0x8e0 += 1/30
    float    countdownTimer;               // 0x8e4 -= 1/30; <0 -> stop
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PendulumGadget {                    // engine GadgetPendulum
    uint8_t  _pad00[0x18 - 0x00];          // 0x00
    int32_t  activeFlag;                   // 0x18  Update early-out when 0
    uint8_t  _pad1c[0x2c4 - 0x1c];         // 0x1c
    int32_t  renderOffset;                 // 0x2c4 +/- speed for swing direction
    uint8_t  _pad2c8[0x2dc - 0x2c8];       // 0x2c8
    int32_t  direction;                    // 0x2dc 0=increasing(right), 1=decreasing(left)
    int32_t  swingSpeed;                   // 0x2e0 step magnitude
    uint8_t  _pad2e4[0x2e8 - 0x2e4];       // 0x2e4
    int32_t  swingAngle;                   // 0x2e8 bounds 0x90(144)..0xda(218)
    float    animTimer;                    // 0x2ec -= 1/30
};
#pragma pack(pop)

// ===========================================================================
//  6. Typed call wrappers
//     __thiscall: object pointer is the FIRST argument.
// ===========================================================================
namespace fn {

// ---- treasure_chest lifecycle / setup --------------------------------------
// treasure_chest::treasure_chest(void) — placement ctor over an allocated block.
//   Raw sig: treasure_chest* __thiscall treasure_chest::treasure_chest(treasure_chest*)
//   (ctor address not captured in the analyzed chunks; expose accessor when found)

// treasure_chest::Init(vector3 pos, radian3 rot, vector3 scale, bbox box, int)
// vector3/radian3/bbox are complete, so the by-value ABI is reproduced faithfully.
inline void Chest_Init(TreasureChest* chest, const vector3& pos, const radian3& rot,
                       const vector3& scale, const bbox& box, int flag) {
    using F = void (__thiscall*)(TreasureChest*, const vector3&, const radian3&,
                                 const vector3&, const bbox&, int);
    reinterpret_cast<F>(meridian::rebase(0x004d3f30))(chest, pos, rot, scale, box, flag);
}

// treasure_chest::SetChestType(enum chest_type) — wood/black/gold visual variant.
inline void Chest_SetChestType(TreasureChest* chest, eChestType type) {
    using F = void (__thiscall*)(TreasureChest*, int32_t);
    reinterpret_cast<F>(meridian::rebase(0x004d6080))(chest, static_cast<int32_t>(type));
}

// ---- treasure_chest per-frame / open ---------------------------------------
// virtual treasure_chest::OnAdvanceLogic(float dt) — tick (creates glow FX).
inline void Chest_OnAdvanceLogic(TreasureChest* chest, float dt) {
    using F = void (__thiscall*)(TreasureChest*, float);
    reinterpret_cast<F>(meridian::rebase(0x004d4360))(chest, dt);
}
// treasure_chest::Open(void) — dispense loot (launch pickups + credit inventory).
inline void Chest_Open(TreasureChest* chest) {
    using F = void (__thiscall*)(TreasureChest*);
    reinterpret_cast<F>(meridian::rebase(0x004d5bd0))(chest);
}
// virtual treasure_chest::OnReset(void) — back to closed/un-looted state.
inline void Chest_OnReset(TreasureChest* chest) {
    using F = void (__thiscall*)(TreasureChest*);
    reinterpret_cast<F>(meridian::rebase(0x004d42b0))(chest);
}
// virtual treasure_chest::OnObjectDeactivate(void) — tears down lock sub-object.
inline void Chest_OnObjectDeactivate(TreasureChest* chest) {
    using F = void (__thiscall*)(TreasureChest*);
    reinterpret_cast<F>(meridian::rebase(0x00495fc0))(chest);
}

// ---- treasure_chest serialization ------------------------------------------
// virtual treasure_chest::OnImport(bin_in&) — load Value/trap/Contents.
inline void Chest_OnImport(TreasureChest* chest, bin_in* stream) {
    using F = void (__thiscall*)(TreasureChest*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x004d5180))(chest, stream);
}

// ---- treasure_chest queries ------------------------------------------------
// treasure_chest::IsOpen(void) -> int
inline int Chest_IsOpen(TreasureChest* chest) {
    using F = int (__thiscall*)(TreasureChest*);
    return reinterpret_cast<F>(meridian::rebase(0x004c8970))(chest);
}
// treasure_chest::IsTrapped(void) -> int  (trapNumGadgets > 0)
inline int Chest_IsTrapped(TreasureChest* chest) {
    using F = int (__thiscall*)(TreasureChest*);
    return reinterpret_cast<F>(meridian::rebase(0x004d57b0))(chest);
}

// ---- treasure_chest editor property grid -----------------------------------
// virtual treasure_chest::GetProperty(const char* key) -> property (by value).
// property is COMPLETE in meridian_types.h (blob 0x258), but MSVC returns large
// aggregates via a hidden sret pointer; expressing the exact ABI here is fragile.
// Use the address accessor and form the call at the site once the sret convention
// is pinned.  Raw sig: property __thiscall treasure_chest::GetProperty(const char*)
inline void* Chest_GetProperty_at() { return meridian::rebase(0x004d8140); }
// virtual treasure_chest::EnumerateProperties(xarray<property_desc>&)
//   Raw sig: void __thiscall treasure_chest::EnumerateProperties(xarray<property_desc>&)
inline void* Chest_EnumerateProperties_at() { return meridian::rebase(0x004d65b0); }

// ---- ChestContents (engine ChestContents == chests_sdk::ChestContentsRow) --
// ChestContents::CopyConstruct(const ChestContents&) — per-element copy ctor
// (proposed; the API bundle labels this xarray<ChestContents>::Append).
inline void ChestContents_CopyConstruct(ChestContentsRow* dst, const ChestContentsRow* src) {
    using F = void (__thiscall*)(ChestContentsRow*, const ChestContentsRow*);
    reinterpret_cast<F>(meridian::rebase(0x004d8c10))(dst, src);
}
// ChestContents scalar/vector deleting destructor (bundle labels it the ctor).
//   Raw sig: void* __thiscall ChestContents::`deleting dtor'(ChestContents*, uint flags)
inline void* ChestContents_DeletingDtor(ChestContentsRow* self, unsigned int flags) {
    using F = void* (__thiscall*)(ChestContentsRow*, unsigned int);
    return reinterpret_cast<F>(meridian::rebase(0x004d8bb0))(self, flags);
}

// ---- pickup lifecycle / setup ----------------------------------------------
// pickup::Init(vector3 pos, radian3 rot, vector3 scale, bbox box)
inline void Pickup_Init(Pickup* p, const vector3& pos, const radian3& rot,
                        const vector3& scale, const bbox& box) {
    using F = void (__thiscall*)(Pickup*, const vector3&, const radian3&,
                                 const vector3&, const bbox&);
    reinterpret_cast<F>(meridian::rebase(0x004af7a0))(p, pos, rot, scale, box);
}
// pickup::SetupTypeInfo(short typeIndex) — set type + per-type behaviour bits.
inline void Pickup_SetupTypeInfo(Pickup* p, short typeIndex) {
    using F = void (__thiscall*)(Pickup*, short);
    reinterpret_cast<F>(meridian::rebase(0x004b0eb0))(p, typeIndex);
}
// pickup::SetupFX(const bbox&) — create/attach glow/sparkle FX by item type.
inline int Pickup_SetupFX(Pickup* p, const bbox& box) {
    using F = int (__thiscall*)(Pickup*, const bbox&);
    return reinterpret_cast<F>(meridian::rebase(0x004b0900))(p, box);
}
// pickup::SetupLaunch(vector3 from, vector3 to, int a, int b) — arc-eject loot.
inline void Pickup_SetupLaunch(Pickup* p, const vector3& from, const vector3& to,
                               int a, int b) {
    using F = void (__thiscall*)(Pickup*, const vector3&, const vector3&, int, int);
    reinterpret_cast<F>(meridian::rebase(0x004af8d0))(p, from, to, a, b);
}
// pickup::SetupChase(void) — switch into magnet/vacuum-toward-Bilbo mode.
inline void Pickup_SetupChase(Pickup* p) {
    using F = void (__thiscall*)(Pickup*);
    reinterpret_cast<F>(meridian::rebase(0x004b3400))(p);
}

// ---- pickup per-frame motion / logic ---------------------------------------
// pickup::UpdateLaunch(float dt) — advance the launch arc.
inline void Pickup_UpdateLaunch(Pickup* p, float dt) {
    using F = void (__thiscall*)(Pickup*, float);
    reinterpret_cast<F>(meridian::rebase(0x004b2390))(p, dt);
}
// pickup::UpdateChase(float dt) — advance the chase/vacuum motion.
inline void Pickup_UpdateChase(Pickup* p, float dt) {
    using F = void (__thiscall*)(Pickup*, float);
    reinterpret_cast<F>(meridian::rebase(0x004b31f0))(p, dt);
}
// virtual pickup::OnAdvanceLogic(float dt) — main per-frame tick.
inline void Pickup_OnAdvanceLogic(Pickup* p, float dt) {
    using F = void (__thiscall*)(Pickup*, float);
    reinterpret_cast<F>(meridian::rebase(0x004afe00))(p, dt);
}
// virtual pickup::OnObjectDeactivate(void) — award + release FX/resources.
inline void Pickup_OnObjectDeactivate(Pickup* p) {
    using F = void (__thiscall*)(Pickup*);
    reinterpret_cast<F>(meridian::rebase(0x004b2310))(p);
}
// pickup::DestroyMovingInfo(void) — clear launch/chase bits + free the helper.
inline void Pickup_DestroyMovingInfo(Pickup* p) {
    using F = void (__thiscall*)(Pickup*);
    reinterpret_cast<F>(meridian::rebase(0x004b3730))(p);
}
// virtual pickup::Render(void) — billboard render.
inline void Pickup_Render(Pickup* p) {
    using F = void (__thiscall*)(Pickup*);
    reinterpret_cast<F>(meridian::rebase(0x0059b1d0))(p);
}
// virtual pickup::OnImport(bin_in&) — load type/amount/flags.
inline void Pickup_OnImport(Pickup* p, bin_in* stream) {
    using F = void (__thiscall*)(Pickup*, bin_in*);
    reinterpret_cast<F>(meridian::rebase(0x004b0c30))(p, stream);
}
// virtual pickup::SetProperty(const char* key, const property& val) -> int
inline int Pickup_SetProperty(Pickup* p, const char* key, const property& val) {
    using F = int (__thiscall*)(Pickup*, const char*, const property&);
    return reinterpret_cast<F>(meridian::rebase(0x004b0f30))(p, key, val);
}

// ---- pickup queries (small accessors) --------------------------------------
// pickup::GetType(void) -> xstring (by value). xstring is complete (sizeof 0x2c),
// but it is returned via a hidden sret pointer; use the accessor + cast at site.
//   Raw sig: xstring __thiscall pickup::GetType(pickup*)
inline void* Pickup_GetType_at() { return meridian::rebase(0x004b0e70); }
// pickup::GetTypeIndex(void) -> int
inline int Pickup_GetTypeIndex(Pickup* p) {
    using F = int (__thiscall*)(Pickup*);
    return reinterpret_cast<F>(meridian::rebase(0x004b0ea0))(p);
}
// pickup::GetAmount(void) -> float
inline float Pickup_GetAmount(Pickup* p) {
    using F = float (__thiscall*)(Pickup*);
    return reinterpret_cast<F>(meridian::rebase(0x004b0f50))(p);
}
// pickup::GetPickedUp(void) -> int  (flag 0x4)
inline int Pickup_GetPickedUp(Pickup* p) {
    using F = int (__thiscall*)(Pickup*);
    return reinterpret_cast<F>(meridian::rebase(0x004b1070))(p);
}
// pickup::IsGetAble(void) -> int
inline int Pickup_IsGetAble(Pickup* p) {
    using F = int (__thiscall*)(Pickup*);
    return reinterpret_cast<F>(meridian::rebase(0x004b1080))(p);
}
// pickup::IsBeingLaunched(void) -> int  (flag 0x20)
inline int Pickup_IsBeingLaunched(Pickup* p) {
    using F = int (__thiscall*)(Pickup*);
    return reinterpret_cast<F>(meridian::rebase(0x004b25f0))(p);
}

// ---- pickup statics: courage / spawning ------------------------------------
// pickup::BreakDownCP(CPBreakDown& out, int total, int maxCount) — denominate CP.
inline void Pickup_BreakDownCP(CPBreakDown* out, int total, int maxCount) {
    using F = void (__cdecl*)(CPBreakDown*, int, int);
    reinterpret_cast<F>(meridian::rebase(0x004b2600))(out, total, maxCount);
}
// pickup::SpawnCouragePickups(int amount, const vector3& at, uint64 ownerGuid, int)
inline void Pickup_SpawnCouragePickups(int amount, const vector3& at,
                                       uint64_t ownerGuid, int flag) {
    using F = void (__cdecl*)(int, const vector3&, uint64_t, int);
    reinterpret_cast<F>(meridian::rebase(0x004b2a60))(amount, at, ownerGuid, flag);
}
// pickup::FindSafeSpawnPoint(const vector3& origin, uint64 guid, vector3& out,
//                            float radius, float, float)
inline void Pickup_FindSafeSpawnPoint(const vector3& origin, uint64_t guid,
                                      vector3& out, float radius, float b, float c) {
    using F = void (__cdecl*)(const vector3&, uint64_t, vector3&, float, float, float);
    reinterpret_cast<F>(meridian::rebase(0x004b2740))(origin, guid, out, radius, b, c);
}
// pickup::SpawnChestItemPickup(vector3 from, vector3 to, int type, uint64 guid,
//                              float scale) — launch a chest reward item.
inline void Pickup_SpawnChestItemPickup(vector3 from, vector3 to, int type,
                                        uint64_t guid, float scale) {
    using F = void (__cdecl*)(vector3, vector3, int, uint64_t, float);
    reinterpret_cast<F>(meridian::rebase(0x00000000 /* addr not in analyzed chunks */))(
        from, to, type, guid, scale);
    // NOTE: SpawnChestItemPickup address was not captured in the analyzed chunks.
    //       Replace 0x00000000 with the real address before calling, or resolve
    //       it from treasure_chest::Open's call site.
}

// ---- bilbo: pickup driver (player-side glue) -------------------------------
// bilbo::Pickups_CheckForPickups(void) — per-frame proximity scan around Bilbo.
inline void Bilbo_Pickups_CheckForPickups(bilbo* self) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x00446010))(self);
}
// bilbo::Pickups_ShouldPickUp(object* pickup) -> int
inline int Bilbo_Pickups_ShouldPickUp(bilbo* self, object* pickupObj) {
    using F = int (__thiscall*)(bilbo*, object*);
    return reinterpret_cast<F>(meridian::rebase(0x00446180))(self, pickupObj);
}
// bilbo::Pickups_GetPickup(object* pickup) — apply the collected effect.
inline void Bilbo_Pickups_GetPickup(bilbo* self, object* pickupObj) {
    using F = void (__thiscall*)(bilbo*, object*);
    reinterpret_cast<F>(meridian::rebase(0x00446330))(self, pickupObj);
}

// ---- lockGadgets: lockpicking minigame -------------------------------------
// lockGadgets::Render(void)
inline void LockGadgets_Render(LockGadgets* lg) {
    using F = void (__thiscall*)(LockGadgets*);
    reinterpret_cast<F>(meridian::rebase(0x00529520))(lg);
}
// lockGadgets::Update(void) -> int  (0=running, 1=success, 2=fail)
inline eLockResult LockGadgets_Update(LockGadgets* lg) {
    using F = int (__thiscall*)(LockGadgets*);
    return static_cast<eLockResult>(reinterpret_cast<F>(meridian::rebase(0x005299e0))(lg));
}
// lockGadgets::Action(void) — handle a player tumbler action.
inline void LockGadgets_Action(LockGadgets* lg) {
    using F = void (__thiscall*)(LockGadgets*);
    reinterpret_cast<F>(meridian::rebase(0x0052a3f0))(lg);
}

// ---- lock gadget tumblers (Update only; others not in analyzed chunks) -----
inline void GadgetWackAMole_Update(WackAMoleGadget* g) {
    using F = void (__thiscall*)(WackAMoleGadget*);
    reinterpret_cast<F>(meridian::rebase(0x00526fc0))(g);
}
inline void GadgetWackAMole2_Update(WackAMoleGadget2* g) {
    using F = void (__thiscall*)(WackAMoleGadget2*);
    reinterpret_cast<F>(meridian::rebase(0x00528f90))(g);
}
inline void GadgetPendulum_Update(PendulumGadget* g) {
    using F = void (__thiscall*)(PendulumGadget*);
    reinterpret_cast<F>(meridian::rebase(0x00527850))(g);
}

// ---- dlg_pickLock: lockpick UI dialog --------------------------------------
// virtual dlg_pickLock::OnUpdate(ui_win* win, float dt) — drives the minigame,
// calls treasure_chest::Open on success. (Active chest is held at DAT_00734f1c.)
inline void DlgPickLock_OnUpdate(ui_win* dlg, ui_win* win, float dt) {
    using F = void (__thiscall*)(ui_win*, ui_win*, float);
    reinterpret_cast<F>(meridian::rebase(0x0051dbc5))(dlg, win, dt);
}

} // namespace fn

} // namespace chests_sdk
