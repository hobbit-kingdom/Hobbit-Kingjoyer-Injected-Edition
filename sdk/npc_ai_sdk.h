// =============================================================================
// npc_ai_sdk.h  --  THE HOBBIT (2003, PC / Entropy engine, MSVC, 32-bit)
//
// Reverse-engineered SDK for the "npc_ai" subsystem: NPCObject / CharacterObject,
// the AIManager trigger/action/link graph, the StateController + AIState/AIGoal
// brain, SenseController perception, ConversationMgr, the Smaug boss states, and
// the camera_influence / level_lonelymountain neighbours that ride along.
//
// All addresses are PC retail VAs. Wrappers rebase through meridian::rebase()
// so the same header works against a relocated module load.
//
//   meridian::rebase(VA) -> actual in-process address of that VA.
//
// Calling conventions are taken from the demangled symbol table:
//   - virtual / member methods are __thiscall (this in ECX, args on stack)
//   - free functions are __cdecl
// Offsets in struct comments are byte offsets recovered from the decompiler.
// Types that were not recovered are forward-declared as opaque.
// =============================================================================
#pragma once
#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/radian3/..., xarray<T>, opaque engine types

// ---- primitive / engine aliases -------------------------------------------
typedef std::uint64_t Guid;     // 64-bit object handle (obj_mgr key)
typedef std::uint32_t u32;
typedef std::int32_t  s32;

// ---- opaque forward declarations (defined elsewhere in the engine) ---------
struct vector3;            // {float x,y,z}  (3 contiguous floats)
struct radian3;
struct plane;
struct property;           // ~0x258-byte editor property value (see layout below)
struct property_desc;      // 0x108-byte editor property descriptor (see below)
struct bin_in;             // binary import stream
struct text_in;            // text/INI import stream
struct bitstream;          // save-state writer
struct MessageInfo;
struct PainData;
struct anim_event;
class  xstring;            // {char* buffer @ +0; ...}  sizeof 0x2c
template <class T> struct xarray;  // (matches meridian_types.h)
class  object;
class  CharacterObject;
class  NPCObject;
class  AIManager;
class  AIAction;
class  AITrigger;
class  AIGoal;
class  StateController;
class  SenseController;
class  AIState;
class  char_anim_player;
class  anim_group;

// =============================================================================
//  property  --  the engine's fat tagged-variant used by every Get/SetProperty.
//  Recovered field offsets (the record is value-copied as ~0x21c bytes):
//    +0x000  int   type      // 1=int, 2=float, 3=bool, 4/0xd=string,
//                            // 0xc=enum, 0xf=object-ref, 0x10=character-ref,
//                            // 0x11=color
//    +0x008  char[0x200] stringValue   // inline string buffer (dword index 2)
//    +0x240  u32   guidLo / valueWord0 // object/vector low word (dword 0x90)
//    +0x244  u32   guidHi / valueWord1 // object/vector high word (dword 0x91)
//    +0x24c  int   intValue            // dword 0x93
//    +0x250  float floatValue          // dword 0x94
//    +0x254  int   boolValue / enum    // dword 0x95
// =============================================================================

// =============================================================================
//  property_desc  --  0x108-byte editor schema descriptor (xarray element).
//    +0x000  xstring name        // display/path name (set via 0x647d10)
//    +0x080  int  type           // tag (1 int,2 float,3 bool,4/0xd string,
//                                // 0xc enum,0xf objref,0x10 charref)
//    +0x084  int  subType/flags
//    +0x088  xstring  member     // sub-objects copy-constructed on grow
//    +0x0b8  void*    member
//    +0x0c0  vector3  member
//    +0x0d8  vector3  member
//    +0x0f8  float minValue      // 0x00800000 (FLT min) for float props
//    +0x0fc  float maxValue      // 0x7f7fffff (FLT_MAX) for float props
//    +0x100  int   refKind       // editor ref category: 0x1c npc, 0x2f volume,
//                                // 0x50 character, 0x23 navpoint, 0x11 cinema,
//                                // 0x35 trigger, 0x2d fxobject, 0x33 switch
//    +0x104  int   refFlag
//  sizeof(property_desc) == 0x108
// =============================================================================

// =============================================================================
//  xarray<property_desc>  --  growable descriptor list passed to Enumerate*().
//    +0x08 int count   +0x0c T* data   +0x10 int capacity   +0x18 int growHint
//  Standard MSVC reserve idiom: grow when capacity < count+1; element stride
//  is sizeof(T) (0x108 for property_desc, 0x2c for xstring).
// =============================================================================

// =============================================================================
//  obj_mgr global tables (used by every Guid->object resolve)
//    DAT_0076cd88 : int16[] guid-hash bucket heads, bucket =
//                   ((guidLo ^ guidHi) * -0xfb) & 0xfff
//    DAT_0076f648 : slot[] node array, stride 0x14; slot+8/+0xc = Guid lo/hi,
//                   slot+0xe = next-in-bucket link, (slot+0x7f & 0x10) = alive.
// =============================================================================

// =============================================================================
//  STRUCT LAYOUTS (recovered offsets)
// =============================================================================

// ---- object (engine base) --------------------------------------------------
struct object_layout {
	// +0x008  Guid     guid              // self handle
	// +0x044  vector3  position          // world pos (x@+44, y@+48, z@+4c)
	// +0x050  vector3  aabbMax            // bounding-box max (min@+44)
	// +0x07c  uint8    typeTag           // object class tag (0x11 cinema,
	//                                     // 0x12 Bilbo-class, 0x1c, 0x2f volume)
	// +0x07f  uint8    stateFlags        // bit0x10 = valid/alive
};

