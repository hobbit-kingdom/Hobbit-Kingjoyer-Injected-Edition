// =============================================================================
// camera_sdk.h  —  THE HOBBIT (2003) PC build, Entropy engine (MSVC, 32-bit)
//
// Reverse-engineered SDK wrappers for the "camera" subsystem:
//   - camera / camera_mgr : the active game camera (position/target/FOV, follow
//                           logic, per-frame state advance, transitions/blends)
//   - camera_modifier / camera_influence : volume zones that re-tune / snap the camera
//   - camera_path / path / MotionLinear / marker / nav_point : spline rails and
//                           scripted-motion waypoints the camera and other movers follow
//
// Legitimate RE of the user's own game for a modding / trainer SDK.
//
// All addresses are PREFERRED-base (image base 0x00400000, ASLR off). Resolve at
// runtime with meridian::rebase(0xADDR); set meridian::g_delta once at init if the
// image is loaded at a non-preferred base. Calling convention is __thiscall (this in
// ECX) unless the typedef says __cdecl.
//
// Struct offsets are CONSOLIDATED from the per-chunk analyses (camera__00/01).
// Layouts are PARTIAL: only fields with real evidence are named; the rest is
// byte-accurate padding so named members land at their true offsets. Offsets marked
// "?" are lower confidence. These structs are NOT meant to be instantiated — they are
// reinterpret_cast onto a live engine object (e.g. the slot resolved from a GUID).
//
// Only functions with a recovered absolute address are wrapped. Many demangled API
// names (camera::SetCamera, camera_mgr::StartCinema, ...) are documented in
// docs/subsystems/camera.md but lack a recovered address and are intentionally absent.
// =============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/radian3/bbox/matrix4, xarray<T>, property, ...

// ---- Forward declarations for opaque / cross-subsystem types ----------------
// (camera, camera_mgr, camera_modifier, camera_influence, camera_path, path,
//  marker, nav_point, NavLink, MotionLinear, object, view, bin_in, bin_out,
//  property, property_desc are already forward-declared in meridian_types.h.)
// Engine-type names that COLLIDE with std are global-qualified at the use site
// (e.g. ::path) so this header is immune to `using namespace std;`.

