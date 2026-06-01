// ============================================================================
//  projectile_sdk.h  —  PROJECTILE subsystem SDK for THE HOBBIT (2003) PC build
//  Entropy engine, MSVC, 32-bit (Meridian.exe).
//
//  Reverse-engineered modding / trainer SDK. All addresses are absolute PC
//  virtual addresses; resolve them at runtime with meridian::rebase(0xADDR)
//  which applies the current module-base delta vs the analyzed image base.
//
//  The PROJECTILE subsystem models thrown stones, falling boulders, the
//  Gandalf-staff / lightning-discharge attacks, and their motion trails.
//  A Projectile is an engine `object` (its base) with a MotionLinear driver,
//  a ground-shadow helper (Projectile::shadow), a trail FX object, a swoosh
//  ribbon FX, and a per-type definition row from a static type-def table.
//
//  Field offsets in the struct below are CONSOLIDATED from the single per-chunk
//  analysis (evidence-backed in projectile__00.json). Offsets marked "?" are
//  lower confidence. Only well-evidenced fields are declared as named members;
//  everything else is explicit padding so named members land at their true
//  byte offsets. The struct is NOT meant to be instantiated — only
//  reinterpret_cast onto a live Projectile* obtained from a GUID slot.
//
//  ---- USAGE / RECIPE ------------------------------------------------------
//    using namespace projectile_sdk;
//    // Spawn a stone from owner `bilboGuid` at `from` aimed at `to`:
//    uint64_t guid = fn::CreateProjectileByType(
//        (uint32_t)eProjType::ThrownStone, bilboGuid, from, to);
//    // Resolve it later from the obj_mgr slot, then poke fields:
//    Projectile* p = reinterpret_cast<Projectile*>(slotPtr);
//    p->lifetime = 5.0f;          // extend time-to-live
//    fn::KillTrail(p);            // detach the trail FX manually
//
//  __thiscall wrappers take the object pointer as the FIRST argument.
//  Statics / creators are __cdecl. Any method taking an INCOMPLETE engine type
//  (xcolor) BY VALUE cannot be expressed as a typed wrapper — those expose an
//  address accessor (*_at) plus the raw signature in a comment instead.
// ============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase, vector3, radian3, matrix4, bbox, xstring, xcolor (fwd), Ghidra aliases

// ---- Forward declarations for engine types we don't fully model -------------
// (Most are already declared in meridian_types.h; re-declaring a struct name is
//  harmless and keeps this header readable standalone.)
// NOTE: the engine's `Projectile` class is forward-declared GLOBALLY in
// meridian_types.h. We model its byte layout below as projectile_sdk::Projectile
// to avoid a one-definition clash with that opaque global forward-declaration;
// always refer to the layout as projectile_sdk::Projectile (do not bring it into
// global scope alongside `using namespace projectile_sdk;` if the global engine
// forward-decl is also visible).
struct object;              // engine base of Projectile
struct MotionLinear;        // linear-motion driver attached at Projectile+0x158
struct collision;           // collision_mgr::collision record (Impact arg)
struct obj_mgr;
struct Switch;
struct bilbo;
struct fx_object;
struct xbitmap;
struct xcolor;              // INCOMPLETE here; passed BY VALUE by InitSwoosh
struct xstring;

