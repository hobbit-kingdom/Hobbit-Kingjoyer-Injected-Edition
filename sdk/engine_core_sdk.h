// engine_core_sdk.h
// -----------------------------------------------------------------------------
// SDK shim for THE HOBBIT (2003 PC, Entropy / "meridian" engine, MSVC 32-bit).
// Recovered struct layouts + typed function-pointer wrappers at PC image
// addresses. Resolve every address through meridian::rebase(0xADDR).
//
// Legitimate reverse-engineering of the user's own game.
//
// Conventions:
//   __thiscall methods take `this` (the object pointer) as the first argument.
//   __cdecl free functions take their arguments normally.
//   GUIDs are 64-bit (uint64_t).
//   Offsets in comments are byte offsets into the object.
//   Unknown types are forward-declared; treat them as opaque.
// -----------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/vector4/radian3/bbox/matrix4, xarray<T>, ...

// ----------------------------------------------------------------------------
// Extra forward declarations for engine types not in meridian_types.h.
// (vector3/vector4/radian3/bbox/matrix4/xarray come from meridian_types.h.)
// ----------------------------------------------------------------------------
//struct xcolor  { uint8_t r, g, b, a; };       // RGBA8 (not declared in meridian_types.h)
struct plane;
struct AnimInfo;

// ============================================================================
// object  --  abstract base of every game object  (ObjectMgr/Object.cpp)
//   Singleton vtable hot slots: +0x14 SetPosition, +0x28 GetPosition,
//   +0x44 OnActivate, +0x48 SetName, +0x60 Render, +0x154 GetModel/Skeleton.
// ============================================================================

/*
struct object {
	void** vtable;            // +0x00
	uint8_t  _pad08[0x08];      // +0x08 .. : (overlaps guid below)
	// The guid occupies +0x08; the layout is unioned with _pad08 conceptually.
	// Accessors use the offsets below directly.
};
*/

// object field offsets (use with reinterpret_cast<char*>(obj) + OFF):
namespace object_off {
	enum : uint32_t {
		kVTable = 0x00,   // void**
		kGuid = 0x08,   // uint64_t
		kFlags = 0x10,   // uint32_t  master flags (Ladder/Vine/GoldPile/in-water)
		kPosition = 0x14,   // vector3
		kInitialPosition = 0x20,   // vector3 (also prevPosition)
		kLocalBBox = 0x2c,   // bbox (min @0x2c, max @0x38)
		kWorldBBox = 0x44,   // bbox (min @0x44, max @0x50)
		kOrientation = 0x68,   // radian3
		kScriptResource = 0x74,   // rhandle / kstring (script-VM binding)
		kShortId = 0x78,   // int16  collision/layer handle
		kFlags16 = 0x7a,   // uint16 b0 allowName,b1 RequestDestroy,b2 noCollide,b4 camColl,b5 camFade
		kCollDisableFlags = 0x7b,   // uint8  b1 Bilbo-no-collide, b2 NPC-no-collide
		kTypeId = 0x7c,   // uint8  object::type
		kLightChannels = 0x7e,   // uint8
		kStateFlags = 0x7f,   // uint8  b0 ObjSaveFlag,b3 splash,b4 active/locked,b6 at-surface
		kScriptHeapBlock = 0x8c,   // void*  (freed in ~object)
		kName = 0xa0    // char*  (shared s_NONAME when unnamed)
	};
}

