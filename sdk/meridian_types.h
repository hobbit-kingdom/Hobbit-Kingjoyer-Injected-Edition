// AUTO-GENERATED type stubs for Meridian SDK. Refine with real layouts.
// Single source of truth for meridian::rebase + the shared value types.
// Every *_sdk.h header includes this; do not redefine these elsewhere.
#pragma once
#include <cstdint>

// ---- Runtime rebasing -------------------------------------------------------
// The retail build has ASLR OFF (preferred base 0x00400000), so PC addresses
// are absolute and g_delta stays 0. If you ever load the image at a non-
// preferred base, set meridian::g_delta = actualBase - 0x400000 once at init.
namespace meridian {
	inline std::intptr_t  g_delta = 0;
	inline void* rebase(std::uintptr_t preferred) {
		return reinterpret_cast<void*>(static_cast<std::uintptr_t>(preferred) + g_delta);
	}
}

// ---- Known value types ------------------------------------------------------
// Define MERIDIAN_NO_MATH_TYPES before including if your project already
// declares vector3/etc., to avoid redefinition.
#ifndef MERIDIAN_NO_MATH_TYPES
#define MERIDIAN_MATH_TYPES_DEFINED 1
struct vector3 { float x, y, z; };
struct vector2 { float x, y; };
struct vector4 { float x, y, z, w; };
struct matrix4 { float m[16]; };
struct quaternion { float x, y, z, w; };
struct radian3 { float x, y, z; };          // Euler pitch/yaw/roll (radians)
struct bbox { vector3 min; vector3 max; };  // min @ +0x0, max @ +0xc
#endif

// ---- Ghidra decompiler primitive aliases (so undefined4/code/etc. resolve) --
typedef unsigned long long __uint64; // Ghidra emits __uint64; not a keyword in MSVC or GCC
typedef std::uint8_t  undefined;
typedef std::uint8_t  undefined1;
typedef std::uint16_t undefined2;
typedef std::uint32_t undefined4;
typedef std::uint64_t undefined8;
typedef std::uint8_t  byte;
typedef std::uint8_t  uchar;
typedef std::uint16_t ushort;
typedef unsigned int  uint;
typedef void          code;          // Ghidra 'code' (used only as code*)

// ---- Engine value types that some signatures pass/return BY VALUE -----------
// Recovered sizes; treated as opaque blobs so by-value calls compile. Sizes are
// approximate — prefer pointer/reference variants for ABI-critical paths.
#ifndef MERIDIAN_NO_ENGINE_VALUE_TYPES
struct xstring { unsigned char _bytes[0x2c]; };  // sizeof 0x2c (confirmed)
struct xwstring { unsigned char _bytes[0x2c]; };  // wide string (approx)
struct property { unsigned char _bytes[0x258]; }; // tagged variant (~0x21c-0x258)
struct property_desc { unsigned char _bytes[0x108]; }; // editor schema row (0x108)
#endif