namespace projectile_sdk {

// ===========================================================================
//  1. Projectile type enum  (Projectile::eProjectileType)
//     Stored at Projectile+0x180. Indexes the static type-def table that
//     begins near &DAT_0075d490 with a stride of 0x24 bytes (9 dwords) per row.
//     Names below are derived from the type-name strings referenced by
//     CreateProjectile ('FallingBoulder','GandalfStaff','Props', ...).
//     Numeric values are tentative ordering; 0x17/0x18 are the two indices
//     that Impact treats as Bilbo-jump-level-scaled damage attacks.
// ===========================================================================
enum class eProjType : uint32_t {
    ThrownStone        = 0x00,  // Bilbo's stone / sling throw (best-guess index)
    FallingBoulder     = 0x01,  // "FallingBoulder" type-def row
    GandalfStaff       = 0x02,  // "GandalfStaff" discharge bolt
    Props              = 0x03,  // generic thrown prop
    // ... additional rows exist in the type-def table ...
    JumpScaledA        = 0x17,  // Impact applies bilbo::GetJumpLevel-scaled damage
    JumpScaledB        = 0x18,  // Impact applies bilbo::GetAEJumpLevel-scaled damage
};

// OnAdvanceLogic dispatches on the sub-mode field at Projectile+0x184.
enum class eProjSubMode : int32_t {
    Normal     = 0,   // straight ballistic / motion-driven
    Discharge  = 3,   // lightning-discharge re-fire on a 1.0s timer (+0x178)
    PathFollow = 4,   // path / sub-timer driven branch (+0x17c)
};

// ===========================================================================
//  2. Projectile::shadow  —  ground-shadow helper (nested, 8 bytes)
//     Loads ShadowDisc.xbmp; allocated by Projectile::SetupShadow into
//     Projectile+0x1ac. handle starts at 0x7fffffff (invalid sentinel).
// ===========================================================================
#pragma pack(push, 1)
struct ProjectileShadow {
    int32_t  handle;        // 0x00  invalid-handle sentinel 0x7fffffff at ctor
    uint32_t discBitmap;    // 0x04  xbitmap handle for "ShadowDisc.xbmp"
};                          // sizeof == 0x08 (operator_new(8) in SetupShadow)
#pragma pack(pop)

// ===========================================================================
//  3. Projectile  —  main class (consolidated layout)
//     Cast a live slot pointer to Projectile*. Do NOT instantiate.
//     #pragma pack(1) so explicit padding lands members at true offsets.
//     The leading region (vtable .. 0x14) is inherited from `object`.
// ===========================================================================
#pragma pack(push, 1)
struct Projectile {
    void*    vtable;                         // 0x000  vtbl: +0x14 SetPos, +0x28 GetPos, +0x1c SetOrient (used by SetupBBox/UpdateTrail)
    uint8_t  _pad004[0x14 - 0x04];           // 0x004  object base header
    // ---- world position (vector3) ---------------------------------------
    float    posX;                           // 0x014  Render matrix translation X; UpdateTrail heading source
    float    posY;                           // 0x018  Render translation Y
    float    posZ;                           // 0x01c  Render translation Z
    uint8_t  _pad020[0x2c - 0x20];           // 0x020
    // ---- local-space bounding box (min then max) ------------------------
    float    bboxMinX;                       // 0x02c  SetupBBox min (default -50.0)
    float    bboxMinY;                       // 0x030
    float    bboxMinZ;                       // 0x034
    float    bboxMaxX;                       // 0x038  SetupBBox max (default +50.0)
    float    bboxMaxY;                       // 0x03c
    float    bboxMaxZ;                        // 0x040
    uint8_t  _pad044[0x68 - 0x44];           // 0x044
    // ---- orientation (radian3: pitch/yaw/roll) --------------------------
    float    rotPitch;                       // 0x068  Render: matrix4::Rotate(m, (radian3*)+0x68)
    float    rotYaw;                         // 0x06c
    float    rotRoll;                        // 0x070
    uint8_t  _pad074[0xa8 - 0x74];           // 0x074
    uint32_t modelRef;                       // 0x0a8  model/mesh handle (0x7fffffff sentinel); SetupBBox source bbox
    uint8_t  _pad0ac[0xd4 - 0xac];           // 0x0ac
    // ---- render scale (Render matrix scale row) -------------------------
    float    scaleX;                         // 0x0d4
    float    scaleY;                         // 0x0d8
    float    scaleZ;                         // 0x0dc
    float    renderBoundsMinX;               // 0x0e0  Render resets to -1.0 (0xbf800000)
    float    renderBoundsMinY;               // 0x0e4
    float    renderBoundsMinZ;               // 0x0e8
    uint8_t  _pad0ec[0xfc - 0xec];           // 0x0ec
    int32_t  childCount;                     // 0x0fc  ~Projectile drains child list while >0
    uint8_t  _pad100[0x158 - 0x100];         // 0x100
    MotionLinear* motion;                    // 0x158  motion driver; vtbl+4=advance (OnAdvanceLogic), vtbl[0]=dtor (~Projectile)
    float    age;                            // 0x15c  OnAdvanceLogic accumulates += dt
    uint32_t ownerGuidLo;                    // 0x160  spawning owner GUID low dword
    uint32_t ownerGuidHi;                    // 0x164  spawning owner GUID high dword
    int32_t  expiredFlag;                    // 0x168  set 1 when age >= lifetime (gates destroy/impact)
    uint8_t  _pad16c[0x170 - 0x16c];         // 0x16c
    uint32_t hitGuidLo;                      // 0x170  Impact: collision+0x30 (hit object GUID low)
    uint32_t hitGuidHi;                      // 0x174  Impact: collision+0x34 (hit object GUID high)
    float    dischargeTimer;                 // 0x178  sub-mode 3: reset to 1.0, decremented by dt
    float    subTimer;                       // 0x17c  sub-mode 4: path/sign-tested timer
    uint32_t type;                           // 0x180  eProjectileType; indexes type-def table at type*0x24
    int32_t  subMode;                        // 0x184  OnAdvanceLogic switch (eProjSubMode)
    uint8_t  _pad188[0x18c - 0x188];         // 0x188
    float    lifetime;                       // 0x18c  expiry threshold compared to age
    float    alphaScale;                     // 0x190  init 1.0; trail color/scale param
    // ---- target / destination position (vector3) ------------------------
    float    targetX;                        // 0x194  CreateProjectile dest; UpdateTrail heading dest
    float    targetY;                        // 0x198
    float    targetZ;                        // 0x19c
    uint32_t trailGuidLo;                    // 0x1a0  trail FX object GUID low (InitTrail/UpdateTrail/KillTrail)
    uint32_t trailGuidHi;                    // 0x1a4  trail FX object GUID high
    int32_t  hostedFxHandle;                 // 0x1a8  secondary hosted trail/swoosh FX handle
    ProjectileShadow* shadow;                // 0x1ac  ground-shadow helper (SetupShadow / ~Projectile)
    int32_t  swooshHandle;                   // 0x1b0  swoosh ribbon FX handle (-1 / >=0 sentinel)
    int32_t  advanceFlag;                    // 0x1b4  OnAdvanceLogic resets to 0 in expiry branch
};                                           // size >= 0x1b8
#pragma pack(pop)

// ===========================================================================
//  4. Typed call wrappers
//     __thiscall: object pointer is the FIRST argument.
//     vector3 IS a complete type (meridian_types.h), so the by-value vector3
//     creator/static signatures are ABI-safe to express directly.
// ===========================================================================
namespace fn {

// ---- Lifecycle: construct / destroy ----------------------------------------
// Projectile::Projectile(void) — placement ctor over an allocated block.
inline Projectile* ctor(Projectile* p) {
    using F = Projectile* (__thiscall*)(Projectile*);
    return reinterpret_cast<F>(meridian::rebase(0x004b6620))(p);
}
// Projectile::~Projectile(void) — tears down shadow, motion, swoosh, trail, kids.
inline void dtor(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004b65a0))(p);
}
// virtual `vector deleting destructor'(uint flags) — runs ~Projectile then frees if flags&1.
inline void* VectorDeletingDtor(Projectile* p, unsigned int flags) {
    using F = void* (__thiscall*)(Projectile*, unsigned int);
    return reinterpret_cast<F>(meridian::rebase(0x004b6580))(p, flags);
}