namespace camera_sdk {

// =============================================================================
// 1. Enums / constants (consolidated from SetState / AdvanceStatic / serializers)
// =============================================================================

// camera_mgr::cameraMode (camera_mgr+0x480). AdvanceStatic tests ==4 (static).
// Other modes are inferred from the AdvanceXxx routine set; exact ordinals for the
// non-static modes are NOT confirmed and are flagged "?".
enum CameraMode : std::int32_t {
    CAMERA_MODE_STATIC = 4,   // confirmed: AdvanceStatic gate (influencer-driven)
    // CAMERA_MODE_AUTO / CHASE / FIRST_PERSON / TARGET / DEATH / MANUAL /
    // CINEMA_AUTO / CINEMA_PATH exist as AdvanceXxx routines; ordinals unconfirmed.
};

// camera_mgr::stateFlags (camera_mgr+0x484) — partial bit map.
enum CameraStateFlag : std::uint32_t {
    CAMERA_STATE_BIT1 = 0x00000002, // SetState writes stateTimer under this bit
    CAMERA_STATE_BIT2 = 0x00000004, // AdvanceStatic ORs this in (static latched)
    CAMERA_STATE_BIT3 = 0x00000008, // SetState tests this
};

// property::valueType (property+0x00) / property_desc::valueType (property_desc+0x80).
enum PropertyValueType : std::int32_t {
    PROP_FLOAT   = 2,    // distance / scalar float
    PROP_BOOL    = 3,
    PROP_ENUM    = 5,    // selection / combo
    PROP_VECTOR3 = 8,
    PROP_RADIAN  = 0xa,  // angle in radians (pitch fields)
    PROP_OBJREF  = 0xf,  // GUID / object reference
};

// NavLink::flags (NavLink+0x0c).
enum NavLinkType : std::int32_t {
    NAVLINK_NORMAL = 0,  // RemoveLink only removes type-0 links
    NAVLINK_JUMP   = 1,  // SetJumpTarget writes this
};

// =============================================================================
// 2. Recovered struct layouts
//
// The target is 32-bit MSVC (default member alignment 4, pointers 4 bytes). We
// reproduce that ABI on any host with:
//   - #pragma pack(push, 4)  — so embedded uint64_t GUIDs align to 4, not 8
//   - pointer members declared as std::uint32_t (a 32-bit pointer's storage size)
// This keeps every named member at its TRUE target offset even when the header is
// compiled in a 64-bit build (where a native void* would be 8 bytes and shift things).
// =============================================================================
#pragma pack(push, 4)

// camera — concrete camera object (extends object). Only the view-relevant fields
// recovered by camera::SetupView are named. (camera::SetupView)
struct camera_layout {
    /* 0x000 */ std::uint8_t  _pad000[0x14];
    /* 0x014 */ vector3       position;     // -> view.SetPosition
    /* 0x020 */ std::uint8_t  _pad020[0x48];
    /* 0x068 */ float         orientYaw;    // orientation triple [0]
    /* 0x06c */ float         orientPitch;  // orientation triple [1]
    /* 0x070 */ std::uint8_t  _pad070[0x54];
    /* 0x0c4 */ float         fov;          // -> view.SetFOV
    /* 0x0c8 */ float         zNear;        // -> view.SetClipPlanes(far,near)
    /* 0x0cc */ float         zFar;         //    (zFar is the first clip arg)
    /* 0x0d0 */ std::uint8_t  _pad0d0[0x1c];
    /* 0x0ec */ float         orientRoll;   // orientation triple [2]
};

// camera_modifier — volume-shaped camera tuning zone (extends volume). The single
// most authoritative field map in the subsystem (camera_modifier::OnImport/OnExport/
// SetProperty/EnumerateProperties). The +0x100 "influenceBlock" sub-object overlaps
// the start of the Auto* float block (both anchored at +0x100); treat +0x100 as the
// Auto* tuning set. (camera_modifier::OnImport)
struct camera_modifier_layout {
    /* 0x000 */ std::uint8_t  _baseVolume[0x78]; // volume base
    /* 0x078 */ vector3       chaseOffset;       // "ChaseOffset" (CheckForModifier)
    /* 0x084 */ std::uint8_t  _pad084[0x7c];
    /* 0x100 */ float         autoSpeed;         // also start of OnInit influenceBlock
    /* 0x104 */ float         autoAccel;
    /* 0x108 */ float         autoMinDist;
    /* 0x10c */ float         autoMaxDist;
    /* 0x110 */ float         autoMinPitch;      // radian
    /* 0x114 */ float         autoBestPitch;     // radian
    /* 0x118 */ float         autoMaxPitch;      // radian
    /* 0x11c */ float         autoYawCorrection;
    /* 0x120 */ float         autoPitchCorrection;
    /* 0x124 */ float         autoExtraCorrection;
    /* 0x128 */ float         autoMinDistPC;
    /* 0x12c */ float         autoMaxDistPC;
    /* 0x130 */ float         targetSpeed;
    /* 0x134 */ float         targetAccel;
    /* 0x138 */ float         targetMinDist;
    /* 0x13c */ float         targetMaxDist;
    /* 0x140 */ float         targetMinPitch;    // radian
    /* 0x144 */ float         targetBestPitch;   // radian
    /* 0x148 */ float         targetMaxPitch;    // radian
    /* 0x14c */ std::uint8_t  _pad14c[0x08];
    /* 0x154 */ std::int32_t  allowManualOverride; // bool
    /* 0x158 */ float         manualPitchSpeed;
    /* 0x15c */ float         manualYawSpeed;
    /* 0x160 */ float         manualMinPitch;
    /* 0x164 */ float         manualMaxPitch;
    /* 0x168 */ std::int32_t  manualInvertPitch;   // bool
    /* 0x16c */ std::uint8_t  _pad16c[0x28];
    /* 0x194 */ vector3       firstPersonOffset;
    /* 0x1a0 */ std::uint8_t  _pad1a0[0x1c];
    /* 0x1bc */ float         pcFocusHeight;
    /* 0x1c0 */ float         lookAheadTime;
    /* 0x1c4 */ float         cameraSize;
    /* 0x1c8 */ float         obstacleAvoidanceWeight;
    /* 0x1cc */ vector3       lookSpring;
    /* 0x1d8 */ float         fovSpeed;
    /* 0x1dc */ float         popDistance;
    /* 0x1e0 */ float         viewXFOV;
    /* 0x1e4 */ float         viewZFar;
    /* 0x1e8 */ float         viewZNear;
};

// camera_influence — zone that snaps the camera onto a path / look-at when triggered
// (extends object). (camera_influence::OnImport / IsTriggered)
struct camera_influence_layout {
    /* 0x000 */ std::uint8_t  _pad000[0xa8];
    /* 0x0a8 */ std::int32_t  snapToPosition;   // bool
    /* 0x0ac */ std::int32_t  forceTriggered;   // skip volume test if non-zero
    /* 0x0b0 */ std::int32_t  editorOnlyFlag;   // bool
    /* 0x0b4 */ std::int32_t  oneShotOnly;      // bool
    /* 0x0b8 */ std::uint64_t targetVolumeGuid;
    /* 0x0c0 */ float         minDistance;
    /* 0x0c4 */ float         maxDistance;
    /* 0x0c8 */ std::uint64_t cameraPathGuid;
    /* 0x0d0 */ float         triggerDelay;
    /* 0x0d4 */ std::uint8_t  _pad0d4[0x14];
    /* 0x0e8 */ std::int32_t  timerActiveFlag;
    /* 0x0ec */ std::uint8_t  _pad0ec[0x04];
    /* 0x0f0 */ std::uint64_t lookatTargetGuid;
    /* 0x0f8 */ std::int32_t  lastTriggered;    // cached IsTriggered result + one-shot latch
};

// camera_path — camera-specific spline rail (extends path / object).
// (camera_path::UpdateOffsetMat / EnumerateProperties)
struct camera_path_layout {
    /* 0x000 */ std::uint8_t  _pad000[0x14];
    /* 0x014 */ vector3       position;             // local offset translation
    /* 0x020 */ std::uint8_t  _pad020[0x48];
    /* 0x068 */ radian3       rotation;             // local offset rotation
    /* 0x074 */ std::uint8_t  _pad074[0xa0];
    /* 0x114 */ std::int32_t  propertyEditType;     // set to 0x12 by EnumerateProperties
    /* 0x118 */ std::uint8_t  _pad118[0x20];
    /* 0x138 */ std::int32_t  offsetMatDisableFlag; // UpdateOffsetMat runs only when 0
};

// path — generic spline base for rail-driven motion (extends object).
// (path::GetInterpL2W)
struct path_layout {
    /* 0x000 */ std::uint8_t  _pad000[0xa8];
    /* 0x0a8 */ radian3       baseRotation;
    /* 0x0b4 */ std::uint8_t  _pad0b4[0x0c];
    /* 0x0c0 */ std::int32_t  keyCount;   // numKeys (modulo wrap)
    /* 0x0c4 */ std::uint32_t keyArray;   // path_key* (32-bit ptr), stride 0x0e
};

// path::key — one packed spline key. int16 xyz; stride >= 6 (indexed *0xe in GetInterpL2W).
struct path_key_layout {
    /* 0x00 */ std::int16_t x;
    /* 0x02 */ std::int16_t y;
    /* 0x04 */ std::int16_t z;
    // remaining bytes up to stride 0x0e unidentified (?)
};

// marker — transform waypoint (extends object). (marker::OnExport / EnumerateProperties)
struct marker_layout {
    /* 0x00 */ std::uint8_t  _pad00[0x44];
    /* 0x44 */ std::uint32_t extraSerialized;
    /* 0x48 */ std::uint8_t  _pad48[0x60];
    /* 0xa8 */ radian3       orient;
    /* 0xb4 */ vector3       scale;
    /* 0xc0 */ std::uint32_t orientBlock;
};

// NavLink — one nav-graph edge (POD, size 0x10). (nav_point::AddLink/RemoveLink/SetJumpTarget)
struct NavLink_layout {
    /* 0x00 */ std::uint32_t targetIdLo;
    /* 0x04 */ std::uint32_t targetIdHi;
    /* 0x08 */ float         weight;   // also reused as distance for jump links
    /* 0x0c */ std::int32_t  flags;    // NavLinkType (1 = jump)
};

// nav_point — AI navigation node (extends object). (nav_point ctor / OnImport / CalculateLinks)
struct nav_point_layout {
    /* 0x000 */ std::uint8_t  _pad000[0x08];
    /* 0x008 */ std::uint32_t selfIdLo;        // own GUID lo
    /* 0x00c */ std::uint32_t selfIdHi;        // own GUID hi
    /* 0x010 */ std::uint8_t  _pad010[0x04];
    /* 0x014 */ vector3       position;
    /* 0x020 */ std::uint8_t  _pad020[0x5d];
    /* 0x07d */ std::uint8_t  objFlag;         // ctor sets 2
    /* 0x07e */ std::uint8_t  _pad07e[0x2a];
    /* 0x0a8 */ std::uint8_t  linksHdr[8];     // xarray<NavLink> header
    /* 0x0b0 */ std::int32_t  linkCount;
    /* 0x0b4 */ std::uint32_t linkData;        // NavLink_layout* (32-bit ptr), stride 0x10
    /* 0x0b8 */ std::uint8_t  _pad0b8[0x04];
    /* 0x0bc */ std::int32_t  linkOwnedFlag;   // 0 => owned buffer (freed)
    /* 0x0c0 */ std::int32_t  keyType;         // ctor sets 2
    /* 0x0c4 */ std::uint8_t  _pad0c4[0x04];
    /* 0x0c8 */ std::uint64_t jumpTargetGuid;
    /* 0x0d0 */ float         radius;
    /* 0x0d4 */ std::uint8_t  navFlags;
};

// MotionLinear — linear-interpolation motion driver (vtable PTR_FUN_006edc0c).
// (MotionLinear ctor / SetImpactOnTarget)
struct MotionLinear_layout {
    /* 0x00 */ std::uint32_t  vftable;          // void** (32-bit ptr), &PTR_FUN_006edc0c
    /* 0x04 */ std::uint8_t   _pad04[0x4c];
    /* 0x50 */ std::uint8_t   flags;            // bit1 (0x2) = impact-on-target
};

#pragma pack(pop)

// =============================================================================
// 3. Function wrappers, grouped by class
//
//   __thiscall methods take the object pointer as the FIRST argument.
//   Only functions with a recovered absolute address appear here.
// =============================================================================

// ------------------------------- camera -------------------------------------
namespace camera_api {
    // camera::SetupView(view&) — copy this camera's stored frame (pos +0x14, orient
    // +0x68/+0x6c/+0xec, fov +0xc4, near/far +0xc8/+0xcc) into a renderer view.
    // 0x0045c360
    using SetupView_t = void(__thiscall*)(::camera* self, ::view* out);
    inline void SetupView(::camera* self, ::view* out) {
        reinterpret_cast<SetupView_t>(meridian::rebase(0x0045c360))(self, out);
    }
} // namespace camera_api

// ----------------------------- camera_mgr -----------------------------------
namespace camera_mgr_api {
    // camera_mgr::SetState — configure the active camera state/target: resolve focus
    // (+0x688), read Bilbo's face-bone look-at, clamp chaseDistance (+0x67c) to the
    // active modifier's pitch/dist min/max, compute pos/orient for the new state.
    // The recovered body matches a state-configure entry, not a 2-arg SetState.
    // 0x0056d5e0
    using SetState_t = void(__thiscall*)(::camera_mgr* self);
    inline void SetState(::camera_mgr* self) {
        reinterpret_cast<SetState_t>(meridian::rebase(0x0056d5e0))(self);
    }

