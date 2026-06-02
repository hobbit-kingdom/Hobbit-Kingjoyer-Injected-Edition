// ============================================================================
//  menus_sdk.h  —  Frontend / Menus / UI-shell SDK for THE HOBBIT (2003) PC
//  Entropy engine, MSVC, 32-bit (Meridian.exe, preferred base 0x00400000).
//
//  Reverse-engineered modding / trainer SDK. All addresses are absolute PC
//  virtual addresses; resolve them at runtime with meridian::rebase(0xADDR)
//  which applies the current module-base delta vs the analyzed image base.
//
//  This subsystem is the 2D menu/dialog shell the player navigates outside
//  gameplay. Two high-level managers drive everything:
//    * FrontEnd_Mgr  (singleton &DAT_00762ae0) — title / front-end flow.
//    * Pause_Mgr     (singletons &DAT_00763208 / &DAT_0075ba48;
//                     global ptr DAT_0081303c)  — in-game pause book.
//  Both push named dialogs through the global ui_manager (&DAT_00813038),
//  which owns the dialog stack, widget factories, fonts, skins and input.
//
//  Field offsets are CONSOLIDATED across 4 per-chunk analyses (evidence-
//  backed). Offsets marked "?" are lower confidence. The structs are NOT
//  meant to be instantiated; only reinterpret_cast onto live objects.
//
//  This header is designed to compile under MSVC and g++ with
//  `using namespace std;` active — engine type names that collide with std
//  (internal/system/path/list) are global-qualified (::name).
// ============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase, vector2/3/4, xstring/xwstring, Ghidra aliases

// ---- Forward declarations for engine types we don't fully model -------------
// (Most are already declared in meridian_types.h; re-declaring is harmless.)
struct FrontEnd_Mgr;
struct Pause_Mgr;
struct ui_manager;
struct ui_dialog;
struct ui_win;
struct ui_control;
struct ui_slider;
struct ui_check;
struct ui_dlg_list;
struct dlg_main_menu;
struct dlg_buy_sale;
struct dlg_credits;
struct dlg_end_chapter_summary;
struct dlg_LevelMap;
struct dlg_message;
struct dlg_pause_inventory;
struct dlg_pause_questlog;
struct dlg_pause_summary;
struct dlg_text_box;
struct dlg_QuestItemPopUp;
struct dialog_tem;     // ui_manager::dialog_tem
struct irect;          // {int l,t,r,b}  (16 bytes)
struct xcolor;         // packed ARGB (4 bytes)
struct xbitmap;
struct bilbo;

