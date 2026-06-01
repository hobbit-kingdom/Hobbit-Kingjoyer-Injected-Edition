// ============================================================================
//  bilbo_sdk.h  —  Player character (BILBO) SDK for THE HOBBIT (2003) PC build
//  Entropy engine, MSVC, 32-bit (Meridian.exe).
//
//  Reverse-engineered modding / trainer SDK. All addresses are absolute PC
//  virtual addresses; resolve them at runtime with meridian::rebase(0xADDR)
//  which applies the current module-base delta vs the analyzed image base.
//
//  Field offsets in the structs below are CONSOLIDATED across 16 per-chunk
//  analyses (majority + evidence). Offsets marked "?" are lower confidence.
//  Only well-evidenced fields are declared as named members; everything else
//  is padding so that named members land at their true offsets. The struct is
//  intentionally NOT meant to be instantiated — only reinterpret_cast onto the
//  live singleton returned by GetBilbo().
// ============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase(uint32_t), vector3, radian3, matrix4, xhandle, ...

// ---- Forward declarations for engine types we don't fully model -------------
struct CharacterObject;     // base of bilbo
struct object;              // base of CharacterObject
struct char_anim_player;    // embedded anim player
struct NPCObject;
struct pickup;
struct rope;
struct push_box;
struct property;
struct property_desc;
struct MessageInfo;
struct light;
struct bbox;
struct bilboInventory;      // global inventory singleton (defined below)
template <class T> struct xarray;
struct xstring;
struct xwstring;