// Opaque forward declarations (used via pointer). Sizes unknown; refine as needed.
struct AIAction;
struct AIManager;
struct AIState;
struct AITrigger;
struct ActionActivateHealthMeter;
struct ActionActivateTrigger;
struct ActionAmbientAudioTrigger;
struct ActionBeornCrossBridge;
struct ActionDisableAudioEmitter;
struct ActionFinishBilboQuest;
struct ActionFinishMainBilboQuest;
struct ActionGiveBilboQuest;
struct ActionInfo;
struct ActionInfoOverlay;
struct ActionLerpScreenDistortAmp;
struct ActionModifyHealth;
struct ActionMoveObject;
struct ActionMusicTrigger;
struct ActionRigidInstAnim;
struct ActionRigidInstanceHidden;
struct ActionRigidInstanceHoistable;
struct ActionSetCinema;
struct ActionSetGoalList;
struct ActionSetIdleAnim;
struct ActionSetInventory;
struct ActionSetInvulnerability;
struct ActionSetNPCAnimController;
struct ActionSetNPCCollision;
struct ActionSetNPCRender;
struct ActionSetNPCRenderProp;
struct ActionSetNPCRootToPosition;
struct ActionSetNPCRunAI;
struct ActionSetNPCSenses;
struct ActionSetNPCStateController;
struct ActionSetObjectCollisionFlags;
struct ActionSetRopeLength;
struct ActionSetState;
struct ActionSetTeam;
struct ActionSpawnCP;
struct ActionSpawnNPC;
struct ActionStartCinema;
struct ActionStartDialog;
struct ActionSwapCharacters;
struct ActionToggleLink;
struct ActionToggleMaterialAnimation;
struct ActionTriggerSwitch;
struct AlertState;
struct AmbientAudioMgr;
struct AttackState;
struct BeornAlertState;
struct BolgAttackState;
struct BolgShamanIdleState;
struct BossSpiderIdleState;
struct BossSpiderWickedAttackState;
struct BossSpiderWrathAttackState;
struct BridgeTrollAttackState;
struct CPBreakDown;
struct CastAttackState;
struct CaveGuardianMinionAttackState;
struct CaveGuardianRangedAttackState;
struct CharacterObject;
struct ChestContents;
struct ChickenIdleState;
struct ConversationMgr;
struct CrowIdleState;
struct FeedbackType;
struct FrontEnd_Mgr;
struct GadgetPendulum;
struct GadgetWackAMole;
struct GadgetWackAMole2;
struct GoalAction;
struct GoalGotoTarget;
struct GoalSendMessage;
struct Hud_3D_Object;
struct IdleState;
struct LoadScreen;
struct MessageInfo;
struct MotionLinear;
struct MusicLogic;
struct NPCObject;
struct NavLink;
struct PainData;
struct Pause_Mgr;
struct PhysController;
struct Projectile;
struct RangedAttackState;
struct RetreatState;
struct RockBadgerAttackState;
struct SWITCHTYPE;
struct SenseController;
struct SlotTypes;
struct SmaugAlertState;
struct SmaugAttackState;
struct SmaugIdleState;
struct SpiderAlertState;
struct StateController;
struct Switch;
struct TakeCoverState;
struct TriggerBilboHasItem;
struct TriggerBilboPicksUpItem;
struct TriggerCharacterPlayingAnimation;
struct TriggerChestOpened;
struct TriggerCinemaBegins;
struct TriggerCinemaFinished;
struct TriggerConversationComplete;
struct TriggerEffectFinishes;
struct TriggerGold;
struct TriggerInfo;
struct TriggerNPCBeginsAction;
struct TriggerNPCChangesState;
struct TriggerNPCFinishesGoalList;
struct TriggerNPCHit;
struct TriggerNPCInState;
struct TriggerNPCSensesCharacter;
struct TriggerOnVine;
struct TriggerQuestComplete;
struct TriggerRigidAnimPlaying;
struct TriggerRigidAnimStarted;
struct TriggerSwitchIsOn;
struct TriggerTimedRandom;
struct TriggerVolumeCharacter;
struct TriggerVolumeObject;
struct TriggerWebBreaks;
struct TriggerWorldTriggerToggled;
struct WarIdleState;
struct WightBossAttackState;
struct WispFollowState;
struct WispIdleState;
struct _D3DVBLANKDATA;
struct __value;
struct _func_int_uint_ptr;
struct _func_int_uint_ptr_int_int;
struct _func_int_uint_ptr_uchar_ptr_int;
struct _func_uint_ptr_char_ptr_char_ptr;
struct _func_void_uint_ptr;
struct ambient_audio_trigger;
struct anim_event;
struct anim_group;
struct anim_loader;
struct audio_emitter;
struct audio_mgr;
struct audio_package;
struct bbox;
struct bilbo;
struct bilboInventory;
struct bin_in;
struct bin_out;
struct bitstream;
struct boulder_run;
struct breakaway;
struct camera;
struct camera_influence;
struct camera_mgr;
struct camera_modifier;
struct camera_path;
struct camera_state;
struct cart_status;
struct catapult;
struct char_anim_player;
struct chest_type;
struct cinema;
struct cinema_action;
struct cinema_anim;
struct cinema_anim_inst;
struct cinema_camera;
struct cinema_fx;
struct cinema_fxobj_trigger;
struct cinema_popto;
struct cinema_script;
struct cinema_shot;
struct cinema_syncpoint;
struct clutter_mgr;
struct collision;
struct collmesh;
struct cursor_direction;
struct dialog_tem;
struct dlg_LevelMap;
struct dlg_QuestItemPopUp;
struct dlg_buy_sale;
struct dlg_credits;
struct dlg_end_chapter_summary;
struct dlg_main_menu;
struct dlg_message;
struct dlg_pause_inventory;
struct dlg_pause_questlog;
struct dlg_pause_summary;
struct dlg_pickLock;
struct dlg_text_box;
struct eCharacterCategory;
struct eCharacterType;
struct ePainType;
struct eProjectileType;
struct ePropTypes;
struct eStateType;
struct eel_colony;
struct eel_hole;
struct event_mgr;
struct fog_plane;
struct fog_volume;
struct fogmode;
struct forge_puzzle;
struct fork;
struct fx_object;
struct gas_pipe;
struct geom;
struct globals;
struct hud;
struct info_overlay;
struct internal;
struct io_device;
struct irect;
struct key;
struct layer_mgr;
struct level;
struct level_cloudsburst;
struct level_hobbiton;
struct level_laketown;
struct level_lonelymountain;
struct level_mirkwood;
struct level_overhill;
struct level_roastmutton;
struct level_smaug;
struct level_swordlight;
struct light;
struct line_seg;
struct load_trigger;
struct lockGadgets;
struct lonely_mountain_fx;
struct marker;
struct memcard_hardware;
struct memcard_op;
struct mine_cart_ride;
struct music_mgr;
struct music_trigger;
struct nav_point;
struct nav_state;
struct obj_mgr;
struct object;
struct occluder_mgr;
struct one_shot_light;
struct path;
struct pickup;
struct plane;
struct platform_puzzle;
struct play_surface;
struct pool;
struct pool_implementation;
struct prop;
struct property;
struct property_desc;
struct push_box;
struct radian3;
struct rawanim;
struct render_mgr;
struct rhandle;
struct rigid_instance;
struct rope;
struct rsc_mgr;
struct save_mgr;
struct save_pedestal;
struct shadow;
struct simple_anim_player;
struct skybox;
struct slider;
struct smart_2dsprite;
struct spatial_dbase;
struct special_surfaces;
struct state;
struct static_textin_loader;
struct string_mgr;
struct subtitle_mgr;
struct system;
struct text_in;
struct tile_puzzle;
struct tile_type;
struct token_stream;
struct treasure_chest;
struct treeleaf_cluster;
struct trigger;
struct type;
struct ui_check;
struct ui_control;
struct ui_dialog;
struct ui_dlg_list;
struct ui_fx_mgr;
struct ui_fx_render_order;
struct ui_manager;
struct ui_slider;
struct ui_win;
struct uncompressed_parameters;
struct unsigned___int64;
struct view;
struct vm_arglist;
struct volume;
struct wall;
struct water;
struct water_puzzle;
struct weather_mgr;
struct web_line;
struct web_wall;
template <class T> struct xarray;   // engine template container (xarray<property_desc>, ...)
struct xbitmap;
struct xcolor;
struct xhandle;
struct xstring;
struct xthread;
struct xwstring;
