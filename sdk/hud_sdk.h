// ============================================================================
//  hud_sdk.h  —  HUD / on-screen-overlay SDK for THE HOBBIT (2003) PC build
//  Entropy engine, MSVC, 32-bit (Meridian.exe).
//
//  Reverse-engineered modding / trainer SDK. All addresses are absolute PC
//  virtual addresses; resolve them at runtime with meridian::rebase(0xADDR)
//  which applies the current module-base delta vs the analyzed image base.
//
//  The HUD is a SINGLETON living at &DAT_0075e388. Methods are __thiscall and
//  operate on that instance; obtain it with hud_sdk::fn::GetHud().
//
//  Field offsets below are CONSOLIDATED across 4 per-chunk analyses (evidence-
//  backed). Offsets marked "?" are lower confidence. Some regions are aliased
//  by two interpretations (e.g. hud+0x194 is both the frontend-texture sprite
//  array and the stone-RI array) — they are the same physical bytes. The
//  structs are NOT meant to be instantiated; only reinterpret_cast onto the
//  live singletons.
// ============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase, vector2/3/4, xstring, xcolor (fwd), Ghidra aliases, ...

// ---- Forward declarations for engine types we don't fully model -------------
// (Most of these are already declared in meridian_types.h; re-declaring a
//  struct name is harmless and keeps this header readable standalone.)
struct hud;
struct Hud_3D_Object;
struct info_overlay;
struct dlg_QuestItemPopUp;
struct dlg_message;
struct MusicLogic;
struct Pause_Mgr;
struct bilbo;
struct bilboInventory;
struct bin_in;
struct bin_out;
struct smart_2dsprite;
struct xbitmap;
struct xcolor;
struct xstring;
template <class T> struct xarray;

namespace hud_sdk {

	// ===========================================================================
	//  1. Enums
	// ===========================================================================

	// MusicLogic state machine ids (hud_sdk: MusicLogic+0x24c). Dispatched by
	// MusicLogic::AdvanceStateMachine; targeted by ChangeState(int).
	enum class MusicState : int32_t {
		AmbientOutdoor = 1,
		Silence = 2,   // also entered as 4 in some transitions
		Combat = 3,
		AmbientStinger = 4,
		BossCombat = 5,
		CombatVictory = 6,
		BossCombatVictory = 7,
		CombatLoss = 9,
		Transition = 10,  // active cross-fade / ChangeState(10) target
	};

	// hud use-icon ("exclaim") animation sub-state (hud+0x8a4).
	enum class UseIconState : int32_t {
		Idle = 0,
		StartForward = 1,
		StartReverse = 2,
		Playing = 3,
		Hold = 4,
		PlayingAlt = 5,
		Teardown = 6,
	};