namespace menus_sdk {

// ===========================================================================
//  1. Enums  (recovered state-machine ids)
// ===========================================================================

// FrontEnd_Mgr+0x78 — title/front-end flow state (Update switch).
enum class FrontEndState : int32_t {
    PressStart      = 1,   // RunPressStartScreen attract loop
    // 2,4,6,8 = transition steps between the odd "settled" states
    Options         = 3,
    MainMenu        = 5,
    LevelSelect     = 7,
    PageTurnsDone   = 0x0b,
    DemoLoop        = 0x11, // UpdateAfterLevel
    PageTurnsCont   = 0x13, // StartPageTurnNarration "continue page-turns"
};

// Pause_Mgr+0xc28 — active pause page (Update switch cases 1..9) and the
// modal substate ids pushed by the overlay openers.
enum class PausePage : int32_t {
    TextBox        = 10,   // Pause_Mgr::TextBox
    LockPick       = 4,    // Pause_Mgr::PickLocks
    SaveKiosk      = 9,    // Pause_Mgr::SaveKiosk
    QuestItemPopUp = 0x0c, // Pause_Mgr::ActivateQuestLogPopup
};

// ===========================================================================
//  2. Struct layouts (reinterpret_cast onto live objects; do NOT instantiate)
//     #pragma pack(1) so explicit byte padding lands members at true offsets.
// ===========================================================================

// ---- FrontEnd_Mgr  (singleton &DAT_00762ae0) -----------------------------
#pragma pack(push, 1)
struct FrontEnd_Mgr_layout {
    uint8_t _pad000[0x70 - 0x00];     // 0x000
    int32_t  initFlag;                // 0x070  PreGame sets =1
    uint8_t _pad074[0x78 - 0x74];     // 0x074
    int32_t  state;                   // 0x078  FrontEndState (Update switch)
    int32_t  currentDialogId;         // 0x07c  -1 = none; also pageTurnIndex (1..0xc)
    int32_t  subState;                // 0x080  PreGame =0
    uint32_t field84;                 // 0x084  render param
    uint8_t _pad088[0x14c - 0x88];    // 0x088
    uint8_t  elements[0x1ac - 0x14c]; // 0x14c  Element[], stride 0x30 (volume/fade UI elems)
    int32_t  activeElementIndex;      // 0x1ac  index into elements[]
    uint8_t _pad1b0[0x1c4 - 0x1b0];   // 0x1b0
    float    normalizedValue;         // 0x1c4  clamped [0,1] volume/fade
    uint8_t _pad1c8[0x504 - 0x1c8];   // 0x1c8
    char     chapterNameBuf[0x604 - 0x504]; // 0x504 BuildChapterLevelName dest
    char     levelNameBuf[0x704 - 0x604];   // 0x604 Update case7 level/dreamworld string
    int32_t  field704;                // 0x704  PreGame clears
    int32_t  field708;                // 0x708  PreGame clears
    int32_t  field70c;                // 0x70c  PreGame sets -1
    int32_t  quitRequested;           // 0x710  Update sets 1 on exit
    uint8_t _pad714[0x718 - 0x714];   // 0x714
    uint8_t  rect[0x728 - 0x718];     // 0x718  irect (full-screen)
};
#pragma pack(pop)

// ---- Pause_Mgr  (singletons &DAT_00763208 / &DAT_0075ba48) ----------------
// Note: +0x15c is aliased — IsPaused reads it as a paused-flag int, while
// CloseSubMenu treats it as an owned sub-dialog pointer. Same physical bytes.
#pragma pack(push, 1)
struct Pause_Mgr_layout {
    int32_t  treasureChestsCount;     // 0x000  summary.txt ItemCounts
    int32_t  couragePtsCount;         // 0x004
    int32_t  mainQuestCount;          // 0x008
    int32_t  totalSPThisLevel;        // 0x00c
    int32_t  initFlag;                // 0x010  Init=1
    int32_t  overlayActive;           // 0x014  set 1 by TextBox/PickLocks/SaveKiosk
    uint8_t  inventoryPartWidgets[0x15c - 0x18]; // 0x018 widget[45], stride 0x20
    int32_t  isPaused;                // 0x15c  IsPaused() != 0  (alias: activeSubDialog*)
    uint8_t _pad160[0x394 - 0x160];   // 0x160
    int32_t  closeRequestFlag;        // 0x394  CloseSubMenu sets 1
    uint8_t _pad398[0x4b8 - 0x398];   // 0x398
    uint8_t  backArrowBmp[0x4f8 - 0x4b8];  // 0x4b8  xbitmap
    uint8_t  bookBackgroundBmp[0x518 - 0x4f8]; // 0x4f8 xbitmap
    uint8_t  nextArrowBmp[0x5d8 - 0x518];  // 0x518  xbitmap
    uint8_t  secondaryWidgets[0xc18 - 0x5d8]; // 0x5d8 widget[49], stride 0x20
    float    cachedScreenW;           // 0xc18  resize detect
    float    cachedScreenH;           // 0xc1c
    uint8_t _padc20[0xc28 - 0xc20];   // 0xc20
    int32_t  currentPage;             // 0xc28  PausePage (Update switch 1..9)
    int32_t  previousPage;            // 0xc2c  SetCurrentPage saves old (Back)
    uint8_t _padc30[0xccc - 0xc30];   // 0xc30
    int32_t  questPopupFlag1;         // 0xccc  ActivateQuestLogPopup=1
    int32_t  questPopupActive;        // 0xcd0  ActivateQuestLogPopup=1
};
#pragma pack(pop)

// ---- ui_win  (base widget) ------------------------------------------------
#pragma pack(push, 1)
struct ui_win_layout {
    uint8_t _pad00[0x44 - 0x00];      // 0x00  vtable + parent/child + flags + label
    uint8_t  position[0x54 - 0x44];   // 0x44  irect {l,t,r,b} (16 bytes)
    // Notable vtable SLOT offsets (not data): +0x3c OnValueChanged/OnNotify,
    // +0x6c OnPadNavigate. Used by ui_slider::OnPadNavigate.
};
#pragma pack(pop)

// ---- ui_slider ------------------------------------------------------------
#pragma pack(push, 1)
struct ui_slider_layout {
    uint8_t _pad00[0x0c - 0x00];      // 0x00
    uint32_t parent;                  // 0x0c  ui_win* parent (value-changed/base-nav vtbls)
    uint8_t _pad10[0x10c - 0x10];     // 0x10
    int32_t  minValue;                // 0x10c
    int32_t  maxValue;                // 0x110  default 100
    int32_t  step;                    // 0x114  base nav delta
    int32_t  accelStep;               // 0x118  *=10 per accel cycle
    int32_t  accelStepMax;            // 0x11c  accel cap
    int32_t  value;                   // 0x120  current value
    uint8_t _pad124[0x128 - 0x124];   // 0x124
    float    fraction;                // 0x128  (value-min)/(max-min)
    int32_t  playSfx;                 // 0x12c  gates VolumeFader_SFX
};
#pragma pack(pop)

// ---- ui_dialog (embedded-slider sub-control region) -----------------------
#pragma pack(push, 1)
struct ui_dialog_sliderbox {
    uint8_t _pad00[0xe8 - 0x00];      // 0x00
    uint32_t sliderBarBmp;            // 0xe8  xbitmap*
    uint32_t sliderThumbBmp;          // 0xec  xbitmap*
    uint8_t _padf0[0x110 - 0xf0];     // 0xf0
    int32_t  sliderMax;               // 0x110  =100
    int32_t  sliderLargeStep;         // 0x114  =10
    int32_t  sliderSmallStep;         // 0x118  =1
    int32_t  sliderStep2;             // 0x11c  =1
};
#pragma pack(pop)

// ---- ui_dlg_list ----------------------------------------------------------
#pragma pack(push, 1)
struct ui_dlg_list_layout {
    uint8_t _pad00[0x48 - 0x00];      // 0x00
    int32_t  listTopPx;               // 0x48
    uint8_t _pad4c[0x50 - 0x4c];      // 0x4c
    int32_t  listBottomPx;            // 0x50  visibleRows = (bottom-top-8)/16
    uint8_t _pad54[0xa0 - 0x54];      // 0x54
    int32_t  flags;                   // 0xa0  Render sets 0x292
    uint8_t _pada4[0xf8 - 0xa4];      // 0xa4
    uint32_t bmpFrame;                // 0xf8  xbitmap* "frame"
    uint32_t bmpArrowDown;            // 0xfc  "sb_arrowdown"
    uint32_t bmpArrowUp;              // 0x100 "sb_arrowup"
    uint32_t bmpContainer;            // 0x104 "sb_container"
    uint32_t bmpThumb;                // 0x108 "sb_thumb"
    uint8_t _pad10c[0x174 - 0x10c];   // 0x10c
    int32_t  selIndex;                // 0x174  init -1
    int32_t  hoverIndex;              // 0x178  init -1
    uint8_t _pad17c[0x180 - 0x17c];   // 0x17c
    int32_t  visibleRows;             // 0x180  (bottom-top-8)/16
};
#pragma pack(pop)

// ---- ui_check / ui_text_grid  (render routine @ 0x006a96b0) ---------------
#pragma pack(push, 1)
struct ui_check_layout {
    uint8_t _pad00[0x50 - 0x00];      // 0x00
    uint8_t  bitmap[0x6c - 0x50];     // 0x50  xbitmap
    uint8_t  useBitmapSize;           // 0x6c  0 -> use fields else bitmap header
    uint8_t _pad6d[0x70 - 0x6d];      // 0x6d
    int32_t  cols;                    // 0x70
    int32_t  rows;                    // 0x74
    int32_t  lineHeight;              // 0x78
    int32_t  maxCellWidth;            // 0x7c
    uint8_t _pad80[0x84 - 0x80];      // 0x80
    int32_t  rowCountMinus1;          // 0x84
    // 0x88  cellBuffer byte[0xc00] (3072) cleared. NOTE: the cellRecords[]
    // region documented by the analysis at 0x14c (x,y,width tuples, stride
    // 0xc) lies INSIDE this 0x88..0xc88 span — the two are overlapping
    // interpretations of the same physical bytes, so cellRecords is not a
    // separate member here.
    uint8_t  cellBuffer[0xc00];       // 0x88  (ends at 0xc88)
};
#pragma pack(pop)

// ---- dlg_main_menu  (size 0x190) ------------------------------------------
#pragma pack(push, 1)
struct dlg_main_menu_layout {
    uint8_t _pad000[0x15c - 0x00];    // 0x000  ui_dialog base
    uint32_t ctrlNewGame;             // 0x15c  ui_control* (focus default)
    uint32_t ctrlOptions;             // 0x160
    uint32_t ctrlControls;            // 0x164
    uint32_t ctrlCredits;             // 0x168
    uint32_t ctrlContinue;            // 0x16c  disabled when DAT_007600ec==0
    uint32_t ctrlLoad;                // 0x170  disabled with Continue
    uint8_t _pad174[0x184 - 0x174];   // 0x174
    uint32_t ctrlQuit;                // 0x184
    uint32_t ctrlExtra;               // 0x188
};
#pragma pack(pop)

// ---- dlg_buy_sale ---------------------------------------------------------
#pragma pack(push, 1)
struct dlg_buy_sale_layout {
    uint8_t _pad000[0x158 - 0x00];    // 0x000
    float    slot0_y;                 // 0x158  grid slot 0 (stride 0x10)
    float    slot0_x;                 // 0x15c
    float    slot0_w;                 // 0x160  64.0
    float    slot0_h;                 // 0x164  64.0
    uint8_t _pad168[0x518 - 0x168];   // 0x168  remaining grid slots
    float    cursorCol;               // 0x518  dpad +/-1, +/-6
    float    cursorRow;               // 0x51c  vertical dpad
    uint8_t _pad520[0x55c - 0x520];   // 0x520
    uint32_t ctrlLeave;               // 0x55c  ui_control* (Leave vendor)
    uint8_t _pad560[0x56c - 0x560];   // 0x560
    int32_t  msgBoxResult;            // 0x56c  1=confirm / 2=cancel
    uint8_t _pad570[0x5bc - 0x570];   // 0x570
    int32_t  msgBoxHandle;            // 0x5bc  created mcmessage dialog
    uint8_t _pad5c0[0x5c4 - 0x5c0];   // 0x5c0
    int32_t  purchaseConfirmPending;  // 0x5c4
    int16_t  openDialogCount;         // 0x5c8  inc/dec around msgbox
    uint8_t _pad5ca[0x5cc - 0x5ca];   // 0x5ca
    int32_t  pendingPurchaseId;       // 0x5cc
    int32_t  leaveConfirmPending;     // 0x5d0  also pendingMsg (OnUpdate)
};
#pragma pack(pop)

// ---- dlg_pause_questlog  (size 0xb68) -------------------------------------
#pragma pack(push, 1)
struct dlg_pause_questlog_layout {
    uint8_t _pad000[0x168 - 0x00];    // 0x000
    int32_t  scrollOffset;            // 0x168
    uint8_t _pad16c[0x174 - 0x16c];   // 0x16c
    int32_t  numQuests;               // 0x174  GetNumberOfQuests()
    int32_t  questSlotIndex[30];      // 0x178  init -1 (0x1e entries, stride 4)
    uint8_t _pad1f0[0x1f4 - 0x1f0];   // 0x1f0  (questItemIndices ends at 0x1f0)
    int32_t  childWidgetA;            // 0x1f4  GetControl handle (== 500 decimal)
    int32_t  childWidgetB;            // 0x1f8  GetControl handle
    int32_t  childWidgetC;            // 0x1fc  GetControl handle
};
#pragma pack(pop)

// ---- dlg_credits  (size 0x190) --------------------------------------------
#pragma pack(push, 1)
struct dlg_credits_layout {
    uint8_t _pad000[0x158 - 0x00];    // 0x000
    int32_t  scrollWidget;            // 0x158  child handle
    uint8_t _pad15c[0x160 - 0x15c];   // 0x15c
    int32_t  scrollState;             // 0x160  cleared
    uint8_t _pad164[0x170 - 0x164];   // 0x164
    float    scrollSpeed;             // 0x170  1.0
    uint8_t _pad174[0x178 - 0x174];   // 0x174
    uint32_t stringTable;             // 0x178  "credits" string-table ptr
};
#pragma pack(pop)

// ---- dlg_end_chapter_summary  (size 0x190) --------------------------------
#pragma pack(push, 1)
struct dlg_end_chapter_summary_layout {
    uint8_t _pad000[0x158 - 0x00];    // 0x000
    uint32_t ctrlContinue;            // 0x158  GetControl(1)
    uint32_t ctrlMain;                // 0x15c  GetControl(0) + focus
    int32_t  startCourage;            // 0x160  snapshot Has(0x18)
    int32_t  tallyCourage;            // 0x164  accumulator
    int32_t  startSilver;             // 0x168  snapshot Has(9)
    uint8_t _pad16c[0x170 - 0x16c];   // 0x16c
    int32_t  startItem0x19;           // 0x170  snapshot Has(0x19)
    uint8_t _pad174[0x178 - 0x174];   // 0x174
    int32_t  startQuestsFinished;     // 0x178  GetNumQuestsFinished()
    uint8_t _pad17c[0x180 - 0x17c];   // 0x17c
    float    tallyAnimTimer;          // 0x180  15.0
};
#pragma pack(pop)

// ---- dlg_message ----------------------------------------------------------
#pragma pack(push, 1)
struct dlg_message_layout {
    uint8_t _pad000[0x158 - 0x00];    // 0x000
    uint32_t ctrlButton1;             // 0x158  shown if label non-empty
    uint32_t ctrlButton2;             // 0x15c  shown + focus
    uint8_t _pad160[0x1ac - 0x160];   // 0x160
    uint8_t  textColor[0x1b0 - 0x1ac];// 0x1ac  xcolor (4 bytes)
    uint32_t resultOut;               // 0x1b0  int* (zeroed)
    float    field1b4;                // 0x1b4  -1.0
    int32_t  flags;                   // 0x1b8
    uint8_t _pad1bc[0x1c8 - 0x1bc];   // 0x1bc
    double   startTime;               // 0x1c8  auto-close timeout base
};
#pragma pack(pop)

// ---- dlg_LevelMap  (size 0x1c4) -------------------------------------------
#pragma pack(push, 1)
struct dlg_LevelMap_layout {
    uint8_t _pad000[0x158 - 0x00];    // 0x000
    uint32_t ctrlNode0;               // 0x158  Narrator_PT01
    uint32_t ctrlNode1;               // 0x15c  Narrator_PT02
    uint32_t ctrlNode2;               // 0x160  Narrator_PT03
    uint32_t ctrlNode3;               // 0x164  Narrator_PT04
    uint32_t ctrlNode4;               // 0x168  Narrator_PT05
    uint32_t ctrlNode5;               // 0x16c  Narrator_PT06
    uint32_t ctrlNode6;               // 0x170  Narrator_PT07
    uint8_t _pad174[0x1bc - 0x174];   // 0x174
    uint32_t ctrlAux;                 // 0x1bc
    uint32_t ctrlContinue;            // 0x1c0  page-turn + UpdateAfterLevel
};
#pragma pack(pop)

// ---- dlg_QuestItemPopUp  (embedded in bilbo at +0x4ee0) -------------------
#pragma pack(push, 1)
struct dlg_QuestItemPopUp_layout {
    uint64_t itemGuid;                // 0x000  Init stores; Update GetSlotFromGuid
    int32_t  active;                  // 0x008  Init=1; Render early-out
    int32_t  questItemCount;          // 0x00c  collected count
    int32_t  cursorMoveTimer;         // 0x010  CursorMove SFX gate
    int32_t  questItemIndices[30];    // 0x014  -1 sentinel + Has()&IsQuestItem
    uint8_t _pad08c[0x090 - 0x8c];    // 0x08c
    int32_t  selectedIndex;           // 0x090  clamp to DAT_00762690-1
    uint8_t _pad094[0x144 - 0x94];    // 0x094
    float    modelScale;              // 0x144  2.0
    uint8_t _pad148[0x9c8 - 0x148];   // 0x148
    int32_t  firstFrameFlag;          // 0x9c8  init 1; cleared once
    int32_t  leftEdge;                // 0x9cc  keycodes 0x7b/0x165
    int32_t  leftHeld;                // 0x9d0
    int32_t  rightEdge;               // 0x9d4  keycodes 0x7d/0x16d
    int32_t  rightHeld;               // 0x9d8
};
#pragma pack(pop)

// ===========================================================================
//  3. Address constants (resolved EAs from the analysis)
// ===========================================================================
namespace addr {
    // Singletons / globals (data addresses).
    inline constexpr std::uintptr_t FRONTEND_MGR_SINGLETON = 0x00762ae0;
    inline constexpr std::uintptr_t PAUSE_MGR_SINGLETON     = 0x00763208; // book/page mgr
    inline constexpr std::uintptr_t PAUSE_MGR_ALT_SINGLETON = 0x0075ba48; // second instance
    inline constexpr std::uintptr_t UI_MANAGER_GLOBAL       = 0x00813038;
    inline constexpr std::uintptr_t UI_MANAGER_GLOBAL_PTR   = 0x0081303c; // ptr to pause mgr / ui mgr