    // camera_mgr::UpdateView — build the renderer view from the active camera (when
    // useStoredView(+0x714)==0, via camera::SetupView) or from stored view pos/orient
    // (+0x718/+0x724) plus the active modifier's fov/near/far (+0x730 +0xe0/+0xe4/+0xe8).
    // NOTE: the imported symbol for this address was "camera_mgr::GetProperty(char const*)"
    // but the decompiled body takes no name arg and returns void — it is the view
    // build/commit routine. (proposed UpdateView, confidence 0.55) 0x0056b420
    using UpdateView_t = void(__thiscall*)(::camera_mgr* self);
    inline void UpdateView(::camera_mgr* self) {
        reinterpret_cast<UpdateView_t>(meridian::rebase(0x0056b420))(self);
    }

    // camera_mgr::AdvanceStatic(dt) — static/influencer state tick: re-validate the
    // current camera_influence (+0x6a0), else scan all influences for one containing
    // Bilbo, latch it, adopt its look-at into focusTargetGuid (+0x688). 0x00570ee0
    using AdvanceStatic_t = void(__thiscall*)(::camera_mgr* self, float dt);
    inline void AdvanceStatic(::camera_mgr* self, float dt) {
        reinterpret_cast<AdvanceStatic_t>(meridian::rebase(0x00570ee0))(self, dt);
    }