	// ===========================================================================
	//  2. hud  —  master overlay singleton (consolidated layout)
	//     Cast GetHud() to hud*. Do NOT instantiate.
	//     #pragma pack(1) so explicit padding lands members at their true offsets.
	// ===========================================================================
#pragma pack(push, 1)
	struct hud {
		uint32_t blinkState0;                      // 0x000  selected-item blink toggle (XOR 1)
		float    blinkTimer4;                      // 0x004  selected-item blink timer (counts down ~1/30s)
		//uint8_t _pad008[0x08 - 0x08];              // 0x008
		int32_t  active;                           // 0x008  init/active flag; gates HUD logic
		int32_t  overlayFlagC;                     // 0x00c  sub-overlay enable
		uint8_t _pad010[0x14 - 0x10];              // 0x010
		// 0x14  auxRIArray: Hud_3D_Object[10], stride 0x20 (each +0x10 = active flag).
		//       Also reused as a HUD element pos/anchor block (posX@0x14,posY@0x18,
		//       anchorX@0x1c,anchorY@0x20) by SetPositionAndAnchor.
		uint8_t  auxRIArray[0x54 - 0x14];          // 0x014
		uint8_t  awarenessFillSprite[0x74 - 0x54]; // 0x054  smart_2dsprite (awareness fg fill)
		uint8_t  awarenessBgSprite[0x94 - 0x74];   // 0x074  smart_2dsprite (awareness bg)
		uint8_t  npcHealthSkin1Sprite[0xd4 - 0x94];// 0x094  smart_2dsprite (NPC health skin 1)
		uint8_t  npcHealthSkin0Sprite[0x128 - 0xd4];// 0x0d4 smart_2dsprite (NPC health skin 0)
		int32_t  riPoolCount;                      // 0x128  UnloadHudRIPool loop bound
		uint32_t riPoolGuids;                      // 0x12c  __uint64* guid array base (game ptr; 32-bit)
		uint8_t _pad130[0x158 - 0x130];            // 0x130
		int32_t  screenWidthPx;                    // 0x158  selected-item icon base X
		int32_t  screenHeightPx;                   // 0x15c  selected-item icon base Y (iconScale lives @0x15c word)
		uint8_t _pad160[0x16c - 0x160];            // 0x160
		int32_t  trollMeterValue;                  // 0x16c  troll/boss meter (0..100; <0 hidden) / awareness setter target
		int32_t  npcHealthValue;                   // 0x170  named-NPC health (0..100; <0 hidden)
		int32_t  npcHealthStyle;                   // 0x174  NPC health skin selector
		int32_t  awarenessLevel;                   // 0x178  stealth "eye" level (0..100; <0 hidden)
		int32_t  npcHealthBlinkTrigger;            // 0x17c
		int32_t  npcHealthBlinkState;              // 0x180
		int32_t  awarenessBlinkTrigger;            // 0x184
		int32_t  awarenessBlinkState;              // 0x188
		uint8_t _pad18c[0x194 - 0x18c];            // 0x18c
		// 0x194  frontend texture sprite array (xbitmap[], stride 0x20) ==
		//        stoneRIArray (Hud_3D_Object[23], stride 0x20). Same bytes.
		uint8_t  frontendTextures[0x1d4 - 0x194];  // 0x194
		uint8_t  cpBarCapSprite[0x1f4 - 0x1d4];    // 0x1d4  smart_2dsprite (CP-bar cap)
		uint8_t  cpBarMidSprite[0x210 - 0x1f4];    // 0x1f4  smart_2dsprite (CP-bar middle segment)
		int32_t  selectedItemFillPct;              // 0x210  depleting fill (x0.01)
		uint8_t _pad214[0x294 - 0x214];            // 0x214
		uint8_t  healthBarSprite[0x380 - 0x294];   // 0x294  smart_2dsprite (small health bar)
		uint32_t riPoolMask;                       // 0x380  2D RI occupancy bitmask (slots 1..31)
		uint8_t  riPool[0x3d4 - 0x384];            // 0x384  RenderInstance[31] (0x1c stride; first usable @0x398)
		uint8_t  potionSlotBitmap[0x554 - 0x3d4];  // 0x3d4  xbitmap (potion slot)
		int32_t  questTimerActive;                 // 0x554  quest-timer gate / RenderRocks reset flag (same bytes)
		//uint8_t _pad558[0x558 - 0x558];            // 0x558
		float    screenCenterX;                    // 0x558  width * 0.5
		float    screenCenterY;                    // 0x55c  height * 0.5
		float    screenWidth;                      // 0x560  framebuffer width
		float    screenHeight;                     // 0x564  framebuffer height
		float    pulseTimer;                       // 0x568  += 0.0333667 each frame
		float    frameDt;                          // 0x56c  ~0.03337 const
		float    uiScale;                          // 0x570  width / 1024.0 (multiplies layout dims)
		float    health;                           // 0x574  bilbo::GetHealth snapshot
		float    prevHealth;                       // 0x578  change detect
		uint8_t _pad57c[0x584 - 0x57c];            // 0x57c
		int32_t  modeA;                            // 0x584  =1 default
		int32_t  modeB;                            // 0x588  =3 default
		uint8_t _pad58c[0x5a4 - 0x58c];            // 0x58c
		float    questTimerBarX;                   // 0x5a4  width - 60
		float    questTimerBarY;                   // 0x5a8  height - 40
		uint8_t _pad5ac[0x5bc - 0x5ac];            // 0x5ac
		float    questTimerBarW;                   // 0x5bc  60.0
		float    questTimerBarH;                   // 0x5c0  height - 40
		uint8_t _pad5c4[0x5e0 - 0x5c4];            // 0x5c4
		uint8_t  slotArray[0x6c4 - 0x5e0];         // 0x5e0  struct[15], stride 0x10 (per-slot float records)
		uint8_t  potionSprite[0x72c - 0x6c4];      // 0x6c4  smart_2dsprite (potion)
		int32_t  hasPotionFlag;                    // 0x72c  item 3 present
		int32_t  potionSpriteHandle;               // 0x730  -1 = none
		int32_t  potionState734;                   // 0x734
		uint8_t _pad738[0x73c - 0x738];            // 0x738
		uint8_t  ringSlotSprite[0x7d0 - 0x73c];    // 0x73c  smart_2dsprite (ring slot)
		float    const125;                         // 0x7d0  125.0
		uint8_t _pad7d4[0x7e8 - 0x7d4];            // 0x7d4
		uint32_t cpBarColor;                       // 0x7e8  passed to RenderCPBar
		uint8_t _pad7ec[0x7f4 - 0x7ec];            // 0x7ec
		int32_t  fullHudFlag;                      // 0x7f4  0 = minimal HUD path
		uint8_t _pad7f8[0x814 - 0x7f8];            // 0x7f8
		float    letterboxAmount;                  // 0x814  >0 -> letterbox / suppress 3D icons
		float    fadeoutAmount;                    // 0x818  >0 -> fadeout
		float    fadeSpeed;                        // 0x81c  sign = direction
		uint32_t fadeColor;                        // 0x820  xcolor (4 bytes)
		float    fadeProgress;                     // 0x824  accumulator
		float    wipeProgress;                     // 0x828
		float    wipeTarget;                       // 0x82c
		float    wipeSpeed;                        // 0x830
		uint32_t wipeColor;                        // 0x834  xcolor (4 bytes)
		uint8_t _pad838[0x848 - 0x838];            // 0x838
		float    effectTimer848;                   // 0x848  health-change effect timer
		float    const255;                         // 0x84c  255.0
		uint8_t _pad850[0x868 - 0x850];            // 0x850
		int32_t  overlayFlag868;                   // 0x868
		uint8_t _pad86c[0x874 - 0x86c];            // 0x86c
		int32_t  couragePointCount;                // 0x874  =0x18; CP cells = count/4
		uint8_t _pad878[0x884 - 0x878];            // 0x878
		int32_t  overlayFlag884;                   // 0x884
		uint8_t _pad888[0x890 - 0x888];            // 0x888
		uint64_t useIconGuid;                      // 0x890  active use-icon GUID
		int32_t  useTargetIdLo;                    // 0x898
		int32_t  useTargetIdHi;                    // 0x89c
		float    useIconTimestamp;                 // 0x8a0  game time
		int32_t  useIconAnimState;                 // 0x8a4  UseIconState (0..6)
		uint8_t  riPool3D[0xb10 - 0x8a8];          // 0x8a8  GuidPair[77] (RI pool, stride 8)
		float    riPoolTimestamps[(0xc48 - 0xb10) / 4]; // 0xb10  float[77] lock timestamps
		uint8_t  targetPool[0x138c - 0xc48];       // 0xc48  GuidPair[77] (target reticle pool)
		int32_t  targetAnimHandleB;                // 0x138c  also rocksTimers[0] region (0x7fffffff)
		int32_t  targetAnimHandleA;                // 0x1390
		uint8_t _pad1394[0x13a0 - 0x1394];         // 0x1394
		float    ringProgress;                     // 0x13a0  ring effect 0<x<1, two phases at 0.5
		uint8_t  ringHaloBitmap[0x13c4 - 0x13a4];  // 0x13a4  xbitmap / Hud_3D_Object (RingScreenHalo)
		uint8_t  ringHaloBlackBitmap[0x13e4 - 0x13c4]; // 0x13c4 xbitmap / Hud_3D_Object (RingScreenHaloBlack)
		// (struct intentionally ends at 0x13e4; higher offsets like the selected-
		//  item RI handle @ word 0x1ea (=byte 0x7a8) and sub-resource @0x2098 are
		//  reached via off:: constants + field<T>(), not modeled as members.)
	};
#pragma pack(pop)