    // FrontEnd_Mgr methods.
    inline constexpr std::uintptr_t FrontEnd_Update                 = 0x0052b560;
    inline constexpr std::uintptr_t FrontEnd_UpdateAfterLevel       = 0x0052ae30;
    inline constexpr std::uintptr_t FrontEnd_E3_AfterGameParty      = 0x0052c080;
    inline constexpr std::uintptr_t FrontEnd_PreGame_CheckMemoryCard= 0x0052a7b0;
    inline constexpr std::uintptr_t FrontEnd_BuildChapterLevelName  = 0x0052a670; // was ReadErrorHandler
    inline constexpr std::uintptr_t FrontEnd_StartPageTurnNarration = 0x0052b310;
    inline constexpr std::uintptr_t FrontEnd_SetNormalizedValue     = 0x00532c80;

    // Pause_Mgr methods.
    inline constexpr std::uintptr_t Pause_Init                  = 0x0052c8c0;
    inline constexpr std::uintptr_t Pause_Kill                  = 0x0052c870;
    inline constexpr std::uintptr_t Pause_Update                = 0x0052d1a0;
    inline constexpr std::uintptr_t Pause_UpdateSummaryStats    = 0x0052cb70;
    inline constexpr std::uintptr_t Pause_RenderMainWindow      = 0x0052cd20;
    inline constexpr std::uintptr_t Pause_RenderBookArrows      = 0x0052cf40;
    inline constexpr std::uintptr_t Pause_ActivateQuestLogPopup = 0x0052da60;
    inline constexpr std::uintptr_t Pause_TextBox               = 0x0052d9b0;
    inline constexpr std::uintptr_t Pause_PickLocks             = 0x0052d910;
    inline constexpr std::uintptr_t Pause_SaveKiosk             = 0x0052d960;
    inline constexpr std::uintptr_t Pause_SetInventoryPartsTexture = 0x0052db00;
    inline constexpr std::uintptr_t Pause_IsPaused              = 0x005268d0;
    inline constexpr std::uintptr_t Pause_CloseSubMenu          = 0x00526600;
    inline constexpr std::uintptr_t Pause_SetCurrentPage        = 0x0052db90;