// ----- object function wrappers ---------------------------------------------
inline object* object_ctor(object* self) {
	using Fn = object * (__thiscall*)(object*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004aa170))(self);          // object::object
}
inline void object_OnImport(object* self, bin_in* in) {
	using Fn = void(__thiscall*)(object*, bin_in*);
	reinterpret_cast<Fn>(meridian::rebase(0x004aa740))(self, in);             // object::OnImport
}
inline void object_OnExport(object* self, bin_out* out) {
	using Fn = void(__thiscall*)(object*, bin_out*);
	reinterpret_cast<Fn>(meridian::rebase(0x004aa650))(self, out);            // object::OnExport
}
inline void object_Move(object* self, const vector3* pos, int recordPrev) {
	using Fn = void(__thiscall*)(object*, const vector3*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004aa440))(self, pos, recordPrev); // object::Move
}
inline void object_SetName(object* self, const char* name) {
	using Fn = void(__thiscall*)(object*, const char*);
	reinterpret_cast<Fn>(meridian::rebase(0x004aa910))(self, name);           // object::SetName(char const*)
}
inline void object_RequestDestroy(object* self) {
	using Fn = void(__thiscall*)(object*);
	reinterpret_cast<Fn>(meridian::rebase(0x004aaa60))(self);                 // object::RequestDestroy
}
inline void object_ExecuteScript(object* self, const char* obj, const char* method, void* userData) {
	using Fn = void(__thiscall*)(object*, const char*, const char*, void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004aaaf0))(self, obj, method, userData); // object::ExecuteScript(void*)
}
inline int object_HasScriptMethod(object* self, const char* name, const char* sig) {
	using Fn = int(__thiscall*)(object*, const char*, const char*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004aabb0))(self, name, sig); // object::HasScriptMethod
}
inline uint64_t object_GetWaterGuid(object* self) {
	using Fn = uint64_t(__thiscall*)(object*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004aac60))(self);          // object::GetWaterGuid
}
inline void object_MakeSplash(object* self, const vector3* velocity) {
	using Fn = void(__thiscall*)(object*, const vector3*);
	reinterpret_cast<Fn>(meridian::rebase(0x004aad90))(self, velocity);       // object::MakeSplash
}
inline void object_CheckForFog(object* self, const vector3* delta) {
	using Fn = void(__thiscall*)(object*, const vector3*);
	reinterpret_cast<Fn>(meridian::rebase(0x004ab260))(self, delta);          // object::CheckForFog
}
inline void object_SetDoesCollision(object* self, int enable) {
	using Fn = void(__thiscall*)(object*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004ab3e0))(self, enable);         // object::SetDoesCollision
}
inline void object_SetDoesBilboCollision(object* self, int enable) {
	using Fn = void(__thiscall*)(object*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004ab400))(self, enable);         // object::SetDoesBilboCollision
}
inline void object_SetDoesNPCCollision(object* self, int enable) {
	using Fn = void(__thiscall*)(object*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004ab420))(self, enable);         // object::SetDoesNPCCollision
}
inline void object_SetDoesCameraCollision(object* self, int enable) {
	using Fn = void(__thiscall*)(object*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004ab450))(self, enable);         // object::SetDoesCameraCollision
}
inline void object_SetDoesCameraFade(object* self, int enable) {
	using Fn = void(__thiscall*)(object*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004ab480))(self, enable);         // object::SetDoesCameraFade
}
inline void object_SetGoldPile(object* self, int isGold) {
	using Fn = void(__thiscall*)(object*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004ac4e0))(self, isGold);         // object::SetGoldPile
}
inline void object_OnObjectActivate(object* self) {
	using Fn = void(__thiscall*)(object*);
	reinterpret_cast<Fn>(meridian::rebase(0x004ac510))(self);                 // object::OnObjectActivate
}
inline void object_OnObjectDeactivate(object* self) {
	using Fn = void(__thiscall*)(object*);
	reinterpret_cast<Fn>(meridian::rebase(0x004ac540))(self);                 // object::OnObjectDeactivate
}
inline int object_GetIsLayerActive(object* self) {
	using Fn = int(__thiscall*)(object*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004ac5d0))(self);          // object::GetIsLayerActive
}
inline void object_SetLightChannel(object* self, uint8_t channel) {
	using Fn = void(__thiscall*)(object*, uint8_t);
	reinterpret_cast<Fn>(meridian::rebase(0x00494890))(self, channel);        // object::SetLightChannel
}
// __cdecl property reflection helpers used by object editor surface:
inline void PropertyEnumerateColor(xarray<property_desc>* arr, const char* base, uint32_t flags) {
	using Fn = void(__cdecl*)(xarray<property_desc>*, const char*, uint32_t);
	reinterpret_cast<Fn>(meridian::rebase(0x0048b8e0))(arr, base, flags);     // PropertyEnumerateColor
}
inline void PropertyEnumerateBBox(xarray<property_desc>* arr, const char* base, uint32_t flags,
	const bbox* mn, const bbox* mx) {
	using Fn = void(__cdecl*)(xarray<property_desc>*, const char*, uint32_t, const bbox*, const bbox*);
	reinterpret_cast<Fn>(meridian::rebase(0x004acff0))(arr, base, flags, mn, mx); // PropertyEnumerateBBox
}
inline int PropertySetRadian3(const char* name, const property* p, const char* base, radian3* out) {
	using Fn = int(__cdecl*)(const char*, const property*, const char*, radian3*);
	return reinterpret_cast<Fn>(meridian::rebase(0x0048b7d0))(name, p, base, out); // PropertySetRadian3
}

// ============================================================================
// rigid_instance  --  static/animated mesh instance  (RigidInstance.cpp)
//   Anim playback handled by simple_anim_player at +0x140.
// ============================================================================
namespace rigid_instance_off {
	enum : uint32_t {
		kFlags = 0x10,   // uint32 (0x40000000 plant render flag)
		kPosition = 0x14,   // vector3
		kWorldBBox = 0x44,   // bbox
		kRotation = 0x68,   // radian3
		kAmbientColor = 0x82,   // xcolor (4 bytes)
		kScale = 0x130,  // vector3
		kAnimResourceName = 0x13c,  // kstring (0x7fffffff sentinel)
		kAnimPlayer = 0x140,  // simple_anim_player*
		kDestructInfo = 0x144,  // void* (+4 = destruct timer float, -1.0 = inactive)
		kPlantAnimPair = 0x148,  // xstring[2]*
		kCollisionId = 0x158,  // uint16 (0xffff none) | waterHashSlot
		kRigidFlags = 0x15a,  // uint16 b0 HasLOD,b1 Ladder,b2 Vine,b3 LeafPile,b4 Hoistable,
		//        b5 MovingPlatform,b6 AutoEdgeGrab,b10 destruct,b14 Animating
		kAdvanceFlags = 0x15b,  // uint8  b0 DoesFloat,b6 AdvanceAnim
		kFloatYTweak = 0x15c,  // int8
		kFeatureFlags = 0x15d,  // uint8  b0 wiggle/auto-hide, b6 fire-forget
		kLightingType = 0x15e,  // uint8
		kAnimFlags = 0x160,  // uint32 (DestroyChildObjects looping ctrl)
		kChildCount = 0x170,  // int32
		kChildGuidArray = 0x174   // uint64* (child GUIDs)
	};
}
// simple_anim_player layout (rigid_instance +0x140):
namespace anim_player_off {
	enum : uint32_t {
		kSequenceIndex = 0x08,   // int32 (-1 = none)
		kFrameCount = 0x0c,   // int32
		kCurrentFrame = 0x10,   // float
		kFrameDelta = 0x14,   // float (accumulator; zeroed on set)
		kTimeAccumulator = 0x68,   // float (event cursor; zeroed on set)
		kLoopDelayRemaining = 0x7c,   // float
		kAnimSpeed = 0x80,   // float
		kAnimIndex = 0x84,   // int32
		kBoundFlag = 0x88,   // int32 (0 = not bound)
		kLoopDelay = 0x8c,   // float
		kLooping = 0x90    // int32
	};
}