    // camera_mgr::AdvanceAvoidObstruction(dt) — re-validate the current camera_modifier
    // (+0x6a8), else scan all modifiers containing Bilbo, latch (+0x6a8/+0x730) and fire
    // enter/exit hooks. 0x00571090
    using AdvanceAvoidObstruction_t = void(__thiscall*)(::camera_mgr* self, float dt);
    inline void AdvanceAvoidObstruction(::camera_mgr* self, float dt) {
        reinterpret_cast<AdvanceAvoidObstruction_t>(meridian::rebase(0x00571090))(self, dt);
    }

    // camera_mgr::CheckForModifier — refresh runtime params from the active modifier
    // (+0x730): read "ChaseOffset" into modifier +0x78. 0x005717e0
    using CheckForModifier_t = void(__thiscall*)(::camera_mgr* self);
    inline void CheckForModifier(::camera_mgr* self) {
        reinterpret_cast<CheckForModifier_t>(meridian::rebase(0x005717e0))(self);
    }

    // camera_mgr editor-property enumeration for the influencer rows — lazily registers
    // a "CameraMgr" enum property and "CameraMgr\ChaseOffset" vector3 into the
    // xarray<property_desc>. NOTE: the imported symbol was "camera_mgr::CheckForInfluencer"
    // but the body only builds property_desc rows (the runtime influencer scan is
    // AdvanceStatic). Editor-only. 0x005712d0
    // raw sig: void __thiscall (camera_mgr* self, xarray<property_desc>& out)
    using EnumerateProperties_Influencer_t = void(__thiscall*)(::camera_mgr* self, void* descArray);
    inline void EnumerateProperties_Influencer(::camera_mgr* self, void* descArray) {
        reinterpret_cast<EnumerateProperties_Influencer_t>(meridian::rebase(0x005712d0))(self, descArray);
    }
} // namespace camera_mgr_api

// --------------------------- camera_modifier --------------------------------
namespace camera_modifier_api {
    // camera_modifier::OnInit — volume::OnInit then init embedded sub-object @+0x100. 0x0045e370
    using OnInit_t = void(__thiscall*)(::camera_modifier* self);
    inline void OnInit(::camera_modifier* self) {
        reinterpret_cast<OnInit_t>(meridian::rebase(0x0045e370))(self);
    }