namespace bilbo_sdk {

// ===========================================================================
//  1. Player logic-state enum  (authoritative: bilbo::State_GetName @0x0043a420)
//     Lives in bilbo at offset 0x8d4 (current) / 0x8d8 (pending) / 0x8dc (prev).
// ===========================================================================
enum class BilboState : int32_t {
    IDLE                 = 0x01,  // STAND / default
    RUN                  = 0x03,  // walk + run
    SNEAK                = 0x04,
    JUMP                 = 0x05,
    FALL                 = 0x06,
    LAND                 = 0x07,
    CROUCH_SLIDE         = 0x08,
    CLIMB_WALL           = 0x09,
    WALL_PULLUP          = 0x0a,
    EDGE_MOUNT           = 0x0b,
    EDGE_GRAB            = 0x0c,
    EDGE_PULLUP          = 0x0d,
    EDGE_DROP_OFF        = 0x0e,
    POLEJUMP             = 0x0f,
    CHAIN_ATTACK         = 0x10,  // Sting/Staff melee combo
    TARG_IDLE            = 0x11,  // lock-on idle (also swim/aim path)
    TARG_RUN             = 0x12,
    TARG_JUMP            = 0x13,  // (swim-jump shares 0x13)
    STONE_ATTACK         = 0x14,  // throw stone
    FIRST_PERSON_LOOK    = 0x15,
    TARG_STRAFEATTACK    = 0x16,
    FORWARD_INAIR_ATTACK = 0x17,
    BACKWARD_BLOCK       = 0x18,
    KNOCKBACK            = 0x19,  // also used as forced-cinematic target
    DEATH                = 0x1a,
    DEATH_FALL_OR_WATER  = 0x1b,
    CLIMB_LADDER         = 0x1c,
    LADDER_PULLUP        = 0x1d,
    MINE_CART_RIDE       = 0x1e,
    MINE_CART_SWING      = 0x1f,
    CONVERSATION_LISTEN  = 0x20,
    CONVERSATION_TALK    = 0x21,
    CINEMATIC            = 0x22,
    ROPE_CLIMB           = 0x23,
    HOISTING             = 0x28,  // hoist/crank a heavy object (past GetName table)
    BLOCKED              = 0x24,
    PUSH_BLOCK           = 0x25,
    SLIDING              = 0x26,
    IDLE_FIDGET          = 0x2a,
};

// Nav/locomotion sub-mode enum (bilbo::Nav_Advance switch; active mode @0x748).
enum class BilboNavMode : int32_t {
    GroundHug   = 2,
    LadderMount = 3,
    WallHug     = 4,
    EdgeGrab    = 7,
    EdgeMount   = 8,
    RopeClimb   = 9,
    Cinematic   = 0xc,
    Sliding     = 0xd,
    Launching   = 0xe,
    Jump        = 0x12,
};

// Inventory item indices (item count array @ bilboInventory+0x1cc, 0..0xC5).
enum BilboItem : int {
    ITEM_COINS_OR_VIGOR   = 1,
    ITEM_STONES           = 2,
    ITEM_HEALTH           = 4,   // <-- current HP lives HERE (inventory slot 4)
    ITEM_HEALTH_POOL2     = 5,
    ITEM_GOLD             = 6,   // silver pennies
    ITEM_COURAGE_SCORE    = 8,   // level-up threshold 1000
    ITEM_COIN_5           = 0x10,
    ITEM_COIN_10          = 0x11,
    ITEM_COIN_25          = 0x12,
    ITEM_COIN_50          = 0x13,
    ITEM_COIN_100         = 0x14,
    ITEM_TOTAL_SCORE      = 0x18,
    ITEM_POISON_STATE     = 0x1b,
    ITEM_STAFF_TIER1      = 0x1d,
    ITEM_STAFF_TIER2      = 0x1e,
    ITEM_STAFF_TIER3      = 0x1f,
    ITEM_STING_TIER1      = 0x26,
    ITEM_STING_TIER2      = 0x27,
    ITEM_STING_TIER3      = 0x28,
    ITEM_HEALTH_POTION    = 0x30,
    ITEM_ANTIDOTE         = 0x31,
    ITEM_STING_OWNED      = 0x33,
    ITEM_STAFF_OWNED      = 0x35,
    ITEM_ARKENSTONE       = 0x94,
    INVENTORY_NUM_ITEMS   = 0xC6, // 198 (bilboInventory::GetTotalItems)
};

// ===========================================================================
//  2. bilbo  —  player character struct (consolidated layout)
//     Cast GetBilbo() to bilbo*. Do NOT instantiate.
//     #pragma pack(1) so explicit padding lands members at true offsets.
// ===========================================================================
#pragma pack(push, 1)
struct bilbo {
    void*   vtable;                          // 0x000  (vtbl+0x14=SetPos, +0x28=GetPos, +0x128=ApplyDamage/SetHealth)
    uint8_t _pad008[0x08 - 0x04];            // 0x004
    float   objPosX2D;                       // 0x008  object-base 2D pos x / self-GUID lo (overloaded; used in collision/LOS)
    float   objPosZ2D;                       // 0x00c  object-base 2D pos z / self-GUID hi
    uint8_t _pad010[0x14 - 0x10];            // 0x010
    // ---- world / logic position (vector3) -------------------------------
    float   posX;                            // 0x014  logic position X (used by ALL distance/grab math)
    float   posY;                            // 0x018  logic position Y (apex tracking, fall height)
    float   posZ;                            // 0x01c  logic position Z
    uint8_t _pad020[0x44 - 0x20];            // 0x020
    // ---- world-space AABB (min then max) --------------------------------
    float   aabbMinX, aabbMinY, aabbMinZ;    // 0x044  bbox min (Platform/Hoist midpoint math)
    float   aabbMaxX, aabbMaxY, aabbMaxZ;    // 0x050  bbox max
    uint8_t _pad05c[0xa8 - 0x5c];            // 0x05c
    uint64_t groundContactGuid;              // 0x0a8  GUID of object Bilbo stands on (a8=lo, ac=hi)
    uint8_t _pad0b0[0xb1 - 0xb0];            // 0x0b0
    uint8_t  statusBits;                     // 0x0b1  bit5(0x20)=jump-allow override; bit2(4)=flat-slide
    uint8_t _pad0b2[0xc8 - 0xb2];            // 0x0b2
    uint64_t grabbedPushBoxGuid;             // 0x0c8  GUID of held push_box (also "200" in decomp)
    uint8_t _pad0d0[0xd4 - 0xd0];            // 0x0d0
    float    tweakCachedTurnA;               // 0x0d4  cached tweak[0x58]
    int32_t  tweakCachedCount;               // 0x0d8  cached tweak[0x60] (=8)
    float    tweakCachedScaleOne;            // 0x0dc  cached tweak[0x78] (=1.0)
    float    facingYawE0;                    // 0x0e0  facing/yaw mirror (set from ladder yaw on LADDER_PULLUP exit) ?
    uint8_t _pad0e4[0xe8 - 0xe4];            // 0x0e4
    uint32_t renderEventBits;                // 0x0e8  render/event status bitfield
    float    tweakCachedDist25;              // 0x0ec  cached tweak[0x70] (=25.0)
    uint8_t _pad0f0[0x111 - 0xf0];           // 0x0f0
    uint8_t  flagByte111;                    // 0x111  packed flag byte (bit2 toggled by 0x004948c0) ?
    uint8_t _pad112[0x124 - 0x112];          // 0x112
    int32_t  navSubStateField;               // 0x124  set to 2 on teleport; logic-disabled gate (skip state machine when set)
    void*    conversationCharObjPtr;         // 0x128  CharacterObject conversation ptr / logic-disabled gate
    uint8_t _pad12c[0x158 - 0x12c];          // 0x12c
    int32_t  switchField158;                 // 0x158  switch handle/index setter (0x00587cf0) ?
    uint8_t _pad15c[0x160 - 0x15c];          // 0x15c
    int32_t  switchField160;                 // 0x160  switch handle/index getter (0x004d57a0) ?
    uint8_t _pad164[0x250 - 0x164];          // 0x164
    int32_t  ringForcedFlag250;              // 0x250  set=1 by "IsRingEquipped"(0x00424ce0) — likely forced-visibility/ring ?
    uint8_t _pad254[0x3b0 - 0x254];          // 0x254  (embedded light sub-objects at +0x254/+0x258 live here)
    // ---- weapon-equip flag block (current + 0x4 shadow used by HOISTING) -
    int32_t  usingStone;                     // 0x3b0  bow/sling/stone equipped (D-Pad item==6)
    int32_t  usingStone_b;                   // 0x3b4
    int32_t  savedUsingStone;                // 0x3b8  pre-hoist shadow
    int32_t  savedUsingStone_b;              // 0x3bc
    int32_t  usingSting;                     // 0x3c0  Sting sword equipped (D-Pad item==3)
    int32_t  savedUsingSting;                // 0x3c4  pre-hoist shadow
    int32_t  usingSting_b;                   // 0x3c8
    int32_t  savedUsingSting_b;              // 0x3cc
    int32_t  usingStaff;                     // 0x3d0  Staff/walking-stick equipped (D-Pad item==5)
    int32_t  savedUsingStaff;                // 0x3d4
    int32_t  usingStaff_b;                   // 0x3d8
    int32_t  savedUsingStaff_b;              // 0x3dc
    int32_t  ringEffectActiveLatch;          // 0x3e0  ring/invisibility audio+fx active latch
    uint8_t _pad3e4[0x3e8 - 0x3e4];          // 0x3e4
    float    lastDamageSrcX;                 // 0x3e8  knockback source X
    uint8_t _pad3ec[0x3f0 - 0x3ec];          // 0x3ec
    float    lastDamageSrcZ;                 // 0x3f0  knockback source Z
    uint8_t _pad3f4[0x3fc - 0x3f4];          // 0x3f4
    float    knockbackScale;                 // 0x3fc
    int32_t  hitStaggerFlag;                 // 0x400  hit/stagger/forced-cinematic flag (->state 0x19)
    float    stateTimer404;                  // 0x404  generic state timer (Nav_SetSkid seed)
    uint64_t heldObjectGuid;                 // 0x408  held interactive / chain-attack victim GUID (408=lo,40c=hi)
    int32_t  conversationActiveFlag;         // 0x414  conversation active (==1) gate (StartTalking/EndTalking)
    int32_t  chapterFlagRoastMutton;         // 0x418  per-chapter flag (set by GrabGlobals)
    int32_t  chapterFlagDreamWorld;          // 0x41c  per-chapter flag
    int32_t  ringEquipped;                   // 0x420  ONE RING equipped flag (SetRingEquipped writes here) [canonical]
    int32_t  forcedVisibility;               // 0x424  ForcedVisibility / ring-forced flag; also timer430-active flag
    uint8_t _pad428[0x430 - 0x428];          // 0x428  (PostRender 2D overlay sub-object at +0x428)
    float    timerA430;                      // 0x430  generic timer (overlay fade alpha overloaded)
    float    waterTimer;                     // 0x434  water death timer (set on water entry)
    float    timerB438;                      // 0x438
    uint8_t _pad43c[0x44c - 0x43c];          // 0x43c
    int32_t  invulnerableFlag;               // 0x44c  OnApplyPain early-out / no-fall-damage / talk-request (overloaded)
    void*    tweaks;                         // 0x450  -> tuning/"tweaks" table (&DAT_0075b820); also reused as active traversal/surface object ptr
    uint8_t  animPlayer[0x460 - 0x454];      // 0x454  embedded char_anim_player (opaque; cast &animPlayer to char_anim_player*)
    int32_t  rideLockFlag;                   // 0x460  mine-cart ride link/active flag
    float    facingBasisX;                   // 0x464  facing-derived basis / position-for-Nav vec3
    float    facingBasisY;                   // 0x468
    float    facingBasisZ;                   // 0x46c
    int32_t  traversalActiveFlag;            // 0x470  edge/wall contact reference (cleared on traversal exits)
    float    facingYaw;                      // 0x474  PRIMARY facing yaw (radians) — used by ALL grab/sincos math
    int32_t  moveContactRef;                 // 0x478  movement contact reference (cleared on RUN exit)
    float    scale47c;                       // 0x47c  =1.0 (Init)
    uint8_t _pad480[0x484 - 0x480];          // 0x480  (logic-state mirror at +0x480 used by ApplyMoveInput ==5)
    // ---- climb/velocity-seed vector3 ------------------------------------
    float    climbOffsetX;                   // 0x484  velocity-seed / climb displacement / grab orient X
    float    climbOffsetY;                   // 0x488  (FALL seeds -30.0 here)
    float    climbOffsetZ;                   // 0x48c
    uint8_t _pad490[0x4a0 - 0x490];          // 0x490
    uint8_t  localTransform[0x40];           // 0x4a0  player local transform matrix4 (reset to identity on cart exit)
    uint8_t _pad4e0[0x524 - 0x4e0];          // 0x4e0
    char_anim_player* pullupAnimPlayer;      // 0x524  pull-up / body anim controller sub-object
    int32_t  currentAnimIndex;               // 0x528  current anim/frame index (*0x50 stride table)
    int32_t  animFrameCount;                 // 0x52c  total frames of current anim
    float    animCurrentFrame;               // 0x530  current anim frame/time
    int32_t  animLoopCount;                  // 0x534  anim loop/complete counter (>0 => finished once)
    uint8_t _pad538[0x554 - 0x538];          // 0x538
    int32_t  mineCartRideLinkFlag;           // 0x554  secondary mine-cart link flag
    uint8_t _pad558[0x560 - 0x558];          // 0x558
    void*    activeAnimEventPtr;             // 0x560  active anim-event/track ptr (+8=current anim id)
    void*    conversationCtrl;               // 0x564  active conversation/dialog controller
    uint8_t _pad568[0x580 - 0x568];          // 0x568
    int32_t  physicsEnableFlagA;             // 0x580  collision/physics re-enable flag A (set on traversal exits)
    uint8_t _pad584[0x58c - 0x584];          // 0x584
    int32_t  physicsDirtyCounterA;           // 0x58c  transform/dirty version counter A
    int32_t  physicsEnableFlagB;             // 0x590  collision/physics re-enable flag B
    uint8_t _pad594[0x59c - 0x594];          // 0x594
    int32_t  physicsDirtyCounterB;           // 0x59c  transform/dirty version counter B
    float    grabTargetX, grabTargetY, grabTargetZ; // 0x5a0 snapshot of grab point (Edge_BeginGrab)
    uint8_t _pad5ac[0x600 - 0x5ac];          // 0x5ac  (conversation anim layer at +0x5ac)
    uint8_t  inputBuffer[0x128];             // 0x600  raw input/command buffer (zeroed by SetInput(0))
    // --- selected input/edge-trigger latches within the buffer region ----
    // (offsets below alias into / just after inputBuffer; declared via union-free padding)
    uint8_t _pad728[0x740 - 0x728];          // 0x728
    int32_t  inputEnabled;                   // 0x740  player-input enabled flag (SetInput)
    uint8_t _pad744[0x748 - 0x744];          // 0x744
    int32_t  navModeActive;                  // 0x748  ACTIVE nav mode (BilboNavMode) — dispatched by Nav_Advance
    int32_t  navModeRequested;               // 0x74c  requested nav mode
    int32_t  navModeTimer;                   // 0x750  nav-mode timer (zeroed on change)
    // ---- primary velocity vector3 ---------------------------------------
    float    velX;                           // 0x754  velocity X / stick-input X (rope push)
    float    velY;                           // 0x758  velocity Y (vertical) / jump impulse / climb speed
    float    velZ;                           // 0x75c  velocity Z
    int32_t  navState760;                    // 0x760  grounded flag / nav_state (Nav_ChangeTo writes here)
    int32_t  wallContactFlag;                // 0x764  on-wall/climbing flag
    int32_t  airborneFlag768;                // 0x768  in-air flag (CanJump requires ==0)
    uint8_t _pad76c[0x780 - 0x76c];          // 0x76c  (contactFlag2 @0x770)
    float    skidVelX, skidVelY, skidVelZ;   // 0x780  skid impulse vector (Nav_SetSkid)
    float    skidDuration;                   // 0x78c
    float    skidTimer;                      // 0x790
    float    moveSpeed;                      // 0x794  move-speed / anim-playback-rate / state timer (heavily overloaded)
    float    moveScaleX;                     // 0x798  move-scale X (1.0 normal, ~0.333 sneak)
    float    moveScaleZ;                     // 0x79c  move-scale Z
    float    velAccumX;                      // 0x7a0  velocity/input accumulator (zeroed on most state entries)
    float    velAccumY;                      // 0x7a4
    float    velAccumZ;                      // 0x7a8
    float    desiredFacingYaw;               // 0x7ac  desired/target yaw (Combat_GetYawToTarget result)
    float    turnRateCap;                    // 0x7b0  turn-rate / move-mode cap
    float    velX7b4, velY7b8, velZ7bc;      // 0x7b4  secondary/jump velocity vector3
    int32_t  navFrameScratch;                // 0x7c0  per-frame nav scratch / pole-knocked-off flag
    uint8_t _pad7c4[0x7d0 - 0x7c4];          // 0x7c4  (respawn pos @0x7c4 in some paths)
    float    wallPlaneNX, wallPlaneNY, wallPlaneNZ; // 0x7d0 wall plane normal (+0x7d0 is plane; tangent at 7cc/7d4/7d8)
    uint8_t _pad7dc[0x7e0 - 0x7dc];          // 0x7dc
    float    wallHitX, wallHitY, wallHitZ;   // 0x7e0  wall hit point
    uint8_t _pad7ec[0x7f8 - 0x7ec];          // 0x7ec
    float    fallTimer7f8;                   // 0x7f8  fall timer / wall-grab cooldown
    uint8_t _pad7fc[0x804 - 0x7fc];          // 0x7fc  (edge-grab sub-state @0x7fc, wall-climb progress @0x804 overlap region)
    int32_t  hasValidEdge;                   // 0x804  edge-found flag (set by CollectEdgeInfo/FindClosestEdgePoint)
    uint8_t _pad808[0x830 - 0x808];          // 0x808  (chosen edge endpoints @0x808/0x814)
    float    closestEdgeX, closestEdgeY, closestEdgeZ; // 0x830 closest edge point
    uint8_t _pad83c[0x840 - 0x83c];          // 0x83c
    float    edgeDirX;                       // 0x840  edge tangent/facing X (atan2 arg)
    int32_t  ringExpiredFlag;                // 0x844  One Ring invisibility expired/blink flag
    float    ringWarnTimer;                  // 0x848  ring warning/fade countdown (6.0s)
    uint8_t _pad84c[0x854 - 0x84c];          // 0x84c  (edgeDirZ @0x848 overlaps; edge-mount fields 0x854..0x85c)
    int32_t  edgeMountTimer;                 // 0x854  edge-mount timer/sub-state
    uint64_t edgeObjectGuid;                 // 0x858  latched edge object GUID (858=lo,85c=hi)
    uint8_t _pad860[0x8a0 - 0x860];          // 0x860  (active edge-point buffer)
    float    launchTargetX, launchTargetY, launchTargetZ; // 0x8a0 launch target point
    float    launchStartX, launchStartY, launchStartZ;    // 0x8ac launch start point
    float    launchTotalTime;                // 0x8b8
    float    launchArcHeight;                // 0x8bc
    float    launchElapsed;                  // 0x8c0
    int32_t  inWaterFlag8c4;                 // 0x8c4  in-water / drowning / footfall-suppress (overloaded)
    float    waterDepthOrSink;               // 0x8c8  water depth / sink speed
    uint8_t _pad8cc[0x8d4 - 0x8cc];          // 0x8cc
    // ---- STATE MACHINE TRIAD --------------------------------------------
    BilboState currentState;                 // 0x8d4  CURRENT logic state
    int32_t    pendingState;                 // 0x8d8  pending/next state (also "current anim id" / level-id in some paths)
    int32_t    prevStateOrDeathCause;        // 0x8dc  prev state / death-cause (audio) / mine-cart link discriminator
    uint8_t _pad8e0[0x91c - 0x8e0];          // 0x8e0
    float    stateElapsedTimer;              // 0x91c  per-state elapsed timer / stick-up magnitude / normalized progress
    float    deltaTime;                      // 0x920  per-frame delta time (set by OnAdvanceLogic; read everywhere)
    uint8_t _pad924[0x964 - 0x924];          // 0x924  (16-entry state-history ring log lives at +0x924)
    int32_t  advanceReentryGuard;            // 0x964  State_Advance re-entrancy guard (sign-flipped)
    uint8_t _pad968[0x9a4 - 0x968];          // 0x968
    const char* lastChangeFile;              // 0x9a4  __FILE__ of last debug_ChangeStateTo
    int32_t  lastChangeLine;                 // 0x9a8  __LINE__
    uint8_t _pad9ac[0x9b4 - 0x9ac];          // 0x9ac
    int32_t  stateForceFlag;                 // 0x9b4  force re-run state even if unchanged
    float    slideVelX, slideVelY, slideVelZ;// 0x9b8  slide velocity vec3 (also run accel accumulators)
    uint8_t _pad9c4[0x9c8 - 0x9c4];          // 0x9c4
    float    fallApexMaxY;                   // 0x9c8  fall apex max Y (landing damage)
    float    fallApexMinY;                   // 0x9cc  fall apex min Y / start height
    int32_t  hardLandingFlag;                // 0x9d0  (also "airborne flag" in locomotion arbiter)
    uint8_t _pad9d4[0xa00 - 0x9d4];          // 0x9d4  (attack/combo accumulators 0x9fc/0xa00)
    float    moveHoldTimer;                  // 0xa00
    float    jumpHeightAccum;                // 0xa04  jump height accum (TARG_JUMP -> 0x17 at >=10) / block-repeat counter
    int32_t  stoneThrownLatch;               // 0xa08  one-shot stone-thrown latch / stone-attack active flag
    float    fpLookTimer;                    // 0xa0c
    uint8_t _pada10[0xa18 - 0xa10];          // 0xa10  (edge cursor timer @0xa10)
    uint64_t ledgeAttachHandle;              // 0xa18  ledge/wall-pullup attach handle (a18=lo,a1c=hi)
    const char* cinematicAnimName;           // 0xa20  ptr to scripted cinematic anim name
    uint8_t _pada24[0xa4c - 0xa24];          // 0xa24
    float    cinematicProgressThreshold;     // 0xa4c
    uint64_t hoistObjectGuid;                // 0xa50  hoist/churn object GUID (a50=lo,a54=hi)
    int32_t  pickupCompleteFlag;             // 0xa58  HOISTING pickup-complete flag
    uint8_t _pada5c[0xa60 - 0xa5c];          // 0xa5c
    float    pushBlockAccumX, pushBlockAccumY, pushBlockAccumZ; // 0xa60 push-block accumulator
    uint8_t _pada6c[0xa70 - 0xa6c];          // 0xa6c  (slide speed @0xa6c)
    float    idleTimer;                      // 0xa70  seconds-since-input idle timer (fidget gating)
    float    fidgetCooldownTimer;            // 0xa74  secondary idle/fidget cooldown timer
    // ---- large sub-state regions (rope cache, edge records, combat targets, lights, web) ----
    uint8_t _pada78[0x3a0c - 0xa78];         // 0xa78
    float    grabCenterX, grabCenterY, grabCenterZ; // 0x3a0c edge grab center / probe point (ComputeGrabCenter)
    uint8_t _pad3a18[0x3a34 - 0x3a18];       // 0x3a18  (grab center dup @0x3a18, cooldown @0x3a30)
    float    ropeGrabXform[6];               // 0x3a34  cached rope grab transform (pos+dir)
    uint8_t _pad3a4c[0x3a50 - 0x3a4c];       // 0x3a4c
    uint64_t ropeGuid;                       // 0x3a50  current/grabbed/tracked rope GUID (3a50=lo,3a54=hi)
    uint8_t  ropeSegmentScratch[0x4658 - 0x3a58]; // 0x3a58  rope segment cache/scratch (stride 0x18; seg pos cache @0x3a60)
    int32_t  ropeSegmentCount;               // 0x4658  cached rope segment count
    int32_t  ropeSegmentIndex;               // 0x465c  grabbed rope segment index
    float    ropeGrabParam;                  // 0x4660  parametric grab pos on segment
    int32_t  ropeIsVertical;                 // 0x4664  rope::IsVertical cache / rope-vs-vine selector
    int32_t  ropeTrackedFlag;                // 0x4668  is-climbing-rope flag
    float    ropeReleaseCooldown;            // 0x466c  re-grab cooldown / pole grab timer
    uint64_t lastReleasedRopeGuid;           // 0x4670  last released rope GUID (4670=lo,4674=hi)
    uint8_t _pad4678[0x4680 - 0x4678];       // 0x4678  (rope sub-state 0x4678/0x467c)
    uint64_t ladderGuid;                     // 0x4680  tracked ladder GUID (4680=lo,4684=hi)
    uint8_t _pad4688[0x46a0 - 0x4688];       // 0x4688
    float    ladderRefX, ladderRefY, ladderRefZ;   // 0x46a0 ladder grab/ref point
    float    ladderAnchorX;                  // 0x46ac ladder anchor (approach vector base)
    uint8_t _pad46b0[0x46b4 - 0x46b0];       // 0x46b0
    float    ladderAnchorZ;                  // 0x46b4
    float    ladderFacingX, ladderFacingY, ladderFacingZ; // 0x46b8 ladder facing normal (dot for mount anim)
    uint8_t _pad46c4[0x46cc - 0x46c4];       // 0x46c4
    int32_t  weaponCycleSelector;            // 0x46cc  weapon-cycle / first-person sub-mode / equipped index (-1/0/2)
    int32_t  targetLockEnabled;              // 0x46d0  TARGETING/lock-on active flag (also combat target ptr)
    int32_t  activeTargetIndex;              // 0x46d4  active lock-on target index (-1 = none)
    float    targetPosArray[2];              // 0x46d8  target pos array base (stride 8: lo @+0, hi @+4)
    // (struct intentionally ends here at 0x46e0; higher-offset blocks — combat
    //  target array @0x4cd8, Sting light GUIDs @0x4dc8, ring fade @0x4eb8,
    //  switch/trigger handles @0x4ec8.., push-box GUIDs @0x5918.., poison block
    //  @0x5f34, safe-pos @0x5f44, web slots @0x59c4 — are NOT modeled as members.
    //  Reach them with bilbo_sdk::field<T>(p, off::X) using the constants below.)
} ;
#pragma pack(pop)

// NOTE: The single struct above is large and a few of the very-high-offset
// blocks (rope cache, combat target array, light GUIDs, web slots) overlap
// imperfectly because their exact internal sizes were not fully recovered.
// For trainer use prefer the OFFSET CONSTANTS below + raw byte access; they
// are the authoritative, evidence-backed numbers and avoid struct-packing
// surprises.

// ===========================================================================
//  2b. Authoritative bilbo field offset constants (use with byte access)
// ===========================================================================
namespace off {
    // position / transform
    constexpr uint32_t POS_X                 = 0x014;
    constexpr uint32_t POS_Y                 = 0x018;
    constexpr uint32_t POS_Z                 = 0x01c;
    constexpr uint32_t AABB_MIN              = 0x044;   // vec3
    constexpr uint32_t AABB_MAX              = 0x050;   // vec3
    constexpr uint32_t GROUND_CONTACT_GUID   = 0x0a8;   // u64
    constexpr uint32_t FACING_YAW            = 0x474;   // float (radians)
    // weapon-equip flags
    constexpr uint32_t USING_STONE           = 0x3b0;
    constexpr uint32_t USING_STING           = 0x3c0;
    constexpr uint32_t USING_STAFF           = 0x3d0;
    constexpr uint32_t WEAPON_CYCLE_SEL      = 0x46cc;
    // ring / invisibility
    constexpr uint32_t RING_EQUIPPED         = 0x420;   // int (canonical)
    constexpr uint32_t FORCED_VISIBILITY     = 0x424;
    constexpr uint32_t RING_EXPIRED_FLAG     = 0x844;
    constexpr uint32_t RING_WARN_TIMER       = 0x848;
    constexpr uint32_t RING_FADE_WEIGHT      = 0x13a0;  // float [0,1]
    // state machine
    constexpr uint32_t CURRENT_STATE         = 0x8d4;   // BilboState
    constexpr uint32_t PENDING_STATE         = 0x8d8;
    constexpr uint32_t PREV_STATE            = 0x8dc;
    constexpr uint32_t STATE_FORCE_FLAG      = 0x9b4;
    constexpr uint32_t STATE_ELAPSED_TIMER   = 0x91c;
    constexpr uint32_t DELTA_TIME            = 0x920;
    // nav
    constexpr uint32_t NAV_MODE_ACTIVE       = 0x748;
    constexpr uint32_t NAV_MODE_REQUESTED    = 0x74c;
    constexpr uint32_t NAV_STATE_760         = 0x760;
    // velocity
    constexpr uint32_t VEL                   = 0x754;   // vec3 (primary)
    constexpr uint32_t VEL_ACCUM             = 0x7a0;   // vec3
    constexpr uint32_t MOVE_SPEED            = 0x794;
    // input
    constexpr uint32_t INPUT_ENABLED         = 0x740;
    constexpr uint32_t INPUT_BUFFER          = 0x600;   // 0x128 bytes
    // health / poison (NOTE: HEALTH itself is an INVENTORY slot, not here)
    constexpr uint32_t POISON_ACTIVE         = 0x5f34;  // IsPoisoned
    constexpr uint32_t POISON_TIME           = 0x5f38;
    constexpr uint32_t POISON_DAMAGE         = 0x5f40;
    constexpr uint32_t SAFE_POS              = 0x5f44;  // vec3 checkpoint
    constexpr uint32_t SAFE_POS_BACKUP       = 0x5f50;  // vec3
    // traversal / object GUIDs
    constexpr uint32_t HELD_OBJECT_GUID      = 0x408;   // u64
    constexpr uint32_t GRABBED_PUSHBOX_GUID  = 0x0c8;   // u64
    constexpr uint32_t ROPE_GUID             = 0x3a50;  // u64
    constexpr uint32_t LADDER_GUID           = 0x4680;  // u64
    constexpr uint32_t HOIST_OBJECT_GUID     = 0xa50;   // u64
    // combat targeting
    constexpr uint32_t TARGET_LOCK_ENABLED   = 0x46d0;
    constexpr uint32_t ACTIVE_TARGET_INDEX   = 0x46d4;
    constexpr uint32_t TARGET_COUNT          = 0x4cd8;
    constexpr uint32_t NEAREST_ENEMY_GUID    = 0x5908;  // u64
    // surface / chapter
    constexpr uint32_t CHAPTER_ROASTMUTTON   = 0x418;
    constexpr uint32_t SPECIAL_SURFACE_FLAG  = 0x5960;
}

// ===========================================================================
//  3. bilboInventory  —  global singleton @ &DAT_0075bbe0
// ===========================================================================
namespace inv_off {
    constexpr uint32_t QUESTS_COMPLETED  = 0x004;   // int[50]
    constexpr uint32_t QUEST_ID_ARRAY    = 0x104;   // int[50] (bit 0x10000000 = required)
    constexpr uint32_t ITEM_COUNTS       = 0x1cc;   // float[0xC6], stride 4
    constexpr uint32_t SELECTED_DPAD     = 0x420;   // int (GetDPadSlotSelected)
    constexpr uint32_t ITEM_MIN          = 0x4e4;   // float[0xC6], stride 8
    constexpr uint32_t ITEM_MAX          = 0x4e8;   // float[0xC6], stride 8
    constexpr uint32_t MAX_HEALTH        = 0xb34;   // float
    constexpr uint32_t DPAD_SLOTS        = 0xb38;   // {int id, int sub}[4]
    constexpr uint32_t ACTIVE_DPAD_SLOT  = 0xb58;   // int (also selected-item-id)
    constexpr uint32_t SELECTED_SLOT_IDX = 0xb5c;   // int
    constexpr uint32_t NAME_HASH_TABLE   = 0xb60;   // ptr
}

// ===========================================================================
//  4. Typed function wrappers (call via reinterpret_cast<T>(rebase(addr)))
//     __thiscall is modeled as __fastcall(ecx=this, edx=unused) on MSVC; here
//     we expose them as free helpers taking the instance pointer explicitly.
// ===========================================================================
namespace fn {

// ---- globals -------------------------------------------------------------
inline bilbo* GetBilbo() {
    using F = bilbo* (__cdecl*)();
    return reinterpret_cast<F>(meridian::rebase(0x0041bcc0))();
}
inline uint64_t GetBilboGuid() {
    using F = uint64_t (__cdecl*)();
    return reinterpret_cast<F>(meridian::rebase(0x0041bcd0))();
}
inline bilboInventory* GetInventory() {
    return reinterpret_cast<bilboInventory*>(meridian::rebase(0x0075bbe0));
}

// ---- lifecycle / core ----------------------------------------------------
inline void OnAdvanceLogic(bilbo* p, float dt) {
    using F = void (__thiscall*)(bilbo*, float);
    reinterpret_cast<F>(meridian::rebase(0x0041e360))(p, dt);
}
inline void Reset(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x00424cf0))(p);
}
inline void OnTeleport(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x00424f20))(p);
}