	// ---- hud RI-pool slot entry (0x1c stride @ hud+0x398) ----------------------
#pragma pack(push, 1)
	struct RenderInstance {
		uint8_t _pad00[0x10 - 0x00]; // 0x00
		uint32_t tint;               // 0x10  default 0x3f800000 (1.0f)
		float    alphaOrScale;       // 0x14  1.0 on alloc
		uint8_t  flags;              // 0x18  low bit cleared on alloc
		uint8_t _pad19[0x1c - 0x19]; // 0x19
	};
#pragma pack(pop)

	// ===========================================================================
	//  3. Hud_3D_Object  —  one HUD 3D element (stone / courage point / ring fx)
	// ===========================================================================
#pragma pack(push, 1)
	struct Hud3DObject {
		uint8_t _pad00[0x10 - 0x00]; // 0x00
		int32_t  isActive;           // 0x10  checked before draw
		uint8_t _pad14[0xb0 - 0x14]; // 0x14
		float    posX;               // 0xb0
		float    posY;               // 0xb4
		float    posZ;               // 0xb8
		float    rotOrScale;         // 0xbc
		uint32_t geometryName;       // 0xc0  name/geometry handle (game ptr; 32-bit)
		uint8_t  geometrySubObj[0x10]; // 0xc4 embedded geometry sub-object (opaque)
	};
#pragma pack(pop)

	// ===========================================================================
	//  4. info_overlay
	// ===========================================================================
#pragma pack(push, 1)
	struct info_overlay_layout {
		int32_t  isOpen;                       // 0x00  open/valid flag
		uint8_t _pad04[0x20 - 0x04];           // 0x04
		int32_t  isClosing;                    // 0x20  closing latch
		uint8_t _pad24[0xcc - 0x24];           // 0x24
		uint8_t  stringIdNames[0x158 - 0xcc];  // 0xcc  xarray<xstring>
		uint8_t _pad158[0x15c - 0x158];        // 0x158
		uint32_t messageDialog;                // 0x15c  dlg_message* (game ptr; 32-bit; 0 -> create)
		uint8_t  dialogContext[0x168 - 0x160]; // 0x160  embedded object/context
		int32_t  initFlag168;                  // 0x168
	};
#pragma pack(pop)

	// ===========================================================================
	//  5. dlg_QuestItemPopUp
	// ===========================================================================
#pragma pack(push, 1)
	struct QuestItemPopUp {
		uint64_t ownerGuid;                    // 0x00
		int32_t  isActive;                     // 0x08
		int32_t  itemCount;                    // 0x0c  (also layout-mode selector)
		int32_t  repeatTimer;                  // 0x10
		int32_t  itemIds[(0x8c - 0x14) / 4];   // 0x14  int[30] (init -1)
		int32_t  cursorIndex;                  // 0x8c
		int32_t  cursorRepeat;                 // 0x90
		uint8_t _pad94[0x144 - 0x94];          // 0x94
		float    popupScale;                   // 0x144  2.0
		uint8_t _pad148[0x9c8 - 0x148];        // 0x148
		int32_t  initSkipLatch;                // 0x9c8
		int32_t  leftEdge;                     // 0x9cc
		int32_t  leftHeld;                     // 0x9d0
		int32_t  rightEdge;                    // 0x9d4
		int32_t  rightHeld;                    // 0x9d8
	};
#pragma pack(pop)