    // camera_modifier::OnImport(bin_in&) — read the full Auto*/Target*/Manual* tuning +
    // FOV/view set (+0x100..+0x1e8). 0x0045e660
    using OnImport_t = void(__thiscall*)(::camera_modifier* self, ::bin_in* in);
    inline void OnImport(::camera_modifier* self, ::bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x0045e660))(self, in);
    }

    // camera_modifier::OnExport(bin_out&) — mirror of OnImport. 0x0045e390
    using OnExport_t = void(__thiscall*)(::camera_modifier* self, ::bin_out* out);
    inline void OnExport(::camera_modifier* self, ::bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x0045e390))(self, out);
    }

    // camera_modifier::SetProperty(name, property&) — editor write: match name then
    // copy property+0x250 into the field offset (type 2=float, 0xa=radian).
    // Returns int (1 = handled). 0x0045ef70
    using SetProperty_t = int(__thiscall*)(::camera_modifier* self, const char* name, const ::property* value);
    inline int SetProperty(::camera_modifier* self, const char* name, const ::property* value) {
        return reinterpret_cast<SetProperty_t>(meridian::rebase(0x0045ef70))(self, name, value);
    }

    // camera_modifier::EnumerateProperties(xarray<property_desc>&) — register the full
    // Auto* tuning rows. 0x0045e9a0
    using EnumerateProperties_t = void(__thiscall*)(::camera_modifier* self, void* descArray);
    inline void EnumerateProperties(::camera_modifier* self, void* descArray) {
        reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0045e9a0))(self, descArray);
    }

    // camera_modifier::IsTriggered() — true if Bilbo's position is inside this modifier's
    // volume. 0x0045e970
    using IsTriggered_t = int(__thiscall*)(::camera_modifier* self);
    inline int IsTriggered(::camera_modifier* self) {
        return reinterpret_cast<IsTriggered_t>(meridian::rebase(0x0045e970))(self);
    }

    // camera_modifier::`scalar deleting destructor'(uint) — volume::~volume then free if
    // (flags & 1). Returns this. 0x004e1de0
    using ScalarDeletingDtor_t = void*(__thiscall*)(::camera_modifier* self, unsigned int flags);
    inline void* ScalarDeletingDtor(::camera_modifier* self, unsigned int flags) {
        return reinterpret_cast<ScalarDeletingDtor_t>(meridian::rebase(0x004e1de0))(self, flags);
    }
} // namespace camera_modifier_api