// ---- STATE MACHINE -------------------------------------------------------
// debug_ChangeStateTo(this, BilboState, __FILE__, __LINE__) — the canonical
// "force the player into state X" entry point. Pass any string + 0 for file/line.
inline void ChangeStateTo(bilbo* p, BilboState s, const char* file = "trainer", int line = 0) {
    using F = void (__thiscall*)(bilbo*, int, const char*, int);
    reinterpret_cast<F>(meridian::rebase(0x0043a3f0))(p, static_cast<int>(s), file, line);
}
inline void State_Advance(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x00439a60))(p);
}
inline const char* State_GetName(bilbo* p, BilboState s) {
    using F = const char* (__thiscall*)(bilbo*, int);
    return reinterpret_cast<F>(meridian::rebase(0x0043a420))(p, static_cast<int>(s));
}

// ---- nav -----------------------------------------------------------------
inline void Nav_Advance(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x00442f50))(p);
}
inline void Nav_ChangeTo(bilbo* p, BilboNavMode mode) {
    using F = void (__thiscall*)(bilbo*, int);
    reinterpret_cast<F>(meridian::rebase(0x00442550))(p, static_cast<int>(mode));
}

// ---- input ---------------------------------------------------------------
inline void SetInput(bilbo* p, int enabled) {
    using F = void (__thiscall*)(bilbo*, int);
    reinterpret_cast<F>(meridian::rebase(0x0041c2b0))(p, enabled);
}
inline void FlushInput(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x004336e0))(p);
}