// ---- CharacterObject : object ---------------------------------------------
struct CharacterObject_layout {
	// +0x008  Guid   guid
	// +0x014  vector3 position           // alt position used by SolvePersonalSpace
	// +0x044  vector3 aabbMin            // +0x50 aabbMax (6-float AABB)
	// +0x07c  uint8  characterType       // eCharacterType (0x12 == Bilbo)
	// +0x0a8  void*  groundContactA      // contacted surface ref (lo)
	// +0x0ac  void*  groundContactB      // contacted surface ref (hi)
	// +0x0b1  uint8  surfaceFlags        // bit2 slippery, bit0x20 on-stairs
	// +0x0e0  u32    flags               // bit2 = category-dirty
	// +0x0e8  u32    charFlags
	// +0x0ec  float  height              // default 30.0
	// +0x0f0  s32    pendingActionHandle // -1 when none
	// +0x110  Guid   attachedEnemyGuid
	// +0x118  s32    detachCount
	// +0x11c  s32    field_11c           // default 2
	// +0x124  s32    polyCacheInvalidateTimer
	// +0x128  void*  movementController  // also conversation object slot
	// +0x130  void*  animControllerVtbl
	// +0x13c  s32    frameCount
	// +0x140  float  currentFrame
	// +0x19c  s32    animId / activeConversationId   // -1 invalid
	// +0x1a0  float  scale               // default 1.0
	// +0x1a4  s32    teamId              // 0 = neutral (faction id)
	// +0x248  vector3 personalSpacePush  // SolvePersonalSpace output
};

// ---- NPCObject : CharacterObject ------------------------------------------
struct NPCObject_layout {
	// +0x040  s32    logicState          // ==2 gates a sub-update
	// +0x04c  u32    logicFlags          // bits 0x4 / 0x1000 / 0x200000
	// +0x0bc  void*  aiController         // vtbl+0x24/+0x40/+0x60 dispatch
	// +0x0d4  float  moveSpeed
	// +0x130  u32    stateFlags          // bit0x1000 retaliation gate
	// +0x158  void*  subController        // flags +0x78 bit0x8000
	// +0x180  MessageInfo* pendingAttackerMsg (+0x184 hi)
	// +0x1a4  s32    teamId
	// +0x1b0  s32    npcTypeId           // type/class id; boss set
	//                                    // {0x36,0x3a,0x3b,0x3c,0x41};
	//                                    // firefly 0x47, wisp 0x4e
	// +0x20c  s32    hitCounter   (+0x210 aux)
	// +0x260  void*  heldProp / shieldRecord  // record+8 = prop Guid
	// +0x264  s32    conversationNestCount
	// +0x268  u32    npcFlags            // bit0x1 restore-AI, bit0x10 alive,
	//                                    // bit0x20 doSenses, bit0x80 rooted,
	//                                    // bit0x2000 cansleep, bit0x10000 fx-pending,
	//                                    // bit0x20000 dead, bit0x80000 asleep,
	//                                    // bit0x2000000 drawHealthMeter
	// +0x26c  s32    resourceHandle      // -1 sentinel
	// +0x270  s32    deathTimerMax        // 0x7fffffff init
	// +0x278  Guid   deathCinemaGuid
	// +0x280  float  health
	// +0x288  Guid   targetGuid   (+0x290 cachedTarget object*)
	// +0x29c  float  deathTimer
	// +0x2a8  char*  deathFxName
	// +0x2d4  u32    deathSoundMsgId
	// +0x300  StateController* controller  // brain; +0x138 conversation map
	// +0x304  NPCObject* eventTarget
	// +0x308  void*  config              // +0x24 leash radius
	// +0x310  StateController stateController (embedded subobject)
	// +0x45c  float  deltaTime
	// +0x460  float  sleepTimer  (+0x464/+0x468 spawn timers)
	// +0x478  u32    hudFlags            // bit0x20 boss health-meter visible,
	//                                    // bit0x10 cinema-started, bit0x40 force-die
};

// ---- AIManager : object ----------------------------------------------------
struct AIManager_layout {
	// +0x010 int triggerCount  +0x014 AITrigger** triggers  +0x018 int triggerCap
	// +0x02c int actionCount   +0x030 AIAction**  actions   +0x034 int actionCap
	// +0x03c void* linkClassBlock  // script symbol header (counts @ +0x10/+0x12/+0x14)
	// +0x040 void* linkClassArray  (stride 0xc)
	// +0x044 void* linkMethodArray (stride 8)
	// +0x048 int linkCount      +0x04c AILink** links     +0x050 int linkCap
	//                            (also linkFieldArray for VerifyLinks)
	// +0x060 char* stringPool    // script symbol-name base
	// +0x0b0 s32  filterType     // editor filter
	// +0x0b8 Guid filterObject
};

// ---- AILink ----------------------------------------------------------------
struct AILink_layout {
	// +0x08 s32   state         // 0/2 open, 1/3 closed
	// +0x10 char* name          // link name (compared by SetLinkState)
	// +0x70 int   triggerCount  +0x74 ... action arrays (MakeLinkName)
};

// ---- AITrigger (base + common subclass field cluster) ----------------------
struct AITrigger_layout {
	// +0x04  s32  triggerIndex  // %d in 'AIManager\Triggers\Trigger %d\...'
	// +0x08  u32  stateFlags    // bit0 IsTriggered, bit1 StaysTrueOnceTriggered,
	//                           // bit2 TriggersOnValue (was-triggered marking)
	// +0x0c  s32  goldAmount / applyToAllNPCs
	// +0x10  Guid primaryGuid   // Character/NPC/Chest/Switch/Cinema/Web/...
	// +0x14  int  npcCount      // for list triggers (array @ +0x18, stride 8)
	// +0x18  Guid secondaryGuid / npcList* / volume
	// +0x20  s32  triggersOnce / senseFlags (bit0 Smell, bit1 Sight, ...)
	// +0x24  s32  alreadyFiredLatch
	// +0x4c  s32  painType      // TriggerCharacterDamagesCharacter
};