// --------------------------- camera_influence -------------------------------
namespace camera_influence_api {
    // camera_influence::OnImport(bin_in&) — read camera-path/target-volume/look-at GUIDs,
    // snap/teleport/one-shot flags, delay, min/max distance. 0x0045d350
    using OnImport_t = void(__thiscall*)(::camera_influence* self, ::bin_in* in);
    inline void OnImport(::camera_influence* self, ::bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x0045d350))(self, in);
    }

    // camera_influence::IsTriggered(guid) — test if the target volume contains the object;
    // apply trigger-delay + one-shot latch; cache in +0xf8. Returns int. 0x0045d610
    using IsTriggered_t = int(__thiscall*)(::camera_influence* self, std::uint64_t objectGuid);
    inline int IsTriggered(::camera_influence* self, std::uint64_t objectGuid) {
        return reinterpret_cast<IsTriggered_t>(meridian::rebase(0x0045d610))(self, objectGuid);
    }

    // camera_influence::EnumerateProperties(xarray<property_desc>&) — register Camera Path
    // / Target Volume (objref) + bool/float rows. 0x0045da80
    using EnumerateProperties_t = void(__thiscall*)(::camera_influence* self, void* descArray);
    inline void EnumerateProperties(::camera_influence* self, void* descArray) {
        reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0045da80))(self, descArray);
    }
} // namespace camera_influence_api

// ----------------------------- camera_path ----------------------------------
namespace camera_path_api {
    // camera_path::EnumerateProperties(xarray<property_desc>&) — register Position/Rotation/
    // LocalBBox/Number-of-Frames/Range rows; sets propertyEditType(+0x114)=0x12. 0x00461e90
    using EnumerateProperties_t = void(__thiscall*)(::camera_path* self, void* descArray);
    inline void EnumerateProperties(::camera_path* self, void* descArray) {
        reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x00461e90))(self, descArray);
    }

    // camera_path::UpdateOffsetMat() — recompute the local offset matrix from rotation
    // (+0x68) and translation (+0x14); only when offsetMatDisableFlag(+0x138)==0. 0x004978e0
    using UpdateOffsetMat_t = void(__thiscall*)(::camera_path* self);
    inline void UpdateOffsetMat(::camera_path* self) {
        reinterpret_cast<UpdateOffsetMat_t>(meridian::rebase(0x004978e0))(self);
    }
} // namespace camera_path_api

// -------------------------------- path --------------------------------------
namespace path_api {
    // path::GetInterpL2W(t, matrix4& out) const — interpolated local-to-world matrix at a
    // fractional key index: lerp position keys (+0xc4) between floor(t) and
    // (floor(t)+1)%numKeys(+0xc0), blend orient/scale, apply base rotation (+0xa8). 0x004adc40
    using GetInterpL2W_t = void(__thiscall*)(const ::path* self, float t, matrix4* out);
    inline void GetInterpL2W(const ::path* self, float t, matrix4* out) {
        reinterpret_cast<GetInterpL2W_t>(meridian::rebase(0x004adc40))(self, t, out);
    }

    // path::GetVectorFromKey(out, key) const — read int16 xyz from a key and widen to 3
    // floats into the RVO output buffer. NOTE: the imported symbol was
    // "path::GetOrientationFromKey" returning quaternion, but the body writes only xyz
    // (no w). (proposed GetVectorFromKey, confidence 0.55). 0x004adb90
    // raw sig (RVO): vector3 __thiscall (path* self, vector3* out_hidden, path_key* key)
    using GetVectorFromKey_t = vector3*(__thiscall*)(const ::path* self, vector3* outHidden, const void* key);
    inline vector3* GetVectorFromKey(const ::path* self, vector3* outHidden, const void* key) {
        return reinterpret_cast<GetVectorFromKey_t>(meridian::rebase(0x004adb90))(self, outHidden, key);
    }
} // namespace path_api

// ------------------------------- marker -------------------------------------
namespace marker_api {
    // marker::EnumerateProperties(xarray<property_desc>&) — register Scale (vector3 w/
    // bounds) + patch the "Position\Z" row. 0x0049a5b0
    using EnumerateProperties_t = void(__thiscall*)(::marker* self, void* descArray);
    inline void EnumerateProperties(::marker* self, void* descArray) {
        reinterpret_cast<EnumerateProperties_t>(meridian::rebase(0x0049a5b0))(self, descArray);
    }