// ----- rigid_instance function wrappers (this = rigid_instance*) -------------
inline void* ri_ctor(void* self) {
	using Fn = void* (__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c0370))(self);          // rigid_instance::rigid_instance
}
inline void ri_OnAdvanceLogic(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004c0ce0))(self, dt);             // rigid_instance::OnAdvanceLogic
}
inline void ri_AdvanceAnim(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004c0e10))(self, dt);             // rigid_instance::AdvanceAnim
}
inline void ri_AdvanceFloat(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004c14a0))(self, dt);             // rigid_instance::AdvanceFloat
}
inline void ri_AdvanceDestruct(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004c1750))(self, dt);             // rigid_instance::AdvanceDestruct
}
inline void ri_SetDestructState(void* self, int hidden, int spawnEffects) {
	using Fn = void(__thiscall*)(void*, int, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004c2f60))(self, hidden, spawnEffects); // rigid_instance::SetDestructState
}
inline void ri_InvalidatePolyCache(void* self, const bbox* region, int flag) {
	using Fn = void(__thiscall*)(void*, const bbox*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004c3500))(self, region, flag);   // rigid_instance::InvalidatePolyCache
}
inline void ri_Move(void* self, const vector3* pos, int recordPrev) {
	using Fn = void(__thiscall*)(void*, const vector3*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004c36f0))(self, pos, recordPrev); // rigid_instance::Move
}
inline void ri_MoveAndUpdate(void* self, const vector3* delta, const radian3* rot) {
	using Fn = void(__thiscall*)(void*, const vector3*, const radian3*);
	reinterpret_cast<Fn>(meridian::rebase(0x004c3760))(self, delta, rot);     // rigid_instance::MoveAndUpdate
}
inline void ri_OnRotate(void* self, const radian3* rot) {
	using Fn = void(__thiscall*)(void*, const radian3*);
	reinterpret_cast<Fn>(meridian::rebase(0x004c3bc0))(self, rot);            // rigid_instance::OnRotate
}
inline void ri_UpdateBBoxAndMove(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004c3d20))(self);                 // rigid_instance::UpdateBBoxAndMove
}
inline int ri_SetAnim(void* self, const char* animName) {
	using Fn = int(__thiscall*)(void*, const char*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c6f40))(self, animName); // rigid_instance::SetAnim
}
inline void ri_SetAnimResourceName(void* self, const char* name) {
	using Fn = void(__thiscall*)(void*, const char*);
	reinterpret_cast<Fn>(meridian::rebase(0x004c7010))(self, name);          // rigid_instance::SetAnimResourceName
}
inline const char* ri_GetAnimResourceName(void* self) {
	using Fn = const char* (__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c7170))(self);         // rigid_instance::GetAnimResourceName
}
inline int ri_AnimDataAvailable(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c71a0))(self);         // rigid_instance::AnimDataAvailable
}
inline int ri_IsAtEndOfAnim(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c7410))(self);         // rigid_instance::IsAtEndOfAnim
}
inline simple_anim_player* ri_GetAnimPlayer(void* self) {
	using Fn = simple_anim_player * (__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c74b0))(self);         // rigid_instance::GetAnimPlayer
}
inline void ri_SetLooping(void* self, int looping) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004c74d0))(self, looping);       // rigid_instance::SetLooping (writes player+0x80; verify vs AnimSpeed)
}
inline void ri_SetLoopDelay(void* self, float seconds) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004c74f0))(self, seconds);       // rigid_instance::SetLoopDelay
}
inline int ri_SetAnimByIndex(void* self, int index) {
	using Fn = int(__thiscall*)(void*, int);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c7520))(self, index);  // rigid_instance::SetAnimByIndex
}
inline void ri_SetAnimFrame(void* self, float frame) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004c7580))(self, frame);         // rigid_instance::SetAnimFrame
}
inline void ri_ResetAnimFrame(void* self, int toEnd) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004c75f0))(self, toEnd);         // rigid_instance::ResetAnimFrame
}
inline void ri_ClearAnimData(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004c73d0))(self);                // rigid_instance::ClearAnimData
}
inline int ri_DetectAnimEvent(void* self, int eventType, vector3* outPos) {
	using Fn = int(__thiscall*)(void*, int, vector3*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004c7820))(self, eventType, outPos); // rigid_instance::DetectAnimEvent
}
inline void ri_WigglePlant(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004c7960))(self);                // rigid_instance::WigglePlant
}
inline void ri_SetupPlant(void* self, const char* baseAnim, const char* wiggleAnim) {
	using Fn = void(__thiscall*)(void*, const char*, const char*);
	reinterpret_cast<Fn>(meridian::rebase(0x004c7c80))(self, baseAnim, wiggleAnim); // rigid_instance::SetupPlant
}
inline void ri_SetAnimSpeed(void* self, float speed) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x00412510))(self, speed);         // rigid_instance::SetAnimSpeed
}
// static factory:
inline void ri_FireAndForget(const vector3* pos, const radian3* rot, const vector3* scale,
	const char* geom, const char* anim, int flagA,
	xcolor color, int flagB, int flagC, uint64_t hostGuid) {
	using Fn = void(__cdecl*)(const vector3*, const radian3*, const vector3*, const char*,
		const char*, int, xcolor, int, int, uint64_t);
	reinterpret_cast<Fn>(meridian::rebase(0x004c7a10))(pos, rot, scale, geom, anim,
		flagA, color, flagB, flagC, hostGuid); // rigid_instance::FireAndForget
}