    // ui_manager / widgets.
    inline constexpr std::uintptr_t UiManager_Init        = 0x0069e460;
    inline constexpr std::uintptr_t UiWin_GetPosition     = 0x005c0150;
    inline constexpr std::uintptr_t UiSlider_OnPadNavigate= 0x006a5cc0;
    inline constexpr std::uintptr_t UiTextGrid_Render     = 0x006a96b0; // was ui_check::Render
    inline constexpr std::uintptr_t UiDlgList_Render      = 0x006a4020;
    inline constexpr std::uintptr_t UiDialog_InitSliderControl = 0x006a5a20; // was GotoControl
    inline constexpr std::uintptr_t UiDlgList_Register    = 0x006a6130;
    inline constexpr std::uintptr_t PtrList_Clear         = 0x006a1760;

    // dlg_* screens.
    inline constexpr std::uintptr_t MainMenu_Create        = 0x00514620;
    inline constexpr std::uintptr_t BuySale_Render         = 0x00504aa0;
    inline constexpr std::uintptr_t BuySale_OnUpdate       = 0x00506db0;
    inline constexpr std::uintptr_t BuySale_OnPadSelect    = 0x005066c0;
    inline constexpr std::uintptr_t BuySale_OnPadHelp      = 0x00506650;
    inline constexpr std::uintptr_t BuySale_OptionBox      = 0x00507e00;
    inline constexpr std::uintptr_t PauseInv_Render        = 0x0050fff0;
    inline constexpr std::uintptr_t PauseInv_OnUpdate      = 0x00511cf0;
    inline constexpr std::uintptr_t PauseInv_GetInfoString = 0x00510fa0;
    inline constexpr std::uintptr_t PauseSummary_Render    = 0x0051b100;
    inline constexpr std::uintptr_t QuestLog_Create        = 0x00520170;
    inline constexpr std::uintptr_t QuestLog_Render        = 0x005207a0;
    inline constexpr std::uintptr_t LevelMap_Create        = 0x00513770;
    inline constexpr std::uintptr_t LevelMap_OnPadSelect   = 0x00513ea0;
    inline constexpr std::uintptr_t Credits_Create         = 0x00509bf0;
    inline constexpr std::uintptr_t EndChapter_Create      = 0x0050a540;
    inline constexpr std::uintptr_t Message_Configure      = 0x00515db0;
    inline constexpr std::uintptr_t TextBox_SetString      = 0x00524360;
    // mcmessage confirm box: the ONLY dialog family with selectable Yes/No buttons.
    inline constexpr std::uintptr_t ShowMessageBox         = 0x0052f420; // generic Yes/No box opener (ret 0x18, 6 args)
    inline constexpr std::uintptr_t McMessage_Configure    = 0x005150a0; // dlg_mcmessage::Configure (9 args; called internally)