// ---- AIAction (base + common subclass field cluster) -----------------------
struct AIAction_layout {
	// +0x04  s32   actionIndex  // %d in 'AIManager\Actions\Action %d\...'
	// +0x08  s32   timesTriggered
	// +0x0c  s32   currentExecuteDelay
	// +0x10  float executeDelay  // also reused as char* section name (boss/behavior subclasses)
	// +0x14  u32   flags         // bit0 executeImmediately; bit1 expose-debug
	// +0x18  varies firstField   // first bound prop (guid lo / bool / float)
	// +0x20  varies secondField  // NPC guid / int / second bound prop
	// +0x44  s32   amount / linkState
	// +0x48  u32*  listBuffer / cinemaGuids (8-byte elements; count/cap nearby)
};

// ---- AIGoal ----------------------------------------------------------------
struct AIGoal_layout {
	// +0x04  u32  flags          // bit1 MustSucceed
	// +0x10  Guid target
	// +0x2c  s32  animType / speedToken
	// +0x30  xstring animName
	// +0x54  float playTime
	// +0x5c  u32  lockToPositionFlags  (bit0 Lock, bit1 LookAhead in GoalGotoTarget)
};

// ---- SenseController -------------------------------------------------------
struct SenseController_layout {
	// +0x08  Guid  soundObjectGuid    // lazily created (type 0x2f) listener
	// +0x18  u32   flags              // bit2 DoLOS, bit3(0x10) can-sense gate
	// +0x1c  float sightRange
	// +0x24  float hearingRange / innerSenseRadius
	// +0x28  float loudHearingRange / outerSenseRadius
	// +0x30  float smellRange
	// +0x38  Guid  sensedTargetGuid   // best-guess / bilbo
	// +0x40  Guid  ownerGuid          // resolved via obj_mgr by SetBlind
	// +0x48  object* cachedOwner
	// +0x5958 vector3 lastStimulus  +0x5970 float stimulusIntensity
};

// ---- AIState ---------------------------------------------------------------
struct AIState_layout {
	// +0x00  void** vtable    // +0xc IsDone, +0x10 Update, +0x1c GetPhaseName
	// +0x08  StateController* owner
	// +0x0c  float elapsedTime
	// +0x42  int16 phase      // 0 Unknown, 1 DEFENDING, 2 'Doing a goal list'
	// +0x45  uint8 phaseId    // 1..8
};

// ---- SmaugAttackState (boss) ----------------------------------------------
struct SmaugAttackState_layout {
	// +0x0a0  vector3 mouthTarget
	// +0x0b8  vector3 originRef / fireStrandPos
	// +0x148  FireBreathZone[] safety zones (stride 0xC8)
	// +0x578  int blockerCount   +0x57c void** blockerArray (stride 4)
	// +0x58c  int activeBlockerIndex
	// +0x5b4  int firePointCount +0x5b8 vector3* firePoints (stride 0xc)
	// blocker record: +0x00/+0x08 rigid guids, +0x10 ui guid, +0x18 flags(bit0x10),
	//                 +0x24 timer
};

// ---- SmaugAlertState (boss; embeds path + message scratch) -----------------
struct SmaugAlertState_layout {
	// +0x42  int16 phaseFlag    // ==7 fast path
	// +0x48  float moveSpeed    +0x4c owner/approach +0x50/0x54 target xy
	// +0x58  int   stateCounter
	// +0x64  float aimBias      +0x98 vector3 eyeAimTarget +0x120 sleepAnimCycle
	// +0x118 int pathCount  +0x11c void* pathBuffer  +0x120 cap  +0x124 owned
	// +0x130 u32 stateFlags (0x40 moving, 0x100 path-valid) +0x134 moveMode
};

// ---- ConversationMgr -------------------------------------------------------
struct ConversationMgr_layout {
	// +0x4c  int conversationCount   +0x54 int conversationCapacity
	// conversation record sizeof 0xa0 (3 embedded sub-lists)
};

// ---- camera_influence : object ---------------------------------------------
struct camera_influence_layout {
	// +0xac always-active flag  +0xb0 volume-required  +0xb4 trigger-once
	// +0xc0/0xc4 floats  +0xc8 Guid  +0xd0 float Delay
	// +0xe8 timingState  +0xf0 Guid lookatTarget  +0xf8 lastTriggeredResult
};

// ---- level_lonelymountain (level-specific puzzle driver) -------------------
struct level_lonelymountain_layout {
	// +0x108 tile_puzzle  +0x178 forge_puzzle  +0x270 lonely_mountain_fx
	// +0x2a0 Guid[4] triggerGuids  +0x2d8 water_puzzle  +0xc18 water_puzzle
	// +0x1560 gearRoomObjectGuid  +0x1568/0x1570 cinema guids
	// +0x1578 chainTriggerGuid  +0x15a0 puzzleObjectGuid  +0x15f8 cableSound
	// +0x1630 levelStateFlags  (bit0x20 bellows, 0x40 cooler, 0x80 gearRoom,
	//         0x100 treasury, 0x8000 cinemaShown, 0x20000 secretDoors,
	//         0x100000/0x200000 quest-complete latches)
	// +0x163c int[] secretDoorFiredLatch   +0x164c int[] secretCanalActive
};

// =============================================================================
//  TYPED FUNCTION-POINTER WRAPPERS  (group: meridian / Main.cpp globals)
// =============================================================================
namespace npc_ai {