// ============================================================================
// fx_object  --  particle/effect instance  (FXObject.cpp)
// ============================================================================
namespace fx_object_off {
	enum : uint32_t {
		kFxDescriptor = 0x14,   // xbitmap*
		kOrient = 0x68,   // radian3
		kScaleX = 0x128,  // float (also colorScaleRGB base)
		kScaleY = 0x12c,  // float
		kScaleZ = 0x130,  // float
		kColorRGBA = 0x134,  // uint8[4]
		kScale = 0x150,  // float
		kPlaybackRate = 0x150,  // float (alias: playback rate)
		kStateFlags = 0x154,  // uint8 b0 StartOnInit,b2 active,b3 looping,b4 autodestroy/pending,b6 hasLifetime
		kHostGuid = 0x158,  // uint64
		kLifetime = 0x1bc,  // float
		kDirtyFlags = 0x1b8   // uint32
	};
}
inline void* fx_ctor(void* self) {
	using Fn = void* (__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004888d0))(self);          // fx_object::fx_object
}
inline void fx_OnImport(void* self, bin_in* in) {
	using Fn = void(__thiscall*)(void*, bin_in*);
	reinterpret_cast<Fn>(meridian::rebase(0x00489850))(self, in);            // fx_object::OnImport
}
inline void fx_SetLifetime(void* self, float lifetime) {  // Ghidra label fx_object::Init
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x0048b750))(self, lifetime);      // fx_object::Init (sets lifetime @ +0x1bc)
}
inline void fx_StopThenDie(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x0048a700))(self);                // fx_object::StopThenDie
}
inline void fx_Suspend(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x0048a740))(self);                // fx_object::Suspend
}
inline void fx_OnObjectDeactivate(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x0048b6f0))(self);                // fx_object::OnObjectDeactivate
}
// static factories return the new object's Guid:
inline uint64_t fx_FireAndForget(const char* name, const vector3* pos,
	const radian3* rot, const vector3* scale) {
	using Fn = uint64_t(__cdecl*)(const char*, const vector3*, const radian3*, const vector3*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00488d30))(name, pos, rot, scale); // fx_object::FireAndForget
}
inline uint64_t fx_CreateHosted(const char* name, uint64_t hostGuid, const char* partName,
	const radian3* rot, const vector3* scale, int flag) {
	using Fn = uint64_t(__cdecl*)(const char*, uint64_t, const char*, const radian3*, const vector3*, int);
	return reinterpret_cast<Fn>(meridian::rebase(0x00488f10))(name, hostGuid, partName, rot, scale, flag); // fx_object::CreateHosted
}
inline int FXBitmapLoad(const char* name, xbitmap** out) {
	using Fn = int(__cdecl*)(const char*, xbitmap**);
	return reinterpret_cast<Fn>(meridian::rebase(0x00488c30))(name, out);    // FXBitmapLoad
}

// ============================================================================
// CharacterObject  --  base for living characters  (CharacterObject.cpp)
// ============================================================================
namespace character_off {
	enum : uint32_t {
		kPositionXZ = 0x08,   // (guid/pos overlap region)
		kFlags = 0xe0,   // uint32
		kGroundSurfaceA = 0xa8,   // uint32 (ground contact)
		kGroundSurfaceB = 0xac,   // uint32
		kGroundSurfaceFlags = 0xb1,   // uint8  b2 slippery, b5 on-stairs
		kAttachedEnemy = 0x110,  // uint64 (CharacterObject layout)
		kDetachCount = 0x118,  // int32
		kConversation = 0x128,  // void*
		kPolyCacheFrames = 0x124,  // int32
		kActiveDialogueId = 0x19c,  // int32 (-1 = none)
		kTeamId = 0x1a4   // int32 (NPCObject sets 2)
	};
}
inline void* character_ctor(void* self) {
	using Fn = void* (__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00464130))(self);          // CharacterObject::CharacterObject
}
inline void character_SetupTypeNameArray() {
	using Fn = void(__cdecl*)();
	reinterpret_cast<Fn>(meridian::rebase(0x00464560))();                     // CharacterObject::SetupTypeNameArray
}
inline int character_GetCharacterTypeFromName(/*xstring*/ void* name) {
	using Fn = int(__cdecl*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00467620))(name);          // CharacterObject::GetCharacterTypeFromName
}
inline void character_ApplyEffectToBones(void* self, const char* fxName) {
	using Fn = void(__thiscall*)(void*, const char*);
	reinterpret_cast<Fn>(meridian::rebase(0x00467710))(self, fxName);         // CharacterObject::ApplyEffectToBones
}
inline int character_IsOnStairs(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00467e90))(self);          // CharacterObject::IsOnStairs
}
inline int character_IsGroundSlippery(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00467eb0))(self);          // CharacterObject::IsGroundSlippery
}
inline void character_OnAdvanceLogic(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x00467ed0))(self, dt);             // CharacterObject::OnAdvanceLogic
}
inline void character_SolvePersonalSpace(void* self, vector3* outPush) {
	using Fn = void(__thiscall*)(void*, vector3*);
	reinterpret_cast<Fn>(meridian::rebase(0x004688e0))(self, outPush);        // CharacterObject::SolvePersonalSpace
}
inline void character_HandleMove(void* self, vector3* out, const vector3* dir,
	float a, float b, int mode, int e, int f) {
	using Fn = void(__thiscall*)(void*, vector3*, const vector3*, float, float, int, int, int);
	reinterpret_cast<Fn>(meridian::rebase(0x00469060))(self, out, dir, a, b, mode, e, f); // CharacterObject::HandleMove
}
inline int character_IsEnemy(void* self, void* other) {
	using Fn = int(__thiscall*)(void*, void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004683d0))(self, other);   // CharacterObject::IsEnemy
}
inline void character_IncrementDetachCount(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00468410))(self);                 // CharacterObject::IncrementDetachCount
}
inline uint64_t character_GetAttachedEnemy(void* self) {
	using Fn = uint64_t(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00468420))(self);          // CharacterObject::GetAttachedEnemy
}
inline void character_SetAttachedEnemy(void* self, uint64_t guid) {
	using Fn = void(__thiscall*)(void*, uint64_t);
	reinterpret_cast<Fn>(meridian::rebase(0x00468430))(self, guid);           // CharacterObject::SetAttachedEnemy
}
inline const anim_group* character_GetAnimGroup(void* self) {
	using Fn = const anim_group* (__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00469860))(self);          // CharacterObject::GetAnimGroup
}
inline int character_ProcessPolyCacheInvalidate(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004698c0))(self);          // CharacterObject::ProcessPolyCacheInvalidate
}