// ---- Static factory ---------------------------------------------------------
// Projectile::CreateProjectile(eProjectileType, owner, from, to) -> new GUID.
// vector3 is complete, so the by-value ABI is reproduced faithfully.
inline uint64_t CreateProjectileByType(uint32_t type, uint64_t ownerGuid,
                                       vector3 from, vector3 to) {
    using F = uint64_t (__cdecl*)(uint32_t, uint64_t, vector3, vector3);
    return reinterpret_cast<F>(meridian::rebase(0x004b53a0))(type, ownerGuid, from, to);
}
// Projectile::CreateProjectile(xstring name, owner, from, to) -> new GUID.
// xstring IS complete in meridian_types.h (sizeof 0x2c), so by-value is safe.
inline uint64_t CreateProjectileByName(xstring name, uint64_t ownerGuid,
                                       vector3 from, vector3 to) {
    using F = uint64_t (__cdecl*)(xstring, uint64_t, vector3, vector3);
    return reinterpret_cast<F>(meridian::rebase(0x004b52b0))(name, ownerGuid, from, to);
}
// class object* ProjectileCreator(void) — engine object-factory entry for the
// Projectile class id (raw thunk address from the API bundle, name only).
// Raw sig: object* __cdecl ProjectileCreator(void)
//   (address not present in the analyzed chunk; expose accessor only if found)