	// ===========================================================================
	//  6. MusicLogic  —  gameplay-driven music state machine
	//     Cast GetMusicLogic() to MusicLogic*. Do NOT instantiate.
	// ===========================================================================
#pragma pack(push, 1)
	struct MusicLogicLayout {
		uint8_t _pad00[0x7f - 0x00];           // 0x00
		uint8_t  initFlags;                    // 0x7f  ctor sets |=1
		uint8_t _pad80[0xa8 - 0x80];           // 0x80
		int32_t  bossCombatLatch;              // 0xa8  set on a type-0x12 object; forces ChangeState(5)
		uint8_t _pad_ac[0xbc - 0xac];          // 0xac
		int32_t  packageCount;                 // 0xbc
		uint32_t packageArray;                 // 0xc0  void** (game ptr; 32-bit)
		uint8_t  musicLevelFile[0xf4 - 0xc4];  // 0xc4  xstring (0xc8 in some notes; field spans here)
		uint8_t  musicLevelName[0x120 - 0xf4]; // 0xf4  xstring
		int32_t  audioPackageCount;            // 0x120
		uint8_t _pad124[0x12c - 0x124];        // 0x124
		int32_t  audioPackageActiveCount;      // 0x12c
		uint32_t audioPackageArray;            // 0x130  void* (game ptr; 32-bit); count*0x2c+4
		int32_t  audioPackageCapacity;         // 0x134
		uint8_t _pad138[0x140 - 0x138];        // 0x138
		uint32_t activeDescriptor;             // 0x140
		uint8_t _pad144[0x15c - 0x144];        // 0x144
		int32_t  stateDirty;                   // 0x15c
		int32_t  stateChangedThisFrame;        // 0x160
		uint8_t  defaultSuite[0x190 - 0x164];  // 0x164  xstring
		uint8_t  defaultTrack[0x214 - 0x190];  // 0x190  xstring (+ misc)
		uint32_t trackedZoneDescriptor;        // 0x214
		uint8_t _pad218[0x240 - 0x218];        // 0x218
		int32_t  fadeActive;                   // 0x240  (also "musicPlaying")
		int32_t  fadeType;                     // 0x244
		uint32_t currentSuiteHandle;           // 0x248
		int32_t  state;                        // 0x24c  canonical MusicState id
		int32_t  previousState;                // 0x250  (also fallbackStateA)
		float    bossCombatArg;                // 0x254  699.0
		float    timerConst1500;               // 0x258  1500.0
		uint8_t _pad25c[0x260 - 0x25c];        // 0x25c
		float    threatVerticalRange;          // 0x260
		int32_t  desiredAmbientSuite;          // 0x264  (also committedSuiteHandle)
		int32_t  combatIntensity;              // 0x268  (also selectedTrackId)
		int32_t  peakCombatIntensity;          // 0x26c  (also trackWatermark)
		float    stateTimer;                   // 0x270  (combat-proximity / intensity)
		float    combatSampleTimer;            // 0x274  7.5s gate (boss-combat timer)
		float    minSilenceTime;               // 0x278  (also stateMinDuration)
		float    maxSilenceTime;               // 0x27c
		float    volumeFadeTime;               // 0x280  (also pendingTrackHandle)
		float    volumeFadeTimeCur;            // 0x284
		//uint8_t _pad288[0x288 - 0x288];        // 0x288
		float    combatTimeout;                // 0x288  (also stateTimeout)
		uint8_t _pad28c[0x290 - 0x28c];        // 0x28c
		int32_t  transitionDone;               // 0x290
		int32_t  fadeCounter;                  // 0x294  (also stateTimer294)
		int32_t  defaultState;                 // 0x298  (resume / fallbackStateB)
		uint8_t  defaultStateName[0x2c8 - 0x29c]; // 0x29c xstring
		uint32_t currentZoneDescriptor;        // 0x2c8
		uint8_t _pad2cc[0x2f4 - 0x2cc];        // 0x2cc
		float    minCombatThreshold;           // 0x2f4  10.0 (threatThresholdLow)
		float    maxCombatThreshold;           // 0x2f8
		float    minCombatTimeForStinger;      // 0x2fc
		float    currentThreat;                // 0x300  (threatThresholdHigh)
		float    peakThreat;                   // 0x304  running max
	};
#pragma pack(pop)