// ============================================================================
// NPCObject  --  AI NPC (extends CharacterObject)  (NPCObject.cpp)
// ============================================================================
namespace npc_off {
	enum : uint32_t {
		kRootedAnchorPos = 0x20,    // vector3
		kTeamId = 0x1a4,   // int32 (=2)
		kNpcTypeId = 0x1b0,   // int32 eCharacterType
		kLoadoutShield = 0x260,   // void*
		kConversationDepth = 0x264,   // int32
		kNpcFlags = 0x268,   // uint32 b3 senses?,b5 doSenses,b7 rooted,
		//   0x2000 canSleep,0x20000 dead,0x80000 sleeping,0x2000000 drawMeter
		kHitPoints = 0x290,   // float
		kDeathCinemaGuid = 0x278,   // uint64
		kDeathTimer = 0x29c,   // float
		kDeathFx = 0x2a8,   // fx_object*
		kAiController = 0x300,   // void*
		kStateController = 0x310,   // StateController (embedded)
		kLastDeltaTime = 0x45c,   // float (=1.0)
		kSleepTimer = 0x460,   // float
		kDrownTimer = 0x464,   // float
		kDeathFlags = 0x478,   // uint32 b4 cinema-started,b5 boss-meter,b6 force-die
		kPainImmuneState = 0x4e4    // int32
	};
}
inline void* npc_ctor(void* self) {
	using Fn = void* (__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x0049eff0))(self);          // NPCObject::NPCObject
}
inline void npc_LoadCharacterData(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x0049f8f0))(self);                 // NPCObject::LoadCharacterData
}
inline void npc_OnAdvanceLogic(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004a14c0))(self, dt);             // NPCObject::OnAdvanceLogic
}
inline void npc_AdvanceFullUpdate(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a1750))(self);                 // NPCObject::AdvanceFullUpdate
}
inline void npc_AdvanceSleep(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a1ad0))(self);                 // NPCObject::AdvanceSleep
}
inline void npc_AdvanceDeathTimer(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a1c30))(self);                 // NPCObject::AdvanceDeathTimer
}
inline void npc_AdvanceHealthMeter(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a1e50))(self);                 // NPCObject::AdvanceHealthMeter
}
inline void npc_AdvanceEventProcessing(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00594be0))(self);                 // NPCObject::AdvanceEventProcessing
}
inline int npc_IsBoss(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004a2340))(self);          // NPCObject::IsBoss
}
inline int npc_IsTargetable(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004a2300))(self);          // NPCObject::IsTargetable
}
inline void npc_GotoSleep(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a22a0))(self);                 // NPCObject::GotoSleep
}
inline void npc_UpdateProps(void* self, int reason) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004a29b0))(self, reason);         // NPCObject::UpdateProps
}
inline void npc_ShatterShield(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a40d0))(self);                 // NPCObject::ShatterShield
}
inline float npc_GetHitPoints(void* self) {
	using Fn = float(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004a4130))(self);          // NPCObject::GetHitPoints
}
inline void npc_TakeDamage(void* self, uint64_t sourceGuid, PainData* pain) {
	using Fn = void(__thiscall*)(void*, uint64_t, PainData*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a5130))(self, sourceGuid, pain); // NPCObject::TakeDamage
}
inline void npc_Die(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a58a0))(self);                 // NPCObject::Die
}
inline void npc_DieScumDie(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004a69a0))(self);                 // NPCObject::DieScumDie
}
inline void npc_SetIsRooted(void* self, int rooted, int snap) {
	using Fn = void(__thiscall*)(void*, int, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004a5790))(self, rooted, snap);   // NPCObject::SetIsRooted
}
inline void npc_SetDrawHealthMeter(void* self, int enable) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004a9960))(self, enable);         // NPCObject::SetDrawHealthMeter
}
inline int npc_GetDoSenses(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004a1060))(self);          // NPCObject::GetDoSenses
}
inline int npc_HasConversation(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004a1210))(self);          // NPCObject::HasConversation
}
inline uint64_t npc_GetAITarget(void* self) {
	using Fn = uint64_t(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x005b6f40))(self);          // NPCObject::GetAITarget
}

// ============================================================================
// StateController / PhysController  --  per-NPC AI + physics controllers
// ============================================================================
namespace statecontroller_off {
	enum : uint32_t {
		kEelColonyX = 0x98,   // float
		kEelColonyY = 0x9c,   // float
		kFlags = 0xe0,   // uint32 (b4 conversation flag)
		kStateCount = 0xa8,   // int32
		kStateArray = 0xac,   // State**
		kCombatParams = 0x214,  // CombatParams*
		kTriggeredCinema = 0x168  // guid/string
	};
}
namespace physcontroller_off {
	enum : uint32_t {
		kGroundConfig = 0x34,   // void* (+0 MaxGroundDist, +4 MinGroundDist)
		kFlags = 0x4c,   // uint32 (b1 head-track active)
		kAnimSet = 0x9c,   // handle
		kCurrentAnimIndex = 0xa0,   // int32 (-1 none)
		kRenderInstance = 0x98,   // void*
		kHeadTrackTarget = 0xf8,   // uint64
		kIdleAnimName = 0x110   // char[]
	};
}
inline void state_LoadStates(void* self, /*xwstring*/ void* baseName) {
	using Fn = void(__thiscall*)(void*, void*);
	reinterpret_cast<Fn>(meridian::rebase(0x005ad7b0))(self, baseName);       // StateController::LoadStates
}
inline void state_OnImport(void* self, bin_in* in) {
	using Fn = void(__thiscall*)(void*, bin_in*);
	reinterpret_cast<Fn>(meridian::rebase(0x005b0190))(self, in);            // StateController::OnImport
}
inline void phys_LoadAnims(void* self, /*xstring*/ void* baseName) {
	using Fn = void(__thiscall*)(void*, void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00591540))(self, baseName);      // PhysController::LoadAnims
}
inline void phys_UpdateHeadTracking(void* self, float a, float b, int c) {
	using Fn = void(__thiscall*)(void*, float, float, int);
	reinterpret_cast<Fn>(meridian::rebase(0x00594990))(self, a, b, c);       // PhysController::UpdateHeadTracking
}
inline void phys_UpdateCinemaAnim(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00595170))(self);                // PhysController::UpdateCinemaAnim
}
inline AnimInfo* phys_GetAnimInfoFromName(void* self, const char* name) {
	using Fn = AnimInfo * (__thiscall*)(void*, const char*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00594390))(self, name);   // PhysController::GetAnimInfoFromName
}

