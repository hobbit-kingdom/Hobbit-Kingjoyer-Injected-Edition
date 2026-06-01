// AUTO-GENERATED Meridian SDK (The Hobbit 2003, PC build).  Do not edit by hand.
// 1441 named functions across 317 classes. Addresses are absolute (image base 0x400000, ASLR off).
// Typed wrappers are emitted when all types are complete; otherwise an *_at() address
// accessor + the raw signature is provided (cast it yourself with your own types).
#pragma once
#include <cstdint>
#include "meridian_types.h"   // meridian::rebase, value types, xarray<T>, opaque forward decls

// ===== AIAction =====  (3 functions)  ->  namespace AIAction_
namespace AIAction_ {
  // 0x005CD4C0  conf=0.97  ?EnumerateProperties@AIAction@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::AIAction *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::AIAction * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005CD4C0))(a0, a1); }
  // 0x005CC820  conf=0.97  ?EnumerateSaveProperties@AIAction@@QAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateSaveProperties_t = void (__thiscall*)(::AIAction *, ::xarray< ::property_desc> *);
  inline void EnumerateSaveProperties(::AIAction * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateSaveProperties_t>(meridian::rebase(0x005CC820))(a0, a1); }
  // 0x005CC4B0  conf=0.97  ?GetProperty@AIAction@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::AIAction *, char *);
  inline ::property GetProperty(::AIAction * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005CC4B0))(a0, a1); }
} // AIAction_

// ===== AIManager =====  (9 functions)  ->  namespace AIManager_
namespace AIManager_ {
  // 0x0055E1C0  conf=0.636  ?ActionFiltered@AIManager@@IAEHPAUActionInfo@@@Z
  using ActionFiltered_t = int (__thiscall*)(::AIManager *, ::ActionInfo *);
  inline int ActionFiltered(::AIManager * a0, ::ActionInfo * a1) { return reinterpret_cast<ActionFiltered_t>(meridian::rebase(0x0055E1C0))(a0, a1); }
  // 0x00563550  conf=0.97  ?EnumerateProperties@AIManager@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::AIManager *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::AIManager * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00563550))(a0, a1); }
  // 0x005657A0  conf=0.97  ?GetProperty@AIManager@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::AIManager *, char *);
  inline ::property GetProperty(::AIManager * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005657A0))(a0, a1); }
  // 0x0055EB10  conf=0.97  ?Kill@AIManager@@QAEXXZ
  using Kill_t = void (__thiscall*)(::AIManager *);
  inline void Kill(::AIManager * a0) { reinterpret_cast<Kill_t>(meridian::rebase(0x0055EB10))(a0); }
  // 0x00562900  conf=0.97  ?OnImport@AIManager@@QAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::AIManager *, ::bin_in *);
  inline void OnImport(::AIManager * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00562900))(a0, a1); }
  // 0x00564940  conf=0.638  ?SetProperty@AIManager@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::AIManager *, char *, ::property *);
  inline int SetProperty(::AIManager * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00564940))(a0, a1, a2); }
  // 0x0055F050  conf=0.97  ?SetupActionList@AIManager@@QAEXXZ
  using SetupActionList_t = void (__thiscall*)(::AIManager *);
  inline void SetupActionList(::AIManager * a0) { reinterpret_cast<SetupActionList_t>(meridian::rebase(0x0055F050))(a0); }
  // 0x005605E0  conf=0.97  ?SetupTriggerList@AIManager@@QAEXXZ
  using SetupTriggerList_t = void (__thiscall*)(::AIManager *);
  inline void SetupTriggerList(::AIManager * a0) { reinterpret_cast<SetupTriggerList_t>(meridian::rebase(0x005605E0))(a0); }
  // 0x005620D0  conf=0.557  ?TriggerFiltered@AIManager@@IAEHPAUTriggerInfo@@@Z
  using TriggerFiltered_t = int (__thiscall*)(::AIManager *, ::TriggerInfo *);
  inline int TriggerFiltered(::AIManager * a0, ::TriggerInfo * a1) { return reinterpret_cast<TriggerFiltered_t>(meridian::rebase(0x005620D0))(a0, a1); }
} // AIManager_

// ===== AIState =====  (3 functions)  ->  namespace AIState_
namespace AIState_ {
  // 0x005BEC40  conf=0.97  ?CalcFlinchType@AIState@@UAEHXZ
  using CalcFlinchType_t = int (__thiscall*)(::AIState *);
  inline int CalcFlinchType(::AIState * a0) { return reinterpret_cast<CalcFlinchType_t>(meridian::rebase(0x005BEC40))(a0); }
  // 0x005BEDE0  conf=0.93  ?GetPhaseName@AIState@@UAEPBDXZ
  using GetPhaseName_t = char * (__thiscall*)(::AIState *);
  inline char * GetPhaseName(::AIState * a0) { return reinterpret_cast<GetPhaseName_t>(meridian::rebase(0x005BEDE0))(a0); }
  // 0x005BF100  conf=0.97  ?GetProperty@AIState@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::AIState *, char *);
  inline ::property GetProperty(::AIState * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005BF100))(a0, a1); }
} // AIState_

// ===== AITrigger =====  (2 functions)  ->  namespace AITrigger_
namespace AITrigger_ {
  // 0x005F1E70  conf=0.97  ?OnImport@AITrigger@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::AITrigger *, ::bin_in *);
  inline void OnImport(::AITrigger * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005F1E70))(a0, a1); }
  // 0x005F1CF0  conf=0.97  ?SetProperty@AITrigger@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::AITrigger *, char *, ::property *);
  inline int SetProperty(::AITrigger * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F1CF0))(a0, a1, a2); }
} // AITrigger_

// ===== ActionActivateHealthMeter =====  (1 functions)  ->  namespace ActionActivateHealthMeter_
namespace ActionActivateHealthMeter_ {
  // 0x005EBA90  conf=0.97  ?SetProperty@ActionActivateHealthMeter@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionActivateHealthMeter *, char *, ::property *);
  inline int SetProperty(::ActionActivateHealthMeter * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005EBA90))(a0, a1, a2); }
} // ActionActivateHealthMeter_

// ===== ActionActivateTrigger =====  (1 functions)  ->  namespace ActionActivateTrigger_
namespace ActionActivateTrigger_ {
  // 0x005CD280  conf=0.93  ?SetProperty@ActionActivateTrigger@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionActivateTrigger *, char *, ::property *);
  inline int SetProperty(::ActionActivateTrigger * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005CD280))(a0, a1, a2); }
} // ActionActivateTrigger_

// ===== ActionAmbientAudioTrigger =====  (2 functions)  ->  namespace ActionAmbientAudioTrigger_
namespace ActionAmbientAudioTrigger_ {
  // 0x005CF140  conf=0.97  ?GetProperty@ActionAmbientAudioTrigger@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionAmbientAudioTrigger *, char *);
  inline ::property GetProperty(::ActionAmbientAudioTrigger * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005CF140))(a0, a1); }
  // 0x005CF080  conf=0.97  ?SetProperty@ActionAmbientAudioTrigger@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionAmbientAudioTrigger *, char *, ::property *);
  inline int SetProperty(::ActionAmbientAudioTrigger * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005CF080))(a0, a1, a2); }
} // ActionAmbientAudioTrigger_

// ===== ActionBeornCrossBridge =====  (2 functions)  ->  namespace ActionBeornCrossBridge_
namespace ActionBeornCrossBridge_ {
  // 0x005EB520  conf=0.628  ?GetProperty@ActionBeornCrossBridge@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionBeornCrossBridge *, char *);
  inline ::property GetProperty(::ActionBeornCrossBridge * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005EB520))(a0, a1); }
  // 0x005EB150  conf=0.97  ?SetProperty@ActionBeornCrossBridge@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionBeornCrossBridge *, char *, ::property *);
  inline int SetProperty(::ActionBeornCrossBridge * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005EB150))(a0, a1, a2); }
} // ActionBeornCrossBridge_

// ===== ActionDisableAudioEmitter =====  (1 functions)  ->  namespace ActionDisableAudioEmitter_
namespace ActionDisableAudioEmitter_ {
  // 0x005EEAD0  conf=0.97  ?GetProperty@ActionDisableAudioEmitter@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionDisableAudioEmitter *, char *);
  inline ::property GetProperty(::ActionDisableAudioEmitter * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005EEAD0))(a0, a1); }
} // ActionDisableAudioEmitter_

// ===== ActionFinishBilboQuest =====  (1 functions)  ->  namespace ActionFinishBilboQuest_
namespace ActionFinishBilboQuest_ {
  // 0x0047A9D0  conf=0.637  ?EnumerateProperties@ActionFinishBilboQuest@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionFinishBilboQuest *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionFinishBilboQuest * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0047A9D0))(a0, a1); }
} // ActionFinishBilboQuest_

// ===== ActionFinishMainBilboQuest =====  (3 functions)  ->  namespace ActionFinishMainBilboQuest_
namespace ActionFinishMainBilboQuest_ {
  // 0x005E4580  conf=0.97  ?Execute@ActionFinishMainBilboQuest@@UAEXXZ
  using Execute_t = void (__thiscall*)(::ActionFinishMainBilboQuest *);
  inline void Execute(::ActionFinishMainBilboQuest * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x005E4580))(a0); }
  // 0x005E5590  conf=0.97  ?SetProperty@ActionFinishMainBilboQuest@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionFinishMainBilboQuest *, char *, ::property *);
  inline int SetProperty(::ActionFinishMainBilboQuest * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E5590))(a0, a1, a2); }
  // 0x005E5130  conf=0.629  ?ValidData@ActionFinishMainBilboQuest@@UAEHXZ
  using ValidData_t = int (__thiscall*)(::ActionFinishMainBilboQuest *);
  inline int ValidData(::ActionFinishMainBilboQuest * a0) { return reinterpret_cast<ValidData_t>(meridian::rebase(0x005E5130))(a0); }
} // ActionFinishMainBilboQuest_

// ===== ActionGiveBilboQuest =====  (3 functions)  ->  namespace ActionGiveBilboQuest_
namespace ActionGiveBilboQuest_ {
  // 0x005DF070  conf=0.97  ?Execute@ActionGiveBilboQuest@@UAEXXZ
  using Execute_t = void (__thiscall*)(::ActionGiveBilboQuest *);
  inline void Execute(::ActionGiveBilboQuest * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x005DF070))(a0); }
  // 0x005DFFF0  conf=0.624  ?GetProperty@ActionGiveBilboQuest@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionGiveBilboQuest *, char *);
  inline ::property GetProperty(::ActionGiveBilboQuest * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005DFFF0))(a0, a1); }
  // 0x005DFB90  conf=0.97  ?SetProperty@ActionGiveBilboQuest@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionGiveBilboQuest *, char *, ::property *);
  inline int SetProperty(::ActionGiveBilboQuest * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005DFB90))(a0, a1, a2); }
} // ActionGiveBilboQuest_

// ===== ActionInfoOverlay =====  (2 functions)  ->  namespace ActionInfoOverlay_
namespace ActionInfoOverlay_ {
  // 0x005DC0B0  conf=0.97  ?EnumerateProperties@ActionInfoOverlay@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionInfoOverlay *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionInfoOverlay * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005DC0B0))(a0, a1); }
  // 0x005DBFA0  conf=0.97  ?Execute@ActionInfoOverlay@@UAEXXZ
  using Execute_t = void (__thiscall*)(::ActionInfoOverlay *);
  inline void Execute(::ActionInfoOverlay * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x005DBFA0))(a0); }
} // ActionInfoOverlay_

// ===== ActionLerpScreenDistortAmp =====  (2 functions)  ->  namespace ActionLerpScreenDistortAmp_
namespace ActionLerpScreenDistortAmp_ {
  // 0x005EF860  conf=0.627  ?GetProperty@ActionLerpScreenDistortAmp@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionLerpScreenDistortAmp *, char *);
  inline ::property GetProperty(::ActionLerpScreenDistortAmp * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005EF860))(a0, a1); }
  // 0x005EF490  conf=0.97  ?SetProperty@ActionLerpScreenDistortAmp@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionLerpScreenDistortAmp *, char *, ::property *);
  inline int SetProperty(::ActionLerpScreenDistortAmp * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005EF490))(a0, a1, a2); }
} // ActionLerpScreenDistortAmp_

// ===== ActionModifyHealth =====  (1 functions)  ->  namespace ActionModifyHealth_
namespace ActionModifyHealth_ {
  // 0x005DA840  conf=0.97  ?SetProperty@ActionModifyHealth@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionModifyHealth *, char *, ::property *);
  inline int SetProperty(::ActionModifyHealth * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005DA840))(a0, a1, a2); }
} // ActionModifyHealth_

// ===== ActionMoveObject =====  (5 functions)  ->  namespace ActionMoveObject_
namespace ActionMoveObject_ {
  // 0x005D9530  conf=0.97  ?EnumerateProperties@ActionMoveObject@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionMoveObject *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionMoveObject * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005D9530))(a0, a1); }
  // 0x005D9430  conf=0.97  ?Execute@ActionMoveObject@@UAEXXZ
  using Execute_t = void (__thiscall*)(::ActionMoveObject *);
  inline void Execute(::ActionMoveObject * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x005D9430))(a0); }
  // 0x005D9A70  conf=0.95  ?GetProperty@ActionMoveObject@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionMoveObject *, char *);
  inline ::property GetProperty(::ActionMoveObject * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005D9A70))(a0, a1); }
  // 0x005D9CA0  conf=0.97  ?OnImport@ActionMoveObject@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::ActionMoveObject *, ::bin_in *);
  inline void OnImport(::ActionMoveObject * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005D9CA0))(a0, a1); }
  // 0x005DB140  conf=0.97  ?SetProperty@ActionMoveObject@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionMoveObject *, char *, ::property *);
  inline int SetProperty(::ActionMoveObject * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005DB140))(a0, a1, a2); }
} // ActionMoveObject_

// ===== ActionMusicTrigger =====  (1 functions)  ->  namespace ActionMusicTrigger_
namespace ActionMusicTrigger_ {
  // 0x005CEB10  conf=0.641  ?GetProperty@ActionMusicTrigger@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionMusicTrigger *, char *);
  inline ::property GetProperty(::ActionMusicTrigger * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005CEB10))(a0, a1); }
} // ActionMusicTrigger_

// ===== ActionRigidInstAnim =====  (3 functions)  ->  namespace ActionRigidInstAnim_
namespace ActionRigidInstAnim_ {
  // 0x005E8740  conf=0.95  ?EnumerateProperties@ActionRigidInstAnim@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionRigidInstAnim *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionRigidInstAnim * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005E8740))(a0, a1); }
  // 0x004790E0  conf=0.653  ?GetProperty@ActionRigidInstAnim@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionRigidInstAnim *, char *);
  inline ::property GetProperty(::ActionRigidInstAnim * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004790E0))(a0, a1); }
  // 0x005E72E0  conf=0.97  ?SetProperty@ActionRigidInstAnim@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionRigidInstAnim *, char *, ::property *);
  inline int SetProperty(::ActionRigidInstAnim * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E72E0))(a0, a1, a2); }
} // ActionRigidInstAnim_

// ===== ActionRigidInstanceHidden =====  (2 functions)  ->  namespace ActionRigidInstanceHidden_
namespace ActionRigidInstanceHidden_ {
  // 0x005F01A0  conf=0.628  ?GetProperty@ActionRigidInstanceHidden@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionRigidInstanceHidden *, char *);
  inline ::property GetProperty(::ActionRigidInstanceHidden * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005F01A0))(a0, a1); }
  // 0x005EFDD0  conf=0.97  ?SetProperty@ActionRigidInstanceHidden@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionRigidInstanceHidden *, char *, ::property *);
  inline int SetProperty(::ActionRigidInstanceHidden * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005EFDD0))(a0, a1, a2); }
} // ActionRigidInstanceHidden_

// ===== ActionRigidInstanceHoistable =====  (1 functions)  ->  namespace ActionRigidInstanceHoistable_
namespace ActionRigidInstanceHoistable_ {
  // 0x005CD250  conf=0.93  ?SetProperty@ActionRigidInstanceHoistable@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionRigidInstanceHoistable *, char *, ::property *);
  inline int SetProperty(::ActionRigidInstanceHoistable * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005CD250))(a0, a1, a2); }
} // ActionRigidInstanceHoistable_

// ===== ActionSetCinema =====  (2 functions)  ->  namespace ActionSetCinema_
namespace ActionSetCinema_ {
  // 0x005DD460  conf=0.721  ?SetProperty@ActionSetCinema@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetCinema *, char *, ::property *);
  inline int SetProperty(::ActionSetCinema * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005DD460))(a0, a1, a2); }
  // 0x005DDED0  conf=0.97  ?ValidData@ActionSetCinema@@UAEHXZ
  using ValidData_t = int (__thiscall*)(::ActionSetCinema *);
  inline int ValidData(::ActionSetCinema * a0) { return reinterpret_cast<ValidData_t>(meridian::rebase(0x005DDED0))(a0); }
} // ActionSetCinema_

// ===== ActionSetGoalList =====  (1 functions)  ->  namespace ActionSetGoalList_
namespace ActionSetGoalList_ {
  // 0x005D08A0  conf=0.97  ?Execute@ActionSetGoalList@@UAEXXZ
  using Execute_t = void (__thiscall*)(::ActionSetGoalList *);
  inline void Execute(::ActionSetGoalList * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x005D08A0))(a0); }
} // ActionSetGoalList_

// ===== ActionSetIdleAnim =====  (2 functions)  ->  namespace ActionSetIdleAnim_
namespace ActionSetIdleAnim_ {
  // 0x005E09F0  conf=0.628  ?GetProperty@ActionSetIdleAnim@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetIdleAnim *, char *);
  inline ::property GetProperty(::ActionSetIdleAnim * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005E09F0))(a0, a1); }
  // 0x005E0600  conf=0.97  ?SetProperty@ActionSetIdleAnim@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetIdleAnim *, char *, ::property *);
  inline int SetProperty(::ActionSetIdleAnim * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E0600))(a0, a1, a2); }
} // ActionSetIdleAnim_

// ===== ActionSetInventory =====  (2 functions)  ->  namespace ActionSetInventory_
namespace ActionSetInventory_ {
  // 0x005D3D60  conf=0.97  ?EnumerateProperties@ActionSetInventory@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionSetInventory *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionSetInventory * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005D3D60))(a0, a1); }
  // 0x005D3C10  conf=0.97  ?Execute@ActionSetInventory@@UAEXXZ
  using Execute_t = void (__thiscall*)(::ActionSetInventory *);
  inline void Execute(::ActionSetInventory * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x005D3C10))(a0); }
} // ActionSetInventory_

// ===== ActionSetInvulnerability =====  (2 functions)  ->  namespace ActionSetInvulnerability_
namespace ActionSetInvulnerability_ {
  // 0x005EABE0  conf=0.628  ?GetProperty@ActionSetInvulnerability@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetInvulnerability *, char *);
  inline ::property GetProperty(::ActionSetInvulnerability * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005EABE0))(a0, a1); }
  // 0x005EA810  conf=0.97  ?SetProperty@ActionSetInvulnerability@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetInvulnerability *, char *, ::property *);
  inline int SetProperty(::ActionSetInvulnerability * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005EA810))(a0, a1, a2); }
} // ActionSetInvulnerability_

// ===== ActionSetNPCAnimController =====  (2 functions)  ->  namespace ActionSetNPCAnimController_
namespace ActionSetNPCAnimController_ {
  // 0x005F9110  conf=0.672  ?GetProperty@ActionSetNPCAnimController@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetNPCAnimController *, char *);
  inline ::property GetProperty(::ActionSetNPCAnimController * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005F9110))(a0, a1); }
  // 0x005E3B20  conf=0.97  ?SetProperty@ActionSetNPCAnimController@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetNPCAnimController *, char *, ::property *);
  inline int SetProperty(::ActionSetNPCAnimController * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E3B20))(a0, a1, a2); }
} // ActionSetNPCAnimController_

// ===== ActionSetNPCCollision =====  (1 functions)  ->  namespace ActionSetNPCCollision_
namespace ActionSetNPCCollision_ {
  // 0x005E51F0  conf=0.619  ?GetProperty@ActionSetNPCCollision@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetNPCCollision *, char *);
  inline ::property GetProperty(::ActionSetNPCCollision * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005E51F0))(a0, a1); }
} // ActionSetNPCCollision_

// ===== ActionSetNPCRender =====  (1 functions)  ->  namespace ActionSetNPCRender_
namespace ActionSetNPCRender_ {
  // 0x005E3240  conf=0.97  ?SetProperty@ActionSetNPCRender@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetNPCRender *, char *, ::property *);
  inline int SetProperty(::ActionSetNPCRender * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E3240))(a0, a1, a2); }
} // ActionSetNPCRender_

// ===== ActionSetNPCRenderProp =====  (2 functions)  ->  namespace ActionSetNPCRenderProp_
namespace ActionSetNPCRenderProp_ {
  // 0x005F0BE0  conf=0.628  ?GetProperty@ActionSetNPCRenderProp@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetNPCRenderProp *, char *);
  inline ::property GetProperty(::ActionSetNPCRenderProp * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005F0BE0))(a0, a1); }
  // 0x005F0810  conf=0.97  ?SetProperty@ActionSetNPCRenderProp@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetNPCRenderProp *, char *, ::property *);
  inline int SetProperty(::ActionSetNPCRenderProp * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F0810))(a0, a1, a2); }
} // ActionSetNPCRenderProp_

// ===== ActionSetNPCRootToPosition =====  (1 functions)  ->  namespace ActionSetNPCRootToPosition_
namespace ActionSetNPCRootToPosition_ {
  // 0x005EBB90  conf=0.97  ?OnImport@ActionSetNPCRootToPosition@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::ActionSetNPCRootToPosition *, ::bin_in *);
  inline void OnImport(::ActionSetNPCRootToPosition * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005EBB90))(a0, a1); }
} // ActionSetNPCRootToPosition_

// ===== ActionSetNPCRunAI =====  (2 functions)  ->  namespace ActionSetNPCRunAI_
namespace ActionSetNPCRunAI_ {
  // 0x005E1370  conf=0.628  ?GetProperty@ActionSetNPCRunAI@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetNPCRunAI *, char *);
  inline ::property GetProperty(::ActionSetNPCRunAI * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005E1370))(a0, a1); }
  // 0x005E0F80  conf=0.97  ?SetProperty@ActionSetNPCRunAI@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetNPCRunAI *, char *, ::property *);
  inline int SetProperty(::ActionSetNPCRunAI * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E0F80))(a0, a1, a2); }
} // ActionSetNPCRunAI_

// ===== ActionSetNPCSenses =====  (2 functions)  ->  namespace ActionSetNPCSenses_
namespace ActionSetNPCSenses_ {
  // 0x005E1CD0  conf=0.628  ?GetProperty@ActionSetNPCSenses@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetNPCSenses *, char *);
  inline ::property GetProperty(::ActionSetNPCSenses * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005E1CD0))(a0, a1); }
  // 0x005E18E0  conf=0.97  ?SetProperty@ActionSetNPCSenses@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetNPCSenses *, char *, ::property *);
  inline int SetProperty(::ActionSetNPCSenses * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E18E0))(a0, a1, a2); }
} // ActionSetNPCSenses_

// ===== ActionSetNPCStateController =====  (2 functions)  ->  namespace ActionSetNPCStateController_
namespace ActionSetNPCStateController_ {
  // 0x005E2630  conf=0.628  ?GetProperty@ActionSetNPCStateController@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetNPCStateController *, char *);
  inline ::property GetProperty(::ActionSetNPCStateController * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005E2630))(a0, a1); }
  // 0x005E2240  conf=0.97  ?SetProperty@ActionSetNPCStateController@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetNPCStateController *, char *, ::property *);
  inline int SetProperty(::ActionSetNPCStateController * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E2240))(a0, a1, a2); }
} // ActionSetNPCStateController_

// ===== ActionSetObjectCollisionFlags =====  (2 functions)  ->  namespace ActionSetObjectCollisionFlags_
namespace ActionSetObjectCollisionFlags_ {
  // 0x005E9010  conf=0.712  ?EnumerateProperties@ActionSetObjectCollisionFlags@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionSetObjectCollisionFlags *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionSetObjectCollisionFlags * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005E9010))(a0, a1); }
  // 0x005E9EC0  conf=0.95  ?SetProperty@ActionSetObjectCollisionFlags@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetObjectCollisionFlags *, char *, ::property *);
  inline int SetProperty(::ActionSetObjectCollisionFlags * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E9EC0))(a0, a1, a2); }
} // ActionSetObjectCollisionFlags_

// ===== ActionSetRopeLength =====  (2 functions)  ->  namespace ActionSetRopeLength_
namespace ActionSetRopeLength_ {
  // 0x005E8370  conf=0.97  ?SetProperty@ActionSetRopeLength@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetRopeLength *, char *, ::property *);
  inline int SetProperty(::ActionSetRopeLength * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005E8370))(a0, a1, a2); }
  // 0x005E8170  conf=0.97  ?UsesObject@ActionSetRopeLength@@UAEH_K@Z
  using UsesObject_t = int (__thiscall*)(::ActionSetRopeLength *, __uint64);
  inline int UsesObject(::ActionSetRopeLength * a0, __uint64 a1) { return reinterpret_cast<UsesObject_t>(meridian::rebase(0x005E8170))(a0, a1); }
} // ActionSetRopeLength_

// ===== ActionSetState =====  (2 functions)  ->  namespace ActionSetState_
namespace ActionSetState_ {
  // 0x005D7F00  conf=0.97  ??0ActionSetState@@QAE@H@Z
  using ctor_t = undefined (__thiscall*)(::ActionSetState *, int);
  inline undefined ctor(::ActionSetState * a0, int a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x005D7F00))(a0, a1); }
  // 0x005D8DF0  conf=0.622  ?GetProperty@ActionSetState@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetState *, char *);
  inline ::property GetProperty(::ActionSetState * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005D8DF0))(a0, a1); }
} // ActionSetState_

// ===== ActionSetTeam =====  (2 functions)  ->  namespace ActionSetTeam_
namespace ActionSetTeam_ {
  // 0x005D0070  conf=0.629  ?GetProperty@ActionSetTeam@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSetTeam *, char *);
  inline ::property GetProperty(::ActionSetTeam * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005D0070))(a0, a1); }
  // 0x005CFC50  conf=0.97  ?SetProperty@ActionSetTeam@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSetTeam *, char *, ::property *);
  inline int SetProperty(::ActionSetTeam * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005CFC50))(a0, a1, a2); }
} // ActionSetTeam_

// ===== ActionSpawnCP =====  (2 functions)  ->  namespace ActionSpawnCP_
namespace ActionSpawnCP_ {
  // 0x005DB200  conf=0.97  ?EnumerateProperties@ActionSpawnCP@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionSpawnCP *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionSpawnCP * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005DB200))(a0, a1); }
  // 0x005DBE60  conf=0.729  ?SetProperty@ActionSpawnCP@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSpawnCP *, char *, ::property *);
  inline int SetProperty(::ActionSpawnCP * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005DBE60))(a0, a1, a2); }
} // ActionSpawnCP_

// ===== ActionSpawnNPC =====  (4 functions)  ->  namespace ActionSpawnNPC_
namespace ActionSpawnNPC_ {
  // 0x005D6C10  conf=0.97  ?EnumerateProperties@ActionSpawnNPC@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ActionSpawnNPC *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ActionSpawnNPC * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005D6C10))(a0, a1); }
  // 0x005D7420  conf=0.95  ?GetProperty@ActionSpawnNPC@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionSpawnNPC *, char *);
  inline ::property GetProperty(::ActionSpawnNPC * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005D7420))(a0, a1); }
  // 0x005D5950  conf=0.97  ?OnImport@ActionSpawnNPC@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::ActionSpawnNPC *, ::bin_in *);
  inline void OnImport(::ActionSpawnNPC * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005D5950))(a0, a1); }
  // 0x005D61D0  conf=0.97  ?SetProperty@ActionSpawnNPC@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSpawnNPC *, char *, ::property *);
  inline int SetProperty(::ActionSpawnNPC * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005D61D0))(a0, a1, a2); }
} // ActionSpawnNPC_

// ===== ActionStartCinema =====  (1 functions)  ->  namespace ActionStartCinema_
namespace ActionStartCinema_ {
  // 0x005DD0E0  conf=0.97  ?SetProperty@ActionStartCinema@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionStartCinema *, char *, ::property *);
  inline int SetProperty(::ActionStartCinema * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005DD0E0))(a0, a1, a2); }
} // ActionStartCinema_

// ===== ActionStartDialog =====  (1 functions)  ->  namespace ActionStartDialog_
namespace ActionStartDialog_ {
  // 0x005D1880  conf=0.97  ?OnImport@ActionStartDialog@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::ActionStartDialog *, ::bin_in *);
  inline void OnImport(::ActionStartDialog * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005D1880))(a0, a1); }
} // ActionStartDialog_

// ===== ActionSwapCharacters =====  (2 functions)  ->  namespace ActionSwapCharacters_
namespace ActionSwapCharacters_ {
  // 0x005EC6B0  conf=0.97  ?Execute@ActionSwapCharacters@@UAEXXZ
  using Execute_t = void (__thiscall*)(::ActionSwapCharacters *);
  inline void Execute(::ActionSwapCharacters * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x005EC6B0))(a0); }
  // 0x005ED240  conf=0.97  ?SetProperty@ActionSwapCharacters@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ActionSwapCharacters *, char *, ::property *);
  inline int SetProperty(::ActionSwapCharacters * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005ED240))(a0, a1, a2); }
} // ActionSwapCharacters_

// ===== ActionToggleLink =====  (1 functions)  ->  namespace ActionToggleLink_
namespace ActionToggleLink_ {
  // 0x005D8410  conf=0.624  ?GetProperty@ActionToggleLink@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionToggleLink *, char *);
  inline ::property GetProperty(::ActionToggleLink * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005D8410))(a0, a1); }
} // ActionToggleLink_

// ===== ActionToggleMaterialAnimation =====  (1 functions)  ->  namespace ActionToggleMaterialAnimation_
namespace ActionToggleMaterialAnimation_ {
  // 0x005EE6B0  conf=0.621  ?GetProperty@ActionToggleMaterialAnimation@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ActionToggleMaterialAnimation *, char *);
  inline ::property GetProperty(::ActionToggleMaterialAnimation * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005EE6B0))(a0, a1); }
} // ActionToggleMaterialAnimation_

// ===== ActionTriggerSwitch =====  (1 functions)  ->  namespace ActionTriggerSwitch_
namespace ActionTriggerSwitch_ {
  // 0x005CD850  conf=0.97  ?OnImport@ActionTriggerSwitch@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::ActionTriggerSwitch *, ::bin_in *);
  inline void OnImport(::ActionTriggerSwitch * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005CD850))(a0, a1); }
} // ActionTriggerSwitch_

// ===== AlertState =====  (1 functions)  ->  namespace AlertState_
namespace AlertState_ {
  // 0x00638C80  conf=0.97  ?ChangePhase@AlertState@@UAEXH@Z
  using ChangePhase_t = void (__thiscall*)(::AlertState *, int);
  inline void ChangePhase(::AlertState * a0, int a1) { reinterpret_cast<ChangePhase_t>(meridian::rebase(0x00638C80))(a0, a1); }
} // AlertState_

// ===== AmbientAudioMgr =====  (6 functions)  ->  namespace AmbientAudioMgr_
namespace AmbientAudioMgr_ {
  // 0x00452EB0  conf=0.8  ?GetAmbientAudioMgr@@YAPAVAmbientAudioMgr@@XZ
  using GetAmbientAudioMgr_t = ::AmbientAudioMgr * (__cdecl*)();
  inline ::AmbientAudioMgr * GetAmbientAudioMgr() { return reinterpret_cast<GetAmbientAudioMgr_t>(meridian::rebase(0x00452EB0))(); }
  // 0x00453360  conf=0.97  ?Init@AmbientAudioMgr@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::AmbientAudioMgr *, ::vector3 *, ::radian3 *, ::vector3 *, ::bbox *);
  inline void Init(::AmbientAudioMgr * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3, ::bbox * a4) { reinterpret_cast<Init_t>(meridian::rebase(0x00453360))(a0, a1, a2, a3, a4); }
  // 0x00454000  conf=0.85  ?OnExport@AmbientAudioMgr@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::AmbientAudioMgr *, ::bin_out *);
  inline void OnExport(::AmbientAudioMgr * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00454000))(a0, a1); }
  // 0x004540F0  conf=0.85  ?OnImport@AmbientAudioMgr@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::AmbientAudioMgr *, ::bin_in *);
  inline void OnImport(::AmbientAudioMgr * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004540F0))(a0, a1); }
  // 0x00453740  conf=0.97  ?SetDesiredNextTrackByNameFromTrigger@AmbientAudioMgr@@QAEHAAVxstring@@HW4SWITCHTYPE@1@MM@Z
  inline void* SetDesiredNextTrackByNameFromTrigger_at() { return meridian::rebase(0x00453740); } // int __thiscall SetDesiredNextTrackByNameFromTrigger(AmbientAudioMgr *, xstring *, int, SWITCHTYPE, float, float)
  // 0x00453630  conf=0.784  ?SetVolumeTarget@AmbientAudioMgr@@QAEXMMM@Z
  using SetVolumeTarget_t = void (__thiscall*)(::AmbientAudioMgr *, float, float, float);
  inline void SetVolumeTarget(::AmbientAudioMgr * a0, float a1, float a2, float a3) { reinterpret_cast<SetVolumeTarget_t>(meridian::rebase(0x00453630))(a0, a1, a2, a3); }
} // AmbientAudioMgr_

// ===== AttackState =====  (2 functions)  ->  namespace AttackState_
namespace AttackState_ {
  // 0x00637900  conf=0.97  ?ChangePhase@AttackState@@UAEXH@Z
  using ChangePhase_t = void (__thiscall*)(::AttackState *, int);
  inline void ChangePhase(::AttackState * a0, int a1) { reinterpret_cast<ChangePhase_t>(meridian::rebase(0x00637900))(a0, a1); }
  // 0x0062E090  conf=0.97  ?UpdateState@AttackState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x0062E090); } // eStateType __thiscall UpdateState(AttackState *, int)
} // AttackState_

// ===== BeornAlertState =====  (4 functions)  ->  namespace BeornAlertState_
namespace BeornAlertState_ {
  // 0x0060F8C0  conf=0.97  ?ChangePhase@BeornAlertState@@UAEXH@Z
  using ChangePhase_t = void (__thiscall*)(::BeornAlertState *, int);
  inline void ChangePhase(::BeornAlertState * a0, int a1) { reinterpret_cast<ChangePhase_t>(meridian::rebase(0x0060F8C0))(a0, a1); }
  // 0x006115C0  conf=0.97  ?EnumerateProperties@BeornAlertState@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::BeornAlertState *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::BeornAlertState * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x006115C0))(a0, a1); }
  // 0x00610840  conf=0.97  ?SetProperty@BeornAlertState@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::BeornAlertState *, char *, ::property *);
  inline int SetProperty(::BeornAlertState * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00610840))(a0, a1, a2); }
  // 0x0060F720  conf=0.97  ?UpdateState@BeornAlertState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x0060F720); } // eStateType __thiscall UpdateState(BeornAlertState *, int)
} // BeornAlertState_

// ===== Bilbo =====  (2 functions)  ->  namespace Bilbo_
namespace Bilbo_ {
  // 0x0041BCC0  conf=0.782  ?GetBilbo@@YAAAVbilbo@@XZ
  using GetBilbo_t = ::bilbo * (__cdecl*)();
  inline ::bilbo * GetBilbo() { return reinterpret_cast<GetBilbo_t>(meridian::rebase(0x0041BCC0))(); }
  // 0x0041BCD0  conf=0.75  ?GetBilboGuid@@YA_KXZ
  using GetBilboGuid_t = __uint64 (__cdecl*)();
  inline __uint64 GetBilboGuid() { return reinterpret_cast<GetBilboGuid_t>(meridian::rebase(0x0041BCD0))(); }
} // Bilbo_

// ===== BilboCombatState =====  (1 functions)  ->  namespace BilboCombatState_
namespace BilboCombatState_ {
  // 0x00426B90  conf=0.792  ?IsTargetVisible@@YAH_K@Z
  using IsTargetVisible_t = int (__cdecl*)(__uint64);
  inline int IsTargetVisible(__uint64 a0) { return reinterpret_cast<IsTargetVisible_t>(meridian::rebase(0x00426B90))(a0); }
} // BilboCombatState_

// ===== BilboHoistable =====  (1 functions)  ->  namespace BilboHoistable_
namespace BilboHoistable_ {
  // 0x00431660  conf=0.783  ?IsHoistingBlockedByWall@@YAHABUvector3@@0@Z
  using IsHoistingBlockedByWall_t = int (__cdecl*)(::vector3 *, ::vector3 *);
  inline int IsHoistingBlockedByWall(::vector3 * a0, ::vector3 * a1) { return reinterpret_cast<IsHoistingBlockedByWall_t>(meridian::rebase(0x00431660))(a0, a1); }
} // BilboHoistable_

// ===== BolgAttackState =====  (2 functions)  ->  namespace BolgAttackState_
namespace BolgAttackState_ {
  // 0x00613A90  conf=0.97  ?EnumerateProperties@BolgAttackState@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::BolgAttackState *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::BolgAttackState * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00613A90))(a0, a1); }
  // 0x006122F0  conf=0.97  ?UpdateState@BolgAttackState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x006122F0); } // eStateType __thiscall UpdateState(BolgAttackState *, int)
} // BolgAttackState_

// ===== BolgShamanIdleState =====  (1 functions)  ->  namespace BolgShamanIdleState_
namespace BolgShamanIdleState_ {
  // 0x005B97C0  conf=0.93  ?OnExit@BolgShamanIdleState@@UAEXXZ
  using OnExit_t = void (__thiscall*)(::BolgShamanIdleState *);
  inline void OnExit(::BolgShamanIdleState * a0) { reinterpret_cast<OnExit_t>(meridian::rebase(0x005B97C0))(a0); }
} // BolgShamanIdleState_

// ===== BossSpiderIdleState =====  (1 functions)  ->  namespace BossSpiderIdleState_
namespace BossSpiderIdleState_ {
  // 0x0059A6F0  conf=0.85  ?GetProperty@BossSpiderIdleState@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::BossSpiderIdleState *, char *);
  inline ::property GetProperty(::BossSpiderIdleState * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x0059A6F0))(a0, a1); }
} // BossSpiderIdleState_

// ===== BossSpiderWickedAttackState =====  (1 functions)  ->  namespace BossSpiderWickedAttackState_
namespace BossSpiderWickedAttackState_ {
  // 0x00618C20  conf=0.789  ?GetPhaseName@BossSpiderWickedAttackState@@UAEPBDXZ
  using GetPhaseName_t = char * (__thiscall*)(::BossSpiderWickedAttackState *);
  inline char * GetPhaseName(::BossSpiderWickedAttackState * a0) { return reinterpret_cast<GetPhaseName_t>(meridian::rebase(0x00618C20))(a0); }
} // BossSpiderWickedAttackState_

// ===== BossSpiderWrathAttackState =====  (1 functions)  ->  namespace BossSpiderWrathAttackState_
namespace BossSpiderWrathAttackState_ {
  // 0x005AB800  conf=0.795  ?SetProperty@BossSpiderWrathAttackState@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::BossSpiderWrathAttackState *, char *, ::property *);
  inline int SetProperty(::BossSpiderWrathAttackState * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005AB800))(a0, a1, a2); }
} // BossSpiderWrathAttackState_

// ===== BridgeTrollAttackState =====  (2 functions)  ->  namespace BridgeTrollAttackState_
namespace BridgeTrollAttackState_ {
  // 0x0061D6C0  conf=0.97  ?EnumerateProperties@BridgeTrollAttackState@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::BridgeTrollAttackState *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::BridgeTrollAttackState * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0061D6C0))(a0, a1); }
  // 0x0061C6F0  conf=0.97  ?UpdateState@BridgeTrollAttackState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x0061C6F0); } // eStateType __thiscall UpdateState(BridgeTrollAttackState *, int)
} // BridgeTrollAttackState_

// ===== CastAttackState =====  (1 functions)  ->  namespace CastAttackState_
namespace CastAttackState_ {
  // 0x00634E50  conf=0.97  ?UpdateState@CastAttackState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x00634E50); } // eStateType __thiscall UpdateState(CastAttackState *, int)
} // CastAttackState_

// ===== CaveGuardianMinionAttackState =====  (1 functions)  ->  namespace CaveGuardianMinionAttackState_
namespace CaveGuardianMinionAttackState_ {
  // 0x006224B0  conf=0.97  ?SpawnMinions@CaveGuardianMinionAttackState@@IAEXXZ
  using SpawnMinions_t = void (__thiscall*)(::CaveGuardianMinionAttackState *);
  inline void SpawnMinions(::CaveGuardianMinionAttackState * a0) { reinterpret_cast<SpawnMinions_t>(meridian::rebase(0x006224B0))(a0); }
} // CaveGuardianMinionAttackState_

// ===== CaveGuardianRangedAttackState =====  (1 functions)  ->  namespace CaveGuardianRangedAttackState_
namespace CaveGuardianRangedAttackState_ {
  // 0x00620BE0  conf=0.97  ?UpdateState@CaveGuardianRangedAttackState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x00620BE0); } // eStateType __thiscall UpdateState(CaveGuardianRangedAttackState *, int)
} // CaveGuardianRangedAttackState_

// ===== CharacterObject =====  (19 functions)  ->  namespace CharacterObject_
namespace CharacterObject_ {
  // 0x00467710  conf=0.73  ?ApplyEffectToBones@CharacterObject@@QAEXPBD@Z
  using ApplyEffectToBones_t = void (__thiscall*)(::CharacterObject *, char *);
  inline void ApplyEffectToBones(::CharacterObject * a0, char * a1) { reinterpret_cast<ApplyEffectToBones_t>(meridian::rebase(0x00467710))(a0, a1); }
  // 0x00464130  conf=0.721  ??0CharacterObject@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::CharacterObject *);
  inline undefined ctor(::CharacterObject * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x00464130))(a0); }
  // 0x00468250  conf=0.75  ?EndConversationMode@CharacterObject@@UAEXH@Z
  using EndConversationMode_t = void (__thiscall*)(::CharacterObject *, int);
  inline void EndConversationMode(::CharacterObject * a0, int a1) { reinterpret_cast<EndConversationMode_t>(meridian::rebase(0x00468250))(a0, a1); }
  // 0x00467E40  conf=0.75  ?EndTalking@CharacterObject@@UAEXXZ
  using EndTalking_t = void (__thiscall*)(::CharacterObject *);
  inline void EndTalking(::CharacterObject * a0) { reinterpret_cast<EndTalking_t>(meridian::rebase(0x00467E40))(a0); }
  // 0x00469860  conf=0.75  ?GetAnimGroup@CharacterObject@@QAEPBVanim_group@@XZ
  using GetAnimGroup_t = ::anim_group * (__thiscall*)(::CharacterObject *);
  inline ::anim_group * GetAnimGroup(::CharacterObject * a0) { return reinterpret_cast<GetAnimGroup_t>(meridian::rebase(0x00469860))(a0); }
  // 0x00468420  conf=0.8  ?GetAttachedEnemy@CharacterObject@@QAE_KXZ
  using GetAttachedEnemy_t = __uint64 (__thiscall*)(::CharacterObject *);
  inline __uint64 GetAttachedEnemy(::CharacterObject * a0) { return reinterpret_cast<GetAttachedEnemy_t>(meridian::rebase(0x00468420))(a0); }
  // 0x00580A60  conf=0.75  ?GetCharacterCategory@CharacterObject@@QAE?AW4eCharacterCategory@1@XZ
  inline void* GetCharacterCategory_at() { return meridian::rebase(0x00580A60); } // eCharacterCategory __thiscall GetCharacterCategory(CharacterObject *)
  // 0x004675A0  conf=0.732  ?GetCharacterNameFromType@CharacterObject@@QAE?AVxstring@@W4eCharacterType@1@@Z
  inline void* GetCharacterNameFromType_at() { return meridian::rebase(0x004675A0); } // xstring __thiscall GetCharacterNameFromType(CharacterObject *, eCharacterType)
  // 0x00467620  conf=0.97  ?GetCharacterTypeFromName@CharacterObject@@SA?AW4eCharacterType@1@Vxstring@@@Z
  inline void* GetCharacterTypeFromName_at() { return meridian::rebase(0x00467620); } // eCharacterType __cdecl GetCharacterTypeFromName(xstring)
  // 0x00469060  conf=0.782  ?HandleMove@CharacterObject@@QAEXAAUvector3@@ABU2@MMHHH@Z
  using HandleMove_t = void (__thiscall*)(::CharacterObject *, ::vector3 *, ::vector3 *, float, float, int, int, int);
  inline void HandleMove(::CharacterObject * a0, ::vector3 * a1, ::vector3 * a2, float a3, float a4, int a5, int a6, int a7) { reinterpret_cast<HandleMove_t>(meridian::rebase(0x00469060))(a0, a1, a2, a3, a4, a5, a6, a7); }
  // 0x00468410  conf=0.75  ?IncrementDetachCount@CharacterObject@@QAEXXZ
  using IncrementDetachCount_t = void (__thiscall*)(::CharacterObject *);
  inline void IncrementDetachCount(::CharacterObject * a0) { reinterpret_cast<IncrementDetachCount_t>(meridian::rebase(0x00468410))(a0); }
  // 0x004683D0  conf=0.683  ?IsEnemy@CharacterObject@@QAEHPAV1@@Z
  using IsEnemy_t = int (__thiscall*)(::CharacterObject *, ::CharacterObject *);
  inline int IsEnemy(::CharacterObject * a0, ::CharacterObject * a1) { return reinterpret_cast<IsEnemy_t>(meridian::rebase(0x004683D0))(a0, a1); }
  // 0x00467EB0  conf=0.8  ?IsGroundSlippery@CharacterObject@@QAEHXZ
  using IsGroundSlippery_t = int (__thiscall*)(::CharacterObject *);
  inline int IsGroundSlippery(::CharacterObject * a0) { return reinterpret_cast<IsGroundSlippery_t>(meridian::rebase(0x00467EB0))(a0); }
  // 0x00467E90  conf=0.75  ?IsOnStairs@CharacterObject@@QAEHXZ
  using IsOnStairs_t = int (__thiscall*)(::CharacterObject *);
  inline int IsOnStairs(::CharacterObject * a0) { return reinterpret_cast<IsOnStairs_t>(meridian::rebase(0x00467E90))(a0); }
  // 0x00467ED0  conf=0.779  ?OnAdvanceLogic@CharacterObject@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::CharacterObject *, float);
  inline void OnAdvanceLogic(::CharacterObject * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x00467ED0))(a0, a1); }
  // 0x004698C0  conf=0.776  ?ProcessPolyCacheInvalidate@CharacterObject@@QAEHXZ
  using ProcessPolyCacheInvalidate_t = int (__thiscall*)(::CharacterObject *);
  inline int ProcessPolyCacheInvalidate(::CharacterObject * a0) { return reinterpret_cast<ProcessPolyCacheInvalidate_t>(meridian::rebase(0x004698C0))(a0); }
  // 0x00468430  conf=0.75  ?SetAttachedEnemy@CharacterObject@@QAEX_K@Z
  using SetAttachedEnemy_t = void (__thiscall*)(::CharacterObject *, __uint64);
  inline void SetAttachedEnemy(::CharacterObject * a0, __uint64 a1) { reinterpret_cast<SetAttachedEnemy_t>(meridian::rebase(0x00468430))(a0, a1); }
  // 0x00464560  conf=0.97  ?SetupTypeNameArray@CharacterObject@@SAXXZ
  using SetupTypeNameArray_t = void (__cdecl*)();
  inline void SetupTypeNameArray() { reinterpret_cast<SetupTypeNameArray_t>(meridian::rebase(0x00464560))(); }
  // 0x004688E0  conf=0.755  ?SolvePersonalSpace@CharacterObject@@QAEXAAUvector3@@@Z
  using SolvePersonalSpace_t = void (__thiscall*)(::CharacterObject *, ::vector3 *);
  inline void SolvePersonalSpace(::CharacterObject * a0, ::vector3 * a1) { reinterpret_cast<SolvePersonalSpace_t>(meridian::rebase(0x004688E0))(a0, a1); }
} // CharacterObject_

// ===== ChestContents =====  (1 functions)  ->  namespace ChestContents_
namespace ChestContents_ {
  // 0x004D8BB0  conf=0.793  ??0ChestContents@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::ChestContents *);
  inline undefined ctor(::ChestContents * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004D8BB0))(a0); }
} // ChestContents_

// ===== ChickenIdleState =====  (1 functions)  ->  namespace ChickenIdleState_
namespace ChickenIdleState_ {
  // 0x0061DCA0  conf=0.97  ?EnumerateProperties@ChickenIdleState@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::ChickenIdleState *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::ChickenIdleState * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0061DCA0))(a0, a1); }
} // ChickenIdleState_

// ===== Cinema =====  (6 functions)  ->  namespace Cinema_
namespace Cinema_ {
  // 0x004BEA00  conf=0.75  ?IsCinemaBypassQueue@@YAHXZ
  using IsCinemaBypassQueue_t = int (__cdecl*)();
  inline int IsCinemaBypassQueue() { return reinterpret_cast<IsCinemaBypassQueue_t>(meridian::rebase(0x004BEA00))(); }
  // 0x00472E70  conf=0.797  ?IsCinemaDisableControl@@YAHXZ
  using IsCinemaDisableControl_t = int (__cdecl*)();
  inline int IsCinemaDisableControl() { return reinterpret_cast<IsCinemaDisableControl_t>(meridian::rebase(0x00472E70))(); }
  // 0x00472EC0  conf=0.774  ?IsCinemaLowPriority@@YAHXZ
  using IsCinemaLowPriority_t = int (__cdecl*)();
  inline int IsCinemaLowPriority() { return reinterpret_cast<IsCinemaLowPriority_t>(meridian::rebase(0x00472EC0))(); }
  // 0x00472DF0  conf=0.8  ?IsCinemaPlaying@@YAHXZ
  using IsCinemaPlaying_t = int (__cdecl*)();
  inline int IsCinemaPlaying() { return reinterpret_cast<IsCinemaPlaying_t>(meridian::rebase(0x00472DF0))(); }
  // 0x00472FB0  conf=0.75  ?ResetSkipCinemaPressed@@YAXXZ
  using ResetSkipCinemaPressed_t = void (__cdecl*)();
  inline void ResetSkipCinemaPressed() { reinterpret_cast<ResetSkipCinemaPressed_t>(meridian::rebase(0x00472FB0))(); }
  // 0x00472FA0  conf=0.75  ?WasSkipCinemaPressed@@YAHXZ
  using WasSkipCinemaPressed_t = int (__cdecl*)();
  inline int WasSkipCinemaPressed() { return reinterpret_cast<WasSkipCinemaPressed_t>(meridian::rebase(0x00472FA0))(); }
} // Cinema_

// ===== CinemaActions =====  (2 functions)  ->  namespace CinemaActions_
namespace CinemaActions_ {
  // 0x00463D50  conf=0.9  ?PropertyEnumerateRadian3@@YAXAAV?$xarray@Uproperty_desc@@@@PBDIABUradian3@@2@Z
  using PropertyEnumerateRadian3_t = void (__cdecl*)(::xarray< ::property_desc> *, char *, uint, ::radian3 *, ::radian3 *);
  inline void PropertyEnumerateRadian3(::xarray< ::property_desc> * a0, char * a1, uint a2, ::radian3 * a3, ::radian3 * a4) { reinterpret_cast<PropertyEnumerateRadian3_t>(meridian::rebase(0x00463D50))(a0, a1, a2, a3, a4); }
  // 0x00480FF0  conf=0.8  ?PropertyEnumerateVector3@@YAXAAV?$xarray@Uproperty_desc@@@@PBDIUvector3@@2@Z
  using PropertyEnumerateVector3_t = void (__cdecl*)(::xarray< ::property_desc> *, char *, uint, ::vector3, ::vector3);
  inline void PropertyEnumerateVector3(::xarray< ::property_desc> * a0, char * a1, uint a2, ::vector3 a3, ::vector3 a4) { reinterpret_cast<PropertyEnumerateVector3_t>(meridian::rebase(0x00480FF0))(a0, a1, a2, a3, a4); }
} // CinemaActions_

// ===== ConversationMgr =====  (3 functions)  ->  namespace ConversationMgr_
namespace ConversationMgr_ {
  // 0x005A0FA0  conf=0.742  ?GetProperty@ConversationMgr@@QAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::ConversationMgr *, char *);
  inline ::property GetProperty(::ConversationMgr * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005A0FA0))(a0, a1); }
  // 0x0059D750  conf=0.97  ?OnImport@ConversationMgr@@QAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::ConversationMgr *, ::bin_in *);
  inline void OnImport(::ConversationMgr * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0059D750))(a0, a1); }
  // 0x0059ED80  conf=0.739  ?SetProperty@ConversationMgr@@QAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ConversationMgr *, char *, ::property *);
  inline int SetProperty(::ConversationMgr * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0059ED80))(a0, a1, a2); }
} // ConversationMgr_

// ===== CrowIdleState =====  (1 functions)  ->  namespace CrowIdleState_
namespace CrowIdleState_ {
  // 0x0060C870  conf=0.97  ?UpdatePhase@CrowIdleState@@UAEHMH@Z
  using UpdatePhase_t = int (__thiscall*)(::CrowIdleState *, float, int);
  inline int UpdatePhase(::CrowIdleState * a0, float a1, int a2) { return reinterpret_cast<UpdatePhase_t>(meridian::rebase(0x0060C870))(a0, a1, a2); }
} // CrowIdleState_

// ===== EelHole =====  (1 functions)  ->  namespace EelHole_
namespace EelHole_ {
  // 0x004C0310  conf=0.746  ?EelHoleCreator@@YAPAVobject@@XZ
  using EelHoleCreator_t = ::object * (__cdecl*)();
  inline ::object * EelHoleCreator() { return reinterpret_cast<EelHoleCreator_t>(meridian::rebase(0x004C0310))(); }
} // EelHole_

// ===== FXObject =====  (5 functions)  ->  namespace FXObject_
namespace FXObject_ {
  // 0x00488F10  conf=0.702  ?CreateHosted@fx_object@@SA_KPBD_K0ABUradian3@@ABUvector3@@H@Z
  using CreateHosted_t = __uint64 (__cdecl*)(char *, __uint64, char *, ::radian3 *, ::vector3 *, int);
  inline __uint64 CreateHosted(char * a0, __uint64 a1, char * a2, ::radian3 * a3, ::vector3 * a4, int a5) { return reinterpret_cast<CreateHosted_t>(meridian::rebase(0x00488F10))(a0, a1, a2, a3, a4, a5); }
  // 0x00488C30  conf=0.97  ?FXBitmapLoad@@YAHPBDAAPAVxbitmap@@@Z
  using FXBitmapLoad_t = int (__cdecl*)(char *, ::xbitmap * *);
  inline int FXBitmapLoad(char * a0, ::xbitmap * * a1) { return reinterpret_cast<FXBitmapLoad_t>(meridian::rebase(0x00488C30))(a0, a1); }
  // 0x00488D30  conf=0.723  ?FireAndForget@fx_object@@SA_KPBDABUvector3@@ABUradian3@@1@Z
  using FireAndForget_t = __uint64 (__cdecl*)(char *, ::vector3 *, ::radian3 *, ::vector3 *);
  inline __uint64 FireAndForget(char * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3) { return reinterpret_cast<FireAndForget_t>(meridian::rebase(0x00488D30))(a0, a1, a2, a3); }
  // 0x0048B8E0  conf=0.799  ?PropertyEnumerateColor@@YAXAAV?$xarray@Uproperty_desc@@@@PBDI@Z
  using PropertyEnumerateColor_t = void (__cdecl*)(::xarray< ::property_desc> *, char *, uint);
  inline void PropertyEnumerateColor(::xarray< ::property_desc> * a0, char * a1, uint a2) { reinterpret_cast<PropertyEnumerateColor_t>(meridian::rebase(0x0048B8E0))(a0, a1, a2); }
  // 0x0048B7D0  conf=0.85  ?PropertySetRadian3@@YAHPBDABUproperty@@0AAUradian3@@@Z
  using PropertySetRadian3_t = int (__cdecl*)(char *, ::property *, char *, ::radian3 *);
  inline int PropertySetRadian3(char * a0, ::property * a1, char * a2, ::radian3 * a3) { return reinterpret_cast<PropertySetRadian3_t>(meridian::rebase(0x0048B7D0))(a0, a1, a2, a3); }
} // FXObject_

// ===== FrontEnd_Mgr =====  (5 functions)  ->  namespace FrontEnd_Mgr_
namespace FrontEnd_Mgr_ {
  // 0x0052C080  conf=0.97  ?E3_AfterGameParty@FrontEnd_Mgr@@QAEXXZ
  using E3_AfterGameParty_t = void (__thiscall*)(::FrontEnd_Mgr *);
  inline void E3_AfterGameParty(::FrontEnd_Mgr * a0) { reinterpret_cast<E3_AfterGameParty_t>(meridian::rebase(0x0052C080))(a0); }
  // 0x0052A7B0  conf=0.776  ?PreGame_CheckMemoryCard@FrontEnd_Mgr@@QAEXXZ
  using PreGame_CheckMemoryCard_t = void (__thiscall*)(::FrontEnd_Mgr *);
  inline void PreGame_CheckMemoryCard(::FrontEnd_Mgr * a0) { reinterpret_cast<PreGame_CheckMemoryCard_t>(meridian::rebase(0x0052A7B0))(a0); }
  // 0x0052A670  conf=0.97  ?ReadErrorHandler@FrontEnd_Mgr@@KAXXZ
  using ReadErrorHandler_t = void (__cdecl*)();
  inline void ReadErrorHandler() { reinterpret_cast<ReadErrorHandler_t>(meridian::rebase(0x0052A670))(); }
  // 0x0052B560  conf=0.97  ?Update@FrontEnd_Mgr@@QAEXM@Z
  using Update_t = void (__thiscall*)(::FrontEnd_Mgr *, float);
  inline void Update(::FrontEnd_Mgr * a0, float a1) { reinterpret_cast<Update_t>(meridian::rebase(0x0052B560))(a0, a1); }
  // 0x0052AE30  conf=0.97  ?UpdateAfterLevel@FrontEnd_Mgr@@QAEXXZ
  using UpdateAfterLevel_t = void (__thiscall*)(::FrontEnd_Mgr *);
  inline void UpdateAfterLevel(::FrontEnd_Mgr * a0) { reinterpret_cast<UpdateAfterLevel_t>(meridian::rebase(0x0052AE30))(a0); }
} // FrontEnd_Mgr_

// ===== GadgetPendulum =====  (1 functions)  ->  namespace GadgetPendulum_
namespace GadgetPendulum_ {
  // 0x00527850  conf=0.97  ?Update@GadgetPendulum@@UAEXXZ
  using Update_t = void (__thiscall*)(::GadgetPendulum *);
  inline void Update(::GadgetPendulum * a0) { reinterpret_cast<Update_t>(meridian::rebase(0x00527850))(a0); }
} // GadgetPendulum_

// ===== GadgetWackAMole =====  (1 functions)  ->  namespace GadgetWackAMole_
namespace GadgetWackAMole_ {
  // 0x00526FC0  conf=0.97  ?Update@GadgetWackAMole@@UAEXXZ
  using Update_t = void (__thiscall*)(::GadgetWackAMole *);
  inline void Update(::GadgetWackAMole * a0) { reinterpret_cast<Update_t>(meridian::rebase(0x00526FC0))(a0); }
} // GadgetWackAMole_

// ===== GadgetWackAMole2 =====  (1 functions)  ->  namespace GadgetWackAMole2_
namespace GadgetWackAMole2_ {
  // 0x00528F90  conf=0.97  ?Update@GadgetWackAMole2@@UAEXXZ
  using Update_t = void (__thiscall*)(::GadgetWackAMole2 *);
  inline void Update(::GadgetWackAMole2 * a0) { reinterpret_cast<Update_t>(meridian::rebase(0x00528F90))(a0); }
} // GadgetWackAMole2_

// ===== GoalAction =====  (1 functions)  ->  namespace GoalAction_
namespace GoalAction_ {
  // 0x005696C0  conf=0.97  ?GetTargetLocation@GoalAction@@UAEHAAUvector3@@@Z
  using GetTargetLocation_t = int (__thiscall*)(::GoalAction *, ::vector3 *);
  inline int GetTargetLocation(::GoalAction * a0, ::vector3 * a1) { return reinterpret_cast<GetTargetLocation_t>(meridian::rebase(0x005696C0))(a0, a1); }
} // GoalAction_

// ===== GoalGotoTarget =====  (1 functions)  ->  namespace GoalGotoTarget_
namespace GoalGotoTarget_ {
  // 0x00568690  conf=0.925  ?OnImport@GoalGotoTarget@@UAEXAAVbin_in@@HH@Z
  using OnImport_t = void (__thiscall*)(::GoalGotoTarget *, ::bin_in *, int, int);
  inline void OnImport(::GoalGotoTarget * a0, ::bin_in * a1, int a2, int a3) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00568690))(a0, a1, a2, a3); }
} // GoalGotoTarget_

// ===== GoalSendMessage =====  (1 functions)  ->  namespace GoalSendMessage_
namespace GoalSendMessage_ {
  // 0x0056A120  conf=0.97  ?GetProperty@GoalSendMessage@@UAE?AUproperty@@PBDHH@Z
  using GetProperty_t = ::property (__thiscall*)(::GoalSendMessage *, char *, int, int);
  inline ::property GetProperty(::GoalSendMessage * a0, char * a1, int a2, int a3) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x0056A120))(a0, a1, a2, a3); }
} // GoalSendMessage_

// ===== Hud_3D_Object =====  (1 functions)  ->  namespace Hud_3D_Object_
namespace Hud_3D_Object_ {
  // 0x004F93E0  conf=0.784  ?Set@Hud_3D_Object@@QAEXUvector4@@PBD@Z
  using Set_t = void (__thiscall*)(::Hud_3D_Object *, ::vector4, char *);
  inline void Set(::Hud_3D_Object * a0, ::vector4 a1, char * a2) { reinterpret_cast<Set_t>(meridian::rebase(0x004F93E0))(a0, a1, a2); }
} // Hud_3D_Object_

// ===== IdleState =====  (1 functions)  ->  namespace IdleState_
namespace IdleState_ {
  // 0x00639D50  conf=0.97  ?ChangePhase@IdleState@@UAEXH@Z
  using ChangePhase_t = void (__thiscall*)(::IdleState *, int);
  inline void ChangePhase(::IdleState * a0, int a1) { reinterpret_cast<ChangePhase_t>(meridian::rebase(0x00639D50))(a0, a1); }
} // IdleState_

// ===== LegalScreen =====  (1 functions)  ->  namespace LegalScreen_
namespace LegalScreen_ {
  // 0x004FB310  conf=0.757  ?LegalScreen@@YAHXZ
  using ctor_t = int (__cdecl*)();
  inline int ctor() { return reinterpret_cast<ctor_t>(meridian::rebase(0x004FB310))(); }
} // LegalScreen_

// ===== Level =====  (3 functions)  ->  namespace Level_
namespace Level_ {
  // 0x004196A0  conf=0.97  ?LevelCreate@@YAPAVlevel@@PBD@Z
  using LevelCreate_t = ::level * (__cdecl*)(char *);
  inline ::level * LevelCreate(char * a0) { return reinterpret_cast<LevelCreate_t>(meridian::rebase(0x004196A0))(a0); }
  // 0x00419FF0  conf=0.75  ?LevelDestroy@@YAXPAVlevel@@@Z
  using LevelDestroy_t = void (__cdecl*)(::level *);
  inline void LevelDestroy(::level * a0) { reinterpret_cast<LevelDestroy_t>(meridian::rebase(0x00419FF0))(a0); }
  // 0x00419620  conf=0.97  ?LevelGetDialogPackage@@YAXPADPBD@Z
  using LevelGetDialogPackage_t = void (__cdecl*)(char *, char *);
  inline void LevelGetDialogPackage(char * a0, char * a1) { reinterpret_cast<LevelGetDialogPackage_t>(meridian::rebase(0x00419620))(a0, a1); }
} // Level_

// ===== LevelLaketown =====  (1 functions)  ->  namespace LevelLaketown_
namespace LevelLaketown_ {
  // 0x00416480  conf=0.762  ?BilboIntersectsSphere@@YAHABUvector3@@M@Z
  using BilboIntersectsSphere_t = int (__cdecl*)(::vector3 *, float);
  inline int BilboIntersectsSphere(::vector3 * a0, float a1) { return reinterpret_cast<BilboIntersectsSphere_t>(meridian::rebase(0x00416480))(a0, a1); }
} // LevelLaketown_

// ===== LevelLoader =====  (4 functions)  ->  namespace LevelLoader_
namespace LevelLoader_ {
  // 0x004FBF00  conf=0.75  ?LevelLoader_Close@@YAXXZ
  using LevelLoader_Close_t = void (__cdecl*)();
  inline void LevelLoader_Close() { reinterpret_cast<LevelLoader_Close_t>(meridian::rebase(0x004FBF00))(); }
  // 0x004FB7E0  conf=0.97  ?LevelLoader_LoadManualResources@@YAXXZ
  using LevelLoader_LoadManualResources_t = void (__cdecl*)();
  inline void LevelLoader_LoadManualResources() { reinterpret_cast<LevelLoader_LoadManualResources_t>(meridian::rebase(0x004FB7E0))(); }
  // 0x004FBE30  conf=0.97  ?LevelLoader_Open@@YAHXZ
  using LevelLoader_Open_t = int (__cdecl*)();
  inline int LevelLoader_Open() { return reinterpret_cast<LevelLoader_Open_t>(meridian::rebase(0x004FBE30))(); }
  // 0x005C5210  conf=0.724  ?LevelLoader_UnloadManualResources@@YAXXZ
  using LevelLoader_UnloadManualResources_t = void (__cdecl*)();
  inline void LevelLoader_UnloadManualResources() { reinterpret_cast<LevelLoader_UnloadManualResources_t>(meridian::rebase(0x005C5210))(); }
} // LevelLoader_

// ===== LevelLonelyMountain =====  (1 functions)  ->  namespace LevelLonelyMountain_
namespace LevelLonelyMountain_ {
  // 0x0040C5E0  conf=0.97  ?StartGondolas@@YAXH@Z
  using StartGondolas_t = void (__cdecl*)(int);
  inline void StartGondolas(int a0) { reinterpret_cast<StartGondolas_t>(meridian::rebase(0x0040C5E0))(a0); }
} // LevelLonelyMountain_

// ===== LevelSelect =====  (2 functions)  ->  namespace LevelSelect_
namespace LevelSelect_ {
  // 0x004FC090  conf=0.97  ?LS_DisplayMenu@@YAXXZ
  using LS_DisplayMenu_t = void (__cdecl*)();
  inline void LS_DisplayMenu() { reinterpret_cast<LS_DisplayMenu_t>(meridian::rebase(0x004FC090))(); }
  // 0x004FC380  conf=0.72  ?LS_LevelSelect@@YAHPADH@Z
  using LS_LevelSelect_t = int (__cdecl*)(char *, int);
  inline int LS_LevelSelect(char * a0, int a1) { return reinterpret_cast<LS_LevelSelect_t>(meridian::rebase(0x004FC380))(a0, a1); }
} // LevelSelect_

// ===== Light =====  (2 functions)  ->  namespace Light_
namespace Light_ {
  // 0x00493850  conf=0.747  ?ParseLightName@@YAIPBD@Z
  using ParseLightName_t = uint (__cdecl*)(char *);
  inline uint ParseLightName(char * a0) { return reinterpret_cast<ParseLightName_t>(meridian::rebase(0x00493850))(a0); }
  // 0x00571480  conf=0.745  ?PropertySetColor@@YAHPBDABUproperty@@0AAUxcolor@@@Z
  using PropertySetColor_t = int (__cdecl*)(char *, ::property *, char *, ::xcolor *);
  inline int PropertySetColor(char * a0, ::property * a1, char * a2, ::xcolor * a3) { return reinterpret_cast<PropertySetColor_t>(meridian::rebase(0x00571480))(a0, a1, a2, a3); }
} // Light_

// ===== LoadScreen =====  (1 functions)  ->  namespace LoadScreen_
namespace LoadScreen_ {
  // 0x004F9920  conf=0.97  ?Init@LoadScreen@@QAEXXZ
  using Init_t = void (__thiscall*)(::LoadScreen *);
  inline void Init(::LoadScreen * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x004F9920))(a0); }
} // LoadScreen_

// ===== Main =====  (13 functions)  ->  namespace Main_
namespace Main_ {
  // 0x004FD7C0  conf=0.97  ?AppBegin@@YAXPAX@Z
  using AppBegin_t = void (__cdecl*)(void *);
  inline void AppBegin(void * a0) { reinterpret_cast<AppBegin_t>(meridian::rebase(0x004FD7C0))(a0); }
  // 0x0052AC30  conf=0.519  ?CacheNextLevel@@YAXXZ
  using CacheNextLevel_t = void (__cdecl*)();
  inline void CacheNextLevel() { reinterpret_cast<CacheNextLevel_t>(meridian::rebase(0x0052AC30))(); }
  // 0x00572800  conf=0.572  ?GameCoreInit@@YAXXZ
  using GameCoreInit_t = void (__cdecl*)();
  inline void GameCoreInit() { reinterpret_cast<GameCoreInit_t>(meridian::rebase(0x00572800))(); }
  // 0x004FE2A0  conf=0.74  ?GameCoreKill@@YAXXZ
  using GameCoreKill_t = void (__cdecl*)();
  inline void GameCoreKill() { reinterpret_cast<GameCoreKill_t>(meridian::rebase(0x004FE2A0))(); }
  // 0x004FE1B0  conf=0.97  ?Kill@@YAXXZ
  using Kill_t = void (__cdecl*)();
  inline void Kill() { reinterpret_cast<Kill_t>(meridian::rebase(0x004FE1B0))(); }
  // 0x004FE5A0  conf=0.917  ?LoadLevel@@YAHXZ
  using LoadLevel_t = int (__cdecl*)();
  inline int LoadLevel() { return reinterpret_cast<LoadLevel_t>(meridian::rebase(0x004FE5A0))(); }
  // 0x004FD2B0  conf=0.97  ?PreloadResources@@YAXXZ
  using PreloadResources_t = void (__cdecl*)();
  inline void PreloadResources() { reinterpret_cast<PreloadResources_t>(meridian::rebase(0x004FD2B0))(); }
  // 0x004FF0A0  conf=0.713  ?Render@@YAXXZ
  using Render_t = void (__cdecl*)();
  inline void Render() { reinterpret_cast<Render_t>(meridian::rebase(0x004FF0A0))(); }
  // 0x004FE3E0  conf=0.97  ?RunFrontEnd@@YAHXZ
  using RunFrontEnd_t = int (__cdecl*)();
  inline int RunFrontEnd() { return reinterpret_cast<RunFrontEnd_t>(meridian::rebase(0x004FE3E0))(); }
  // 0x004FEE90  conf=0.795  ?RunLevel@@YAXXZ
  using RunLevel_t = void (__cdecl*)();
  inline void RunLevel() { reinterpret_cast<RunLevel_t>(meridian::rebase(0x004FEE90))(); }
  // 0x004FEC70  conf=0.8  ?SetBilboCombatLevels@@YAXXZ
  using SetBilboCombatLevels_t = void (__cdecl*)();
  inline void SetBilboCombatLevels() { reinterpret_cast<SetBilboCombatLevels_t>(meridian::rebase(0x004FEC70))(); }
  // 0x004FCE90  conf=0.711  ?SetupRootDirectories@@YAXPBD@Z
  using SetupRootDirectories_t = void (__cdecl*)(char *);
  inline void SetupRootDirectories(char * a0) { reinterpret_cast<SetupRootDirectories_t>(meridian::rebase(0x004FCE90))(a0); }
  // 0x004FEDC0  conf=0.751  ?UnloadLevel@@YAXXZ
  using UnloadLevel_t = void (__cdecl*)();
  inline void UnloadLevel() { reinterpret_cast<UnloadLevel_t>(meridian::rebase(0x004FEDC0))(); }
} // Main_

// ===== Meridian =====  (1 functions)  ->  namespace Meridian_
namespace Meridian_ {
  // 0x00500510  conf=0.8  ?EndLevel@@YAXXZ
  using EndLevel_t = void (__cdecl*)();
  inline void EndLevel() { reinterpret_cast<EndLevel_t>(meridian::rebase(0x00500510))(); }
} // Meridian_

// ===== MeridianObj =====  (4 functions)  ->  namespace MeridianObj_
namespace MeridianObj_ {
  // 0x0049B580  conf=0.731  ?xsc_GetTriggerItem@@YAXPAE@Z
  using xsc_GetTriggerItem_t = void (__cdecl*)(uchar *);
  inline void xsc_GetTriggerItem(uchar * a0) { reinterpret_cast<xsc_GetTriggerItem_t>(meridian::rebase(0x0049B580))(a0); }
  // 0x0049B460  conf=0.712  ?xsc_InfoOverlay@@YAXPAE@Z
  using xsc_InfoOverlay_t = void (__cdecl*)(uchar *);
  inline void xsc_InfoOverlay(uchar * a0) { reinterpret_cast<xsc_InfoOverlay_t>(meridian::rebase(0x0049B460))(a0); }
  // 0x0049BBD0  conf=0.75  ?xsc_IsMeshHidden@@YAXPAE@Z
  using xsc_IsMeshHidden_t = void (__cdecl*)(uchar *);
  inline void xsc_IsMeshHidden(uchar * a0) { reinterpret_cast<xsc_IsMeshHidden_t>(meridian::rebase(0x0049BBD0))(a0); }
  // 0x0049B600  conf=0.715  ?xsc_IsSwitchOn@@YAXPAE@Z
  using xsc_IsSwitchOn_t = void (__cdecl*)(uchar *);
  inline void xsc_IsSwitchOn(uchar * a0) { reinterpret_cast<xsc_IsSwitchOn_t>(meridian::rebase(0x0049B600))(a0); }
} // MeridianObj_

// ===== MotionLinear =====  (2 functions)  ->  namespace MotionLinear_
namespace MotionLinear_ {
  // 0x0049D020  conf=0.75  ??0MotionLinear@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::MotionLinear *);
  inline undefined ctor(::MotionLinear * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0049D020))(a0); }
  // 0x0049D570  conf=0.75  ?SetImpactOnTarget@MotionLinear@@QAEXH@Z
  using SetImpactOnTarget_t = void (__thiscall*)(::MotionLinear *, int);
  inline void SetImpactOnTarget(::MotionLinear * a0, int a1) { reinterpret_cast<SetImpactOnTarget_t>(meridian::rebase(0x0049D570))(a0, a1); }
} // MotionLinear_

// ===== MusicLogic =====  (9 functions)  ->  namespace MusicLogic_
namespace MusicLogic_ {
  // 0x00534F30  conf=0.97  ?ChangeState@MusicLogic@@QAEXH@Z
  using ChangeState_t = void (__thiscall*)(::MusicLogic *, int);
  inline void ChangeState(::MusicLogic * a0, int a1) { reinterpret_cast<ChangeState_t>(meridian::rebase(0x00534F30))(a0, a1); }
  // 0x005349A0  conf=0.689  ?CollectNPCInfo@MusicLogic@@QAEXMAAH000000AAM@Z
  using CollectNPCInfo_t = void (__thiscall*)(::MusicLogic *, float, int *, int *, int *, int *, int *, int *, int *, float *);
  inline void CollectNPCInfo(::MusicLogic * a0, float a1, int * a2, int * a3, int * a4, int * a5, int * a6, int * a7, int * a8, float * a9) { reinterpret_cast<CollectNPCInfo_t>(meridian::rebase(0x005349A0))(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); }
  // 0x00535EC0  conf=0.97  ?ExportThreatValues@MusicLogic@@QAEXAAVbin_out@@@Z
  using ExportThreatValues_t = void (__thiscall*)(::MusicLogic *, ::bin_out *);
  inline void ExportThreatValues(::MusicLogic * a0, ::bin_out * a1) { reinterpret_cast<ExportThreatValues_t>(meridian::rebase(0x00535EC0))(a0, a1); }
  // 0x005360D0  conf=0.581  ?ImportThreatValues@MusicLogic@@QAEXAAVbin_in@@@Z
  using ImportThreatValues_t = void (__thiscall*)(::MusicLogic *, ::bin_in *);
  inline void ImportThreatValues(::MusicLogic * a0, ::bin_in * a1) { reinterpret_cast<ImportThreatValues_t>(meridian::rebase(0x005360D0))(a0, a1); }
  // 0x00536400  conf=0.97  ?OnImport@MusicLogic@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::MusicLogic *, ::bin_in *);
  inline void OnImport(::MusicLogic * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00536400))(a0, a1); }
  // 0x005346E0  conf=0.616  ?SetTrackBySuiteTypeAndIntensity@MusicLogic@@QAEHAAVxstring@@HW4SWITCHTYPE@music_mgr@@@Z
  inline void* SetTrackBySuiteTypeAndIntensity_at() { return meridian::rebase(0x005346E0); } // int __thiscall SetTrackBySuiteTypeAndIntensity(MusicLogic *, xstring *, int, SWITCHTYPE)
  // 0x005342F0  conf=0.685  ?UpDateBossCombat@MusicLogic@@QAEXM@Z
  using UpDateBossCombat_t = void (__thiscall*)(::MusicLogic *, float);
  inline void UpDateBossCombat(::MusicLogic * a0, float a1) { reinterpret_cast<UpDateBossCombat_t>(meridian::rebase(0x005342F0))(a0, a1); }
  // 0x00534B00  conf=0.606  ?UpDatePostCombat@MusicLogic@@QAEXM@Z
  using UpDatePostCombat_t = void (__thiscall*)(::MusicLogic *, float);
  inline void UpDatePostCombat(::MusicLogic * a0, float a1) { reinterpret_cast<UpDatePostCombat_t>(meridian::rebase(0x00534B00))(a0, a1); }
  // 0x00534DD0  conf=0.627  ?UpDateStateSilence@MusicLogic@@QAEXM@Z
  using UpDateStateSilence_t = void (__thiscall*)(::MusicLogic *, float);
  inline void UpDateStateSilence(::MusicLogic * a0, float a1) { reinterpret_cast<UpDateStateSilence_t>(meridian::rebase(0x00534DD0))(a0, a1); }
} // MusicLogic_

// ===== MusicManager =====  (1 functions)  ->  namespace MusicManager_
namespace MusicManager_ {
  // 0x004FB0D0  conf=0.75  ?music_Kill@@YAXXZ
  using music_Kill_t = void (__cdecl*)();
  inline void music_Kill() { reinterpret_cast<music_Kill_t>(meridian::rebase(0x004FB0D0))(); }
} // MusicManager_

// ===== MusicTrigger =====  (1 functions)  ->  namespace MusicTrigger_
namespace MusicTrigger_ {
  // 0x005385E0  conf=0.97  ?InitializeTriggerActionTypeList@@YAXXZ
  using InitializeTriggerActionTypeList_t = void (__cdecl*)();
  inline void InitializeTriggerActionTypeList() { reinterpret_cast<InitializeTriggerActionTypeList_t>(meridian::rebase(0x005385E0))(); }
} // MusicTrigger_

// ===== NPCObject =====  (32 functions)  ->  namespace NPCObject_
namespace NPCObject_ {
  // 0x004A1C30  conf=0.767  ?AdvanceDeathTimer@NPCObject@@QAEXXZ
  using AdvanceDeathTimer_t = void (__thiscall*)(::NPCObject *);
  inline void AdvanceDeathTimer(::NPCObject * a0) { reinterpret_cast<AdvanceDeathTimer_t>(meridian::rebase(0x004A1C30))(a0); }
  // 0x00594BE0  conf=0.579  ?AdvanceEventProcessing@NPCObject@@QAEXXZ
  using AdvanceEventProcessing_t = void (__thiscall*)(::NPCObject *);
  inline void AdvanceEventProcessing(::NPCObject * a0) { reinterpret_cast<AdvanceEventProcessing_t>(meridian::rebase(0x00594BE0))(a0); }
  // 0x004A1750  conf=0.766  ?AdvanceFullUpdate@NPCObject@@QAEXXZ
  using AdvanceFullUpdate_t = void (__thiscall*)(::NPCObject *);
  inline void AdvanceFullUpdate(::NPCObject * a0) { reinterpret_cast<AdvanceFullUpdate_t>(meridian::rebase(0x004A1750))(a0); }
  // 0x004A1E50  conf=0.798  ?AdvanceHealthMeter@NPCObject@@QAEXXZ
  using AdvanceHealthMeter_t = void (__thiscall*)(::NPCObject *);
  inline void AdvanceHealthMeter(::NPCObject * a0) { reinterpret_cast<AdvanceHealthMeter_t>(meridian::rebase(0x004A1E50))(a0); }
  // 0x004A1AD0  conf=0.773  ?AdvanceSleep@NPCObject@@QAEXXZ
  using AdvanceSleep_t = void (__thiscall*)(::NPCObject *);
  inline void AdvanceSleep(::NPCObject * a0) { reinterpret_cast<AdvanceSleep_t>(meridian::rebase(0x004A1AD0))(a0); }
  // 0x004A58A0  conf=0.734  ?Die@NPCObject@@IAEXXZ
  using Die_t = void (__thiscall*)(::NPCObject *);
  inline void Die(::NPCObject * a0) { reinterpret_cast<Die_t>(meridian::rebase(0x004A58A0))(a0); }
  // 0x004A69A0  conf=0.796  ?DieScumDie@NPCObject@@QAEXXZ
  using DieScumDie_t = void (__thiscall*)(::NPCObject *);
  inline void DieScumDie(::NPCObject * a0) { reinterpret_cast<DieScumDie_t>(meridian::rebase(0x004A69A0))(a0); }
  // 0x004A13D0  conf=0.74  ?EndConversationMode@NPCObject@@UAEXH@Z
  using EndConversationMode_t = void (__thiscall*)(::NPCObject *, int);
  inline void EndConversationMode(::NPCObject * a0, int a1) { reinterpret_cast<EndConversationMode_t>(meridian::rebase(0x004A13D0))(a0, a1); }
  // 0x005B6F40  conf=0.75  ?GetAITarget@NPCObject@@QAE_KXZ
  using GetAITarget_t = __uint64 (__thiscall*)(::NPCObject *);
  inline __uint64 GetAITarget(::NPCObject * a0) { return reinterpret_cast<GetAITarget_t>(meridian::rebase(0x005B6F40))(a0); }
  // 0x004A1230  conf=0.75  ?GetCinema@NPCObject@@QAE_KXZ
  using GetCinema_t = __uint64 (__thiscall*)(::NPCObject *);
  inline __uint64 GetCinema(::NPCObject * a0) { return reinterpret_cast<GetCinema_t>(meridian::rebase(0x004A1230))(a0); }
  // 0x004A1060  conf=0.683  ?GetDoSenses@NPCObject@@QAEHXZ
  using GetDoSenses_t = int (__thiscall*)(::NPCObject *);
  inline int GetDoSenses(::NPCObject * a0) { return reinterpret_cast<GetDoSenses_t>(meridian::rebase(0x004A1060))(a0); }
  // 0x004A4130  conf=0.75  ?GetHitPoints@NPCObject@@QAEMXZ
  using GetHitPoints_t = float (__thiscall*)(::NPCObject *);
  inline float GetHitPoints(::NPCObject * a0) { return reinterpret_cast<GetHitPoints_t>(meridian::rebase(0x004A4130))(a0); }
  // 0x004A8190  conf=0.772  ?GetProperty@NPCObject@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::NPCObject *, char *);
  inline ::property GetProperty(::NPCObject * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004A8190))(a0, a1); }
  // 0x004A22A0  conf=0.71  ?GotoSleep@NPCObject@@IAEXXZ
  using GotoSleep_t = void (__thiscall*)(::NPCObject *);
  inline void GotoSleep(::NPCObject * a0) { reinterpret_cast<GotoSleep_t>(meridian::rebase(0x004A22A0))(a0); }
  // 0x005AEAD0  conf=0.676  ?HandleMessage@NPCObject@@UAEHPAUMessageInfo@@@Z
  using HandleMessage_t = int (__thiscall*)(::NPCObject *, ::MessageInfo *);
  inline int HandleMessage(::NPCObject * a0, ::MessageInfo * a1) { return reinterpret_cast<HandleMessage_t>(meridian::rebase(0x005AEAD0))(a0, a1); }
  // 0x004A1240  conf=0.75  ?HasCinema@NPCObject@@QAEHXZ
  using HasCinema_t = int (__thiscall*)(::NPCObject *);
  inline int HasCinema(::NPCObject * a0) { return reinterpret_cast<HasCinema_t>(meridian::rebase(0x004A1240))(a0); }
  // 0x004A1210  conf=0.75  ?HasConversation@NPCObject@@QAEHXZ
  using HasConversation_t = int (__thiscall*)(::NPCObject *);
  inline int HasConversation(::NPCObject * a0) { return reinterpret_cast<HasConversation_t>(meridian::rebase(0x004A1210))(a0); }
  // 0x004A2340  conf=0.562  ?IsBoss@NPCObject@@QAEHXZ
  using IsBoss_t = int (__thiscall*)(::NPCObject *);
  inline int IsBoss(::NPCObject * a0) { return reinterpret_cast<IsBoss_t>(meridian::rebase(0x004A2340))(a0); }
  // 0x004A2300  conf=0.75  ?IsTargetable@NPCObject@@QAEHXZ
  using IsTargetable_t = int (__thiscall*)(::NPCObject *);
  inline int IsTargetable(::NPCObject * a0) { return reinterpret_cast<IsTargetable_t>(meridian::rebase(0x004A2300))(a0); }
  // 0x0049F8F0  conf=0.97  ?LoadCharacterData@NPCObject@@QAEXXZ
  using LoadCharacterData_t = void (__thiscall*)(::NPCObject *);
  inline void LoadCharacterData(::NPCObject * a0) { reinterpret_cast<LoadCharacterData_t>(meridian::rebase(0x0049F8F0))(a0); }
  // 0x0049EFF0  conf=0.97  ??0NPCObject@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::NPCObject *);
  inline undefined ctor(::NPCObject * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0049EFF0))(a0); }
  // 0x004A14C0  conf=0.784  ?OnAdvanceLogic@NPCObject@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::NPCObject *, float);
  inline void OnAdvanceLogic(::NPCObject * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004A14C0))(a0, a1); }
  // 0x004A4610  conf=0.793  ?OnApplyPain@NPCObject@@UAEH_KABUvector3@@MMMMW4ePainType@PainData@@H@Z
  inline void* OnApplyPain_at() { return meridian::rebase(0x004A4610); } // int __thiscall OnApplyPain(NPCObject *, __uint64, vector3 *, float, float, float, float, ePainType, int)
  // 0x004A5A70  conf=0.97  ?OnImport@NPCObject@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::NPCObject *, ::bin_in *);
  inline void OnImport(::NPCObject * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004A5A70))(a0, a1); }
  // 0x0049F480  conf=0.75  ?OnObjectActivate@NPCObject@@UAEXXZ
  using OnObjectActivate_t = void (__thiscall*)(::NPCObject *);
  inline void OnObjectActivate(::NPCObject * a0) { reinterpret_cast<OnObjectActivate_t>(meridian::rebase(0x0049F480))(a0); }
  // 0x004A9870  conf=0.737  ?OnObjectDeactivate@NPCObject@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::NPCObject *);
  inline void OnObjectDeactivate(::NPCObject * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004A9870))(a0); }
  // 0x004A9960  conf=0.75  ?SetDrawHealthMeter@NPCObject@@QAEXH@Z
  using SetDrawHealthMeter_t = void (__thiscall*)(::NPCObject *, int);
  inline void SetDrawHealthMeter(::NPCObject * a0, int a1) { reinterpret_cast<SetDrawHealthMeter_t>(meridian::rebase(0x004A9960))(a0, a1); }
  // 0x004A5790  conf=0.735  ?SetIsRooted@NPCObject@@QAEXHH@Z
  using SetIsRooted_t = void (__thiscall*)(::NPCObject *, int, int);
  inline void SetIsRooted(::NPCObject * a0, int a1, int a2) { reinterpret_cast<SetIsRooted_t>(meridian::rebase(0x004A5790))(a0, a1, a2); }
  // 0x0049FEE0  conf=0.719  ?SetProp@NPCObject@@IAEXW4ePropTypes@1@Vxwstring@@@Z
  inline void* SetProp_at() { return meridian::rebase(0x0049FEE0); } // void __thiscall SetProp(NPCObject *, ePropTypes, xwstring)
  // 0x004A40D0  conf=0.724  ?ShatterShield@NPCObject@@QAEXXZ
  using ShatterShield_t = void (__thiscall*)(::NPCObject *);
  inline void ShatterShield(::NPCObject * a0) { reinterpret_cast<ShatterShield_t>(meridian::rebase(0x004A40D0))(a0); }
  // 0x004A5130  conf=0.97  ?TakeDamage@NPCObject@@QAEX_KPAVPainData@@@Z
  using TakeDamage_t = void (__thiscall*)(::NPCObject *, __uint64, ::PainData *);
  inline void TakeDamage(::NPCObject * a0, __uint64 a1, ::PainData * a2) { reinterpret_cast<TakeDamage_t>(meridian::rebase(0x004A5130))(a0, a1, a2); }
  // 0x004A29B0  conf=0.97  ?UpdateProps@NPCObject@@IAEXH@Z
  using UpdateProps_t = void (__thiscall*)(::NPCObject *, int);
  inline void UpdateProps(::NPCObject * a0, int a1) { reinterpret_cast<UpdateProps_t>(meridian::rebase(0x004A29B0))(a0, a1); }
} // NPCObject_

// ===== Object =====  (1 functions)  ->  namespace Object_
namespace Object_ {
  // 0x004ACFF0  conf=0.762  ?PropertyEnumerateBBox@@YAXAAV?$xarray@Uproperty_desc@@@@PBDIABUbbox@@2@Z
  using PropertyEnumerateBBox_t = void (__cdecl*)(::xarray< ::property_desc> *, char *, uint, ::bbox *, ::bbox *);
  inline void PropertyEnumerateBBox(::xarray< ::property_desc> * a0, char * a1, uint a2, ::bbox * a3, ::bbox * a4) { reinterpret_cast<PropertyEnumerateBBox_t>(meridian::rebase(0x004ACFF0))(a0, a1, a2, a3, a4); }
} // Object_

// ===== PainData =====  (1 functions)  ->  namespace PainData_
namespace PainData_ {
  // 0x005B8B20  conf=0.97  ?InitializeNames@PainData@@KAXXZ
  using InitializeNames_t = void (__cdecl*)();
  inline void InitializeNames() { reinterpret_cast<InitializeNames_t>(meridian::rebase(0x005B8B20))(); }
} // PainData_

// ===== Pause_Mgr =====  (14 functions)  ->  namespace Pause_Mgr_
namespace Pause_Mgr_ {
  // 0x0052DA60  conf=0.798  ?ActivateQuestLogPopup@Pause_Mgr@@QAEX_K@Z
  using ActivateQuestLogPopup_t = void (__thiscall*)(::Pause_Mgr *, __uint64);
  inline void ActivateQuestLogPopup(::Pause_Mgr * a0, __uint64 a1) { reinterpret_cast<ActivateQuestLogPopup_t>(meridian::rebase(0x0052DA60))(a0, a1); }
  // 0x0052C8C0  conf=0.925  ?Init@Pause_Mgr@@QAEHXZ
  using Init_t = int (__thiscall*)(::Pause_Mgr *);
  inline int Init(::Pause_Mgr * a0) { return reinterpret_cast<Init_t>(meridian::rebase(0x0052C8C0))(a0); }
  // 0x005268D0  conf=0.725  ?IsPaused@Pause_Mgr@@QAEHXZ
  using IsPaused_t = int (__thiscall*)(::Pause_Mgr *);
  inline int IsPaused(::Pause_Mgr * a0) { return reinterpret_cast<IsPaused_t>(meridian::rebase(0x005268D0))(a0); }
  // 0x0052C870  conf=0.75  ?Kill@Pause_Mgr@@QAEXXZ
  using Kill_t = void (__thiscall*)(::Pause_Mgr *);
  inline void Kill(::Pause_Mgr * a0) { reinterpret_cast<Kill_t>(meridian::rebase(0x0052C870))(a0); }
  // 0x0052D910  conf=0.744  ?PickLocks@Pause_Mgr@@QAEXXZ
  using PickLocks_t = void (__thiscall*)(::Pause_Mgr *);
  inline void PickLocks(::Pause_Mgr * a0) { reinterpret_cast<PickLocks_t>(meridian::rebase(0x0052D910))(a0); }
  // 0x0052CF40  conf=0.762  ?RenderBookArrows@Pause_Mgr@@QAEXXZ
  using RenderBookArrows_t = void (__thiscall*)(::Pause_Mgr *);
  inline void RenderBookArrows(::Pause_Mgr * a0) { reinterpret_cast<RenderBookArrows_t>(meridian::rebase(0x0052CF40))(a0); }
  // 0x0052CD20  conf=0.787  ?RenderMainWindow@Pause_Mgr@@QAEXH@Z
  using RenderMainWindow_t = void (__thiscall*)(::Pause_Mgr *, int);
  inline void RenderMainWindow(::Pause_Mgr * a0, int a1) { reinterpret_cast<RenderMainWindow_t>(meridian::rebase(0x0052CD20))(a0, a1); }
  // 0x0052D960  conf=0.788  ?SaveKiosk@Pause_Mgr@@QAEXXZ
  using SaveKiosk_t = void (__thiscall*)(::Pause_Mgr *);
  inline void SaveKiosk(::Pause_Mgr * a0) { reinterpret_cast<SaveKiosk_t>(meridian::rebase(0x0052D960))(a0); }
  // 0x0052DB00  conf=0.8  ?SetInventoryPartsTexture@Pause_Mgr@@QAEXH@Z
  using SetInventoryPartsTexture_t = void (__thiscall*)(::Pause_Mgr *, int);
  inline void SetInventoryPartsTexture(::Pause_Mgr * a0, int a1) { reinterpret_cast<SetInventoryPartsTexture_t>(meridian::rebase(0x0052DB00))(a0, a1); }
  // 0x0042A7D0  conf=0.771  ?SetPaused@Pause_Mgr@@QAEXH@Z
  using SetPaused_t = void (__thiscall*)(::Pause_Mgr *, int);
  inline void SetPaused(::Pause_Mgr * a0, int a1) { reinterpret_cast<SetPaused_t>(meridian::rebase(0x0042A7D0))(a0, a1); }
  // 0x0052B120  conf=0.726  ?SetUnplugged@Pause_Mgr@@QAEXH@Z
  using SetUnplugged_t = void (__thiscall*)(::Pause_Mgr *, int);
  inline void SetUnplugged(::Pause_Mgr * a0, int a1) { reinterpret_cast<SetUnplugged_t>(meridian::rebase(0x0052B120))(a0, a1); }
  // 0x0052D9B0  conf=0.744  ?TextBox@Pause_Mgr@@QAEXPBG0@Z
  using TextBox_t = void (__thiscall*)(::Pause_Mgr *, ushort *, ushort *);
  inline void TextBox(::Pause_Mgr * a0, ushort * a1, ushort * a2) { reinterpret_cast<TextBox_t>(meridian::rebase(0x0052D9B0))(a0, a1, a2); }
  // 0x0052D1A0  conf=0.83  ?Update@Pause_Mgr@@QAEXXZ
  using Update_t = void (__thiscall*)(::Pause_Mgr *);
  inline void Update(::Pause_Mgr * a0) { reinterpret_cast<Update_t>(meridian::rebase(0x0052D1A0))(a0); }
  // 0x0052CB70  conf=0.97  ?UpdateSummaryStats@Pause_Mgr@@QAEXXZ
  using UpdateSummaryStats_t = void (__thiscall*)(::Pause_Mgr *);
  inline void UpdateSummaryStats(::Pause_Mgr * a0) { reinterpret_cast<UpdateSummaryStats_t>(meridian::rebase(0x0052CB70))(a0); }
} // Pause_Mgr_

// ===== PhysController =====  (6 functions)  ->  namespace PhysController_
namespace PhysController_ {
  // 0x0059AD20  conf=0.97  ?BuildMatrices@PhysController@@QAEXPAPAVmatrix4@@AAHH@Z
  using BuildMatrices_t = void (__thiscall*)(::PhysController *, ::matrix4 * *, int *, int);
  inline void BuildMatrices(::PhysController * a0, ::matrix4 * * a1, int * a2, int a3) { reinterpret_cast<BuildMatrices_t>(meridian::rebase(0x0059AD20))(a0, a1, a2, a3); }
  // 0x0059AC20  conf=0.97  ?DoNavigate@PhysController@@IAEHAAH@Z
  using DoNavigate_t = int (__thiscall*)(::PhysController *, int *);
  inline int DoNavigate(::PhysController * a0, int * a1) { return reinterpret_cast<DoNavigate_t>(meridian::rebase(0x0059AC20))(a0, a1); }
  // 0x00591540  conf=0.97  ?LoadAnims@PhysController@@QAEXVxstring@@@Z
  using LoadAnims_t = void (__thiscall*)(::PhysController *, ::xstring);
  inline void LoadAnims(::PhysController * a0, ::xstring a1) { reinterpret_cast<LoadAnims_t>(meridian::rebase(0x00591540))(a0, a1); }
  // 0x0059AE70  conf=0.97  ?SetProperty@PhysController@@QAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::PhysController *, char *, ::property *);
  inline int SetProperty(::PhysController * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0059AE70))(a0, a1, a2); }
  // 0x00595170  conf=0.97  ?UpdateCinemaAnim@PhysController@@QAEXXZ
  using UpdateCinemaAnim_t = void (__thiscall*)(::PhysController *);
  inline void UpdateCinemaAnim(::PhysController * a0) { reinterpret_cast<UpdateCinemaAnim_t>(meridian::rebase(0x00595170))(a0); }
  // 0x00594990  conf=0.781  ?UpdateHeadTracking@PhysController@@QAEXMMH@Z
  using UpdateHeadTracking_t = void (__thiscall*)(::PhysController *, float, float, int);
  inline void UpdateHeadTracking(::PhysController * a0, float a1, float a2, int a3) { reinterpret_cast<UpdateHeadTracking_t>(meridian::rebase(0x00594990))(a0, a1, a2, a3); }
} // PhysController_

// ===== Pickup =====  (4 functions)  ->  namespace Pickup_
namespace Pickup_ {
  // 0x004B2600  conf=0.75  ?BreakDownCP@pickup@@SAXAAUCPBreakDown@@HH@Z
  using BreakDownCP_t = void (__cdecl*)(::CPBreakDown *, int, int);
  inline void BreakDownCP(::CPBreakDown * a0, int a1, int a2) { reinterpret_cast<BreakDownCP_t>(meridian::rebase(0x004B2600))(a0, a1, a2); }
  // 0x004B2740  conf=0.78  ?FindSafeSpawnPoint@pickup@@SAXABUvector3@@_KAAU2@MMM@Z
  using FindSafeSpawnPoint_t = void (__cdecl*)(::vector3 *, __uint64, ::vector3 *, float, float, float);
  inline void FindSafeSpawnPoint(::vector3 * a0, __uint64 a1, ::vector3 * a2, float a3, float a4, float a5) { reinterpret_cast<FindSafeSpawnPoint_t>(meridian::rebase(0x004B2740))(a0, a1, a2, a3, a4, a5); }
  // 0x004B3180  conf=0.774  ?SpawnChestItemPickup@pickup@@SAXUvector3@@0H_KM@Z
  using SpawnChestItemPickup_t = void (__cdecl*)(::vector3, ::vector3, int, __uint64, float);
  inline void SpawnChestItemPickup(::vector3 a0, ::vector3 a1, int a2, __uint64 a3, float a4) { reinterpret_cast<SpawnChestItemPickup_t>(meridian::rebase(0x004B3180))(a0, a1, a2, a3, a4); }
  // 0x004B2A60  conf=0.756  ?SpawnCouragePickups@pickup@@SAXHABUvector3@@_KH@Z
  using SpawnCouragePickups_t = void (__cdecl*)(int, ::vector3 *, __uint64, int);
  inline void SpawnCouragePickups(int a0, ::vector3 * a1, __uint64 a2, int a3) { reinterpret_cast<SpawnCouragePickups_t>(meridian::rebase(0x004B2A60))(a0, a1, a2, a3); }
} // Pickup_

// ===== Projectile =====  (12 functions)  ->  namespace Projectile_
namespace Projectile_ {
  // 0x004B52B0  conf=0.774  ?CreateProjectile@Projectile@@SA_KVxstring@@_KUvector3@@2@Z
  using CreateProjectile_t = __uint64 (__cdecl*)(::xstring, __uint64, ::vector3, ::vector3);
  inline __uint64 CreateProjectile(::xstring a0, __uint64 a1, ::vector3 a2, ::vector3 a3) { return reinterpret_cast<CreateProjectile_t>(meridian::rebase(0x004B52B0))(a0, a1, a2, a3); }
  // 0x004B53A0  conf=0.846  ?CreateProjectile@Projectile@@SA_KW4eProjectileType@1@_KUvector3@@2@Z
  inline void* CreateProjectile_4B53A0_at() { return meridian::rebase(0x004B53A0); } // __uint64 __cdecl CreateProjectile(eProjectileType, __uint64, vector3, vector3)
  // 0x004B7CE0  conf=0.791  ?Impact@Projectile@@QAEHABUcollision@collision_mgr@@@Z
  using Impact_t = int (__thiscall*)(::Projectile *, ::collision *);
  inline int Impact(::Projectile * a0, ::collision * a1) { return reinterpret_cast<Impact_t>(meridian::rebase(0x004B7CE0))(a0, a1); }
  // 0x004B8450  conf=0.747  ?InitSwoosh@Projectile@@QAEXEEUxcolor@@PBD@Z
  inline void* InitSwoosh_at() { return meridian::rebase(0x004B8450); } // void __thiscall InitSwoosh(Projectile *, uchar, uchar, xcolor, char *)
  // 0x004B81C0  conf=0.681  ?InitTrail@Projectile@@QAEXXZ
  using InitTrail_t = void (__thiscall*)(::Projectile *);
  inline void InitTrail(::Projectile * a0) { reinterpret_cast<InitTrail_t>(meridian::rebase(0x004B81C0))(a0); }
  // 0x004B83E0  conf=0.783  ?KillTrail@Projectile@@QAEXXZ
  using KillTrail_t = void (__thiscall*)(::Projectile *);
  inline void KillTrail(::Projectile * a0) { reinterpret_cast<KillTrail_t>(meridian::rebase(0x004B83E0))(a0); }
  // 0x004B6230  conf=0.747  ?LightningDischargeAttack@Projectile@@SAX_KUvector3@@1@Z
  using LightningDischargeAttack_t = void (__cdecl*)(__uint64, ::vector3, ::vector3);
  inline void LightningDischargeAttack(__uint64 a0, ::vector3 a1, ::vector3 a2) { reinterpret_cast<LightningDischargeAttack_t>(meridian::rebase(0x004B6230))(a0, a1, a2); }
  // 0x004B66E0  conf=0.744  ?OnAdvanceLogic@Projectile@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::Projectile *, float);
  inline void OnAdvanceLogic(::Projectile * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004B66E0))(a0, a1); }
  // 0x004E3F20  conf=0.704  ?Render@Projectile@@UAEXXZ
  using Render_t = void (__thiscall*)(::Projectile *);
  inline void Render(::Projectile * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x004E3F20))(a0); }
  // 0x004B7B20  conf=0.723  ?SetupBBox@Projectile@@QAEXAAVmatrix4@@@Z
  using SetupBBox_t = void (__thiscall*)(::Projectile *, ::matrix4 *);
  inline void SetupBBox(::Projectile * a0, ::matrix4 * a1) { reinterpret_cast<SetupBBox_t>(meridian::rebase(0x004B7B20))(a0, a1); }
  // 0x004B84E0  conf=0.703  ?SetupShadow@Projectile@@QAEXXZ
  using SetupShadow_t = void (__thiscall*)(::Projectile *);
  inline void SetupShadow(::Projectile * a0) { reinterpret_cast<SetupShadow_t>(meridian::rebase(0x004B84E0))(a0); }
  // 0x004B82C0  conf=0.798  ?UpdateTrail@Projectile@@QAEXXZ
  using UpdateTrail_t = void (__thiscall*)(::Projectile *);
  inline void UpdateTrail(::Projectile * a0) { reinterpret_cast<UpdateTrail_t>(meridian::rebase(0x004B82C0))(a0); }
} // Projectile_

// ===== PushBox =====  (1 functions)  ->  namespace PushBox_
namespace PushBox_ {
  // 0x004BB9B0  conf=0.75  ?CopyCollision@@YAXAAUcollision@collision_mgr@@ABU12@@Z
  using CopyCollision_t = void (__cdecl*)(::collision *, ::collision *);
  inline void CopyCollision(::collision * a0, ::collision * a1) { reinterpret_cast<CopyCollision_t>(meridian::rebase(0x004BB9B0))(a0, a1); }
} // PushBox_

// ===== RangedAttackState =====  (1 functions)  ->  namespace RangedAttackState_
namespace RangedAttackState_ {
  // 0x00632F20  conf=0.97  ?UpdateState@RangedAttackState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x00632F20); } // eStateType __thiscall UpdateState(RangedAttackState *, int)
} // RangedAttackState_

// ===== RetreatState =====  (1 functions)  ->  namespace RetreatState_
namespace RetreatState_ {
  // 0x005B9D10  conf=0.93  ?ChangePhase@RetreatState@@UAEXH@Z
  using ChangePhase_t = void (__thiscall*)(::RetreatState *, int);
  inline void ChangePhase(::RetreatState * a0, int a1) { reinterpret_cast<ChangePhase_t>(meridian::rebase(0x005B9D10))(a0, a1); }
} // RetreatState_

// ===== RigidInstance =====  (1 functions)  ->  namespace RigidInstance_
namespace RigidInstance_ {
  // 0x004C7A10  conf=0.97  ?FireAndForget@rigid_instance@@SAXABUvector3@@ABUradian3@@0PBD2HUxcolor@@HH_K@Z
  inline void* FireAndForget_at() { return meridian::rebase(0x004C7A10); } // void __cdecl FireAndForget(vector3 *, radian3 *, vector3 *, char *, char *, int, xcolor, int, int, __uint64)
} // RigidInstance_

// ===== RockBadgerAttackState =====  (1 functions)  ->  namespace RockBadgerAttackState_
namespace RockBadgerAttackState_ {
  // 0x00625C60  conf=0.97  ?UpdateState@RockBadgerAttackState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x00625C60); } // eStateType __thiscall UpdateState(RockBadgerAttackState *, int)
} // RockBadgerAttackState_

// ===== SavePedestal =====  (4 functions)  ->  namespace SavePedestal_
namespace SavePedestal_ {
  // 0x004CDF40  conf=0.715  ?ActivateSavePedestalFX@@YAXXZ
  using ActivateSavePedestalFX_t = void (__cdecl*)();
  inline void ActivateSavePedestalFX() { reinterpret_cast<ActivateSavePedestalFX_t>(meridian::rebase(0x004CDF40))(); }
  // 0x004CDFA0  conf=0.75  ?GetActiveSavePedestal@@YA_KXZ
  using GetActiveSavePedestal_t = __uint64 (__cdecl*)();
  inline __uint64 GetActiveSavePedestal() { return reinterpret_cast<GetActiveSavePedestal_t>(meridian::rebase(0x004CDFA0))(); }
  // 0x004CDF30  conf=0.8  ?GetLastSavePedestal@@YAXXZ
  using GetLastSavePedestal_t = void (__cdecl*)();
  inline void GetLastSavePedestal() { reinterpret_cast<GetLastSavePedestal_t>(meridian::rebase(0x004CDF30))(); }
  // 0x004CDF70  conf=0.767  ?SetActiveSavePedestal@@YAXAB_K@Z
  using SetActiveSavePedestal_t = void (__cdecl*)(__uint64 *);
  inline void SetActiveSavePedestal(__uint64 * a0) { reinterpret_cast<SetActiveSavePedestal_t>(meridian::rebase(0x004CDF70))(a0); }
} // SavePedestal_

// ===== SenseController =====  (8 functions)  ->  namespace SenseController_
namespace SenseController_ {
  // 0x005AA9E0  conf=0.714  ?CanHear@SenseController@@QAEHUvector3@@@Z
  using CanHear_t = int (__thiscall*)(::SenseController *, ::vector3);
  inline int CanHear(::SenseController * a0, ::vector3 a1) { return reinterpret_cast<CanHear_t>(meridian::rebase(0x005AA9E0))(a0, a1); }
  // 0x005AB710  conf=0.696  ?CanHear@SenseController@@QAEH_KH@Z
  using CanHear_5AB710_t = int (__thiscall*)(::SenseController *, __uint64, int);
  inline int CanHear_5AB710(::SenseController * a0, __uint64 a1, int a2) { return reinterpret_cast<CanHear_5AB710_t>(meridian::rebase(0x005AB710))(a0, a1, a2); }
  // 0x005AB600  conf=0.688  ?CanHearLoud@SenseController@@QAEH_KH@Z
  using CanHearLoud_t = int (__thiscall*)(::SenseController *, __uint64, int);
  inline int CanHearLoud(::SenseController * a0, __uint64 a1, int a2) { return reinterpret_cast<CanHearLoud_t>(meridian::rebase(0x005AB600))(a0, a1, a2); }
  // 0x005ABCD0  conf=0.97  ?CanSee@SenseController@@QAEH_KHH@Z
  using CanSee_t = int (__thiscall*)(::SenseController *, __uint64, int, int);
  inline int CanSee(::SenseController * a0, __uint64 a1, int a2, int a3) { return reinterpret_cast<CanSee_t>(meridian::rebase(0x005ABCD0))(a0, a1, a2, a3); }
  // 0x005AB3F0  conf=0.696  ?CanSmell@SenseController@@QAEH_KH@Z
  using CanSmell_t = int (__thiscall*)(::SenseController *, __uint64, int);
  inline int CanSmell(::SenseController * a0, __uint64 a1, int a2) { return reinterpret_cast<CanSmell_t>(meridian::rebase(0x005AB3F0))(a0, a1, a2); }
  // 0x005AA880  conf=0.688  ?IsAbleToSense@SenseController@@QAEH_KH@Z
  using IsAbleToSense_t = int (__thiscall*)(::SenseController *, __uint64, int);
  inline int IsAbleToSense(::SenseController * a0, __uint64 a1, int a2) { return reinterpret_cast<IsAbleToSense_t>(meridian::rebase(0x005AA880))(a0, a1, a2); }
  // 0x005AA750  conf=0.585  ?SetBlind@SenseController@@QAEXH@Z
  using SetBlind_t = void (__thiscall*)(::SenseController *, int);
  inline void SetBlind(::SenseController * a0, int a1) { reinterpret_cast<SetBlind_t>(meridian::rebase(0x005AA750))(a0, a1); }
  // 0x005AAE10  conf=0.651  ?SoundEvent@SenseController@@QAEX_KUvector3@@M@Z
  using SoundEvent_t = void (__thiscall*)(::SenseController *, __uint64, ::vector3, float);
  inline void SoundEvent(::SenseController * a0, __uint64 a1, ::vector3 a2, float a3) { reinterpret_cast<SoundEvent_t>(meridian::rebase(0x005AAE10))(a0, a1, a2, a3); }
} // SenseController_

// ===== Slider =====  (2 functions)  ->  namespace Slider_
namespace Slider_ {
  // 0x004D0700  conf=0.794  ?PropertyGetVector3@@YAHPBDAAUproperty@@0ABUvector3@@@Z
  using PropertyGetVector3_t = int (__cdecl*)(char *, ::property *, char *, ::vector3 *);
  inline int PropertyGetVector3(char * a0, ::property * a1, char * a2, ::vector3 * a3) { return reinterpret_cast<PropertyGetVector3_t>(meridian::rebase(0x004D0700))(a0, a1, a2, a3); }
  // 0x004BFED0  conf=0.795  ?PropertySetVector3@@YAHPBDABUproperty@@0AAUvector3@@@Z
  using PropertySetVector3_t = int (__cdecl*)(char *, ::property *, char *, ::vector3 *);
  inline int PropertySetVector3(char * a0, ::property * a1, char * a2, ::vector3 * a3) { return reinterpret_cast<PropertySetVector3_t>(meridian::rebase(0x004BFED0))(a0, a1, a2, a3); }
} // Slider_

// ===== SmaugAlertState =====  (5 functions)  ->  namespace SmaugAlertState_
namespace SmaugAlertState_ {
  // 0x005BAFA0  conf=0.97  ?BlendAnimsToTarget@SmaugAlertState@@QAEXXZ
  using BlendAnimsToTarget_t = void (__thiscall*)(::SmaugAlertState *);
  inline void BlendAnimsToTarget(::SmaugAlertState * a0) { reinterpret_cast<BlendAnimsToTarget_t>(meridian::rebase(0x005BAFA0))(a0); }
  // 0x005BB680  conf=0.97  ?EnumerateProperties@SmaugAlertState@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::SmaugAlertState *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::SmaugAlertState * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005BB680))(a0, a1); }
  // 0x005BA860  conf=0.97  ?SetProperty@SmaugAlertState@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::SmaugAlertState *, char *, ::property *);
  inline int SetProperty(::SmaugAlertState * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005BA860))(a0, a1, a2); }
  // 0x005B96E0  conf=0.97  ??0SmaugAlertState@@QAE@PBDPAVStateController@@@Z
  using ctor_t = undefined (__thiscall*)(::SmaugAlertState *, char *, ::StateController *);
  inline undefined ctor(::SmaugAlertState * a0, char * a1, ::StateController * a2) { return reinterpret_cast<ctor_t>(meridian::rebase(0x005B96E0))(a0, a1, a2); }
  // 0x005BD7D0  conf=0.85  ?UpdateTail@SmaugAlertState@@QAEXM@Z
  using UpdateTail_t = void (__thiscall*)(::SmaugAlertState *, float);
  inline void UpdateTail(::SmaugAlertState * a0, float a1) { reinterpret_cast<UpdateTail_t>(meridian::rebase(0x005BD7D0))(a0, a1); }
} // SmaugAlertState_

// ===== SmaugAttackState =====  (7 functions)  ->  namespace SmaugAttackState_
namespace SmaugAttackState_ {
  // 0x00619660  conf=0.97  ?CheckBilboForSafety@SmaugAttackState@@QAEHXZ
  using CheckBilboForSafety_t = int (__thiscall*)(::SmaugAttackState *);
  inline int CheckBilboForSafety(::SmaugAttackState * a0) { return reinterpret_cast<CheckBilboForSafety_t>(meridian::rebase(0x00619660))(a0); }
  // 0x00617880  conf=0.779  ?DebugRender@SmaugAttackState@@UAEXXZ
  using DebugRender_t = void (__thiscall*)(::SmaugAttackState *);
  inline void DebugRender(::SmaugAttackState * a0) { reinterpret_cast<DebugRender_t>(meridian::rebase(0x00617880))(a0); }
  // 0x006197D0  conf=0.73  ?InitFireFx@SmaugAttackState@@IAEXXZ
  using InitFireFx_t = void (__thiscall*)(::SmaugAttackState *);
  inline void InitFireFx(::SmaugAttackState * a0) { reinterpret_cast<InitFireFx_t>(meridian::rebase(0x006197D0))(a0); }
  // 0x006140F0  conf=0.97  ?SetSafetyZoneCount@SmaugAttackState@@QAEXI@Z
  using SetSafetyZoneCount_t = void (__thiscall*)(::SmaugAttackState *, uint);
  inline void SetSafetyZoneCount(::SmaugAttackState * a0, uint a1) { reinterpret_cast<SetSafetyZoneCount_t>(meridian::rebase(0x006140F0))(a0, a1); }
  // 0x006193C0  conf=0.76  ?UpdateBlockers@SmaugAttackState@@QAEXM@Z
  using UpdateBlockers_t = void (__thiscall*)(::SmaugAttackState *, float);
  inline void UpdateBlockers(::SmaugAttackState * a0, float a1) { reinterpret_cast<UpdateBlockers_t>(meridian::rebase(0x006193C0))(a0, a1); }
  // 0x00618B50  conf=0.97  ?UpdateFireStrands@SmaugAttackState@@QAEXM@Z
  using UpdateFireStrands_t = void (__thiscall*)(::SmaugAttackState *, float);
  inline void UpdateFireStrands(::SmaugAttackState * a0, float a1) { reinterpret_cast<UpdateFireStrands_t>(meridian::rebase(0x00618B50))(a0, a1); }
  // 0x00618CD0  conf=0.73  ?UpdateHeadPosition@SmaugAttackState@@QAEXAAUvector3@@@Z
  using UpdateHeadPosition_t = void (__thiscall*)(::SmaugAttackState *, ::vector3 *);
  inline void UpdateHeadPosition(::SmaugAttackState * a0, ::vector3 * a1) { reinterpret_cast<UpdateHeadPosition_t>(meridian::rebase(0x00618CD0))(a0, a1); }
} // SmaugAttackState_

// ===== SmaugIdleState =====  (1 functions)  ->  namespace SmaugIdleState_
namespace SmaugIdleState_ {
  // 0x005BA910  conf=0.85  ?UpdateTail@SmaugIdleState@@QAEXM@Z
  using UpdateTail_t = void (__thiscall*)(::SmaugIdleState *, float);
  inline void UpdateTail(::SmaugIdleState * a0, float a1) { reinterpret_cast<UpdateTail_t>(meridian::rebase(0x005BA910))(a0, a1); }
} // SmaugIdleState_

// ===== SpecialSurfaces =====  (1 functions)  ->  namespace SpecialSurfaces_
namespace SpecialSurfaces_ {
  // 0x004D1140  conf=0.75  ?GetSurfaceTypeNumber@special_surfaces@@KAHPBD@Z
  using GetSurfaceTypeNumber_t = int (__cdecl*)(char *);
  inline int GetSurfaceTypeNumber(char * a0) { return reinterpret_cast<GetSurfaceTypeNumber_t>(meridian::rebase(0x004D1140))(a0); }
} // SpecialSurfaces_

// ===== SpiderAlertState =====  (1 functions)  ->  namespace SpiderAlertState_
namespace SpiderAlertState_ {
  // 0x0062FF30  conf=0.97  ?UpdatePhase@SpiderAlertState@@UAEHMH@Z
  using UpdatePhase_t = int (__thiscall*)(::SpiderAlertState *, float, int);
  inline int UpdatePhase(::SpiderAlertState * a0, float a1, int a2) { return reinterpret_cast<UpdatePhase_t>(meridian::rebase(0x0062FF30))(a0, a1, a2); }
} // SpiderAlertState_

// ===== StateController =====  (4 functions)  ->  namespace StateController_
namespace StateController_ {
  // 0x00580A90  conf=0.576  ?GetNextConversation@StateController@@QAE?AVxstring@@XZ
  using GetNextConversation_t = ::xstring (__thiscall*)(::StateController *);
  inline ::xstring GetNextConversation(::StateController * a0) { return reinterpret_cast<GetNextConversation_t>(meridian::rebase(0x00580A90))(a0); }
  // 0x005B2100  conf=0.849  ?GetProperty@StateController@@UAE?AUproperty@@PBDPAVNPCObject@@@Z
  using GetProperty_t = ::property (__thiscall*)(::StateController *, char *, ::NPCObject *);
  inline ::property GetProperty(::StateController * a0, char * a1, ::NPCObject * a2) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005B2100))(a0, a1, a2); }
  // 0x005AD7B0  conf=0.97  ?LoadStates@StateController@@QAEXVxwstring@@@Z
  using LoadStates_t = void (__thiscall*)(::StateController *, ::xwstring);
  inline void LoadStates(::StateController * a0, ::xwstring a1) { reinterpret_cast<LoadStates_t>(meridian::rebase(0x005AD7B0))(a0, a1); }
  // 0x005B0190  conf=0.97  ?OnImport@StateController@@QAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::StateController *, ::bin_in *);
  inline void OnImport(::StateController * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005B0190))(a0, a1); }
} // StateController_

// ===== Switch =====  (9 functions)  ->  namespace Switch_
namespace Switch_ {
  // 0x0044F030  conf=0.75  ?Activate@Switch@@QAEXXZ
  using Activate_t = void (__thiscall*)(::Switch *);
  inline void Activate(::Switch * a0) { reinterpret_cast<Activate_t>(meridian::rebase(0x0044F030))(a0); }
  // 0x004D3090  conf=0.799  ?EnumerateProperties@Switch@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::Switch *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::Switch * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004D3090))(a0, a1); }
  // 0x004D2F10  conf=0.683  ?GetOn@Switch@@QAEHXZ
  using GetOn_t = int (__thiscall*)(::Switch *);
  inline int GetOn(::Switch * a0) { return reinterpret_cast<GetOn_t>(meridian::rebase(0x004D2F10))(a0); }
  // 0x004D2F40  conf=0.75  ?GetRockCanTrigger@Switch@@QAEHXZ
  using GetRockCanTrigger_t = int (__thiscall*)(::Switch *);
  inline int GetRockCanTrigger(::Switch * a0) { return reinterpret_cast<GetRockCanTrigger_t>(meridian::rebase(0x004D2F40))(a0); }
  // 0x004D2610  conf=0.736  ?Init@Switch@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::Switch *, ::vector3 *, ::radian3 *, ::vector3 *, ::bbox *);
  inline void Init(::Switch * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3, ::bbox * a4) { reinterpret_cast<Init_t>(meridian::rebase(0x004D2610))(a0, a1, a2, a3, a4); }
  // 0x004D2CC0  conf=0.97  ?OnExport@Switch@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::Switch *, ::bin_out *);
  inline void OnExport(::Switch * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004D2CC0))(a0, a1); }
  // 0x004D2D50  conf=0.97  ?OnImport@Switch@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::Switch *, ::bin_in *);
  inline void OnImport(::Switch * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004D2D50))(a0, a1); }
  // 0x004D2F20  conf=0.8  ?SetOn@Switch@@QAEXH@Z
  using SetOn_t = void (__thiscall*)(::Switch *, int);
  inline void SetOn(::Switch * a0, int a1) { reinterpret_cast<SetOn_t>(meridian::rebase(0x004D2F20))(a0, a1); }
  // 0x004D2F50  conf=0.97  ?Toggle@Switch@@QAEXXZ
  using Toggle_t = void (__thiscall*)(::Switch *);
  inline void Toggle(::Switch * a0) { reinterpret_cast<Toggle_t>(meridian::rebase(0x004D2F50))(a0); }
} // Switch_

// ===== TakeCoverState =====  (1 functions)  ->  namespace TakeCoverState_
namespace TakeCoverState_ {
  // 0x00634100  conf=0.97  ?UpdateState@TakeCoverState@@UAE?AW4eStateType@AIState@@H@Z
  inline void* UpdateState_at() { return meridian::rebase(0x00634100); } // eStateType __thiscall UpdateState(TakeCoverState *, int)
} // TakeCoverState_

// ===== TreasureChest =====  (1 functions)  ->  namespace TreasureChest_
namespace TreasureChest_ {
  // 0x0064A360  conf=0.544  ?CalculateTargetPosition@@YA?AUvector3@@HH@Z
  using CalculateTargetPosition_t = ::vector3 (__cdecl*)(int, int);
  inline ::vector3 CalculateTargetPosition(int a0, int a1) { return reinterpret_cast<CalculateTargetPosition_t>(meridian::rebase(0x0064A360))(a0, a1); }
} // TreasureChest_

// ===== Trigger =====  (8 functions)  ->  namespace Trigger_
namespace Trigger_ {
  // 0x0040CC40  conf=0.725  ?ActivateLoadTrigger@@YAXPBD@Z
  using ActivateLoadTrigger_t = void (__cdecl*)(char *);
  inline void ActivateLoadTrigger(char * a0) { reinterpret_cast<ActivateLoadTrigger_t>(meridian::rebase(0x0040CC40))(a0); }
  // 0x004DBA10  conf=0.97  ?AddInvenItem@@YAXPBDH@Z
  using AddInvenItem_t = void (__cdecl*)(char *, int);
  inline void AddInvenItem(char * a0, int a1) { reinterpret_cast<AddInvenItem_t>(meridian::rebase(0x004DBA10))(a0, a1); }
  // 0x004DBCD0  conf=0.743  ?HideRigidInstanceByName@@YAXPBDH@Z
  using HideRigidInstanceByName_t = void (__cdecl*)(char *, int);
  inline void HideRigidInstanceByName(char * a0, int a1) { reinterpret_cast<HideRigidInstanceByName_t>(meridian::rebase(0x004DBCD0))(a0, a1); }
  // 0x0040F0E0  conf=0.722  ?xsc_ActivateLoadTrigger@@YAXPAE@Z
  using xsc_ActivateLoadTrigger_t = void (__cdecl*)(uchar *);
  inline void xsc_ActivateLoadTrigger(uchar * a0) { reinterpret_cast<xsc_ActivateLoadTrigger_t>(meridian::rebase(0x0040F0E0))(a0); }
  // 0x005E0F30  conf=0.731  ?xsc_EnableFireFXAtVolume@@YAXPAE@Z
  using xsc_EnableFireFXAtVolume_t = void (__cdecl*)(uchar *);
  inline void xsc_EnableFireFXAtVolume(uchar * a0) { reinterpret_cast<xsc_EnableFireFXAtVolume_t>(meridian::rebase(0x005E0F30))(a0); }
  // 0x005E05B0  conf=0.735  ?xsc_EnableTriggerByName@@YAXPAE@Z
  using xsc_EnableTriggerByName_t = void (__cdecl*)(uchar *);
  inline void xsc_EnableTriggerByName(uchar * a0) { reinterpret_cast<xsc_EnableTriggerByName_t>(meridian::rebase(0x005E05B0))(a0); }
  // 0x005DA180  conf=0.74  ?xsc_HideRigidInstanceByName@@YAXPAE@Z
  using xsc_HideRigidInstanceByName_t = void (__cdecl*)(uchar *);
  inline void xsc_HideRigidInstanceByName(uchar * a0) { reinterpret_cast<xsc_HideRigidInstanceByName_t>(meridian::rebase(0x005DA180))(a0); }
  // 0x004DB990  conf=0.787  ?xsc_StartMineCartRide@@YAXPAE@Z
  using xsc_StartMineCartRide_t = void (__cdecl*)(uchar *);
  inline void xsc_StartMineCartRide(uchar * a0) { reinterpret_cast<xsc_StartMineCartRide_t>(meridian::rebase(0x004DB990))(a0); }
} // Trigger_

// ===== TriggerBilboHasItem =====  (2 functions)  ->  namespace TriggerBilboHasItem_
namespace TriggerBilboHasItem_ {
  // 0x005F2660  conf=0.97  ?SetProperty@TriggerBilboHasItem@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerBilboHasItem *, char *, ::property *);
  inline int SetProperty(::TriggerBilboHasItem * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F2660))(a0, a1, a2); }
  // 0x005F7960  conf=0.97  ??0TriggerBilboHasItem@@QAE@H@Z
  using ctor_t = undefined (__thiscall*)(::TriggerBilboHasItem *, int);
  inline undefined ctor(::TriggerBilboHasItem * a0, int a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x005F7960))(a0, a1); }
} // TriggerBilboHasItem_

// ===== TriggerBilboPicksUpItem =====  (1 functions)  ->  namespace TriggerBilboPicksUpItem_
namespace TriggerBilboPicksUpItem_ {
  // 0x00606610  conf=0.97  ?SetProperty@TriggerBilboPicksUpItem@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerBilboPicksUpItem *, char *, ::property *);
  inline int SetProperty(::TriggerBilboPicksUpItem * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00606610))(a0, a1, a2); }
} // TriggerBilboPicksUpItem_

// ===== TriggerCharacterPlayingAnimation =====  (1 functions)  ->  namespace TriggerCharacterPlayingAnimation_
namespace TriggerCharacterPlayingAnimation_ {
  // 0x005FC440  conf=0.97  ?EnumerateProperties@TriggerCharacterPlayingAnimation@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::TriggerCharacterPlayingAnimation *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::TriggerCharacterPlayingAnimation * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005FC440))(a0, a1); }
} // TriggerCharacterPlayingAnimation_

// ===== TriggerChestOpened =====  (1 functions)  ->  namespace TriggerChestOpened_
namespace TriggerChestOpened_ {
  // 0x005F4400  conf=0.97  ?GetProperty@TriggerChestOpened@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerChestOpened *, char *);
  inline ::property GetProperty(::TriggerChestOpened * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005F4400))(a0, a1); }
} // TriggerChestOpened_

// ===== TriggerCinemaBegins =====  (1 functions)  ->  namespace TriggerCinemaBegins_
namespace TriggerCinemaBegins_ {
  // 0x00600840  conf=0.97  ?SetProperty@TriggerCinemaBegins@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerCinemaBegins *, char *, ::property *);
  inline int SetProperty(::TriggerCinemaBegins * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00600840))(a0, a1, a2); }
} // TriggerCinemaBegins_

// ===== TriggerCinemaFinished =====  (2 functions)  ->  namespace TriggerCinemaFinished_
namespace TriggerCinemaFinished_ {
  // 0x005FF460  conf=0.97  ?GetProperty@TriggerCinemaFinished@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerCinemaFinished *, char *);
  inline ::property GetProperty(::TriggerCinemaFinished * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005FF460))(a0, a1); }
  // 0x005FE890  conf=0.97  ??0TriggerCinemaFinished@@QAE@H@Z
  using ctor_t = undefined (__thiscall*)(::TriggerCinemaFinished *, int);
  inline undefined ctor(::TriggerCinemaFinished * a0, int a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x005FE890))(a0, a1); }
} // TriggerCinemaFinished_

// ===== TriggerConversationComplete =====  (1 functions)  ->  namespace TriggerConversationComplete_
namespace TriggerConversationComplete_ {
  // 0x005F2DF0  conf=0.608  ?SetProperty@TriggerConversationComplete@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerConversationComplete *, char *, ::property *);
  inline int SetProperty(::TriggerConversationComplete * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F2DF0))(a0, a1, a2); }
} // TriggerConversationComplete_

// ===== TriggerEffectFinishes =====  (2 functions)  ->  namespace TriggerEffectFinishes_
namespace TriggerEffectFinishes_ {
  // 0x00604300  conf=0.97  ?GetProperty@TriggerEffectFinishes@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerEffectFinishes *, char *);
  inline ::property GetProperty(::TriggerEffectFinishes * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x00604300))(a0, a1); }
  // 0x00604240  conf=0.97  ?SetProperty@TriggerEffectFinishes@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerEffectFinishes *, char *, ::property *);
  inline int SetProperty(::TriggerEffectFinishes * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00604240))(a0, a1, a2); }
} // TriggerEffectFinishes_

// ===== TriggerGold =====  (1 functions)  ->  namespace TriggerGold_
namespace TriggerGold_ {
  // 0x005F3480  conf=0.97  ?EnumerateProperties@TriggerGold@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::TriggerGold *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::TriggerGold * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005F3480))(a0, a1); }
} // TriggerGold_

// ===== TriggerNPCBeginsAction =====  (2 functions)  ->  namespace TriggerNPCBeginsAction_
namespace TriggerNPCBeginsAction_ {
  // 0x005F7A30  conf=0.97  ?GetProperty@TriggerNPCBeginsAction@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerNPCBeginsAction *, char *);
  inline ::property GetProperty(::TriggerNPCBeginsAction * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005F7A30))(a0, a1); }
  // 0x005FD4C0  conf=0.97  ?SetProperty@TriggerNPCBeginsAction@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerNPCBeginsAction *, char *, ::property *);
  inline int SetProperty(::TriggerNPCBeginsAction * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005FD4C0))(a0, a1, a2); }
} // TriggerNPCBeginsAction_

// ===== TriggerNPCChangesState =====  (2 functions)  ->  namespace TriggerNPCChangesState_
namespace TriggerNPCChangesState_ {
  // 0x005F5B10  conf=0.97  ?HandleMessage@TriggerNPCChangesState@@UAEHPAUMessageInfo@@@Z
  using HandleMessage_t = int (__thiscall*)(::TriggerNPCChangesState *, ::MessageInfo *);
  inline int HandleMessage(::TriggerNPCChangesState * a0, ::MessageInfo * a1) { return reinterpret_cast<HandleMessage_t>(meridian::rebase(0x005F5B10))(a0, a1); }
  // 0x005F60B0  conf=0.97  ?SetProperty@TriggerNPCChangesState@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerNPCChangesState *, char *, ::property *);
  inline int SetProperty(::TriggerNPCChangesState * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F60B0))(a0, a1, a2); }
} // TriggerNPCChangesState_

// ===== TriggerNPCFinishesGoalList =====  (3 functions)  ->  namespace TriggerNPCFinishesGoalList_
namespace TriggerNPCFinishesGoalList_ {
  // 0x005FA970  conf=0.97  ?GetProperty@TriggerNPCFinishesGoalList@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerNPCFinishesGoalList *, char *);
  inline ::property GetProperty(::TriggerNPCFinishesGoalList * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005FA970))(a0, a1); }
  // 0x005FA8B0  conf=0.97  ?SetProperty@TriggerNPCFinishesGoalList@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerNPCFinishesGoalList *, char *, ::property *);
  inline int SetProperty(::TriggerNPCFinishesGoalList * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005FA8B0))(a0, a1, a2); }
  // 0x005FA1A0  conf=0.97  ??0TriggerNPCFinishesGoalList@@QAE@H@Z
  using ctor_t = undefined (__thiscall*)(::TriggerNPCFinishesGoalList *, int);
  inline undefined ctor(::TriggerNPCFinishesGoalList * a0, int a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x005FA1A0))(a0, a1); }
} // TriggerNPCFinishesGoalList_

// ===== TriggerNPCHit =====  (1 functions)  ->  namespace TriggerNPCHit_
namespace TriggerNPCHit_ {
  // 0x005F6EA0  conf=0.97  ?SetProperty@TriggerNPCHit@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerNPCHit *, char *, ::property *);
  inline int SetProperty(::TriggerNPCHit * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F6EA0))(a0, a1, a2); }
} // TriggerNPCHit_

// ===== TriggerNPCInState =====  (1 functions)  ->  namespace TriggerNPCInState_
namespace TriggerNPCInState_ {
  // 0x005FC800  conf=0.97  ?SetProperty@TriggerNPCInState@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerNPCInState *, char *, ::property *);
  inline int SetProperty(::TriggerNPCInState * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005FC800))(a0, a1, a2); }
} // TriggerNPCInState_

// ===== TriggerNPCSensesCharacter =====  (1 functions)  ->  namespace TriggerNPCSensesCharacter_
namespace TriggerNPCSensesCharacter_ {
  // 0x00602520  conf=0.97  ?Test@TriggerNPCSensesCharacter@@UAEHM@Z
  using Test_t = int (__thiscall*)(::TriggerNPCSensesCharacter *, float);
  inline int Test(::TriggerNPCSensesCharacter * a0, float a1) { return reinterpret_cast<Test_t>(meridian::rebase(0x00602520))(a0, a1); }
} // TriggerNPCSensesCharacter_

// ===== TriggerOnVine =====  (1 functions)  ->  namespace TriggerOnVine_
namespace TriggerOnVine_ {
  // 0x005F4DB0  conf=0.97  ?GetProperty@TriggerOnVine@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerOnVine *, char *);
  inline ::property GetProperty(::TriggerOnVine * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005F4DB0))(a0, a1); }
} // TriggerOnVine_

// ===== TriggerQuestComplete =====  (1 functions)  ->  namespace TriggerQuestComplete_
namespace TriggerQuestComplete_ {
  // 0x00601E60  conf=0.97  ?GetProperty@TriggerQuestComplete@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerQuestComplete *, char *);
  inline ::property GetProperty(::TriggerQuestComplete * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x00601E60))(a0, a1); }
} // TriggerQuestComplete_

// ===== TriggerRigidAnimPlaying =====  (1 functions)  ->  namespace TriggerRigidAnimPlaying_
namespace TriggerRigidAnimPlaying_ {
  // 0x00604FC0  conf=0.93  ?Test@TriggerRigidAnimPlaying@@UAEHM@Z
  using Test_t = int (__thiscall*)(::TriggerRigidAnimPlaying *, float);
  inline int Test(::TriggerRigidAnimPlaying * a0, float a1) { return reinterpret_cast<Test_t>(meridian::rebase(0x00604FC0))(a0, a1); }
} // TriggerRigidAnimPlaying_

// ===== TriggerRigidAnimStarted =====  (1 functions)  ->  namespace TriggerRigidAnimStarted_
namespace TriggerRigidAnimStarted_ {
  // 0x00604B70  conf=0.774  ?HandleMessage@TriggerRigidAnimStarted@@UAEHPAUMessageInfo@@@Z
  using HandleMessage_t = int (__thiscall*)(::TriggerRigidAnimStarted *, ::MessageInfo *);
  inline int HandleMessage(::TriggerRigidAnimStarted * a0, ::MessageInfo * a1) { return reinterpret_cast<HandleMessage_t>(meridian::rebase(0x00604B70))(a0, a1); }
} // TriggerRigidAnimStarted_

// ===== TriggerSwitchIsOn =====  (2 functions)  ->  namespace TriggerSwitchIsOn_
namespace TriggerSwitchIsOn_ {
  // 0x005FACA0  conf=0.97  ?OnImport@TriggerSwitchIsOn@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::TriggerSwitchIsOn *, ::bin_in *);
  inline void OnImport(::TriggerSwitchIsOn * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x005FACA0))(a0, a1); }
  // 0x005FB710  conf=0.97  ?SetProperty@TriggerSwitchIsOn@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerSwitchIsOn *, char *, ::property *);
  inline int SetProperty(::TriggerSwitchIsOn * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005FB710))(a0, a1, a2); }
} // TriggerSwitchIsOn_

// ===== TriggerTimedRandom =====  (1 functions)  ->  namespace TriggerTimedRandom_
namespace TriggerTimedRandom_ {
  // 0x005F5090  conf=0.97  ?SetProperty@TriggerTimedRandom@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerTimedRandom *, char *, ::property *);
  inline int SetProperty(::TriggerTimedRandom * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F5090))(a0, a1, a2); }
} // TriggerTimedRandom_

// ===== TriggerVolumeCharacter =====  (3 functions)  ->  namespace TriggerVolumeCharacter_
namespace TriggerVolumeCharacter_ {
  // 0x005F30A0  conf=0.95  ?GetProperty@TriggerVolumeCharacter@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerVolumeCharacter *, char *);
  inline ::property GetProperty(::TriggerVolumeCharacter * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005F30A0))(a0, a1); }
  // 0x005F3B90  conf=0.97  ?SetProperty@TriggerVolumeCharacter@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerVolumeCharacter *, char *, ::property *);
  inline int SetProperty(::TriggerVolumeCharacter * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x005F3B90))(a0, a1, a2); }
  // 0x005F2F60  conf=0.97  ?Test@TriggerVolumeCharacter@@UAEHM@Z
  using Test_t = int (__thiscall*)(::TriggerVolumeCharacter *, float);
  inline int Test(::TriggerVolumeCharacter * a0, float a1) { return reinterpret_cast<Test_t>(meridian::rebase(0x005F2F60))(a0, a1); }
} // TriggerVolumeCharacter_

// ===== TriggerVolumeObject =====  (3 functions)  ->  namespace TriggerVolumeObject_
namespace TriggerVolumeObject_ {
  // 0x00601970  conf=0.97  ?EnumerateProperties@TriggerVolumeObject@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::TriggerVolumeObject *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::TriggerVolumeObject * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00601970))(a0, a1); }
  // 0x00602070  conf=0.97  ?OnImport@TriggerVolumeObject@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::TriggerVolumeObject *, ::bin_in *);
  inline void OnImport(::TriggerVolumeObject * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00602070))(a0, a1); }
  // 0x006018B0  conf=0.97  ??0TriggerVolumeObject@@QAE@H@Z
  using ctor_t = undefined (__thiscall*)(::TriggerVolumeObject *, int);
  inline undefined ctor(::TriggerVolumeObject * a0, int a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x006018B0))(a0, a1); }
} // TriggerVolumeObject_

// ===== TriggerWebBreaks =====  (1 functions)  ->  namespace TriggerWebBreaks_
namespace TriggerWebBreaks_ {
  // 0x005FAE60  conf=0.97  ?EnumerateProperties@TriggerWebBreaks@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::TriggerWebBreaks *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::TriggerWebBreaks * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x005FAE60))(a0, a1); }
} // TriggerWebBreaks_

// ===== TriggerWorldTriggerToggled =====  (2 functions)  ->  namespace TriggerWorldTriggerToggled_
namespace TriggerWorldTriggerToggled_ {
  // 0x005FE950  conf=0.97  ?GetProperty@TriggerWorldTriggerToggled@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::TriggerWorldTriggerToggled *, char *);
  inline ::property GetProperty(::TriggerWorldTriggerToggled * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x005FE950))(a0, a1); }
  // 0x00473D60  conf=0.687  ?SetProperty@TriggerWorldTriggerToggled@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::TriggerWorldTriggerToggled *, char *, ::property *);
  inline int SetProperty(::TriggerWorldTriggerToggled * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00473D60))(a0, a1, a2); }
} // TriggerWorldTriggerToggled_

// ===== Version =====  (1 functions)  ->  namespace Version_
namespace Version_ {
  // 0x00502D60  conf=0.732  ?MeridianVersion@@YAPBDXZ
  using MeridianVersion_t = char * (__cdecl*)();
  inline char * MeridianVersion() { return reinterpret_cast<MeridianVersion_t>(meridian::rebase(0x00502D60))(); }
} // Version_

// ===== WarIdleState =====  (1 functions)  ->  namespace WarIdleState_
namespace WarIdleState_ {
  // 0x00632110  conf=0.97  ?OnImport@WarIdleState@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::WarIdleState *, ::bin_in *);
  inline void OnImport(::WarIdleState * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00632110))(a0, a1); }
} // WarIdleState_

// ===== WightBossAttackState =====  (1 functions)  ->  namespace WightBossAttackState_
namespace WightBossAttackState_ {
  // 0x0060A100  conf=0.97  ?UpdatePhaseStrafing@WightBossAttackState@@IAEHPAVobject@@MH@Z
  using UpdatePhaseStrafing_t = int (__thiscall*)(::WightBossAttackState *, ::object *, float, int);
  inline int UpdatePhaseStrafing(::WightBossAttackState * a0, ::object * a1, float a2, int a3) { return reinterpret_cast<UpdatePhaseStrafing_t>(meridian::rebase(0x0060A100))(a0, a1, a2, a3); }
} // WightBossAttackState_

// ===== WispFollowState =====  (1 functions)  ->  namespace WispFollowState_
namespace WispFollowState_ {
  // 0x0060DCE0  conf=0.97  ?ChangePhase@WispFollowState@@UAEXH@Z
  using ChangePhase_t = void (__thiscall*)(::WispFollowState *, int);
  inline void ChangePhase(::WispFollowState * a0, int a1) { reinterpret_cast<ChangePhase_t>(meridian::rebase(0x0060DCE0))(a0, a1); }
} // WispFollowState_

// ===== WispIdleState =====  (1 functions)  ->  namespace WispIdleState_
namespace WispIdleState_ {
  // 0x0060E820  conf=0.97  ?ChangePhase@WispIdleState@@UAEXH@Z
  using ChangePhase_t = void (__thiscall*)(::WispIdleState *, int);
  inline void ChangePhase(::WispIdleState * a0, int a1) { reinterpret_cast<ChangePhase_t>(meridian::rebase(0x0060E820))(a0, a1); }
} // WispIdleState_

// ===== Xbox =====  (1 functions)  ->  namespace Xbox_
namespace Xbox_ {
  // 0x00650210  conf=0.721  ?VBlankCallback@@YAXPAU_D3DVBLANKDATA@@@Z
  using VBlankCallback_t = void (__cdecl*)(::_D3DVBLANKDATA *);
  inline void VBlankCallback(::_D3DVBLANKDATA * a0) { reinterpret_cast<VBlankCallback_t>(meridian::rebase(0x00650210))(a0); }
} // Xbox_

// ===== __value =====  (1 functions)  ->  namespace __value_
namespace __value_ {
  // 0x00424890  conf=0.79  ??0__value@property@@QAE@ABU01@@Z
  using ctor_t = undefined (__thiscall*)(::__value *, ::__value *);
  inline undefined ctor(::__value * a0, ::__value * a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x00424890))(a0, a1); }
} // __value_

// ===== ambient_audio_trigger =====  (7 functions)  ->  namespace ambient_audio_trigger_
namespace ambient_audio_trigger_ {
  // 0x004551C0  conf=0.595  ?CheckForCrossing@ambient_audio_trigger@@QAEXUvector3@@0@Z
  using CheckForCrossing_t = void (__thiscall*)(::ambient_audio_trigger *, ::vector3, ::vector3);
  inline void CheckForCrossing(::ambient_audio_trigger * a0, ::vector3 a1, ::vector3 a2) { reinterpret_cast<CheckForCrossing_t>(meridian::rebase(0x004551C0))(a0, a1, a2); }
  // 0x00454E40  conf=0.85  ?Init@ambient_audio_trigger@@QAEXABUvector3@@ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::ambient_audio_trigger *, ::vector3 *, ::bbox *);
  inline void Init(::ambient_audio_trigger * a0, ::vector3 * a1, ::bbox * a2) { reinterpret_cast<Init_t>(meridian::rebase(0x00454E40))(a0, a1, a2); }
  // 0x0053AFF0  conf=0.85  ?OnExport@ambient_audio_trigger@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::ambient_audio_trigger *, ::bin_out *);
  inline void OnExport(::ambient_audio_trigger * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x0053AFF0))(a0, a1); }
  // 0x0053B1A0  conf=0.85  ?OnImport@ambient_audio_trigger@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::ambient_audio_trigger *, ::bin_in *);
  inline void OnImport(::ambient_audio_trigger * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0053B1A0))(a0, a1); }
  // 0x00455570  conf=0.749  ?OnTriggerGreenToRed@ambient_audio_trigger@@QAEXXZ
  using OnTriggerGreenToRed_t = void (__thiscall*)(::ambient_audio_trigger *);
  inline void OnTriggerGreenToRed(::ambient_audio_trigger * a0) { reinterpret_cast<OnTriggerGreenToRed_t>(meridian::rebase(0x00455570))(a0); }
  // 0x004554A0  conf=0.749  ?OnTriggerRedToGreen@ambient_audio_trigger@@QAEXXZ
  using OnTriggerRedToGreen_t = void (__thiscall*)(::ambient_audio_trigger *);
  inline void OnTriggerRedToGreen(::ambient_audio_trigger * a0) { reinterpret_cast<OnTriggerRedToGreen_t>(meridian::rebase(0x004554A0))(a0); }
  // 0x00455A20  conf=0.97  ?SetProperty@ambient_audio_trigger@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::ambient_audio_trigger *, char *, ::property *);
  inline int SetProperty(::ambient_audio_trigger * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00455A20))(a0, a1, a2); }
} // ambient_audio_trigger_

// ===== anim_group =====  (1 functions)  ->  namespace anim_group_
namespace anim_group_ {
  // 0x0053DBA0  conf=0.655  ?Load@anim_group@@QAEHPAIPBD@Z
  using Load_t = int (__thiscall*)(::anim_group *, uint *, char *);
  inline int Load(::anim_group * a0, uint * a1, char * a2) { return reinterpret_cast<Load_t>(meridian::rebase(0x0053DBA0))(a0, a1, a2); }
} // anim_group_

// ===== anim_loader =====  (1 functions)  ->  namespace anim_loader_
namespace anim_loader_ {
  // 0x0053CAA0  conf=0.676  ?Load@anim_loader@@UAEPAXPAIPBD@Z
  using Load_t = void * (__thiscall*)(::anim_loader *, uint *, char *);
  inline void * Load(::anim_loader * a0, uint * a1, char * a2) { return reinterpret_cast<Load_t>(meridian::rebase(0x0053CAA0))(a0, a1, a2); }
} // anim_loader_

// ===== audio_emitter =====  (5 functions)  ->  namespace audio_emitter_
namespace audio_emitter_ {
  // 0x00459CF0  conf=0.748  ?Enable@audio_emitter@@QAEXH@Z
  using Enable_t = void (__thiscall*)(::audio_emitter *, int);
  inline void Enable(::audio_emitter * a0, int a1) { reinterpret_cast<Enable_t>(meridian::rebase(0x00459CF0))(a0, a1); }
  // 0x00458720  conf=0.85  ?EnumerateProperties@audio_emitter@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::audio_emitter *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::audio_emitter * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00458720))(a0, a1); }
  // 0x00457F60  conf=0.85  ?OnImport@audio_emitter@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::audio_emitter *, ::bin_in *);
  inline void OnImport(::audio_emitter * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00457F60))(a0, a1); }
  // 0x00459D70  conf=0.75  ?OnObjectDeactivate@audio_emitter@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::audio_emitter *);
  inline void OnObjectDeactivate(::audio_emitter * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x00459D70))(a0); }
  // 0x00457120  conf=0.97  ??0audio_emitter@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::audio_emitter *);
  inline undefined ctor(::audio_emitter * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x00457120))(a0); }
} // audio_emitter_

// ===== audio_mgr =====  (1 functions)  ->  namespace audio_mgr_
namespace audio_mgr_ {
  // 0x0065AF40  conf=0.749  ?GetVoiceParameters@audio_mgr@@AAEXPAUuncompressed_parameters@@PAGPAVaudio_package@@@Z
  using GetVoiceParameters_t = void (__thiscall*)(::audio_mgr *, ::uncompressed_parameters *, ushort *, ::audio_package *);
  inline void GetVoiceParameters(::audio_mgr * a0, ::uncompressed_parameters * a1, ushort * a2, ::audio_package * a3) { reinterpret_cast<GetVoiceParameters_t>(meridian::rebase(0x0065AF40))(a0, a1, a2, a3); }
} // audio_mgr_

// ===== audio_package =====  (1 functions)  ->  namespace audio_package_
namespace audio_package_ {
  // 0x0067C640  conf=0.633  ?SetUserVolume@audio_package@@QAEXM@Z
  using SetUserVolume_t = void (__thiscall*)(::audio_package *, float);
  inline void SetUserVolume(::audio_package * a0, float a1) { reinterpret_cast<SetUserVolume_t>(meridian::rebase(0x0067C640))(a0, a1); }
} // audio_package_

// ===== bbox =====  (1 functions)  ->  namespace bbox_
namespace bbox_ {
  // 0x004936F0  conf=0.782  ?Transform@bbox@@QAEXABVmatrix4@@@Z
  using Transform_t = void (__thiscall*)(::bbox *, ::matrix4 *);
  inline void Transform(::bbox * a0, ::matrix4 * a1) { reinterpret_cast<Transform_t>(meridian::rebase(0x004936F0))(a0, a1); }
} // bbox_

// ===== bilbo =====  (242 functions)  ->  namespace bilbo_
namespace bilbo_ {
  // 0x0042FDF0  conf=0.97  ?ActivateHeadTracking@bilbo@@AAEXXZ
  using ActivateHeadTracking_t = void (__thiscall*)(::bilbo *);
  inline void ActivateHeadTracking(::bilbo * a0) { reinterpret_cast<ActivateHeadTracking_t>(meridian::rebase(0x0042FDF0))(a0); }
  // 0x0044D280  conf=0.768  ?ActivateInvenMenu@bilbo@@QAEXXZ
  using ActivateInvenMenu_t = void (__thiscall*)(::bilbo *);
  inline void ActivateInvenMenu(::bilbo * a0) { reinterpret_cast<ActivateInvenMenu_t>(meridian::rebase(0x0044D280))(a0); }
  // 0x0042DA90  conf=0.704  ?AdvanceEdgeCursor@bilbo@@AAEHAAUvector3@@ABU2@@Z
  using AdvanceEdgeCursor_t = int (__thiscall*)(::bilbo *, ::vector3 *, ::vector3 *);
  inline int AdvanceEdgeCursor(::bilbo * a0, ::vector3 * a1, ::vector3 * a2) { return reinterpret_cast<AdvanceEdgeCursor_t>(meridian::rebase(0x0042DA90))(a0, a1, a2); }
  // 0x00425A60  conf=0.97  ?AudioBlocked@bilbo@@AAEXXZ
  using AudioBlocked_t = void (__thiscall*)(::bilbo *);
  inline void AudioBlocked(::bilbo * a0) { reinterpret_cast<AudioBlocked_t>(meridian::rebase(0x00425A60))(a0); }
  // 0x00425B10  conf=0.97  ?AudioBlockedHitByWeapon@bilbo@@AAEXH@Z
  using AudioBlockedHitByWeapon_t = void (__thiscall*)(::bilbo *, int);
  inline void AudioBlockedHitByWeapon(::bilbo * a0, int a1) { reinterpret_cast<AudioBlockedHitByWeapon_t>(meridian::rebase(0x00425B10))(a0, a1); }
  // 0x00425A80  conf=0.97  ?AudioDeath@bilbo@@AAEXXZ
  using AudioDeath_t = void (__thiscall*)(::bilbo *);
  inline void AudioDeath(::bilbo * a0) { reinterpret_cast<AudioDeath_t>(meridian::rebase(0x00425A80))(a0); }
  // 0x00425D30  conf=0.75  ?AudioEndPushBlock@bilbo@@AAEXXZ
  using AudioEndPushBlock_t = void (__thiscall*)(::bilbo *);
  inline void AudioEndPushBlock(::bilbo * a0) { reinterpret_cast<AudioEndPushBlock_t>(meridian::rebase(0x00425D30))(a0); }
  // 0x00425AC0  conf=0.97  ?AudioHitByWeapon@bilbo@@AAEXH@Z
  using AudioHitByWeapon_t = void (__thiscall*)(::bilbo *, int);
  inline void AudioHitByWeapon(::bilbo * a0, int a1) { reinterpret_cast<AudioHitByWeapon_t>(meridian::rebase(0x00425AC0))(a0, a1); }
  // 0x00425C80  conf=0.97  ?AudioJump@bilbo@@AAEXXZ
  using AudioJump_t = void (__thiscall*)(::bilbo *);
  inline void AudioJump(::bilbo * a0) { reinterpret_cast<AudioJump_t>(meridian::rebase(0x00425C80))(a0); }
  // 0x00425A40  conf=0.97  ?AudioKnockback@bilbo@@AAEXXZ
  using AudioKnockback_t = void (__thiscall*)(::bilbo *);
  inline void AudioKnockback(::bilbo * a0) { reinterpret_cast<AudioKnockback_t>(meridian::rebase(0x00425A40))(a0); }
  // 0x00425B70  conf=0.97  ?AudioPolePlant@bilbo@@AAEXXZ
  using AudioPolePlant_t = void (__thiscall*)(::bilbo *);
  inline void AudioPolePlant(::bilbo * a0) { reinterpret_cast<AudioPolePlant_t>(meridian::rebase(0x00425B70))(a0); }
  // 0x00425CA0  conf=0.97  ?AudioStartPushBlock@bilbo@@AAEXXZ
  using AudioStartPushBlock_t = void (__thiscall*)(::bilbo *);
  inline void AudioStartPushBlock(::bilbo * a0) { reinterpret_cast<AudioStartPushBlock_t>(meridian::rebase(0x00425CA0))(a0); }
  // 0x00425D60  conf=0.97  ?AudioStartRing@bilbo@@AAEXXZ
  using AudioStartRing_t = void (__thiscall*)(::bilbo *);
  inline void AudioStartRing(::bilbo * a0) { reinterpret_cast<AudioStartRing_t>(meridian::rebase(0x00425D60))(a0); }
  // 0x00425DD0  conf=0.97  ?AudioStopRing@bilbo@@AAEXH@Z
  using AudioStopRing_t = void (__thiscall*)(::bilbo *, int);
  inline void AudioStopRing(::bilbo * a0, int a1) { reinterpret_cast<AudioStopRing_t>(meridian::rebase(0x00425DD0))(a0, a1); }
  // 0x00425B30  conf=0.97  ?AudioTargetedEnter@bilbo@@AAEXXZ
  using AudioTargetedEnter_t = void (__thiscall*)(::bilbo *);
  inline void AudioTargetedEnter(::bilbo * a0) { reinterpret_cast<AudioTargetedEnter_t>(meridian::rebase(0x00425B30))(a0); }
  // 0x00425B50  conf=0.97  ?AudioTargetedNext@bilbo@@AAEXXZ
  using AudioTargetedNext_t = void (__thiscall*)(::bilbo *);
  inline void AudioTargetedNext(::bilbo * a0) { reinterpret_cast<AudioTargetedNext_t>(meridian::rebase(0x00425B50))(a0); }
  // 0x00448530  conf=0.745  ?AutoDetachPushBlock@bilbo@@QAEXXZ
  using AutoDetachPushBlock_t = void (__thiscall*)(::bilbo *);
  inline void AutoDetachPushBlock(::bilbo * a0) { reinterpret_cast<AutoDetachPushBlock_t>(meridian::rebase(0x00448530))(a0); }
  // 0x00446DE0  conf=0.777  ?Breakaway_CheckForBreakaway@bilbo@@QAEXXZ
  using Breakaway_CheckForBreakaway_t = void (__thiscall*)(::bilbo *);
  inline void Breakaway_CheckForBreakaway(::bilbo * a0) { reinterpret_cast<Breakaway_CheckForBreakaway_t>(meridian::rebase(0x00446DE0))(a0); }
  // 0x00442640  conf=0.794  ?CanDoPullup@bilbo@@AAEHXZ
  using CanDoPullup_t = int (__thiscall*)(::bilbo *);
  inline int CanDoPullup(::bilbo * a0) { return reinterpret_cast<CanDoPullup_t>(meridian::rebase(0x00442640))(a0); }
  // 0x0042FB20  conf=0.791  ?CanGrabEdge@bilbo@@AAEHXZ
  using CanGrabEdge_t = int (__thiscall*)(::bilbo *);
  inline int CanGrabEdge(::bilbo * a0) { return reinterpret_cast<CanGrabEdge_t>(meridian::rebase(0x0042FB20))(a0); }
  // 0x00442A80  conf=0.761  ?CanGrabWall@bilbo@@AAEHABUvector3@@MMMHHAAUplane@@AAU2@@Z
  using CanGrabWall_t = int (__thiscall*)(::bilbo *, ::vector3 *, float, float, float, int, int, ::plane *, ::vector3 *);
  inline int CanGrabWall(::bilbo * a0, ::vector3 * a1, float a2, float a3, float a4, int a5, int a6, ::plane * a7, ::vector3 * a8) { return reinterpret_cast<CanGrabWall_t>(meridian::rebase(0x00442A80))(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
  // 0x00422510  conf=0.727  ?CanJump@bilbo@@AAEHXZ
  using CanJump_t = int (__thiscall*)(::bilbo *);
  inline int CanJump(::bilbo * a0) { return reinterpret_cast<CanJump_t>(meridian::rebase(0x00422510))(a0); }
  // 0x00442790  conf=0.783  ?CanTransitionToWall@bilbo@@AAEHABUvector3@@MAAU2@AAMH@Z
  using CanTransitionToWall_t = int (__thiscall*)(::bilbo *, ::vector3 *, float, ::vector3 *, float *, int);
  inline int CanTransitionToWall(::bilbo * a0, ::vector3 * a1, float a2, ::vector3 * a3, float * a4, int a5) { return reinterpret_cast<CanTransitionToWall_t>(meridian::rebase(0x00442790))(a0, a1, a2, a3, a4, a5); }
  // 0x00422360  conf=0.783  ?ChargePickupLight@bilbo@@QAEXXZ
  using ChargePickupLight_t = void (__thiscall*)(::bilbo *);
  inline void ChargePickupLight(::bilbo * a0) { reinterpret_cast<ChargePickupLight_t>(meridian::rebase(0x00422360))(a0); }
  // 0x0044CF70  conf=0.737  ?CheckForActivate@bilbo@@IAEHAB_K@Z
  using CheckForActivate_t = int (__thiscall*)(::bilbo *, __uint64 *);
  inline int CheckForActivate(::bilbo * a0, __uint64 * a1) { return reinterpret_cast<CheckForActivate_t>(meridian::rebase(0x0044CF70))(a0, a1); }
  // 0x0044CC90  conf=0.749  ?CheckForObject@bilbo@@IAEXUxhandle@@W4type@object@@MMAA_KI@Z
  inline void* CheckForObject_at() { return meridian::rebase(0x0044CC90); } // void __thiscall CheckForObject(bilbo *, xhandle, type, float, float, __uint64 *, uint)
  // 0x0043B690  conf=0.97  ?ChooseFidgetAnim@bilbo@@AAEHXZ
  using ChooseFidgetAnim_t = int (__thiscall*)(::bilbo *);
  inline int ChooseFidgetAnim(::bilbo * a0) { return reinterpret_cast<ChooseFidgetAnim_t>(meridian::rebase(0x0043B690))(a0); }
  // 0x00422B80  conf=0.75  ?Cinema_UseNoWeapon@bilbo@@QAEXXZ
  using Cinema_UseNoWeapon_t = void (__thiscall*)(::bilbo *);
  inline void Cinema_UseNoWeapon(::bilbo * a0) { reinterpret_cast<Cinema_UseNoWeapon_t>(meridian::rebase(0x00422B80))(a0); }
  // 0x00422C40  conf=0.8  ?Cinema_UseStick@bilbo@@QAEXXZ
  using Cinema_UseStick_t = void (__thiscall*)(::bilbo *);
  inline void Cinema_UseStick(::bilbo * a0) { reinterpret_cast<Cinema_UseStick_t>(meridian::rebase(0x00422C40))(a0); }
  // 0x00422BE0  conf=0.75  ?Cinema_UseSting@bilbo@@QAEXXZ
  using Cinema_UseSting_t = void (__thiscall*)(::bilbo *);
  inline void Cinema_UseSting(::bilbo * a0) { reinterpret_cast<Cinema_UseSting_t>(meridian::rebase(0x00422BE0))(a0); }
  // 0x0042C8B0  conf=0.771  ?CollectEdgeInfo@bilbo@@AAEHABUvector3@@MH@Z
  using CollectEdgeInfo_t = int (__thiscall*)(::bilbo *, ::vector3 *, float, int);
  inline int CollectEdgeInfo(::bilbo * a0, ::vector3 * a1, float a2, int a3) { return reinterpret_cast<CollectEdgeInfo_t>(meridian::rebase(0x0042C8B0))(a0, a1, a2, a3); }
  // 0x00426760  conf=0.745  ?Combat_GetYawToTarget@bilbo@@QAEMXZ
  using Combat_GetYawToTarget_t = float (__thiscall*)(::bilbo *);
  inline float Combat_GetYawToTarget(::bilbo * a0) { return reinterpret_cast<Combat_GetYawToTarget_t>(meridian::rebase(0x00426760))(a0); }
  // 0x00425FB0  conf=0.692  ?Combat_ThrowStone@bilbo@@QAEHH@Z
  using Combat_ThrowStone_t = int (__thiscall*)(::bilbo *, int);
  inline int Combat_ThrowStone(::bilbo * a0, int a1) { return reinterpret_cast<Combat_ThrowStone_t>(meridian::rebase(0x00425FB0))(a0, a1); }
  // 0x00426C60  conf=0.8  ?Combat_UpdateTarget@bilbo@@QAEXXZ
  using Combat_UpdateTarget_t = void (__thiscall*)(::bilbo *);
  inline void Combat_UpdateTarget(::bilbo * a0) { reinterpret_cast<Combat_UpdateTarget_t>(meridian::rebase(0x00426C60))(a0); }
  // 0x0042C800  conf=0.798  ?ComputeGrabCenter@bilbo@@AAEXABUvector3@@M@Z
  using ComputeGrabCenter_t = void (__thiscall*)(::bilbo *, ::vector3 *, float);
  inline void ComputeGrabCenter(::bilbo * a0, ::vector3 * a1, float a2) { reinterpret_cast<ComputeGrabCenter_t>(meridian::rebase(0x0042C800))(a0, a1, a2); }
  // 0x0044D940  conf=0.764  ?Conversation_CheckForParticipants@bilbo@@QAEXUxhandle@@@Z
  inline void* Conversation_CheckForParticipants_at() { return meridian::rebase(0x0044D940); } // void __thiscall Conversation_CheckForParticipants(bilbo *, xhandle)
  // 0x0044DD20  conf=0.706  ?Conversation_CheckForStart@bilbo@@QAEHXZ
  using Conversation_CheckForStart_t = int (__thiscall*)(::bilbo *);
  inline int Conversation_CheckForStart(::bilbo * a0) { return reinterpret_cast<Conversation_CheckForStart_t>(meridian::rebase(0x0044DD20))(a0); }
  // 0x0044DC50  conf=0.8  ?Conversation_DrawConversationIndicator@bilbo@@QAEXXZ
  using Conversation_DrawConversationIndicator_t = void (__thiscall*)(::bilbo *);
  inline void Conversation_DrawConversationIndicator(::bilbo * a0) { reinterpret_cast<Conversation_DrawConversationIndicator_t>(meridian::rebase(0x0044DC50))(a0); }
  // 0x00424C30  conf=0.785  ?CreateStoneProjectile@bilbo@@AAEXABUvector3@@0@Z
  using CreateStoneProjectile_t = void (__thiscall*)(::bilbo *, ::vector3 *, ::vector3 *);
  inline void CreateStoneProjectile(::bilbo * a0, ::vector3 * a1, ::vector3 * a2) { reinterpret_cast<CreateStoneProjectile_t>(meridian::rebase(0x00424C30))(a0, a1, a2); }
  // 0x004300C0  conf=0.8  ?DeactivateHeadTracking@bilbo@@AAEXXZ
  using DeactivateHeadTracking_t = void (__thiscall*)(::bilbo *);
  inline void DeactivateHeadTracking(::bilbo * a0) { reinterpret_cast<DeactivateHeadTracking_t>(meridian::rebase(0x004300C0))(a0); }
  // 0x00448560  conf=0.8  ?DetachPushbox@bilbo@@QAEXXZ
  using DetachPushbox_t = void (__thiscall*)(::bilbo *);
  inline void DetachPushbox(::bilbo * a0) { reinterpret_cast<DetachPushbox_t>(meridian::rebase(0x00448560))(a0); }
  // 0x00421F80  conf=0.97  ?DisableStingLight@bilbo@@QAEXXZ
  using DisableStingLight_t = void (__thiscall*)(::bilbo *);
  inline void DisableStingLight(::bilbo * a0) { reinterpret_cast<DisableStingLight_t>(meridian::rebase(0x00421F80))(a0); }
  // 0x0044CE60  conf=0.799  ?DrawIndicator@bilbo@@IAEXAB_KABUvector3@@@Z
  using DrawIndicator_t = void (__thiscall*)(::bilbo *, __uint64 *, ::vector3 *);
  inline void DrawIndicator(::bilbo * a0, __uint64 * a1, ::vector3 * a2) { reinterpret_cast<DrawIndicator_t>(meridian::rebase(0x0044CE60))(a0, a1, a2); }
  // 0x0054FC60  conf=0.708  ?EnableStingLight@bilbo@@QAEXXZ
  using EnableStingLight_t = void (__thiscall*)(::bilbo *);
  inline void EnableStingLight(::bilbo * a0) { reinterpret_cast<EnableStingLight_t>(meridian::rebase(0x0054FC60))(a0); }
  // 0x004229E0  conf=0.618  ?EndConversationMode@bilbo@@UAEXH@Z
  using EndConversationMode_t = void (__thiscall*)(::bilbo *, int);
  inline void EndConversationMode(::bilbo * a0, int a1) { reinterpret_cast<EndConversationMode_t>(meridian::rebase(0x004229E0))(a0, a1); }
  // 0x00422940  conf=0.75  ?EndTalking@bilbo@@UAEXXZ
  using EndTalking_t = void (__thiscall*)(::bilbo *);
  inline void EndTalking(::bilbo * a0) { reinterpret_cast<EndTalking_t>(meridian::rebase(0x00422940))(a0); }
  // 0x0041FBD0  conf=0.745  ?Enemy_CheckForNearest@bilbo@@IAEXUxhandle@@@Z
  inline void* Enemy_CheckForNearest_at() { return meridian::rebase(0x0041FBD0); } // void __thiscall Enemy_CheckForNearest(bilbo *, xhandle)
  // 0x00423EC0  conf=0.85  ?EnumerateProperties@bilbo@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::bilbo *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::bilbo * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00423EC0))(a0, a1); }
  // 0x0042D800  conf=0.796  ?FindClosestEdgePoint@bilbo@@AAEHABUvector3@@@Z
  using FindClosestEdgePoint_t = int (__thiscall*)(::bilbo *, ::vector3 *);
  inline int FindClosestEdgePoint(::bilbo * a0, ::vector3 * a1) { return reinterpret_cast<FindClosestEdgePoint_t>(meridian::rebase(0x0042D800))(a0, a1); }
  // 0x004267A0  conf=0.612  ?FindTargets@bilbo@@QAEXXZ
  using FindTargets_t = void (__thiscall*)(::bilbo *);
  inline void FindTargets(::bilbo * a0) { reinterpret_cast<FindTargets_t>(meridian::rebase(0x004267A0))(a0); }
  // 0x004336E0  conf=0.7  ?FlushBilboInput@bilbo@@QAEXXZ
  using FlushBilboInput_t = void (__thiscall*)(::bilbo *);
  inline void FlushBilboInput(::bilbo * a0) { reinterpret_cast<FlushBilboInput_t>(meridian::rebase(0x004336E0))(a0); }
  // 0x00427320  conf=0.8  ?GetAEJumpLevel@bilbo@@QAEMXZ
  using GetAEJumpLevel_t = float (__thiscall*)(::bilbo *);
  inline float GetAEJumpLevel(::bilbo * a0) { return reinterpret_cast<GetAEJumpLevel_t>(meridian::rebase(0x00427320))(a0); }
  // 0x00422FB0  conf=0.8  ?GetFacing@bilbo@@UAEMXZ
  using GetFacing_t = float (__thiscall*)(::bilbo *);
  inline float GetFacing(::bilbo * a0) { return reinterpret_cast<GetFacing_t>(meridian::rebase(0x00422FB0))(a0); }
  // 0x00422420  conf=0.75  ?GetHealth@bilbo@@QAEMXZ
  using GetHealth_t = float (__thiscall*)(::bilbo *);
  inline float GetHealth(::bilbo * a0) { return reinterpret_cast<GetHealth_t>(meridian::rebase(0x00422420))(a0); }
  // 0x004272D0  conf=0.8  ?GetJumpLevel@bilbo@@QAEMXZ
  using GetJumpLevel_t = float (__thiscall*)(::bilbo *);
  inline float GetJumpLevel(::bilbo * a0) { return reinterpret_cast<GetJumpLevel_t>(meridian::rebase(0x004272D0))(a0); }
  // 0x00422460  conf=0.75  ?GetNGold@bilbo@@QAEHXZ
  using GetNGold_t = int (__thiscall*)(::bilbo *);
  inline int GetNGold(::bilbo * a0) { return reinterpret_cast<GetNGold_t>(meridian::rebase(0x00422460))(a0); }
  // 0x00422440  conf=0.75  ?GetPoisonDamage@bilbo@@QAEMXZ
  using GetPoisonDamage_t = float (__thiscall*)(::bilbo *);
  inline float GetPoisonDamage(::bilbo * a0) { return reinterpret_cast<GetPoisonDamage_t>(meridian::rebase(0x00422440))(a0); }
  // 0x00422430  conf=0.75  ?GetPoisonTime@bilbo@@QAEMXZ
  using GetPoisonTime_t = float (__thiscall*)(::bilbo *);
  inline float GetPoisonTime(::bilbo * a0) { return reinterpret_cast<GetPoisonTime_t>(meridian::rebase(0x00422430))(a0); }
  // 0x00449810  conf=0.789  ?GetPositionFromPushBox@bilbo@@IAEXAAUvector3@@M@Z
  using GetPositionFromPushBox_t = void (__thiscall*)(::bilbo *, ::vector3 *, float);
  inline void GetPositionFromPushBox(::bilbo * a0, ::vector3 * a1, float a2) { reinterpret_cast<GetPositionFromPushBox_t>(meridian::rebase(0x00449810))(a0, a1, a2); }
  // 0x004272A0  conf=0.8  ?GetSwingLevel@bilbo@@QAEMXZ
  using GetSwingLevel_t = float (__thiscall*)(::bilbo *);
  inline float GetSwingLevel(::bilbo * a0) { return reinterpret_cast<GetSwingLevel_t>(meridian::rebase(0x004272A0))(a0); }
  // 0x004228E0  conf=0.8  ?GetVigorHealth@bilbo@@QAEMXZ
  using GetVigorHealth_t = float (__thiscall*)(::bilbo *);
  inline float GetVigorHealth(::bilbo * a0) { return reinterpret_cast<GetVigorHealth_t>(meridian::rebase(0x004228E0))(a0); }
  // 0x0041C960  conf=0.831  ?GrabGlobals@bilbo@@QAEXXZ
  using GrabGlobals_t = void (__thiscall*)(::bilbo *);
  inline void GrabGlobals(::bilbo * a0) { reinterpret_cast<GrabGlobals_t>(meridian::rebase(0x0041C960))(a0); }
  // 0x0044D7F0  conf=0.796  ?Hoistables_DrawIndicator@bilbo@@QAEXXZ
  using Hoistables_DrawIndicator_t = void (__thiscall*)(::bilbo *);
  inline void Hoistables_DrawIndicator(::bilbo * a0) { reinterpret_cast<Hoistables_DrawIndicator_t>(meridian::rebase(0x0044D7F0))(a0); }
  // 0x0041CBD0  conf=0.97  ?Init@bilbo@@QAEXXZ
  using Init_t = void (__thiscall*)(::bilbo *);
  inline void Init(::bilbo * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x0041CBD0))(a0); }
  // 0x0041BCE0  conf=0.788  ?InitTweaks@bilbo@@QAEXXZ
  using InitTweaks_t = void (__thiscall*)(::bilbo *);
  inline void InitTweaks(::bilbo * a0) { reinterpret_cast<InitTweaks_t>(meridian::rebase(0x0041BCE0))(a0); }
  // 0x0044C120  conf=0.765  ?InputFeedback@bilbo@@QAEXW4FeedbackType@@M@Z
  inline void* InputFeedback_at() { return meridian::rebase(0x0044C120); } // void __thiscall InputFeedback(bilbo *, FeedbackType, float)
  // 0x00422450  conf=0.8  ?IsPoisoned@bilbo@@QAEHXZ
  using IsPoisoned_t = int (__thiscall*)(::bilbo *);
  inline int IsPoisoned(::bilbo * a0) { return reinterpret_cast<IsPoisoned_t>(meridian::rebase(0x00422450))(a0); }
  // 0x00424CE0  conf=0.75  ?IsRingEquipped@bilbo@@QAEHXZ
  using IsRingEquipped_t = int (__thiscall*)(::bilbo *);
  inline int IsRingEquipped(::bilbo * a0) { return reinterpret_cast<IsRingEquipped_t>(meridian::rebase(0x00424CE0))(a0); }
  // 0x00426A90  conf=0.738  ?IsValidTarget@bilbo@@QAEHPAVNPCObject@@@Z
  using IsValidTarget_t = int (__thiscall*)(::bilbo *, ::NPCObject *);
  inline int IsValidTarget(::bilbo * a0, ::NPCObject * a1) { return reinterpret_cast<IsValidTarget_t>(meridian::rebase(0x00426A90))(a0, a1); }
  // 0x00422590  conf=0.799  ?Jump@bilbo@@AAEXXZ
  using Jump_t = void (__thiscall*)(::bilbo *);
  inline void Jump(::bilbo * a0) { reinterpret_cast<Jump_t>(meridian::rebase(0x00422590))(a0); }
  // 0x004383B0  conf=0.71  ?Ladder_CanGrab@bilbo@@AAEHXZ
  using Ladder_CanGrab_t = int (__thiscall*)(::bilbo *);
  inline int Ladder_CanGrab(::bilbo * a0) { return reinterpret_cast<Ladder_CanGrab_t>(meridian::rebase(0x004383B0))(a0); }
  // 0x0044C360  conf=0.759  ?LimitVelocities@bilbo@@AAEXXZ
  using LimitVelocities_t = void (__thiscall*)(::bilbo *);
  inline void LimitVelocities(::bilbo * a0) { reinterpret_cast<LimitVelocities_t>(meridian::rebase(0x0044C360))(a0); }
  // 0x0052E990  conf=0.792  ?ModifyHealth@bilbo@@UAEXH@Z
  using ModifyHealth_t = void (__thiscall*)(::bilbo *, int);
  inline void ModifyHealth(::bilbo * a0, int a1) { reinterpret_cast<ModifyHealth_t>(meridian::rebase(0x0052E990))(a0, a1); }
  // 0x00448C70  conf=0.828  ?MoveBilboToPushBox@bilbo@@IAEXH@Z
  using MoveBilboToPushBox_t = void (__thiscall*)(::bilbo *, int);
  inline void MoveBilboToPushBox(::bilbo * a0, int a1) { reinterpret_cast<MoveBilboToPushBox_t>(meridian::rebase(0x00448C70))(a0, a1); }
  // 0x00442F50  conf=0.786  ?Nav_Advance@bilbo@@AAEXXZ
  using Nav_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_Advance(::bilbo * a0) { reinterpret_cast<Nav_Advance_t>(meridian::rebase(0x00442F50))(a0); }
  // 0x00442550  conf=0.683  ?Nav_ChangeTo@bilbo@@AAEXW4nav_state@1@@Z
  inline void* Nav_ChangeTo_at() { return meridian::rebase(0x00442550); } // void __thiscall Nav_ChangeTo(bilbo *, nav_state)
  // 0x00445430  conf=0.748  ?Nav_Cinematic_Advance@bilbo@@AAEXXZ
  using Nav_Cinematic_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_Cinematic_Advance(::bilbo * a0) { reinterpret_cast<Nav_Cinematic_Advance_t>(meridian::rebase(0x00445430))(a0); }
  // 0x004449C0  conf=0.79  ?Nav_EdgeGrab_Advance@bilbo@@AAEXXZ
  using Nav_EdgeGrab_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_EdgeGrab_Advance(::bilbo * a0) { reinterpret_cast<Nav_EdgeGrab_Advance_t>(meridian::rebase(0x004449C0))(a0); }
  // 0x00444C70  conf=0.764  ?Nav_EdgeMount_Advance@bilbo@@AAEXXZ
  using Nav_EdgeMount_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_EdgeMount_Advance(::bilbo * a0) { reinterpret_cast<Nav_EdgeMount_Advance_t>(meridian::rebase(0x00444C70))(a0); }
  // 0x004430F0  conf=0.849  ?Nav_GroundHug_Advance@bilbo@@AAEXXZ
  using Nav_GroundHug_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_GroundHug_Advance(::bilbo * a0) { reinterpret_cast<Nav_GroundHug_Advance_t>(meridian::rebase(0x004430F0))(a0); }
  // 0x00445DD0  conf=0.7  ?Nav_Jump_Advance@bilbo@@AAEXXZ
  using Nav_Jump_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_Jump_Advance(::bilbo * a0) { reinterpret_cast<Nav_Jump_Advance_t>(meridian::rebase(0x00445DD0))(a0); }
  // 0x004441D0  conf=0.604  ?Nav_LadderMount_Advance@bilbo@@AAEXXZ
  using Nav_LadderMount_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_LadderMount_Advance(::bilbo * a0) { reinterpret_cast<Nav_LadderMount_Advance_t>(meridian::rebase(0x004441D0))(a0); }
  // 0x00443A70  conf=0.774  ?Nav_Launching_Advance@bilbo@@AAEXXZ
  using Nav_Launching_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_Launching_Advance(::bilbo * a0) { reinterpret_cast<Nav_Launching_Advance_t>(meridian::rebase(0x00443A70))(a0); }
  // 0x0044A940  conf=0.798  ?Nav_RopeClimb_Advance@bilbo@@AAEXXZ
  using Nav_RopeClimb_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_RopeClimb_Advance(::bilbo * a0) { reinterpret_cast<Nav_RopeClimb_Advance_t>(meridian::rebase(0x0044A940))(a0); }
  // 0x00442560  conf=0.8  ?Nav_SetSkid@bilbo@@AAEXABUvector3@@M@Z
  using Nav_SetSkid_t = void (__thiscall*)(::bilbo *, ::vector3 *, float);
  inline void Nav_SetSkid(::bilbo * a0, ::vector3 * a1, float a2) { reinterpret_cast<Nav_SetSkid_t>(meridian::rebase(0x00442560))(a0, a1, a2); }
  // 0x00443D30  conf=0.598  ?Nav_Sliding_Advance@bilbo@@AAEXXZ
  using Nav_Sliding_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_Sliding_Advance(::bilbo * a0) { reinterpret_cast<Nav_Sliding_Advance_t>(meridian::rebase(0x00443D30))(a0); }
  // 0x00444730  conf=0.97  ?Nav_WallHug_Advance@bilbo@@AAEXXZ
  using Nav_WallHug_Advance_t = void (__thiscall*)(::bilbo *);
  inline void Nav_WallHug_Advance(::bilbo * a0) { reinterpret_cast<Nav_WallHug_Advance_t>(meridian::rebase(0x00444730))(a0); }
  // 0x00425E90  conf=0.754  ?NotifyNPCOfAttack@bilbo@@QAEXH@Z
  using NotifyNPCOfAttack_t = void (__thiscall*)(::bilbo *, int);
  inline void NotifyNPCOfAttack(::bilbo * a0, int a1) { reinterpret_cast<NotifyNPCOfAttack_t>(meridian::rebase(0x00425E90))(a0, a1); }
  // 0x0041E360  conf=0.97  ?OnAdvanceLogic@bilbo@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::bilbo *, float);
  inline void OnAdvanceLogic(::bilbo * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x0041E360))(a0, a1); }
  // 0x00421120  conf=0.97  ?OnApplyPain@bilbo@@UAEH_KABUvector3@@MMMMW4ePainType@PainData@@H@Z
  inline void* OnApplyPain_at() { return meridian::rebase(0x00421120); } // int __thiscall OnApplyPain(bilbo *, __uint64, vector3 *, float, float, float, float, ePainType, int)
  // 0x00424BD0  conf=0.75  ?OnObjectDeactivate@bilbo@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::bilbo *);
  inline void OnObjectDeactivate(::bilbo * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x00424BD0))(a0); }
  // 0x00424F20  conf=0.769  ?OnTeleport@bilbo@@QAEXXZ
  using OnTeleport_t = void (__thiscall*)(::bilbo *);
  inline void OnTeleport(::bilbo * a0) { reinterpret_cast<OnTeleport_t>(meridian::rebase(0x00424F20))(a0); }
  // 0x00446010  conf=0.789  ?Pickups_CheckForPickups@bilbo@@QAEXXZ
  using Pickups_CheckForPickups_t = void (__thiscall*)(::bilbo *);
  inline void Pickups_CheckForPickups(::bilbo * a0) { reinterpret_cast<Pickups_CheckForPickups_t>(meridian::rebase(0x00446010))(a0); }
  // 0x00446330  conf=0.97  ?Pickups_GetPickup@bilbo@@QAEXPAVobject@@@Z
  using Pickups_GetPickup_t = void (__thiscall*)(::bilbo *, ::object *);
  inline void Pickups_GetPickup(::bilbo * a0, ::object * a1) { reinterpret_cast<Pickups_GetPickup_t>(meridian::rebase(0x00446330))(a0, a1); }
  // 0x00446180  conf=0.798  ?Pickups_ShouldPickUp@bilbo@@QAEHPAVobject@@@Z
  using Pickups_ShouldPickUp_t = int (__thiscall*)(::bilbo *, ::object *);
  inline int Pickups_ShouldPickUp(::bilbo * a0, ::object * a1) { return reinterpret_cast<Pickups_ShouldPickUp_t>(meridian::rebase(0x00446180))(a0, a1); }
  // 0x00423AA0  conf=0.758  ?Plants_CheckForPlants@bilbo@@QAEXUxhandle@@@Z
  inline void* Plants_CheckForPlants_at() { return meridian::rebase(0x00423AA0); } // void __thiscall Plants_CheckForPlants(bilbo *, xhandle)
  // 0x00447160  conf=0.77  ?Platform_CatchUpWithPlatform@bilbo@@QAEXXZ
  using Platform_CatchUpWithPlatform_t = void (__thiscall*)(::bilbo *);
  inline void Platform_CatchUpWithPlatform(::bilbo * a0) { reinterpret_cast<Platform_CatchUpWithPlatform_t>(meridian::rebase(0x00447160))(a0); }
  // 0x00447C60  conf=0.768  ?Platform_CollideWithPlatforms@bilbo@@QAEXUxhandle@@@Z
  inline void* Platform_CollideWithPlatforms_at() { return meridian::rebase(0x00447C60); } // void __thiscall Platform_CollideWithPlatforms(bilbo *, xhandle)
  // 0x00446EB0  conf=0.712  ?Platform_DetachFromPlatform@bilbo@@QAEXXZ
  using Platform_DetachFromPlatform_t = void (__thiscall*)(::bilbo *);
  inline void Platform_DetachFromPlatform(::bilbo * a0) { reinterpret_cast<Platform_DetachFromPlatform_t>(meridian::rebase(0x00446EB0))(a0); }
  // 0x00447610  conf=0.765  ?Platform_JumpFollowPlatform@bilbo@@QAEXXZ
  using Platform_JumpFollowPlatform_t = void (__thiscall*)(::bilbo *);
  inline void Platform_JumpFollowPlatform(::bilbo * a0) { reinterpret_cast<Platform_JumpFollowPlatform_t>(meridian::rebase(0x00447610))(a0); }
  // 0x0041AFB0  conf=0.97  ?PostRender@bilbo@@QAEXXZ
  using PostRender_t = void (__thiscall*)(::bilbo *);
  inline void PostRender(::bilbo * a0) { reinterpret_cast<PostRender_t>(meridian::rebase(0x0041AFB0))(a0); }
  // 0x00420560  conf=0.97  ?ProcessEvents@bilbo@@AAEXXZ
  using ProcessEvents_t = void (__thiscall*)(::bilbo *);
  inline void ProcessEvents(::bilbo * a0) { reinterpret_cast<ProcessEvents_t>(meridian::rebase(0x00420560))(a0); }
  // 0x00448920  conf=0.753  ?PushBox_CheckForActivatePushBox@bilbo@@QAEHXZ
  using PushBox_CheckForActivatePushBox_t = int (__thiscall*)(::bilbo *);
  inline int PushBox_CheckForActivatePushBox(::bilbo * a0) { return reinterpret_cast<PushBox_CheckForActivatePushBox_t>(meridian::rebase(0x00448920))(a0); }
  // 0x00448B10  conf=0.776  ?PushBox_DrawPushBoxIndicator@bilbo@@QAEXXZ
  using PushBox_DrawPushBoxIndicator_t = void (__thiscall*)(::bilbo *);
  inline void PushBox_DrawPushBoxIndicator(::bilbo * a0) { reinterpret_cast<PushBox_DrawPushBoxIndicator_t>(meridian::rebase(0x00448B10))(a0); }
  // 0x00424CF0  conf=0.746  ?Reset@bilbo@@QAEXXZ
  using Reset_t = void (__thiscall*)(::bilbo *);
  inline void Reset(::bilbo * a0) { reinterpret_cast<Reset_t>(meridian::rebase(0x00424CF0))(a0); }
  // 0x00427270  conf=0.722  ?ResetPoison@bilbo@@QAEXXZ
  using ResetPoison_t = void (__thiscall*)(::bilbo *);
  inline void ResetPoison(::bilbo * a0) { reinterpret_cast<ResetPoison_t>(meridian::rebase(0x00427270))(a0); }
  // 0x0044C810  conf=0.717  ?ResetSafePos@bilbo@@QAEXXZ
  using ResetSafePos_t = void (__thiscall*)(::bilbo *);
  inline void ResetSafePos(::bilbo * a0) { reinterpret_cast<ResetSafePos_t>(meridian::rebase(0x0044C810))(a0); }
  // 0x0044CA80  conf=0.796  ?ResetToSafePos@bilbo@@QAEXXZ
  using ResetToSafePos_t = void (__thiscall*)(::bilbo *);
  inline void ResetToSafePos(::bilbo * a0) { reinterpret_cast<ResetToSafePos_t>(meridian::rebase(0x0044CA80))(a0); }
  // 0x004F5080  conf=0.715  ?RingExpired@bilbo@@QAEXXZ
  using RingExpired_t = void (__thiscall*)(::bilbo *);
  inline void RingExpired(::bilbo * a0) { reinterpret_cast<RingExpired_t>(meridian::rebase(0x004F5080))(a0); }
  // 0x00449E80  conf=0.746  ?Rope_CanGrab@bilbo@@AAEHXZ
  using Rope_CanGrab_t = int (__thiscall*)(::bilbo *);
  inline int Rope_CanGrab(::bilbo * a0) { return reinterpret_cast<Rope_CanGrab_t>(meridian::rebase(0x00449E80))(a0); }
  // 0x0044AD00  conf=0.792  ?Rope_CanReachAnotherRope@bilbo@@AAEHAAM@Z
  using Rope_CanReachAnotherRope_t = int (__thiscall*)(::bilbo *, float *);
  inline int Rope_CanReachAnotherRope(::bilbo * a0, float * a1) { return reinterpret_cast<Rope_CanReachAnotherRope_t>(meridian::rebase(0x0044AD00))(a0, a1); }
  // 0x00449D90  conf=0.787  ?Rope_CollectSegs@bilbo@@AAEXXZ
  using Rope_CollectSegs_t = void (__thiscall*)(::bilbo *);
  inline void Rope_CollectSegs(::bilbo * a0) { reinterpret_cast<Rope_CollectSegs_t>(meridian::rebase(0x00449D90))(a0); }
  // 0x0044A0B0  conf=0.772  ?Rope_ComputeGrab@bilbo@@AAEXAAUvector3@@AAM@Z
  using Rope_ComputeGrab_t = void (__thiscall*)(::bilbo *, ::vector3 *, float *);
  inline void Rope_ComputeGrab(::bilbo * a0, ::vector3 * a1, float * a2) { reinterpret_cast<Rope_ComputeGrab_t>(meridian::rebase(0x0044A0B0))(a0, a1, a2); }
  // 0x0044A3A0  conf=0.788  ?Rope_ComputeInitialGrab@bilbo@@AAEXAAUvector3@@AAM@Z
  using Rope_ComputeInitialGrab_t = void (__thiscall*)(::bilbo *, ::vector3 *, float *);
  inline void Rope_ComputeInitialGrab(::bilbo * a0, ::vector3 * a1, float * a2) { reinterpret_cast<Rope_ComputeInitialGrab_t>(meridian::rebase(0x0044A3A0))(a0, a1, a2); }
  // 0x0044ABA0  conf=0.793  ?Rope_PushWholeRope@bilbo@@AAEXHABUvector3@@@Z
  using Rope_PushWholeRope_t = void (__thiscall*)(::bilbo *, int, ::vector3 *);
  inline void Rope_PushWholeRope(::bilbo * a0, int a1, ::vector3 * a2) { reinterpret_cast<Rope_PushWholeRope_t>(meridian::rebase(0x0044ABA0))(a0, a1, a2); }
  // 0x00449B80  conf=0.774  ?Rope_ScanForRopes@bilbo@@AAEXUxhandle@@@Z
  inline void* Rope_ScanForRopes_at() { return meridian::rebase(0x00449B80); } // void __thiscall Rope_ScanForRopes(bilbo *, xhandle)
  // 0x0043B5F0  conf=0.553  ?RunFidgets@bilbo@@AAEXXZ
  using RunFidgets_t = void (__thiscall*)(::bilbo *);
  inline void RunFidgets(::bilbo * a0) { reinterpret_cast<RunFidgets_t>(meridian::rebase(0x0043B5F0))(a0); }
  // 0x004300E0  conf=0.798  ?RunHeadTracking@bilbo@@AAEXXZ
  using RunHeadTracking_t = void (__thiscall*)(::bilbo *);
  inline void RunHeadTracking(::bilbo * a0) { reinterpret_cast<RunHeadTracking_t>(meridian::rebase(0x004300E0))(a0); }
  // 0x0044D620  conf=0.742  ?Save_DrawSaveIndicator@bilbo@@QAEXXZ
  using Save_DrawSaveIndicator_t = void (__thiscall*)(::bilbo *);
  inline void Save_DrawSaveIndicator(::bilbo * a0) { reinterpret_cast<Save_DrawSaveIndicator_t>(meridian::rebase(0x0044D620))(a0); }
  // 0x00442400  conf=0.75  ?SetDamageWiggle@bilbo@@QAEXMM@Z
  using SetDamageWiggle_t = void (__thiscall*)(::bilbo *, float, float);
  inline void SetDamageWiggle(::bilbo * a0, float a1, float a2) { reinterpret_cast<SetDamageWiggle_t>(meridian::rebase(0x00442400))(a0, a1, a2); }
  // 0x0041C2B0  conf=0.723  ?SetInput@bilbo@@QAEXH@Z
  using SetInput_t = void (__thiscall*)(::bilbo *, int);
  inline void SetInput(::bilbo * a0, int a1) { reinterpret_cast<SetInput_t>(meridian::rebase(0x0041C2B0))(a0, a1); }
  // 0x00424080  conf=0.9  ?SetProperty@bilbo@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::bilbo *, char *, ::property *);
  inline int SetProperty(::bilbo * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00424080))(a0, a1, a2); }
  // 0x00423C90  conf=0.744  ?SetRingEquipped@bilbo@@QAEXHH@Z
  using SetRingEquipped_t = void (__thiscall*)(::bilbo *, int, int);
  inline void SetRingEquipped(::bilbo * a0, int a1, int a2) { reinterpret_cast<SetRingEquipped_t>(meridian::rebase(0x00423C90))(a0, a1, a2); }
  // 0x004249C0  conf=0.747  ?StartMineCartRide@bilbo@@QAEXH@Z
  using StartMineCartRide_t = void (__thiscall*)(::bilbo *, int);
  inline void StartMineCartRide(::bilbo * a0, int a1) { reinterpret_cast<StartMineCartRide_t>(meridian::rebase(0x004249C0))(a0, a1); }
  // 0x00422900  conf=0.75  ?StartTalking@bilbo@@UAEXH@Z
  using StartTalking_t = void (__thiscall*)(::bilbo *, int);
  inline void StartTalking(::bilbo * a0, int a1) { reinterpret_cast<StartTalking_t>(meridian::rebase(0x00422900))(a0, a1); }
  // 0x00439A60  conf=0.762  ?State_Advance@bilbo@@AAEXXZ
  using State_Advance_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance(::bilbo * a0) { reinterpret_cast<State_Advance_t>(meridian::rebase(0x00439A60))(a0); }
  // 0x0042A250  conf=0.731  ?State_Advance_BACKWARD_BLOCK@bilbo@@AAEXXZ
  using State_Advance_BACKWARD_BLOCK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_BACKWARD_BLOCK(::bilbo * a0) { reinterpret_cast<State_Advance_BACKWARD_BLOCK_t>(meridian::rebase(0x0042A250))(a0); }
  // 0x0044E030  conf=0.728  ?State_Advance_BLOCKED@bilbo@@AAEXXZ
  using State_Advance_BLOCKED_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_BLOCKED(::bilbo * a0) { reinterpret_cast<State_Advance_BLOCKED_t>(meridian::rebase(0x0044E030))(a0); }
  // 0x004274B0  conf=0.97  ?State_Advance_CHAIN_ATTACK@bilbo@@AAEXXZ
  using State_Advance_CHAIN_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_CHAIN_ATTACK(::bilbo * a0) { reinterpret_cast<State_Advance_CHAIN_ATTACK_t>(meridian::rebase(0x004274B0))(a0); }
  // 0x00442320  conf=0.582  ?State_Advance_CINEMATIC@bilbo@@AAEXXZ
  using State_Advance_CINEMATIC_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_CINEMATIC(::bilbo * a0) { reinterpret_cast<State_Advance_CINEMATIC_t>(meridian::rebase(0x00442320))(a0); }
  // 0x00438990  conf=0.97  ?State_Advance_CLIMB_LADDER@bilbo@@AAEXXZ
  using State_Advance_CLIMB_LADDER_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_CLIMB_LADDER(::bilbo * a0) { reinterpret_cast<State_Advance_CLIMB_LADDER_t>(meridian::rebase(0x00438990))(a0); }
  // 0x0043F290  conf=0.97  ?State_Advance_CLIMB_WALL@bilbo@@AAEXXZ
  using State_Advance_CLIMB_WALL_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_CLIMB_WALL(::bilbo * a0) { reinterpret_cast<State_Advance_CLIMB_WALL_t>(meridian::rebase(0x0043F290))(a0); }
  // 0x0043F070  conf=0.793  ?State_Advance_CROUCH_SLIDE@bilbo@@AAEXXZ
  using State_Advance_CROUCH_SLIDE_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_CROUCH_SLIDE(::bilbo * a0) { reinterpret_cast<State_Advance_CROUCH_SLIDE_t>(meridian::rebase(0x0043F070))(a0); }
  // 0x00440EC0  conf=0.742  ?State_Advance_DEATH@bilbo@@AAEXXZ
  using State_Advance_DEATH_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_DEATH(::bilbo * a0) { reinterpret_cast<State_Advance_DEATH_t>(meridian::rebase(0x00440EC0))(a0); }
  // 0x00441200  conf=0.639  ?State_Advance_DEATH_WATER@bilbo@@AAEXXZ
  using State_Advance_DEATH_WATER_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_DEATH_WATER(::bilbo * a0) { reinterpret_cast<State_Advance_DEATH_WATER_t>(meridian::rebase(0x00441200))(a0); }
  // 0x0042EFC0  conf=0.799  ?State_Advance_EDGE_DROP_OFF@bilbo@@AAEXXZ
  using State_Advance_EDGE_DROP_OFF_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_EDGE_DROP_OFF(::bilbo * a0) { reinterpret_cast<State_Advance_EDGE_DROP_OFF_t>(meridian::rebase(0x0042EFC0))(a0); }
  // 0x0042E260  conf=0.97  ?State_Advance_EDGE_GRAB@bilbo@@AAEXXZ
  using State_Advance_EDGE_GRAB_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_EDGE_GRAB(::bilbo * a0) { reinterpret_cast<State_Advance_EDGE_GRAB_t>(meridian::rebase(0x0042E260))(a0); }
  // 0x0042DE50  conf=0.97  ?State_Advance_EDGE_MOUNT@bilbo@@AAEXXZ
  using State_Advance_EDGE_MOUNT_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_EDGE_MOUNT(::bilbo * a0) { reinterpret_cast<State_Advance_EDGE_MOUNT_t>(meridian::rebase(0x0042DE50))(a0); }
  // 0x0043FA00  conf=0.743  ?State_Advance_EDGE_PULLUP@bilbo@@AAEXXZ
  using State_Advance_EDGE_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_EDGE_PULLUP(::bilbo * a0) { reinterpret_cast<State_Advance_EDGE_PULLUP_t>(meridian::rebase(0x0043FA00))(a0); }
  // 0x0043E250  conf=0.9  ?State_Advance_FALL@bilbo@@AAEXXZ
  using State_Advance_FALL_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_FALL(::bilbo * a0) { reinterpret_cast<State_Advance_FALL_t>(meridian::rebase(0x0043E250))(a0); }
  // 0x0043B180  conf=0.97  ?State_Advance_FIDGET@bilbo@@AAEXXZ
  using State_Advance_FIDGET_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_FIDGET(::bilbo * a0) { reinterpret_cast<State_Advance_FIDGET_t>(meridian::rebase(0x0043B180))(a0); }
  // 0x004405F0  conf=0.765  ?State_Advance_FIRST_PERSON_LOOK@bilbo@@AAEXXZ
  using State_Advance_FIRST_PERSON_LOOK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_FIRST_PERSON_LOOK(::bilbo * a0) { reinterpret_cast<State_Advance_FIRST_PERSON_LOOK_t>(meridian::rebase(0x004405F0))(a0); }
  // 0x0043EEC0  conf=0.707  ?State_Advance_FLY@bilbo@@AAEXXZ
  using State_Advance_FLY_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_FLY(::bilbo * a0) { reinterpret_cast<State_Advance_FLY_t>(meridian::rebase(0x0043EEC0))(a0); }
  // 0x00429D00  conf=0.744  ?State_Advance_FORWARD_INAIR_ATTACK@bilbo@@AAEXXZ
  using State_Advance_FORWARD_INAIR_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_FORWARD_INAIR_ATTACK(::bilbo * a0) { reinterpret_cast<State_Advance_FORWARD_INAIR_ATTACK_t>(meridian::rebase(0x00429D00))(a0); }
  // 0x004318D0  conf=0.97  ?State_Advance_HOISTING@bilbo@@AAEXXZ
  using State_Advance_HOISTING_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_HOISTING(::bilbo * a0) { reinterpret_cast<State_Advance_HOISTING_t>(meridian::rebase(0x004318D0))(a0); }
  // 0x0043A7E0  conf=0.97  ?State_Advance_IDLE@bilbo@@AAEXXZ
  using State_Advance_IDLE_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_IDLE(::bilbo * a0) { reinterpret_cast<State_Advance_IDLE_t>(meridian::rebase(0x0043A7E0))(a0); }
  // 0x0043D6B0  conf=0.97  ?State_Advance_JUMP@bilbo@@AAEXXZ
  using State_Advance_JUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_JUMP(::bilbo * a0) { reinterpret_cast<State_Advance_JUMP_t>(meridian::rebase(0x0043D6B0))(a0); }
  // 0x0042A520  conf=0.731  ?State_Advance_KNOCKBACK@bilbo@@AAEXXZ
  using State_Advance_KNOCKBACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_KNOCKBACK(::bilbo * a0) { reinterpret_cast<State_Advance_KNOCKBACK_t>(meridian::rebase(0x0042A520))(a0); }
  // 0x004395B0  conf=0.74  ?State_Advance_LADDER_PULLUP@bilbo@@AAEXXZ
  using State_Advance_LADDER_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_LADDER_PULLUP(::bilbo * a0) { reinterpret_cast<State_Advance_LADDER_PULLUP_t>(meridian::rebase(0x004395B0))(a0); }
  // 0x00429AE0  conf=0.677  ?State_Advance_LAND@bilbo@@AAEXXZ
  using State_Advance_LAND_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_LAND(::bilbo * a0) { reinterpret_cast<State_Advance_LAND_t>(meridian::rebase(0x00429AE0))(a0); }
  // 0x00441450  conf=0.678  ?State_Advance_MINE_CART_RIDE@bilbo@@AAEXXZ
  using State_Advance_MINE_CART_RIDE_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_MINE_CART_RIDE(::bilbo * a0) { reinterpret_cast<State_Advance_MINE_CART_RIDE_t>(meridian::rebase(0x00441450))(a0); }
  // 0x00441A80  conf=0.693  ?State_Advance_MINE_CART_SWING@bilbo@@AAEXXZ
  using State_Advance_MINE_CART_SWING_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_MINE_CART_SWING(::bilbo * a0) { reinterpret_cast<State_Advance_MINE_CART_SWING_t>(meridian::rebase(0x00441A80))(a0); }
  // 0x0043FCC0  conf=0.97  ?State_Advance_POLEJUMP@bilbo@@AAEXXZ
  using State_Advance_POLEJUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_POLEJUMP(::bilbo * a0) { reinterpret_cast<State_Advance_POLEJUMP_t>(meridian::rebase(0x0043FCC0))(a0); }
  // 0x00430B90  conf=0.761  ?State_Advance_PUSH_BLOCK@bilbo@@AAEXXZ
  using State_Advance_PUSH_BLOCK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_PUSH_BLOCK(::bilbo * a0) { reinterpret_cast<State_Advance_PUSH_BLOCK_t>(meridian::rebase(0x00430B90))(a0); }
  // 0x0044B3B0  conf=0.97  ?State_Advance_ROPE_CLIMB@bilbo@@AAEXXZ
  using State_Advance_ROPE_CLIMB_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_ROPE_CLIMB(::bilbo * a0) { reinterpret_cast<State_Advance_ROPE_CLIMB_t>(meridian::rebase(0x0044B3B0))(a0); }
  // 0x0043B970  conf=0.97  ?State_Advance_RUN@bilbo@@AAEXXZ
  using State_Advance_RUN_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_RUN(::bilbo * a0) { reinterpret_cast<State_Advance_RUN_t>(meridian::rebase(0x0043B970))(a0); }
  // 0x0044C250  conf=0.9  ?State_Advance_SLIDING@bilbo@@AAEXXZ
  using State_Advance_SLIDING_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_SLIDING(::bilbo * a0) { reinterpret_cast<State_Advance_SLIDING_t>(meridian::rebase(0x0044C250))(a0); }
  // 0x0043CEA0  conf=0.694  ?State_Advance_SNEAK@bilbo@@AAEXXZ
  using State_Advance_SNEAK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_SNEAK(::bilbo * a0) { reinterpret_cast<State_Advance_SNEAK_t>(meridian::rebase(0x0043CEA0))(a0); }
  // 0x00428850  conf=0.74  ?State_Advance_STONE_ATTACK@bilbo@@AAEXXZ
  using State_Advance_STONE_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_STONE_ATTACK(::bilbo * a0) { reinterpret_cast<State_Advance_STONE_ATTACK_t>(meridian::rebase(0x00428850))(a0); }
  // 0x004299E0  conf=0.711  ?State_Advance_TARG_IDLE@bilbo@@AAEXXZ
  using State_Advance_TARG_IDLE_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_TARG_IDLE(::bilbo * a0) { reinterpret_cast<State_Advance_TARG_IDLE_t>(meridian::rebase(0x004299E0))(a0); }
  // 0x00429410  conf=0.764  ?State_Advance_TARG_JUMP@bilbo@@AAEXXZ
  using State_Advance_TARG_JUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_TARG_JUMP(::bilbo * a0) { reinterpret_cast<State_Advance_TARG_JUMP_t>(meridian::rebase(0x00429410))(a0); }
  // 0x00428AA0  conf=0.85  ?State_Advance_TARG_RUN@bilbo@@AAEXXZ
  using State_Advance_TARG_RUN_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_TARG_RUN(::bilbo * a0) { reinterpret_cast<State_Advance_TARG_RUN_t>(meridian::rebase(0x00428AA0))(a0); }
  // 0x00441060  conf=0.772  ?State_Advance_TARG_STRAFEATTACK@bilbo@@AAEXXZ
  using State_Advance_TARG_STRAFEATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_TARG_STRAFEATTACK(::bilbo * a0) { reinterpret_cast<State_Advance_TARG_STRAFEATTACK_t>(meridian::rebase(0x00441060))(a0); }
  // 0x0042A5D0  conf=0.778  ?State_Advance_USE@bilbo@@AAEXXZ
  using State_Advance_USE_t = void (__thiscall*)(::bilbo *);
  inline void State_Advance_USE(::bilbo * a0) { reinterpret_cast<State_Advance_USE_t>(meridian::rebase(0x0042A5D0))(a0); }
  // 0x0042A0D0  conf=0.97  ?State_Enter_BACKWARD_BLOCK@bilbo@@AAEXXZ
  using State_Enter_BACKWARD_BLOCK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_BACKWARD_BLOCK(::bilbo * a0) { reinterpret_cast<State_Enter_BACKWARD_BLOCK_t>(meridian::rebase(0x0042A0D0))(a0); }
  // 0x0042A550  conf=0.97  ?State_Enter_BLOCKED@bilbo@@AAEXXZ
  using State_Enter_BLOCKED_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_BLOCKED(::bilbo * a0) { reinterpret_cast<State_Enter_BLOCKED_t>(meridian::rebase(0x0042A550))(a0); }
  // 0x00427390  conf=0.97  ?State_Enter_CHAIN_ATTACK@bilbo@@AAEXXZ
  using State_Enter_CHAIN_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_CHAIN_ATTACK(::bilbo * a0) { reinterpret_cast<State_Enter_CHAIN_ATTACK_t>(meridian::rebase(0x00427390))(a0); }
  // 0x004422B0  conf=0.797  ?State_Enter_CINEMATIC@bilbo@@AAEXXZ
  using State_Enter_CINEMATIC_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_CINEMATIC(::bilbo * a0) { reinterpret_cast<State_Enter_CINEMATIC_t>(meridian::rebase(0x004422B0))(a0); }
  // 0x004385D0  conf=0.97  ?State_Enter_CLIMB_LADDER@bilbo@@AAEXXZ
  using State_Enter_CLIMB_LADDER_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_CLIMB_LADDER(::bilbo * a0) { reinterpret_cast<State_Enter_CLIMB_LADDER_t>(meridian::rebase(0x004385D0))(a0); }
  // 0x0043F1C0  conf=0.97  ?State_Enter_CLIMB_WALL@bilbo@@AAEXXZ
  using State_Enter_CLIMB_WALL_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_CLIMB_WALL(::bilbo * a0) { reinterpret_cast<State_Enter_CLIMB_WALL_t>(meridian::rebase(0x0043F1C0))(a0); }
  // 0x00442070  conf=0.9  ?State_Enter_CONVERSATION_LISTEN@bilbo@@AAEXXZ
  using State_Enter_CONVERSATION_LISTEN_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_CONVERSATION_LISTEN(::bilbo * a0) { reinterpret_cast<State_Enter_CONVERSATION_LISTEN_t>(meridian::rebase(0x00442070))(a0); }
  // 0x00442140  conf=0.97  ?State_Enter_CONVERSATION_TALK@bilbo@@AAEXXZ
  using State_Enter_CONVERSATION_TALK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_CONVERSATION_TALK(::bilbo * a0) { reinterpret_cast<State_Enter_CONVERSATION_TALK_t>(meridian::rebase(0x00442140))(a0); }
  // 0x0043EF60  conf=0.97  ?State_Enter_CROUCH_SLIDE@bilbo@@AAEXXZ
  using State_Enter_CROUCH_SLIDE_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_CROUCH_SLIDE(::bilbo * a0) { reinterpret_cast<State_Enter_CROUCH_SLIDE_t>(meridian::rebase(0x0043EF60))(a0); }
  // 0x00440DE0  conf=0.771  ?State_Enter_DEATH@bilbo@@AAEXXZ
  using State_Enter_DEATH_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_DEATH(::bilbo * a0) { reinterpret_cast<State_Enter_DEATH_t>(meridian::rebase(0x00440DE0))(a0); }
  // 0x00441000  conf=0.75  ?State_Enter_DEATH_FALL@bilbo@@AAEXXZ
  using State_Enter_DEATH_FALL_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_DEATH_FALL(::bilbo * a0) { reinterpret_cast<State_Enter_DEATH_FALL_t>(meridian::rebase(0x00441000))(a0); }
  // 0x00441160  conf=0.97  ?State_Enter_DEATH_WATER@bilbo@@AAEXXZ
  using State_Enter_DEATH_WATER_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_DEATH_WATER(::bilbo * a0) { reinterpret_cast<State_Enter_DEATH_WATER_t>(meridian::rebase(0x00441160))(a0); }
  // 0x0042EF70  conf=0.75  ?State_Enter_EDGE_DROP_OFF@bilbo@@AAEXXZ
  using State_Enter_EDGE_DROP_OFF_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_EDGE_DROP_OFF(::bilbo * a0) { reinterpret_cast<State_Enter_EDGE_DROP_OFF_t>(meridian::rebase(0x0042EF70))(a0); }
  // 0x0042E0C0  conf=0.741  ?State_Enter_EDGE_GRAB@bilbo@@AAEXXZ
  using State_Enter_EDGE_GRAB_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_EDGE_GRAB(::bilbo * a0) { reinterpret_cast<State_Enter_EDGE_GRAB_t>(meridian::rebase(0x0042E0C0))(a0); }
  // 0x0042DD20  conf=0.749  ?State_Enter_EDGE_MOUNT@bilbo@@AAEXXZ
  using State_Enter_EDGE_MOUNT_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_EDGE_MOUNT(::bilbo * a0) { reinterpret_cast<State_Enter_EDGE_MOUNT_t>(meridian::rebase(0x0042DD20))(a0); }
  // 0x0042EC70  conf=0.97  ?State_Enter_EDGE_PULLUP@bilbo@@AAEXXZ
  using State_Enter_EDGE_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_EDGE_PULLUP(::bilbo * a0) { reinterpret_cast<State_Enter_EDGE_PULLUP_t>(meridian::rebase(0x0042EC70))(a0); }
  // 0x0043E180  conf=0.736  ?State_Enter_FALL@bilbo@@AAEXXZ
  using State_Enter_FALL_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_FALL(::bilbo * a0) { reinterpret_cast<State_Enter_FALL_t>(meridian::rebase(0x0043E180))(a0); }
  // 0x0043B130  conf=0.796  ?State_Enter_FIDGET@bilbo@@AAEXXZ
  using State_Enter_FIDGET_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_FIDGET(::bilbo * a0) { reinterpret_cast<State_Enter_FIDGET_t>(meridian::rebase(0x0043B130))(a0); }
  // 0x00440530  conf=0.85  ?State_Enter_FIRST_PERSON_LOOK@bilbo@@AAEXXZ
  using State_Enter_FIRST_PERSON_LOOK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_FIRST_PERSON_LOOK(::bilbo * a0) { reinterpret_cast<State_Enter_FIRST_PERSON_LOOK_t>(meridian::rebase(0x00440530))(a0); }
  // 0x0043EE60  conf=0.797  ?State_Enter_FLY@bilbo@@AAEXXZ
  using State_Enter_FLY_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_FLY(::bilbo * a0) { reinterpret_cast<State_Enter_FLY_t>(meridian::rebase(0x0043EE60))(a0); }
  // 0x00429C60  conf=0.97  ?State_Enter_FORWARD_INAIR_ATTACK@bilbo@@AAEXXZ
  using State_Enter_FORWARD_INAIR_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_FORWARD_INAIR_ATTACK(::bilbo * a0) { reinterpret_cast<State_Enter_FORWARD_INAIR_ATTACK_t>(meridian::rebase(0x00429C60))(a0); }
  // 0x004314F0  conf=0.97  ?State_Enter_HOISTING@bilbo@@AAEXXZ
  using State_Enter_HOISTING_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_HOISTING(::bilbo * a0) { reinterpret_cast<State_Enter_HOISTING_t>(meridian::rebase(0x004314F0))(a0); }
  // 0x0043A6A0  conf=0.9  ?State_Enter_IDLE@bilbo@@AAEXXZ
  using State_Enter_IDLE_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_IDLE(::bilbo * a0) { reinterpret_cast<State_Enter_IDLE_t>(meridian::rebase(0x0043A6A0))(a0); }
  // 0x0043D570  conf=0.97  ?State_Enter_JUMP@bilbo@@AAEXXZ
  using State_Enter_JUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_JUMP(::bilbo * a0) { reinterpret_cast<State_Enter_JUMP_t>(meridian::rebase(0x0043D570))(a0); }
  // 0x0042A280  conf=0.97  ?State_Enter_KNOCKBACK@bilbo@@AAEXXZ
  using State_Enter_KNOCKBACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_KNOCKBACK(::bilbo * a0) { reinterpret_cast<State_Enter_KNOCKBACK_t>(meridian::rebase(0x0042A280))(a0); }
  // 0x00439500  conf=0.75  ?State_Enter_LADDER_PULLUP@bilbo@@AAEXXZ
  using State_Enter_LADDER_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_LADDER_PULLUP(::bilbo * a0) { reinterpret_cast<State_Enter_LADDER_PULLUP_t>(meridian::rebase(0x00439500))(a0); }
  // 0x0043E970  conf=0.97  ?State_Enter_LAND@bilbo@@AAEXXZ
  using State_Enter_LAND_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_LAND(::bilbo * a0) { reinterpret_cast<State_Enter_LAND_t>(meridian::rebase(0x0043E970))(a0); }
  // 0x00441F70  conf=0.749  ?State_Enter_LAUNCHING@bilbo@@AAEXXZ
  using State_Enter_LAUNCHING_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_LAUNCHING(::bilbo * a0) { reinterpret_cast<State_Enter_LAUNCHING_t>(meridian::rebase(0x00441F70))(a0); }
  // 0x00441370  conf=0.97  ?State_Enter_MINE_CART_RIDE@bilbo@@AAEXXZ
  using State_Enter_MINE_CART_RIDE_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_MINE_CART_RIDE(::bilbo * a0) { reinterpret_cast<State_Enter_MINE_CART_RIDE_t>(meridian::rebase(0x00441370))(a0); }
  // 0x004419D0  conf=0.97  ?State_Enter_MINE_CART_SWING@bilbo@@AAEXXZ
  using State_Enter_MINE_CART_SWING_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_MINE_CART_SWING(::bilbo * a0) { reinterpret_cast<State_Enter_MINE_CART_SWING_t>(meridian::rebase(0x004419D0))(a0); }
  // 0x0043FBD0  conf=0.97  ?State_Enter_POLEJUMP@bilbo@@AAEXXZ
  using State_Enter_POLEJUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_POLEJUMP(::bilbo * a0) { reinterpret_cast<State_Enter_POLEJUMP_t>(meridian::rebase(0x0043FBD0))(a0); }
  // 0x00448BA0  conf=0.85  ?State_Enter_PUSH_BLOCK@bilbo@@AAEXXZ
  using State_Enter_PUSH_BLOCK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_PUSH_BLOCK(::bilbo * a0) { reinterpret_cast<State_Enter_PUSH_BLOCK_t>(meridian::rebase(0x00448BA0))(a0); }
  // 0x0044B1B0  conf=0.97  ?State_Enter_ROPE_CLIMB@bilbo@@AAEXXZ
  using State_Enter_ROPE_CLIMB_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_ROPE_CLIMB(::bilbo * a0) { reinterpret_cast<State_Enter_ROPE_CLIMB_t>(meridian::rebase(0x0044B1B0))(a0); }
  // 0x0043B940  conf=0.702  ?State_Enter_SLIDING@bilbo@@AAEXXZ
  using State_Enter_SLIDING_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_SLIDING(::bilbo * a0) { reinterpret_cast<State_Enter_SLIDING_t>(meridian::rebase(0x0043B940))(a0); }
  // 0x0043CDC0  conf=0.85  ?State_Enter_SNEAK@bilbo@@AAEXXZ
  using State_Enter_SNEAK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_SNEAK(::bilbo * a0) { reinterpret_cast<State_Enter_SNEAK_t>(meridian::rebase(0x0043CDC0))(a0); }
  // 0x00429A60  conf=0.746  ?State_Enter_STONE_ATTACK@bilbo@@AAEXXZ
  using State_Enter_STONE_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_STONE_ATTACK(::bilbo * a0) { reinterpret_cast<State_Enter_STONE_ATTACK_t>(meridian::rebase(0x00429A60))(a0); }
  // 0x00429110  conf=0.782  ?State_Enter_TARG_JUMP@bilbo@@AAEXXZ
  using State_Enter_TARG_JUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_TARG_JUMP(::bilbo * a0) { reinterpret_cast<State_Enter_TARG_JUMP_t>(meridian::rebase(0x00429110))(a0); }
  // 0x00428830  conf=0.75  ?State_Enter_TARG_RUN@bilbo@@AAEXXZ
  using State_Enter_TARG_RUN_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_TARG_RUN(::bilbo * a0) { reinterpret_cast<State_Enter_TARG_RUN_t>(meridian::rebase(0x00428830))(a0); }
  // 0x004298D0  conf=0.97  ?State_Enter_TARG_STRAFEATTACK@bilbo@@AAEXXZ
  using State_Enter_TARG_STRAFEATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_TARG_STRAFEATTACK(::bilbo * a0) { reinterpret_cast<State_Enter_TARG_STRAFEATTACK_t>(meridian::rebase(0x004298D0))(a0); }
  // 0x0044DFC0  conf=0.85  ?State_Enter_USE@bilbo@@AAEXXZ
  using State_Enter_USE_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_USE(::bilbo * a0) { reinterpret_cast<State_Enter_USE_t>(meridian::rebase(0x0044DFC0))(a0); }
  // 0x0043A390  conf=0.585  ?State_Enter_WALL_PULLUP@bilbo@@AAEXXZ
  using State_Enter_WALL_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Enter_WALL_PULLUP(::bilbo * a0) { reinterpret_cast<State_Enter_WALL_PULLUP_t>(meridian::rebase(0x0043A390))(a0); }
  // 0x004287E0  conf=0.777  ?State_Exit_CHAIN_ATTACK@bilbo@@AAEXXZ
  using State_Exit_CHAIN_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_CHAIN_ATTACK(::bilbo * a0) { reinterpret_cast<State_Exit_CHAIN_ATTACK_t>(meridian::rebase(0x004287E0))(a0); }
  // 0x00439490  conf=0.747  ?State_Exit_CLIMB_LADDER@bilbo@@AAEXXZ
  using State_Exit_CLIMB_LADDER_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_CLIMB_LADDER(::bilbo * a0) { reinterpret_cast<State_Exit_CLIMB_LADDER_t>(meridian::rebase(0x00439490))(a0); }
  // 0x0042EC20  conf=0.717  ?State_Exit_CLIMB_WALL@bilbo@@AAEXXZ
  using State_Exit_CLIMB_WALL_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_CLIMB_WALL(::bilbo * a0) { reinterpret_cast<State_Exit_CLIMB_WALL_t>(meridian::rebase(0x0042EC20))(a0); }
  // 0x00442270  conf=0.75  ?State_Exit_CONVERSATION_TALK@bilbo@@AAEXXZ
  using State_Exit_CONVERSATION_TALK_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_CONVERSATION_TALK(::bilbo * a0) { reinterpret_cast<State_Exit_CONVERSATION_TALK_t>(meridian::rebase(0x00442270))(a0); }
  // 0x00440F70  conf=0.737  ?State_Exit_DEATH@bilbo@@AAEXXZ
  using State_Exit_DEATH_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_DEATH(::bilbo * a0) { reinterpret_cast<State_Exit_DEATH_t>(meridian::rebase(0x00440F70))(a0); }
  // 0x00441300  conf=0.797  ?State_Exit_DEATH_WATER@bilbo@@AAEXXZ
  using State_Exit_DEATH_WATER_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_DEATH_WATER(::bilbo * a0) { reinterpret_cast<State_Exit_DEATH_WATER_t>(meridian::rebase(0x00441300))(a0); }
  // 0x0043F910  conf=0.75  ?State_Exit_EDGE_GRAB@bilbo@@AAEXXZ
  using State_Exit_EDGE_GRAB_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_EDGE_GRAB(::bilbo * a0) { reinterpret_cast<State_Exit_EDGE_GRAB_t>(meridian::rebase(0x0043F910))(a0); }
  // 0x0042E070  conf=0.75  ?State_Exit_EDGE_MOUNT@bilbo@@AAEXXZ
  using State_Exit_EDGE_MOUNT_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_EDGE_MOUNT(::bilbo * a0) { reinterpret_cast<State_Exit_EDGE_MOUNT_t>(meridian::rebase(0x0042E070))(a0); }
  // 0x0042EED0  conf=0.748  ?State_Exit_EDGE_PULLUP@bilbo@@AAEXXZ
  using State_Exit_EDGE_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_EDGE_PULLUP(::bilbo * a0) { reinterpret_cast<State_Exit_EDGE_PULLUP_t>(meridian::rebase(0x0042EED0))(a0); }
  // 0x0043E880  conf=0.747  ?State_Exit_FALL@bilbo@@AAEXXZ
  using State_Exit_FALL_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_FALL(::bilbo * a0) { reinterpret_cast<State_Exit_FALL_t>(meridian::rebase(0x0043E880))(a0); }
  // 0x00440B70  conf=0.97  ?State_Exit_FIRST_PERSON_LOOK@bilbo@@AAEXXZ
  using State_Exit_FIRST_PERSON_LOOK_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_FIRST_PERSON_LOOK(::bilbo * a0) { reinterpret_cast<State_Exit_FIRST_PERSON_LOOK_t>(meridian::rebase(0x00440B70))(a0); }
  // 0x0042A030  conf=0.791  ?State_Exit_FORWARD_INAIR_ATTACK@bilbo@@AAEXXZ
  using State_Exit_FORWARD_INAIR_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_FORWARD_INAIR_ATTACK(::bilbo * a0) { reinterpret_cast<State_Exit_FORWARD_INAIR_ATTACK_t>(meridian::rebase(0x0042A030))(a0); }
  // 0x00432140  conf=0.97  ?State_Exit_HOISTING@bilbo@@AAEXXZ
  using State_Exit_HOISTING_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_HOISTING(::bilbo * a0) { reinterpret_cast<State_Exit_HOISTING_t>(meridian::rebase(0x00432140))(a0); }
  // 0x0043B110  conf=0.75  ?State_Exit_IDLE@bilbo@@AAEXXZ
  using State_Exit_IDLE_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_IDLE(::bilbo * a0) { reinterpret_cast<State_Exit_IDLE_t>(meridian::rebase(0x0043B110))(a0); }
  // 0x0043E0A0  conf=0.794  ?State_Exit_JUMP@bilbo@@AAEXXZ
  using State_Exit_JUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_JUMP(::bilbo * a0) { reinterpret_cast<State_Exit_JUMP_t>(meridian::rebase(0x0043E0A0))(a0); }
  // 0x00439770  conf=0.75  ?State_Exit_LADDER_PULLUP@bilbo@@AAEXXZ
  using State_Exit_LADDER_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_LADDER_PULLUP(::bilbo * a0) { reinterpret_cast<State_Exit_LADDER_PULLUP_t>(meridian::rebase(0x00439770))(a0); }
  // 0x00441880  conf=0.771  ?State_Exit_MINE_CART_RIDE@bilbo@@AAEXXZ
  using State_Exit_MINE_CART_RIDE_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_MINE_CART_RIDE(::bilbo * a0) { reinterpret_cast<State_Exit_MINE_CART_RIDE_t>(meridian::rebase(0x00441880))(a0); }
  // 0x00441E30  conf=0.769  ?State_Exit_MINE_CART_SWING@bilbo@@AAEXXZ
  using State_Exit_MINE_CART_SWING_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_MINE_CART_SWING(::bilbo * a0) { reinterpret_cast<State_Exit_MINE_CART_SWING_t>(meridian::rebase(0x00441E30))(a0); }
  // 0x004404D0  conf=0.75  ?State_Exit_POLEJUMP@bilbo@@AAEXXZ
  using State_Exit_POLEJUMP_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_POLEJUMP(::bilbo * a0) { reinterpret_cast<State_Exit_POLEJUMP_t>(meridian::rebase(0x004404D0))(a0); }
  // 0x004497B0  conf=0.746  ?State_Exit_PUSH_BLOCK@bilbo@@AAEXXZ
  using State_Exit_PUSH_BLOCK_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_PUSH_BLOCK(::bilbo * a0) { reinterpret_cast<State_Exit_PUSH_BLOCK_t>(meridian::rebase(0x004497B0))(a0); }
  // 0x0044C080  conf=0.97  ?State_Exit_ROPE_CLIMB@bilbo@@AAEXXZ
  using State_Exit_ROPE_CLIMB_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_ROPE_CLIMB(::bilbo * a0) { reinterpret_cast<State_Exit_ROPE_CLIMB_t>(meridian::rebase(0x0044C080))(a0); }
  // 0x0043CD70  conf=0.75  ?State_Exit_RUN@bilbo@@AAEXXZ
  using State_Exit_RUN_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_RUN(::bilbo * a0) { reinterpret_cast<State_Exit_RUN_t>(meridian::rebase(0x0043CD70))(a0); }
  // 0x00429C50  conf=0.75  ?State_Exit_STONE_ATTACK@bilbo@@AAEXXZ
  using State_Exit_STONE_ATTACK_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_STONE_ATTACK(::bilbo * a0) { reinterpret_cast<State_Exit_STONE_ATTACK_t>(meridian::rebase(0x00429C50))(a0); }
  // 0x0043FB50  conf=0.747  ?State_Exit_WALL_PULLUP@bilbo@@AAEXXZ
  using State_Exit_WALL_PULLUP_t = void (__thiscall*)(::bilbo *);
  inline void State_Exit_WALL_PULLUP(::bilbo * a0) { reinterpret_cast<State_Exit_WALL_PULLUP_t>(meridian::rebase(0x0043FB50))(a0); }
  // 0x0043A420  conf=0.97  ?State_GetName@bilbo@@AAEPBDW4state@1@@Z
  inline void* State_GetName_at() { return meridian::rebase(0x0043A420); } // char * __thiscall State_GetName(bilbo *, state)
  // 0x00420330  conf=0.735  ?SurfaceTags_Update@bilbo@@QAEXXZ
  using SurfaceTags_Update_t = void (__thiscall*)(::bilbo *);
  inline void SurfaceTags_Update(::bilbo * a0) { reinterpret_cast<SurfaceTags_Update_t>(meridian::rebase(0x00420330))(a0); }
  // 0x0044D500  conf=0.742  ?Switches_DrawSwitchIndicator@bilbo@@QAEXXZ
  using Switches_DrawSwitchIndicator_t = void (__thiscall*)(::bilbo *);
  inline void Switches_DrawSwitchIndicator(::bilbo * a0) { reinterpret_cast<Switches_DrawSwitchIndicator_t>(meridian::rebase(0x0044D500))(a0); }
  // 0x0044D740  conf=0.735  ?Treasure_DrawChestIndicator@bilbo@@QAEXXZ
  using Treasure_DrawChestIndicator_t = void (__thiscall*)(::bilbo *);
  inline void Treasure_DrawChestIndicator(::bilbo * a0) { reinterpret_cast<Treasure_DrawChestIndicator_t>(meridian::rebase(0x0044D740))(a0); }
  // 0x0044D370  conf=0.742  ?Triggers_DrawIndicator@bilbo@@QAEXXZ
  using Triggers_DrawIndicator_t = void (__thiscall*)(::bilbo *);
  inline void Triggers_DrawIndicator(::bilbo * a0) { reinterpret_cast<Triggers_DrawIndicator_t>(meridian::rebase(0x0044D370))(a0); }
  // 0x00582C00  conf=0.762  ?UpdatePickupLight@bilbo@@QAEXXZ
  using UpdatePickupLight_t = void (__thiscall*)(::bilbo *);
  inline void UpdatePickupLight(::bilbo * a0) { reinterpret_cast<UpdatePickupLight_t>(meridian::rebase(0x00582C00))(a0); }
  // 0x00426ED0  conf=0.792  ?UpdatePoison@bilbo@@AAEXXZ
  using UpdatePoison_t = void (__thiscall*)(::bilbo *);
  inline void UpdatePoison(::bilbo * a0) { reinterpret_cast<UpdatePoison_t>(meridian::rebase(0x00426ED0))(a0); }
  // 0x0041FD30  conf=0.777  ?UpdateProps@bilbo@@AAEXXZ
  using UpdateProps_t = void (__thiscall*)(::bilbo *);
  inline void UpdateProps(::bilbo * a0) { reinterpret_cast<UpdateProps_t>(meridian::rebase(0x0041FD30))(a0); }
  // 0x00422FC0  conf=0.97  ?Water_CheckForWater@bilbo@@QAEXUxhandle@@@Z
  inline void* Water_CheckForWater_at() { return meridian::rebase(0x00422FC0); } // void __thiscall Water_CheckForWater(bilbo *, xhandle)
  // 0x0044EA20  conf=0.97  ?Web_Advance@bilbo@@IAEXM@Z
  using Web_Advance_t = void (__thiscall*)(::bilbo *, float);
  inline void Web_Advance(::bilbo * a0, float a1) { reinterpret_cast<Web_Advance_t>(meridian::rebase(0x0044EA20))(a0, a1); }
  // 0x0044EC20  conf=0.742  ?Web_DeactivateAll@bilbo@@IAEXXZ
  using Web_DeactivateAll_t = void (__thiscall*)(::bilbo *);
  inline void Web_DeactivateAll(::bilbo * a0) { reinterpret_cast<Web_DeactivateAll_t>(meridian::rebase(0x0044EC20))(a0); }
  // 0x0041C2F0  conf=0.686  ??0bilbo@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::bilbo *);
  inline undefined ctor(::bilbo * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0041C2F0))(a0); }
  // 0x0043A3F0  conf=0.785  ?debug_ChangeStateTo@bilbo@@AAEXW4state@1@PBDH@Z
  inline void* debug_ChangeStateTo_at() { return meridian::rebase(0x0043A3F0); } // void __thiscall debug_ChangeStateTo(bilbo *, state, char *, int)
} // bilbo_

// ===== bilboInventory =====  (38 functions)  ->  namespace bilboInventory_
namespace bilboInventory_ {
  // 0x00434CF0  conf=0.712  ?Add@bilboInventory@@QAEXH@Z
  using Add_t = void (__thiscall*)(::bilboInventory *, int);
  inline void Add(::bilboInventory * a0, int a1) { reinterpret_cast<Add_t>(meridian::rebase(0x00434CF0))(a0, a1); }
  // 0x00434D10  conf=0.725  ?Add@bilboInventory@@QAEXHM@Z
  using Add_434D10_t = void (__thiscall*)(::bilboInventory *, int, float);
  inline void Add_434D10(::bilboInventory * a0, int a1, float a2) { reinterpret_cast<Add_434D10_t>(meridian::rebase(0x00434D10))(a0, a1, a2); }
  // 0x00434D90  conf=0.715  ?Add@bilboInventory@@QAEXABVxstring@@M@Z
  using Add_434D90_t = void (__thiscall*)(::bilboInventory *, ::xstring *, float);
  inline void Add_434D90(::bilboInventory * a0, ::xstring * a1, float a2) { reinterpret_cast<Add_434D90_t>(meridian::rebase(0x00434D90))(a0, a1, a2); }
  // 0x00434400  conf=0.748  ?ClearChapterSpacificInventory@bilboInventory@@QAEXXZ
  using ClearChapterSpacificInventory_t = void (__thiscall*)(::bilboInventory *);
  inline void ClearChapterSpacificInventory(::bilboInventory * a0) { reinterpret_cast<ClearChapterSpacificInventory_t>(meridian::rebase(0x00434400))(a0); }
  // 0x00435880  conf=0.765  ?DrinkPotion@bilboInventory@@QAEXXZ
  using DrinkPotion_t = void (__thiscall*)(::bilboInventory *);
  inline void DrinkPotion(::bilboInventory * a0) { reinterpret_cast<DrinkPotion_t>(meridian::rebase(0x00435880))(a0); }
  // 0x0056B710  conf=0.745  ?EquipWeapon@bilboInventory@@QAEXW4SlotTypes@1@@Z
  inline void* EquipWeapon_at() { return meridian::rebase(0x0056B710); } // void __thiscall EquipWeapon(bilboInventory *, SlotTypes)
  // 0x00434C10  conf=0.683  ?GetBilboMaxHealth@bilboInventory@@QAEMXZ
  using GetBilboMaxHealth_t = float (__thiscall*)(::bilboInventory *);
  inline float GetBilboMaxHealth(::bilboInventory * a0) { return reinterpret_cast<GetBilboMaxHealth_t>(meridian::rebase(0x00434C10))(a0); }
  // 0x00423C80  conf=0.683  ?GetDPadSlotSelected@bilboInventory@@QAEHXZ
  using GetDPadSlotSelected_t = int (__thiscall*)(::bilboInventory *);
  inline int GetDPadSlotSelected(::bilboInventory * a0) { return reinterpret_cast<GetDPadSlotSelected_t>(meridian::rebase(0x00423C80))(a0); }
  // 0x00433B30  conf=0.75  ?GetInventoryItemGeomName@bilboInventory@@QAEPBDH@Z
  using GetInventoryItemGeomName_t = char * (__thiscall*)(::bilboInventory *, int);
  inline char * GetInventoryItemGeomName(::bilboInventory * a0, int a1) { return reinterpret_cast<GetInventoryItemGeomName_t>(meridian::rebase(0x00433B30))(a0, a1); }
  // 0x00435800  conf=0.8  ?GetItemInDPadSlot@bilboInventory@@QAEHH@Z
  using GetItemInDPadSlot_t = int (__thiscall*)(::bilboInventory *, int);
  inline int GetItemInDPadSlot(::bilboInventory * a0, int a1) { return reinterpret_cast<GetItemInDPadSlot_t>(meridian::rebase(0x00435800))(a0, a1); }
  // 0x00434EB0  conf=0.8  ?GetItemIndex@bilboInventory@@QAEHABVxstring@@@Z
  using GetItemIndex_t = int (__thiscall*)(::bilboInventory *, ::xstring *);
  inline int GetItemIndex(::bilboInventory * a0, ::xstring * a1) { return reinterpret_cast<GetItemIndex_t>(meridian::rebase(0x00434EB0))(a0, a1); }
  // 0x00434E80  conf=0.742  ?GetItemName@bilboInventory@@QAEPADH@Z
  using GetItemName_t = char * (__thiscall*)(::bilboInventory *, int);
  inline char * GetItemName(::bilboInventory * a0, int a1) { return reinterpret_cast<GetItemName_t>(meridian::rebase(0x00434E80))(a0, a1); }
  // 0x00434E60  conf=0.75  ?GetItemNameWide@bilboInventory@@QAEPBGH@Z
  using GetItemNameWide_t = ushort * (__thiscall*)(::bilboInventory *, int);
  inline ushort * GetItemNameWide(::bilboInventory * a0, int a1) { return reinterpret_cast<GetItemNameWide_t>(meridian::rebase(0x00434E60))(a0, a1); }
  // 0x00434FB0  conf=0.8  ?GetMax@bilboInventory@@QAEMH@Z
  using GetMax_t = float (__thiscall*)(::bilboInventory *, int);
  inline float GetMax(::bilboInventory * a0, int a1) { return reinterpret_cast<GetMax_t>(meridian::rebase(0x00434FB0))(a0, a1); }
  // 0x00436DF0  conf=0.719  ?GetNumQuestsFinished@bilboInventory@@QAEHXZ
  using GetNumQuestsFinished_t = int (__thiscall*)(::bilboInventory *);
  inline int GetNumQuestsFinished(::bilboInventory * a0) { return reinterpret_cast<GetNumQuestsFinished_t>(meridian::rebase(0x00436DF0))(a0); }
  // 0x00437340  conf=0.732  ?GetNumberOfQuests@bilboInventory@@QAEHXZ
  using GetNumberOfQuests_t = int (__thiscall*)(::bilboInventory *);
  inline int GetNumberOfQuests(::bilboInventory * a0) { return reinterpret_cast<GetNumberOfQuests_t>(meridian::rebase(0x00437340))(a0); }
  // 0x00436DB0  conf=0.75  ?GetQuestByIndex@bilboInventory@@QAEHH@Z
  using GetQuestByIndex_t = int (__thiscall*)(::bilboInventory *, int);
  inline int GetQuestByIndex(::bilboInventory * a0, int a1) { return reinterpret_cast<GetQuestByIndex_t>(meridian::rebase(0x00436DB0))(a0, a1); }
  // 0x00436E60  conf=0.97  ?GetQuestDescByIndex@bilboInventory@@QAEPBGH@Z
  using GetQuestDescByIndex_t = ushort * (__thiscall*)(::bilboInventory *, int);
  inline ushort * GetQuestDescByIndex(::bilboInventory * a0, int a1) { return reinterpret_cast<GetQuestDescByIndex_t>(meridian::rebase(0x00436E60))(a0, a1); }
  // 0x00435940  conf=0.8  ?GetQuestItemName@bilboInventory@@QAEPADH@Z
  using GetQuestItemName_t = char * (__thiscall*)(::bilboInventory *, int);
  inline char * GetQuestItemName(::bilboInventory * a0, int a1) { return reinterpret_cast<GetQuestItemName_t>(meridian::rebase(0x00435940))(a0, a1); }
  // 0x00436E10  conf=0.85  ?GetQuestNameByIndex@bilboInventory@@QAEPBGH@Z
  using GetQuestNameByIndex_t = ushort * (__thiscall*)(::bilboInventory *, int);
  inline ushort * GetQuestNameByIndex(::bilboInventory * a0, int a1) { return reinterpret_cast<GetQuestNameByIndex_t>(meridian::rebase(0x00436E10))(a0, a1); }
  // 0x00436DD0  conf=0.75  ?GetQuestRequired@bilboInventory@@QAEHH@Z
  using GetQuestRequired_t = int (__thiscall*)(::bilboInventory *, int);
  inline int GetQuestRequired(::bilboInventory * a0, int a1) { return reinterpret_cast<GetQuestRequired_t>(meridian::rebase(0x00436DD0))(a0, a1); }
  // 0x00434E50  conf=0.712  ?GetTotalItems@bilboInventory@@QAEHXZ
  using GetTotalItems_t = int (__thiscall*)(::bilboInventory *);
  inline int GetTotalItems(::bilboInventory * a0) { return reinterpret_cast<GetTotalItems_t>(meridian::rebase(0x00434E50))(a0); }
  // 0x00434CA0  conf=0.763  ?Has@bilboInventory@@QAEMH@Z
  using Has_t = float (__thiscall*)(::bilboInventory *, int);
  inline float Has(::bilboInventory * a0, int a1) { return reinterpret_cast<Has_t>(meridian::rebase(0x00434CA0))(a0, a1); }
  // 0x00434D70  conf=0.591  ?Has@bilboInventory@@QAEMABVxstring@@@Z
  using Has_434D70_t = float (__thiscall*)(::bilboInventory *, ::xstring *);
  inline float Has_434D70(::bilboInventory * a0, ::xstring * a1) { return reinterpret_cast<Has_434D70_t>(meridian::rebase(0x00434D70))(a0, a1); }
  // 0x004359A0  conf=0.97  ?InitQuestData@bilboInventory@@QAEXXZ
  using InitQuestData_t = void (__thiscall*)(::bilboInventory *);
  inline void InitQuestData(::bilboInventory * a0) { reinterpret_cast<InitQuestData_t>(meridian::rebase(0x004359A0))(a0); }
  // 0x00437330  conf=0.75  ?IsQuestFinished@bilboInventory@@QAEHH@Z
  using IsQuestFinished_t = int (__thiscall*)(::bilboInventory *, int);
  inline int IsQuestFinished(::bilboInventory * a0, int a1) { return reinterpret_cast<IsQuestFinished_t>(meridian::rebase(0x00437330))(a0, a1); }
  // 0x00434E40  conf=0.8  ?IsQuestItem@bilboInventory@@QAEHH@Z
  using IsQuestItem_t = int (__thiscall*)(::bilboInventory *, int);
  inline int IsQuestItem(::bilboInventory * a0, int a1) { return reinterpret_cast<IsQuestItem_t>(meridian::rebase(0x00434E40))(a0, a1); }
  // 0x00434DD0  conf=0.678  ?Remove@bilboInventory@@QAEXHM@Z
  using Remove_t = void (__thiscall*)(::bilboInventory *, int, float);
  inline void Remove(::bilboInventory * a0, int a1, float a2) { reinterpret_cast<Remove_t>(meridian::rebase(0x00434DD0))(a0, a1, a2); }
  // 0x00434E10  conf=0.738  ?Remove@bilboInventory@@QAEXABVxstring@@M@Z
  using Remove_434E10_t = void (__thiscall*)(::bilboInventory *, ::xstring *, float);
  inline void Remove_434E10(::bilboInventory * a0, ::xstring * a1, float a2) { reinterpret_cast<Remove_434E10_t>(meridian::rebase(0x00434E10))(a0, a1, a2); }
  // 0x004343C0  conf=0.75  ?ResetDPadSlots@bilboInventory@@QAEXXZ
  using ResetDPadSlots_t = void (__thiscall*)(::bilboInventory *);
  inline void ResetDPadSlots(::bilboInventory * a0) { reinterpret_cast<ResetDPadSlots_t>(meridian::rebase(0x004343C0))(a0); }
  // 0x00433C80  conf=0.657  ?ResetInventory@bilboInventory@@QAEXXZ
  using ResetInventory_t = void (__thiscall*)(::bilboInventory *);
  inline void ResetInventory(::bilboInventory * a0) { reinterpret_cast<ResetInventory_t>(meridian::rebase(0x00433C80))(a0); }
  // 0x00434C40  conf=0.696  ?Set@bilboInventory@@QAEXHM@Z
  using Set_t = void (__thiscall*)(::bilboInventory *, int, float);
  inline void Set(::bilboInventory * a0, int a1, float a2) { reinterpret_cast<Set_t>(meridian::rebase(0x00434C40))(a0, a1, a2); }
  // 0x00434C20  conf=0.715  ?SetBilboMaxHealth@bilboInventory@@QAEXM@Z
  using SetBilboMaxHealth_t = void (__thiscall*)(::bilboInventory *, float);
  inline void SetBilboMaxHealth(::bilboInventory * a0, float a1) { reinterpret_cast<SetBilboMaxHealth_t>(meridian::rebase(0x00434C20))(a0, a1); }
  // 0x00435900  conf=0.683  ?SetDPadSlotSelected@bilboInventory@@QAEXH@Z
  using SetDPadSlotSelected_t = void (__thiscall*)(::bilboInventory *, int);
  inline void SetDPadSlotSelected(::bilboInventory * a0, int a1) { reinterpret_cast<SetDPadSlotSelected_t>(meridian::rebase(0x00435900))(a0, a1); }
  // 0x00435820  conf=0.758  ?SetItemInDPadSlot@bilboInventory@@QAEXHHH@Z
  using SetItemInDPadSlot_t = void (__thiscall*)(::bilboInventory *, int, int, int);
  inline void SetItemInDPadSlot(::bilboInventory * a0, int a1, int a2, int a3) { reinterpret_cast<SetItemInDPadSlot_t>(meridian::rebase(0x00435820))(a0, a1, a2, a3); }
  // 0x00435330  conf=0.85  ?SetProperty@bilboInventory@@QAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::bilboInventory *, char *, ::property *);
  inline int SetProperty(::bilboInventory * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00435330))(a0, a1, a2); }
  // 0x00436D00  conf=0.677  ?UnloadQuestData@bilboInventory@@QAEXXZ
  using UnloadQuestData_t = void (__thiscall*)(::bilboInventory *);
  inline void UnloadQuestData(::bilboInventory * a0) { reinterpret_cast<UnloadQuestData_t>(meridian::rebase(0x00436D00))(a0); }
  // 0x004346D0  conf=0.97  ?Update@bilboInventory@@QAEXXZ
  using Update_t = void (__thiscall*)(::bilboInventory *);
  inline void Update(::bilboInventory * a0) { reinterpret_cast<Update_t>(meridian::rebase(0x004346D0))(a0); }
} // bilboInventory_

// ===== bin_in =====  (2 functions)  ->  namespace bin_in_
namespace bin_in_ {
  // 0x00463B80  conf=0.794  ?GetRadian3@bin_in@@QAEHPBDAAUradian3@@@Z
  using GetRadian3_t = int (__thiscall*)(::bin_in *, char *, ::radian3 *);
  inline int GetRadian3(::bin_in * a0, char * a1, ::radian3 * a2) { return reinterpret_cast<GetRadian3_t>(meridian::rebase(0x00463B80))(a0, a1, a2); }
  // 0x005F11B0  conf=0.93  ?SkipToNextHeader@bin_in@@QAEHXZ
  using SkipToNextHeader_t = int (__thiscall*)(::bin_in *);
  inline int SkipToNextHeader(::bin_in * a0) { return reinterpret_cast<SkipToNextHeader_t>(meridian::rebase(0x005F11B0))(a0); }
} // bin_in_

// ===== bin_out =====  (3 functions)  ->  namespace bin_out_
namespace bin_out_ {
  // 0x006408E0  conf=0.687  ?AddBBox@bin_out@@QAEXPBDABUbbox@@@Z
  using AddBBox_t = void (__thiscall*)(::bin_out *, char *, ::bbox *);
  inline void AddBBox(::bin_out * a0, char * a1, ::bbox * a2) { reinterpret_cast<AddBBox_t>(meridian::rebase(0x006408E0))(a0, a1, a2); }
  // 0x00641370  conf=0.791  ?AddColor@bin_out@@QAEXPBDUxcolor@@@Z
  inline void* AddColor_at() { return meridian::rebase(0x00641370); } // void __thiscall AddColor(bin_out *, char *, xcolor)
  // 0x00641600  conf=0.715  ?AddS32@bin_out@@QAEXPBDH@Z
  using AddS32_t = void (__thiscall*)(::bin_out *, char *, int);
  inline void AddS32(::bin_out * a0, char * a1, int a2) { reinterpret_cast<AddS32_t>(meridian::rebase(0x00641600))(a0, a1, a2); }
} // bin_out_

// ===== bitstream =====  (2 functions)  ->  namespace bitstream_
namespace bitstream_ {
  // 0x0063D990  conf=0.71  ?GetCursor@bitstream@@QBEHXZ
  using GetCursor_t = int (__thiscall*)(::bitstream *);
  inline int GetCursor(::bitstream * a0) { return reinterpret_cast<GetCursor_t>(meridian::rebase(0x0063D990))(a0); }
  // 0x0063DF00  conf=0.699  ?WriteVector@bitstream@@QAEXABUvector3@@@Z
  using WriteVector_t = void (__thiscall*)(::bitstream *, ::vector3 *);
  inline void WriteVector(::bitstream * a0, ::vector3 * a1) { reinterpret_cast<WriteVector_t>(meridian::rebase(0x0063DF00))(a0, a1); }
} // bitstream_

// ===== boulder_run =====  (6 functions)  ->  namespace boulder_run_
namespace boulder_run_ {
  // 0x0045AA00  conf=0.85  ?EnumerateProperties@boulder_run@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::boulder_run *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::boulder_run * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0045AA00))(a0, a1); }
  // 0x0045A2B0  conf=0.694  ?OnAdvanceLogic@boulder_run@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::boulder_run *, float);
  inline void OnAdvanceLogic(::boulder_run * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x0045A2B0))(a0, a1); }
  // 0x0045A8D0  conf=0.85  ?OnExport@boulder_run@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::boulder_run *, ::bin_out *);
  inline void OnExport(::boulder_run * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x0045A8D0))(a0, a1); }
  // 0x0045A660  conf=0.818  ?OnImport@boulder_run@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::boulder_run *, ::bin_in *);
  inline void OnImport(::boulder_run * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0045A660))(a0, a1); }
  // 0x0045A1A0  conf=0.72  ?OnInit@boulder_run@@UAEXXZ
  using OnInit_t = void (__thiscall*)(::boulder_run *);
  inline void OnInit(::boulder_run * a0) { reinterpret_cast<OnInit_t>(meridian::rebase(0x0045A1A0))(a0); }
  // 0x0045AC70  conf=0.85  ?SetProperty@boulder_run@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::boulder_run *, char *, ::property *);
  inline int SetProperty(::boulder_run * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0045AC70))(a0, a1, a2); }
} // boulder_run_

// ===== breakaway =====  (6 functions)  ->  namespace breakaway_
namespace breakaway_ {
  // 0x0045BB90  conf=0.75  ?ActivateCollapse@breakaway@@QAEXXZ
  using ActivateCollapse_t = void (__thiscall*)(::breakaway *);
  inline void ActivateCollapse(::breakaway * a0) { reinterpret_cast<ActivateCollapse_t>(meridian::rebase(0x0045BB90))(a0); }
  // 0x0045B960  conf=0.85  ?EnumerateProperties@breakaway@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::breakaway *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::breakaway * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0045B960))(a0, a1); }
  // 0x0045B550  conf=0.732  ?OnAdvanceLogic@breakaway@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::breakaway *, float);
  inline void OnAdvanceLogic(::breakaway * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x0045B550))(a0, a1); }
  // 0x0045B8B0  conf=0.85  ?OnExport@breakaway@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::breakaway *, ::bin_out *);
  inline void OnExport(::breakaway * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x0045B8B0))(a0, a1); }
  // 0x0045B8E0  conf=0.751  ?OnImport@breakaway@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::breakaway *, ::bin_in *);
  inline void OnImport(::breakaway * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0045B8E0))(a0, a1); }
  // 0x0045B520  conf=0.735  ?OnInit@breakaway@@UAEXXZ
  using OnInit_t = void (__thiscall*)(::breakaway *);
  inline void OnInit(::breakaway * a0) { reinterpret_cast<OnInit_t>(meridian::rebase(0x0045B520))(a0); }
} // breakaway_

// ===== camera =====  (1 functions)  ->  namespace camera_
namespace camera_ {
  // 0x0045C360  conf=0.75  ?SetupView@camera@@QAEXAAVview@@@Z
  using SetupView_t = void (__thiscall*)(::camera *, ::view *);
  inline void SetupView(::camera * a0, ::view * a1) { reinterpret_cast<SetupView_t>(meridian::rebase(0x0045C360))(a0, a1); }
} // camera_

// ===== camera_influence =====  (3 functions)  ->  namespace camera_influence_
namespace camera_influence_ {
  // 0x0045DA80  conf=0.85  ?EnumerateProperties@camera_influence@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::camera_influence *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::camera_influence * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0045DA80))(a0, a1); }
  // 0x0045D610  conf=0.746  ?IsTriggered@camera_influence@@QAEH_K@Z
  using IsTriggered_t = int (__thiscall*)(::camera_influence *, __uint64);
  inline int IsTriggered(::camera_influence * a0, __uint64 a1) { return reinterpret_cast<IsTriggered_t>(meridian::rebase(0x0045D610))(a0, a1); }
  // 0x0045D350  conf=0.817  ?OnImport@camera_influence@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::camera_influence *, ::bin_in *);
  inline void OnImport(::camera_influence * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0045D350))(a0, a1); }
} // camera_influence_

// ===== camera_mgr =====  (6 functions)  ->  namespace camera_mgr_
namespace camera_mgr_ {
  // 0x00571090  conf=0.595  ?AdvanceAvoidObstruction@camera_mgr@@IAEXM@Z
  using AdvanceAvoidObstruction_t = void (__thiscall*)(::camera_mgr *, float);
  inline void AdvanceAvoidObstruction(::camera_mgr * a0, float a1) { reinterpret_cast<AdvanceAvoidObstruction_t>(meridian::rebase(0x00571090))(a0, a1); }
  // 0x00570EE0  conf=0.662  ?AdvanceStatic@camera_mgr@@IAEXM@Z
  using AdvanceStatic_t = void (__thiscall*)(::camera_mgr *, float);
  inline void AdvanceStatic(::camera_mgr * a0, float a1) { reinterpret_cast<AdvanceStatic_t>(meridian::rebase(0x00570EE0))(a0, a1); }
  // 0x005712D0  conf=0.97  ?CheckForInfluencer@camera_mgr@@IAEXXZ
  using CheckForInfluencer_t = void (__thiscall*)(::camera_mgr *);
  inline void CheckForInfluencer(::camera_mgr * a0) { reinterpret_cast<CheckForInfluencer_t>(meridian::rebase(0x005712D0))(a0); }
  // 0x005717E0  conf=0.97  ?CheckForModifier@camera_mgr@@IAEXXZ
  using CheckForModifier_t = void (__thiscall*)(::camera_mgr *);
  inline void CheckForModifier(::camera_mgr * a0) { reinterpret_cast<CheckForModifier_t>(meridian::rebase(0x005717E0))(a0); }
  // 0x0056B420  conf=0.748  ?GetProperty@camera_mgr@@QAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::camera_mgr *, char *);
  inline ::property GetProperty(::camera_mgr * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x0056B420))(a0, a1); }
  // 0x0056D5E0  conf=0.97  ?SetState@camera_mgr@@IAEHW4camera_state@1@H@Z
  inline void* SetState_at() { return meridian::rebase(0x0056D5E0); } // int __thiscall SetState(camera_mgr *, camera_state, int)
} // camera_mgr_

// ===== camera_modifier =====  (6 functions)  ->  namespace camera_modifier_
namespace camera_modifier_ {
  // 0x0045E9A0  conf=0.892  ?EnumerateProperties@camera_modifier@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::camera_modifier *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::camera_modifier * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0045E9A0))(a0, a1); }
  // 0x0045E970  conf=0.732  ?IsTriggered@camera_modifier@@QAEHXZ
  using IsTriggered_t = int (__thiscall*)(::camera_modifier *);
  inline int IsTriggered(::camera_modifier * a0) { return reinterpret_cast<IsTriggered_t>(meridian::rebase(0x0045E970))(a0); }
  // 0x0045E390  conf=0.85  ?OnExport@camera_modifier@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::camera_modifier *, ::bin_out *);
  inline void OnExport(::camera_modifier * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x0045E390))(a0, a1); }
  // 0x0045E660  conf=0.85  ?OnImport@camera_modifier@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::camera_modifier *, ::bin_in *);
  inline void OnImport(::camera_modifier * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0045E660))(a0, a1); }
  // 0x0045E370  conf=0.75  ?OnInit@camera_modifier@@UAEXXZ
  using OnInit_t = void (__thiscall*)(::camera_modifier *);
  inline void OnInit(::camera_modifier * a0) { reinterpret_cast<OnInit_t>(meridian::rebase(0x0045E370))(a0); }
  // 0x0045EF70  conf=0.802  ?SetProperty@camera_modifier@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::camera_modifier *, char *, ::property *);
  inline int SetProperty(::camera_modifier * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0045EF70))(a0, a1, a2); }
} // camera_modifier_

// ===== camera_path =====  (2 functions)  ->  namespace camera_path_
namespace camera_path_ {
  // 0x00461E90  conf=0.899  ?EnumerateProperties@camera_path@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::camera_path *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::camera_path * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00461E90))(a0, a1); }
  // 0x004978E0  conf=0.776  ?UpdateOffsetMat@camera_path@@IAEXXZ
  using UpdateOffsetMat_t = void (__thiscall*)(::camera_path *);
  inline void UpdateOffsetMat(::camera_path * a0) { reinterpret_cast<UpdateOffsetMat_t>(meridian::rebase(0x004978E0))(a0); }
} // camera_path_

// ===== catapult =====  (16 functions)  ->  namespace catapult_
namespace catapult_ {
  // 0x00411FC0  conf=0.97  ?AdvanceLogic@catapult@@QAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::catapult *, float);
  inline void AdvanceLogic(::catapult * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00411FC0))(a0, a1); }
  // 0x00412B80  conf=0.755  ?DetectLaunchEvent@catapult@@IAEHAAUvector3@@@Z
  using DetectLaunchEvent_t = int (__thiscall*)(::catapult *, ::vector3 *);
  inline int DetectLaunchEvent(::catapult * a0, ::vector3 * a1) { return reinterpret_cast<DetectLaunchEvent_t>(meridian::rebase(0x00412B80))(a0, a1); }
  // 0x00412720  conf=0.732  ?FindTargetObject@catapult@@QAE_KH@Z
  using FindTargetObject_t = __uint64 (__thiscall*)(::catapult *, int);
  inline __uint64 FindTargetObject(::catapult * a0, int a1) { return reinterpret_cast<FindTargetObject_t>(meridian::rebase(0x00412720))(a0, a1); }
  // 0x00412850  conf=0.686  ?GetCatapultYaw@catapult@@IAEMXZ
  using GetCatapultYaw_t = float (__thiscall*)(::catapult *);
  inline float GetCatapultYaw(::catapult * a0) { return reinterpret_cast<GetCatapultYaw_t>(meridian::rebase(0x00412850))(a0); }
  // 0x00412910  conf=0.675  ?GetCurrentTargetPosition@catapult@@IAE?AUvector3@@XZ
  using GetCurrentTargetPosition_t = ::vector3 (__thiscall*)(::catapult *);
  inline ::vector3 GetCurrentTargetPosition(::catapult * a0) { return reinterpret_cast<GetCurrentTargetPosition_t>(meridian::rebase(0x00412910))(a0); }
  // 0x004129F0  conf=0.7  ?GetCurrentTargetYaw@catapult@@IAEMXZ
  using GetCurrentTargetYaw_t = float (__thiscall*)(::catapult *);
  inline float GetCurrentTargetYaw(::catapult * a0) { return reinterpret_cast<GetCurrentTargetYaw_t>(meridian::rebase(0x004129F0))(a0); }
  // 0x00411EE0  conf=0.85  ?Init@catapult@@QAEX_K00000@Z
  using Init_t = void (__thiscall*)(::catapult *, __uint64, __uint64, __uint64, __uint64, __uint64, __uint64);
  inline void Init(::catapult * a0, __uint64 a1, __uint64 a2, __uint64 a3, __uint64 a4, __uint64 a5, __uint64 a6) { reinterpret_cast<Init_t>(meridian::rebase(0x00411EE0))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x00412BB0  conf=0.746  ?IsProjectileActive@catapult@@IAEHXZ
  using IsProjectileActive_t = int (__thiscall*)(::catapult *);
  inline int IsProjectileActive(::catapult * a0) { return reinterpret_cast<IsProjectileActive_t>(meridian::rebase(0x00412BB0))(a0); }
  // 0x00413200  conf=0.58  ?LockCinema@catapult@@IAEPAVcinema@@XZ
  using LockCinema_t = ::cinema * (__thiscall*)(::catapult *);
  inline ::cinema * LockCinema(::catapult * a0) { return reinterpret_cast<LockCinema_t>(meridian::rebase(0x00413200))(a0); }
  // 0x004125D0  conf=0.546  ?LockControlPanel@catapult@@IAEPAVrigid_instance@@XZ
  using LockControlPanel_t = ::rigid_instance * (__thiscall*)(::catapult *);
  inline ::rigid_instance * LockControlPanel(::catapult * a0) { return reinterpret_cast<LockControlPanel_t>(meridian::rebase(0x004125D0))(a0); }
  // 0x00413220  conf=0.719  ?LockProjectile@catapult@@IAEPAVrigid_instance@@XZ
  using LockProjectile_t = ::rigid_instance * (__thiscall*)(::catapult *);
  inline ::rigid_instance * LockProjectile(::catapult * a0) { return reinterpret_cast<LockProjectile_t>(meridian::rebase(0x00413220))(a0); }
  // 0x004131A0  conf=0.58  ?LockTrigger@catapult@@IAEPAVtrigger@@XZ
  using LockTrigger_t = ::trigger * (__thiscall*)(::catapult *);
  inline ::trigger * LockTrigger(::catapult * a0) { return reinterpret_cast<LockTrigger_t>(meridian::rebase(0x004131A0))(a0); }
  // 0x00412470  conf=0.776  ?RestoreState@catapult@@QAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::catapult *, ::bitstream *);
  inline void RestoreState(::catapult * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x00412470))(a0, a1); }
  // 0x00412AE0  conf=0.697  ?SetCatapultYaw@catapult@@IAEXM@Z
  using SetCatapultYaw_t = void (__thiscall*)(::catapult *, float);
  inline void SetCatapultYaw(::catapult * a0, float a1) { reinterpret_cast<SetCatapultYaw_t>(meridian::rebase(0x00412AE0))(a0, a1); }
  // 0x00412620  conf=0.75  ?SetTargetVolume@catapult@@QAEXH_K@Z
  using SetTargetVolume_t = void (__thiscall*)(::catapult *, int, __uint64);
  inline void SetTargetVolume(::catapult * a0, int a1, __uint64 a2) { reinterpret_cast<SetTargetVolume_t>(meridian::rebase(0x00412620))(a0, a1, a2); }
  // 0x00411DF0  conf=0.75  ??0catapult@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::catapult *);
  inline undefined ctor(::catapult * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x00411DF0))(a0); }
} // catapult_

// ===== char_anim_player =====  (2 functions)  ->  namespace char_anim_player_
namespace char_anim_player_ {
  // 0x00429030  conf=0.725  ?IsPlaying@char_anim_player@@QAEHPBDH@Z
  using IsPlaying_t = int (__thiscall*)(::char_anim_player *, char *, int);
  inline int IsPlaying(::char_anim_player * a0, char * a1, int a2) { return reinterpret_cast<IsPlaying_t>(meridian::rebase(0x00429030))(a0, a1, a2); }
  // 0x0041BA80  conf=0.704  ?SetAnimHoriz@char_anim_player@@QAEXPBDM@Z
  using SetAnimHoriz_t = void (__thiscall*)(::char_anim_player *, char *, float);
  inline void SetAnimHoriz(::char_anim_player * a0, char * a1, float a2) { reinterpret_cast<SetAnimHoriz_t>(meridian::rebase(0x0041BA80))(a0, a1, a2); }
} // char_anim_player_

// ===== cinema =====  (28 functions)  ->  namespace cinema_
namespace cinema_ {
  // 0x00472B60  conf=0.788  ?AdvanceShot@cinema@@IAEXM@Z
  using AdvanceShot_t = void (__thiscall*)(::cinema *, float);
  inline void AdvanceShot(::cinema * a0, float a1) { reinterpret_cast<AdvanceShot_t>(meridian::rebase(0x00472B60))(a0, a1); }
  // 0x0046ADD0  conf=0.737  ?EnableConversationMode@cinema@@IAEXH@Z
  using EnableConversationMode_t = void (__thiscall*)(::cinema *, int);
  inline void EnableConversationMode(::cinema * a0, int a1) { reinterpret_cast<EnableConversationMode_t>(meridian::rebase(0x0046ADD0))(a0, a1); }
  // 0x0046AA20  conf=0.766  ?End@cinema@@IAEXXZ
  using End_t = void (__thiscall*)(::cinema *);
  inline void End(::cinema * a0) { reinterpret_cast<End_t>(meridian::rebase(0x0046AA20))(a0); }
  // 0x0046D160  conf=0.97  ?EnumerateProperties@cinema@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::cinema *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::cinema * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0046D160))(a0, a1); }
  // 0x00471FF0  conf=0.97  ?EnumeratePropertiesSave@cinema@@QAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumeratePropertiesSave_t = void (__thiscall*)(::cinema *, ::xarray< ::property_desc> *);
  inline void EnumeratePropertiesSave(::cinema * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumeratePropertiesSave_t>(meridian::rebase(0x00471FF0))(a0, a1); }
  // 0x0046F5F0  conf=0.97  ?GetProperty@cinema@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::cinema *, char *);
  inline ::property GetProperty(::cinema * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x0046F5F0))(a0, a1); }
  // 0x00473C60  conf=0.744  ?GetShotDuration@cinema@@IAEMHAAH@Z
  using GetShotDuration_t = float (__thiscall*)(::cinema *, int, int *);
  inline float GetShotDuration(::cinema * a0, int a1, int * a2) { return reinterpret_cast<GetShotDuration_t>(meridian::rebase(0x00473C60))(a0, a1, a2); }
  // 0x0046ADC0  conf=0.8  ?IsFinished@cinema@@QAEHXZ
  using IsFinished_t = int (__thiscall*)(::cinema *);
  inline int IsFinished(::cinema * a0) { return reinterpret_cast<IsFinished_t>(meridian::rebase(0x0046ADC0))(a0); }
  // 0x00472F30  conf=0.75  ?IsSkippable@cinema@@QAEHXZ
  using IsSkippable_t = int (__thiscall*)(::cinema *);
  inline int IsSkippable(::cinema * a0) { return reinterpret_cast<IsSkippable_t>(meridian::rebase(0x00472F30))(a0); }
  // 0x0046A1F0  conf=0.774  ?OnAdvanceLogic@cinema@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::cinema *, float);
  inline void OnAdvanceLogic(::cinema * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x0046A1F0))(a0, a1); }
  // 0x0046BE00  conf=0.829  ?OnImport@cinema@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::cinema *, ::bin_in *);
  inline void OnImport(::cinema * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0046BE00))(a0, a1); }
  // 0x004733F0  conf=0.74  ?OnObjectDeactivate@cinema@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::cinema *);
  inline void OnObjectDeactivate(::cinema * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004733F0))(a0); }
  // 0x00471F10  conf=0.793  ?OnReset@cinema@@UAEXXZ
  using OnReset_t = void (__thiscall*)(::cinema *);
  inline void OnReset(::cinema * a0) { reinterpret_cast<OnReset_t>(meridian::rebase(0x00471F10))(a0); }
  // 0x00472B20  conf=0.79  ?ResetSyncPoint@cinema@@IAEXH@Z
  using ResetSyncPoint_t = void (__thiscall*)(::cinema *, int);
  inline void ResetSyncPoint(::cinema * a0, int a1) { reinterpret_cast<ResetSyncPoint_t>(meridian::rebase(0x00472B20))(a0, a1); }
  // 0x00473410  conf=0.723  ?RuntimeUpdateAll@cinema@@IAEXXZ
  using RuntimeUpdateAll_t = void (__thiscall*)(::cinema *);
  inline void RuntimeUpdateAll(::cinema * a0) { reinterpret_cast<RuntimeUpdateAll_t>(meridian::rebase(0x00473410))(a0); }
  // 0x0046B3B0  conf=0.835  ?SetActionCount@cinema@@IAEXHH@Z
  using SetActionCount_t = void (__thiscall*)(::cinema *, int, int);
  inline void SetActionCount(::cinema * a0, int a1, int a2) { reinterpret_cast<SetActionCount_t>(meridian::rebase(0x0046B3B0))(a0, a1, a2); }
  // 0x0046DBC0  conf=0.97  ?SetProperty@cinema@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::cinema *, char *, ::property *);
  inline int SetProperty(::cinema * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0046DBC0))(a0, a1, a2); }
  // 0x0046B050  conf=0.802  ?SetShotCount@cinema@@IAEXHH@Z
  using SetShotCount_t = void (__thiscall*)(::cinema *, int, int);
  inline void SetShotCount(::cinema * a0, int a1, int a2) { reinterpret_cast<SetShotCount_t>(meridian::rebase(0x0046B050))(a0, a1, a2); }
  // 0x0046B180  conf=0.834  ?SetSkipActionCount@cinema@@IAEXHH@Z
  using SetSkipActionCount_t = void (__thiscall*)(::cinema *, int, int);
  inline void SetSkipActionCount(::cinema * a0, int a1, int a2) { reinterpret_cast<SetSkipActionCount_t>(meridian::rebase(0x0046B180))(a0, a1, a2); }
  // 0x0046AF70  conf=0.85  ?SetSyncCount@cinema@@IAEXHH@Z
  using SetSyncCount_t = void (__thiscall*)(::cinema *, int, int);
  inline void SetSyncCount(::cinema * a0, int a1, int a2) { reinterpret_cast<SetSyncCount_t>(meridian::rebase(0x0046AF70))(a0, a1, a2); }
  // 0x0046AB10  conf=0.97  ?Shutdown@cinema@@IAEXXZ
  using Shutdown_t = void (__thiscall*)(::cinema *);
  inline void Shutdown(::cinema * a0) { reinterpret_cast<Shutdown_t>(meridian::rebase(0x0046AB10))(a0); }
  // 0x00473020  conf=0.795  ?Skip@cinema@@IAEXXZ
  using Skip_t = void (__thiscall*)(::cinema *);
  inline void Skip(::cinema * a0) { reinterpret_cast<Skip_t>(meridian::rebase(0x00473020))(a0); }
  // 0x0046A550  conf=0.727  ?Start@cinema@@QAEXXZ
  using Start_t = void (__thiscall*)(::cinema *);
  inline void Start(::cinema * a0) { reinterpret_cast<Start_t>(meridian::rebase(0x0046A550))(a0); }
  // 0x00473BB0  conf=0.744  ?UpdateCameras@cinema@@IAEXXZ
  using UpdateCameras_t = void (__thiscall*)(::cinema *);
  inline void UpdateCameras(::cinema * a0) { reinterpret_cast<UpdateCameras_t>(meridian::rebase(0x00473BB0))(a0); }
  // 0x00473B60  conf=0.75  ?UpdateShotTimes@cinema@@IAEXXZ
  using UpdateShotTimes_t = void (__thiscall*)(::cinema *);
  inline void UpdateShotTimes(::cinema * a0) { reinterpret_cast<UpdateShotTimes_t>(meridian::rebase(0x00473B60))(a0); }
  // 0x00473650  conf=0.782  ?UpdateSyncPoint@cinema@@IAEXH@Z
  using UpdateSyncPoint_t = void (__thiscall*)(::cinema *, int);
  inline void UpdateSyncPoint(::cinema * a0, int a1) { reinterpret_cast<UpdateSyncPoint_t>(meridian::rebase(0x00473650))(a0, a1); }
  // 0x00473AD0  conf=0.75  ?UpdateSyncPointsFromAction@cinema@@IAEXH@Z
  using UpdateSyncPointsFromAction_t = void (__thiscall*)(::cinema *, int);
  inline void UpdateSyncPointsFromAction(::cinema * a0, int a1) { reinterpret_cast<UpdateSyncPointsFromAction_t>(meridian::rebase(0x00473AD0))(a0, a1); }
  // 0x00469C50  conf=0.711  ??0cinema@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::cinema *);
  inline undefined ctor(::cinema * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x00469C50))(a0); }
} // cinema_

// ===== cinema_action =====  (1 functions)  ->  namespace cinema_action_
namespace cinema_action_ {
  // 0x00475120  conf=0.85  ?OnExport@cinema_action@@UAEXHAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::cinema_action *, int, ::bin_out *);
  inline void OnExport(::cinema_action * a0, int a1, ::bin_out * a2) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00475120))(a0, a1, a2); }
} // cinema_action_

// ===== cinema_anim =====  (1 functions)  ->  namespace cinema_anim_
namespace cinema_anim_ {
  // 0x0047EBB0  conf=0.85  ?OnExport@cinema_anim@@UAEXHAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::cinema_anim *, int, ::bin_out *);
  inline void OnExport(::cinema_anim * a0, int a1, ::bin_out * a2) { reinterpret_cast<OnExport_t>(meridian::rebase(0x0047EBB0))(a0, a1, a2); }
} // cinema_anim_

// ===== cinema_anim_inst =====  (1 functions)  ->  namespace cinema_anim_inst_
namespace cinema_anim_inst_ {
  // 0x00480370  conf=0.85  ?OnExport@cinema_anim_inst@@UAEXHAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::cinema_anim_inst *, int, ::bin_out *);
  inline void OnExport(::cinema_anim_inst * a0, int a1, ::bin_out * a2) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00480370))(a0, a1, a2); }
} // cinema_anim_inst_

// ===== cinema_camera =====  (2 functions)  ->  namespace cinema_camera_
namespace cinema_camera_ {
  // 0x004777C0  conf=0.97  ?EnumerateProperties@cinema_camera@@UAEXPBDAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::cinema_camera *, char *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::cinema_camera * a0, char * a1, ::xarray< ::property_desc> * a2) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004777C0))(a0, a1, a2); }
  // 0x00479C70  conf=0.85  ?OnExport@cinema_camera@@UAEXHAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::cinema_camera *, int, ::bin_out *);
  inline void OnExport(::cinema_camera * a0, int a1, ::bin_out * a2) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00479C70))(a0, a1, a2); }
} // cinema_camera_

// ===== cinema_fx =====  (1 functions)  ->  namespace cinema_fx_
namespace cinema_fx_ {
  // 0x0047A3C0  conf=0.735  ??0cinema_fx@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::cinema_fx *);
  inline undefined ctor(::cinema_fx * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0047A3C0))(a0); }
} // cinema_fx_

// ===== cinema_fxobj_trigger =====  (1 functions)  ->  namespace cinema_fxobj_trigger_
namespace cinema_fxobj_trigger_ {
  // 0x00603A70  conf=0.75  ?Execute@cinema_fxobj_trigger@@UAEXXZ
  using Execute_t = void (__thiscall*)(::cinema_fxobj_trigger *);
  inline void Execute(::cinema_fxobj_trigger * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x00603A70))(a0); }
} // cinema_fxobj_trigger_

// ===== cinema_popto =====  (1 functions)  ->  namespace cinema_popto_
namespace cinema_popto_ {
  // 0x004754F0  conf=0.773  ?Execute@cinema_popto@@UAEXXZ
  using Execute_t = void (__thiscall*)(::cinema_popto *);
  inline void Execute(::cinema_popto * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x004754F0))(a0); }
} // cinema_popto_

// ===== cinema_script =====  (1 functions)  ->  namespace cinema_script_
namespace cinema_script_ {
  // 0x00472E20  conf=0.746  ?Execute@cinema_script@@UAEXXZ
  using Execute_t = void (__thiscall*)(::cinema_script *);
  inline void Execute(::cinema_script * a0) { reinterpret_cast<Execute_t>(meridian::rebase(0x00472E20))(a0); }
} // cinema_script_

// ===== clutter_mgr =====  (2 functions)  ->  namespace clutter_mgr_
namespace clutter_mgr_ {
  // 0x005C6720  conf=0.97  ?Import@clutter_mgr@@QAEXXZ
  using Import_t = void (__thiscall*)(::clutter_mgr *);
  inline void Import(::clutter_mgr * a0) { reinterpret_cast<Import_t>(meridian::rebase(0x005C6720))(a0); }
  // 0x005C6A60  conf=0.821  ?ShowClutter@clutter_mgr@@IAEXH@Z
  using ShowClutter_t = void (__thiscall*)(::clutter_mgr *, int);
  inline void ShowClutter(::clutter_mgr * a0, int a1) { reinterpret_cast<ShowClutter_t>(meridian::rebase(0x005C6A60))(a0, a1); }
} // clutter_mgr_

// ===== collmesh =====  (1 functions)  ->  namespace collmesh_
namespace collmesh_ {
  // 0x005A5D80  conf=0.97  ?Build@collmesh@@QAEXPBUvector3@@HPBEPAD@Z
  using Build_t = void (__thiscall*)(::collmesh *, ::vector3 *, int, uchar *, char *);
  inline void Build(::collmesh * a0, ::vector3 * a1, int a2, uchar * a3, char * a4) { reinterpret_cast<Build_t>(meridian::rebase(0x005A5D80))(a0, a1, a2, a3, a4); }
} // collmesh_

// ===== dlg_BuySaleScrn =====  (1 functions)  ->  namespace dlg_BuySaleScrn_
namespace dlg_BuySaleScrn_ {
  // 0x00503720  conf=0.97  ?dlg_buy_sale_register@@YAXPAVui_manager@@@Z
  using dlg_buy_sale_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_buy_sale_register(::ui_manager * a0) { reinterpret_cast<dlg_buy_sale_register_t>(meridian::rebase(0x00503720))(a0); }
} // dlg_BuySaleScrn_

// ===== dlg_Credits =====  (2 functions)  ->  namespace dlg_Credits_
namespace dlg_Credits_ {
  // 0x00509B20  conf=0.731  ?dlg_credits_factory@@YAPAVui_win@@HPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAV1@HPAX@Z
  using dlg_credits_factory_t = ::ui_win * (__cdecl*)(int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline ::ui_win * dlg_credits_factory(int a0, ::ui_manager * a1, ::dialog_tem * a2, ::irect * a3, ::ui_win * a4, int a5, void * a6) { return reinterpret_cast<dlg_credits_factory_t>(meridian::rebase(0x00509B20))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x00509B00  conf=0.85  ?dlg_credits_register@@YAXPAVui_manager@@@Z
  using dlg_credits_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_credits_register(::ui_manager * a0) { reinterpret_cast<dlg_credits_register_t>(meridian::rebase(0x00509B00))(a0); }
} // dlg_Credits_

// ===== dlg_EndGameSum =====  (2 functions)  ->  namespace dlg_EndGameSum_
namespace dlg_EndGameSum_ {
  // 0x0050A430  conf=0.731  ?dlg_end_chapter_summary_factory@@YAPAVui_win@@HPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAV1@HPAX@Z
  using dlg_end_chapter_summary_factory_t = ::ui_win * (__cdecl*)(int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline ::ui_win * dlg_end_chapter_summary_factory(int a0, ::ui_manager * a1, ::dialog_tem * a2, ::irect * a3, ::ui_win * a4, int a5, void * a6) { return reinterpret_cast<dlg_end_chapter_summary_factory_t>(meridian::rebase(0x0050A430))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x0050A410  conf=0.97  ?dlg_end_chapter_summary_register@@YAXPAVui_manager@@@Z
  using dlg_end_chapter_summary_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_end_chapter_summary_register(::ui_manager * a0) { reinterpret_cast<dlg_end_chapter_summary_register_t>(meridian::rebase(0x0050A410))(a0); }
} // dlg_EndGameSum_

// ===== dlg_FE_LoadGame =====  (1 functions)  ->  namespace dlg_FE_LoadGame_
namespace dlg_FE_LoadGame_ {
  // 0x0050B850  conf=0.75  ?dlg_load_game_register@@YAXPAVui_manager@@@Z
  using dlg_load_game_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_load_game_register(::ui_manager * a0) { reinterpret_cast<dlg_load_game_register_t>(meridian::rebase(0x0050B850))(a0); }
} // dlg_FE_LoadGame_

// ===== dlg_FE_OPTAudio =====  (1 functions)  ->  namespace dlg_FE_OPTAudio_
namespace dlg_FE_OPTAudio_ {
  // 0x0050BE90  conf=0.75  ?dlg_FEOptAudio_register@@YAXPAVui_manager@@@Z
  using dlg_FEOptAudio_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_FEOptAudio_register(::ui_manager * a0) { reinterpret_cast<dlg_FEOptAudio_register_t>(meridian::rebase(0x0050BE90))(a0); }
} // dlg_FE_OPTAudio_

// ===== dlg_FE_OPTCamera =====  (1 functions)  ->  namespace dlg_FE_OPTCamera_
namespace dlg_FE_OPTCamera_ {
  // 0x0050D2B0  conf=0.75  ?dlg_FEOptCamera_register@@YAXPAVui_manager@@@Z
  using dlg_FEOptCamera_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_FEOptCamera_register(::ui_manager * a0) { reinterpret_cast<dlg_FEOptCamera_register_t>(meridian::rebase(0x0050D2B0))(a0); }
} // dlg_FE_OPTCamera_

// ===== dlg_FE_OPTVideo =====  (1 functions)  ->  namespace dlg_FE_OPTVideo_
namespace dlg_FE_OPTVideo_ {
  // 0x0050B480  conf=0.75  ?dlg_FEOptVideo_register@@YAXPAVui_manager@@@Z
  using dlg_FEOptVideo_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_FEOptVideo_register(::ui_manager * a0) { reinterpret_cast<dlg_FEOptVideo_register_t>(meridian::rebase(0x0050B480))(a0); }
} // dlg_FE_OPTVideo_

// ===== dlg_FE_Options =====  (1 functions)  ->  namespace dlg_FE_Options_
namespace dlg_FE_Options_ {
  // 0x0050CC90  conf=0.97  ?dlg_front_end_options_register@@YAXPAVui_manager@@@Z
  using dlg_front_end_options_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_front_end_options_register(::ui_manager * a0) { reinterpret_cast<dlg_front_end_options_register_t>(meridian::rebase(0x0050CC90))(a0); }
} // dlg_FE_Options_

// ===== dlg_Inventory =====  (1 functions)  ->  namespace dlg_Inventory_
namespace dlg_Inventory_ {
  // 0x0050E800  conf=0.85  ?dlg_pause_inventory_register@@YAXPAVui_manager@@@Z
  using dlg_pause_inventory_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_pause_inventory_register(::ui_manager * a0) { reinterpret_cast<dlg_pause_inventory_register_t>(meridian::rebase(0x0050E800))(a0); }
} // dlg_Inventory_

// ===== dlg_LevelMap =====  (4 functions)  ->  namespace dlg_LevelMap_
namespace dlg_LevelMap_ {
  // 0x00513770  conf=0.97  ?Create@dlg_LevelMap@@QAEHHPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAVui_win@@HPAX@Z
  using Create_t = int (__thiscall*)(::dlg_LevelMap *, int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline int Create(::dlg_LevelMap * a0, int a1, ::ui_manager * a2, ::dialog_tem * a3, ::irect * a4, ::ui_win * a5, int a6, void * a7) { return reinterpret_cast<Create_t>(meridian::rebase(0x00513770))(a0, a1, a2, a3, a4, a5, a6, a7); }
  // 0x00513EA0  conf=0.97  ?OnPadSelect@dlg_LevelMap@@UAEXPAVui_win@@@Z
  using OnPadSelect_t = void (__thiscall*)(::dlg_LevelMap *, ::ui_win *);
  inline void OnPadSelect(::dlg_LevelMap * a0, ::ui_win * a1) { reinterpret_cast<OnPadSelect_t>(meridian::rebase(0x00513EA0))(a0, a1); }
  // 0x00513660  conf=0.731  ?dlg_LevelMap_factory@@YAPAVui_win@@HPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAV1@HPAX@Z
  using dlg_LevelMap_factory_t = ::ui_win * (__cdecl*)(int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline ::ui_win * dlg_LevelMap_factory(int a0, ::ui_manager * a1, ::dialog_tem * a2, ::irect * a3, ::ui_win * a4, int a5, void * a6) { return reinterpret_cast<dlg_LevelMap_factory_t>(meridian::rebase(0x00513660))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x00513640  conf=0.97  ?dlg_LevelMap_register@@YAXPAVui_manager@@@Z
  using dlg_LevelMap_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_LevelMap_register(::ui_manager * a0) { reinterpret_cast<dlg_LevelMap_register_t>(meridian::rebase(0x00513640))(a0); }
} // dlg_LevelMap_

// ===== dlg_MCMessage =====  (1 functions)  ->  namespace dlg_MCMessage_
namespace dlg_MCMessage_ {
  // 0x0050B9A0  conf=0.75  ?dlg_mcmessage_register@@YAXPAVui_manager@@@Z
  using dlg_mcmessage_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_mcmessage_register(::ui_manager * a0) { reinterpret_cast<dlg_mcmessage_register_t>(meridian::rebase(0x0050B9A0))(a0); }
} // dlg_MCMessage_

// ===== dlg_MainMenu =====  (2 functions)  ->  namespace dlg_MainMenu_
namespace dlg_MainMenu_ {
  // 0x00514510  conf=0.731  ?dlg_main_menu_factory@@YAPAVui_win@@HPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAV1@HPAX@Z
  using dlg_main_menu_factory_t = ::ui_win * (__cdecl*)(int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline ::ui_win * dlg_main_menu_factory(int a0, ::ui_manager * a1, ::dialog_tem * a2, ::irect * a3, ::ui_win * a4, int a5, void * a6) { return reinterpret_cast<dlg_main_menu_factory_t>(meridian::rebase(0x00514510))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x005144F0  conf=0.97  ?dlg_main_menu_register@@YAXPAVui_manager@@@Z
  using dlg_main_menu_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_main_menu_register(::ui_manager * a0) { reinterpret_cast<dlg_main_menu_register_t>(meridian::rebase(0x005144F0))(a0); }
} // dlg_MainMenu_

// ===== dlg_Message =====  (1 functions)  ->  namespace dlg_Message_
namespace dlg_Message_ {
  // 0x00515C30  conf=0.97  ?dlg_message_register@@YAXPAVui_manager@@@Z
  using dlg_message_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_message_register(::ui_manager * a0) { reinterpret_cast<dlg_message_register_t>(meridian::rebase(0x00515C30))(a0); }
} // dlg_Message_

// ===== dlg_OptAudio =====  (1 functions)  ->  namespace dlg_OptAudio_
namespace dlg_OptAudio_ {
  // 0x005169E0  conf=0.85  ?dlg_OptAudio_register@@YAXPAVui_manager@@@Z
  using dlg_OptAudio_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_OptAudio_register(::ui_manager * a0) { reinterpret_cast<dlg_OptAudio_register_t>(meridian::rebase(0x005169E0))(a0); }
} // dlg_OptAudio_

// ===== dlg_OptCamera =====  (1 functions)  ->  namespace dlg_OptCamera_
namespace dlg_OptCamera_ {
  // 0x00517800  conf=0.85  ?dlg_OptCamera_register@@YAXPAVui_manager@@@Z
  using dlg_OptCamera_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_OptCamera_register(::ui_manager * a0) { reinterpret_cast<dlg_OptCamera_register_t>(meridian::rebase(0x00517800))(a0); }
} // dlg_OptCamera_

// ===== dlg_OptVideo =====  (1 functions)  ->  namespace dlg_OptVideo_
namespace dlg_OptVideo_ {
  // 0x0051AD90  conf=0.75  ?dlg_OptVideo_register@@YAXPAVui_manager@@@Z
  using dlg_OptVideo_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_OptVideo_register(::ui_manager * a0) { reinterpret_cast<dlg_OptVideo_register_t>(meridian::rebase(0x0051AD90))(a0); }
} // dlg_OptVideo_

// ===== dlg_PauseOpt =====  (1 functions)  ->  namespace dlg_PauseOpt_
namespace dlg_PauseOpt_ {
  // 0x00519B10  conf=0.85  ?dlg_pause_options_register@@YAXPAVui_manager@@@Z
  using dlg_pause_options_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_pause_options_register(::ui_manager * a0) { reinterpret_cast<dlg_pause_options_register_t>(meridian::rebase(0x00519B10))(a0); }
} // dlg_PauseOpt_

// ===== dlg_PauseSum =====  (1 functions)  ->  namespace dlg_PauseSum_
namespace dlg_PauseSum_ {
  // 0x00517FF0  conf=0.75  ?dlg_pause_summary_register@@YAXPAVui_manager@@@Z
  using dlg_pause_summary_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_pause_summary_register(::ui_manager * a0) { reinterpret_cast<dlg_pause_summary_register_t>(meridian::rebase(0x00517FF0))(a0); }
} // dlg_PauseSum_

// ===== dlg_PickLock =====  (1 functions)  ->  namespace dlg_PickLock_
namespace dlg_PickLock_ {
  // 0x00518780  conf=0.75  ?dlg_pickLock_register@@YAXPAVui_manager@@@Z
  using dlg_pickLock_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_pickLock_register(::ui_manager * a0) { reinterpret_cast<dlg_pickLock_register_t>(meridian::rebase(0x00518780))(a0); }
} // dlg_PickLock_

// ===== dlg_PressStart =====  (2 functions)  ->  namespace dlg_PressStart_
namespace dlg_PressStart_ {
  // 0x0051E860  conf=0.97  ?RunPressStartScreen@@YAXXZ
  using RunPressStartScreen_t = void (__cdecl*)();
  inline void RunPressStartScreen() { reinterpret_cast<RunPressStartScreen_t>(meridian::rebase(0x0051E860))(); }
  // 0x0051E730  conf=0.97  ?dlg_press_start_register@@YAXPAVui_manager@@@Z
  using dlg_press_start_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_press_start_register(::ui_manager * a0) { reinterpret_cast<dlg_press_start_register_t>(meridian::rebase(0x0051E730))(a0); }
} // dlg_PressStart_

// ===== dlg_QuestItemPopUp =====  (3 functions)  ->  namespace dlg_QuestItemPopUp_
namespace dlg_QuestItemPopUp_ {
  // 0x0051EE60  conf=0.9  ?Init@dlg_QuestItemPopUp@@QAEX_K@Z
  using Init_t = void (__thiscall*)(::dlg_QuestItemPopUp *, __uint64);
  inline void Init(::dlg_QuestItemPopUp * a0, __uint64 a1) { reinterpret_cast<Init_t>(meridian::rebase(0x0051EE60))(a0, a1); }
  // 0x0051F4D0  conf=0.97  ?Render@dlg_QuestItemPopUp@@QAEXXZ
  using Render_t = void (__thiscall*)(::dlg_QuestItemPopUp *);
  inline void Render(::dlg_QuestItemPopUp * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x0051F4D0))(a0); }
  // 0x0051EFA0  conf=0.97  ?Update@dlg_QuestItemPopUp@@QAEHXZ
  using Update_t = int (__thiscall*)(::dlg_QuestItemPopUp *);
  inline int Update(::dlg_QuestItemPopUp * a0) { return reinterpret_cast<Update_t>(meridian::rebase(0x0051EFA0))(a0); }
} // dlg_QuestItemPopUp_

// ===== dlg_QuestLog =====  (2 functions)  ->  namespace dlg_QuestLog_
namespace dlg_QuestLog_ {
  // 0x0051FF30  conf=0.728  ?dlg_pause_questlog_factory@@YAPAVui_win@@HPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAV1@HPAX@Z
  using dlg_pause_questlog_factory_t = ::ui_win * (__cdecl*)(int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline ::ui_win * dlg_pause_questlog_factory(int a0, ::ui_manager * a1, ::dialog_tem * a2, ::irect * a3, ::ui_win * a4, int a5, void * a6) { return reinterpret_cast<dlg_pause_questlog_factory_t>(meridian::rebase(0x0051FF30))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x005183B0  conf=0.75  ?dlg_pause_questlog_register@@YAXPAVui_manager@@@Z
  using dlg_pause_questlog_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_pause_questlog_register(::ui_manager * a0) { reinterpret_cast<dlg_pause_questlog_register_t>(meridian::rebase(0x005183B0))(a0); }
} // dlg_QuestLog_

// ===== dlg_SaveLoad =====  (1 functions)  ->  namespace dlg_SaveLoad_
namespace dlg_SaveLoad_ {
  // 0x005185B0  conf=0.75  ?dlg_save_load_register@@YAXPAVui_manager@@@Z
  using dlg_save_load_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_save_load_register(::ui_manager * a0) { reinterpret_cast<dlg_save_load_register_t>(meridian::rebase(0x005185B0))(a0); }
} // dlg_SaveLoad_

// ===== dlg_TextBox =====  (1 functions)  ->  namespace dlg_TextBox_
namespace dlg_TextBox_ {
  // 0x00518980  conf=0.75  ?dlg_text_box_register@@YAXPAVui_manager@@@Z
  using dlg_text_box_register_t = void (__cdecl*)(::ui_manager *);
  inline void dlg_text_box_register(::ui_manager * a0) { reinterpret_cast<dlg_text_box_register_t>(meridian::rebase(0x00518980))(a0); }
} // dlg_TextBox_

// ===== dlg_buy_sale =====  (5 functions)  ->  namespace dlg_buy_sale_
namespace dlg_buy_sale_ {
  // 0x00506650  conf=0.97  ?OnPadHelp@dlg_buy_sale@@UAEXPAVui_win@@@Z
  using OnPadHelp_t = void (__thiscall*)(::dlg_buy_sale *, ::ui_win *);
  inline void OnPadHelp(::dlg_buy_sale * a0, ::ui_win * a1) { reinterpret_cast<OnPadHelp_t>(meridian::rebase(0x00506650))(a0, a1); }
  // 0x005066C0  conf=0.97  ?OnPadSelect@dlg_buy_sale@@UAEXPAVui_win@@@Z
  using OnPadSelect_t = void (__thiscall*)(::dlg_buy_sale *, ::ui_win *);
  inline void OnPadSelect(::dlg_buy_sale * a0, ::ui_win * a1) { reinterpret_cast<OnPadSelect_t>(meridian::rebase(0x005066C0))(a0, a1); }
  // 0x00506DB0  conf=0.97  ?OnUpdate@dlg_buy_sale@@UAEXPAVui_win@@M@Z
  using OnUpdate_t = void (__thiscall*)(::dlg_buy_sale *, ::ui_win *, float);
  inline void OnUpdate(::dlg_buy_sale * a0, ::ui_win * a1, float a2) { reinterpret_cast<OnUpdate_t>(meridian::rebase(0x00506DB0))(a0, a1, a2); }
  // 0x00507E00  conf=0.9  ?OptionBox@dlg_buy_sale@@QAEXPBG0000HH@Z
  using OptionBox_t = void (__thiscall*)(::dlg_buy_sale *, ushort *, ushort *, ushort *, ushort *, ushort *, int, int);
  inline void OptionBox(::dlg_buy_sale * a0, ushort * a1, ushort * a2, ushort * a3, ushort * a4, ushort * a5, int a6, int a7) { reinterpret_cast<OptionBox_t>(meridian::rebase(0x00507E00))(a0, a1, a2, a3, a4, a5, a6, a7); }
  // 0x00504AA0  conf=0.97  ?Render@dlg_buy_sale@@UAEXHH@Z
  using Render_t = void (__thiscall*)(::dlg_buy_sale *, int, int);
  inline void Render(::dlg_buy_sale * a0, int a1, int a2) { reinterpret_cast<Render_t>(meridian::rebase(0x00504AA0))(a0, a1, a2); }
} // dlg_buy_sale_

// ===== dlg_credits =====  (1 functions)  ->  namespace dlg_credits_
namespace dlg_credits_ {
  // 0x00509BF0  conf=0.97  ?Create@dlg_credits@@QAEHHPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAVui_win@@HPAX@Z
  using Create_t = int (__thiscall*)(::dlg_credits *, int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline int Create(::dlg_credits * a0, int a1, ::ui_manager * a2, ::dialog_tem * a3, ::irect * a4, ::ui_win * a5, int a6, void * a7) { return reinterpret_cast<Create_t>(meridian::rebase(0x00509BF0))(a0, a1, a2, a3, a4, a5, a6, a7); }
} // dlg_credits_

// ===== dlg_end_chapter_summary =====  (1 functions)  ->  namespace dlg_end_chapter_summary_
namespace dlg_end_chapter_summary_ {
  // 0x0050A540  conf=0.747  ?Create@dlg_end_chapter_summary@@QAEHHPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAVui_win@@HPAX@Z
  using Create_t = int (__thiscall*)(::dlg_end_chapter_summary *, int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline int Create(::dlg_end_chapter_summary * a0, int a1, ::ui_manager * a2, ::dialog_tem * a3, ::irect * a4, ::ui_win * a5, int a6, void * a7) { return reinterpret_cast<Create_t>(meridian::rebase(0x0050A540))(a0, a1, a2, a3, a4, a5, a6, a7); }
} // dlg_end_chapter_summary_

// ===== dlg_main_menu =====  (1 functions)  ->  namespace dlg_main_menu_
namespace dlg_main_menu_ {
  // 0x00514620  conf=0.709  ?Create@dlg_main_menu@@QAEHHPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAVui_win@@HPAX@Z
  using Create_t = int (__thiscall*)(::dlg_main_menu *, int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline int Create(::dlg_main_menu * a0, int a1, ::ui_manager * a2, ::dialog_tem * a3, ::irect * a4, ::ui_win * a5, int a6, void * a7) { return reinterpret_cast<Create_t>(meridian::rebase(0x00514620))(a0, a1, a2, a3, a4, a5, a6, a7); }
} // dlg_main_menu_

// ===== dlg_message =====  (1 functions)  ->  namespace dlg_message_
namespace dlg_message_ {
  // 0x00515DB0  conf=0.749  ?Configure@dlg_message@@QAEXPBG000Uxcolor@@PAHHH@Z
  inline void* Configure_at() { return meridian::rebase(0x00515DB0); } // void __thiscall Configure(dlg_message *, ushort *, ushort *, ushort *, ushort *, xcolor, int *, int, int)
} // dlg_message_

// ===== dlg_pause_inventory =====  (3 functions)  ->  namespace dlg_pause_inventory_
namespace dlg_pause_inventory_ {
  // 0x00510FA0  conf=0.97  ?GetInfoStringBasedOnX@dlg_pause_inventory@@QAEPBGH@Z
  using GetInfoStringBasedOnX_t = ushort * (__thiscall*)(::dlg_pause_inventory *, int);
  inline ushort * GetInfoStringBasedOnX(::dlg_pause_inventory * a0, int a1) { return reinterpret_cast<GetInfoStringBasedOnX_t>(meridian::rebase(0x00510FA0))(a0, a1); }
  // 0x00511CF0  conf=0.97  ?OnUpdate@dlg_pause_inventory@@UAEXPAVui_win@@M@Z
  using OnUpdate_t = void (__thiscall*)(::dlg_pause_inventory *, ::ui_win *, float);
  inline void OnUpdate(::dlg_pause_inventory * a0, ::ui_win * a1, float a2) { reinterpret_cast<OnUpdate_t>(meridian::rebase(0x00511CF0))(a0, a1, a2); }
  // 0x0050FFF0  conf=0.97  ?Render@dlg_pause_inventory@@UAEXHH@Z
  using Render_t = void (__thiscall*)(::dlg_pause_inventory *, int, int);
  inline void Render(::dlg_pause_inventory * a0, int a1, int a2) { reinterpret_cast<Render_t>(meridian::rebase(0x0050FFF0))(a0, a1, a2); }
} // dlg_pause_inventory_

// ===== dlg_pause_questlog =====  (2 functions)  ->  namespace dlg_pause_questlog_
namespace dlg_pause_questlog_ {
  // 0x00520170  conf=0.75  ?Create@dlg_pause_questlog@@QAEHHPAVui_manager@@PAUdialog_tem@2@ABUirect@@PAVui_win@@HPAX@Z
  using Create_t = int (__thiscall*)(::dlg_pause_questlog *, int, ::ui_manager *, ::dialog_tem *, ::irect *, ::ui_win *, int, void *);
  inline int Create(::dlg_pause_questlog * a0, int a1, ::ui_manager * a2, ::dialog_tem * a3, ::irect * a4, ::ui_win * a5, int a6, void * a7) { return reinterpret_cast<Create_t>(meridian::rebase(0x00520170))(a0, a1, a2, a3, a4, a5, a6, a7); }
  // 0x005207A0  conf=0.97  ?Render@dlg_pause_questlog@@UAEXHH@Z
  using Render_t = void (__thiscall*)(::dlg_pause_questlog *, int, int);
  inline void Render(::dlg_pause_questlog * a0, int a1, int a2) { reinterpret_cast<Render_t>(meridian::rebase(0x005207A0))(a0, a1, a2); }
} // dlg_pause_questlog_

// ===== dlg_pause_summary =====  (1 functions)  ->  namespace dlg_pause_summary_
namespace dlg_pause_summary_ {
  // 0x0051B100  conf=0.9  ?Render@dlg_pause_summary@@UAEXHH@Z
  using Render_t = void (__thiscall*)(::dlg_pause_summary *, int, int);
  inline void Render(::dlg_pause_summary * a0, int a1, int a2) { reinterpret_cast<Render_t>(meridian::rebase(0x0051B100))(a0, a1, a2); }
} // dlg_pause_summary_

// ===== dlg_pickLock =====  (1 functions)  ->  namespace dlg_pickLock_
namespace dlg_pickLock_ {
  // 0x0051DBC5  conf=0.97  ?OnUpdate@dlg_pickLock@@UAEXPAVui_win@@M@Z
  using OnUpdate_t = void (__thiscall*)(::dlg_pickLock *, ::ui_win *, float);
  inline void OnUpdate(::dlg_pickLock * a0, ::ui_win * a1, float a2) { reinterpret_cast<OnUpdate_t>(meridian::rebase(0x0051DBC5))(a0, a1, a2); }
} // dlg_pickLock_

// ===== dlg_text_box =====  (1 functions)  ->  namespace dlg_text_box_
namespace dlg_text_box_ {
  // 0x00524360  conf=0.75  ?SetTextBoxString@dlg_text_box@@QAEXPBG0@Z
  using SetTextBoxString_t = void (__thiscall*)(::dlg_text_box *, ushort *, ushort *);
  inline void SetTextBoxString(::dlg_text_box * a0, ushort * a1, ushort * a2) { reinterpret_cast<SetTextBoxString_t>(meridian::rebase(0x00524360))(a0, a1, a2); }
} // dlg_text_box_

// ===== eel_colony =====  (8 functions)  ->  namespace eel_colony_
namespace eel_colony_ {
  // 0x0044F5D0  conf=0.736  ?ClearEelsArray@eel_colony@@QAEXXZ
  using ClearEelsArray_t = void (__thiscall*)(::eel_colony *);
  inline void ClearEelsArray(::eel_colony * a0) { reinterpret_cast<ClearEelsArray_t>(meridian::rebase(0x0044F5D0))(a0); }
  // 0x00450040  conf=0.777  ?CountActive@eel_colony@@QAEHXZ
  using CountActive_t = int (__thiscall*)(::eel_colony *);
  inline int CountActive(::eel_colony * a0) { return reinterpret_cast<CountActive_t>(meridian::rebase(0x00450040))(a0); }
  // 0x0044F290  conf=0.716  ?GetNClosestHoles@eel_colony@@QAEHABUvector3@@MH@Z
  using GetNClosestHoles_t = int (__thiscall*)(::eel_colony *, ::vector3 *, float, int);
  inline int GetNClosestHoles(::eel_colony * a0, ::vector3 * a1, float a2, int a3) { return reinterpret_cast<GetNClosestHoles_t>(meridian::rebase(0x0044F290))(a0, a1, a2, a3); }
  // 0x0044F7E0  conf=0.766  ?OnAdvanceLogic@eel_colony@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::eel_colony *, float);
  inline void OnAdvanceLogic(::eel_colony * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x0044F7E0))(a0, a1); }
  // 0x0044FC90  conf=0.97  ?OnImport@eel_colony@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::eel_colony *, ::bin_in *);
  inline void OnImport(::eel_colony * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0044FC90))(a0, a1); }
  // 0x00450430  conf=0.779  ?ResetAll@eel_colony@@QAEXXZ
  using ResetAll_t = void (__thiscall*)(::eel_colony *);
  inline void ResetAll(::eel_colony * a0) { reinterpret_cast<ResetAll_t>(meridian::rebase(0x00450430))(a0); }
  // 0x004500C0  conf=0.762  ?SortGuidsByDist@eel_colony@@IAEXAAV?$xarray@_K@@ABV2@ABUvector3@@H@Z
  using SortGuidsByDist_t = void (__thiscall*)(::eel_colony *, ::xarray< ::unsigned___int64> *, ::xarray< ::unsigned___int64> *, ::vector3 *, int);
  inline void SortGuidsByDist(::eel_colony * a0, ::xarray< ::unsigned___int64> * a1, ::xarray< ::unsigned___int64> * a2, ::vector3 * a3, int a4) { reinterpret_cast<SortGuidsByDist_t>(meridian::rebase(0x004500C0))(a0, a1, a2, a3, a4); }
  // 0x004F9160  conf=0.746  ??0eel_colony@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::eel_colony *);
  inline undefined ctor(::eel_colony * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004F9160))(a0); }
} // eel_colony_

// ===== eel_hole =====  (4 functions)  ->  namespace eel_hole_
namespace eel_hole_ {
  // 0x00452690  conf=0.97  ?EnumerateProperties@eel_hole@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::eel_hole *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::eel_hole * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00452690))(a0, a1); }
  // 0x00452680  conf=0.75  ?GetParentColony@eel_hole@@QAEAB_KXZ
  using GetParentColony_t = __uint64 * (__thiscall*)(::eel_hole *);
  inline __uint64 * GetParentColony(::eel_hole * a0) { return reinterpret_cast<GetParentColony_t>(meridian::rebase(0x00452680))(a0); }
  // 0x00452080  conf=0.742  ?Init@eel_hole@@QAEXABUvector3@@ABUradian3@@ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::eel_hole *, ::vector3 *, ::radian3 *, ::bbox *);
  inline void Init(::eel_hole * a0, ::vector3 * a1, ::radian3 * a2, ::bbox * a3) { reinterpret_cast<Init_t>(meridian::rebase(0x00452080))(a0, a1, a2, a3); }
  // 0x00452550  conf=0.75  ?OnExport@eel_hole@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::eel_hole *, ::bin_out *);
  inline void OnExport(::eel_hole * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00452550))(a0, a1); }
} // eel_hole_

// ===== event_mgr =====  (5 functions)  ->  namespace event_mgr_
namespace event_mgr_ {
  // 0x00572CE0  conf=0.698  ?ApplyPainFromTable@event_mgr@@QAEXH_KUvector3@@MIH@Z
  using ApplyPainFromTable_t = void (__thiscall*)(::event_mgr *, int, __uint64, ::vector3, float, uint, int);
  inline void ApplyPainFromTable(::event_mgr * a0, int a1, __uint64 a2, ::vector3 a3, float a4, uint a5, int a6) { reinterpret_cast<ApplyPainFromTable_t>(meridian::rebase(0x00572CE0))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x00573ED0  conf=0.97  ?HandleContactAudioEvent@event_mgr@@AAEXABUanim_event@@ABUvector3@@_K@Z
  using HandleContactAudioEvent_t = void (__thiscall*)(::event_mgr *, ::anim_event *, ::vector3 *, __uint64);
  inline void HandleContactAudioEvent(::event_mgr * a0, ::anim_event * a1, ::vector3 * a2, __uint64 a3) { reinterpret_cast<HandleContactAudioEvent_t>(meridian::rebase(0x00573ED0))(a0, a1, a2, a3); }
  // 0x005734C0  conf=0.97  ?HandleEffectsEvent@event_mgr@@AAEXAAUanim_event@@_KABUvector3@@ABUradian3@@H@Z
  using HandleEffectsEvent_t = void (__thiscall*)(::event_mgr *, ::anim_event *, __uint64, ::vector3 *, ::radian3 *, int);
  inline void HandleEffectsEvent(::event_mgr * a0, ::anim_event * a1, __uint64 a2, ::vector3 * a3, ::radian3 * a4, int a5) { reinterpret_cast<HandleEffectsEvent_t>(meridian::rebase(0x005734C0))(a0, a1, a2, a3, a4, a5); }
  // 0x00574C00  conf=0.97  ?HandlePainEvent@event_mgr@@AAEXABUanim_event@@ABUvector3@@_K@Z
  using HandlePainEvent_t = void (__thiscall*)(::event_mgr *, ::anim_event *, ::vector3 *, __uint64);
  inline void HandlePainEvent(::event_mgr * a0, ::anim_event * a1, ::vector3 * a2, __uint64 a3) { reinterpret_cast<HandlePainEvent_t>(meridian::rebase(0x00574C00))(a0, a1, a2, a3); }
  // 0x00571F10  conf=0.97  ?Init@event_mgr@@QAEXXZ
  using Init_t = void (__thiscall*)(::event_mgr *);
  inline void Init(::event_mgr * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x00571F10))(a0); }
} // event_mgr_

// ===== fog_plane =====  (3 functions)  ->  namespace fog_plane_
namespace fog_plane_ {
  // 0x00483400  conf=0.97  ?EnumerateProperties@fog_plane@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::fog_plane *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::fog_plane * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00483400))(a0, a1); }
  // 0x00481B90  conf=0.85  ?OnExport@fog_plane@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::fog_plane *, ::bin_out *);
  inline void OnExport(::fog_plane * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00481B90))(a0, a1); }
  // 0x00481F90  conf=0.85  ?OnImport@fog_plane@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::fog_plane *, ::bin_in *);
  inline void OnImport(::fog_plane * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00481F90))(a0, a1); }
} // fog_plane_

// ===== fog_volume =====  (8 functions)  ->  namespace fog_volume_
namespace fog_volume_ {
  // 0x004851F0  conf=0.58  ?Displace@fog_volume@@QAEXABUvector3@@0@Z
  using Displace_t = void (__thiscall*)(::fog_volume *, ::vector3 *, ::vector3 *);
  inline void Displace(::fog_volume * a0, ::vector3 * a1, ::vector3 * a2) { reinterpret_cast<Displace_t>(meridian::rebase(0x004851F0))(a0, a1, a2); }
  // 0x004865E0  conf=0.97  ?EnumerateProperties@fog_volume@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::fog_volume *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::fog_volume * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004865E0))(a0, a1); }
  // 0x004862E0  conf=0.85  ?OnImport@fog_volume@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::fog_volume *, ::bin_in *);
  inline void OnImport(::fog_volume * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004862E0))(a0, a1); }
  // 0x004E9D90  conf=0.75  ?OnObjectActivate@fog_volume@@UAEXXZ
  using OnObjectActivate_t = void (__thiscall*)(::fog_volume *);
  inline void OnObjectActivate(::fog_volume * a0) { reinterpret_cast<OnObjectActivate_t>(meridian::rebase(0x004E9D90))(a0); }
  // 0x00486560  conf=0.75  ?OnObjectDeactivate@fog_volume@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::fog_volume *);
  inline void OnObjectDeactivate(::fog_volume * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x00486560))(a0); }
  // 0x00485840  conf=0.774  ?RebuildCells@fog_volume@@IAEXXZ
  using RebuildCells_t = void (__thiscall*)(::fog_volume *);
  inline void RebuildCells(::fog_volume * a0) { reinterpret_cast<RebuildCells_t>(meridian::rebase(0x00485840))(a0); }
  // 0x00485FA0  conf=0.794  ?RebuildParticles@fog_volume@@IAEXXZ
  using RebuildParticles_t = void (__thiscall*)(::fog_volume *);
  inline void RebuildParticles(::fog_volume * a0) { reinterpret_cast<RebuildParticles_t>(meridian::rebase(0x00485FA0))(a0); }
  // 0x00487170  conf=0.85  ?SetProperty@fog_volume@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::fog_volume *, char *, ::property *);
  inline int SetProperty(::fog_volume * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00487170))(a0, a1, a2); }
} // fog_volume_

// ===== forge_puzzle =====  (12 functions)  ->  namespace forge_puzzle_
namespace forge_puzzle_ {
  // 0x0040AAA0  conf=0.95  ?AdvanceLogic@forge_puzzle@@QAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::forge_puzzle *, float);
  inline void AdvanceLogic(::forge_puzzle * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x0040AAA0))(a0, a1); }
  // 0x0040AFD0  conf=0.783  ?GetCartStatus@forge_puzzle@@IAE?AW4cart_status@1@XZ
  inline void* GetCartStatus_at() { return meridian::rebase(0x0040AFD0); } // cart_status __thiscall GetCartStatus(forge_puzzle *)
  // 0x0040A810  conf=0.97  ?Init@forge_puzzle@@QAEXPAVlonely_mountain_fx@@@Z
  using Init_t = void (__thiscall*)(::forge_puzzle *, ::lonely_mountain_fx *);
  inline void Init(::forge_puzzle * a0, ::lonely_mountain_fx * a1) { reinterpret_cast<Init_t>(meridian::rebase(0x0040A810))(a0, a1); }
  // 0x0040ADB0  conf=0.97  ?OnActivate@forge_puzzle@@IAEXXZ
  using OnActivate_t = void (__thiscall*)(::forge_puzzle *);
  inline void OnActivate(::forge_puzzle * a0) { reinterpret_cast<OnActivate_t>(meridian::rebase(0x0040ADB0))(a0); }
  // 0x0040AF40  conf=0.786  ?OnComplete@forge_puzzle@@IAEXXZ
  using OnComplete_t = void (__thiscall*)(::forge_puzzle *);
  inline void OnComplete(::forge_puzzle * a0) { reinterpret_cast<OnComplete_t>(meridian::rebase(0x0040AF40))(a0); }
  // 0x0040AEA0  conf=0.97  ?OnEnterFire@forge_puzzle@@IAEXXZ
  using OnEnterFire_t = void (__thiscall*)(::forge_puzzle *);
  inline void OnEnterFire(::forge_puzzle * a0) { reinterpret_cast<OnEnterFire_t>(meridian::rebase(0x0040AEA0))(a0); }
  // 0x0040AEF0  conf=0.97  ?OnEnterWater@forge_puzzle@@IAEXXZ
  using OnEnterWater_t = void (__thiscall*)(::forge_puzzle *);
  inline void OnEnterWater(::forge_puzzle * a0) { reinterpret_cast<OnEnterWater_t>(meridian::rebase(0x0040AEF0))(a0); }
  // 0x0040B4D0  conf=0.75  ?RestoreState@forge_puzzle@@QAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::forge_puzzle *, ::bitstream *);
  inline void RestoreState(::forge_puzzle * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x0040B4D0))(a0, a1); }
  // 0x0040B470  conf=0.75  ?SaveState@forge_puzzle@@QAEXAAVbitstream@@@Z
  using SaveState_t = void (__thiscall*)(::forge_puzzle *, ::bitstream *);
  inline void SaveState(::forge_puzzle * a0, ::bitstream * a1) { reinterpret_cast<SaveState_t>(meridian::rebase(0x0040B470))(a0, a1); }
  // 0x0040AD50  conf=0.8  ?SetBellowsActive@forge_puzzle@@QAEXH@Z
  using SetBellowsActive_t = void (__thiscall*)(::forge_puzzle *, int);
  inline void SetBellowsActive(::forge_puzzle * a0, int a1) { reinterpret_cast<SetBellowsActive_t>(meridian::rebase(0x0040AD50))(a0, a1); }
  // 0x0040AD70  conf=0.8  ?SetWaterActive@forge_puzzle@@QAEXH@Z
  using SetWaterActive_t = void (__thiscall*)(::forge_puzzle *, int);
  inline void SetWaterActive(::forge_puzzle * a0, int a1) { reinterpret_cast<SetWaterActive_t>(meridian::rebase(0x0040AD70))(a0, a1); }
  // 0x0040B050  conf=0.97  ?UpdateForgeState@forge_puzzle@@IAEXXZ
  using UpdateForgeState_t = void (__thiscall*)(::forge_puzzle *);
  inline void UpdateForgeState(::forge_puzzle * a0) { reinterpret_cast<UpdateForgeState_t>(meridian::rebase(0x0040B050))(a0); }
} // forge_puzzle_

// ===== fx_object =====  (7 functions)  ->  namespace fx_object_
namespace fx_object_ {
  // 0x0048B750  conf=0.687  ?Init@fx_object@@QAEXPBD@Z
  using Init_t = void (__thiscall*)(::fx_object *, char *);
  inline void Init(::fx_object * a0, char * a1) { reinterpret_cast<Init_t>(meridian::rebase(0x0048B750))(a0, a1); }
  // 0x00489850  conf=0.749  ?OnImport@fx_object@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::fx_object *, ::bin_in *);
  inline void OnImport(::fx_object * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00489850))(a0, a1); }
  // 0x0048B6F0  conf=0.75  ?OnObjectDeactivate@fx_object@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::fx_object *);
  inline void OnObjectDeactivate(::fx_object * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x0048B6F0))(a0); }
  // 0x00489D80  conf=0.97  ?SetProperty@fx_object@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::fx_object *, char *, ::property *);
  inline int SetProperty(::fx_object * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00489D80))(a0, a1, a2); }
  // 0x0048A700  conf=0.75  ?StopThenDie@fx_object@@UAEXXZ
  using StopThenDie_t = void (__thiscall*)(::fx_object *);
  inline void StopThenDie(::fx_object * a0) { reinterpret_cast<StopThenDie_t>(meridian::rebase(0x0048A700))(a0); }
  // 0x0048A740  conf=0.8  ?Suspend@fx_object@@QAEXXZ
  using Suspend_t = void (__thiscall*)(::fx_object *);
  inline void Suspend(::fx_object * a0) { reinterpret_cast<Suspend_t>(meridian::rebase(0x0048A740))(a0); }
  // 0x004888D0  conf=0.755  ??0fx_object@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::fx_object *);
  inline undefined ctor(::fx_object * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004888D0))(a0); }
} // fx_object_

// ===== geom =====  (1 functions)  ->  namespace geom_
namespace geom_ {
  // 0x005C0600  conf=0.95  ??0geom@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::geom *);
  inline undefined ctor(::geom * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x005C0600))(a0); }
} // geom_

// ===== globals =====  (6 functions)  ->  namespace globals_
namespace globals_ {
  // 0x0048D4A0  conf=0.97  ?GetProperty@globals@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::globals *, char *);
  inline ::property GetProperty(::globals * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x0048D4A0))(a0, a1); }
  // 0x0048BF50  conf=0.97  ?Init@globals@@QAEXXZ
  using Init_t = void (__thiscall*)(::globals *);
  inline void Init(::globals * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x0048BF50))(a0); }
  // 0x0048C0A0  conf=0.97  ?OnImport@globals@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::globals *, ::bin_in *);
  inline void OnImport(::globals * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0048C0A0))(a0, a1); }
  // 0x0048BFF0  conf=0.75  ?OnInit@globals@@UAEXXZ
  using OnInit_t = void (__thiscall*)(::globals *);
  inline void OnInit(::globals * a0) { reinterpret_cast<OnInit_t>(meridian::rebase(0x0048BFF0))(a0); }
  // 0x0048C690  conf=0.97  ?SetProperty@globals@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::globals *, char *, ::property *);
  inline int SetProperty(::globals * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0048C690))(a0, a1, a2); }
  // 0x0048BD40  conf=0.75  ??0globals@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::globals *);
  inline undefined ctor(::globals * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0048BD40))(a0); }
} // globals_

// ===== hud =====  (35 functions)  ->  namespace hud_
namespace hud_ {
  // 0x004F7A00  conf=0.786  ?AdvanceRIPool@hud@@QAEXXZ
  using AdvanceRIPool_t = void (__thiscall*)(::hud *);
  inline void AdvanceRIPool(::hud * a0) { reinterpret_cast<AdvanceRIPool_t>(meridian::rebase(0x004F7A00))(a0); }
  // 0x004F8FB0  conf=0.97  ?BlackOutScreen@hud@@QAEXXZ
  using BlackOutScreen_t = void (__thiscall*)(::hud *);
  inline void BlackOutScreen(::hud * a0) { reinterpret_cast<BlackOutScreen_t>(meridian::rebase(0x004F8FB0))(a0); }
  // 0x004F2290  conf=0.677  ?Init@hud@@QAEHXZ
  using Init_t = int (__thiscall*)(::hud *);
  inline int Init(::hud * a0) { return reinterpret_cast<Init_t>(meridian::rebase(0x004F2290))(a0); }
  // 0x004F6EB0  conf=0.97  ?InitHudRIPool@hud@@QAEXXZ
  using InitHudRIPool_t = void (__thiscall*)(::hud *);
  inline void InitHudRIPool(::hud * a0) { reinterpret_cast<InitHudRIPool_t>(meridian::rebase(0x004F6EB0))(a0); }
  // 0x004F32F0  conf=0.786  ?Render@hud@@QAEXXZ
  using Render_t = void (__thiscall*)(::hud *);
  inline void Render(::hud * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x004F32F0))(a0); }
  // 0x004F4E90  conf=0.582  ?RenderAwarenessMeter@hud@@IAEXXZ
  using RenderAwarenessMeter_t = void (__thiscall*)(::hud *);
  inline void RenderAwarenessMeter(::hud * a0) { reinterpret_cast<RenderAwarenessMeter_t>(meridian::rebase(0x004F4E90))(a0); }
  // 0x004F60B0  conf=0.673  ?RenderCPBar@hud@@QAEXUvector2@@H@Z
  using RenderCPBar_t = void (__thiscall*)(::hud *, ::vector2, int);
  inline void RenderCPBar(::hud * a0, ::vector2 a1, int a2) { reinterpret_cast<RenderCPBar_t>(meridian::rebase(0x004F60B0))(a0, a1, a2); }
  // 0x004F3F90  conf=0.759  ?RenderChargeMeter@hud@@QAEXXZ
  using RenderChargeMeter_t = void (__thiscall*)(::hud *);
  inline void RenderChargeMeter(::hud * a0) { reinterpret_cast<RenderChargeMeter_t>(meridian::rebase(0x004F3F90))(a0); }
  // 0x004F4990  conf=0.685  ?RenderCustomNPCHealthMeter@hud@@IAEXXZ
  using RenderCustomNPCHealthMeter_t = void (__thiscall*)(::hud *);
  inline void RenderCustomNPCHealthMeter(::hud * a0) { reinterpret_cast<RenderCustomNPCHealthMeter_t>(meridian::rebase(0x004F4990))(a0); }
  // 0x004F85C0  conf=0.597  ?RenderFadeout@hud@@QAEXXZ
  using RenderFadeout_t = void (__thiscall*)(::hud *);
  inline void RenderFadeout(::hud * a0) { reinterpret_cast<RenderFadeout_t>(meridian::rebase(0x004F85C0))(a0); }
  // 0x004F2B00  conf=0.68  ?RenderFullscreenRingHalo@hud@@IAEXXZ
  using RenderFullscreenRingHalo_t = void (__thiscall*)(::hud *);
  inline void RenderFullscreenRingHalo(::hud * a0) { reinterpret_cast<RenderFullscreenRingHalo_t>(meridian::rebase(0x004F2B00))(a0); }
  // 0x004F83A0  conf=0.695  ?RenderLetterbox@hud@@QAEXXZ
  using RenderLetterbox_t = void (__thiscall*)(::hud *);
  inline void RenderLetterbox(::hud * a0) { reinterpret_cast<RenderLetterbox_t>(meridian::rebase(0x004F83A0))(a0); }
  // 0x004F34E0  conf=0.704  ?RenderPotions@hud@@QAEXXZ
  using RenderPotions_t = void (__thiscall*)(::hud *);
  inline void RenderPotions(::hud * a0) { reinterpret_cast<RenderPotions_t>(meridian::rebase(0x004F34E0))(a0); }
  // 0x004F3AC0  conf=0.678  ?RenderRing@hud@@QAEXXZ
  using RenderRing_t = void (__thiscall*)(::hud *);
  inline void RenderRing(::hud * a0) { reinterpret_cast<RenderRing_t>(meridian::rebase(0x004F3AC0))(a0); }
  // 0x004F2E00  conf=0.699  ?RenderRingEffects@hud@@IAEXXZ
  using RenderRingEffects_t = void (__thiscall*)(::hud *);
  inline void RenderRingEffects(::hud * a0) { reinterpret_cast<RenderRingEffects_t>(meridian::rebase(0x004F2E00))(a0); }
  // 0x004F28E0  conf=0.95  ?RenderRocks@hud@@QAEXXZ
  using RenderRocks_t = void (__thiscall*)(::hud *);
  inline void RenderRocks(::hud * a0) { reinterpret_cast<RenderRocks_t>(meridian::rebase(0x004F28E0))(a0); }
  // 0x004F8EC0  conf=0.733  ?RenderScreenColorizer@hud@@QAEXUxcolor@@@Z
  inline void* RenderScreenColorizer_at() { return meridian::rebase(0x004F8EC0); } // void __thiscall RenderScreenColorizer(hud *, xcolor)
  // 0x004F9070  conf=0.741  ?RenderSkipControl@hud@@QAEXXZ
  using RenderSkipControl_t = void (__thiscall*)(::hud *);
  inline void RenderSkipControl(::hud * a0) { reinterpret_cast<RenderSkipControl_t>(meridian::rebase(0x004F9070))(a0); }
  // 0x004F58F0  conf=0.77  ?RenderSmallHealthBar@hud@@QAEXH@Z
  using RenderSmallHealthBar_t = void (__thiscall*)(::hud *, int);
  inline void RenderSmallHealthBar(::hud * a0, int a1) { reinterpret_cast<RenderSmallHealthBar_t>(meridian::rebase(0x004F58F0))(a0, a1); }
  // 0x004F7E10  conf=0.784  ?RenderTarget@hud@@QAEXABUvector3@@MH_K@Z
  using RenderTarget_t = void (__thiscall*)(::hud *, ::vector3 *, float, int, __uint64);
  inline void RenderTarget(::hud * a0, ::vector3 * a1, float a2, int a3, __uint64 a4) { reinterpret_cast<RenderTarget_t>(meridian::rebase(0x004F7E10))(a0, a1, a2, a3, a4); }
  // 0x004F34C0  conf=0.75  ?RenderTopHalfOfHud@hud@@QAEXXZ
  using RenderTopHalfOfHud_t = void (__thiscall*)(::hud *);
  inline void RenderTopHalfOfHud(::hud * a0) { reinterpret_cast<RenderTopHalfOfHud_t>(meridian::rebase(0x004F34C0))(a0); }
  // 0x004F42C0  conf=0.707  ?RenderTrollMeter@hud@@IAEXXZ
  using RenderTrollMeter_t = void (__thiscall*)(::hud *);
  inline void RenderTrollMeter(::hud * a0) { reinterpret_cast<RenderTrollMeter_t>(meridian::rebase(0x004F42C0))(a0); }
  // 0x004F7610  conf=0.684  ?RenderUseIcon@hud@@QAEXABUvector3@@_K@Z
  using RenderUseIcon_t = void (__thiscall*)(::hud *, ::vector3 *, __uint64);
  inline void RenderUseIcon(::hud * a0, ::vector3 * a1, __uint64 a2) { reinterpret_cast<RenderUseIcon_t>(meridian::rebase(0x004F7610))(a0, a1, a2); }
  // 0x004F86E0  conf=0.747  ?RenderWipe@hud@@QAEXXZ
  using RenderWipe_t = void (__thiscall*)(::hud *);
  inline void RenderWipe(::hud * a0) { reinterpret_cast<RenderWipe_t>(meridian::rebase(0x004F86E0))(a0); }
  // 0x004F2440  conf=0.796  ?ResetHudVars@hud@@QAEXXZ
  using ResetHudVars_t = void (__thiscall*)(::hud *);
  inline void ResetHudVars(::hud * a0) { reinterpret_cast<ResetHudVars_t>(meridian::rebase(0x004F2440))(a0); }
  // 0x004F8A30  conf=0.75  ?SetAwarenessMeter@hud@@QAEXH@Z
  using SetAwarenessMeter_t = void (__thiscall*)(::hud *, int);
  inline void SetAwarenessMeter(::hud * a0, int a1) { reinterpret_cast<SetAwarenessMeter_t>(meridian::rebase(0x004F8A30))(a0, a1); }
  // 0x004F42B0  conf=0.75  ?SetBlinkRing@hud@@QAEXM@Z
  using SetBlinkRing_t = void (__thiscall*)(::hud *, float);
  inline void SetBlinkRing(::hud * a0, float a1) { reinterpret_cast<SetBlinkRing_t>(meridian::rebase(0x004F42B0))(a0, a1); }
  // 0x004F8A50  conf=0.8  ?SetCustomNPCHealthMeter@hud@@QAEXHHH@Z
  using SetCustomNPCHealthMeter_t = void (__thiscall*)(::hud *, int, int, int);
  inline void SetCustomNPCHealthMeter(::hud * a0, int a1, int a2, int a3) { reinterpret_cast<SetCustomNPCHealthMeter_t>(meridian::rebase(0x004F8A50))(a0, a1, a2, a3); }
  // 0x004F8520  conf=0.693  ?SetFadeout@hud@@QAEXHUxcolor@@M@Z
  inline void* SetFadeout_at() { return meridian::rebase(0x004F8520); } // void __thiscall SetFadeout(hud *, int, xcolor, float)
  // 0x004F8640  conf=0.788  ?SetWipeout@hud@@QAEXMMUxcolor@@@Z
  inline void* SetWipeout_at() { return meridian::rebase(0x004F8640); } // void __thiscall SetWipeout(hud *, float, float, xcolor)
  // 0x004DE520  conf=0.736  ?UnloadHudRIPool@hud@@QAEXXZ
  using UnloadHudRIPool_t = void (__thiscall*)(::hud *);
  inline void UnloadHudRIPool(::hud * a0) { reinterpret_cast<UnloadHudRIPool_t>(meridian::rebase(0x004DE520))(a0); }
  // 0x0058EB00  conf=0.75  ?UnloadMeters@hud@@QAEXXZ
  using UnloadMeters_t = void (__thiscall*)(::hud *);
  inline void UnloadMeters(::hud * a0) { reinterpret_cast<UnloadMeters_t>(meridian::rebase(0x0058EB00))(a0); }
  // 0x004F5340  conf=0.721  ?Update@hud@@IAEXXZ
  using Update_t = void (__thiscall*)(::hud *);
  inline void Update(::hud * a0) { reinterpret_cast<Update_t>(meridian::rebase(0x004F5340))(a0); }
  // 0x004F50E0  conf=0.97  ?UpdateBilboHealth@hud@@IAEXXZ
  using UpdateBilboHealth_t = void (__thiscall*)(::hud *);
  inline void UpdateBilboHealth(::hud * a0) { reinterpret_cast<UpdateBilboHealth_t>(meridian::rebase(0x004F50E0))(a0); }
  // 0x004F8DC0  conf=0.673  ?UpdateQuestTimer@hud@@QAEXM@Z
  using UpdateQuestTimer_t = void (__thiscall*)(::hud *, float);
  inline void UpdateQuestTimer(::hud * a0, float a1) { reinterpret_cast<UpdateQuestTimer_t>(meridian::rebase(0x004F8DC0))(a0, a1); }
} // hud_

// ===== info_overlay =====  (4 functions)  ->  namespace info_overlay_
namespace info_overlay_ {
  // 0x005577E0  conf=0.8  ?CloseInfoBox@info_overlay@@QAEXXZ
  using CloseInfoBox_t = void (__thiscall*)(::info_overlay *);
  inline void CloseInfoBox(::info_overlay * a0) { reinterpret_cast<CloseInfoBox_t>(meridian::rebase(0x005577E0))(a0); }
  // 0x00435990  conf=0.75  ?GetStringIDNames@info_overlay@@QAEPAV?$xarray@Vxstring@@@@XZ
  using GetStringIDNames_t = ::xarray< ::xstring> * (__thiscall*)(::info_overlay *);
  inline ::xarray< ::xstring> * GetStringIDNames(::info_overlay * a0) { return reinterpret_cast<GetStringIDNames_t>(meridian::rebase(0x00435990))(a0); }
  // 0x00526640  conf=0.97  ?InfoBox@info_overlay@@QAEXPBDPBGH@Z
  using InfoBox_t = void (__thiscall*)(::info_overlay *, char *, ushort *, int);
  inline void InfoBox(::info_overlay * a0, char * a1, ushort * a2, int a3) { reinterpret_cast<InfoBox_t>(meridian::rebase(0x00526640))(a0, a1, a2, a3); }
  // 0x00525E20  conf=0.97  ?init@info_overlay@@QAEXXZ
  using init_t = void (__thiscall*)(::info_overlay *);
  inline void init(::info_overlay * a0) { reinterpret_cast<init_t>(meridian::rebase(0x00525E20))(a0); }
} // info_overlay_

// ===== internal =====  (12 functions)  ->  namespace internal_
namespace internal_ {
  // 0x004911B0  conf=0.78  ?CheckForBilbo@internal@@IAEHXZ
  using CheckForBilbo_t = int (__thiscall*)(::internal *);
  inline int CheckForBilbo(::internal * a0) { return reinterpret_cast<CheckForBilbo_t>(meridian::rebase(0x004911B0))(a0); }
  // 0x00491B00  conf=0.9  ?EnumerateProperties@internal@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::internal *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::internal * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00491B00))(a0, a1); }
  // 0x00491AD0  conf=0.8  ?GetLastMovement@internal@@QAE?AUvector3@@XZ
  using GetLastMovement_t = ::vector3 (__thiscall*)(::internal *);
  inline ::vector3 GetLastMovement(::internal * a0) { return reinterpret_cast<GetLastMovement_t>(meridian::rebase(0x00491AD0))(a0); }
  // 0x0048E930  conf=0.708  ?Init@internal@@QAEXABUvector3@@ABUquaternion@@0ABUbbox@@MM00HMMH@Z
  using Init_t = void (__thiscall*)(::internal *, ::vector3 *, ::quaternion *, ::vector3 *, ::bbox *, float, float, ::vector3 *, ::vector3 *, int, float, float, int);
  inline void Init(::internal * a0, ::vector3 * a1, ::quaternion * a2, ::vector3 * a3, ::bbox * a4, float a5, float a6, ::vector3 * a7, ::vector3 * a8, int a9, float a10, float a11, int a12) { reinterpret_cast<Init_t>(meridian::rebase(0x0048E930))(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); }
  // 0x0048EDE0  conf=0.97  ?OnAdvanceLogic@internal@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::internal *, float);
  inline void OnAdvanceLogic(::internal * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x0048EDE0))(a0, a1); }
  // 0x00490DB0  conf=0.9  ?OnExport@internal@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::internal *, ::bin_out *);
  inline void OnExport(::internal * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00490DB0))(a0, a1); }
  // 0x00490960  conf=0.833  ?OnImport@internal@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::internal *, ::bin_in *);
  inline void OnImport(::internal * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00490960))(a0, a1); }
  // 0x004917C0  conf=0.97  ?State_Advance@internal@@AAEXXZ
  using State_Advance_t = void (__thiscall*)(::internal *);
  inline void State_Advance(::internal * a0) { reinterpret_cast<State_Advance_t>(meridian::rebase(0x004917C0))(a0); }
  // 0x00491490  conf=0.745  ?State_Advance_SUNKEN@internal@@AAEXXZ
  using State_Advance_SUNKEN_t = void (__thiscall*)(::internal *);
  inline void State_Advance_SUNKEN(::internal * a0) { reinterpret_cast<State_Advance_SUNKEN_t>(meridian::rebase(0x00491490))(a0); }
  // 0x00491510  conf=0.97  ?State_Enter_RISING@internal@@AAEXXZ
  using State_Enter_RISING_t = void (__thiscall*)(::internal *);
  inline void State_Enter_RISING(::internal * a0) { reinterpret_cast<State_Enter_RISING_t>(meridian::rebase(0x00491510))(a0); }
  // 0x00491840  conf=0.97  ?State_Enter_SINKING@internal@@AAEXXZ
  using State_Enter_SINKING_t = void (__thiscall*)(::internal *);
  inline void State_Enter_SINKING(::internal * a0) { reinterpret_cast<State_Enter_SINKING_t>(meridian::rebase(0x00491840))(a0); }
  // 0x0048E800  conf=0.726  ??0internal@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::internal *);
  inline undefined ctor(::internal * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0048E800))(a0); }
} // internal_

// ===== io_device =====  (1 functions)  ->  namespace io_device_
namespace io_device_ {
  // 0x00680A30  conf=0.97  ?Init@io_device@@UAEXXZ
  using Init_t = void (__thiscall*)(::io_device *);
  inline void Init(::io_device * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x00680A30))(a0); }
} // io_device_

// ===== io_mgr =====  (1 functions)  ->  namespace io_mgr_
namespace io_mgr_ {
  // 0x00677060  conf=0.97  ?io_dispatcher@@YAXXZ
  using io_dispatcher_t = void (__cdecl*)();
  inline void io_dispatcher() { reinterpret_cast<io_dispatcher_t>(meridian::rebase(0x00677060))(); }
} // io_mgr_

// ===== layer_mgr =====  (2 functions)  ->  namespace layer_mgr_
namespace layer_mgr_ {
  // 0x005F8BC0  conf=0.684  ?LoadObjects@layer_mgr@@QAEXXZ
  using LoadObjects_t = void (__thiscall*)(::layer_mgr *);
  inline void LoadObjects(::layer_mgr * a0) { reinterpret_cast<LoadObjects_t>(meridian::rebase(0x005F8BC0))(a0); }
  // 0x0055A2F0  conf=0.703  ?UnloadResources@layer_mgr@@QAEXH@Z
  using UnloadResources_t = void (__thiscall*)(::layer_mgr *, int);
  inline void UnloadResources(::layer_mgr * a0, int a1) { reinterpret_cast<UnloadResources_t>(meridian::rebase(0x0055A2F0))(a0, a1); }
} // layer_mgr_

// ===== level =====  (2 functions)  ->  namespace level_
namespace level_ {
  // 0x0041A080  conf=0.75  ?RestoreState@level@@UAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::level *, ::bitstream *);
  inline void RestoreState(::level * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x0041A080))(a0, a1); }
  // 0x0041A060  conf=0.93  ?SaveState@level@@UAEXAAVbitstream@@@Z
  using SaveState_t = void (__thiscall*)(::level *, ::bitstream *);
  inline void SaveState(::level * a0, ::bitstream * a1) { reinterpret_cast<SaveState_t>(meridian::rebase(0x0041A060))(a0, a1); }
} // level_

// ===== level_cloudsburst =====  (1 functions)  ->  namespace level_cloudsburst_
namespace level_cloudsburst_ {
  // 0x004134E0  conf=0.97  ?Init@level_cloudsburst@@UAEXXZ
  using Init_t = void (__thiscall*)(::level_cloudsburst *);
  inline void Init(::level_cloudsburst * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x004134E0))(a0); }
} // level_cloudsburst_

// ===== level_hobbiton =====  (9 functions)  ->  namespace level_hobbiton_
namespace level_hobbiton_ {
  // 0x00411C90  conf=0.95  ?AdvanceLogic@level_hobbiton@@UAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::level_hobbiton *, float);
  inline void AdvanceLogic(::level_hobbiton * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00411C90))(a0, a1); }
  // 0x00410C80  conf=0.97  ?Init@level_hobbiton@@UAEXXZ
  using Init_t = void (__thiscall*)(::level_hobbiton *);
  inline void Init(::level_hobbiton * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x00410C80))(a0); }
  // 0x00411BA0  conf=0.739  ?LilyStateAdvance@level_hobbiton@@IAEXM@Z
  using LilyStateAdvance_t = void (__thiscall*)(::level_hobbiton *, float);
  inline void LilyStateAdvance(::level_hobbiton * a0, float a1) { reinterpret_cast<LilyStateAdvance_t>(meridian::rebase(0x00411BA0))(a0, a1); }
  // 0x00411D60  conf=0.75  ?RestoreState@level_hobbiton@@UAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::level_hobbiton *, ::bitstream *);
  inline void RestoreState(::level_hobbiton * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x00411D60))(a0, a1); }
  // 0x00411D10  conf=0.93  ?SaveState@level_hobbiton@@UAEXAAVbitstream@@@Z
  using SaveState_t = void (__thiscall*)(::level_hobbiton *, ::bitstream *);
  inline void SaveState(::level_hobbiton * a0, ::bitstream * a1) { reinterpret_cast<SaveState_t>(meridian::rebase(0x00411D10))(a0, a1); }
  // 0x00411B60  conf=0.774  ?StateAdvanceCLOSING@level_hobbiton@@IAEXH@Z
  using StateAdvanceCLOSING_t = void (__thiscall*)(::level_hobbiton *, int);
  inline void StateAdvanceCLOSING(::level_hobbiton * a0, int a1) { reinterpret_cast<StateAdvanceCLOSING_t>(meridian::rebase(0x00411B60))(a0, a1); }
  // 0x004119C0  conf=0.724  ?StateAdvanceOPEN_IMPACT@level_hobbiton@@IAEXH@Z
  using StateAdvanceOPEN_IMPACT_t = void (__thiscall*)(::level_hobbiton *, int);
  inline void StateAdvanceOPEN_IMPACT(::level_hobbiton * a0, int a1) { reinterpret_cast<StateAdvanceOPEN_IMPACT_t>(meridian::rebase(0x004119C0))(a0, a1); }
  // 0x00411AE0  conf=0.85  ?StateEnterCLOSING@level_hobbiton@@IAEXH@Z
  using StateEnterCLOSING_t = void (__thiscall*)(::level_hobbiton *, int);
  inline void StateEnterCLOSING(::level_hobbiton * a0, int a1) { reinterpret_cast<StateEnterCLOSING_t>(meridian::rebase(0x00411AE0))(a0, a1); }
  // 0x00411A00  conf=0.97  ?StateEnterOPEN_IDLE@level_hobbiton@@IAEXH@Z
  using StateEnterOPEN_IDLE_t = void (__thiscall*)(::level_hobbiton *, int);
  inline void StateEnterOPEN_IDLE(::level_hobbiton * a0, int a1) { reinterpret_cast<StateEnterOPEN_IDLE_t>(meridian::rebase(0x00411A00))(a0, a1); }
} // level_hobbiton_

// ===== level_laketown =====  (14 functions)  ->  namespace level_laketown_
namespace level_laketown_ {
  // 0x00416F60  conf=0.97  ?AdvanceDoorSwitchPuzzle@level_laketown@@IAEXM@Z
  using AdvanceDoorSwitchPuzzle_t = void (__thiscall*)(::level_laketown *, float);
  inline void AdvanceDoorSwitchPuzzle(::level_laketown * a0, float a1) { reinterpret_cast<AdvanceDoorSwitchPuzzle_t>(meridian::rebase(0x00416F60))(a0, a1); }
  // 0x00416630  conf=0.97  ?AdvanceGasPuzzle@level_laketown@@IAEXM@Z
  using AdvanceGasPuzzle_t = void (__thiscall*)(::level_laketown *, float);
  inline void AdvanceGasPuzzle(::level_laketown * a0, float a1) { reinterpret_cast<AdvanceGasPuzzle_t>(meridian::rebase(0x00416630))(a0, a1); }
  // 0x004157A0  conf=0.95  ?AdvancePPPuzz@level_laketown@@IAEXXZ
  using AdvancePPPuzz_t = void (__thiscall*)(::level_laketown *);
  inline void AdvancePPPuzz(::level_laketown * a0) { reinterpret_cast<AdvancePPPuzz_t>(meridian::rebase(0x004157A0))(a0); }
  // 0x00415590  conf=0.75  ?GetMatchingTorch@level_laketown@@IAE_KAB_K@Z
  using GetMatchingTorch_t = __uint64 (__thiscall*)(::level_laketown *, __uint64 *);
  inline __uint64 GetMatchingTorch(::level_laketown * a0, __uint64 * a1) { return reinterpret_cast<GetMatchingTorch_t>(meridian::rebase(0x00415590))(a0, a1); }
  // 0x00414EF0  conf=0.97  ?InitDoorSwitchPuzzle@level_laketown@@IAEXXZ
  using InitDoorSwitchPuzzle_t = void (__thiscall*)(::level_laketown *);
  inline void InitDoorSwitchPuzzle(::level_laketown * a0) { reinterpret_cast<InitDoorSwitchPuzzle_t>(meridian::rebase(0x00414EF0))(a0); }
  // 0x00416110  conf=0.97  ?InitGasPuzzle@level_laketown@@IAEXXZ
  using InitGasPuzzle_t = void (__thiscall*)(::level_laketown *);
  inline void InitGasPuzzle(::level_laketown * a0) { reinterpret_cast<InitGasPuzzle_t>(meridian::rebase(0x00416110))(a0); }
  // 0x00415070  conf=0.97  ?InitPPPuzz@level_laketown@@IAEXXZ
  using InitPPPuzz_t = void (__thiscall*)(::level_laketown *);
  inline void InitPPPuzz(::level_laketown * a0) { reinterpret_cast<InitPPPuzz_t>(meridian::rebase(0x00415070))(a0); }
  // 0x00417600  conf=0.75  ?RestoreState@level_laketown@@UAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::level_laketown *, ::bitstream *);
  inline void RestoreState(::level_laketown * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x00417600))(a0, a1); }
  // 0x004174D0  conf=0.93  ?SaveState@level_laketown@@UAEXAAVbitstream@@@Z
  using SaveState_t = void (__thiscall*)(::level_laketown *, ::bitstream *);
  inline void SaveState(::level_laketown * a0, ::bitstream * a1) { reinterpret_cast<SaveState_t>(meridian::rebase(0x004174D0))(a0, a1); }
  // 0x00415610  conf=0.9  ?SetDoorState@level_laketown@@IAEXAB_KH@Z
  using SetDoorState_t = void (__thiscall*)(::level_laketown *, __uint64 *, int);
  inline void SetDoorState(::level_laketown * a0, __uint64 * a1, int a2) { reinterpret_cast<SetDoorState_t>(meridian::rebase(0x00415610))(a0, a1, a2); }
  // 0x00417340  conf=0.773  ?SyncBarrelHeights@level_laketown@@IAEXXZ
  using SyncBarrelHeights_t = void (__thiscall*)(::level_laketown *);
  inline void SyncBarrelHeights(::level_laketown * a0) { reinterpret_cast<SyncBarrelHeights_t>(meridian::rebase(0x00417340))(a0); }
  // 0x00416870  conf=0.744  ?UpdateGasPuzzleActivity@level_laketown@@IAEXXZ
  using UpdateGasPuzzleActivity_t = void (__thiscall*)(::level_laketown *);
  inline void UpdateGasPuzzleActivity(::level_laketown * a0) { reinterpret_cast<UpdateGasPuzzleActivity_t>(meridian::rebase(0x00416870))(a0); }
  // 0x00417260  conf=0.97  ?UpdateLitPlates@level_laketown@@IAEXXZ
  using UpdateLitPlates_t = void (__thiscall*)(::level_laketown *);
  inline void UpdateLitPlates(::level_laketown * a0) { reinterpret_cast<UpdateLitPlates_t>(meridian::rebase(0x00417260))(a0); }
  // 0x0040A7E0  conf=0.738  ??0level_laketown@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::level_laketown *);
  inline undefined ctor(::level_laketown * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0040A7E0))(a0); }
} // level_laketown_

// ===== level_lonelymountain =====  (11 functions)  ->  namespace level_lonelymountain_
namespace level_lonelymountain_ {
  // 0x0040C130  conf=0.97  ?AdvanceLogic@level_lonelymountain@@UAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::level_lonelymountain *, float);
  inline void AdvanceLogic(::level_lonelymountain * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x0040C130))(a0, a1); }
  // 0x0040D560  conf=0.97  ?AdvanceTreasuryPuzzle@level_lonelymountain@@QAEXXZ
  using AdvanceTreasuryPuzzle_t = void (__thiscall*)(::level_lonelymountain *);
  inline void AdvanceTreasuryPuzzle(::level_lonelymountain * a0) { reinterpret_cast<AdvanceTreasuryPuzzle_t>(meridian::rebase(0x0040D560))(a0); }
  // 0x0040E010  conf=0.93  ?PostHudRender@level_lonelymountain@@UAEXXZ
  using PostHudRender_t = void (__thiscall*)(::level_lonelymountain *);
  inline void PostHudRender(::level_lonelymountain * a0) { reinterpret_cast<PostHudRender_t>(meridian::rebase(0x0040E010))(a0); }
  // 0x0040C680  conf=0.75  ?SaveState@level_lonelymountain@@UAEXAAVbitstream@@@Z
  using SaveState_t = void (__thiscall*)(::level_lonelymountain *, ::bitstream *);
  inline void SaveState(::level_lonelymountain * a0, ::bitstream * a1) { reinterpret_cast<SaveState_t>(meridian::rebase(0x0040C680))(a0, a1); }
  // 0x0040CE00  conf=0.97  ?SetForgeBellowsActive@level_lonelymountain@@QAEXH@Z
  using SetForgeBellowsActive_t = void (__thiscall*)(::level_lonelymountain *, int);
  inline void SetForgeBellowsActive(::level_lonelymountain * a0, int a1) { reinterpret_cast<SetForgeBellowsActive_t>(meridian::rebase(0x0040CE00))(a0, a1); }
  // 0x0040CFA0  conf=0.97  ?SetForgeWaterActive@level_lonelymountain@@QAEXH@Z
  using SetForgeWaterActive_t = void (__thiscall*)(::level_lonelymountain *, int);
  inline void SetForgeWaterActive(::level_lonelymountain * a0, int a1) { reinterpret_cast<SetForgeWaterActive_t>(meridian::rebase(0x0040CFA0))(a0, a1); }
  // 0x0040D0E0  conf=0.97  ?SetGearRoomActive@level_lonelymountain@@QAEXH@Z
  using SetGearRoomActive_t = void (__thiscall*)(::level_lonelymountain *, int);
  inline void SetGearRoomActive(::level_lonelymountain * a0, int a1) { reinterpret_cast<SetGearRoomActive_t>(meridian::rebase(0x0040D0E0))(a0, a1); }
  // 0x0040D310  conf=0.803  ?SetSecretCanalActive@level_lonelymountain@@QAEXHH@Z
  using SetSecretCanalActive_t = void (__thiscall*)(::level_lonelymountain *, int, int);
  inline void SetSecretCanalActive(::level_lonelymountain * a0, int a1, int a2) { reinterpret_cast<SetSecretCanalActive_t>(meridian::rebase(0x0040D310))(a0, a1, a2); }
  // 0x0040D3A0  conf=0.789  ?SetSecretWaterDoorsActive@level_lonelymountain@@QAEXXZ
  using SetSecretWaterDoorsActive_t = void (__thiscall*)(::level_lonelymountain *);
  inline void SetSecretWaterDoorsActive(::level_lonelymountain * a0) { reinterpret_cast<SetSecretWaterDoorsActive_t>(meridian::rebase(0x0040D3A0))(a0); }
  // 0x0040D400  conf=0.97  ?SetTreasuryActive@level_lonelymountain@@QAEXH@Z
  using SetTreasuryActive_t = void (__thiscall*)(::level_lonelymountain *, int);
  inline void SetTreasuryActive(::level_lonelymountain * a0, int a1) { reinterpret_cast<SetTreasuryActive_t>(meridian::rebase(0x0040D400))(a0, a1); }
  // 0x0040CCA0  conf=0.9  ?TurnRoomsOnOff@level_lonelymountain@@QAEXXZ
  using TurnRoomsOnOff_t = void (__thiscall*)(::level_lonelymountain *);
  inline void TurnRoomsOnOff(::level_lonelymountain * a0) { reinterpret_cast<TurnRoomsOnOff_t>(meridian::rebase(0x0040CCA0))(a0); }
} // level_lonelymountain_

// ===== level_mirkwood =====  (1 functions)  ->  namespace level_mirkwood_
namespace level_mirkwood_ {
  // 0x00408D10  conf=0.7  ?AdvanceLogic@level_mirkwood@@UAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::level_mirkwood *, float);
  inline void AdvanceLogic(::level_mirkwood * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00408D10))(a0, a1); }
} // level_mirkwood_

// ===== level_overhill =====  (3 functions)  ->  namespace level_overhill_
namespace level_overhill_ {
  // 0x00409BC0  conf=0.801  ?AdvanceLogic@level_overhill@@UAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::level_overhill *, float);
  inline void AdvanceLogic(::level_overhill * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00409BC0))(a0, a1); }
  // 0x00409250  conf=0.97  ?Init@level_overhill@@UAEXXZ
  using Init_t = void (__thiscall*)(::level_overhill *);
  inline void Init(::level_overhill * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x00409250))(a0); }
  // 0x00409FA0  conf=0.799  ?SetRockPointNear@level_overhill@@IAEXAAUvector3@@H@Z
  using SetRockPointNear_t = void (__thiscall*)(::level_overhill *, ::vector3 *, int);
  inline void SetRockPointNear(::level_overhill * a0, ::vector3 * a1, int a2) { reinterpret_cast<SetRockPointNear_t>(meridian::rebase(0x00409FA0))(a0, a1, a2); }
} // level_overhill_

// ===== level_roastmutton =====  (3 functions)  ->  namespace level_roastmutton_
namespace level_roastmutton_ {
  // 0x00407540  conf=0.97  ?AdvanceLogic@level_roastmutton@@UAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::level_roastmutton *, float);
  inline void AdvanceLogic(::level_roastmutton * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00407540))(a0, a1); }
  // 0x00407E80  conf=0.97  ?DisableEffects@level_roastmutton@@IAEXXZ
  using DisableEffects_t = void (__thiscall*)(::level_roastmutton *);
  inline void DisableEffects(::level_roastmutton * a0) { reinterpret_cast<DisableEffects_t>(meridian::rebase(0x00407E80))(a0); }
  // 0x0040E060  conf=0.75  ??0level_roastmutton@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::level_roastmutton *);
  inline undefined ctor(::level_roastmutton * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0040E060))(a0); }
} // level_roastmutton_

// ===== level_smaug =====  (2 functions)  ->  namespace level_smaug_
namespace level_smaug_ {
  // 0x0040A510  conf=0.97  ?AdvanceLogic@level_smaug@@UAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::level_smaug *, float);
  inline void AdvanceLogic(::level_smaug * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x0040A510))(a0, a1); }
  // 0x0063CE50  conf=0.737  ?RestoreState@level_smaug@@UAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::level_smaug *, ::bitstream *);
  inline void RestoreState(::level_smaug * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x0063CE50))(a0, a1); }
} // level_smaug_

// ===== level_swordlight =====  (3 functions)  ->  namespace level_swordlight_
namespace level_swordlight_ {
  // 0x00401B40  conf=0.97  ?AdvanceLogic@level_swordlight@@UAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::level_swordlight *, float);
  inline void AdvanceLogic(::level_swordlight * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00401B40))(a0, a1); }
  // 0x004016E0  conf=0.97  ?CheckGate@level_swordlight@@QAEXHABUvector3@@@Z
  using CheckGate_t = void (__thiscall*)(::level_swordlight *, int, ::vector3 *);
  inline void CheckGate(::level_swordlight * a0, int a1, ::vector3 * a2) { reinterpret_cast<CheckGate_t>(meridian::rebase(0x004016E0))(a0, a1, a2); }
  // 0x00401EE0  conf=0.75  ?RestoreState@level_swordlight@@UAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::level_swordlight *, ::bitstream *);
  inline void RestoreState(::level_swordlight * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x00401EE0))(a0, a1); }
} // level_swordlight_

// ===== light =====  (17 functions)  ->  namespace light_
namespace light_ {
  // 0x00406BD0  conf=0.75  ?Enable@light@@QAEXH@Z
  using Enable_t = void (__thiscall*)(::light *, int);
  inline void Enable(::light * a0, int a1) { reinterpret_cast<Enable_t>(meridian::rebase(0x00406BD0))(a0, a1); }
  // 0x00494930  conf=0.9  ?EnumerateProperties@light@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::light *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::light * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00494930))(a0, a1); }
  // 0x00494640  conf=0.75  ?GetAttenEnd@light@@QBEMXZ
  using GetAttenEnd_t = float (__thiscall*)(::light *);
  inline float GetAttenEnd(::light * a0) { return reinterpret_cast<GetAttenEnd_t>(meridian::rebase(0x00494640))(a0); }
  // 0x004948A0  conf=0.75  ?GetAttr@light@@QAEIXZ
  using GetAttr_t = uint (__thiscall*)(::light *);
  inline uint GetAttr(::light * a0) { return reinterpret_cast<GetAttr_t>(meridian::rebase(0x004948A0))(a0); }
  // 0x004945E0  conf=0.75  ?GetColor@light@@QBE?AUxcolor@@XZ
  inline void* GetColor_at() { return meridian::rebase(0x004945E0); } // xcolor __thiscall GetColor(light *)
  // 0x00494610  conf=0.75  ?GetIntensity@light@@QBEMXZ
  using GetIntensity_t = float (__thiscall*)(::light *);
  inline float GetIntensity(::light * a0) { return reinterpret_cast<GetIntensity_t>(meridian::rebase(0x00494610))(a0); }
  // 0x00493B80  conf=0.75  ?InitFlicker@light@@QAEXXZ
  using InitFlicker_t = void (__thiscall*)(::light *);
  inline void InitFlicker(::light * a0) { reinterpret_cast<InitFlicker_t>(meridian::rebase(0x00493B80))(a0); }
  // 0x00493C70  conf=0.778  ?InitPoint@light@@QAEXPBDABUvector3@@Uxcolor@@MMMHHIE@Z
  inline void* InitPoint_at() { return meridian::rebase(0x00493C70); } // void __thiscall InitPoint(light *, char *, vector3 *, xcolor, float, float, float, int, int, uint, uchar)
  // 0x00493FF0  conf=0.85  ?OnExport@light@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::light *, ::bin_out *);
  inline void OnExport(::light * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00493FF0))(a0, a1); }
  // 0x00494130  conf=0.85  ?OnImport@light@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::light *, ::bin_in *);
  inline void OnImport(::light * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00494130))(a0, a1); }
  // 0x00495F90  conf=0.735  ?OnObjectActivate@light@@UAEXXZ
  using OnObjectActivate_t = void (__thiscall*)(::light *);
  inline void OnObjectActivate(::light * a0) { reinterpret_cast<OnObjectActivate_t>(meridian::rebase(0x00495F90))(a0); }
  // 0x004CD850  conf=0.75  ?OnObjectDeactivate@light@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::light *);
  inline void OnObjectDeactivate(::light * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004CD850))(a0); }
  // 0x004947C0  conf=0.742  ?SetAttenEnd@light@@QAEXM@Z
  using SetAttenEnd_t = void (__thiscall*)(::light *, float);
  inline void SetAttenEnd(::light * a0, float a1) { reinterpret_cast<SetAttenEnd_t>(meridian::rebase(0x004947C0))(a0, a1); }
  // 0x004948B0  conf=0.8  ?SetAttr@light@@QAEXI@Z
  using SetAttr_t = void (__thiscall*)(::light *, uint);
  inline void SetAttr(::light * a0, uint a1) { reinterpret_cast<SetAttr_t>(meridian::rebase(0x004948B0))(a0, a1); }
  // 0x004EE2D0  conf=0.75  ?SetColor@light@@QAEXUxcolor@@@Z
  inline void* SetColor_at() { return meridian::rebase(0x004EE2D0); } // void __thiscall SetColor(light *, xcolor)
  // 0x004946D0  conf=0.637  ?SetFlicker@light@@QAEXH@Z
  using SetFlicker_t = void (__thiscall*)(::light *, int);
  inline void SetFlicker(::light * a0, int a1) { reinterpret_cast<SetFlicker_t>(meridian::rebase(0x004946D0))(a0, a1); }
  // 0x004948F0  conf=0.68  ?SetIntensity@light@@QAEXM@Z
  using SetIntensity_t = void (__thiscall*)(::light *, float);
  inline void SetIntensity(::light * a0, float a1) { reinterpret_cast<SetIntensity_t>(meridian::rebase(0x004948F0))(a0, a1); }
} // light_

// ===== line_seg =====  (3 functions)  ->  namespace line_seg_
namespace line_seg_ {
  // 0x00496790  conf=0.97  ?EnumerateProperties@line_seg@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::line_seg *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::line_seg * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00496790))(a0, a1); }
  // 0x004970B0  conf=0.835  ?GetProperty@line_seg@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::line_seg *, char *);
  inline ::property GetProperty(::line_seg * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004970B0))(a0, a1); }
  // 0x004962E0  conf=0.75  ??0line_seg@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::line_seg *);
  inline undefined ctor(::line_seg * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004962E0))(a0); }
} // line_seg_

// ===== load_trigger =====  (4 functions)  ->  namespace load_trigger_
namespace load_trigger_ {
  // 0x00497E30  conf=0.97  ?EnumerateProperties@load_trigger@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::load_trigger *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::load_trigger * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00497E30))(a0, a1); }
  // 0x00497600  conf=0.75  ?Init@load_trigger@@QAEXABUvector3@@ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::load_trigger *, ::vector3 *, ::bbox *);
  inline void Init(::load_trigger * a0, ::vector3 * a1, ::bbox * a2) { reinterpret_cast<Init_t>(meridian::rebase(0x00497600))(a0, a1, a2); }
  // 0x004860F0  conf=0.736  ?OnExport@load_trigger@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::load_trigger *, ::bin_out *);
  inline void OnExport(::load_trigger * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004860F0))(a0, a1); }
  // 0x00499930  conf=0.785  ?OnImport@load_trigger@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::load_trigger *, ::bin_in *);
  inline void OnImport(::load_trigger * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00499930))(a0, a1); }
} // load_trigger_

// ===== lockGadgets =====  (3 functions)  ->  namespace lockGadgets_
namespace lockGadgets_ {
  // 0x0052A3F0  conf=0.97  ?Action@lockGadgets@@QAEXXZ
  using Action_t = void (__thiscall*)(::lockGadgets *);
  inline void Action(::lockGadgets * a0) { reinterpret_cast<Action_t>(meridian::rebase(0x0052A3F0))(a0); }
  // 0x00529520  conf=0.97  ?Render@lockGadgets@@QAEXXZ
  using Render_t = void (__thiscall*)(::lockGadgets *);
  inline void Render(::lockGadgets * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x00529520))(a0); }
  // 0x005299E0  conf=0.743  ?Update@lockGadgets@@QAEHXZ
  using Update_t = int (__thiscall*)(::lockGadgets *);
  inline int Update(::lockGadgets * a0) { return reinterpret_cast<Update_t>(meridian::rebase(0x005299E0))(a0); }
} // lockGadgets_

// ===== lonely_mountain_fx =====  (4 functions)  ->  namespace lonely_mountain_fx_
namespace lonely_mountain_fx_ {
  // 0x0040E1F0  conf=0.734  ?AdvanceLogic@lonely_mountain_fx@@QAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::lonely_mountain_fx *, float);
  inline void AdvanceLogic(::lonely_mountain_fx * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x0040E1F0))(a0, a1); }
  // 0x0040E590  conf=0.85  ?ExtinguishForge@lonely_mountain_fx@@QAEXXZ
  using ExtinguishForge_t = void (__thiscall*)(::lonely_mountain_fx *);
  inline void ExtinguishForge(::lonely_mountain_fx * a0) { reinterpret_cast<ExtinguishForge_t>(meridian::rebase(0x0040E590))(a0); }
  // 0x0040E4E0  conf=0.85  ?IgniteForge@lonely_mountain_fx@@QAEXH@Z
  using IgniteForge_t = void (__thiscall*)(::lonely_mountain_fx *, int);
  inline void IgniteForge(::lonely_mountain_fx * a0, int a1) { reinterpret_cast<IgniteForge_t>(meridian::rebase(0x0040E4E0))(a0, a1); }
  // 0x0040E080  conf=0.97  ?Init@lonely_mountain_fx@@QAEXXZ
  using Init_t = void (__thiscall*)(::lonely_mountain_fx *);
  inline void Init(::lonely_mountain_fx * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x0040E080))(a0); }
} // lonely_mountain_fx_

// ===== marker =====  (2 functions)  ->  namespace marker_
namespace marker_ {
  // 0x0049A5B0  conf=0.817  ?EnumerateProperties@marker@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::marker *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::marker * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0049A5B0))(a0, a1); }
  // 0x0049A3E0  conf=0.85  ?OnExport@marker@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::marker *, ::bin_out *);
  inline void OnExport(::marker * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x0049A3E0))(a0, a1); }
} // marker_

// ===== matrix4 =====  (6 functions)  ->  namespace matrix4_
namespace matrix4_ {
  // 0x004065C0  conf=0.775  ?GetRotation@matrix4@@QBE?AUradian3@@XZ
  using GetRotation_t = ::radian3 (__thiscall*)(::matrix4 *);
  inline ::radian3 GetRotation(::matrix4 * a0) { return reinterpret_cast<GetRotation_t>(meridian::rebase(0x004065C0))(a0); }
  // 0x004068C0  conf=0.743  ?GetScale@matrix4@@QBE?AUvector3@@XZ
  using GetScale_t = ::vector3 (__thiscall*)(::matrix4 *);
  inline ::vector3 GetScale(::matrix4 * a0) { return reinterpret_cast<GetScale_t>(meridian::rebase(0x004068C0))(a0); }
  // 0x00463C20  conf=0.716  ?Rotate@matrix4@@QAEXABUradian3@@@Z
  using Rotate_t = void (__thiscall*)(::matrix4 *, ::radian3 *);
  inline void Rotate(::matrix4 * a0, ::radian3 * a1) { reinterpret_cast<Rotate_t>(meridian::rebase(0x00463C20))(a0, a1); }
  // 0x0064D480  conf=0.739  ?Setup@matrix4@@QAEXABUvector3@@ABUradian3@@0@Z
  using Setup_t = void (__thiscall*)(::matrix4 *, ::vector3 *, ::radian3 *, ::vector3 *);
  inline void Setup(::matrix4 * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3) { reinterpret_cast<Setup_t>(meridian::rebase(0x0064D480))(a0, a1, a2, a3); }
  // 0x006ABE30  conf=0.97  ?Setup@matrix4@@QAEXABUvector3@@ABUquaternion@@0@Z
  using Setup_6ABE30_t = void (__thiscall*)(::matrix4 *, ::vector3 *, ::quaternion *, ::vector3 *);
  inline void Setup_6ABE30(::matrix4 * a0, ::vector3 * a1, ::quaternion * a2, ::vector3 * a3) { reinterpret_cast<Setup_6ABE30_t>(meridian::rebase(0x006ABE30))(a0, a1, a2, a3); }
  // 0x00420470  conf=0.796  ?Translate@matrix4@@QAEXABUvector3@@@Z
  using Translate_t = void (__thiscall*)(::matrix4 *, ::vector3 *);
  inline void Translate(::matrix4 * a0, ::vector3 * a1) { reinterpret_cast<Translate_t>(meridian::rebase(0x00420470))(a0, a1); }
} // matrix4_

// ===== memcard_hardware =====  (1 functions)  ->  namespace memcard_hardware_
namespace memcard_hardware_ {
  // 0x004F8C00  conf=0.8  ?SetOperation@memcard_hardware@@QAEXW4memcard_op@@@Z
  inline void* SetOperation_at() { return meridian::rebase(0x004F8C00); } // void __thiscall SetOperation(memcard_hardware *, memcard_op)
} // memcard_hardware_

// ===== mine_cart_ride =====  (20 functions)  ->  namespace mine_cart_ride_
namespace mine_cart_ride_ {
  // 0x00402D40  conf=0.97  ?Begin@mine_cart_ride@@QAEXH@Z
  using Begin_t = void (__thiscall*)(::mine_cart_ride *, int);
  inline void Begin(::mine_cart_ride * a0, int a1) { reinterpret_cast<Begin_t>(meridian::rebase(0x00402D40))(a0, a1); }
  // 0x004060E0  conf=0.75  ?BilboSwinging@mine_cart_ride@@QAEXXZ
  using BilboSwinging_t = void (__thiscall*)(::mine_cart_ride *);
  inline void BilboSwinging(::mine_cart_ride * a0) { reinterpret_cast<BilboSwinging_t>(meridian::rebase(0x004060E0))(a0); }
  // 0x004050B0  conf=0.97  ?DecrementAnim@mine_cart_ride@@AAEXXZ
  using DecrementAnim_t = void (__thiscall*)(::mine_cart_ride *);
  inline void DecrementAnim(::mine_cart_ride * a0) { reinterpret_cast<DecrementAnim_t>(meridian::rebase(0x004050B0))(a0); }
  // 0x00405850  conf=0.75  ?FlipBilbo@mine_cart_ride@@QBEHXZ
  using FlipBilbo_t = int (__thiscall*)(::mine_cart_ride *);
  inline int FlipBilbo(::mine_cart_ride * a0) { return reinterpret_cast<FlipBilbo_t>(meridian::rebase(0x00405850))(a0); }
  // 0x00405F80  conf=0.683  ?Freeze@mine_cart_ride@@QAEXXZ
  using Freeze_t = void (__thiscall*)(::mine_cart_ride *);
  inline void Freeze(::mine_cart_ride * a0) { reinterpret_cast<Freeze_t>(meridian::rebase(0x00405F80))(a0); }
  // 0x00404A60  conf=0.75  ?GetMineCartL2W@mine_cart_ride@@QBEABVmatrix4@@XZ
  using GetMineCartL2W_t = ::matrix4 * (__thiscall*)(::mine_cart_ride *);
  inline ::matrix4 * GetMineCartL2W(::mine_cart_ride * a0) { return reinterpret_cast<GetMineCartL2W_t>(meridian::rebase(0x00404A60))(a0); }
  // 0x00404A40  conf=0.75  ?GetMineCartPosition@mine_cart_ride@@QBE?AUvector3@@XZ
  using GetMineCartPosition_t = ::vector3 (__thiscall*)(::mine_cart_ride *);
  inline ::vector3 GetMineCartPosition(::mine_cart_ride * a0) { return reinterpret_cast<GetMineCartPosition_t>(meridian::rebase(0x00404A40))(a0); }
  // 0x00405860  conf=0.737  ?HandleInput@mine_cart_ride@@AAEXXZ
  using HandleInput_t = void (__thiscall*)(::mine_cart_ride *);
  inline void HandleInput(::mine_cart_ride * a0) { reinterpret_cast<HandleInput_t>(meridian::rebase(0x00405860))(a0); }
  // 0x00404A90  conf=0.97  ?IncrementAnim@mine_cart_ride@@AAEXXZ
  using IncrementAnim_t = void (__thiscall*)(::mine_cart_ride *);
  inline void IncrementAnim(::mine_cart_ride * a0) { reinterpret_cast<IncrementAnim_t>(meridian::rebase(0x00404A90))(a0); }
  // 0x00402AF0  conf=0.97  ?Init@mine_cart_ride@@QAEXXZ
  using Init_t = void (__thiscall*)(::mine_cart_ride *);
  inline void Init(::mine_cart_ride * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x00402AF0))(a0); }
  // 0x00405FC0  conf=0.75  ?IsFrozen@mine_cart_ride@@QBEHXZ
  using IsFrozen_t = int (__thiscall*)(::mine_cart_ride *);
  inline int IsFrozen(::mine_cart_ride * a0) { return reinterpret_cast<IsFrozen_t>(meridian::rebase(0x00405FC0))(a0); }
  // 0x00405FF0  conf=0.75  ?IsRolling@mine_cart_ride@@QBEHXZ
  using IsRolling_t = int (__thiscall*)(::mine_cart_ride *);
  inline int IsRolling(::mine_cart_ride * a0) { return reinterpret_cast<IsRolling_t>(meridian::rebase(0x00405FF0))(a0); }
  // 0x00406DC0  conf=0.745  ?LowerArrow@mine_cart_ride@@AAEXH@Z
  using LowerArrow_t = void (__thiscall*)(::mine_cart_ride *, int);
  inline void LowerArrow(::mine_cart_ride * a0, int a1) { reinterpret_cast<LowerArrow_t>(meridian::rebase(0x00406DC0))(a0, a1); }
  // 0x00403120  conf=0.682  ?OnAdvanceLogic@mine_cart_ride@@QAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::mine_cart_ride *, float);
  inline void OnAdvanceLogic(::mine_cart_ride * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x00403120))(a0, a1); }
  // 0x0053BE70  conf=0.719  ?RaiseArrow@mine_cart_ride@@AAEXH@Z
  using RaiseArrow_t = void (__thiscall*)(::mine_cart_ride *, int);
  inline void RaiseArrow(::mine_cart_ride * a0, int a1) { reinterpret_cast<RaiseArrow_t>(meridian::rebase(0x0053BE70))(a0, a1); }
  // 0x00406430  conf=0.97  ?RestoreState@mine_cart_ride@@QAEXAAVbitstream@@@Z
  using RestoreState_t = void (__thiscall*)(::mine_cart_ride *, ::bitstream *);
  inline void RestoreState(::mine_cart_ride * a0, ::bitstream * a1) { reinterpret_cast<RestoreState_t>(meridian::rebase(0x00406430))(a0, a1); }
  // 0x00405E10  conf=0.736  ?RunThroughAnim@mine_cart_ride@@AAEXH@Z
  using RunThroughAnim_t = void (__thiscall*)(::mine_cart_ride *, int);
  inline void RunThroughAnim(::mine_cart_ride * a0, int a1) { reinterpret_cast<RunThroughAnim_t>(meridian::rebase(0x00405E10))(a0, a1); }
  // 0x004048C0  conf=0.725  ?SetAnimResourceName@mine_cart_ride@@AAEXPBD@Z
  using SetAnimResourceName_t = void (__thiscall*)(::mine_cart_ride *, char *);
  inline void SetAnimResourceName(::mine_cart_ride * a0, char * a1) { reinterpret_cast<SetAnimResourceName_t>(meridian::rebase(0x004048C0))(a0, a1); }
  // 0x004063F0  conf=0.97  ?StartRolling@mine_cart_ride@@QAEXXZ
  using StartRolling_t = void (__thiscall*)(::mine_cart_ride *);
  inline void StartRolling(::mine_cart_ride * a0) { reinterpret_cast<StartRolling_t>(meridian::rebase(0x004063F0))(a0); }
  // 0x004057B0  conf=0.97  ?Stop@mine_cart_ride@@QAEXXZ
  using Stop_t = void (__thiscall*)(::mine_cart_ride *);
  inline void Stop(::mine_cart_ride * a0) { reinterpret_cast<Stop_t>(meridian::rebase(0x004057B0))(a0); }
} // mine_cart_ride_

// ===== music_mgr =====  (1 functions)  ->  namespace music_mgr_
namespace music_mgr_ {
  // 0x00530CE0  conf=0.97  ??0music_mgr@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::music_mgr *);
  inline undefined ctor(::music_mgr * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x00530CE0))(a0); }
} // music_mgr_

// ===== music_trigger =====  (3 functions)  ->  namespace music_trigger_
namespace music_trigger_ {
  // 0x00456BB0  conf=0.842  ?OnExport@music_trigger@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::music_trigger *, ::bin_out *);
  inline void OnExport(::music_trigger * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x00456BB0))(a0, a1); }
  // 0x00456D80  conf=0.812  ?OnImport@music_trigger@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::music_trigger *, ::bin_in *);
  inline void OnImport(::music_trigger * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x00456D80))(a0, a1); }
  // 0x00539D90  conf=0.97  ?SetProperty@music_trigger@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::music_trigger *, char *, ::property *);
  inline int SetProperty(::music_trigger * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x00539D90))(a0, a1, a2); }
} // music_trigger_

// ===== nav_point =====  (8 functions)  ->  namespace nav_point_
namespace nav_point_ {
  // 0x0049DFF0  conf=0.748  ?AddLink@nav_point@@QAEX_KM@Z
  using AddLink_t = void (__thiscall*)(::nav_point *, __uint64, float);
  inline void AddLink(::nav_point * a0, __uint64 a1, float a2) { reinterpret_cast<AddLink_t>(meridian::rebase(0x0049DFF0))(a0, a1, a2); }
  // 0x0049DD50  conf=0.777  ?CalculateLinks@nav_point@@QAEXXZ
  using CalculateLinks_t = void (__thiscall*)(::nav_point *);
  inline void CalculateLinks(::nav_point * a0) { reinterpret_cast<CalculateLinks_t>(meridian::rebase(0x0049DD50))(a0); }
  // 0x0049E130  conf=0.85  ?OnExport@nav_point@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::nav_point *, ::bin_out *);
  inline void OnExport(::nav_point * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x0049E130))(a0, a1); }
  // 0x0049E1A0  conf=0.832  ?OnImport@nav_point@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::nav_point *, ::bin_in *);
  inline void OnImport(::nav_point * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x0049E1A0))(a0, a1); }
  // 0x0049E090  conf=0.72  ?RemoveLink@nav_point@@QAEX_K@Z
  using RemoveLink_t = void (__thiscall*)(::nav_point *, __uint64);
  inline void RemoveLink(::nav_point * a0, __uint64 a1) { reinterpret_cast<RemoveLink_t>(meridian::rebase(0x0049E090))(a0, a1); }
  // 0x00650150  conf=0.75  ?Render@nav_point@@UAEXXZ
  using Render_t = void (__thiscall*)(::nav_point *);
  inline void Render(::nav_point * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x00650150))(a0); }
  // 0x0049DBD0  conf=0.778  ?SetJumpTarget@nav_point@@IAEX_K@Z
  using SetJumpTarget_t = void (__thiscall*)(::nav_point *, __uint64);
  inline void SetJumpTarget(::nav_point * a0, __uint64 a1) { reinterpret_cast<SetJumpTarget_t>(meridian::rebase(0x0049DBD0))(a0, a1); }
  // 0x0049D660  conf=0.97  ??0nav_point@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::nav_point *);
  inline undefined ctor(::nav_point * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x0049D660))(a0); }
} // nav_point_

// ===== obj_mgr =====  (5 functions)  ->  namespace obj_mgr_
namespace obj_mgr_ {
  // 0x0054D950  conf=0.97  ?ApplyPain@obj_mgr@@QAEH_KABUvector3@@MMMMIW4ePainType@PainData@@HH@Z
  inline void* ApplyPain_at() { return meridian::rebase(0x0054D950); } // int __thiscall ApplyPain(obj_mgr *, __uint64, vector3 *, float, float, float, float, uint, ePainType, int, int)
  // 0x00406BF0  conf=0.723  ?DestroyObject@obj_mgr@@QAEX_K@Z
  using DestroyObject_t = void (__thiscall*)(::obj_mgr *, __uint64);
  inline void DestroyObject(::obj_mgr * a0, __uint64 a1) { reinterpret_cast<DestroyObject_t>(meridian::rebase(0x00406BF0))(a0, a1); }
  // 0x004021C0  conf=0.698  ?GetSlotFromGuid@obj_mgr@@QAEH_K@Z
  using GetSlotFromGuid_t = int (__thiscall*)(::obj_mgr *, __uint64);
  inline int GetSlotFromGuid(::obj_mgr * a0, __uint64 a1) { return reinterpret_cast<GetSlotFromGuid_t>(meridian::rebase(0x004021C0))(a0, a1); }
  // 0x00413480  conf=0.692  ?Kill@obj_mgr@@QAEXXZ
  using Kill_t = void (__thiscall*)(::obj_mgr *);
  inline void Kill(::obj_mgr * a0) { reinterpret_cast<Kill_t>(meridian::rebase(0x00413480))(a0); }
  // 0x004DBD50  conf=0.796  ?LockObject@obj_mgr@@QAEPAVobject@@_K@Z
  using LockObject_t = ::object * (__thiscall*)(::obj_mgr *, __uint64);
  inline ::object * LockObject(::obj_mgr * a0, __uint64 a1) { return reinterpret_cast<LockObject_t>(meridian::rebase(0x004DBD50))(a0, a1); }
} // obj_mgr_

// ===== object =====  (27 functions)  ->  namespace object_
namespace object_ {
  // 0x004AB260  conf=0.744  ?CheckForFog@object@@IAEXABUvector3@@@Z
  using CheckForFog_t = void (__thiscall*)(::object *, ::vector3 *);
  inline void CheckForFog(::object * a0, ::vector3 * a1) { reinterpret_cast<CheckForFog_t>(meridian::rebase(0x004AB260))(a0, a1); }
  // 0x004AB4E0  conf=0.97  ?EnumerateProperties@object@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::object *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::object * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004AB4E0))(a0, a1); }
  // 0x004AAAF0  conf=0.8  ?ExecuteScript@object@@QAEXPBD0PAX@Z
  using ExecuteScript_t = void (__thiscall*)(::object *, char *, char *, void *);
  inline void ExecuteScript(::object * a0, char * a1, char * a2, void * a3) { reinterpret_cast<ExecuteScript_t>(meridian::rebase(0x004AAAF0))(a0, a1, a2, a3); }
  // 0x004AAB50  conf=0.8  ?ExecuteScript@object@@QAEXPBD0AAVvm_arglist@@@Z
  using ExecuteScript_4AAB50_t = void (__thiscall*)(::object *, char *, char *, ::vm_arglist *);
  inline void ExecuteScript_4AAB50(::object * a0, char * a1, char * a2, ::vm_arglist * a3) { reinterpret_cast<ExecuteScript_4AAB50_t>(meridian::rebase(0x004AAB50))(a0, a1, a2, a3); }
  // 0x004AC5D0  conf=0.75  ?GetIsLayerActive@object@@QAEHXZ
  using GetIsLayerActive_t = int (__thiscall*)(::object *);
  inline int GetIsLayerActive(::object * a0) { return reinterpret_cast<GetIsLayerActive_t>(meridian::rebase(0x004AC5D0))(a0); }
  // 0x004ABDF0  conf=0.878  ?GetProperty@object@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::object *, char *);
  inline ::property GetProperty(::object * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004ABDF0))(a0, a1); }
  // 0x004AAC60  conf=0.741  ?GetWaterGuid@object@@IAE_KXZ
  using GetWaterGuid_t = __uint64 (__thiscall*)(::object *);
  inline __uint64 GetWaterGuid(::object * a0) { return reinterpret_cast<GetWaterGuid_t>(meridian::rebase(0x004AAC60))(a0); }
  // 0x004AABB0  conf=0.75  ?HasScriptMethod@object@@QAEHPBD0@Z
  using HasScriptMethod_t = int (__thiscall*)(::object *, char *, char *);
  inline int HasScriptMethod(::object * a0, char * a1, char * a2) { return reinterpret_cast<HasScriptMethod_t>(meridian::rebase(0x004AABB0))(a0, a1, a2); }
  // 0x004D1130  conf=0.725  ?IsGoldPile@object@@QAEHXZ
  using IsGoldPile_t = int (__thiscall*)(::object *);
  inline int IsGoldPile(::object * a0) { return reinterpret_cast<IsGoldPile_t>(meridian::rebase(0x004D1130))(a0); }
  // 0x004AAD90  conf=0.97  ?MakeSplash@object@@IAEXABUvector3@@@Z
  using MakeSplash_t = void (__thiscall*)(::object *, ::vector3 *);
  inline void MakeSplash(::object * a0, ::vector3 * a1) { reinterpret_cast<MakeSplash_t>(meridian::rebase(0x004AAD90))(a0, a1); }
  // 0x004AA440  conf=0.786  ?Move@object@@UAEXABUvector3@@H@Z
  using Move_t = void (__thiscall*)(::object *, ::vector3 *, int);
  inline void Move(::object * a0, ::vector3 * a1, int a2) { reinterpret_cast<Move_t>(meridian::rebase(0x004AA440))(a0, a1, a2); }
  // 0x004AA650  conf=0.856  ?OnExport@object@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::object *, ::bin_out *);
  inline void OnExport(::object * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004AA650))(a0, a1); }
  // 0x004AA740  conf=0.9  ?OnImport@object@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::object *, ::bin_in *);
  inline void OnImport(::object * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004AA740))(a0, a1); }
  // 0x004AC510  conf=0.744  ?OnObjectActivate@object@@UAEXXZ
  using OnObjectActivate_t = void (__thiscall*)(::object *);
  inline void OnObjectActivate(::object * a0) { reinterpret_cast<OnObjectActivate_t>(meridian::rebase(0x004AC510))(a0); }
  // 0x004AC540  conf=0.789  ?OnObjectDeactivate@object@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::object *);
  inline void OnObjectDeactivate(::object * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004AC540))(a0); }
  // 0x004AAA60  conf=0.75  ?RequestDestroy@object@@QAEXXZ
  using RequestDestroy_t = void (__thiscall*)(::object *);
  inline void RequestDestroy(::object * a0) { reinterpret_cast<RequestDestroy_t>(meridian::rebase(0x004AAA60))(a0); }
  // 0x004AB400  conf=0.75  ?SetDoesBilboCollision@object@@QAEXH@Z
  using SetDoesBilboCollision_t = void (__thiscall*)(::object *, int);
  inline void SetDoesBilboCollision(::object * a0, int a1) { reinterpret_cast<SetDoesBilboCollision_t>(meridian::rebase(0x004AB400))(a0, a1); }
  // 0x004AB450  conf=0.736  ?SetDoesCameraCollision@object@@QAEXH@Z
  using SetDoesCameraCollision_t = void (__thiscall*)(::object *, int);
  inline void SetDoesCameraCollision(::object * a0, int a1) { reinterpret_cast<SetDoesCameraCollision_t>(meridian::rebase(0x004AB450))(a0, a1); }
  // 0x004AB480  conf=0.722  ?SetDoesCameraFade@object@@QAEXH@Z
  using SetDoesCameraFade_t = void (__thiscall*)(::object *, int);
  inline void SetDoesCameraFade(::object * a0, int a1) { reinterpret_cast<SetDoesCameraFade_t>(meridian::rebase(0x004AB480))(a0, a1); }
  // 0x004AB3E0  conf=0.8  ?SetDoesCollision@object@@QAEXH@Z
  using SetDoesCollision_t = void (__thiscall*)(::object *, int);
  inline void SetDoesCollision(::object * a0, int a1) { reinterpret_cast<SetDoesCollision_t>(meridian::rebase(0x004AB3E0))(a0, a1); }
  // 0x004AB420  conf=0.75  ?SetDoesNPCCollision@object@@QAEXH@Z
  using SetDoesNPCCollision_t = void (__thiscall*)(::object *, int);
  inline void SetDoesNPCCollision(::object * a0, int a1) { reinterpret_cast<SetDoesNPCCollision_t>(meridian::rebase(0x004AB420))(a0, a1); }
  // 0x004AC4E0  conf=0.8  ?SetGoldPile@object@@QAEXH@Z
  using SetGoldPile_t = void (__thiscall*)(::object *, int);
  inline void SetGoldPile(::object * a0, int a1) { reinterpret_cast<SetGoldPile_t>(meridian::rebase(0x004AC4E0))(a0, a1); }
  // 0x00494890  conf=0.75  ?SetLightChannel@object@@QAEXE@Z
  using SetLightChannel_t = void (__thiscall*)(::object *, uchar);
  inline void SetLightChannel(::object * a0, uchar a1) { reinterpret_cast<SetLightChannel_t>(meridian::rebase(0x00494890))(a0, a1); }
  // 0x004AA910  conf=0.9  ?SetName@object@@UAEXPBD@Z
  using SetName_t = void (__thiscall*)(::object *, char *);
  inline void SetName(::object * a0, char * a1) { reinterpret_cast<SetName_t>(meridian::rebase(0x004AA910))(a0, a1); }
  // 0x004AA9E0  conf=0.713  ?SetName@object@@QAEXABVxwstring@@@Z
  using SetName_4AA9E0_t = void (__thiscall*)(::object *, ::xwstring *);
  inline void SetName_4AA9E0(::object * a0, ::xwstring * a1) { reinterpret_cast<SetName_4AA9E0_t>(meridian::rebase(0x004AA9E0))(a0, a1); }
  // 0x004AB750  conf=0.9  ?SetProperty@object@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::object *, char *, ::property *);
  inline int SetProperty(::object * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004AB750))(a0, a1, a2); }
  // 0x004AA170  conf=0.867  ??0object@@IAE@XZ
  using ctor_t = undefined (__thiscall*)(::object *);
  inline undefined ctor(::object * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004AA170))(a0); }
} // object_

// ===== occluder_mgr =====  (1 functions)  ->  namespace occluder_mgr_
namespace occluder_mgr_ {
  // 0x00653240  conf=0.791  ?LoadNonPermanentOccluders@occluder_mgr@@QAEXXZ
  using LoadNonPermanentOccluders_t = void (__thiscall*)(::occluder_mgr *);
  inline void LoadNonPermanentOccluders(::occluder_mgr * a0) { reinterpret_cast<LoadNonPermanentOccluders_t>(meridian::rebase(0x00653240))(a0); }
} // occluder_mgr_

// ===== one_shot_light =====  (1 functions)  ->  namespace one_shot_light_
namespace one_shot_light_ {
  // 0x004AD470  conf=0.738  ?InitOneShot@one_shot_light@@QAEXPBDABUvector3@@MMMUxcolor@@2@Z
  inline void* InitOneShot_at() { return meridian::rebase(0x004AD470); } // void __thiscall InitOneShot(one_shot_light *, char *, vector3 *, float, float, float, xcolor, xcolor)
} // one_shot_light_

// ===== path =====  (2 functions)  ->  namespace path_
namespace path_ {
  // 0x004ADC40  conf=0.776  ?GetInterpL2W@path@@QBEXMAAVmatrix4@@@Z
  using GetInterpL2W_t = void (__thiscall*)(::path *, float, ::matrix4 *);
  inline void GetInterpL2W(::path * a0, float a1, ::matrix4 * a2) { reinterpret_cast<GetInterpL2W_t>(meridian::rebase(0x004ADC40))(a0, a1, a2); }
  // 0x004ADB90  conf=0.702  ?GetOrientationFromKey@path@@IBE?AUquaternion@@AAUkey@1@@Z
  using GetOrientationFromKey_t = ::quaternion (__thiscall*)(::path *, ::key *);
  inline ::quaternion GetOrientationFromKey(::path * a0, ::key * a1) { return reinterpret_cast<GetOrientationFromKey_t>(meridian::rebase(0x004ADB90))(a0, a1); }
} // path_

// ===== pickup =====  (21 functions)  ->  namespace pickup_
namespace pickup_ {
  // 0x004B3730  conf=0.794  ?DestroyMovingInfo@pickup@@QAEXXZ
  using DestroyMovingInfo_t = void (__thiscall*)(::pickup *);
  inline void DestroyMovingInfo(::pickup * a0) { reinterpret_cast<DestroyMovingInfo_t>(meridian::rebase(0x004B3730))(a0); }
  // 0x004B1090  conf=0.9  ?EnumerateProperties@pickup@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::pickup *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::pickup * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004B1090))(a0, a1); }
  // 0x004B0F50  conf=0.8  ?GetAmount@pickup@@QAEMXZ
  using GetAmount_t = float (__thiscall*)(::pickup *);
  inline float GetAmount(::pickup * a0) { return reinterpret_cast<GetAmount_t>(meridian::rebase(0x004B0F50))(a0); }
  // 0x004B1070  conf=0.8  ?GetPickedUp@pickup@@QAEHXZ
  using GetPickedUp_t = int (__thiscall*)(::pickup *);
  inline int GetPickedUp(::pickup * a0) { return reinterpret_cast<GetPickedUp_t>(meridian::rebase(0x004B1070))(a0); }
  // 0x004B0E70  conf=0.781  ?GetType@pickup@@QAE?AVxstring@@XZ
  using GetType_t = ::xstring (__thiscall*)(::pickup *);
  inline ::xstring GetType(::pickup * a0) { return reinterpret_cast<GetType_t>(meridian::rebase(0x004B0E70))(a0); }
  // 0x004B0EA0  conf=0.75  ?GetTypeIndex@pickup@@QAEHXZ
  using GetTypeIndex_t = int (__thiscall*)(::pickup *);
  inline int GetTypeIndex(::pickup * a0) { return reinterpret_cast<GetTypeIndex_t>(meridian::rebase(0x004B0EA0))(a0); }
  // 0x004AF7A0  conf=0.85  ?Init@pickup@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::pickup *, ::vector3 *, ::radian3 *, ::vector3 *, ::bbox *);
  inline void Init(::pickup * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3, ::bbox * a4) { reinterpret_cast<Init_t>(meridian::rebase(0x004AF7A0))(a0, a1, a2, a3, a4); }
  // 0x004B25F0  conf=0.75  ?IsBeingLaunched@pickup@@QAEHXZ
  using IsBeingLaunched_t = int (__thiscall*)(::pickup *);
  inline int IsBeingLaunched(::pickup * a0) { return reinterpret_cast<IsBeingLaunched_t>(meridian::rebase(0x004B25F0))(a0); }
  // 0x004B1080  conf=0.75  ?IsGetAble@pickup@@QAEHXZ
  using IsGetAble_t = int (__thiscall*)(::pickup *);
  inline int IsGetAble(::pickup * a0) { return reinterpret_cast<IsGetAble_t>(meridian::rebase(0x004B1080))(a0); }
  // 0x004AFE00  conf=0.792  ?OnAdvanceLogic@pickup@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::pickup *, float);
  inline void OnAdvanceLogic(::pickup * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004AFE00))(a0, a1); }
  // 0x004B0C30  conf=0.9  ?OnImport@pickup@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::pickup *, ::bin_in *);
  inline void OnImport(::pickup * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004B0C30))(a0, a1); }
  // 0x004B2310  conf=0.782  ?OnObjectDeactivate@pickup@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::pickup *);
  inline void OnObjectDeactivate(::pickup * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004B2310))(a0); }
  // 0x0059B1D0  conf=0.73  ?Render@pickup@@UAEXXZ
  using Render_t = void (__thiscall*)(::pickup *);
  inline void Render(::pickup * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x0059B1D0))(a0); }
  // 0x004B0F80  conf=0.7  ?SetPickedUp@pickup@@QAEXH@Z
  using SetPickedUp_t = void (__thiscall*)(::pickup *, int);
  inline void SetPickedUp(::pickup * a0, int a1) { reinterpret_cast<SetPickedUp_t>(meridian::rebase(0x004B0F80))(a0, a1); }
  // 0x004B0F30  conf=0.552  ?SetProperty@pickup@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::pickup *, char *, ::property *);
  inline int SetProperty(::pickup * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004B0F30))(a0, a1, a2); }
  // 0x004B3400  conf=0.97  ?SetupChase@pickup@@QAEXXZ
  using SetupChase_t = void (__thiscall*)(::pickup *);
  inline void SetupChase(::pickup * a0) { reinterpret_cast<SetupChase_t>(meridian::rebase(0x004B3400))(a0); }
  // 0x004B0900  conf=0.97  ?SetupFX@pickup@@IAEHABUbbox@@@Z
  using SetupFX_t = int (__thiscall*)(::pickup *, ::bbox *);
  inline int SetupFX(::pickup * a0, ::bbox * a1) { return reinterpret_cast<SetupFX_t>(meridian::rebase(0x004B0900))(a0, a1); }
  // 0x004AF8D0  conf=0.97  ?SetupLaunch@pickup@@QAEXABUvector3@@0HH@Z
  using SetupLaunch_t = void (__thiscall*)(::pickup *, ::vector3 *, ::vector3 *, int, int);
  inline void SetupLaunch(::pickup * a0, ::vector3 * a1, ::vector3 * a2, int a3, int a4) { reinterpret_cast<SetupLaunch_t>(meridian::rebase(0x004AF8D0))(a0, a1, a2, a3, a4); }
  // 0x004B0EB0  conf=0.746  ?SetupTypeInfo@pickup@@IAEXF@Z
  using SetupTypeInfo_t = void (__thiscall*)(::pickup *, short);
  inline void SetupTypeInfo(::pickup * a0, short a1) { reinterpret_cast<SetupTypeInfo_t>(meridian::rebase(0x004B0EB0))(a0, a1); }
  // 0x004B31F0  conf=0.79  ?UpdateChase@pickup@@IAEXM@Z
  using UpdateChase_t = void (__thiscall*)(::pickup *, float);
  inline void UpdateChase(::pickup * a0, float a1) { reinterpret_cast<UpdateChase_t>(meridian::rebase(0x004B31F0))(a0, a1); }
  // 0x004B2390  conf=0.97  ?UpdateLaunch@pickup@@IAEXM@Z
  using UpdateLaunch_t = void (__thiscall*)(::pickup *, float);
  inline void UpdateLaunch(::pickup * a0, float a1) { reinterpret_cast<UpdateLaunch_t>(meridian::rebase(0x004B2390))(a0, a1); }
} // pickup_

// ===== plane =====  (1 functions)  ->  namespace plane_
namespace plane_ {
  // 0x006A1050  conf=0.677  ?GetBBoxIndices@plane@@QBEXPAH0@Z
  using GetBBoxIndices_t = void (__thiscall*)(::plane *, int *, int *);
  inline void GetBBoxIndices(::plane * a0, int * a1, int * a2) { reinterpret_cast<GetBBoxIndices_t>(meridian::rebase(0x006A1050))(a0, a1, a2); }
} // plane_

// ===== platform_puzzle =====  (11 functions)  ->  namespace platform_puzzle_
namespace platform_puzzle_ {
  // 0x00418110  conf=0.719  ?AdvanceLogic@platform_puzzle@@QAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::platform_puzzle *, float);
  inline void AdvanceLogic(::platform_puzzle * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x00418110))(a0, a1); }
  // 0x00418290  conf=0.97  ?AdvancePuzzleEditing@platform_puzzle@@AAEXM@Z
  using AdvancePuzzleEditing_t = void (__thiscall*)(::platform_puzzle *, float);
  inline void AdvancePuzzleEditing(::platform_puzzle * a0, float a1) { reinterpret_cast<AdvancePuzzleEditing_t>(meridian::rebase(0x00418290))(a0, a1); }
  // 0x00418C20  conf=0.85  ?AdvanceSwapPlatform@platform_puzzle@@AAEHM@Z
  using AdvanceSwapPlatform_t = int (__thiscall*)(::platform_puzzle *, float);
  inline int AdvanceSwapPlatform(::platform_puzzle * a0, float a1) { return reinterpret_cast<AdvanceSwapPlatform_t>(meridian::rebase(0x00418C20))(a0, a1); }
  // 0x00418EA0  conf=0.765  ?HideObstructions@platform_puzzle@@AAEXH@Z
  using HideObstructions_t = void (__thiscall*)(::platform_puzzle *, int);
  inline void HideObstructions(::platform_puzzle * a0, int a1) { reinterpret_cast<HideObstructions_t>(meridian::rebase(0x00418EA0))(a0, a1); }
  // 0x00417E90  conf=0.97  ?Init@platform_puzzle@@QAEXABUvector3@@@Z
  using Init_t = void (__thiscall*)(::platform_puzzle *, ::vector3 *);
  inline void Init(::platform_puzzle * a0, ::vector3 * a1) { reinterpret_cast<Init_t>(meridian::rebase(0x00417E90))(a0, a1); }
  // 0x004189D0  conf=0.779  ?ResetPlatformPositions@platform_puzzle@@AAEXXZ
  using ResetPlatformPositions_t = void (__thiscall*)(::platform_puzzle *);
  inline void ResetPlatformPositions(::platform_puzzle * a0) { reinterpret_cast<ResetPlatformPositions_t>(meridian::rebase(0x004189D0))(a0); }
  // 0x00418850  conf=0.73  ?Select@platform_puzzle@@AAEXXZ
  using Select_t = void (__thiscall*)(::platform_puzzle *);
  inline void Select(::platform_puzzle * a0) { reinterpret_cast<Select_t>(meridian::rebase(0x00418850))(a0); }
  // 0x00417C90  conf=0.8  ?SetCursorPos@platform_puzzle@@AAEXHH@Z
  using SetCursorPos_t = void (__thiscall*)(::platform_puzzle *, int, int);
  inline void SetCursorPos(::platform_puzzle * a0, int a1, int a2) { reinterpret_cast<SetCursorPos_t>(meridian::rebase(0x00417C90))(a0, a1, a2); }
  // 0x00418AF0  conf=0.85  ?StartSwapPlatform@platform_puzzle@@AAEXXZ
  using StartSwapPlatform_t = void (__thiscall*)(::platform_puzzle *);
  inline void StartSwapPlatform(::platform_puzzle * a0) { reinterpret_cast<StartSwapPlatform_t>(meridian::rebase(0x00418AF0))(a0); }
  // 0x004188D0  conf=0.778  ?TestPlatformPosition@platform_puzzle@@AAEHH@Z
  using TestPlatformPosition_t = int (__thiscall*)(::platform_puzzle *, int);
  inline int TestPlatformPosition(::platform_puzzle * a0, int a1) { return reinterpret_cast<TestPlatformPosition_t>(meridian::rebase(0x004188D0))(a0, a1); }
  // 0x005AA780  conf=0.75  ?Unselect@platform_puzzle@@AAEXXZ
  using Unselect_t = void (__thiscall*)(::platform_puzzle *);
  inline void Unselect(::platform_puzzle * a0) { reinterpret_cast<Unselect_t>(meridian::rebase(0x005AA780))(a0); }
} // platform_puzzle_

// ===== play_surface =====  (7 functions)  ->  namespace play_surface_
namespace play_surface_ {
  // 0x004B4720  conf=0.85  ?EnumerateProperties@play_surface@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::play_surface *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::play_surface * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004B4720))(a0, a1); }
  // 0x004B42C0  conf=0.97  ?OnExport@play_surface@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::play_surface *, ::bin_out *);
  inline void OnExport(::play_surface * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004B42C0))(a0, a1); }
  // 0x004B4340  conf=0.97  ?OnImport@play_surface@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::play_surface *, ::bin_in *);
  inline void OnImport(::play_surface * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004B4340))(a0, a1); }
  // 0x004B3FB0  conf=0.75  ?OnKill@play_surface@@UAEXXZ
  using OnKill_t = void (__thiscall*)(::play_surface *);
  inline void OnKill(::play_surface * a0) { reinterpret_cast<OnKill_t>(meridian::rebase(0x004B3FB0))(a0); }
  // 0x004B4270  conf=0.75  ?SetResourceName@play_surface@@UAEXPBD@Z
  using SetResourceName_t = void (__thiscall*)(::play_surface *, char *);
  inline void SetResourceName(::play_surface * a0, char * a1) { reinterpret_cast<SetResourceName_t>(meridian::rebase(0x004B4270))(a0, a1); }
  // 0x004B49B0  conf=0.739  ?UpdateBBox@play_surface@@QAEXXZ
  using UpdateBBox_t = void (__thiscall*)(::play_surface *);
  inline void UpdateBBox(::play_surface * a0) { reinterpret_cast<UpdateBBox_t>(meridian::rebase(0x004B49B0))(a0); }
  // 0x004B3D80  conf=0.749  ??0play_surface@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::play_surface *);
  inline undefined ctor(::play_surface * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004B3D80))(a0); }
} // play_surface_

// ===== pool =====  (1 functions)  ->  namespace pool_
namespace pool_ {
  // 0x00567080  conf=0.97  ?AllocBlock@?$pool@VGoalAction@@@@EAEPAXXZ
  inline void* AllocBlock_at() { return meridian::rebase(0x00567080); } // void * __thiscall AllocBlock(pool<GoalAction> *)
} // pool_

// ===== pool_implementation =====  (1 functions)  ->  namespace pool_implementation_
namespace pool_implementation_ {
  // 0x005C9580  conf=0.729  ?SortBlocks@pool_implementation@@IAEXXZ
  using SortBlocks_t = void (__thiscall*)(::pool_implementation *);
  inline void SortBlocks(::pool_implementation * a0) { reinterpret_cast<SortBlocks_t>(meridian::rebase(0x005C9580))(a0); }
} // pool_implementation_

// ===== prop =====  (4 functions)  ->  namespace prop_
namespace prop_ {
  // 0x004B89F0  conf=0.747  ?Init@prop@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::prop *, ::vector3 *, ::radian3 *, ::vector3 *, ::bbox *);
  inline void Init(::prop * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3, ::bbox * a4) { reinterpret_cast<Init_t>(meridian::rebase(0x004B89F0))(a0, a1, a2, a3, a4); }
  // 0x004B9230  conf=0.741  ?InitSwoosh@prop@@QAEXEEUxcolor@@PBD@Z
  inline void* InitSwoosh_at() { return meridian::rebase(0x004B9230); } // void __thiscall InitSwoosh(prop *, uchar, uchar, xcolor, char *)
  // 0x004B9290  conf=0.75  ?PropUpdateBBox@prop@@QAEXXZ
  using PropUpdateBBox_t = void (__thiscall*)(::prop *);
  inline void PropUpdateBBox(::prop * a0) { reinterpret_cast<PropUpdateBBox_t>(meridian::rebase(0x004B9290))(a0); }
  // 0x004AAC20  conf=0.75  ?SetSwoosh@prop@@QAEXH@Z
  using SetSwoosh_t = void (__thiscall*)(::prop *, int);
  inline void SetSwoosh(::prop * a0, int a1) { reinterpret_cast<SetSwoosh_t>(meridian::rebase(0x004AAC20))(a0, a1); }
} // prop_

// ===== property =====  (1 functions)  ->  namespace property_
namespace property_ {
  // 0x004AA040  conf=0.75  ??0property@@QAE@ABU0@@Z
  using ctor_t = undefined (__thiscall*)(::property *, ::property *);
  inline undefined ctor(::property * a0, ::property * a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004AA040))(a0, a1); }
} // property_

// ===== push_box =====  (24 functions)  ->  namespace push_box_
namespace push_box_ {
  // 0x004BD710  conf=0.97  ?AdvanceFlip@push_box@@IAEXM@Z
  using AdvanceFlip_t = void (__thiscall*)(::push_box *, float);
  inline void AdvanceFlip(::push_box * a0, float a1) { reinterpret_cast<AdvanceFlip_t>(meridian::rebase(0x004BD710))(a0, a1); }
  // 0x004BA6F0  conf=0.781  ?AutoDetach@push_box@@QAEXXZ
  using AutoDetach_t = void (__thiscall*)(::push_box *);
  inline void AutoDetach(::push_box * a0) { reinterpret_cast<AutoDetach_t>(meridian::rebase(0x004BA6F0))(a0); }
  // 0x004BF630  conf=0.97  ?CreateDust@push_box@@QAEXXZ
  using CreateDust_t = void (__thiscall*)(::push_box *);
  inline void CreateDust(::push_box * a0) { reinterpret_cast<CreateDust_t>(meridian::rebase(0x004BF630))(a0); }
  // 0x004BF9D0  conf=0.75  ?FindDropPoint@push_box@@AAEHAAUvector3@@ABU2@H@Z
  using FindDropPoint_t = int (__thiscall*)(::push_box *, ::vector3 *, ::vector3 *, int);
  inline int FindDropPoint(::push_box * a0, ::vector3 * a1, ::vector3 * a2, int a3) { return reinterpret_cast<FindDropPoint_t>(meridian::rebase(0x004BF9D0))(a0, a1, a2, a3); }
  // 0x004BF9F0  conf=0.775  ?FindDropPoint@push_box@@AAEHAAUvector3@@ABU2@1H@Z
  using FindDropPoint_4BF9F0_t = int (__thiscall*)(::push_box *, ::vector3 *, ::vector3 *, ::vector3 *, int);
  inline int FindDropPoint_4BF9F0(::push_box * a0, ::vector3 * a1, ::vector3 * a2, ::vector3 * a3, int a4) { return reinterpret_cast<FindDropPoint_4BF9F0_t>(meridian::rebase(0x004BF9F0))(a0, a1, a2, a3, a4); }
  // 0x004BEA50  conf=0.79  ?FindGround@push_box@@QAEHABUvector3@@@Z
  using FindGround_t = int (__thiscall*)(::push_box *, ::vector3 *);
  inline int FindGround(::push_box * a0, ::vector3 * a1) { return reinterpret_cast<FindGround_t>(meridian::rebase(0x004BEA50))(a0, a1); }
  // 0x004BEBF0  conf=0.75  ?FindGround@push_box@@QAEHXZ
  using FindGround_4BEBF0_t = int (__thiscall*)(::push_box *);
  inline int FindGround_4BEBF0(::push_box * a0) { return reinterpret_cast<FindGround_4BEBF0_t>(meridian::rebase(0x004BEBF0))(a0); }
  // 0x004BB370  conf=0.789  ?GetBlockPosOrient@push_box@@AAEHABUvector3@@AAU2@AAUradian3@@AA_KMMH@Z
  using GetBlockPosOrient_t = int (__thiscall*)(::push_box *, ::vector3 *, ::vector3 *, ::radian3 *, __uint64 *, float, float, int);
  inline int GetBlockPosOrient(::push_box * a0, ::vector3 * a1, ::vector3 * a2, ::radian3 * a3, __uint64 * a4, float a5, float a6, int a7) { return reinterpret_cast<GetBlockPosOrient_t>(meridian::rebase(0x004BB370))(a0, a1, a2, a3, a4, a5, a6, a7); }
  // 0x004B9DF0  conf=0.798  ?GetCursorCell@push_box@@QAEXABUvector3@@QAUvector2@@M@Z
  using GetCursorCell_t = void (__thiscall*)(::push_box *, ::vector3 *, ::vector2 *, float);
  inline void GetCursorCell(::push_box * a0, ::vector3 * a1, ::vector2 * a2, float a3) { reinterpret_cast<GetCursorCell_t>(meridian::rebase(0x004B9DF0))(a0, a1, a2, a3); }
  // 0x004BF200  conf=0.799  ?GetFrontSpheres@push_box@@AAEHABUvector3@@PAU2@MM0@Z
  using GetFrontSpheres_t = int (__thiscall*)(::push_box *, ::vector3 *, ::vector3 *, float, float, ::vector3 *);
  inline int GetFrontSpheres(::push_box * a0, ::vector3 * a1, ::vector3 * a2, float a3, float a4, ::vector3 * a5) { return reinterpret_cast<GetFrontSpheres_t>(meridian::rebase(0x004BF200))(a0, a1, a2, a3, a4, a5); }
  // 0x004BC630  conf=0.629  ?GetNextCursor@push_box@@AAEHW4cursor_direction@1@AAUvector3@@ABU3@@Z
  inline void* GetNextCursor_at() { return meridian::rebase(0x004BC630); } // int __thiscall GetNextCursor(push_box *, cursor_direction, vector3 *, vector3 *)
  // 0x004BE9B0  conf=0.686  ?GetStackHeight@push_box@@IAEHH@Z
  using GetStackHeight_t = int (__thiscall*)(::push_box *, int);
  inline int GetStackHeight(::push_box * a0, int a1) { return reinterpret_cast<GetStackHeight_t>(meridian::rebase(0x004BE9B0))(a0, a1); }
  // 0x004BBCC0  conf=0.783  ?HandleMove@push_box@@QAEXAAUvector3@@ABU2@@Z
  using HandleMove_t = void (__thiscall*)(::push_box *, ::vector3 *, ::vector3 *);
  inline void HandleMove(::push_box * a0, ::vector3 * a1, ::vector3 * a2) { reinterpret_cast<HandleMove_t>(meridian::rebase(0x004BBCC0))(a0, a1, a2); }
  // 0x004BA6E0  conf=0.75  ?IsAttached@push_box@@QAEHXZ
  using IsAttached_t = int (__thiscall*)(::push_box *);
  inline int IsAttached(::push_box * a0) { return reinterpret_cast<IsAttached_t>(meridian::rebase(0x004BA6E0))(a0); }
  // 0x004BA710  conf=0.756  ?OnAdvanceLogic@push_box@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::push_box *, float);
  inline void OnAdvanceLogic(::push_box * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004BA710))(a0, a1); }
  // 0x004BB0D0  conf=0.85  ?OnExport@push_box@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::push_box *, ::bin_out *);
  inline void OnExport(::push_box * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004BB0D0))(a0, a1); }
  // 0x004BB140  conf=0.844  ?OnImport@push_box@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::push_box *, ::bin_in *);
  inline void OnImport(::push_box * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004BB140))(a0, a1); }
  // 0x004B9A50  conf=0.796  ?OnReset@push_box@@UAEXXZ
  using OnReset_t = void (__thiscall*)(::push_box *);
  inline void OnReset(::push_box * a0) { reinterpret_cast<OnReset_t>(meridian::rebase(0x004B9A50))(a0); }
  // 0x004BBA30  conf=0.747  ?SetupCollision@push_box@@AAEH_KABUvector3@@1IAAUcollision@collision_mgr@@@Z
  using SetupCollision_t = int (__thiscall*)(::push_box *, __uint64, ::vector3 *, ::vector3 *, uint, ::collision *);
  inline int SetupCollision(::push_box * a0, __uint64 a1, ::vector3 * a2, ::vector3 * a3, uint a4, ::collision * a5) { return reinterpret_cast<SetupCollision_t>(meridian::rebase(0x004BBA30))(a0, a1, a2, a3, a4, a5); }
  // 0x004BD4F0  conf=0.741  ?StartFlip@push_box@@QAEXXZ
  using StartFlip_t = void (__thiscall*)(::push_box *);
  inline void StartFlip(::push_box * a0) { reinterpret_cast<StartFlip_t>(meridian::rebase(0x004BD4F0))(a0); }
  // 0x004BD4C0  conf=0.581  ?StateChangeTo@push_box@@AAEXW4state@1@@Z
  inline void* StateChangeTo_at() { return meridian::rebase(0x004BD4C0); } // void __thiscall StateChangeTo(push_box *, state)
  // 0x004BD3E0  conf=0.729  ?State_Advance@push_box@@AAEXXZ
  using State_Advance_t = void (__thiscall*)(::push_box *);
  inline void State_Advance(::push_box * a0) { reinterpret_cast<State_Advance_t>(meridian::rebase(0x004BD3E0))(a0); }
  // 0x004BE320  conf=0.97  ?State_Advance_FALLING@push_box@@AAEXXZ
  using State_Advance_FALLING_t = void (__thiscall*)(::push_box *);
  inline void State_Advance_FALLING(::push_box * a0) { reinterpret_cast<State_Advance_FALLING_t>(meridian::rebase(0x004BE320))(a0); }
  // 0x004BE800  conf=0.78  ?UpdateStack@push_box@@QAEXABUvector3@@ABUradian3@@H@Z
  using UpdateStack_t = void (__thiscall*)(::push_box *, ::vector3 *, ::radian3 *, int);
  inline void UpdateStack(::push_box * a0, ::vector3 * a1, ::radian3 * a2, int a3) { reinterpret_cast<UpdateStack_t>(meridian::rebase(0x004BE800))(a0, a1, a2, a3); }
} // push_box_

// ===== quaternion =====  (1 functions)  ->  namespace quaternion_
namespace quaternion_ {
  // 0x0053D2D0  conf=0.56  ?GetRotation@quaternion@@QBE?AUradian3@@XZ
  using GetRotation_t = ::radian3 (__thiscall*)(::quaternion *);
  inline ::radian3 GetRotation(::quaternion * a0) { return reinterpret_cast<GetRotation_t>(meridian::rebase(0x0053D2D0))(a0); }
} // quaternion_

// ===== rawanim =====  (1 functions)  ->  namespace rawanim_
namespace rawanim_ {
  // 0x006ABF10  conf=0.97  ?Load@rawanim@@QAEHPBD@Z
  using Load_t = int (__thiscall*)(::rawanim *, char *);
  inline int Load(::rawanim * a0, char * a1) { return reinterpret_cast<Load_t>(meridian::rebase(0x006ABF10))(a0, a1); }
} // rawanim_

// ===== render_mgr =====  (2 functions)  ->  namespace render_mgr_
namespace render_mgr_ {
  // 0x00587FC0  conf=0.97  ?EnableFog@render_mgr@@QAEXW4fogmode@1@@Z
  inline void* EnableFog_at() { return meridian::rebase(0x00587FC0); } // void __thiscall EnableFog(render_mgr *, fogmode)
  // 0x00586FF0  conf=0.787  ?RenderStingGlow@render_mgr@@AAEXXZ
  using RenderStingGlow_t = void (__thiscall*)(::render_mgr *);
  inline void RenderStingGlow(::render_mgr * a0) { reinterpret_cast<RenderStingGlow_t>(meridian::rebase(0x00586FF0))(a0); }
} // render_mgr_

// ===== rigid_instance =====  (38 functions)  ->  namespace rigid_instance_
namespace rigid_instance_ {
  // 0x004C0E10  conf=0.764  ?AdvanceAnim@rigid_instance@@QAEXM@Z
  using AdvanceAnim_t = void (__thiscall*)(::rigid_instance *, float);
  inline void AdvanceAnim(::rigid_instance * a0, float a1) { reinterpret_cast<AdvanceAnim_t>(meridian::rebase(0x004C0E10))(a0, a1); }
  // 0x004C1750  conf=0.779  ?AdvanceDestruct@rigid_instance@@QAEXM@Z
  using AdvanceDestruct_t = void (__thiscall*)(::rigid_instance *, float);
  inline void AdvanceDestruct(::rigid_instance * a0, float a1) { reinterpret_cast<AdvanceDestruct_t>(meridian::rebase(0x004C1750))(a0, a1); }
  // 0x004C14A0  conf=0.709  ?AdvanceFloat@rigid_instance@@QAEXM@Z
  using AdvanceFloat_t = void (__thiscall*)(::rigid_instance *, float);
  inline void AdvanceFloat(::rigid_instance * a0, float a1) { reinterpret_cast<AdvanceFloat_t>(meridian::rebase(0x004C14A0))(a0, a1); }
  // 0x004C71A0  conf=0.682  ?AnimDataAvailable@rigid_instance@@QAEHXZ
  using AnimDataAvailable_t = int (__thiscall*)(::rigid_instance *);
  inline int AnimDataAvailable(::rigid_instance * a0) { return reinterpret_cast<AnimDataAvailable_t>(meridian::rebase(0x004C71A0))(a0); }
  // 0x004C73D0  conf=0.75  ?ClearAnimData@rigid_instance@@QAEXXZ
  using ClearAnimData_t = void (__thiscall*)(::rigid_instance *);
  inline void ClearAnimData(::rigid_instance * a0) { reinterpret_cast<ClearAnimData_t>(meridian::rebase(0x004C73D0))(a0); }
  // 0x004C7820  conf=0.731  ?DetectAnimEvent@rigid_instance@@QAEHHAAUvector3@@@Z
  using DetectAnimEvent_t = int (__thiscall*)(::rigid_instance *, int, ::vector3 *);
  inline int DetectAnimEvent(::rigid_instance * a0, int a1, ::vector3 * a2) { return reinterpret_cast<DetectAnimEvent_t>(meridian::rebase(0x004C7820))(a0, a1, a2); }
  // 0x004C3F80  conf=0.97  ?EnumerateProperties@rigid_instance@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::rigid_instance *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::rigid_instance * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004C3F80))(a0, a1); }
  // 0x004C7460  conf=0.737  ?GetAnimGroup@rigid_instance@@QAEPBVanim_group@@XZ
  using GetAnimGroup_t = ::anim_group * (__thiscall*)(::rigid_instance *);
  inline ::anim_group * GetAnimGroup(::rigid_instance * a0) { return reinterpret_cast<GetAnimGroup_t>(meridian::rebase(0x004C7460))(a0); }
  // 0x004C74B0  conf=0.75  ?GetAnimPlayer@rigid_instance@@QAEPBVsimple_anim_player@@XZ
  using GetAnimPlayer_t = ::simple_anim_player * (__thiscall*)(::rigid_instance *);
  inline ::simple_anim_player * GetAnimPlayer(::rigid_instance * a0) { return reinterpret_cast<GetAnimPlayer_t>(meridian::rebase(0x004C74B0))(a0); }
  // 0x004C7170  conf=0.637  ?GetAnimResourceName@rigid_instance@@QAEPBDXZ
  using GetAnimResourceName_t = char * (__thiscall*)(::rigid_instance *);
  inline char * GetAnimResourceName(::rigid_instance * a0) { return reinterpret_cast<GetAnimResourceName_t>(meridian::rebase(0x004C7170))(a0); }
  // 0x004C5BA0  conf=0.9  ?GetProperty@rigid_instance@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::rigid_instance *, char *);
  inline ::property GetProperty(::rigid_instance * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004C5BA0))(a0, a1); }
  // 0x004C08B0  conf=0.79  ?Init@rigid_instance@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@Uxcolor@@HHHHHHH@Z
  inline void* Init_at() { return meridian::rebase(0x004C08B0); } // void __thiscall Init(rigid_instance *, vector3 *, radian3 *, vector3 *, bbox *, xcolor, int, int, int, int, int, int, int)
  // 0x004C3500  conf=0.757  ?InvalidatePolyCache@rigid_instance@@QAEXABUbbox@@H@Z
  using InvalidatePolyCache_t = void (__thiscall*)(::rigid_instance *, ::bbox *, int);
  inline void InvalidatePolyCache(::rigid_instance * a0, ::bbox * a1, int a2) { reinterpret_cast<InvalidatePolyCache_t>(meridian::rebase(0x004C3500))(a0, a1, a2); }
  // 0x004C7410  conf=0.772  ?IsAtEndOfAnim@rigid_instance@@QAEHXZ
  using IsAtEndOfAnim_t = int (__thiscall*)(::rigid_instance *);
  inline int IsAtEndOfAnim(::rigid_instance * a0) { return reinterpret_cast<IsAtEndOfAnim_t>(meridian::rebase(0x004C7410))(a0); }
  // 0x004C36F0  conf=0.8  ?Move@rigid_instance@@UAEXABUvector3@@H@Z
  using Move_t = void (__thiscall*)(::rigid_instance *, ::vector3 *, int);
  inline void Move(::rigid_instance * a0, ::vector3 * a1, int a2) { reinterpret_cast<Move_t>(meridian::rebase(0x004C36F0))(a0, a1, a2); }
  // 0x004C3760  conf=0.796  ?MoveAndUpdate@rigid_instance@@UAEXABUvector3@@ABUradian3@@@Z
  using MoveAndUpdate_t = void (__thiscall*)(::rigid_instance *, ::vector3 *, ::radian3 *);
  inline void MoveAndUpdate(::rigid_instance * a0, ::vector3 * a1, ::radian3 * a2) { reinterpret_cast<MoveAndUpdate_t>(meridian::rebase(0x004C3760))(a0, a1, a2); }
  // 0x004C0CE0  conf=0.767  ?OnAdvanceLogic@rigid_instance@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::rigid_instance *, float);
  inline void OnAdvanceLogic(::rigid_instance * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004C0CE0))(a0, a1); }
  // 0x004C1FF0  conf=0.9  ?OnExport@rigid_instance@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::rigid_instance *, ::bin_out *);
  inline void OnExport(::rigid_instance * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004C1FF0))(a0, a1); }
  // 0x004C2430  conf=0.9  ?OnImport@rigid_instance@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::rigid_instance *, ::bin_in *);
  inline void OnImport(::rigid_instance * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004C2430))(a0, a1); }
  // 0x004C0A40  conf=0.758  ?OnInit@rigid_instance@@UAEXXZ
  using OnInit_t = void (__thiscall*)(::rigid_instance *);
  inline void OnInit(::rigid_instance * a0) { reinterpret_cast<OnInit_t>(meridian::rebase(0x004C0A40))(a0); }
  // 0x004C7C60  conf=0.8  ?OnNotifyFireForgetComplete@rigid_instance@@QAEXXZ
  using OnNotifyFireForgetComplete_t = void (__thiscall*)(::rigid_instance *);
  inline void OnNotifyFireForgetComplete(::rigid_instance * a0) { reinterpret_cast<OnNotifyFireForgetComplete_t>(meridian::rebase(0x004C7C60))(a0); }
  // 0x004C3BC0  conf=0.741  ?OnRotate@rigid_instance@@UAEXABUradian3@@@Z
  using OnRotate_t = void (__thiscall*)(::rigid_instance *, ::radian3 *);
  inline void OnRotate(::rigid_instance * a0, ::radian3 * a1) { reinterpret_cast<OnRotate_t>(meridian::rebase(0x004C3BC0))(a0, a1); }
  // 0x004C3200  conf=0.754  ?RenderCollision@rigid_instance@@UAEXXZ
  using RenderCollision_t = void (__thiscall*)(::rigid_instance *);
  inline void RenderCollision(::rigid_instance * a0) { reinterpret_cast<RenderCollision_t>(meridian::rebase(0x004C3200))(a0); }
  // 0x004C75F0  conf=0.728  ?ResetAnimFrame@rigid_instance@@QAEXH@Z
  using ResetAnimFrame_t = void (__thiscall*)(::rigid_instance *, int);
  inline void ResetAnimFrame(::rigid_instance * a0, int a1) { reinterpret_cast<ResetAnimFrame_t>(meridian::rebase(0x004C75F0))(a0, a1); }
  // 0x004C6F40  conf=0.795  ?SetAnim@rigid_instance@@QAEHPBD@Z
  using SetAnim_t = int (__thiscall*)(::rigid_instance *, char *);
  inline int SetAnim(::rigid_instance * a0, char * a1) { return reinterpret_cast<SetAnim_t>(meridian::rebase(0x004C6F40))(a0, a1); }
  // 0x004C7520  conf=0.716  ?SetAnimByIndex@rigid_instance@@QAEHH@Z
  using SetAnimByIndex_t = int (__thiscall*)(::rigid_instance *, int);
  inline int SetAnimByIndex(::rigid_instance * a0, int a1) { return reinterpret_cast<SetAnimByIndex_t>(meridian::rebase(0x004C7520))(a0, a1); }
  // 0x004C7580  conf=0.779  ?SetAnimFrame@rigid_instance@@QAEXM@Z
  using SetAnimFrame_t = void (__thiscall*)(::rigid_instance *, float);
  inline void SetAnimFrame(::rigid_instance * a0, float a1) { reinterpret_cast<SetAnimFrame_t>(meridian::rebase(0x004C7580))(a0, a1); }
  // 0x004C7010  conf=0.738  ?SetAnimResourceName@rigid_instance@@QAEXPBD@Z
  using SetAnimResourceName_t = void (__thiscall*)(::rigid_instance *, char *);
  inline void SetAnimResourceName(::rigid_instance * a0, char * a1) { reinterpret_cast<SetAnimResourceName_t>(meridian::rebase(0x004C7010))(a0, a1); }
  // 0x00412510  conf=0.734  ?SetAnimSpeed@rigid_instance@@QAEXM@Z
  using SetAnimSpeed_t = void (__thiscall*)(::rigid_instance *, float);
  inline void SetAnimSpeed(::rigid_instance * a0, float a1) { reinterpret_cast<SetAnimSpeed_t>(meridian::rebase(0x00412510))(a0, a1); }
  // 0x004C2F60  conf=0.796  ?SetDestructState@rigid_instance@@QAEXHH@Z
  using SetDestructState_t = void (__thiscall*)(::rigid_instance *, int, int);
  inline void SetDestructState(::rigid_instance * a0, int a1, int a2) { reinterpret_cast<SetDestructState_t>(meridian::rebase(0x004C2F60))(a0, a1, a2); }
  // 0x004C74F0  conf=0.604  ?SetLoopDelay@rigid_instance@@QAEXM@Z
  using SetLoopDelay_t = void (__thiscall*)(::rigid_instance *, float);
  inline void SetLoopDelay(::rigid_instance * a0, float a1) { reinterpret_cast<SetLoopDelay_t>(meridian::rebase(0x004C74F0))(a0, a1); }
  // 0x004C74D0  conf=0.677  ?SetLooping@rigid_instance@@QAEXH@Z
  using SetLooping_t = void (__thiscall*)(::rigid_instance *, int);
  inline void SetLooping(::rigid_instance * a0, int a1) { reinterpret_cast<SetLooping_t>(meridian::rebase(0x004C74D0))(a0, a1); }
  // 0x004C49A0  conf=0.9  ?SetProperty@rigid_instance@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::rigid_instance *, char *, ::property *);
  inline int SetProperty(::rigid_instance * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004C49A0))(a0, a1, a2); }
  // 0x004C7C80  conf=0.723  ?SetupPlant@rigid_instance@@QAEXPBD0@Z
  using SetupPlant_t = void (__thiscall*)(::rigid_instance *, char *, char *);
  inline void SetupPlant(::rigid_instance * a0, char * a1, char * a2) { reinterpret_cast<SetupPlant_t>(meridian::rebase(0x004C7C80))(a0, a1, a2); }
  // 0x004C3D20  conf=0.766  ?UpdateBBoxAndMove@rigid_instance@@UAEXXZ
  using UpdateBBoxAndMove_t = void (__thiscall*)(::rigid_instance *);
  inline void UpdateBBoxAndMove(::rigid_instance * a0) { reinterpret_cast<UpdateBBoxAndMove_t>(meridian::rebase(0x004C3D20))(a0); }
  // 0x004C7930  conf=0.581  ?UpdateDoNotAdvanceLogicFlag@rigid_instance@@QAEXXZ
  using UpdateDoNotAdvanceLogicFlag_t = void (__thiscall*)(::rigid_instance *);
  inline void UpdateDoNotAdvanceLogicFlag(::rigid_instance * a0) { reinterpret_cast<UpdateDoNotAdvanceLogicFlag_t>(meridian::rebase(0x004C7930))(a0); }
  // 0x004C7960  conf=0.726  ?WigglePlant@rigid_instance@@QAEXXZ
  using WigglePlant_t = void (__thiscall*)(::rigid_instance *);
  inline void WigglePlant(::rigid_instance * a0) { reinterpret_cast<WigglePlant_t>(meridian::rebase(0x004C7960))(a0); }
  // 0x004C0370  conf=0.731  ??0rigid_instance@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::rigid_instance *);
  inline undefined ctor(::rigid_instance * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004C0370))(a0); }
} // rigid_instance_

// ===== rope =====  (24 functions)  ->  namespace rope_
namespace rope_ {
  // 0x004C89C0  conf=0.793  ?ApplyVelocity@rope@@QAEXABUvector3@@H@Z
  using ApplyVelocity_t = void (__thiscall*)(::rope *, ::vector3 *, int);
  inline void ApplyVelocity(::rope * a0, ::vector3 * a1, int a2) { reinterpret_cast<ApplyVelocity_t>(meridian::rebase(0x004C89C0))(a0, a1, a2); }
  // 0x004CB990  conf=0.787  ?AttachToObject@rope@@QAEXXZ
  using AttachToObject_t = void (__thiscall*)(::rope *);
  inline void AttachToObject(::rope * a0) { reinterpret_cast<AttachToObject_t>(meridian::rebase(0x004CB990))(a0); }
  // 0x004C88F0  conf=0.743  ?Clear@rope@@QAEXXZ
  using Clear_t = void (__thiscall*)(::rope *);
  inline void Clear(::rope * a0) { reinterpret_cast<Clear_t>(meridian::rebase(0x004C88F0))(a0); }
  // 0x004C8C80  conf=0.716  ?ComputeTextureV@rope@@AAEXXZ
  using ComputeTextureV_t = void (__thiscall*)(::rope *);
  inline void ComputeTextureV(::rope * a0) { reinterpret_cast<ComputeTextureV_t>(meridian::rebase(0x004C8C80))(a0); }
  // 0x004CBB50  conf=0.9  ?EnumerateProperties@rope@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::rope *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::rope * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004CBB50))(a0, a1); }
  // 0x004CB020  conf=0.755  ?GetHostPosition@rope@@QAE?AUvector3@@XZ
  using GetHostPosition_t = ::vector3 (__thiscall*)(::rope *);
  inline ::vector3 GetHostPosition(::rope * a0) { return reinterpret_cast<GetHostPosition_t>(meridian::rebase(0x004CB020))(a0); }
  // 0x004C8990  conf=0.8  ?GetPointPos@rope@@QAE?AUvector3@@H@Z
  using GetPointPos_t = ::vector3 (__thiscall*)(::rope *, int);
  inline ::vector3 GetPointPos(::rope * a0, int a1) { return reinterpret_cast<GetPointPos_t>(meridian::rebase(0x004C8990))(a0, a1); }
  // 0x004CAFF0  conf=0.737  ?IsGrabbable@rope@@QAEHXZ
  using IsGrabbable_t = int (__thiscall*)(::rope *);
  inline int IsGrabbable(::rope * a0) { return reinterpret_cast<IsGrabbable_t>(meridian::rebase(0x004CAFF0))(a0); }
  // 0x004C8960  conf=0.75  ?IsVertical@rope@@QAEHXZ
  using IsVertical_t = int (__thiscall*)(::rope *);
  inline int IsVertical(::rope * a0) { return reinterpret_cast<IsVertical_t>(meridian::rebase(0x004C8960))(a0); }
  // 0x004CB390  conf=0.764  ?OnAdvanceLogic@rope@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::rope *, float);
  inline void OnAdvanceLogic(::rope * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004CB390))(a0, a1); }
  // 0x004CA940  conf=0.85  ?OnImport@rope@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::rope *, ::bin_in *);
  inline void OnImport(::rope * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004CA940))(a0, a1); }
  // 0x004C7EB0  conf=0.75  ?OnObjectActivate@rope@@UAEXXZ
  using OnObjectActivate_t = void (__thiscall*)(::rope *);
  inline void OnObjectActivate(::rope * a0) { reinterpret_cast<OnObjectActivate_t>(meridian::rebase(0x004C7EB0))(a0); }
  // 0x004C7ED0  conf=0.75  ?OnObjectDeactivate@rope@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::rope *);
  inline void OnObjectDeactivate(::rope * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004C7ED0))(a0); }
  // 0x004C9510  conf=0.97  ?RenderCustomDebug@rope@@UAEXXZ
  using RenderCustomDebug_t = void (__thiscall*)(::rope *);
  inline void RenderCustomDebug(::rope * a0) { reinterpret_cast<RenderCustomDebug_t>(meridian::rebase(0x004C9510))(a0); }
  // 0x004C9290  conf=0.712  ?Reset@rope@@AAEXH@Z
  using Reset_t = void (__thiscall*)(::rope *, int);
  inline void Reset(::rope * a0, int a1) { reinterpret_cast<Reset_t>(meridian::rebase(0x004C9290))(a0, a1); }
  // 0x004C8CD0  conf=0.739  ?RespawnAfterFallaway@rope@@AAEXXZ
  using RespawnAfterFallaway_t = void (__thiscall*)(::rope *);
  inline void RespawnAfterFallaway(::rope * a0) { reinterpret_cast<RespawnAfterFallaway_t>(meridian::rebase(0x004C8CD0))(a0); }
  // 0x004C7F80  conf=0.97  ?RunLogic@rope@@AAEXXZ
  using RunLogic_t = void (__thiscall*)(::rope *);
  inline void RunLogic(::rope * a0) { reinterpret_cast<RunLogic_t>(meridian::rebase(0x004C7F80))(a0); }
  // 0x004C8770  conf=0.68  ?SetHoldingWeight@rope@@QAEXH@Z
  using SetHoldingWeight_t = void (__thiscall*)(::rope *, int);
  inline void SetHoldingWeight(::rope * a0, int a1) { reinterpret_cast<SetHoldingWeight_t>(meridian::rebase(0x004C8770))(a0, a1); }
  // 0x004CC200  conf=0.97  ?SetProperty@rope@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::rope *, char *, ::property *);
  inline int SetProperty(::rope * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004CC200))(a0, a1, a2); }
  // 0x004C8DD0  conf=0.97  ?ShrinkAndGrow@rope@@AAEXH@Z
  using ShrinkAndGrow_t = void (__thiscall*)(::rope *, int);
  inline void ShrinkAndGrow(::rope * a0, int a1) { reinterpret_cast<ShrinkAndGrow_t>(meridian::rebase(0x004C8DD0))(a0, a1); }
  // 0x004CB4A0  conf=0.795  ?Simulate@rope@@AAEXXZ
  using Simulate_t = void (__thiscall*)(::rope *);
  inline void Simulate(::rope * a0) { reinterpret_cast<Simulate_t>(meridian::rebase(0x004CB4A0))(a0); }
  // 0x004C8A20  conf=0.75  ?UpdateAnchorPos@rope@@AAEXXZ
  using UpdateAnchorPos_t = void (__thiscall*)(::rope *);
  inline void UpdateAnchorPos(::rope * a0) { reinterpret_cast<UpdateAnchorPos_t>(meridian::rebase(0x004C8A20))(a0); }
  // 0x004C8AA0  conf=0.782  ?UpdateBBox@rope@@AAEXXZ
  using UpdateBBox_t = void (__thiscall*)(::rope *);
  inline void UpdateBBox(::rope * a0) { reinterpret_cast<UpdateBBox_t>(meridian::rebase(0x004C8AA0))(a0); }
  // 0x004C8460  conf=0.85  ??0rope@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::rope *);
  inline undefined ctor(::rope * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004C8460))(a0); }
} // rope_

// ===== rsc_mgr =====  (3 functions)  ->  namespace rsc_mgr_
namespace rsc_mgr_ {
  // 0x004258D0  conf=0.741  ?DelRHandle@rsc_mgr@@AAEXAAVrhandle@@@Z
  using DelRHandle_t = void (__thiscall*)(::rsc_mgr *, ::rhandle *);
  inline void DelRHandle(::rsc_mgr * a0, ::rhandle * a1) { reinterpret_cast<DelRHandle_t>(meridian::rebase(0x004258D0))(a0, a1); }
  // 0x00549D80  conf=0.97  ?FixupFilename@rsc_mgr@@QAEPBDPBD0@Z
  using FixupFilename_t = char * (__thiscall*)(::rsc_mgr *, char *, char *);
  inline char * FixupFilename(::rsc_mgr * a0, char * a1, char * a2) { return reinterpret_cast<FixupFilename_t>(meridian::rebase(0x00549D80))(a0, a1, a2); }
  // 0x00549C40  conf=0.97  ?SetOnDemandLoading@rsc_mgr@@QAEXH@Z
  using SetOnDemandLoading_t = void (__thiscall*)(::rsc_mgr *, int);
  inline void SetOnDemandLoading(::rsc_mgr * a0, int a1) { reinterpret_cast<SetOnDemandLoading_t>(meridian::rebase(0x00549C40))(a0, a1); }
} // rsc_mgr_

// ===== save_mgr =====  (2 functions)  ->  namespace save_mgr_
namespace save_mgr_ {
  // 0x005905F0  conf=0.75  ?Export@save_mgr@@QAEXAAPADAAH@Z
  using Export_t = void (__thiscall*)(::save_mgr *, char * *, int *);
  inline void Export(::save_mgr * a0, char * * a1, int * a2) { reinterpret_cast<Export_t>(meridian::rebase(0x005905F0))(a0, a1, a2); }
  // 0x0058EE10  conf=0.66  ?Import@save_mgr@@QAEXPAD@Z
  using Import_t = void (__thiscall*)(::save_mgr *, char *);
  inline void Import(::save_mgr * a0, char * a1) { reinterpret_cast<Import_t>(meridian::rebase(0x0058EE10))(a0, a1); }
} // save_mgr_

// ===== save_pedestal =====  (4 functions)  ->  namespace save_pedestal_
namespace save_pedestal_ {
  // 0x004CDAA0  conf=0.757  ?OnAdvanceLogic@save_pedestal@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::save_pedestal *, float);
  inline void OnAdvanceLogic(::save_pedestal * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004CDAA0))(a0, a1); }
  // 0x004D4300  conf=0.75  ?OnObjectDeactivate@save_pedestal@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::save_pedestal *);
  inline void OnObjectDeactivate(::save_pedestal * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004D4300))(a0); }
  // 0x004CDA30  conf=0.75  ?SavePoint@save_pedestal@@QAEXABUvector3@@M@Z
  using SavePoint_t = void (__thiscall*)(::save_pedestal *, ::vector3 *, float);
  inline void SavePoint(::save_pedestal * a0, ::vector3 * a1, float a2) { reinterpret_cast<SavePoint_t>(meridian::rebase(0x004CDA30))(a0, a1, a2); }
  // 0x004CD880  conf=0.717  ?SetAura@save_pedestal@@QAEXH@Z
  using SetAura_t = void (__thiscall*)(::save_pedestal *, int);
  inline void SetAura(::save_pedestal * a0, int a1) { reinterpret_cast<SetAura_t>(meridian::rebase(0x004CD880))(a0, a1); }
} // save_pedestal_

// ===== selset =====  (1 functions)  ->  namespace selset_
namespace selset_ {
  // 0x00588910  conf=0.695  ?ResizeNodes@@YAXH@Z
  using ResizeNodes_t = void (__cdecl*)(int);
  inline void ResizeNodes(int a0) { reinterpret_cast<ResizeNodes_t>(meridian::rebase(0x00588910))(a0); }
} // selset_

// ===== shadow =====  (1 functions)  ->  namespace shadow_
namespace shadow_ {
  // 0x004B51B0  conf=0.85  ??0shadow@Projectile@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::shadow *);
  inline undefined ctor(::shadow * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004B51B0))(a0); }
} // shadow_

// ===== simple_anim_player =====  (2 functions)  ->  namespace simple_anim_player_
namespace simple_anim_player_ {
  // 0x0053C3A0  conf=0.724  ?ComputeBoneL2W@simple_anim_player@@QAEXHAAVmatrix4@@@Z
  using ComputeBoneL2W_t = void (__thiscall*)(::simple_anim_player *, int, ::matrix4 *);
  inline void ComputeBoneL2W(::simple_anim_player * a0, int a1, ::matrix4 * a2) { reinterpret_cast<ComputeBoneL2W_t>(meridian::rebase(0x0053C3A0))(a0, a1, a2); }
  // 0x00406D80  conf=0.732  ?SetAnim@simple_anim_player@@QAEXPBDH@Z
  using SetAnim_t = void (__thiscall*)(::simple_anim_player *, char *, int);
  inline void SetAnim(::simple_anim_player * a0, char * a1, int a2) { reinterpret_cast<SetAnim_t>(meridian::rebase(0x00406D80))(a0, a1, a2); }
} // simple_anim_player_

// ===== skybox =====  (3 functions)  ->  namespace skybox_
namespace skybox_ {
  // 0x004CE0E0  conf=0.797  ?Init@skybox@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::skybox *, ::vector3 *, ::radian3 *, ::vector3 *, ::bbox *);
  inline void Init(::skybox * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3, ::bbox * a4) { reinterpret_cast<Init_t>(meridian::rebase(0x004CE0E0))(a0, a1, a2, a3, a4); }
  // 0x004CE5E0  conf=0.85  ?OnExport@skybox@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::skybox *, ::bin_out *);
  inline void OnExport(::skybox * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004CE5E0))(a0, a1); }
  // 0x004CE630  conf=0.878  ?OnImport@skybox@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::skybox *, ::bin_in *);
  inline void OnImport(::skybox * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004CE630))(a0, a1); }
} // skybox_

// ===== slider =====  (4 functions)  ->  namespace slider_
namespace slider_ {
  // 0x004CEFE0  conf=0.744  ?Init@slider@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::slider *, ::vector3 *, ::radian3 *, ::vector3 *, ::bbox *);
  inline void Init(::slider * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3, ::bbox * a4) { reinterpret_cast<Init_t>(meridian::rebase(0x004CEFE0))(a0, a1, a2, a3, a4); }
  // 0x004CF950  conf=0.85  ?OnExport@slider@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::slider *, ::bin_out *);
  inline void OnExport(::slider * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004CF950))(a0, a1); }
  // 0x004CFA10  conf=0.848  ?OnImport@slider@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::slider *, ::bin_in *);
  inline void OnImport(::slider * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004CFA10))(a0, a1); }
  // 0x00669EF0  conf=0.742  ?Render@slider@@UAEXXZ
  using Render_t = void (__thiscall*)(::slider *);
  inline void Render(::slider * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x00669EF0))(a0); }
} // slider_

// ===== smart_2dsprite =====  (4 functions)  ->  namespace smart_2dsprite_
namespace smart_2dsprite_ {
  // 0x004FA4B0  conf=0.75  ?SetColor@smart_2dsprite@@QAEXABUxcolor@@@Z
  using SetColor_t = void (__thiscall*)(::smart_2dsprite *, ::xcolor *);
  inline void SetColor(::smart_2dsprite * a0, ::xcolor * a1) { reinterpret_cast<SetColor_t>(meridian::rebase(0x004FA4B0))(a0, a1); }
  // 0x004F8D60  conf=0.676  ?SetPosition@smart_2dsprite@@QAEXABUvector2@@@Z
  using SetPosition_t = void (__thiscall*)(::smart_2dsprite *, ::vector2 *);
  inline void SetPosition(::smart_2dsprite * a0, ::vector2 * a1) { reinterpret_cast<SetPosition_t>(meridian::rebase(0x004F8D60))(a0, a1); }
  // 0x004FA3D0  conf=0.739  ?SetTexture@smart_2dsprite@@QAEXPAVxbitmap@@@Z
  using SetTexture_t = void (__thiscall*)(::smart_2dsprite *, ::xbitmap *);
  inline void SetTexture(::smart_2dsprite * a0, ::xbitmap * a1) { reinterpret_cast<SetTexture_t>(meridian::rebase(0x004FA3D0))(a0, a1); }
  // 0x004FA4F0  conf=0.735  ?Update@smart_2dsprite@@QAEXM@Z
  using Update_t = void (__thiscall*)(::smart_2dsprite *, float);
  inline void Update(::smart_2dsprite * a0, float a1) { reinterpret_cast<Update_t>(meridian::rebase(0x004FA4F0))(a0, a1); }
} // smart_2dsprite_

// ===== spatial_dbase =====  (2 functions)  ->  namespace spatial_dbase_
namespace spatial_dbase_ {
  // 0x0058A9F0  conf=0.7  ?AcquireLinks@spatial_dbase@@QAEXABUbbox@@HPAXAAG@Z
  using AcquireLinks_t = void (__thiscall*)(::spatial_dbase *, ::bbox *, int, void *, ushort *);
  inline void AcquireLinks(::spatial_dbase * a0, ::bbox * a1, int a2, void * a3, ushort * a4) { reinterpret_cast<AcquireLinks_t>(meridian::rebase(0x0058A9F0))(a0, a1, a2, a3, a4); }
  // 0x0058A310  conf=0.676  ?Clear@spatial_dbase@@AAEXXZ
  using Clear_t = void (__thiscall*)(::spatial_dbase *);
  inline void Clear(::spatial_dbase * a0) { reinterpret_cast<Clear_t>(meridian::rebase(0x0058A310))(a0); }
} // spatial_dbase_

// ===== special_surfaces =====  (19 functions)  ->  namespace special_surfaces_
namespace special_surfaces_ {
  // 0x004D1CB0  conf=0.747  ?ClearVertBuffer@special_surfaces@@QAEXXZ
  using ClearVertBuffer_t = void (__thiscall*)(::special_surfaces *);
  inline void ClearVertBuffer(::special_surfaces * a0) { reinterpret_cast<ClearVertBuffer_t>(meridian::rebase(0x004D1CB0))(a0); }
  // 0x004D0B40  conf=0.617  ?EnableDecals@special_surfaces@@QAEXH@Z
  using EnableDecals_t = void (__thiscall*)(::special_surfaces *, int);
  inline void EnableDecals(::special_surfaces * a0, int a1) { reinterpret_cast<EnableDecals_t>(meridian::rebase(0x004D0B40))(a0, a1); }
  // 0x004D1180  conf=0.97  ?EnumerateProperties@special_surfaces@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::special_surfaces *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::special_surfaces * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004D1180))(a0, a1); }
  // 0x004D0A50  conf=0.75  ?FreeVertexColor@special_surfaces@@IAEXXZ
  using FreeVertexColor_t = void (__thiscall*)(::special_surfaces *);
  inline void FreeVertexColor(::special_surfaces * a0) { reinterpret_cast<FreeVertexColor_t>(meridian::rebase(0x004D0A50))(a0); }
  // 0x004D1FF0  conf=0.712  ?GetCollisionBBox@special_surfaces@@QAEXAAUbbox@@ABVmatrix4@@@Z
  using GetCollisionBBox_t = void (__thiscall*)(::special_surfaces *, ::bbox *, ::matrix4 *);
  inline void GetCollisionBBox(::special_surfaces * a0, ::bbox * a1, ::matrix4 * a2) { reinterpret_cast<GetCollisionBBox_t>(meridian::rebase(0x004D1FF0))(a0, a1, a2); }
  // 0x004D0B20  conf=0.8  ?GetMeshIndex@special_surfaces@@QAEHPBD@Z
  using GetMeshIndex_t = int (__thiscall*)(::special_surfaces *, char *);
  inline int GetMeshIndex(::special_surfaces * a0, char * a1) { return reinterpret_cast<GetMeshIndex_t>(meridian::rebase(0x004D0B20))(a0, a1); }
  // 0x004D1720  conf=0.896  ?GetProperty@special_surfaces@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::special_surfaces *, char *);
  inline ::property GetProperty(::special_surfaces * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004D1720))(a0, a1); }
  // 0x004D1D10  conf=0.733  ?GetVertData@special_surfaces@@QAEHHAAUvector3@@0AAUxcolor@@@Z
  using GetVertData_t = int (__thiscall*)(::special_surfaces *, int, ::vector3 *, ::vector3 *, ::xcolor *);
  inline int GetVertData(::special_surfaces * a0, int a1, ::vector3 * a2, ::vector3 * a3, ::xcolor * a4) { return reinterpret_cast<GetVertData_t>(meridian::rebase(0x004D1D10))(a0, a1, a2, a3, a4); }
  // 0x004D1E90  conf=0.737  ?InitAlphaData@special_surfaces@@QAEXXZ
  using InitAlphaData_t = void (__thiscall*)(::special_surfaces *);
  inline void InitAlphaData(::special_surfaces * a0) { reinterpret_cast<InitAlphaData_t>(meridian::rebase(0x004D1E90))(a0); }
  // 0x004D0AE0  conf=0.789  ?IsMeshHidden@special_surfaces@@QAEHH@Z
  using IsMeshHidden_t = int (__thiscall*)(::special_surfaces *, int);
  inline int IsMeshHidden(::special_surfaces * a0, int a1) { return reinterpret_cast<IsMeshHidden_t>(meridian::rebase(0x004D0AE0))(a0, a1); }
  // 0x004D0D70  conf=0.881  ?OnExport@special_surfaces@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::special_surfaces *, ::bin_out *);
  inline void OnExport(::special_surfaces * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004D0D70))(a0, a1); }
  // 0x004D0E10  conf=0.865  ?OnImport@special_surfaces@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::special_surfaces *, ::bin_in *);
  inline void OnImport(::special_surfaces * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004D0E10))(a0, a1); }
  // 0x004D22C0  conf=0.798  ?SetHidden@special_surfaces@@QAEXH@Z
  using SetHidden_t = void (__thiscall*)(::special_surfaces *, int);
  inline void SetHidden(::special_surfaces * a0, int a1) { reinterpret_cast<SetHidden_t>(meridian::rebase(0x004D22C0))(a0, a1); }
  // 0x004D0A70  conf=0.75  ?SetMeshIsHidden@special_surfaces@@QAEXHH@Z
  using SetMeshIsHidden_t = void (__thiscall*)(::special_surfaces *, int, int);
  inline void SetMeshIsHidden(::special_surfaces * a0, int a1, int a2) { reinterpret_cast<SetMeshIsHidden_t>(meridian::rebase(0x004D0A70))(a0, a1, a2); }
  // 0x004D0BC0  conf=0.75  ?SetMeshRenderMask@special_surfaces@@QAEX_K@Z
  using SetMeshRenderMask_t = void (__thiscall*)(::special_surfaces *, __uint64);
  inline void SetMeshRenderMask(::special_surfaces * a0, __uint64 a1) { reinterpret_cast<SetMeshRenderMask_t>(meridian::rebase(0x004D0BC0))(a0, a1); }
  // 0x004D1430  conf=0.892  ?SetProperty@special_surfaces@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::special_surfaces *, char *, ::property *);
  inline int SetProperty(::special_surfaces * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004D1430))(a0, a1, a2); }
  // 0x004D1F60  conf=0.723  ?SetResourceName@special_surfaces@@UAEXPBD@Z
  using SetResourceName_t = void (__thiscall*)(::special_surfaces *, char *);
  inline void SetResourceName(::special_surfaces * a0, char * a1) { reinterpret_cast<SetResourceName_t>(meridian::rebase(0x004D1F60))(a0, a1); }
  // 0x004ACC10  conf=0.75  ?SetSortGroup@special_surfaces@@QAEXE@Z
  using SetSortGroup_t = void (__thiscall*)(::special_surfaces *, uchar);
  inline void SetSortGroup(::special_surfaces * a0, uchar a1) { reinterpret_cast<SetSortGroup_t>(meridian::rebase(0x004ACC10))(a0, a1); }
  // 0x004D0800  conf=0.756  ??0special_surfaces@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::special_surfaces *);
  inline undefined ctor(::special_surfaces * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004D0800))(a0); }
} // special_surfaces_

// ===== static_textin_loader =====  (1 functions)  ->  namespace static_textin_loader_
namespace static_textin_loader_ {
  // 0x005486B0  conf=0.75  ?Unload@static_textin_loader@@UAEXPAXPBD@Z
  using Unload_t = void (__thiscall*)(::static_textin_loader *, void *, char *);
  inline void Unload(::static_textin_loader * a0, void * a1, char * a2) { reinterpret_cast<Unload_t>(meridian::rebase(0x005486B0))(a0, a1, a2); }
} // static_textin_loader_

// ===== subtitle_mgr =====  (2 functions)  ->  namespace subtitle_mgr_
namespace subtitle_mgr_ {
  // 0x00551280  conf=0.97  ?StartSubTitle@subtitle_mgr@@QAEXPBDMH@Z
  using StartSubTitle_t = void (__thiscall*)(::subtitle_mgr *, char *, float, int);
  inline void StartSubTitle(::subtitle_mgr * a0, char * a1, float a2, int a3) { reinterpret_cast<StartSubTitle_t>(meridian::rebase(0x00551280))(a0, a1, a2, a3); }
  // 0x0054EDF0  conf=0.97  ?Update@subtitle_mgr@@QAEXM@Z
  using Update_t = void (__thiscall*)(::subtitle_mgr *, float);
  inline void Update(::subtitle_mgr * a0, float a1) { reinterpret_cast<Update_t>(meridian::rebase(0x0054EDF0))(a0, a1); }
} // subtitle_mgr_

// ===== text_in =====  (3 functions)  ->  namespace text_in_
namespace text_in_ {
  // 0x0063EA10  conf=0.97  ?GetField@text_in@@QAAHPBDZZ
  inline void* GetField_at() { return meridian::rebase(0x0063EA10); } // int __thiscall GetField(text_in *, char *, ...)
  // 0x0063E1C0  conf=0.967  ?ReadAllFields@text_in@@IAEHXZ
  using ReadAllFields_t = int (__thiscall*)(::text_in *);
  inline int ReadAllFields(::text_in * a0) { return reinterpret_cast<ReadAllFields_t>(meridian::rebase(0x0063E1C0))(a0); }
  // 0x0063E6A0  conf=0.97  ?ReadFields@text_in@@QAEHXZ
  using ReadFields_t = int (__thiscall*)(::text_in *);
  inline int ReadFields(::text_in * a0) { return reinterpret_cast<ReadFields_t>(meridian::rebase(0x0063E6A0))(a0); }
} // text_in_

// ===== tile_puzzle =====  (13 functions)  ->  namespace tile_puzzle_
namespace tile_puzzle_ {
  // 0x0040EF90  conf=0.97  ?ActivateDurin@tile_puzzle@@IAEXXZ
  using ActivateDurin_t = void (__thiscall*)(::tile_puzzle *);
  inline void ActivateDurin(::tile_puzzle * a0) { reinterpret_cast<ActivateDurin_t>(meridian::rebase(0x0040EF90))(a0); }
  // 0x0040EDA0  conf=0.97  ?ActivateErebor@tile_puzzle@@IAEXXZ
  using ActivateErebor_t = void (__thiscall*)(::tile_puzzle *);
  inline void ActivateErebor(::tile_puzzle * a0) { reinterpret_cast<ActivateErebor_t>(meridian::rebase(0x0040EDA0))(a0); }
  // 0x0040EBD0  conf=0.97  ?ActivateLetter@tile_puzzle@@IAEXF@Z
  using ActivateLetter_t = void (__thiscall*)(::tile_puzzle *, short);
  inline void ActivateLetter(::tile_puzzle * a0, short a1) { reinterpret_cast<ActivateLetter_t>(meridian::rebase(0x0040EBD0))(a0, a1); }
  // 0x0040ED50  conf=0.97  ?ActivateReset@tile_puzzle@@IAEXXZ
  using ActivateReset_t = void (__thiscall*)(::tile_puzzle *);
  inline void ActivateReset(::tile_puzzle * a0) { reinterpret_cast<ActivateReset_t>(meridian::rebase(0x0040ED50))(a0); }
  // 0x0040EAB0  conf=0.97  ?ActivateSpike@tile_puzzle@@IAEXF@Z
  using ActivateSpike_t = void (__thiscall*)(::tile_puzzle *, short);
  inline void ActivateSpike(::tile_puzzle * a0, short a1) { reinterpret_cast<ActivateSpike_t>(meridian::rebase(0x0040EAB0))(a0, a1); }
  // 0x0040EE90  conf=0.97  ?ActivateThorin@tile_puzzle@@IAEXXZ
  using ActivateThorin_t = void (__thiscall*)(::tile_puzzle *);
  inline void ActivateThorin(::tile_puzzle * a0) { reinterpret_cast<ActivateThorin_t>(meridian::rebase(0x0040EE90))(a0); }
  // 0x0040EF10  conf=0.97  ?ActivateThrain@tile_puzzle@@IAEXXZ
  using ActivateThrain_t = void (__thiscall*)(::tile_puzzle *);
  inline void ActivateThrain(::tile_puzzle * a0) { reinterpret_cast<ActivateThrain_t>(meridian::rebase(0x0040EF10))(a0); }
  // 0x0040F010  conf=0.97  ?ActivateThror@tile_puzzle@@IAEXXZ
  using ActivateThror_t = void (__thiscall*)(::tile_puzzle *);
  inline void ActivateThror(::tile_puzzle * a0) { reinterpret_cast<ActivateThror_t>(meridian::rebase(0x0040F010))(a0); }
  // 0x0040E700  conf=0.97  ?AdvanceLogic@tile_puzzle@@QAEXM@Z
  using AdvanceLogic_t = void (__thiscall*)(::tile_puzzle *, float);
  inline void AdvanceLogic(::tile_puzzle * a0, float a1) { reinterpret_cast<AdvanceLogic_t>(meridian::rebase(0x0040E700))(a0, a1); }
  // 0x0040E830  conf=0.774  ?GetBilboTileindex@tile_puzzle@@IAEFXZ
  using GetBilboTileindex_t = short (__thiscall*)(::tile_puzzle *);
  inline short GetBilboTileindex(::tile_puzzle * a0) { return reinterpret_cast<GetBilboTileindex_t>(meridian::rebase(0x0040E830))(a0); }
  // 0x0040EA00  conf=0.75  ?GetTileType@tile_puzzle@@IAE?AW4tile_type@1@F@Z
  inline void* GetTileType_at() { return meridian::rebase(0x0040EA00); } // tile_type __thiscall GetTileType(tile_puzzle *, short)
  // 0x0040E6A0  conf=0.97  ?Init@tile_puzzle@@QAEXXZ
  using Init_t = void (__thiscall*)(::tile_puzzle *);
  inline void Init(::tile_puzzle * a0) { reinterpret_cast<Init_t>(meridian::rebase(0x0040E6A0))(a0); }
  // 0x0040ED10  conf=0.97  ?ResetPuzzle@tile_puzzle@@IAEXXZ
  using ResetPuzzle_t = void (__thiscall*)(::tile_puzzle *);
  inline void ResetPuzzle(::tile_puzzle * a0) { reinterpret_cast<ResetPuzzle_t>(meridian::rebase(0x0040ED10))(a0); }
} // tile_puzzle_

// ===== token_stream =====  (1 functions)  ->  namespace token_stream_
namespace token_stream_ {
  // 0x00644820  conf=0.97  ?ReadInt@token_stream@@QAEHXZ
  using ReadInt_t = int (__thiscall*)(::token_stream *);
  inline int ReadInt(::token_stream * a0) { return reinterpret_cast<ReadInt_t>(meridian::rebase(0x00644820))(a0); }
} // token_stream_

// ===== treasure_chest =====  (14 functions)  ->  namespace treasure_chest_
namespace treasure_chest_ {
  // 0x004D65B0  conf=0.97  ?EnumerateProperties@treasure_chest@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::treasure_chest *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::treasure_chest * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004D65B0))(a0, a1); }
  // 0x004D8140  conf=0.9  ?GetProperty@treasure_chest@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::treasure_chest *, char *);
  inline ::property GetProperty(::treasure_chest * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004D8140))(a0, a1); }
  // 0x004D3F30  conf=0.97  ?Init@treasure_chest@@QAEXABUvector3@@ABUradian3@@0ABUbbox@@H@Z
  using Init_t = void (__thiscall*)(::treasure_chest *, ::vector3 *, ::radian3 *, ::vector3 *, ::bbox *, int);
  inline void Init(::treasure_chest * a0, ::vector3 * a1, ::radian3 * a2, ::vector3 * a3, ::bbox * a4, int a5) { reinterpret_cast<Init_t>(meridian::rebase(0x004D3F30))(a0, a1, a2, a3, a4, a5); }
  // 0x004C8970  conf=0.75  ?IsOpen@treasure_chest@@QAEHXZ
  using IsOpen_t = int (__thiscall*)(::treasure_chest *);
  inline int IsOpen(::treasure_chest * a0) { return reinterpret_cast<IsOpen_t>(meridian::rebase(0x004C8970))(a0); }
  // 0x004D57B0  conf=0.75  ?IsTrapped@treasure_chest@@QAEHXZ
  using IsTrapped_t = int (__thiscall*)(::treasure_chest *);
  inline int IsTrapped(::treasure_chest * a0) { return reinterpret_cast<IsTrapped_t>(meridian::rebase(0x004D57B0))(a0); }
  // 0x004D4360  conf=0.93  ?OnAdvanceLogic@treasure_chest@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::treasure_chest *, float);
  inline void OnAdvanceLogic(::treasure_chest * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004D4360))(a0, a1); }
  // 0x004D5180  conf=0.873  ?OnImport@treasure_chest@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::treasure_chest *, ::bin_in *);
  inline void OnImport(::treasure_chest * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004D5180))(a0, a1); }
  // 0x00495FC0  conf=0.735  ?OnObjectDeactivate@treasure_chest@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::treasure_chest *);
  inline void OnObjectDeactivate(::treasure_chest * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x00495FC0))(a0); }
  // 0x004D42B0  conf=0.746  ?OnReset@treasure_chest@@UAEXXZ
  using OnReset_t = void (__thiscall*)(::treasure_chest *);
  inline void OnReset(::treasure_chest * a0) { reinterpret_cast<OnReset_t>(meridian::rebase(0x004D42B0))(a0); }
  // 0x004D5BD0  conf=0.97  ?Open@treasure_chest@@QAEXXZ
  using Open_t = void (__thiscall*)(::treasure_chest *);
  inline void Open(::treasure_chest * a0) { reinterpret_cast<Open_t>(meridian::rebase(0x004D5BD0))(a0); }
  // 0x004D6080  conf=0.97  ?SetChestType@treasure_chest@@IAEXW4chest_type@1@@Z
  inline void* SetChestType_at() { return meridian::rebase(0x004D6080); } // void __thiscall SetChestType(treasure_chest *, chest_type)
  // 0x004D6440  conf=0.786  ?SetContentsType@treasure_chest@@IAEXVxstring@@@Z
  using SetContentsType_t = void (__thiscall*)(::treasure_chest *, ::xstring);
  inline void SetContentsType(::treasure_chest * a0, ::xstring a1) { reinterpret_cast<SetContentsType_t>(meridian::rebase(0x004D6440))(a0, a1); }
  // 0x004D6280  conf=0.748  ?SetElementContentsType@treasure_chest@@IAEXHVxstring@@@Z
  using SetElementContentsType_t = void (__thiscall*)(::treasure_chest *, int, ::xstring);
  inline void SetElementContentsType(::treasure_chest * a0, int a1, ::xstring a2) { reinterpret_cast<SetElementContentsType_t>(meridian::rebase(0x004D6280))(a0, a1, a2); }
  // 0x004D3B70  conf=0.786  ??0treasure_chest@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::treasure_chest *);
  inline undefined ctor(::treasure_chest * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004D3B70))(a0); }
} // treasure_chest_

// ===== treeleaf_cluster =====  (4 functions)  ->  namespace treeleaf_cluster_
namespace treeleaf_cluster_ {
  // 0x004DA890  conf=0.887  ?EnumerateProperties@treeleaf_cluster@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::treeleaf_cluster *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::treeleaf_cluster * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004DA890))(a0, a1); }
  // 0x004D90D0  conf=0.75  ?Init@treeleaf_cluster@@QAEXABUvector3@@@Z
  using Init_t = void (__thiscall*)(::treeleaf_cluster *, ::vector3 *);
  inline void Init(::treeleaf_cluster * a0, ::vector3 * a1) { reinterpret_cast<Init_t>(meridian::rebase(0x004D90D0))(a0, a1); }
  // 0x004DA280  conf=0.9  ?OnExport@treeleaf_cluster@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::treeleaf_cluster *, ::bin_out *);
  inline void OnExport(::treeleaf_cluster * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004DA280))(a0, a1); }
  // 0x004DA460  conf=0.85  ?OnImport@treeleaf_cluster@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::treeleaf_cluster *, ::bin_in *);
  inline void OnImport(::treeleaf_cluster * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004DA460))(a0, a1); }
} // treeleaf_cluster_

// ===== trigger =====  (27 functions)  ->  namespace trigger_
namespace trigger_ {
  // 0x004DF1C0  conf=0.733  ?DrawIndicator@trigger@@QAEHABUvector3@@@Z
  using DrawIndicator_t = int (__thiscall*)(::trigger *, ::vector3 *);
  inline int DrawIndicator(::trigger * a0, ::vector3 * a1) { return reinterpret_cast<DrawIndicator_t>(meridian::rebase(0x004DF1C0))(a0, a1); }
  // 0x004DD1B0  conf=0.97  ?EjectItems@trigger@@QAEXXZ
  using EjectItems_t = void (__thiscall*)(::trigger *);
  inline void EjectItems(::trigger * a0) { reinterpret_cast<EjectItems_t>(meridian::rebase(0x004DD1B0))(a0); }
  // 0x004DE6B0  conf=0.8  ?Enable@trigger@@QAEXH@Z
  using Enable_t = void (__thiscall*)(::trigger *, int);
  inline void Enable(::trigger * a0, int a1) { reinterpret_cast<Enable_t>(meridian::rebase(0x004DE6B0))(a0, a1); }
  // 0x004DF5E0  conf=0.9  ?EnumerateProperties@trigger@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::trigger *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::trigger * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004DF5E0))(a0, a1); }
  // 0x004E1A10  conf=0.794  ?ForceCheckEnter@trigger@@QAEXH@Z
  using ForceCheckEnter_t = void (__thiscall*)(::trigger *, int);
  inline void ForceCheckEnter(::trigger * a0, int a1) { reinterpret_cast<ForceCheckEnter_t>(meridian::rebase(0x004E1A10))(a0, a1); }
  // 0x004DD230  conf=0.8  ?GetItemName@trigger@@QAEPBDH@Z
  using GetItemName_t = char * (__thiscall*)(::trigger *, int);
  inline char * GetItemName(::trigger * a0, int a1) { return reinterpret_cast<GetItemName_t>(meridian::rebase(0x004DD230))(a0, a1); }
  // 0x004DD290  conf=0.75  ?GetItemType@trigger@@QAEHH@Z
  using GetItemType_t = int (__thiscall*)(::trigger *, int);
  inline int GetItemType(::trigger * a0, int a1) { return reinterpret_cast<GetItemType_t>(meridian::rebase(0x004DD290))(a0, a1); }
  // 0x004DD2C0  conf=0.75  ?GetUseInventory@trigger@@QAEHXZ
  using GetUseInventory_t = int (__thiscall*)(::trigger *);
  inline int GetUseInventory(::trigger * a0) { return reinterpret_cast<GetUseInventory_t>(meridian::rebase(0x004DD2C0))(a0); }
  // 0x004DE640  conf=0.609  ?GetWasTriggered@trigger@@QAEHXZ
  using GetWasTriggered_t = int (__thiscall*)(::trigger *);
  inline int GetWasTriggered(::trigger * a0) { return reinterpret_cast<GetWasTriggered_t>(meridian::rebase(0x004DE640))(a0); }
  // 0x004DE6D0  conf=0.8  ?IsEnabled@trigger@@QAEHXZ
  using IsEnabled_t = int (__thiscall*)(::trigger *);
  inline int IsEnabled(::trigger * a0) { return reinterpret_cast<IsEnabled_t>(meridian::rebase(0x004DE6D0))(a0); }
  // 0x004DD210  conf=0.742  ?IsFull@trigger@@QAEHXZ
  using IsFull_t = int (__thiscall*)(::trigger *);
  inline int IsFull(::trigger * a0) { return reinterpret_cast<IsFull_t>(meridian::rebase(0x004DD210))(a0); }
  // 0x004E19B0  conf=0.8  ?IsInside@trigger@@QAEHAB_K@Z
  using IsInside_t = int (__thiscall*)(::trigger *, __uint64 *);
  inline int IsInside(::trigger * a0, __uint64 * a1) { return reinterpret_cast<IsInside_t>(meridian::rebase(0x004E19B0))(a0, a1); }
  // 0x004DF1B0  conf=0.75  ?IsTriggered@trigger@@QAEHXZ
  using IsTriggered_t = int (__thiscall*)(::trigger *);
  inline int IsTriggered(::trigger * a0) { return reinterpret_cast<IsTriggered_t>(meridian::rebase(0x004DF1B0))(a0); }
  // 0x004DE300  conf=0.97  ?OnActivate@trigger@@QAEXXZ
  using OnActivate_t = void (__thiscall*)(::trigger *);
  inline void OnActivate(::trigger * a0) { reinterpret_cast<OnActivate_t>(meridian::rebase(0x004DE300))(a0); }
  // 0x004DD480  conf=0.97  ?OnAdvanceLogic@trigger@@UAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::trigger *, float);
  inline void OnAdvanceLogic(::trigger * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x004DD480))(a0, a1); }
  // 0x004DE760  conf=0.97  ?OnExport@trigger@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::trigger *, ::bin_out *);
  inline void OnExport(::trigger * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004DE760))(a0, a1); }
  // 0x004DE9E0  conf=0.97  ?OnImport@trigger@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::trigger *, ::bin_in *);
  inline void OnImport(::trigger * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004DE9E0))(a0, a1); }
  // 0x004E1A60  conf=0.85  ?OnObjectActivate@trigger@@UAEXXZ
  using OnObjectActivate_t = void (__thiscall*)(::trigger *);
  inline void OnObjectActivate(::trigger * a0) { reinterpret_cast<OnObjectActivate_t>(meridian::rebase(0x004E1A60))(a0); }
  // 0x004DE270  conf=0.97  ?OnPain@trigger@@QAEX_KABUvector3@@MMMH@Z
  using OnPain_t = void (__thiscall*)(::trigger *, __uint64, ::vector3 *, float, float, float, int);
  inline void OnPain(::trigger * a0, __uint64 a1, ::vector3 * a2, float a3, float a4, float a5, int a6) { reinterpret_cast<OnPain_t>(meridian::rebase(0x004DE270))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x004DD2D0  conf=0.97  ?OnPressB@trigger@@QAEXXZ
  using OnPressB_t = void (__thiscall*)(::trigger *);
  inline void OnPressB(::trigger * a0) { reinterpret_cast<OnPressB_t>(meridian::rebase(0x004DD2D0))(a0); }
  // 0x004DCD80  conf=0.83  ?OnReset@trigger@@UAEXXZ
  using OnReset_t = void (__thiscall*)(::trigger *);
  inline void OnReset(::trigger * a0) { reinterpret_cast<OnReset_t>(meridian::rebase(0x004DCD80))(a0); }
  // 0x004DCEF0  conf=0.97  ?OnUse@trigger@@QAEXH@Z
  using OnUse_t = void (__thiscall*)(::trigger *, int);
  inline void OnUse(::trigger * a0, int a1) { reinterpret_cast<OnUse_t>(meridian::rebase(0x004DCEF0))(a0, a1); }
  // 0x004DE5F0  conf=0.75  ?SetAttrMask@trigger@@QAEXI@Z
  using SetAttrMask_t = void (__thiscall*)(::trigger *, uint);
  inline void SetAttrMask(::trigger * a0, uint a1) { reinterpret_cast<SetAttrMask_t>(meridian::rebase(0x004DE5F0))(a0, a1); }
  // 0x004E1A90  conf=0.75  ?SetOneTimeShot@trigger@@QAEXH@Z
  using SetOneTimeShot_t = void (__thiscall*)(::trigger *, int);
  inline void SetOneTimeShot(::trigger * a0, int a1) { reinterpret_cast<SetOneTimeShot_t>(meridian::rebase(0x004E1A90))(a0, a1); }
  // 0x004DE650  conf=0.75  ?SetSaveInside@trigger@@QAEXH@Z
  using SetSaveInside_t = void (__thiscall*)(::trigger *, int);
  inline void SetSaveInside(::trigger * a0, int a1) { reinterpret_cast<SetSaveInside_t>(meridian::rebase(0x004DE650))(a0, a1); }
  // 0x004DE610  conf=0.725  ?SetTriggered@trigger@@QAEXH@Z
  using SetTriggered_t = void (__thiscall*)(::trigger *, int);
  inline void SetTriggered(::trigger * a0, int a1) { reinterpret_cast<SetTriggered_t>(meridian::rebase(0x004DE610))(a0, a1); }
  // 0x004DD060  conf=0.95  ?UseItems@trigger@@IAEXXZ
  using UseItems_t = void (__thiscall*)(::trigger *);
  inline void UseItems(::trigger * a0) { reinterpret_cast<UseItems_t>(meridian::rebase(0x004DD060))(a0); }
} // trigger_

// ===== ui_check =====  (1 functions)  ->  namespace ui_check_
namespace ui_check_ {
  // 0x006A96B0  conf=0.753  ?Render@ui_check@@UAEXHH@Z
  using Render_t = void (__thiscall*)(::ui_check *, int, int);
  inline void Render(::ui_check * a0, int a1, int a2) { reinterpret_cast<Render_t>(meridian::rebase(0x006A96B0))(a0, a1, a2); }
} // ui_check_

// ===== ui_dialog =====  (1 functions)  ->  namespace ui_dialog_
namespace ui_dialog_ {
  // 0x006A5A20  conf=0.97  ?GotoControl@ui_dialog@@QAEHPAVui_control@@@Z
  using GotoControl_t = int (__thiscall*)(::ui_dialog *, ::ui_control *);
  inline int GotoControl(::ui_dialog * a0, ::ui_control * a1) { return reinterpret_cast<GotoControl_t>(meridian::rebase(0x006A5A20))(a0, a1); }
} // ui_dialog_

// ===== ui_dlg_list =====  (1 functions)  ->  namespace ui_dlg_list_
namespace ui_dlg_list_ {
  // 0x006A4020  conf=0.97  ?Render@ui_dlg_list@@UAEXHH@Z
  using Render_t = void (__thiscall*)(::ui_dlg_list *, int, int);
  inline void Render(::ui_dlg_list * a0, int a1, int a2) { reinterpret_cast<Render_t>(meridian::rebase(0x006A4020))(a0, a1, a2); }
} // ui_dlg_list_

// ===== ui_fx_mgr =====  (2 functions)  ->  namespace ui_fx_mgr_
namespace ui_fx_mgr_ {
  // 0x0058E8C0  conf=0.97  ?CreateFX@ui_fx_mgr@@QAEHPBDABUvector2@@W4ui_fx_render_order@@@Z
  inline void* CreateFX_at() { return meridian::rebase(0x0058E8C0); } // int __thiscall CreateFX(ui_fx_mgr *, char *, vector2 *, ui_fx_render_order)
  // 0x0058EA40  conf=0.97  ?FXDie@ui_fx_mgr@@QAEHH@Z
  using FXDie_t = int (__thiscall*)(::ui_fx_mgr *, int);
  inline int FXDie(::ui_fx_mgr * a0, int a1) { return reinterpret_cast<FXDie_t>(meridian::rebase(0x0058EA40))(a0, a1); }
} // ui_fx_mgr_

// ===== ui_manager =====  (1 functions)  ->  namespace ui_manager_
namespace ui_manager_ {
  // 0x0069E460  conf=0.925  ?Init@ui_manager@@QAEHXZ
  using Init_t = int (__thiscall*)(::ui_manager *);
  inline int Init(::ui_manager * a0) { return reinterpret_cast<Init_t>(meridian::rebase(0x0069E460))(a0); }
} // ui_manager_

// ===== ui_slider =====  (1 functions)  ->  namespace ui_slider_
namespace ui_slider_ {
  // 0x006A5CC0  conf=0.97  ?OnPadNavigate@ui_slider@@UAEXPAVui_win@@HHH@Z
  using OnPadNavigate_t = void (__thiscall*)(::ui_slider *, ::ui_win *, int, int, int);
  inline void OnPadNavigate(::ui_slider * a0, ::ui_win * a1, int a2, int a3, int a4) { reinterpret_cast<OnPadNavigate_t>(meridian::rebase(0x006A5CC0))(a0, a1, a2, a3, a4); }
} // ui_slider_

// ===== ui_win =====  (1 functions)  ->  namespace ui_win_
namespace ui_win_ {
  // 0x005C0150  conf=0.683  ?GetPosition@ui_win@@UBEABUirect@@XZ
  using GetPosition_t = ::irect * (__thiscall*)(::ui_win *);
  inline ::irect * GetPosition(::ui_win * a0) { return reinterpret_cast<GetPosition_t>(meridian::rebase(0x005C0150))(a0); }
} // ui_win_

// ===== vector3 =====  (2 functions)  ->  namespace vector3_
namespace vector3_ {
  // 0x00402040  conf=0.789  ?GetSqrDistToLineSeg@vector3@@QBEMABU1@0@Z
  using GetSqrDistToLineSeg_t = float (__thiscall*)(::vector3 *, ::vector3 *, ::vector3 *);
  inline float GetSqrDistToLineSeg(::vector3 * a0, ::vector3 * a1, ::vector3 * a2) { return reinterpret_cast<GetSqrDistToLineSeg_t>(meridian::rebase(0x00402040))(a0, a1, a2); }
  // 0x0042E1F0  conf=0.798  ?Normalize@vector3@@QAEHXZ
  using Normalize_t = int (__thiscall*)(::vector3 *);
  inline int Normalize(::vector3 * a0) { return reinterpret_cast<Normalize_t>(meridian::rebase(0x0042E1F0))(a0); }
} // vector3_

// ===== view =====  (1 functions)  ->  namespace view_
namespace view_ {
  // 0x0057F800  conf=0.698  ?RayFromScreen@view@@QBEXAAUvector3@@0MMW4system@1@@Z
  inline void* RayFromScreen_at() { return meridian::rebase(0x0057F800); } // void __thiscall RayFromScreen(view *, vector3 *, vector3 *, float, float, system)
} // view_

// ===== volume =====  (11 functions)  ->  namespace volume_
namespace volume_ {
  // 0x004E30F0  conf=0.886  ?EnumerateProperties@volume@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::volume *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::volume * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004E30F0))(a0, a1); }
  // 0x004E37D0  conf=0.889  ?GetProperty@volume@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::volume *, char *);
  inline ::property GetProperty(::volume * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004E37D0))(a0, a1); }
  // 0x004E1E70  conf=0.775  ?Init@volume@@QAEXABUvector3@@MMM@Z
  using Init_t = void (__thiscall*)(::volume *, ::vector3 *, float, float, float);
  inline void Init(::volume * a0, ::vector3 * a1, float a2, float a3, float a4) { reinterpret_cast<Init_t>(meridian::rebase(0x004E1E70))(a0, a1, a2, a3, a4); }
  // 0x004E2000  conf=0.615  ?Init@volume@@QAEXABUvector3@@0ABUradian3@@@Z
  using Init_4E2000_t = void (__thiscall*)(::volume *, ::vector3 *, ::vector3 *, ::radian3 *);
  inline void Init_4E2000(::volume * a0, ::vector3 * a1, ::vector3 * a2, ::radian3 * a3) { reinterpret_cast<Init_4E2000_t>(meridian::rebase(0x004E2000))(a0, a1, a2, a3); }
  // 0x004E2330  conf=0.761  ?IsPointInside@volume@@QAEHABUvector3@@@Z
  using IsPointInside_t = int (__thiscall*)(::volume *, ::vector3 *);
  inline int IsPointInside(::volume * a0, ::vector3 * a1) { return reinterpret_cast<IsPointInside_t>(meridian::rebase(0x004E2330))(a0, a1); }
  // 0x004E2B70  conf=0.85  ?OnExport@volume@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::volume *, ::bin_out *);
  inline void OnExport(::volume * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004E2B70))(a0, a1); }
  // 0x004E2C00  conf=0.891  ?OnImport@volume@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::volume *, ::bin_in *);
  inline void OnImport(::volume * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004E2C00))(a0, a1); }
  // 0x004E2050  conf=0.743  ?OnInit@volume@@UAEXXZ
  using OnInit_t = void (__thiscall*)(::volume *);
  inline void OnInit(::volume * a0) { reinterpret_cast<OnInit_t>(meridian::rebase(0x004E2050))(a0); }
  // 0x004E30C0  conf=0.75  ?OnRotate@volume@@UAEXABUradian3@@@Z
  using OnRotate_t = void (__thiscall*)(::volume *, ::radian3 *);
  inline void OnRotate(::volume * a0, ::radian3 * a1) { reinterpret_cast<OnRotate_t>(meridian::rebase(0x004E30C0))(a0, a1); }
  // 0x004E2630  conf=0.76  ?SetPoints@volume@@IAEXXZ
  using SetPoints_t = void (__thiscall*)(::volume *);
  inline void SetPoints(::volume * a0) { reinterpret_cast<SetPoints_t>(meridian::rebase(0x004E2630))(a0); }
  // 0x004E3380  conf=0.898  ?SetProperty@volume@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::volume *, char *, ::property *);
  inline int SetProperty(::volume * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004E3380))(a0, a1, a2); }
} // volume_

// ===== wall =====  (9 functions)  ->  namespace wall_
namespace wall_ {
  // 0x004E4B20  conf=0.743  ?ApplyGeometry@wall@@QAEXXZ
  using ApplyGeometry_t = void (__thiscall*)(::wall *);
  inline void ApplyGeometry(::wall * a0) { reinterpret_cast<ApplyGeometry_t>(meridian::rebase(0x004E4B20))(a0); }
  // 0x004E4ED0  conf=0.9  ?EnumerateProperties@wall@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::wall *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::wall * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004E4ED0))(a0, a1); }
  // 0x004E6120  conf=0.9  ?GetProperty@wall@@UAE?AUproperty@@PBD@Z
  using GetProperty_t = ::property (__thiscall*)(::wall *, char *);
  inline ::property GetProperty(::wall * a0, char * a1) { return reinterpret_cast<GetProperty_t>(meridian::rebase(0x004E6120))(a0, a1); }
  // 0x004E42C0  conf=0.748  ?Init@wall@@QAEXABUvector3@@0ABUradian3@@HHHHHH@Z
  using Init_t = void (__thiscall*)(::wall *, ::vector3 *, ::vector3 *, ::radian3 *, int, int, int, int, int, int);
  inline void Init(::wall * a0, ::vector3 * a1, ::vector3 * a2, ::radian3 * a3, int a4, int a5, int a6, int a7, int a8, int a9) { reinterpret_cast<Init_t>(meridian::rebase(0x004E42C0))(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); }
  // 0x004E4BE0  conf=0.75  ?OnCheckCollision@wall@@UAEXXZ
  using OnCheckCollision_t = void (__thiscall*)(::wall *);
  inline void OnCheckCollision(::wall * a0) { reinterpret_cast<OnCheckCollision_t>(meridian::rebase(0x004E4BE0))(a0); }
  // 0x004E4580  conf=0.9  ?OnExport@wall@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::wall *, ::bin_out *);
  inline void OnExport(::wall * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004E4580))(a0, a1); }
  // 0x004E47A0  conf=0.846  ?OnImport@wall@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::wall *, ::bin_in *);
  inline void OnImport(::wall * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004E47A0))(a0, a1); }
  // 0x004E52C0  conf=0.851  ?SetProperty@wall@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::wall *, char *, ::property *);
  inline int SetProperty(::wall * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004E52C0))(a0, a1, a2); }
  // 0x004E3DD0  conf=0.758  ??0wall@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::wall *);
  inline undefined ctor(::wall * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004E3DD0))(a0); }
} // wall_

// ===== water =====  (14 functions)  ->  namespace water_
namespace water_ {
  // 0x004E8E30  conf=0.721  ?ApplyWaterPain@water@@IAEXM@Z
  using ApplyWaterPain_t = void (__thiscall*)(::water *, float);
  inline void ApplyWaterPain(::water * a0, float a1) { reinterpret_cast<ApplyWaterPain_t>(meridian::rebase(0x004E8E30))(a0, a1); }
  // 0x004E93F0  conf=0.563  ?CalculateSpacing@water@@IAEXXZ
  using CalculateSpacing_t = void (__thiscall*)(::water *);
  inline void CalculateSpacing(::water * a0) { reinterpret_cast<CalculateSpacing_t>(meridian::rebase(0x004E93F0))(a0); }
  // 0x004EB130  conf=0.97  ?EnumerateProperties@water@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::water *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::water * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004EB130))(a0, a1); }
  // 0x004E7B60  conf=0.75  ?GetCurHeightIndex@water@@QAEHXZ
  using GetCurHeightIndex_t = int (__thiscall*)(::water *);
  inline int GetCurHeightIndex(::water * a0) { return reinterpret_cast<GetCurHeightIndex_t>(meridian::rebase(0x004E7B60))(a0); }
  // 0x004E7BA0  conf=0.789  ?GetDepthOfPoint@water@@QAEMABUvector3@@@Z
  using GetDepthOfPoint_t = float (__thiscall*)(::water *, ::vector3 *);
  inline float GetDepthOfPoint(::water * a0, ::vector3 * a1) { return reinterpret_cast<GetDepthOfPoint_t>(meridian::rebase(0x004E7BA0))(a0, a1); }
  // 0x004E78D0  conf=0.747  ?Init@water@@QAEXABUvector3@@ABUbbox@@@Z
  using Init_t = void (__thiscall*)(::water *, ::vector3 *, ::bbox *);
  inline void Init(::water * a0, ::vector3 * a1, ::bbox * a2) { reinterpret_cast<Init_t>(meridian::rebase(0x004E78D0))(a0, a1, a2); }
  // 0x004EA4E0  conf=0.78  ?InitRuntimeData@water@@IAEXXZ
  using InitRuntimeData_t = void (__thiscall*)(::water *);
  inline void InitRuntimeData(::water * a0) { reinterpret_cast<InitRuntimeData_t>(meridian::rebase(0x004EA4E0))(a0); }
  // 0x004E7C90  conf=0.762  ?IsPointInside@water@@QAEHABUvector3@@@Z
  using IsPointInside_t = int (__thiscall*)(::water *, ::vector3 *);
  inline int IsPointInside(::water * a0, ::vector3 * a1) { return reinterpret_cast<IsPointInside_t>(meridian::rebase(0x004E7C90))(a0, a1); }
  // 0x004EA400  conf=0.742  ?KillRuntimeData@water@@IAEXH@Z
  using KillRuntimeData_t = void (__thiscall*)(::water *, int);
  inline void KillRuntimeData(::water * a0, int a1) { reinterpret_cast<KillRuntimeData_t>(meridian::rebase(0x004EA400))(a0, a1); }
  // 0x004E98C0  conf=0.85  ?OnExport@water@@UAEXAAVbin_out@@@Z
  using OnExport_t = void (__thiscall*)(::water *, ::bin_out *);
  inline void OnExport(::water * a0, ::bin_out * a1) { reinterpret_cast<OnExport_t>(meridian::rebase(0x004E98C0))(a0, a1); }
  // 0x004E9DC0  conf=0.85  ?OnImport@water@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::water *, ::bin_in *);
  inline void OnImport(::water * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004E9DC0))(a0, a1); }
  // 0x004E9DA0  conf=0.75  ?OnObjectDeactivate@water@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::water *);
  inline void OnObjectDeactivate(::water * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004E9DA0))(a0); }
  // 0x004E7E70  conf=0.799  ?Splash@water@@QAEXABUvector3@@0EMMM@Z
  using Splash_t = void (__thiscall*)(::water *, ::vector3 *, ::vector3 *, uchar, float, float, float);
  inline void Splash(::water * a0, ::vector3 * a1, ::vector3 * a2, uchar a3, float a4, float a5, float a6) { reinterpret_cast<Splash_t>(meridian::rebase(0x004E7E70))(a0, a1, a2, a3, a4, a5, a6); }
  // 0x0040CDD0  conf=0.748  ?SwitchToHeight@water@@QAEXHM@Z
  using SwitchToHeight_t = void (__thiscall*)(::water *, int, float);
  inline void SwitchToHeight(::water * a0, int a1, float a2) { reinterpret_cast<SwitchToHeight_t>(meridian::rebase(0x0040CDD0))(a0, a1, a2); }
} // water_

// ===== water_puzzle =====  (6 functions)  ->  namespace water_puzzle_
namespace water_puzzle_ {
  // 0x0040FDC0  conf=0.97  ?AdvancePuzzleEditing@water_puzzle@@AAEXM@Z
  using AdvancePuzzleEditing_t = void (__thiscall*)(::water_puzzle *, float);
  inline void AdvancePuzzleEditing(::water_puzzle * a0, float a1) { reinterpret_cast<AdvancePuzzleEditing_t>(meridian::rebase(0x0040FDC0))(a0, a1); }
  // 0x0040F470  conf=0.97  ?Init@water_puzzle@@QAEXPBD000000ABUvector3@@@Z
  using Init_t = void (__thiscall*)(::water_puzzle *, char *, char *, char *, char *, char *, char *, char *, ::vector3 *);
  inline void Init(::water_puzzle * a0, char * a1, char * a2, char * a3, char * a4, char * a5, char * a6, char * a7, ::vector3 * a8) { reinterpret_cast<Init_t>(meridian::rebase(0x0040F470))(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
  // 0x0040FB90  conf=0.75  ?IsActive@water_puzzle@@QAEHXZ
  using IsActive_t = int (__thiscall*)(::water_puzzle *);
  inline int IsActive(::water_puzzle * a0) { return reinterpret_cast<IsActive_t>(meridian::rebase(0x0040FB90))(a0); }
  // 0x004104C0  conf=0.739  ?ResolveWaterLevels@water_puzzle@@AAEXXZ
  using ResolveWaterLevels_t = void (__thiscall*)(::water_puzzle *);
  inline void ResolveWaterLevels(::water_puzzle * a0) { reinterpret_cast<ResolveWaterLevels_t>(meridian::rebase(0x004104C0))(a0); }
  // 0x00410650  conf=0.75  ?SaveState@water_puzzle@@QAEXAAVbitstream@@@Z
  using SaveState_t = void (__thiscall*)(::water_puzzle *, ::bitstream *);
  inline void SaveState(::water_puzzle * a0, ::bitstream * a1) { reinterpret_cast<SaveState_t>(meridian::rebase(0x00410650))(a0, a1); }
  // 0x00410310  conf=0.97  ?StartTurningHandle@water_puzzle@@AAEXH@Z
  using StartTurningHandle_t = void (__thiscall*)(::water_puzzle *, int);
  inline void StartTurningHandle(::water_puzzle * a0, int a1) { reinterpret_cast<StartTurningHandle_t>(meridian::rebase(0x00410310))(a0, a1); }
} // water_puzzle_

// ===== weather_mgr =====  (4 functions)  ->  namespace weather_mgr_
namespace weather_mgr_ {
  // 0x00552AF0  conf=0.97  ?BuildFork@weather_mgr@@IAEXPAUfork@1@HABUvector3@@1MMM@Z
  using BuildFork_t = void (__thiscall*)(::weather_mgr *, ::fork *, int, ::vector3 *, ::vector3 *, float, float, float);
  inline void BuildFork(::weather_mgr * a0, ::fork * a1, int a2, ::vector3 * a3, ::vector3 * a4, float a5, float a6, float a7) { reinterpret_cast<BuildFork_t>(meridian::rebase(0x00552AF0))(a0, a1, a2, a3, a4, a5, a6, a7); }
  // 0x005513A0  conf=0.97  ?EnableStorm@weather_mgr@@QAEXHM@Z
  using EnableStorm_t = void (__thiscall*)(::weather_mgr *, int, float);
  inline void EnableStorm(::weather_mgr * a0, int a1, float a2) { reinterpret_cast<EnableStorm_t>(meridian::rebase(0x005513A0))(a0, a1, a2); }
  // 0x00551C20  conf=0.701  ?OnAdvanceLogic@weather_mgr@@QAEXM@Z
  using OnAdvanceLogic_t = void (__thiscall*)(::weather_mgr *, float);
  inline void OnAdvanceLogic(::weather_mgr * a0, float a1) { reinterpret_cast<OnAdvanceLogic_t>(meridian::rebase(0x00551C20))(a0, a1); }
  // 0x00551A80  conf=0.67  ?Render@weather_mgr@@QAEXXZ
  using Render_t = void (__thiscall*)(::weather_mgr *);
  inline void Render(::weather_mgr * a0) { reinterpret_cast<Render_t>(meridian::rebase(0x00551A80))(a0); }
} // weather_mgr_

// ===== web_line =====  (1 functions)  ->  namespace web_line_
namespace web_line_ {
  // 0x004EDAC0  conf=0.97  ??0web_line@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::web_line *);
  inline undefined ctor(::web_line * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004EDAC0))(a0); }
} // web_line_

// ===== web_wall =====  (9 functions)  ->  namespace web_wall_
namespace web_wall_ {
  // 0x004F18A0  conf=0.872  ?EnumerateProperties@web_wall@@UAEXAAV?$xarray@Uproperty_desc@@@@@Z
  using EnumerateProperties_t = void (__thiscall*)(::web_wall *, ::xarray< ::property_desc> *);
  inline void EnumerateProperties(::web_wall * a0, ::xarray< ::property_desc> * a1) { reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x004F18A0))(a0, a1); }
  // 0x004F0380  conf=0.75  ?Kill@web_wall@@IAEXXZ
  using Kill_t = void (__thiscall*)(::web_wall *);
  inline void Kill(::web_wall * a0) { reinterpret_cast<Kill_t>(meridian::rebase(0x004F0380))(a0); }
  // 0x004EFDD0  conf=0.85  ?OnImport@web_wall@@UAEXAAVbin_in@@@Z
  using OnImport_t = void (__thiscall*)(::web_wall *, ::bin_in *);
  inline void OnImport(::web_wall * a0, ::bin_in * a1) { reinterpret_cast<OnImport_t>(meridian::rebase(0x004EFDD0))(a0, a1); }
  // 0x004EEAF0  conf=0.774  ?OnInit@web_wall@@UAEXXZ
  using OnInit_t = void (__thiscall*)(::web_wall *);
  inline void OnInit(::web_wall * a0) { reinterpret_cast<OnInit_t>(meridian::rebase(0x004EEAF0))(a0); }
  // 0x004EEBB0  conf=0.8  ?OnObjectActivate@web_wall@@UAEXXZ
  using OnObjectActivate_t = void (__thiscall*)(::web_wall *);
  inline void OnObjectActivate(::web_wall * a0) { reinterpret_cast<OnObjectActivate_t>(meridian::rebase(0x004EEBB0))(a0); }
  // 0x004EEBE0  conf=0.75  ?OnObjectDeactivate@web_wall@@UAEXXZ
  using OnObjectDeactivate_t = void (__thiscall*)(::web_wall *);
  inline void OnObjectDeactivate(::web_wall * a0) { reinterpret_cast<OnObjectDeactivate_t>(meridian::rebase(0x004EEBE0))(a0); }
  // 0x004F03E0  conf=0.795  ?RebuildWeb@web_wall@@IAEXXZ
  using RebuildWeb_t = void (__thiscall*)(::web_wall *);
  inline void RebuildWeb(::web_wall * a0) { reinterpret_cast<RebuildWeb_t>(meridian::rebase(0x004F03E0))(a0); }
  // 0x004F11C0  conf=0.97  ?SetProperty@web_wall@@UAEHPBDABUproperty@@@Z
  using SetProperty_t = int (__thiscall*)(::web_wall *, char *, ::property *);
  inline int SetProperty(::web_wall * a0, char * a1, ::property * a2) { return reinterpret_cast<SetProperty_t>(meridian::rebase(0x004F11C0))(a0, a1, a2); }
  // 0x004EE420  conf=0.97  ??0web_wall@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::web_wall *);
  inline undefined ctor(::web_wall * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x004EE420))(a0); }
} // web_wall_

// ===== x_bitmap_quant =====  (1 functions)  ->  namespace x_bitmap_quant_
namespace x_bitmap_quant_ {
  // 0x006568E0  conf=0.626  ?quant_End@@YAXPAUxcolor@@HH@Z
  using quant_End_t = void (__cdecl*)(::xcolor *, int, int);
  inline void quant_End(::xcolor * a0, int a1, int a2) { reinterpret_cast<quant_End_t>(meridian::rebase(0x006568E0))(a0, a1, a2); }
} // x_bitmap_quant_

// ===== x_plus =====  (3 functions)  ->  namespace x_plus_
namespace x_plus_ {
  // 0x00648600  conf=0.706  ?x_memmove@@YAPAXPAXPBXH@Z
  using x_memmove_t = void * (__cdecl*)(void *, void *, int);
  inline void * x_memmove(void * a0, void * a1, int a2) { return reinterpret_cast<x_memmove_t>(meridian::rebase(0x00648600))(a0, a1, a2); }
  // 0x0053F310  conf=0.752  ?x_strcat@@YAPADPADPBD@Z
  using x_strcat_t = char * (__cdecl*)(char *, char *);
  inline char * x_strcat(char * a0, char * a1) { return reinterpret_cast<x_strcat_t>(meridian::rebase(0x0053F310))(a0, a1); }
  // 0x00648480  conf=0.691  ?x_strippath_dir@@YAXPBDPAD@Z
  using x_strippath_dir_t = void (__cdecl*)(char *, char *);
  inline void x_strippath_dir(char * a0, char * a1) { reinterpret_cast<x_strippath_dir_t>(meridian::rebase(0x00648480))(a0, a1); }
} // x_plus_

// ===== x_stdio =====  (1 functions)  ->  namespace x_stdio_
namespace x_stdio_ {
  // 0x0064F210  conf=0.68  ?x_SetFileIOHooks@@YAXP6APAIPBD0@ZP6AXPAI@ZP6AH2PAEH@ZP6AH2PBEH@ZP6AH2HH@ZP6AH2@Z999@Z
  using x_SetFileIOHooks_t = void (__cdecl*)(::_func_uint_ptr_char_ptr_char_ptr *, ::_func_void_uint_ptr *, ::_func_int_uint_ptr_uchar_ptr_int *, ::_func_int_uint_ptr_uchar_ptr_int *, ::_func_int_uint_ptr_int_int *, ::_func_int_uint_ptr *, ::_func_int_uint_ptr *, ::_func_int_uint_ptr *, ::_func_int_uint_ptr *);
  inline void x_SetFileIOHooks(::_func_uint_ptr_char_ptr_char_ptr * a0, ::_func_void_uint_ptr * a1, ::_func_int_uint_ptr_uchar_ptr_int * a2, ::_func_int_uint_ptr_uchar_ptr_int * a3, ::_func_int_uint_ptr_int_int * a4, ::_func_int_uint_ptr * a5, ::_func_int_uint_ptr * a6, ::_func_int_uint_ptr * a7, ::_func_int_uint_ptr * a8) { reinterpret_cast<x_SetFileIOHooks_t>(meridian::rebase(0x0064F210))(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
} // x_stdio_

// ===== x_threads =====  (1 functions)  ->  namespace x_threads_
namespace x_threads_ {
  // 0x00653600  conf=0.97  ?x_GetCurrentThread@@YAPAVxthread@@XZ
  using x_GetCurrentThread_t = ::xthread * (__cdecl*)();
  inline ::xthread * x_GetCurrentThread() { return reinterpret_cast<x_GetCurrentThread_t>(meridian::rebase(0x00653600))(); }
} // x_threads_

// ===== xarray =====  (15 functions)  ->  namespace xarray_
namespace xarray_ {
  // 0x00407F70  conf=0.691  ?Append@?$xarray@Vxstring@@@@QAEXABVxstring@@@Z
  using Append_t = void (__thiscall*)(::xarray< ::xstring> *, ::xstring *);
  inline void Append(::xarray< ::xstring> * a0, ::xstring * a1) { reinterpret_cast<Append_t>(meridian::rebase(0x00407F70))(a0, a1); }
  // 0x00417830  conf=0.724  ?Append@?$xarray@Ugas_pipe@level_laketown@@@@QAEAAUgas_pipe@level_laketown@@XZ
  inline void* Append_417830_at() { return meridian::rebase(0x00417830); } // gas_pipe * __thiscall Append(xarray<level_laketown::gas_pipe> *)
  // 0x00425270  conf=0.748  ?Append@?$xarray@Vxwstring@@@@QAEXABVxwstring@@@Z
  using Append_425270_t = void (__thiscall*)(::xarray< ::xwstring> *, ::xwstring *);
  inline void Append_425270(::xarray< ::xwstring> * a0, ::xwstring * a1) { reinterpret_cast<Append_425270_t>(meridian::rebase(0x00425270))(a0, a1); }
  // 0x00459F30  conf=0.721  ?Append@?$xarray@Uproperty_desc@@@@QAEAAUproperty_desc@@XZ
  using Append_459F30_t = ::property_desc * (__thiscall*)(::xarray< ::property_desc> *);
  inline ::property_desc * Append_459F30(::xarray< ::property_desc> * a0) { return reinterpret_cast<Append_459F30_t>(meridian::rebase(0x00459F30))(a0); }
  // 0x00473DD0  conf=0.739  ?Append@?$xarray@Ucinema_syncpoint@@@@QAEAAUcinema_syncpoint@@XZ
  using Append_473DD0_t = ::cinema_syncpoint * (__thiscall*)(::xarray< ::cinema_syncpoint> *);
  inline ::cinema_syncpoint * Append_473DD0(::xarray< ::cinema_syncpoint> * a0) { return reinterpret_cast<Append_473DD0_t>(meridian::rebase(0x00473DD0))(a0); }
  // 0x00473F70  conf=0.736  ?Append@?$xarray@Ucinema_shot@@@@QAEAAUcinema_shot@@XZ
  using Append_473F70_t = ::cinema_shot * (__thiscall*)(::xarray< ::cinema_shot> *);
  inline ::cinema_shot * Append_473F70(::xarray< ::cinema_shot> * a0) { return reinterpret_cast<Append_473F70_t>(meridian::rebase(0x00473F70))(a0); }
  // 0x0049EC80  conf=0.795  ?Append@?$xarray@UNavLink@@@@QAEXABUNavLink@@@Z
  using Append_49EC80_t = void (__thiscall*)(::xarray< ::NavLink> *, ::NavLink *);
  inline void Append_49EC80(::xarray< ::NavLink> * a0, ::NavLink * a1) { reinterpret_cast<Append_49EC80_t>(meridian::rebase(0x0049EC80))(a0, a1); }
  // 0x004D8C10  conf=0.68  ?Append@?$xarray@UChestContents@@@@QAEXABUChestContents@@@Z
  using Append_4D8C10_t = void (__thiscall*)(::xarray< ::ChestContents> *, ::ChestContents *);
  inline void Append_4D8C10(::xarray< ::ChestContents> * a0, ::ChestContents * a1) { reinterpret_cast<Append_4D8C10_t>(meridian::rebase(0x004D8C10))(a0, a1); }
  // 0x00572970  conf=0.95  ?Append@?$xarray@Uvector3@@@@QAEXABUvector3@@@Z
  using Append_572970_t = void (__thiscall*)(::xarray< ::vector3> *, ::vector3 *);
  inline void Append_572970(::xarray< ::vector3> * a0, ::vector3 * a1) { reinterpret_cast<Append_572970_t>(meridian::rebase(0x00572970))(a0, a1); }
  // 0x005F10C0  conf=0.744  ?Append@?$xarray@_K@@QAEXAB_K@Z
  using Append_5F10C0_t = void (__thiscall*)(::xarray< ::unsigned___int64> *, __uint64 *);
  inline void Append_5F10C0(::xarray< ::unsigned___int64> * a0, __uint64 * a1) { reinterpret_cast<Append_5F10C0_t>(meridian::rebase(0x005F10C0))(a0, a1); }
  // 0x00538050  conf=0.767  ?Clear@?$xarray@Vxstring@@@@QAEXXZ
  using Clear_t = void (__thiscall*)(::xarray< ::xstring> *);
  inline void Clear(::xarray< ::xstring> * a0) { reinterpret_cast<Clear_t>(meridian::rebase(0x00538050))(a0); }
  // 0x00553D60  conf=0.586  ?Delete@?$xarray@Vxstring@@@@QAEXHH@Z
  using Delete_t = void (__thiscall*)(::xarray< ::xstring> *, int, int);
  inline void Delete(::xarray< ::xstring> * a0, int a1, int a2) { reinterpret_cast<Delete_t>(meridian::rebase(0x00553D60))(a0, a1, a2); }
  // 0x00533F60  conf=0.97  ?Find@?$xarray@Vxstring@@@@QBEHABVxstring@@H@Z
  using Find_t = int (__thiscall*)(::xarray< ::xstring> *, ::xstring *, int);
  inline int Find(::xarray< ::xstring> * a0, ::xstring * a1, int a2) { return reinterpret_cast<Find_t>(meridian::rebase(0x00533F60))(a0, a1, a2); }
  // 0x00451C60  conf=0.748  ?Insert@?$xarray@_K@@QAEAA_KH@Z
  using Insert_t = __uint64 * (__thiscall*)(::xarray< ::unsigned___int64> *, int);
  inline __uint64 * Insert(::xarray< ::unsigned___int64> * a0, int a1) { return reinterpret_cast<Insert_t>(meridian::rebase(0x00451C60))(a0, a1); }
  // 0x00417750  conf=0.749  ?SetCapacity@?$xarray@Vxstring@@@@QAEXH@Z
  using SetCapacity_t = void (__thiscall*)(::xarray< ::xstring> *, int);
  inline void SetCapacity(::xarray< ::xstring> * a0, int a1) { reinterpret_cast<SetCapacity_t>(meridian::rebase(0x00417750))(a0, a1); }
} // xarray_

// ===== xbitmap =====  (2 functions)  ->  namespace xbitmap_
namespace xbitmap_ {
  // 0x00652870  conf=0.699  ?Load@xbitmap@@QAEHPAI@Z
  using Load_t = int (__thiscall*)(::xbitmap *, uint *);
  inline int Load(::xbitmap * a0, uint * a1) { return reinterpret_cast<Load_t>(meridian::rebase(0x00652870))(a0, a1); }
  // 0x00650290  conf=0.688  ?Unflip4BitNibbles@xbitmap@@QAEXXZ
  using Unflip4BitNibbles_t = void (__thiscall*)(::xbitmap *);
  inline void Unflip4BitNibbles(::xbitmap * a0) { reinterpret_cast<Unflip4BitNibbles_t>(meridian::rebase(0x00650290))(a0); }
} // xbitmap_

// ===== xstring =====  (2 functions)  ->  namespace xstring_
namespace xstring_ {
  // 0x0064A450  conf=0.688  ?FreeExtra@xstring@@QAEXXZ
  using FreeExtra_t = void (__thiscall*)(::xstring *);
  inline void FreeExtra(::xstring * a0) { reinterpret_cast<FreeExtra_t>(meridian::rebase(0x0064A450))(a0); }
  // 0x00649960  conf=0.701  ??0xstring@@QAE@ABV0@@Z
  using ctor_t = undefined (__thiscall*)(::xstring *, ::xstring *);
  inline undefined ctor(::xstring * a0, ::xstring * a1) { return reinterpret_cast<ctor_t>(meridian::rebase(0x00649960))(a0, a1); }
} // xstring_

// ===== xthread =====  (2 functions)  ->  namespace xthread_
namespace xthread_ {
  // 0x006761F0  conf=0.66  ?InitMain@xthread@@QAEXPAXH@Z
  using InitMain_t = void (__thiscall*)(::xthread *, void *, int);
  inline void InitMain(::xthread * a0, void * a1, int a2) { reinterpret_cast<InitMain_t>(meridian::rebase(0x006761F0))(a0, a1, a2); }
  // 0x00680720  conf=0.637  ?Suspend@xthread@@QAEXHW4state@1@@Z
  inline void* Suspend_at() { return meridian::rebase(0x00680720); } // void __thiscall Suspend(xthread *, int, state)
} // xthread_

// ===== xwstring =====  (4 functions)  ->  namespace xwstring_
namespace xwstring_ {
  // 0x0064B9D0  conf=0.686  ?Left@xwstring@@QBE?AV1@H@Z
  using Left_t = ::xwstring (__thiscall*)(::xwstring *, int);
  inline ::xwstring Left(::xwstring * a0, int a1) { return reinterpret_cast<Left_t>(meridian::rebase(0x0064B9D0))(a0, a1); }
  // 0x005C8690  conf=0.79  ??0xwstring@@QAE@XZ
  using ctor_t = undefined (__thiscall*)(::xwstring *);
  inline undefined ctor(::xwstring * a0) { return reinterpret_cast<ctor_t>(meridian::rebase(0x005C8690))(a0); }
  // 0x0064AFC0  conf=0.708  ??0xwstring@@QAE@PBG@Z
  using ctor_64AFC0_t = undefined (__thiscall*)(::xwstring *, ushort *);
  inline undefined ctor_64AFC0(::xwstring * a0, ushort * a1) { return reinterpret_cast<ctor_64AFC0_t>(meridian::rebase(0x0064AFC0))(a0, a1); }
  // 0x0064B7F0  conf=0.723  ??0xwstring@@QAE@PBD@Z
  using ctor_64B7F0_t = undefined (__thiscall*)(::xwstring *, char *);
  inline undefined ctor_64B7F0(::xwstring * a0, char * a1) { return reinterpret_cast<ctor_64B7F0_t>(meridian::rebase(0x0064B7F0))(a0, a1); }
} // xwstring_