	// ===========================================================================
	//  7. Authoritative offset constants (use with field<T>() byte access)
	// ===========================================================================
	namespace off {
		// ---- hud ----
		constexpr uint32_t ACTIVE = 0x008;
		constexpr uint32_t SCREEN_WIDTH = 0x560;   // float
		constexpr uint32_t SCREEN_HEIGHT = 0x564;   // float
		constexpr uint32_t UI_SCALE = 0x570;   // float (w/1024)
		constexpr uint32_t HEALTH = 0x574;   // float
		constexpr uint32_t TROLL_METER_VALUE = 0x16c;   // int
		constexpr uint32_t NPC_HEALTH_VALUE = 0x170;   // int
		constexpr uint32_t NPC_HEALTH_STYLE = 0x174;   // int
		constexpr uint32_t AWARENESS_LEVEL = 0x178;   // int
		constexpr uint32_t FULL_HUD_FLAG = 0x7f4;   // int (0 = minimal HUD)
		constexpr uint32_t LETTERBOX_AMOUNT = 0x814;   // float
		constexpr uint32_t FADEOUT_AMOUNT = 0x818;   // float
		constexpr uint32_t FADE_SPEED = 0x81c;   // float
		constexpr uint32_t FADE_COLOR = 0x820;   // xcolor (u32)
		constexpr uint32_t FADE_PROGRESS = 0x824;   // float
		constexpr uint32_t WIPE_PROGRESS = 0x828;   // float
		constexpr uint32_t WIPE_TARGET = 0x82c;   // float
		constexpr uint32_t WIPE_SPEED = 0x830;   // float
		constexpr uint32_t WIPE_COLOR = 0x834;   // xcolor (u32)
		constexpr uint32_t COURAGE_POINT_COUNT = 0x874;   // int (=0x18)
		constexpr uint32_t QUEST_TIMER_ACTIVE = 0x554;   // int
		constexpr uint32_t RING_PROGRESS = 0x13a0;  // float [0,1]
		constexpr uint32_t USE_ICON_GUID = 0x890;   // u64
		constexpr uint32_t USE_ICON_ANIM_STATE = 0x8a4;   // int (UseIconState)
		constexpr uint32_t RI_POOL_MASK = 0x380;   // u32 (slots 1..31)
		constexpr uint32_t RI_POOL_3D = 0x8a8;   // GuidPair[77]
		constexpr uint32_t TARGET_POOL = 0xc48;   // GuidPair[77]
		constexpr uint32_t SELECTED_ITEM_RI = 0x7a8;   // int (word index 0x1ea); -1 = none
		constexpr uint32_t SUB_RESOURCE = 0x2098;  // void* (IsReadyAndIdle gate)
		// ---- MusicLogic ----
		constexpr uint32_t ML_STATE = 0x24c;   // int (MusicState)
		constexpr uint32_t ML_BOSS_LATCH = 0xa8;    // int
		constexpr uint32_t ML_STATE_TIMER = 0x270;   // float
		constexpr uint32_t ML_CUR_THREAT = 0x300;   // float
		constexpr uint32_t ML_PEAK_THREAT = 0x304;   // float
		constexpr uint32_t ML_THREAT_THRESH_LOW = 0x2f4;   // float (10.0)
		constexpr uint32_t ML_CUR_SUITE_HANDLE = 0x248;   // u32
		constexpr uint32_t ML_DEFAULT_STATE = 0x298;   // int
	}

	// ===========================================================================
	//  8. Global singletons
	// ===========================================================================
	namespace addr {
		constexpr uint32_t HUD_SINGLETON = 0x0075e388; // &DAT_0075e388
		constexpr uint32_t PAUSE_MGR = 0x00763208; // &DAT_00763208
	}

	// ===========================================================================
	//  9. Typed function wrappers
	//     __thiscall methods take the object pointer as the first arg.
	// ===========================================================================
	namespace fn {

		// ---- singletons ----------------------------------------------------------
		inline hud* GetHud() {
			return reinterpret_cast<hud*>(meridian::rebase(addr::HUD_SINGLETON));
		}
		// MusicLogic singleton getter: demangled API lists GetMusicLogic() __cdecl but
		// no resolved address in the analyzed set. Resolve the global directly if you
		// know its data address, e.g.:  reinterpret_cast<MusicLogic*>(meridian::rebase(0xADDR));