// ---- Static: lightning / electric discharge --------------------------------
// Projectile::LightningDischargeAttack(owner, from, to) — arc FX (color 0xffb4e6ff).
inline void LightningDischargeAttack(uint64_t ownerGuid, vector3 from, vector3 to) {
    using F = void (__cdecl*)(uint64_t, vector3, vector3);
    reinterpret_cast<F>(meridian::rebase(0x004b6230))(ownerGuid, from, to);
}

// ---- Per-frame logic & collision -------------------------------------------
// virtual Projectile::OnAdvanceLogic(float dt) — main tick.
inline void OnAdvanceLogic(Projectile* p, float dt) {
    using F = void (__thiscall*)(Projectile*, float);
    reinterpret_cast<F>(meridian::rebase(0x004b66e0))(p, dt);
}
// virtual Projectile::OnCheckCollision(void) — collision broadphase hook.
inline void OnCheckCollision(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004e3f20 /* see note */))(p);
    // NOTE: OnCheckCollision address was not separately captured in the chunk;
    //       if the live vtable differs, resolve via the vtable slot instead.
}
// Projectile::Impact(collision_mgr::collision const&) -> int (damage/applied).
inline int Impact(Projectile* p, const collision* hit) {
    using F = int (__thiscall*)(Projectile*, const collision*);
    return reinterpret_cast<F>(meridian::rebase(0x004b7ce0))(p, hit);
}

// ---- Rendering --------------------------------------------------------------
// virtual Projectile::Render(void) — builds world transform & submits.
inline void Render(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004e3f20))(p);
}

// ---- BBox -------------------------------------------------------------------
// Projectile::SetupBBox(matrix4&) — matrix4 is complete; pass by reference.
inline void SetupBBox(Projectile* p, matrix4& xform) {
    using F = void (__thiscall*)(Projectile*, matrix4*);
    reinterpret_cast<F>(meridian::rebase(0x004b7b20))(p, &xform);
}

// ---- Trail FX (Init / Update / Kill) ---------------------------------------
inline void InitTrail(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004b81c0))(p);
}
inline void UpdateTrail(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004b82c0))(p);
}
inline void KillTrail(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004b83e0))(p);
}

// ---- Swoosh ribbon FX -------------------------------------------------------
// Projectile::InitSwoosh(uchar startCnt, uchar endCnt, xcolor color, const char* tex)
// xcolor is an INCOMPLETE type passed BY VALUE; the by-value signature cannot be
// formed here. Use the address accessor and cast at the call site once you have
// a concrete xcolor layout.
//   Raw sig: void __thiscall Projectile::InitSwoosh(uchar,uchar,xcolor,const char*)
inline void* InitSwoosh_at() { return meridian::rebase(0x004b8450); }

// Projectile::SetSwooshAlpha(float startA, float endA, int mode)
inline void SetSwooshAlpha(Projectile* p, float startAlpha, float endAlpha, int mode) {
    using F = void (__thiscall*)(Projectile*, float, float, int);
    reinterpret_cast<F>(meridian::rebase(0x004b8560))(p, startAlpha, endAlpha, mode);
}

// ---- Ground shadow ----------------------------------------------------------
inline void SetupShadow(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004b84e0))(p);
}
inline void UpdateShadow(Projectile* p) {
    using F = void (__thiscall*)(Projectile*);
    reinterpret_cast<F>(meridian::rebase(0x004b8580 /* see note */))(p);
    // NOTE: UpdateShadow address not separately captured; resolve via the
    //       Projectile vtable / nearby SetSwooshAlpha block if it differs.
}
// Projectile::shadow::shadow(void) — ctor; loads ShadowDisc.xbmp.
inline ProjectileShadow* Shadow_ctor(ProjectileShadow* s) {
    using F = ProjectileShadow* (__thiscall*)(ProjectileShadow*);
    return reinterpret_cast<F>(meridian::rebase(0x004b51b0))(s);
}

// ---- FX pool helper (proposed; generic, not Projectile-specific) ------------
// fx_pool::ReleaseSlot(int slotIndex) — release a pooled swoosh/FX slot.
// Used by InitSwoosh/~Projectile to free Projectile+0x1b0. `this` is the pool.
inline void Fx_ReleaseSlot(void* pool, int slotIndex) {
    using F = void (__thiscall*)(void*, int);
    reinterpret_cast<F>(meridian::rebase(0x005c1ed0))(pool, slotIndex);
}

} // namespace fn

} // namespace projectile_sdk