    // marker::OnExport(bin_out&) — write type/name, orient block, base transform,
    // Orient (+0xa8), Scale (+0xb4). 0x0049a3e0
    using OnExport_t = void(__thiscall*)(::marker* self, ::bin_out* out);
    inline void OnExport(::marker* self, ::bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x0049a3e0))(self, out);
    }
} // namespace marker_api

// ------------------------------ nav_point -----------------------------------
namespace nav_point_api {
    // nav_point::nav_point() — ctor: install vtable, zero NavLink array, name "NavPoint",
    // defaults (objFlag=2, keyType=2, navFlags=0). 0x0049d660
    using ctor_t = void(__thiscall*)(::nav_point* self);
    inline void ctor(::nav_point* self) {
        reinterpret_cast<ctor_t>(meridian::rebase(0x0049d660))(self);
    }

    // nav_point::CalculateLinks() — clear links, spatial-query nearby nav-points within
    // combined radius, add links, reset jump target. 0x0049dd50
    using CalculateLinks_t = void(__thiscall*)(::nav_point* self);
    inline void CalculateLinks(::nav_point* self) {
        reinterpret_cast<CalculateLinks_t>(meridian::rebase(0x0049dd50))(self);
    }

    // nav_point::SetJumpTarget(guid) — set jumpTargetGuid (+0xc8), refresh the matching
    // NavLink (type=1). 0x0049dbd0
    using SetJumpTarget_t = void(__thiscall*)(::nav_point* self, std::uint64_t targetGuid);
    inline void SetJumpTarget(::nav_point* self, std::uint64_t targetGuid) {
        reinterpret_cast<SetJumpTarget_t>(meridian::rebase(0x0049dbd0))(self, targetGuid);
    }

    // nav_point::AddLink(guid, weight) — add/update a NavLink (self-link guard + de-dup). 0x0049dff0
    using AddLink_t = void(__thiscall*)(::nav_point* self, std::uint64_t targetGuid, float weight);
    inline void AddLink(::nav_point* self, std::uint64_t targetGuid, float weight) {
        reinterpret_cast<AddLink_t>(meridian::rebase(0x0049dff0))(self, targetGuid, weight);
    }

    // nav_point::RemoveLink(guid) — remove the non-flagged NavLink matching the GUID;
    // shift tail down, decrement count. 0x0049e090
    using RemoveLink_t = void(__thiscall*)(::nav_point* self, std::uint64_t targetGuid);
    inline void RemoveLink(::nav_point* self, std::uint64_t targetGuid) {
        reinterpret_cast<RemoveLink_t>(meridian::rebase(0x0049e090))(self, targetGuid);
    }

    // nav_point::OnExport(bin_out&) — write JumpToTarget, NavFlags, transform, Radius. 0x0049e130
    using OnExport_t = void(__thiscall*)(::nav_point* self, ::bin_out* out);
    inline void OnExport(::nav_point* self, ::bin_out* out) {
        reinterpret_cast<OnExport_t>(meridian::rebase(0x0049e130))(self, out);
    }

    // nav_point::OnImport(bin_in&) — read JumpToTarget, NavFlags, transform, Radius. 0x0049e1a0
    using OnImport_t = void(__thiscall*)(::nav_point* self, ::bin_in* in);
    inline void OnImport(::nav_point* self, ::bin_in* in) {
        reinterpret_cast<OnImport_t>(meridian::rebase(0x0049e1a0))(self, in);
    }

    // nav_point::Render() — no-op virtual (nav-points are non-visual at runtime). 0x00650150
    using Render_t = void(__thiscall*)(::nav_point* self);
    inline void Render(::nav_point* self) {
        reinterpret_cast<Render_t>(meridian::rebase(0x00650150))(self);
    }

    // xarray<NavLink>::Append(NavLink const&) — templated dynamic-array append (16-byte
    // stride). 0x0049ec80
    using NavLinkAppend_t = void(__thiscall*)(void* self, const NavLink_layout* element);
    inline void NavLinkArrayAppend(void* self, const NavLink_layout* element) {
        reinterpret_cast<NavLinkAppend_t>(meridian::rebase(0x0049ec80))(self, element);
    }
} // namespace nav_point_api

// ------------------------------ MotionLinear --------------------------------
namespace motion_linear_api {
    // MotionLinear::MotionLinear() — ctor: install vtable PTR_FUN_006edc0c. 0x0049d020
    using ctor_t = void(__thiscall*)(::MotionLinear* self);
    inline void ctor(::MotionLinear* self) {
        reinterpret_cast<ctor_t>(meridian::rebase(0x0049d020))(self);
    }