	// ---- Application / level lifecycle (Main.cpp) ------------------------------
	inline void   AppBegin(void* p) { reinterpret_cast<void(__cdecl*)(void*)>(meridian::rebase(0x004fd7c0))(p); }
	inline int    LoadLevel() { return reinterpret_cast<int(__cdecl*)()>(meridian::rebase(0x004fe5a0))(); }
	inline void   UnloadLevel() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x004fedc0))(); }
	inline void   RunLevel() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x004fee90))(); }
	inline int    RunFrontEnd() { return reinterpret_cast<int(__cdecl*)()>(meridian::rebase(0x004fe3e0))(); }
	inline void   Render() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x004ff0a0))(); }
	inline void   Kill_App() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x004fe1b0))(); }
	inline void   GameCoreKill() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x004fe2a0))(); }
	inline void   PreloadResources() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x004fd2b0))(); }
	inline void   SetupRootDirectories(char const* root) { reinterpret_cast<void(__cdecl*)(char const*)>(meridian::rebase(0x004fce90))(root); }
	inline void   SetBilboCombatLevels() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x004fec70))(); }
	inline void   CacheNextLevel() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x0052ac30))(); }

	// =============================================================================
	//  NPCObject  --  the per-creature AI/render entity (extends CharacterObject)
	// =============================================================================
	inline NPCObject* NPCObject_ctor(NPCObject* self) { return reinterpret_cast<NPCObject * (__thiscall*)(NPCObject*)>(meridian::rebase(0x0049eff0))(self); }
	inline void   NPCObject_LoadCharacterData(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x0049f8f0))(self); }
	inline void   NPCObject_OnImport(NPCObject* self, bin_in* in) { reinterpret_cast<void(__thiscall*)(NPCObject*, bin_in*)>(meridian::rebase(0x004a5a70))(self, in); }
	inline void   NPCObject_OnAdvanceLogic(NPCObject* self, float dt) { reinterpret_cast<void(__thiscall*)(NPCObject*, float)>(meridian::rebase(0x004a14c0))(self, dt); }
	inline void   NPCObject_AdvanceFullUpdate(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1750))(self); }
	inline void   NPCObject_AdvanceEventProcessing(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x00594be0))(self); }
	inline void   NPCObject_AdvanceSleep(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1ad0))(self); }
	inline void   NPCObject_AdvanceHealthMeter(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1e50))(self); }
	inline void   NPCObject_AdvanceDeathTimer(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1c30))(self); }
	inline void   NPCObject_UpdateProps(NPCObject* self, int slot) { reinterpret_cast<void(__thiscall*)(NPCObject*, int)>(meridian::rebase(0x004a29b0))(self, slot); }
	inline void   NPCObject_SetProp(NPCObject* self, int propType, xstring name) { reinterpret_cast<void(__thiscall*)(NPCObject*, int, xstring)>(meridian::rebase(0x0049fee0))(self, propType, name); }
	inline void   NPCObject_TakeDamage(NPCObject* self, Guid attacker, PainData* pd) { reinterpret_cast<void(__thiscall*)(NPCObject*, Guid, PainData*)>(meridian::rebase(0x004a5130))(self, attacker, pd); }
	inline int    NPCObject_OnApplyPain(NPCObject* self, Guid att, vector3 const* at, float a, float b, float c, float d, int painType, int e) { return reinterpret_cast<int(__thiscall*)(NPCObject*, Guid, vector3 const*, float, float, float, float, int, int)>(meridian::rebase(0x004a4610))(self, att, at, a, b, c, d, painType, e); }
	inline void   NPCObject_Die(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a58a0))(self); }
	inline void   NPCObject_DieScumDie(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a69a0))(self); }
	inline void   NPCObject_GotoSleep(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a22a0))(self); }
	inline void   NPCObject_ShatterShield(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a40d0))(self); }
	inline void   NPCObject_OnObjectActivate(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x0049f480))(self); }
	inline void   NPCObject_OnObjectDeactivate(NPCObject* self) { reinterpret_cast<void(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a9870))(self); }
	inline int    NPCObject_HandleMessage(NPCObject* self, MessageInfo* m) { return reinterpret_cast<int(__thiscall*)(NPCObject*, MessageInfo*)>(meridian::rebase(0x005aead0))(self, m); }
	inline void   NPCObject_EndConversationMode(NPCObject* self, int restoreAI) { reinterpret_cast<void(__thiscall*)(NPCObject*, int)>(meridian::rebase(0x004a13d0))(self, restoreAI); }
	inline void   NPCObject_SetIsRooted(NPCObject* self, int rooted, int anchor) { reinterpret_cast<void(__thiscall*)(NPCObject*, int, int)>(meridian::rebase(0x004a5790))(self, rooted, anchor); }
	inline void   NPCObject_SetDrawHealthMeter(NPCObject* self, int on) { reinterpret_cast<void(__thiscall*)(NPCObject*, int)>(meridian::rebase(0x004a9960))(self, on); }
	inline int    NPCObject_GetDoSenses(NPCObject* self) { return reinterpret_cast<int(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1060))(self); }
	inline float  NPCObject_GetHitPoints(NPCObject* self) { return reinterpret_cast<float(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a4130))(self); }
	inline int    NPCObject_IsBoss(NPCObject* self) { return reinterpret_cast<int(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a2340))(self); }
	inline int    NPCObject_IsTargetable(NPCObject* self) { return reinterpret_cast<int(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a2300))(self); }
	inline int    NPCObject_HasConversation(NPCObject* self) { return reinterpret_cast<int(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1210))(self); }
	inline int    NPCObject_HasCinema(NPCObject* self) { return reinterpret_cast<int(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1240))(self); }
	inline Guid   NPCObject_GetCinema(NPCObject* self) { return reinterpret_cast<Guid(__thiscall*)(NPCObject*)>(meridian::rebase(0x004a1230))(self); }
	inline Guid   NPCObject_GetAITarget(NPCObject* self) { return reinterpret_cast<Guid(__thiscall*)(NPCObject*)>(meridian::rebase(0x005b6f40))(self); }
	inline property NPCObject_GetProperty(NPCObject* self, property* out, char const* name) { return reinterpret_cast<property(__thiscall*)(NPCObject*, property*, char const*)>(meridian::rebase(0x004a8190))(self, out, name); }

	// =============================================================================
	//  CharacterObject  --  shared movement / animation / faction base
	// =============================================================================
	inline CharacterObject* CharacterObject_ctor(CharacterObject* self) { return reinterpret_cast<CharacterObject * (__thiscall*)(CharacterObject*)>(meridian::rebase(0x00464130))(self); }
	inline void   CharacterObject_OnAdvanceLogic(CharacterObject* self, float dt) { reinterpret_cast<void(__thiscall*)(CharacterObject*, float)>(meridian::rebase(0x00467ed0))(self, dt); }
	inline void   CharacterObject_HandleMove(CharacterObject* self, vector3* out, vector3 const* delta, float a, float b, int mode, int c, int d) { reinterpret_cast<void(__thiscall*)(CharacterObject*, vector3*, vector3 const*, float, float, int, int, int)>(meridian::rebase(0x00469060))(self, out, delta, a, b, mode, c, d); }
	inline void   CharacterObject_SolvePersonalSpace(CharacterObject* self, vector3* io) { reinterpret_cast<void(__thiscall*)(CharacterObject*, vector3*)>(meridian::rebase(0x004688e0))(self, io); }
	inline int    CharacterObject_IsEnemy(CharacterObject* self, CharacterObject* other) { return reinterpret_cast<int(__thiscall*)(CharacterObject*, CharacterObject*)>(meridian::rebase(0x004683d0))(self, other); }
	inline int    CharacterObject_IsOnStairs(CharacterObject* self) { return reinterpret_cast<int(__thiscall*)(CharacterObject*)>(meridian::rebase(0x00467e90))(self); }
	inline int    CharacterObject_IsGroundSlippery(CharacterObject* self) { return reinterpret_cast<int(__thiscall*)(CharacterObject*)>(meridian::rebase(0x00467eb0))(self); }
	inline int    CharacterObject_ProcessPolyCacheInvalidate(CharacterObject* self) { return reinterpret_cast<int(__thiscall*)(CharacterObject*)>(meridian::rebase(0x004698c0))(self); }
	inline anim_group const* CharacterObject_GetAnimGroup(CharacterObject* self) { return reinterpret_cast<anim_group const* (__thiscall*)(CharacterObject*)>(meridian::rebase(0x00469860))(self); }
	inline void   CharacterObject_ApplyEffectToBones(CharacterObject* self, char const* fx) { reinterpret_cast<void(__thiscall*)(CharacterObject*, char const*)>(meridian::rebase(0x00467710))(self, fx); }
	inline void   CharacterObject_EndTalking(CharacterObject* self) { reinterpret_cast<void(__thiscall*)(CharacterObject*)>(meridian::rebase(0x00467e40))(self); }
	inline void   CharacterObject_EndConversationMode(CharacterObject* self, int x) { reinterpret_cast<void(__thiscall*)(CharacterObject*, int)>(meridian::rebase(0x00468250))(self, x); }
	inline Guid   CharacterObject_GetAttachedEnemy(CharacterObject* self) { return reinterpret_cast<Guid(__thiscall*)(CharacterObject*)>(meridian::rebase(0x00468420))(self); }
	inline void   CharacterObject_SetAttachedEnemy(CharacterObject* self, Guid g) { reinterpret_cast<void(__thiscall*)(CharacterObject*, Guid)>(meridian::rebase(0x00468430))(self, g); }
	inline void   CharacterObject_IncrementDetachCount(CharacterObject* self) { reinterpret_cast<void(__thiscall*)(CharacterObject*)>(meridian::rebase(0x00468410))(self); }
	// statics: type-name <-> id map (built once)
	inline void   CharacterObject_SetupTypeNameArray() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x00464560))(); }
	inline xstring CharacterObject_GetCharacterNameFromType(int t) { xstring r; reinterpret_cast<xstring* (__cdecl*)(xstring*, int)>(meridian::rebase(0x004675a0))(&r, t); return r; }
	inline int    CharacterObject_GetCharacterTypeFromName(xstring n) { return reinterpret_cast<int(__cdecl*)(xstring)>(meridian::rebase(0x00467620))(n); }

	// =============================================================================
	//  AIManager  --  the level's trigger/action/link graph (object subclass)
	// =============================================================================
	// NOTE: AIManager::AIManager ctor VA was not isolated in this pass; construct via the engine.
	inline void   AIManager_OnImport(AIManager* self, bin_in* in) { reinterpret_cast<void(__thiscall*)(AIManager*, bin_in*)>(meridian::rebase(0x00562900))(self, in); }
	// 0x0055e1c0 = AIManager::ActionFiltered (a factory-dispatch over action-type ids; verify vs CreateAction).
	inline void   AIManager_EnumerateProperties(AIManager* self, xarray<property_desc>& out) { reinterpret_cast<void(__thiscall*)(AIManager*, xarray<property_desc>&)>(meridian::rebase(0x00563550))(self, out); }
	inline int    AIManager_SetProperty(AIManager* self, char const* name, property const* v) { return reinterpret_cast<int(__thiscall*)(AIManager*, char const*, property const*)>(meridian::rebase(0x00564940))(self, name, v); }
	inline property AIManager_GetProperty(AIManager* self, property* out, char const* name) { return reinterpret_cast<property(__thiscall*)(AIManager*, property*, char const*)>(meridian::rebase(0x005657a0))(self, out, name); }
	inline void   AIManager_SetupActionList(AIManager* self) { reinterpret_cast<void(__thiscall*)(AIManager*)>(meridian::rebase(0x0055f050))(self); }
	inline void   AIManager_SetupTriggerList(AIManager* self) { reinterpret_cast<void(__thiscall*)(AIManager*)>(meridian::rebase(0x005605e0))(self); }
	inline void   AIManager_SetLinkState(AIManager* self, char const* link, int state) { reinterpret_cast<void(__thiscall*)(AIManager*, char const*, int)>(meridian::rebase(0x0055d360))(self, link, state); } // PROPOSED
	inline int    AIManager_VerifyLinks(AIManager* self) { return reinterpret_cast<int(__thiscall*)(AIManager*)>(meridian::rebase(0x006457f0))(self); } // PROPOSED
	inline void* AIManager_CreateAction(int type, void* arg) { return reinterpret_cast<void* (__cdecl*)(int, void*)>(meridian::rebase(0x0055d520))(type, arg); } // PROPOSED factory
	inline int    YankFirstNumber(char const* s) { return reinterpret_cast<int(__cdecl*)(char const*)>(meridian::rebase(0x005648f0))(s); } // PROPOSED

	// =============================================================================
	//  AIAction base  --  property/serialization contract shared by all actions
	// =============================================================================
	inline int      AIAction_SetProperty(AIAction* self, char const* name, property const* v) { return reinterpret_cast<int(__thiscall*)(AIAction*, char const*, property const*)>(meridian::rebase(0x005ccb60))(self, name, v); } // PROPOSED base
	inline property* AIAction_GetProperty(AIAction* self, property* out, char const* name) { return reinterpret_cast<property * (__thiscall*)(AIAction*, property*, char const*)>(meridian::rebase(0x005ccdb0))(self, out, name); } // PROPOSED base
	inline void     AIAction_EnumerateSaveProperties(AIAction* self, xarray<property_desc>& o) { reinterpret_cast<void(__thiscall*)(AIAction*, xarray<property_desc>&)>(meridian::rebase(0x005bf5e0))(self, o); } // PROPOSED base
	inline void     AIAction_EnumerateSavePropsBase(AIAction* self) { reinterpret_cast<void(__thiscall*)(AIAction*)>(meridian::rebase(0x005cc820))(self); } // EnumerateSaveProperties (ExecuteDelay/ExecuteImmediately)
	inline void     AIAction_EnumerateProperties(AIAction* self, xarray<property_desc>& o) { reinterpret_cast<void(__thiscall*)(AIAction*, xarray<property_desc>&)>(meridian::rebase(0x005cd4c0))(self, o); }
	// Representative concrete actions (Execute / SetProperty / OnImport):
	inline void   ActionSetGoalList_Execute(AIAction* self) { reinterpret_cast<void(__thiscall*)(AIAction*)>(meridian::rebase(0x005d08a0))(self); }
	inline void   ActionSetInventory_Execute(AIAction* self) { reinterpret_cast<void(__thiscall*)(AIAction*)>(meridian::rebase(0x005d3c10))(self); }
	inline void   ActionInfoOverlay_Execute(AIAction* self) { reinterpret_cast<void(__thiscall*)(AIAction*)>(meridian::rebase(0x005dbfa0))(self); }
	inline void   ActionGiveBilboQuest_Execute(AIAction* self) { reinterpret_cast<void(__thiscall*)(AIAction*)>(meridian::rebase(0x005df070))(self); }
	inline void   ActionMoveObject_Execute(AIAction* self) { reinterpret_cast<void(__thiscall*)(AIAction*)>(meridian::rebase(0x005d9430))(self); }
	inline void   ActionTriggerSwitch_OnImport(AIAction* self, bin_in* in) { reinterpret_cast<void(__thiscall*)(AIAction*, bin_in*)>(meridian::rebase(0x005cd850))(self, in); }
	inline void   ActionSpawnNPC_OnImport(AIAction* self, bin_in* in) { reinterpret_cast<void(__thiscall*)(AIAction*, bin_in*)>(meridian::rebase(0x005d5950))(self, in); }

	// =============================================================================
	//  AITrigger base  --  condition/property contract shared by all triggers
	// =============================================================================
	inline int      AITrigger_SetProperty(AITrigger* self, char const* name, property const* v) { return reinterpret_cast<int(__thiscall*)(AITrigger*, char const*, property const*)>(meridian::rebase(0x005f17e0))(self, name, v); } // PROPOSED base
	inline property* AITrigger_GetProperty(AITrigger* self, property* out, char const* name) { return reinterpret_cast<property * (__thiscall*)(AITrigger*, property*, char const*)>(meridian::rebase(0x005f19b0))(self, out, name); } // PROPOSED base
	inline void     AITrigger_EnumerateSaveProperties(AITrigger* self, xarray<property_desc>& o) { reinterpret_cast<void(__thiscall*)(AITrigger*, xarray<property_desc>&)>(meridian::rebase(0x005f1470))(self, o); } // PROPOSED base
	inline void     AITrigger_OnImport(AITrigger* self, bin_in* in) { reinterpret_cast<void(__thiscall*)(AITrigger*, bin_in*)>(meridian::rebase(0x005f1e70))(self, in); }
	inline int      AITrigger_SetPropertyBit(AITrigger* self, char const* name, property const* v) { return reinterpret_cast<int(__thiscall*)(AITrigger*, char const*, property const*)>(meridian::rebase(0x005f1cf0))(self, name, v); } // AITrigger::SetProperty (StaysTrue/TriggeredOnTrue)

	// =============================================================================
	//  AIGoal / AIState / StateController  --  the per-NPC behaviour brain
	// =============================================================================
	inline int    AIGoal_SetProperty(AIGoal* self, char const* name, property const* v, int listIdx, int goalIdx) { return reinterpret_cast<int(__thiscall*)(AIGoal*, char const*, property const*, int, int)>(meridian::rebase(0x00567310))(self, name, v, listIdx, goalIdx); } // PROPOSED
	inline void   AIGoal_OnImport(AIGoal* self, int listIdx, int goalIdx) { reinterpret_cast<void(__thiscall*)(AIGoal*, int, int)>(meridian::rebase(0x00566fe0))(self, listIdx, goalIdx); } // PROPOSED
	inline void   GoalGotoTarget_OnImport(AIGoal* self, bin_in* in, int listIdx, int goalIdx) { reinterpret_cast<void(__thiscall*)(AIGoal*, bin_in*, int, int)>(meridian::rebase(0x00568690))(self, in, listIdx, goalIdx); }
	inline void   AIState_OnTick(AIState* self, float dt) { reinterpret_cast<void(__thiscall*)(AIState*, float)>(meridian::rebase(0x005be280))(self, dt); } // PROPOSED
	inline char const* AIState_GetStateDescription(AIState* self) { return reinterpret_cast<char const* (__thiscall*)(AIState*)>(meridian::rebase(0x005bec40))(self); } // CalcFlinchType body == phase->name mapper
	inline void   StateController_UpdateDesiredState(StateController* self) { reinterpret_cast<void(__thiscall*)(StateController*)>(meridian::rebase(0x005ad140))(self); } // PROPOSED
	inline void* StateController_AcquireMessage(StateController* self, int bucket) { return reinterpret_cast<void* (__thiscall*)(StateController*, int)>(meridian::rebase(0x00567b20))(self, bucket); } // PROPOSED
	inline void   StateController_QueueAction(StateController* self, void* action) { reinterpret_cast<void(__thiscall*)(StateController*, void*)>(meridian::rebase(0x005af9f0))(self, action); } // PROPOSED

	// =============================================================================
	//  SenseController  --  per-NPC perception (sight / hearing / smell)
	// =============================================================================
	inline void   SenseController_SetBlind(SenseController* self, int blind) { reinterpret_cast<void(__thiscall*)(SenseController*, int)>(meridian::rebase(0x005aa750))(self, blind); }
	inline int    SenseController_CanSmell(SenseController* self, Guid target, int enemyOnly) { return reinterpret_cast<int(__thiscall*)(SenseController*, Guid, int)>(meridian::rebase(0x005ab3f0))(self, target, enemyOnly); }
	inline int    SenseController_CanHear(SenseController* self, Guid target, int enemyOnly) { return reinterpret_cast<int(__thiscall*)(SenseController*, Guid, int)>(meridian::rebase(0x005ab710))(self, target, enemyOnly); }
	inline int    SenseController_CanHearLoud(SenseController* self, Guid target, int enemyOnly) { return reinterpret_cast<int(__thiscall*)(SenseController*, Guid, int)>(meridian::rebase(0x005ab600))(self, target, enemyOnly); }
	inline int    SenseController_IsAbleToSense(SenseController* self, Guid target, int x) { return reinterpret_cast<int(__thiscall*)(SenseController*, Guid, int)>(meridian::rebase(0x005aa880))(self, target, x); }
	inline int    SenseController_CanSense(SenseController* self, Guid target, int senseMask) { return reinterpret_cast<int(__thiscall*)(SenseController*, Guid, int)>(meridian::rebase(0x005aa910))(self, target, senseMask); } // PROPOSED (OR-of-senses)
	inline void   SenseController_UpdateBestGuess(SenseController* self, NPCObject* owner) { reinterpret_cast<void(__thiscall*)(SenseController*, NPCObject*)>(meridian::rebase(0x005aae10))(self, owner); } // body == UpdateBestGuess (recovered 'SoundEvent' was wrong)
	inline void   SenseController_UpdateSensedArray(SenseController* self, float dt) { reinterpret_cast<void(__thiscall*)(SenseController*, float)>(meridian::rebase(0x005aaad0))(self, dt); } // PROPOSED
	inline int    SenseController_SetProperty(SenseController* self, char const* name, property const* v) { return reinterpret_cast<int(__thiscall*)(SenseController*, char const*, property const*)>(meridian::rebase(0x005abcd0))(self, name, v); } // body == SetProperty (recovered 'CanSee' was wrong)
	inline int    SenseController_HasActiveStimulus(SenseController* self) { return reinterpret_cast<int(__thiscall*)(SenseController*)>(meridian::rebase(0x00420fe0))(self); } // PROPOSED

	// =============================================================================
	//  Smaug boss states (SmaugIdleState / SmaugAlertState / SmaugAttackState)
	// =============================================================================
	inline void   SmaugIdleState_UpdateTail(void* self, float dt) { reinterpret_cast<void(__thiscall*)(void*, float)>(meridian::rebase(0x005ba910))(self, dt); }
	inline void   SmaugAlertState_UpdateTail(void* self, float dt) { reinterpret_cast<void(__thiscall*)(void*, float)>(meridian::rebase(0x005bd7d0))(self, dt); }
	inline void   SmaugAlertState_BlendAnimsToTarget(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x005bafa0))(self); }
	inline int    SmaugAlertState_SetProperty(void* self, char const* name, property const* v) { return reinterpret_cast<int(__thiscall*)(void*, char const*, property const*)>(meridian::rebase(0x005ba860))(self, name, v); }
	inline void   SmaugAlertState_HandleEvent(void* self, int eventId) { reinterpret_cast<void(__thiscall*)(void*, int)>(meridian::rebase(0x00631e90))(self, eventId); } // PROPOSED
	inline void   SmaugAttackState_InitFireFx(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x006197d0))(self); }
	inline void   SmaugAttackState_UpdateBlockers(void* self, float dt) { reinterpret_cast<void(__thiscall*)(void*, float)>(meridian::rebase(0x006193c0))(self, dt); }
	inline void   SmaugAttackState_UpdateFireStrands(void* self, float dt) { reinterpret_cast<void(__thiscall*)(void*, float)>(meridian::rebase(0x00618b50))(self, dt); }
	inline int    SmaugAttackState_CheckBilboForSafety(void* self) { return reinterpret_cast<int(__thiscall*)(void*)>(meridian::rebase(0x00619660))(self); }
	inline void   SmaugAttackState_DebugRender(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x00617880))(self); }
	inline void   SmaugAttackState_SetSafetyZoneCount(void* self, unsigned int n) { reinterpret_cast<void(__thiscall*)(void*, unsigned int)>(meridian::rebase(0x006140f0))(self, n); } // REAL API name (not UpdateFireBreathZone)
	inline void   SmaugAttackState_ResetBlockerAnims(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x00618cd0))(self); } // body == UpdateHeadPosition slot; resets blocker anims

	// =============================================================================
	//  ConversationMgr  --  dialog/conversation database
	// =============================================================================
	inline void   ConversationMgr_OnImport(ConversationMgr_layout* self, bin_in* in) { reinterpret_cast<void(__thiscall*)(void*, bin_in*)>(meridian::rebase(0x0059d750))(self, in); }
	inline int    ConversationMgr_SetProperty(void* self, char const* name, property const* v) { return reinterpret_cast<int(__thiscall*)(void*, char const*, property const*)>(meridian::rebase(0x0059ed80))(self, name, v); }
	inline property ConversationMgr_GetProperty(void* self, property* out, char const* name) { return reinterpret_cast<property(__thiscall*)(void*, property*, char const*)>(meridian::rebase(0x005a0fa0))(self, out, name); }
	inline xarray<xstring>* ConversationMgr_GetConversationNames() { return reinterpret_cast<xarray<xstring>*(__cdecl*)()>(meridian::rebase(0x0059d060))(); } // PROPOSED

	// =============================================================================
	//  PainData  --  damage-type table (static helpers)
	// =============================================================================
	inline void   PainData_InitializeNames() { reinterpret_cast<void(__cdecl*)()>(meridian::rebase(0x005b8b20))(); }

	// =============================================================================
	//  camera_influence  --  scripted camera trigger volumes
	// =============================================================================
	inline void   camera_influence_OnImport(void* self, bin_in* in) { reinterpret_cast<void(__thiscall*)(void*, bin_in*)>(meridian::rebase(0x0045d350))(self, in); }
	inline int    camera_influence_IsTriggered(void* self, Guid target) { return reinterpret_cast<int(__thiscall*)(void*, Guid)>(meridian::rebase(0x0045d610))(self, target); }
	inline void   camera_influence_EnumerateProperties(void* self, xarray<property_desc>& o) { reinterpret_cast<void(__thiscall*)(void*, xarray<property_desc>&)>(meridian::rebase(0x0045da80))(self, o); }

	// =============================================================================
	//  level_lonelymountain  --  level-specific puzzle/FX driver (neighbour)
	// =============================================================================
	inline void   LonelyMtn_AdvanceLogic(void* self, float dt) { reinterpret_cast<void(__thiscall*)(void*, float)>(meridian::rebase(0x0040c130))(self, dt); }
	inline void   LonelyMtn_AdvanceTreasuryPuzzle(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x0040d560))(self); }
	inline void   LonelyMtn_TurnRoomsOnOff(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x0040cca0))(self); }
	inline void   LonelyMtn_SaveState(void* self, bitstream* bs) { reinterpret_cast<void(__thiscall*)(void*, bitstream*)>(meridian::rebase(0x0040c680))(self, bs); }
	inline void   LonelyMtn_SetForgeBellowsActive(void* self, int on) { reinterpret_cast<void(__thiscall*)(void*, int)>(meridian::rebase(0x0040ce00))(self, on); }
	inline void   LonelyMtn_SetForgeWaterActive(void* self, int on) { reinterpret_cast<void(__thiscall*)(void*, int)>(meridian::rebase(0x0040cfa0))(self, on); }
	inline void   LonelyMtn_SetGearRoomActive(void* self, int on) { reinterpret_cast<void(__thiscall*)(void*, int)>(meridian::rebase(0x0040d0e0))(self, on); }
	inline void   LonelyMtn_SetTreasuryActive(void* self, int on) { reinterpret_cast<void(__thiscall*)(void*, int)>(meridian::rebase(0x0040d400))(self, on); }
	inline void   LonelyMtn_SetSecretCanalActive(void* self, int idx, int on) { reinterpret_cast<void(__thiscall*)(void*, int, int)>(meridian::rebase(0x0040d310))(self, idx, on); }
	inline void   LonelyMtn_SetSecretWaterDoorsActive(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x0040d3a0))(self); }
	inline void   StartGondolas(int start) { reinterpret_cast<void(__cdecl*)(int)>(meridian::rebase(0x0040c5e0))(start); }
	inline void   LonelyMtnFx_Init(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x0040e080))(self); }
	inline void   LonelyMtnFx_AdvanceLogic(void* self, float dt) { reinterpret_cast<void(__thiscall*)(void*, float)>(meridian::rebase(0x0040e1f0))(self, dt); }
	inline void   LonelyMtnFx_IgniteForge(void* self, int on) { reinterpret_cast<void(__thiscall*)(void*, int)>(meridian::rebase(0x0040e4e0))(self, on); }
	inline void   LonelyMtnFx_ExtinguishForge(void* self) { reinterpret_cast<void(__thiscall*)(void*)>(meridian::rebase(0x0040e590))(self); }

} // namespace npc_ai