// ---- health / poison -----------------------------------------------------
inline float GetHealth(bilbo* p) {
    using F = float (__thiscall*)(bilbo*);
    return reinterpret_cast<F>(meridian::rebase(0x00422420))(p);
}
inline void ModifyHealth(bilbo* p, int delta) {
    using F = void (__thiscall*)(bilbo*, int);   // virtual ModifyHealth
    reinterpret_cast<F>(meridian::rebase(0x0052e990))(p, delta);
}
inline float GetVigorHealth(bilbo* p) {
    using F = float (__thiscall*)(bilbo*);
    return reinterpret_cast<F>(meridian::rebase(0x004228e0))(p);
}
inline int   IsPoisoned(bilbo* p) {
    using F = int (__thiscall*)(bilbo*);
    return reinterpret_cast<F>(meridian::rebase(0x00422450))(p);
}
inline void  ResetPoison(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x00427270))(p);
}
inline void  ResetToSafePos(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x0044ca80))(p);
}

// ---- ring / invisibility -------------------------------------------------
inline void SetRingEquipped(bilbo* p, int equip, int instant) {
    using F = void (__thiscall*)(bilbo*, int, int);
    reinterpret_cast<F>(meridian::rebase(0x00423c90))(p, equip, instant);
}
inline void RingExpired(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x004f5080))(p);
}