// ============================================================================
// trigger  --  volume trigger base  (Trigger.cpp)
// ============================================================================
namespace trigger_off {
	enum : uint32_t {
		kTriggerIndex = 0x04,   // int32 (AI subclasses)
		kFiredFlags = 0x08,   // uint32 (AI subclasses)
		kInsideCount = 0x108,  // int32
		kInsideList = 0x10c,  // uint64*
		kAttrMask = 0x11c,  // uint32
		kFlags = 0x120,  // uint32 (see doc for bit map)
		kRequiredItemCount = 0x138,  // int32
		kRequiredItemIds = 0x13c,  // int32*
		kCapacity = 0x140,  // int32
		kOwnsArray = 0x144,  // int32
		kTargetCount = 0x14c,  // int32 (also useMode)
		kPendingCheckState = 0x154,  // int32
		kHeldItemCount = 0x160,  // int32
		kHeldItemIds = 0x164,  // int32*
		kAllowedItemLists = 0x19c,  // void* (stride 0x1c per slot)
		kRetriggerTimer = 0x1b0   // float
	};
}
inline void trigger_OnAdvanceLogic(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x004dd480))(self, dt);            // trigger::OnAdvanceLogic
}
inline void trigger_OnUse(void* self, int itemId) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004dcef0))(self, itemId);        // trigger::OnUse
}
inline void trigger_UseItems(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004dd060))(self);                // trigger::UseItems
}
inline void trigger_EjectItems(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004dd1b0))(self);                // trigger::EjectItems
}
inline int trigger_IsFull(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004dd210))(self);         // trigger::IsFull
}
inline const char* trigger_GetItemName(void* self, int index) {
	using Fn = const char* (__thiscall*)(void*, int);
	return reinterpret_cast<Fn>(meridian::rebase(0x004dd230))(self, index);  // trigger::GetItemName
}
inline int trigger_GetItemType(void* self, int index) {
	using Fn = int(__thiscall*)(void*, int);
	return reinterpret_cast<Fn>(meridian::rebase(0x004dd290))(self, index);  // trigger::GetItemType
}
inline int trigger_GetUseInventory(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004dd2c0))(self);         // trigger::GetUseInventory
}
inline void trigger_OnPressB(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004dd2d0))(self);                // trigger::OnPressB
}
inline void trigger_OnPain(void* self, uint64_t src, const vector3* pos,
	float a, float b, float c, int d) {
	using Fn = void(__thiscall*)(void*, uint64_t, const vector3*, float, float, float, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004de270))(self, src, pos, a, b, c, d); // trigger::OnPain
}
inline void trigger_OnActivate(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004de300))(self);                // trigger::OnActivate
}
inline void trigger_SetAttrMask(void* self, uint32_t mask) {
	using Fn = void(__thiscall*)(void*, uint32_t);
	reinterpret_cast<Fn>(meridian::rebase(0x004de5f0))(self, mask);          // trigger::SetAttrMask
}
inline void trigger_SetTriggered(void* self, int triggered) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004de610))(self, triggered);     // trigger::SetTriggered
}
inline int trigger_GetWasTriggered(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004de640))(self);         // trigger::GetWasTriggered
}
inline void trigger_SetSaveInside(void* self, int save) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004de650))(self, save);          // trigger::SetSaveInside
}
inline void trigger_Enable(void* self, int enable) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004de6b0))(self, enable);        // trigger::Enable
}
inline int trigger_IsEnabled(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004de6d0))(self);         // trigger::IsEnabled
}
inline int trigger_IsTriggered(void* self) {
	using Fn = int(__thiscall*)(void*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004df1b0))(self);         // trigger::IsTriggered
}
inline int trigger_DrawIndicator(void* self, const vector3* queryPoint) {
	using Fn = int(__thiscall*)(void*, const vector3*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004df1c0))(self, queryPoint); // trigger::DrawIndicator
}
inline int trigger_IsInside(void* self, const uint64_t* objGuid) {
	using Fn = int(__thiscall*)(void*, const uint64_t*);
	return reinterpret_cast<Fn>(meridian::rebase(0x004e19b0))(self, objGuid); // trigger::IsInside
}
inline void trigger_ForceCheckEnter(void* self, int force) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004e1a10))(self, force);         // trigger::ForceCheckEnter
}
inline void trigger_SetOneTimeShot(void* self, int oneTime) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004e1a90))(self, oneTime);       // trigger::SetOneTimeShot
}
inline void trigger_OnReset(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004dcd80))(self);                // trigger::OnReset
}

// ============================================================================
// AITrigger family  --  editor/runtime AI condition triggers (AITrigger.cpp)
//   Common members: +0x04 triggerIndex, +0x08 firedFlags, +0x10/+0x18 guids,
//   +0x20 triggersOnce, +0x24 onceLatch.
// ============================================================================
inline int aitrigger_SetProperty(void* self, const char* name, const property* value) {
	using Fn = int(__thiscall*)(void*, const char*, const property*);
	return reinterpret_cast<Fn>(meridian::rebase(0x005f1cf0))(self, name, value); // AITrigger::SetProperty
}
inline void aitrigger_OnImport(void* self, bin_in* in) {
	using Fn = void(__thiscall*)(void*, bin_in*);
	reinterpret_cast<Fn>(meridian::rebase(0x005f1e70))(self, in);            // AITrigger::OnImport
}
// TriggerWorldTriggerToggled base property handlers (recovered from FUN_*):
inline int twtt_SetProperty(void* self, const char* name, const property* value) {
	using Fn = int(__thiscall*)(void*, const char*, const property*);
	return reinterpret_cast<Fn>(meridian::rebase(0x005f17e0))(self, name, value); // TriggerWorldTriggerToggled::SetProperty
}
inline void twtt_EnumerateProperties(void* self, xarray<property_desc>* out) {
	using Fn = void(__thiscall*)(void*, xarray<property_desc>*);
	reinterpret_cast<Fn>(meridian::rebase(0x005f1470))(self, out);           // TriggerWorldTriggerToggled::EnumerateProperties
}
// Note: TriggerWorldTriggerToggled::GetProperty @0x005f19b0 returns property by value (RVO).