		// ---- hud: lifecycle ------------------------------------------------------
		inline int Init(hud* p) {
			using F = int(__thiscall*)(hud*);
			return reinterpret_cast<F>(meridian::rebase(0x004f2290))(p);
		}
		inline void ResetHudVars(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f2440))(p);
		}
		inline void InitHudRIPool(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f6eb0))(p);
		}
		inline void UnloadHudRIPool(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004de520))(p);
		}
		inline void UnloadMeters(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x0058eb00))(p);
		}
		inline void AdvanceRIPool(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f7a00))(p);
		}

		// ---- hud: per-frame ------------------------------------------------------
		inline void Update(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f5340))(p);
		}
		inline void Render(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f32f0))(p);
		}
		inline void RenderTopHalfOfHud(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f34c0))(p);
		}
		inline void UpdateBilboHealth(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f50e0))(p);
		}
		inline void UpdateQuestTimer(hud* p, float dt) {
			using F = void(__thiscall*)(hud*, float);
			reinterpret_cast<F>(meridian::rebase(0x004f8dc0))(p, dt);
		}

		// ---- hud: element draws --------------------------------------------------
		inline void RenderPotions(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f34e0))(p);
		}
		inline void RenderRing(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f3ac0))(p);
		}
		inline void RenderChargeMeter(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f3f90))(p);
		}
		inline void RenderTrollMeter(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f42c0))(p);
		}
		inline void RenderCustomNPCHealthMeter(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f4990))(p);
		}
		inline void RenderAwarenessMeter(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f4e90))(p);
		}
		inline void RenderSmallHealthBar(hud* p, int layoutMode) {
			using F = void(__thiscall*)(hud*, int);
			reinterpret_cast<F>(meridian::rebase(0x004f58f0))(p, layoutMode);
		}
		// RenderCPBar takes vector2 BY VALUE. vector2 IS complete (meridian_types.h),
		// so the typed wrapper is safe.
		inline void RenderCPBar(hud* p, vector2 base, int param2) {
			using F = void(__thiscall*)(hud*, vector2, int);
			reinterpret_cast<F>(meridian::rebase(0x004f60b0))(p, base, param2);
		}
		inline void RenderRingEffects(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f2e00))(p);
		}
		inline void RenderFullscreenRingHalo(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f2b00))(p);
		}
		inline void RenderRocks(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f28e0))(p);
		}
		inline void RenderSkipControl(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f9070))(p);
		}
		inline void BlackOutScreen(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f8fb0))(p);
		}
		// RenderScreenColorizer(hud*, xcolor) — xcolor is an INCOMPLETE type passed BY
		// VALUE; we cannot form the by-value signature here. Use the address accessor.
		// Raw sig: void __thiscall hud::RenderScreenColorizer(hud*, xcolor color)
		inline void* RenderScreenColorizer_at() { return meridian::rebase(0x004f8ec0); }

		// ---- hud: 3D overlays ----------------------------------------------------
		inline void RenderUseIcon(hud* p, const vector3& targetPos, uint64_t guid) {
			using F = void(__thiscall*)(hud*, const vector3*, uint64_t);
			reinterpret_cast<F>(meridian::rebase(0x004f7610))(p, &targetPos, guid);
		}
		inline void RenderTarget(hud* p, const vector3& pos, float dist, int animSel, uint64_t guid) {
			using F = void(__thiscall*)(hud*, const vector3*, float, int, uint64_t);
			reinterpret_cast<F>(meridian::rebase(0x004f7e10))(p, &pos, dist, animSel, guid);
		}

		// ---- hud: transitions / effects ------------------------------------------
		inline void RenderFadeout(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f85c0))(p);
		}
		inline void RenderWipe(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f86e0))(p);
		}
		inline void RenderLetterbox(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f83a0))(p);
		}
		// SetFadeout(hud*, int dir, xcolor color, float speed) — xcolor BY VALUE.
		// Raw sig: void __thiscall hud::SetFadeout(hud*, int, xcolor, float)
		inline void* SetFadeout_at() { return meridian::rebase(0x004f8520); }
		// SetWipeout(hud*, float target, float speed, xcolor color) — xcolor BY VALUE.
		// Raw sig: void __thiscall hud::SetWipeout(hud*, float, float, xcolor)
		inline void* SetWipeout_at() { return meridian::rebase(0x004f8640); }

		// ---- hud: meter setters --------------------------------------------------
		inline void SetAwarenessMeter(hud* p, int level) {
			using F = void(__thiscall*)(hud*, int);
			reinterpret_cast<F>(meridian::rebase(0x004f8a30))(p, level);
		}
		inline void SetCustomNPCHealthMeter(hud* p, int cur, int max, int mode) {
			using F = void(__thiscall*)(hud*, int, int, int);
			reinterpret_cast<F>(meridian::rebase(0x004f8a50))(p, cur, max, mode);
		}
		inline void SetBlinkRing(hud* p, float period) {
			using F = void(__thiscall*)(hud*, float);
			reinterpret_cast<F>(meridian::rebase(0x004f42b0))(p, period);
		}

		// ---- hud: low-level RI-pool slot allocator (proposed names) --------------
		inline int AllocRenderInstance(hud* p, const char* resourceName, void* xform, uint32_t color) {
			using F = int(__thiscall*)(hud*, const char*, void*, uint32_t);
			return reinterpret_cast<F>(meridian::rebase(0x0058e610))(p, resourceName, xform, color);
		}
		inline int FreeRenderInstance(hud* p, int slot) {
			using F = int(__thiscall*)(hud*, int);
			return reinterpret_cast<F>(meridian::rebase(0x0058e880))(p, slot);
		}
		inline void DrawSelectedItemIcon(hud* p) {
			using F = void(__thiscall*)(hud*);
			reinterpret_cast<F>(meridian::rebase(0x004f3ca0))(p);
		}

		// ---- hud2d: immediate-mode 2D primitive API (free, __cdecl) --------------
		inline void SetVertexColor(uint32_t argb) {
			using F = void(__cdecl*)(uint32_t);
			reinterpret_cast<F>(meridian::rebase(0x0066ddd0))(argb);
		}
		inline void PushVertex(float x, float y, float z) {
			using F = void(__cdecl*)(float, float, float);
			reinterpret_cast<F>(meridian::rebase(0x0066dfc0))(x, y, z);
		}
		inline void PushSprite(float* pos, float* size, float* uv0, float* uv1, uint32_t color) {
			using F = void(__cdecl*)(float*, float*, float*, float*, uint32_t);
			reinterpret_cast<F>(meridian::rebase(0x0066e6b0))(pos, size, uv0, uv1, color);
		}
		inline void DrawRect(float* rect, uint32_t color, int outline) {
			using F = void(__cdecl*)(float*, uint32_t, int);
			reinterpret_cast<F>(meridian::rebase(0x0066b080))(rect, color, outline);
		}
		inline void DrawRectOutline(int* rect, uint* c0, uint* c1, uint* c2, uint* c3, int filled) {
			using F = void(__cdecl*)(int*, uint*, uint*, uint*, uint*, int);
			reinterpret_cast<F>(meridian::rebase(0x0066b4f0))(rect, c0, c1, c2, c3, filled);
		}
		inline void DrawScreenRect(int* rect, uint32_t argb, int outline) {
			using F = void(__cdecl*)(int*, uint32_t, int);
			reinterpret_cast<F>(meridian::rebase(0x0066b290))(rect, argb, outline);
		}
		inline void DrawAxisGizmo(float length) {
			using F = void(__cdecl*)(float);
			reinterpret_cast<F>(meridian::rebase(0x0066ab60))(length);
		}

		// ---- info_overlay --------------------------------------------------------
		inline void Info_init(info_overlay* p) {
			using F = void(__thiscall*)(info_overlay*);
			reinterpret_cast<F>(meridian::rebase(0x00525e20))(p);
		}
		inline void Info_InfoBox(info_overlay* p, const char* idLabel, const uint16_t* msg, int showDone) {
			using F = void(__thiscall*)(info_overlay*, const char*, const uint16_t*, int);
			reinterpret_cast<F>(meridian::rebase(0x00526640))(p, idLabel, msg, showDone);
		}
		inline void Info_CloseInfoBox(info_overlay* p) {
			using F = void(__thiscall*)(info_overlay*);
			reinterpret_cast<F>(meridian::rebase(0x005577e0))(p);
		}
		inline xarray<xstring>* Info_GetStringIDNames(info_overlay* p) {
			using F = xarray<xstring>* (__thiscall*)(info_overlay*);
			return reinterpret_cast<F>(meridian::rebase(0x00435990))(p);
		}

		// ---- dlg_QuestItemPopUp --------------------------------------------------
		inline void Popup_Init(dlg_QuestItemPopUp* p, uint64_t ownerGuid) {
			using F = void(__thiscall*)(dlg_QuestItemPopUp*, uint64_t);
			reinterpret_cast<F>(meridian::rebase(0x0051ee60))(p, ownerGuid);
		}
		inline int Popup_Update(dlg_QuestItemPopUp* p) {
			using F = int(__thiscall*)(dlg_QuestItemPopUp*);
			return reinterpret_cast<F>(meridian::rebase(0x0051efa0))(p);
		}
		inline void Popup_Render(dlg_QuestItemPopUp* p) {
			using F = void(__thiscall*)(dlg_QuestItemPopUp*);
			reinterpret_cast<F>(meridian::rebase(0x0051f4d0))(p);
		}

		// ---- Hud_3D_Object -------------------------------------------------------
		// Set(vector4, char*) — vector4 IS complete; passed by value as in the ABI.
		inline void Hud3D_Set(Hud_3D_Object* p, vector4 xform, const char* geomName) {
			using F = void(__thiscall*)(Hud_3D_Object*, vector4, const char*);
			reinterpret_cast<F>(meridian::rebase(0x004f93e0))(p, xform, geomName);
		}

		// ---- MusicLogic ----------------------------------------------------------
		inline void ML_OnAdvanceLogic(MusicLogic* p, float dt) {
			using F = void(__thiscall*)(MusicLogic*, float);
			reinterpret_cast<F>(meridian::rebase(0x00535310))(p, dt);
		}
		inline void ML_AdvanceStateMachine(MusicLogic* p, float dt) {
			using F = void(__thiscall*)(MusicLogic*, float);
			reinterpret_cast<F>(meridian::rebase(0x00535200))(p, dt);
		}
		inline void ML_ChangeState(MusicLogic* p, MusicState s) {
			using F = void(__thiscall*)(MusicLogic*, int);
			reinterpret_cast<F>(meridian::rebase(0x00534f30))(p, static_cast<int>(s));
		}
		inline void ML_UpDateStateSilence(MusicLogic* p, float dt) {
			using F = void(__thiscall*)(MusicLogic*, float);
			reinterpret_cast<F>(meridian::rebase(0x00534dd0))(p, dt);
		}
		inline void ML_UpDatePostCombat(MusicLogic* p, float dt) {
			using F = void(__thiscall*)(MusicLogic*, float);
			reinterpret_cast<F>(meridian::rebase(0x00534b00))(p, dt);
		}
		inline void ML_UpdateStateCombat(MusicLogic* p, float dt) {
			using F = void(__thiscall*)(MusicLogic*, float);
			reinterpret_cast<F>(meridian::rebase(0x00534b80))(p, dt);
		}
		inline void ML_UpDateBossCombat(MusicLogic* p, float radius) {
			using F = void(__thiscall*)(MusicLogic*, float);
			reinterpret_cast<F>(meridian::rebase(0x005342f0))(p, radius);
		}
		inline int ML_CheckCombatPresence(MusicLogic* p) {
			using F = int(__thiscall*)(MusicLogic*);
			return reinterpret_cast<F>(meridian::rebase(0x00534520))(p);
		}
		inline uint32_t ML_SetActiveSuite(MusicLogic* p, void* suiteName, uint32_t param2, uint32_t param3) {
			using F = uint32_t(__thiscall*)(MusicLogic*, void*, uint32_t, uint32_t);
			return reinterpret_cast<F>(meridian::rebase(0x00535810))(p, suiteName, param2, param3);
		}
		inline uint32_t ML_PlayDescriptorByName(MusicLogic* p, char** name, uint32_t param2, uint32_t param3) {
			using F = uint32_t(__thiscall*)(MusicLogic*, char**, uint32_t, uint32_t);
			return reinterpret_cast<F>(meridian::rebase(0x005323f0))(p, name, param2, param3);
		}
		inline void ML_OnImport(MusicLogic* p, bin_in* in) {
			using F = void(__thiscall*)(MusicLogic*, bin_in*);
			reinterpret_cast<F>(meridian::rebase(0x00536400))(p, in);
		}
		inline void ML_OnExport(MusicLogic* p, bin_out* out) {
			using F = void(__thiscall*)(MusicLogic*, bin_out*);
			reinterpret_cast<F>(meridian::rebase(0x00535ec0))(p, out);
		}
		inline void ML_ImportThreatValues(MusicLogic* p, bin_in* in) {
			using F = void(__thiscall*)(MusicLogic*, bin_in*);
			reinterpret_cast<F>(meridian::rebase(0x005360d0))(p, in);
		}

	} // namespace fn

	// ===========================================================================
	//  10. Raw byte accessor (offset-based; safest for trainers)
	// ===========================================================================
	template <class T> inline T& field(void* base, uint32_t o) {
		return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(base) + o);
	}

	// ===========================================================================
	//  TRAINER RECIPES
	//  ---------------------------------------------------------------------------
	//  // Force the FULL HUD on (vs the minimal in-world path), then redraw:
	//      hud* h = hud_sdk::fn::GetHud();
	//      hud_sdk::field<int>(h, hud_sdk::off::FULL_HUD_FLAG) = 1;
	//
	//  // Show / hide a HUD meter directly (values 0..100; <0 = hidden):
	//      hud_sdk::field<int>(h, hud_sdk::off::AWARENESS_LEVEL)  = -1; // hide stealth eye
	//      hud_sdk::fn::SetCustomNPCHealthMeter(h, /*cur*/50, /*max*/100, /*mode*/0);
	//      hud_sdk::field<int>(h, hud_sdk::off::TROLL_METER_VALUE) = -1; // hide troll bar
	//
	//  // Query a HUD element state (e.g. is the ring effect playing?):
	//      float ring = hud_sdk::field<float>(h, hud_sdk::off::RING_PROGRESS); // 0<x<1 active
	//
	//  // Black out / restore the screen (e.g. for a custom transition):
	//      hud_sdk::fn::BlackOutScreen(h);
	//
	//  // Skip a cutscene fade: clear the fade + letterbox + wipe amounts so Render
	//  // takes the no-overlay path next frame:
	//      hud_sdk::field<float>(h, hud_sdk::off::FADEOUT_AMOUNT)   = 0.0f;
	//      hud_sdk::field<float>(h, hud_sdk::off::LETTERBOX_AMOUNT) = 0.0f;
	//      hud_sdk::field<float>(h, hud_sdk::off::WIPE_PROGRESS)    = 0.0f;
	//
	//  // Call SetFadeout (xcolor passed by value -> use the address accessor):
	//      using SetFadeout_t = void (__thiscall*)(hud*, int, /*xcolor*/uint32_t, float);
	//      auto SetFadeout = reinterpret_cast<SetFadeout_t>(hud_sdk::fn::SetFadeout_at());
	//      SetFadeout(h, /*dir*/1, /*0xAARRGGBB*/0xff000000u, /*speed*/2.0f);
	//
	//  // Draw your own immediate-mode HUD box (must be inside the engine's batch):
	//      float rect[4] = { 10, 10, 210, 50 };
	//      hud_sdk::fn::DrawRect(rect, 0x80000000u, /*outline=*/0); // semi-transparent fill
	//
	//  // Read current screen dims / UI scale for custom overlay layout:
	//      float w = hud_sdk::field<float>(h, hud_sdk::off::SCREEN_WIDTH);
	//      float s = hud_sdk::field<float>(h, hud_sdk::off::UI_SCALE);
	//
	//  // Force the music state machine (e.g. force combat / silence):
	//      MusicLogic* m = /* reinterpret_cast<MusicLogic*>(meridian::rebase(0xADDR)) */ nullptr;
	//      if (m) hud_sdk::fn::ML_ChangeState(m, hud_sdk::MusicState::Combat);
	// ===========================================================================

} // namespace hud_sdk