// ---- combat --------------------------------------------------------------
inline void  FindTargets(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x004267a0))(p);
}
inline void  Combat_UpdateTarget(bilbo* p) {
    using F = void (__thiscall*)(bilbo*);
    reinterpret_cast<F>(meridian::rebase(0x00426c60))(p);
}
inline float Combat_GetYawToTarget(bilbo* p) {
    using F = float (__thiscall*)(bilbo*);
    return reinterpret_cast<F>(meridian::rebase(0x00426760))(p);
}
inline int   Combat_ThrowStone(bilbo* p, int arg) {
    using F = int (__thiscall*)(bilbo*, int);
    return reinterpret_cast<F>(meridian::rebase(0x00425fb0))(p, arg);
}

// ---- traversal predicates ------------------------------------------------
inline int Ladder_CanGrab(bilbo* p) {
    using F = int (__thiscall*)(bilbo*);
    return reinterpret_cast<F>(meridian::rebase(0x004383b0))(p);
}
inline int Rope_CanGrab(bilbo* p) {
    using F = int (__thiscall*)(bilbo*);
    return reinterpret_cast<F>(meridian::rebase(0x00449e80))(p);
}
inline int CanJump(bilbo* p) {
    using F = int (__thiscall*)(bilbo*);
    return reinterpret_cast<F>(meridian::rebase(0x00422510))(p);
}