// ============================================================================
// load_trigger / ambient_audio_trigger / music_trigger  (audio + load volumes)
// ============================================================================
inline void loadtrigger_Init(void* self, const vector3* center, const bbox* box) {
	using Fn = void(__thiscall*)(void*, const vector3*, const bbox*);
	reinterpret_cast<Fn>(meridian::rebase(0x00497600))(self, center, box);   // load_trigger::Init
}
inline void loadtrigger_OnImport(void* self, bin_in* in) {
	using Fn = void(__thiscall*)(void*, bin_in*);
	reinterpret_cast<Fn>(meridian::rebase(0x00499930))(self, in);            // load_trigger::OnImport
}
inline void loadtrigger_OnExport(void* self, bin_out* out) {
	using Fn = void(__thiscall*)(void*, bin_out*);
	reinterpret_cast<Fn>(meridian::rebase(0x004860f0))(self, out);           // load_trigger::OnExport
}
inline void aat_Init(void* self, const vector3* center, const bbox* box) {
	using Fn = void(__thiscall*)(void*, const vector3*, const bbox*);
	reinterpret_cast<Fn>(meridian::rebase(0x00454e40))(self, center, box);   // ambient_audio_trigger::Init
}
inline void aat_OnImport(void* self, bin_in* in) {
	using Fn = void(__thiscall*)(void*, bin_in*);
	reinterpret_cast<Fn>(meridian::rebase(0x0053b1a0))(self, in);            // ambient_audio_trigger::OnImport
}
inline int aat_SetProperty(void* self, const char* name, const property* value) {
	using Fn = int(__thiscall*)(void*, const char*, const property*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00455a20))(self, name, value); // ambient_audio_trigger::SetProperty
}
inline void aat_CheckForCrossing(void* self, vector3 prev, vector3 cur) {
	using Fn = void(__thiscall*)(void*, vector3, vector3);
	reinterpret_cast<Fn>(meridian::rebase(0x004551c0))(self, prev, cur);     // ambient_audio_trigger::CheckForCrossing
}
inline void aat_OnTriggerRedToGreen(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x004554a0))(self);                // ambient_audio_trigger::OnTriggerRedToGreen
}
inline void aat_OnTriggerGreenToRed(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00455570))(self);                // ambient_audio_trigger::OnTriggerGreenToRed
}
inline void musictrigger_OnExport(void* self, bin_out* out) {
	using Fn = void(__thiscall*)(void*, bin_out*);
	reinterpret_cast<Fn>(meridian::rebase(0x00456bb0))(self, out);           // music_trigger::OnExport
}
inline int musictrigger_SetProperty(void* self, const char* name, const property* value) {
	using Fn = int(__thiscall*)(void*, const char*, const property*);
	return reinterpret_cast<Fn>(meridian::rebase(0x00539d90))(self, name, value); // music_trigger::SetProperty
}
inline void musictrigger_Init(void* self) {  // Ghidra labeled ~music_trigger
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00538bd0))(self);                // music_trigger::Init
}
inline void InitializeTriggerActionTypeList() {
	using Fn = void(__cdecl*)();
	reinterpret_cast<Fn>(meridian::rebase(0x005385e0))();                    // InitializeTriggerActionTypeList
}

// ============================================================================
// obj_mgr  --  object manager singleton (@ 0x0076cd88)
//   GUID hash: bucket = ((lo^hi) * -0xfb) & 0xfff; slot array @ 0x0076f648,
//   stride 0x14: +0x00 object*, +0x08 Guid, +0x0e nextIndex(i16).
// ============================================================================
namespace obj_mgr_globals {
	static constexpr uintptr_t kSingleton = 0x0076cd88; // obj_mgr instance
	static constexpr uintptr_t kSlotArray = 0x0076f648; // ObjEntry[] stride 0x14
}
inline void* obj_mgr_singleton() { return meridian::rebase(obj_mgr_globals::kSingleton); }

inline void objmgr_DestroyObject(void* self, uint64_t guid) {
	using Fn = void(__thiscall*)(void*, uint64_t);
	reinterpret_cast<Fn>(meridian::rebase(0x00406bf0))(self, guid);          // obj_mgr::DestroyObject
}

// ============================================================================
// render_mgr  --  frame renderer
// ============================================================================
namespace render_mgr_off {
	enum : uint32_t {
		kAmbientLightFlag = 0x98,   // int32
		kShadowLightFlag = 0x9c,   // int32
		kCurrentFogMode = 0x150,  // int32
		kFogSupported = 0x154,  // int32
		kUseCustomFogRange = 0x158,  // int32
		kCustomFogFar = 0x15c   // float
	};
}
inline void rendermgr_Render(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00586880))(self);                // render_mgr::Render
}
inline void rendermgr_EnableFog(void* self, int mode) {
	using Fn = void(__thiscall*)(void*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x00587d00))(self, mode);          // render_mgr::EnableFog
}
inline void rendermgr_RenderSkybox(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00585190))(self);                // render_mgr::RenderSkybox
}
inline void rendermgr_RenderLights(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00584f20))(self);                // render_mgr::RenderLights
}
inline void rendermgr_RenderStingGlow(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00586ff0))(self);                // render_mgr::RenderStingGlow
}
inline void rendermgr_RenderSpecialPickupEffects(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00587fc0))(self);                // render_mgr::RenderSpecialPickupEffects (Ghidra: EnableFog)
}
inline void render_task_mgr_Sort(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x005c33e0))(self);                // render_task_mgr::Sort
}
inline void render_task_mgr_RenderSorted(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x005c3d30))(self);                // render_task_mgr::RenderSorted
}