    // dlg_QuestItemPopUp.
    inline constexpr std::uintptr_t QuestItemPopUp_Init    = 0x0051ee60;
    inline constexpr std::uintptr_t QuestItemPopUp_Update  = 0x0051efa0;
    inline constexpr std::uintptr_t QuestItemPopUp_Render  = 0x0051f4d0;

    // SystemMenu / startup screens.
    inline constexpr std::uintptr_t SystemMenu_Build       = 0x00500ae0;
    inline constexpr std::uintptr_t SystemMenu_NukeNearby  = 0x00501730;
    inline constexpr std::uintptr_t LegalScreen            = 0x004fb310;
    inline constexpr std::uintptr_t RunPressStartScreen    = 0x0051e860;
    inline constexpr std::uintptr_t Pause_RunModalScreen   = 0x0052b120; // was SetUnplugged
}

// ===========================================================================
//  4. Typed wrappers
//     __thiscall methods take the object pointer as the first arg.
// ===========================================================================
namespace fn {

// ---- singletons ----------------------------------------------------------
inline FrontEnd_Mgr* GetFrontEndMgr() {
    return reinterpret_cast<FrontEnd_Mgr*>(meridian::rebase(addr::FRONTEND_MGR_SINGLETON));
}
inline Pause_Mgr* GetPauseMgr() {
    return reinterpret_cast<Pause_Mgr*>(meridian::rebase(addr::PAUSE_MGR_SINGLETON));
}
inline ui_manager* GetUiManager() {
    // The global at DAT_00813038 is the ui_manager instance itself.
    return reinterpret_cast<ui_manager*>(meridian::rebase(addr::UI_MANAGER_GLOBAL));
}

// ---- FrontEnd_Mgr --------------------------------------------------------
inline void FrontEnd_Update(FrontEnd_Mgr* p, float dt) {
    reinterpret_cast<void(__thiscall*)(FrontEnd_Mgr*, float)>(
        meridian::rebase(addr::FrontEnd_Update))(p, dt);
}
inline void FrontEnd_UpdateAfterLevel(FrontEnd_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(FrontEnd_Mgr*)>(
        meridian::rebase(addr::FrontEnd_UpdateAfterLevel))(p);
}
inline void FrontEnd_PreGame_CheckMemoryCard(FrontEnd_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(FrontEnd_Mgr*)>(
        meridian::rebase(addr::FrontEnd_PreGame_CheckMemoryCard))(p);
}
// Maps chapter index (this+0x7c) to chapter dir/level name into outBuf.
inline void FrontEnd_BuildChapterLevelName(FrontEnd_Mgr* p, char* outBuf) {
    reinterpret_cast<void(__thiscall*)(FrontEnd_Mgr*, char*)>(
        meridian::rebase(addr::FrontEnd_BuildChapterLevelName))(p, outBuf);
}
inline void FrontEnd_StartPageTurnNarration(FrontEnd_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(FrontEnd_Mgr*)>(
        meridian::rebase(addr::FrontEnd_StartPageTurnNarration))(p);
}
// Clamp value to [0,1], store at +0x1c4, apply to active element. Returns clamp.
inline float FrontEnd_SetNormalizedValue(FrontEnd_Mgr* p, float value) {
    return reinterpret_cast<float(__thiscall*)(FrontEnd_Mgr*, float)>(
        meridian::rebase(addr::FrontEnd_SetNormalizedValue))(p, value);
}

// ---- Pause_Mgr -----------------------------------------------------------
inline int Pause_Init(Pause_Mgr* p) {
    return reinterpret_cast<int(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_Init))(p);
}
inline void Pause_Kill(Pause_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_Kill))(p);
}
inline void Pause_Update(Pause_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_Update))(p);
}
inline void Pause_UpdateSummaryStats(Pause_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_UpdateSummaryStats))(p);
}
inline void Pause_RenderMainWindow(Pause_Mgr* p, int param) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*, int)>(
        meridian::rebase(addr::Pause_RenderMainWindow))(p, param);
}
inline void Pause_RenderBookArrows(Pause_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_RenderBookArrows))(p);
}
inline void Pause_ActivateQuestLogPopup(Pause_Mgr* p, uint64_t itemGuid) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*, uint64_t)>(
        meridian::rebase(addr::Pause_ActivateQuestLogPopup))(p, itemGuid);
}
// title, body : wide (UTF-16) string pointers.
inline void Pause_TextBox(Pause_Mgr* p, const uint16_t* title, const uint16_t* body) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*, const uint16_t*, const uint16_t*)>(
        meridian::rebase(addr::Pause_TextBox))(p, title, body);
}
inline void Pause_PickLocks(Pause_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_PickLocks))(p);
}
inline void Pause_SaveKiosk(Pause_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_SaveKiosk))(p);
}
inline void Pause_SetInventoryPartsTexture(Pause_Mgr* p, int slot) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*, int)>(
        meridian::rebase(addr::Pause_SetInventoryPartsTexture))(p, slot);
}
inline int Pause_IsPaused(Pause_Mgr* p) {
    return reinterpret_cast<int(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_IsPaused))(p);
}
inline void Pause_CloseSubMenu(Pause_Mgr* p) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*)>(
        meridian::rebase(addr::Pause_CloseSubMenu))(p);
}
inline void Pause_SetCurrentPage(Pause_Mgr* p, int page) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*, int)>(
        meridian::rebase(addr::Pause_SetCurrentPage))(p, page);
}