// ---- inventory (__thiscall on the inventory singleton) -------------------
inline float Inv_Has(bilboInventory* inv, int item) {
    using F = float (__thiscall*)(bilboInventory*, int);
    return reinterpret_cast<F>(meridian::rebase(0x00434ca0))(inv, item);
}
inline void  Inv_Set(bilboInventory* inv, int item, float v) {
    using F = void (__thiscall*)(bilboInventory*, int, float);
    reinterpret_cast<F>(meridian::rebase(0x00434c40))(inv, item, v);
}
inline void  Inv_Add(bilboInventory* inv, int item, float v) {
    using F = void (__thiscall*)(bilboInventory*, int, float);
    reinterpret_cast<F>(meridian::rebase(0x00434d10))(inv, item, v);
}
inline void  Inv_Remove(bilboInventory* inv, int item, float v) {
    using F = void (__thiscall*)(bilboInventory*, int, float);
    reinterpret_cast<F>(meridian::rebase(0x00434dd0))(inv, item, v);
}
inline float Inv_GetMax(bilboInventory* inv, int item) {
    using F = float (__thiscall*)(bilboInventory*, int);
    return reinterpret_cast<F>(meridian::rebase(0x00434fb0))(inv, item);
}
inline float Inv_GetMaxHealth(bilboInventory* inv) {
    using F = float (__thiscall*)(bilboInventory*);
    return reinterpret_cast<F>(meridian::rebase(0x00434c10))(inv);
}
inline void  Inv_SetMaxHealth(bilboInventory* inv, float v) {
    using F = void (__thiscall*)(bilboInventory*, float);
    reinterpret_cast<F>(meridian::rebase(0x00434c20))(inv, v);
}
inline int   Inv_GetItemIndex(bilboInventory* inv, const xstring& name) {
    using F = int (__thiscall*)(bilboInventory*, const xstring&);
    return reinterpret_cast<F>(meridian::rebase(0x00434eb0))(inv, name);
}

} // namespace fn