// ============================================================================
// camera_mgr  --  camera state machine
// ============================================================================
namespace camera_mgr_off {
	enum : uint32_t {
		kCameraFlags = 0x484,  // uint32 (b2,b4 lookat override)
		kFollowBilboFlag = 0x498,  // int32
		kLookatTargetGuid = 0x688,  // uint64
		kStaticInfluenceGuid = 0x6a0,  // uint64
		kObstructionModGuid = 0x6a8,  // uint64
		kScriptedOverride = 0x714,  // int32
		kOverridePosition = 0x718,  // vector3
		kOverrideOrientation = 0x724,  // radian3
		kCameraRig = 0x730   // void* (+0xe0 FOV, +0xe4/+0xe8 clip)
	};
}
inline int cameramgr_SetState(void* self, int state, int flag) {
	using Fn = int(__thiscall*)(void*, int, int);
	return reinterpret_cast<Fn>(meridian::rebase(0x0056d5e0))(self, state, flag); // camera_mgr::SetState
}
inline void cameramgr_ApplyView(void* self) {  // Ghidra labeled GetProperty
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x0056b420))(self);                // camera_mgr::ApplyView
}
inline void cameramgr_AdvanceStatic(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x00570ee0))(self, dt);            // camera_mgr::AdvanceStatic
}
inline void cameramgr_AdvanceAvoidObstruction(void* self, float dt) {
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x00571090))(self, dt);            // camera_mgr::AdvanceAvoidObstruction
}
inline void cameramgr_CheckForModifier(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x005717e0))(self);                // camera_mgr::CheckForModifier
}
inline void cameramgr_CheckForInfluencer(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x005712d0))(self);                // camera_mgr::CheckForInfluencer
}

// ============================================================================
// event_mgr  --  anim-event dispatch
//   Event list: +0x08 count, +0x0c data (stride 0x18).
// ============================================================================
inline void eventmgr_Init(void* self) {
	using Fn = void(__thiscall*)(void*);
	reinterpret_cast<Fn>(meridian::rebase(0x00571f10))(self);                // event_mgr::Init
}
inline void eventmgr_OnAdvanceLogic(void* self, float dt) {  // Ghidra: xarray<vector3>::Append
	using Fn = void(__thiscall*)(void*, float);
	reinterpret_cast<Fn>(meridian::rebase(0x00572970))(self, dt);            // event_mgr::OnAdvanceLogic
}
inline void eventmgr_ApplyPainFromTable(void* self, int tableIdx, uint64_t guid,
	vector3 origin, float amount, unsigned mask, int extra) {
	using Fn = void(__thiscall*)(void*, int, uint64_t, vector3, float, unsigned, int);
	reinterpret_cast<Fn>(meridian::rebase(0x00572ce0))(self, tableIdx, guid, origin, amount, mask, extra); // event_mgr::ApplyPainFromTable
}
inline void eventmgr_HandleContactAudioEvent(void* self, const void* animEvent,
	const vector3* pos, uint64_t srcGuid) {
	using Fn = void(__thiscall*)(void*, const void*, const vector3*, uint64_t);
	reinterpret_cast<Fn>(meridian::rebase(0x00573ed0))(self, animEvent, pos, srcGuid); // event_mgr::HandleContactAudioEvent
}
inline void eventmgr_HandlePainEvent(void* self, const void* animEvent,
	const vector3* pos, uint64_t srcGuid) {
	using Fn = void(__thiscall*)(void*, const void*, const vector3*, uint64_t);
	reinterpret_cast<Fn>(meridian::rebase(0x00574c00))(self, animEvent, pos, srcGuid); // event_mgr::HandlePainEvent
}

// ============================================================================
// collmesh  --  collision mesh  (CollMesh.cpp)
//   +0x00 magic/version 0x7d2, +0x64 numTris, +0x68/+0x6c/+0x70 array ptrs.
// ============================================================================
inline void collmesh_Build(collmesh* self, const vector3* verts, int numTris,
	const uint8_t* indices, char* name) {
	using Fn = void(__thiscall*)(collmesh*, const vector3*, int, const uint8_t*, char*);
	reinterpret_cast<Fn>(meridian::rebase(0x005a5d80))(self, verts, numTris, indices, name); // collmesh::Build
}

// ============================================================================
// matrix4 / Hud_3D_Object  --  misc helpers
// ============================================================================
inline void matrix4_Rotate(matrix4* self, const radian3* euler) {
	using Fn = void(__thiscall*)(matrix4*, const radian3*);
	reinterpret_cast<Fn>(meridian::rebase(0x00463c20))(self, euler);         // matrix4::Rotate
}
inline void hud3d_Set(void* self, vector4 transform, const char* resource) {
	using Fn = void(__thiscall*)(void*, vector4, const char*);
	reinterpret_cast<Fn>(meridian::rebase(0x004f93e0))(self, transform, resource); // Hud_3D_Object::Set
}

// ============================================================================
// Script / trigger free helpers  (Trigger.cpp + script VM)
// ============================================================================
inline void AddInvenItem(const char* itemName, int qty) {
	using Fn = void(__cdecl*)(const char*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004dba10))(itemName, qty);       // AddInvenItem
}
inline void HideRigidInstanceByName(const char* name, int hide) {
	using Fn = void(__cdecl*)(const char*, int);
	reinterpret_cast<Fn>(meridian::rebase(0x004dbcd0))(name, hide);          // HideRigidInstanceByName
}
inline void ActivateLoadTrigger(const char* name) {
	using Fn = void(__cdecl*)(const char*);
	reinterpret_cast<Fn>(meridian::rebase(0x0040cc40))(name);                // ActivateLoadTrigger (stub)
}