// ---- ui_manager / widgets ------------------------------------------------
inline int UiManager_Init(ui_manager* p) {
    return reinterpret_cast<int(__thiscall*)(ui_manager*)>(
        meridian::rebase(addr::UiManager_Init))(p);
}
// Returns the widget rect (irect*) at ui_win+0x44.
inline const ::irect* UiWin_GetPosition(ui_win* p) {
    return reinterpret_cast<const ::irect*(__thiscall*)(ui_win*)>(
        meridian::rebase(addr::UiWin_GetPosition))(p);
}
// dir: 2=left/decrement, 3=right/increment. repeat: key-repeat flag.
inline void UiSlider_OnPadNavigate(ui_slider* p, ui_win* focused, int dir, int repeat, int extra) {
    reinterpret_cast<void(__thiscall*)(ui_slider*, ui_win*, int, int, int)>(
        meridian::rebase(addr::UiSlider_OnPadNavigate))(p, focused, dir, repeat, extra);
}
inline void UiDlgList_Render(ui_dlg_list* p, int x, int y) {
    reinterpret_cast<void(__thiscall*)(ui_dlg_list*, int, int)>(
        meridian::rebase(addr::UiDlgList_Render))(p, x, y);
}

// ---- dlg_* screen handlers -----------------------------------------------
inline void BuySale_Render(dlg_buy_sale* p, int x, int y) {
    reinterpret_cast<void(__thiscall*)(dlg_buy_sale*, int, int)>(
        meridian::rebase(addr::BuySale_Render))(p, x, y);
}
inline void BuySale_OnUpdate(dlg_buy_sale* p, ui_win* w, float dt) {
    reinterpret_cast<void(__thiscall*)(dlg_buy_sale*, ui_win*, float)>(
        meridian::rebase(addr::BuySale_OnUpdate))(p, w, dt);
}
inline void BuySale_OnPadSelect(dlg_buy_sale* p, ui_win* w) {
    reinterpret_cast<void(__thiscall*)(dlg_buy_sale*, ui_win*)>(
        meridian::rebase(addr::BuySale_OnPadSelect))(p, w);
}
inline void PauseInv_Render(dlg_pause_inventory* p, int x, int y) {
    reinterpret_cast<void(__thiscall*)(dlg_pause_inventory*, int, int)>(
        meridian::rebase(addr::PauseInv_Render))(p, x, y);
}
// Returns localized info string (wide) for an inventory display slot index.
inline const uint16_t* PauseInv_GetInfoString(dlg_pause_inventory* p, int slot) {
    return reinterpret_cast<const uint16_t*(__thiscall*)(dlg_pause_inventory*, int)>(
        meridian::rebase(addr::PauseInv_GetInfoString))(p, slot);
}
inline void QuestLog_Render(dlg_pause_questlog* p, int x, int y) {
    reinterpret_cast<void(__thiscall*)(dlg_pause_questlog*, int, int)>(
        meridian::rebase(addr::QuestLog_Render))(p, x, y);
}
inline void LevelMap_OnPadSelect(dlg_LevelMap* p, ui_win* w) {
    reinterpret_cast<void(__thiscall*)(dlg_LevelMap*, ui_win*)>(
        meridian::rebase(addr::LevelMap_OnPadSelect))(p, w);
}
// Set the two wide-string lines shown by the text box (title/body).
inline void TextBox_SetString(dlg_text_box* p, const uint16_t* line1, const uint16_t* line2) {
    reinterpret_cast<void(__thiscall*)(dlg_text_box*, const uint16_t*, const uint16_t*)>(
        meridian::rebase(addr::TextBox_SetString))(p, line1, line2);
}