    // MotionLinear::SetImpactOnTarget(bool) — set bit1 (mask 0x2) of flags byte +0x50. 0x0049d570
    using SetImpactOnTarget_t = void(__thiscall*)(::MotionLinear* self, int impact);
    inline void SetImpactOnTarget(::MotionLinear* self, int impact) {
        reinterpret_cast<SetImpactOnTarget_t>(meridian::rebase(0x0049d570))(self, impact);
    }
} // namespace motion_linear_api

// ----------------------------- UI registration ------------------------------
namespace camera_ui_api {
    // dlg_FEOptCamera_register(ui_manager*) — register the front-end video/camera options
    // screen with the UI manager. 0x0050d2b0
    using FEOptCameraRegister_t = void(__cdecl*)(void* uiManager);
    inline void dlg_FEOptCamera_register(void* uiManager) {
        reinterpret_cast<FEOptCameraRegister_t>(meridian::rebase(0x0050d2b0))(uiManager);
    }

    // dlg_OptCamera_register(ui_manager*) — register the in-game camera options screen. 0x00517800
    using OptCameraRegister_t = void(__cdecl*)(void* uiManager);
    inline void dlg_OptCamera_register(void* uiManager) {
        reinterpret_cast<OptCameraRegister_t>(meridian::rebase(0x00517800))(uiManager);
    }
} // namespace camera_ui_api

// =============================================================================
// 4. Usage / recipes
//
// All wrappers take RAW engine object pointers. Obtain them by resolving a GUID via
// the obj_mgr (see engine_core_sdk.h) or by reading the live camera_mgr singleton
// from its known global, then reinterpret_cast onto the *_layout structs above to
// read/override fields. Set meridian::g_delta once if the image is not at 0x400000.
//
// ---- Recipe A: read / override the active camera position + FOV --------------
//   // 'cam' is a live ::camera* (e.g. camera_mgr's active camera).
//   auto* L = reinterpret_cast<camera_sdk::camera_layout*>(cam);
//   vector3 pos = L->position;          // current camera position
//   float   fov = L->fov;               // current FOV
//   L->fov = 1.20f;                      // widen FOV (radians)
//   L->position.y += 200.0f;             // lift the camera 200 units
//   // Push the edited frame into the renderer view for this object:
//   camera_sdk::camera_api::SetupView(cam, myView);
//
// ---- Recipe B: read the active modifier's chase distance / pitch -------------
//   // 'mgr' is a live ::camera_mgr*.
//   auto* M = reinterpret_cast<camera_sdk::camera_modifier_layout*>(
//                 *reinterpret_cast<void**>(
//                     reinterpret_cast<std::uint8_t*>(mgr) + 0x730)); // activeModifier
//   if (M) {
//       float minDist = M->autoMinDist;
//       float maxDist = M->autoMaxDist;
//       M->autoMaxDist = 1500.0f;        // force a wider chase distance
//   }
//
// ---- Recipe C: snap the camera onto a marker waypoint ------------------------
//   // 'mk' is a live ::marker*. Read its transform and drop the camera there.
//   auto* MK = reinterpret_cast<camera_sdk::marker_layout*>(mk);
//   radian3 orient = MK->orient;         // marker orientation
//   // (position lives in the object base transform; see engine_core_sdk.h)
//   // Then write camera_layout.position/orientYaw/orientPitch/orientRoll and call
//   // camera_api::SetupView, or rely on a camera_influence whose cameraPathGuid points
//   // at a camera_path that interpolates between markers.
//
// ---- Recipe D: drive a camera_path rail and sample its matrix ----------------
//   // 'cp' is a live ::camera_path* (IS-A ::path).
//   camera_sdk::camera_path_api::UpdateOffsetMat(cp);     // refresh local offset matrix
//   matrix4 l2w;
//   camera_sdk::path_api::GetInterpL2W(reinterpret_cast<::path*>(cp), 0.5f, &l2w);
//   // l2w now holds the local-to-world transform at the midpoint of the spline.
//
// ---- Recipe E: force / clear a camera influence trigger ----------------------
//   auto* I = reinterpret_cast<camera_sdk::camera_influence_layout*>(infl);
//   I->forceTriggered = 1;               // always treat the zone as triggered
//   int trig = camera_sdk::camera_influence_api::IsTriggered(infl, bilboGuid);
// =============================================================================

} // namespace camera_sdk