// ===========================================================================
//  5. Raw byte accessors (offset-based; safest for trainers)
// ===========================================================================
template <class T> inline T&  field(void* base, uint32_t o) {
    return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(base) + o);
}

// ===========================================================================
//  TRAINER RECIPES
//  ---------------------------------------------------------------------------
//  // Read / write current HEALTH (health is INVENTORY item 4, NOT a bilbo field):
//      bilboInventory* inv = bilbo_sdk::fn::GetInventory();
//      float hp     = bilbo_sdk::fn::Inv_Has(inv, bilbo_sdk::ITEM_HEALTH);
//      float maxhp  = bilbo_sdk::fn::Inv_GetMaxHealth(inv);
//      bilbo_sdk::fn::Inv_Set(inv, bilbo_sdk::ITEM_HEALTH, maxhp);   // full heal
//
//  // God mode (per-frame): keep HP pinned to max and clear poison:
//      bilbo* b = bilbo_sdk::fn::GetBilbo();
//      bilbo_sdk::fn::Inv_Set(inv, bilbo_sdk::ITEM_HEALTH,
//                             bilbo_sdk::fn::Inv_GetMaxHealth(inv));
//      bilbo_sdk::fn::ResetPoison(b);
//
//  // Give an item (e.g. 99 stones, all coins):
//      bilbo_sdk::fn::Inv_Add(inv, bilbo_sdk::ITEM_STONES, 99.0f);
//      bilbo_sdk::fn::Inv_Set(inv, bilbo_sdk::ITEM_GOLD, 9999.0f);
//
//  // Force a state (e.g. instant ROPE_CLIMB / drop to IDLE / die):
//      bilbo_sdk::fn::ChangeStateTo(b, bilbo_sdk::BilboState::IDLE);
//      bilbo_sdk::fn::ChangeStateTo(b, bilbo_sdk::BilboState::DEATH);
//      // (the dispatcher applies it on the next State_Advance tick)
//
//  // Toggle the One Ring / invisibility instantly:
//      bilbo_sdk::fn::SetRingEquipped(b, /*equip=*/1, /*instant=*/1);
//
//  // Read player position / facing directly via offsets:
//      float& x   = bilbo_sdk::field<float>(b, bilbo_sdk::off::POS_X);
//      float& yaw = bilbo_sdk::field<float>(b, bilbo_sdk::off::FACING_YAW);
//
//  // Freeze input (cutscene-style) / restore:
//      bilbo_sdk::fn::SetInput(b, 0);   // disable
//      bilbo_sdk::fn::SetInput(b, 1);   // enable
//
//  // Infinite jump: force grounded + clear airborne each frame, or just
//  // call ChangeStateTo(JUMP) — but the cleanest is poking the velocity:
//      bilbo_sdk::field<float>(b, bilbo_sdk::off::VEL + 4) = 30.0f; // VEL_Y up
//
//  // Teleport-safe respawn (move to last checkpoint):
//      bilbo_sdk::fn::ResetToSafePos(b);
//
//  // Read current state name (for an on-screen overlay):
//      const char* name = bilbo_sdk::fn::State_GetName(
//          b, bilbo_sdk::field<bilbo_sdk::BilboState>(b, bilbo_sdk::off::CURRENT_STATE));
// ===========================================================================

} // namespace bilbo_sdk