// ---- dlg_QuestItemPopUp --------------------------------------------------
inline void QuestItemPopUp_Init(dlg_QuestItemPopUp* p, uint64_t itemGuid) {
    reinterpret_cast<void(__thiscall*)(dlg_QuestItemPopUp*, uint64_t)>(
        meridian::rebase(addr::QuestItemPopUp_Init))(p, itemGuid);
}
inline int QuestItemPopUp_Update(dlg_QuestItemPopUp* p) {
    return reinterpret_cast<int(__thiscall*)(dlg_QuestItemPopUp*)>(
        meridian::rebase(addr::QuestItemPopUp_Update))(p);
}
inline void QuestItemPopUp_Render(dlg_QuestItemPopUp* p) {
    reinterpret_cast<void(__thiscall*)(dlg_QuestItemPopUp*)>(
        meridian::rebase(addr::QuestItemPopUp_Render))(p);
}

// ---- standalone __cdecl startup screens ----------------------------------
inline int LegalScreen() {
    return reinterpret_cast<int(__cdecl*)()>(meridian::rebase(addr::LegalScreen))();
}
inline void RunPressStartScreen() {
    reinterpret_cast<void(__cdecl*)()>(meridian::rebase(addr::RunPressStartScreen))();
}
inline int SystemMenu_Cheat_NukeNearbyEnemies() {
    return reinterpret_cast<int(__cdecl*)()>(meridian::rebase(addr::SystemMenu_NukeNearby))();
}

// ---- incomplete-by-value helpers -----------------------------------------
// SystemMenu::Build is __thiscall on an incomplete SystemMenu type; call by
// raw signature against the live menu object:
//   void __thiscall SystemMenu::Build(SystemMenu* this);
inline void* SystemMenu_Build_at() { return meridian::rebase(addr::SystemMenu_Build); }

// Pause_Mgr::RunModalScreen (was SetUnplugged) — true arity is 3 args:
//   void __thiscall Pause_Mgr::RunModalScreen(Pause_Mgr* this, int dialogId,
//                                             int waitForInput, float timeoutSecs);
inline void Pause_RunModalScreen(Pause_Mgr* p, int dialogId, int waitForInput, float timeoutSecs) {
    reinterpret_cast<void(__thiscall*)(Pause_Mgr*, int, int, float)>(
        meridian::rebase(addr::Pause_RunModalScreen))(p, dialogId, waitForInput, timeoutSecs);
}

// PtrList::Clear — drain an indexed collection (the dialog/widget stack).
inline void PtrList_Clear(void* list) {
    reinterpret_cast<void(__cdecl*)(void*)>(meridian::rebase(addr::PtrList_Clear))(list);
}

// ---- mcmessage confirm box (the ONLY Yes/No-with-buttons dialog) -----------
// dlg_message (page-10 dlg_text_box too) are passive TEXT-ONLY popups with no
// buttons and no readable result. Buttons live in the 'mcmessage' template.
// FUN_0052f420 is the generic opener (proven by the save Overwrite/Delete
// confirms): it centers a box, opens 'mcmessage', sets two text lines + Yes/No
// labels, and wires the chosen-button index into *(owner + 0x74).
//   owner   : any object with usable slots at +0x20 (modal counter), +0x70
//             (dialog ptr) and +0x74 (result int). A zeroed buffer works (the
//             "close existing" branch is skipped while +0x70 == 0).
//   title/body : wide (UTF-16) strings; pass nullptr for an empty line.
//   yesLabel/noLabel : wide strings, or nullptr to default to IDS_YES / IDS_NO.
//   The game always passes p5=1, p6=0 here.
// Result is written to owner+0x74 asynchronously when the player picks:
//   0 = still open, 1 = first button (Yes/confirm), 2 = second button (No/cancel).
inline void ShowMessageBox(void* owner, const uint16_t* title, const uint16_t* body,
                           const uint16_t* yesLabel, const uint16_t* noLabel,
                           int p5 = 1, int p6 = 0) {
    reinterpret_cast<void(__thiscall*)(void*, const uint16_t*, const uint16_t*,
                                       const uint16_t*, const uint16_t*, int, int)>(
        meridian::rebase(addr::ShowMessageBox))(owner, title, body, yesLabel, noLabel, p5, p6);
}

// Self-contained confirm box: owns a static buffer, returns the result slot
// address so you can poll it. Usage:
//   int* r = menus_sdk::fn::ConfirmBox(L"Quit?", L"Return to menu?");
//   ... each frame: if (*r == 1) {confirmed} else if (*r == 2) {cancelled}
inline int* ConfirmBox(const uint16_t* title, const uint16_t* body,
                       const uint16_t* yesLabel = nullptr, const uint16_t* noLabel = nullptr) {
    static unsigned char owner[0x80] = {0};   // slots used: +0x20,+0x70,+0x74
    *reinterpret_cast<int*>(owner + 0x74) = 0; // clear previous result
    ShowMessageBox(owner, title, body, yesLabel, noLabel, 1, 0);
    return reinterpret_cast<int*>(owner + 0x74);
}

} // namespace fn

// ===========================================================================
//  5. Usage recipes
// ===========================================================================
//
//  --- Read whether the game is paused ----------------------------------
//      using namespace menus_sdk;
//      Pause_Mgr* pm = fn::GetPauseMgr();
//      if (fn::Pause_IsPaused(pm)) { /* in pause book */ }
//
//  --- Inspect the active pause page (no call needed) -------------------
//      auto* L = reinterpret_cast<Pause_Mgr_layout*>(fn::GetPauseMgr());
//      PausePage page = static_cast<PausePage>(L->currentPage);
//
//  --- Open the save kiosk overlay --------------------------------------
//      fn::Pause_SaveKiosk(fn::GetPauseMgr());   // pushes substate 9
//
//  --- Read a bound slider value (no call) ------------------------------
//      auto* s = reinterpret_cast<ui_slider_layout*>(someSliderWin);
//      int vol = s->value;           // 0..max
//      float frac = s->fraction;     // normalized 0..1
//
//  --- Read the main-menu control pointers ------------------------------
//      auto* mm = reinterpret_cast<dlg_main_menu_layout*>(activeMainMenuDlg);
//      void* newGameCtrl = reinterpret_cast<void*>(mm->ctrlNewGame);
//
//  --- Force-apply a normalized volume/fade on the front-end ------------
//      float clamped = fn::FrontEnd_SetNormalizedValue(fn::GetFrontEndMgr(), 0.5f);
//
//  NOTE: layout structs are for reinterpret_cast onto LIVE objects only.
//  Do not instantiate them; sizes/padding are approximate where marked "?".
// ===========================================================================

} // namespace menus_sdk
