// =============================================================================
// animation_sdk.h  —  THE HOBBIT (2003) PC build, Entropy engine (MSVC, 32-bit)
//
// Reverse-engineered SDK wrappers for the "animation" subsystem.
// Legitimate RE of the user's own game for SDK / interop purposes.
//
// All addresses are PREFERRED-base (image base 0x00400000). Resolve at runtime
// with meridian::rebase(0xADDR) — set meridian::g_delta once at init if the
// image is rebased (ASLR). Calling convention is __thiscall (this in ECX)
// unless the typedef says __cdecl.
//
// Struct offsets are documented as comments. Layouts are partial (only the
// fields recovered with evidence are named); pads keep the verified offsets.
// =============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase + g_delta, vector3/matrix4/quaternion/radian3, xarray<T>, ...

// ---- Forward declarations for opaque / cross-subsystem types ----------------
struct anim_group;
struct anim_loader;
struct anim_key_block;
struct anim_key_stream;
struct rawanim;
struct char_anim_player;
struct simple_anim_player;
struct anim_track_controller;
struct anim_info;
struct anim_key;
struct rhandle;

// =============================================================================
// Recovered struct layouts
// =============================================================================

// rawanim — authoring-time skeleton + raw TRS key container (RawAnim.cpp).
// Header object; owns a bone array (0x1c4-byte records) plus aux key/child arrays.
struct rawanim_layout {
    /* 0x00 */ void* pBones;     // bone* — array of nBones records, 0x1c4 each
    /* 0x04 */ std::int32_t nBones;
    /* 0x08 */ void* auxArray0;  // tracked-free buffer (RawAnim.cpp:0x24)
    /* 0x0c */ std::int32_t nKeys; // also used as a flag in Load
    /* 0x10 */ void* auxArray2;
    /* 0x14 */ std::uint32_t _pad14;
    /* 0x18 */ void* auxArray3;
    /* 0x1c */ std::uint32_t _pad1c;
    /* 0x20 */ void* auxArray4;
    /* 0x24 */ std::uint32_t _pad24;
    /* 0x28 */ void* auxArray5;
};

// rawanim::bone — one skeleton bone record (0x1c4 bytes).
struct rawanim_bone {
    /* 0x000 */ std::int32_t Index;
    /* 0x004 */ std::int32_t iParent;     // scanned by DeleteBone (stride 0x1c4)
    /* 0x008 */ std::int32_t nChildren;
    /* 0x00c */ char         name[0x11c]; // name/data block up to Scale
    /* 0x128 */ vector3      Scale;       // Rotate fields follow
    /* ...   */                            // total record size 0x1c4
};

// anim_group — runtime animation asset (AnimGroup.cpp), 0x88 bytes.
struct anim_group_layout {
    /* 0x00 */ std::uint8_t _pad00[0x40];
    /* 0x40 */ std::int32_t version;        // gated == 0x7d1 (2001)
    /* 0x44 */ std::uint8_t _pad44[0x0c];
    /* 0x50 */ void* relocField0;           // rebased by Relocate (+0x7c delta)
    /* 0x54 */ std::int32_t nAnims;
    /* 0x58 */ void* pAnims;                // anim_desc*, 0x50 each
    /* 0x5c */ std::uint32_t _pad5c;
    /* 0x60 */ void* relocField2;
    /* 0x64 */ std::int32_t nElements;
    /* 0x68 */ void* pBoneArray;            // count-prefixed, 0x18 each
    /* 0x6c */ void* pTempAnims;            // count*0x15c (load-time temp)
    /* 0x70 */ std::int32_t nStreams;
    /* 0x74 */ void* relocField3;
    /* 0x78 */ char* srcPath0;
    /* 0x7c */ char* path0;
    /* 0x80 */ char* srcPath1;
    /* 0x84 */ char* path1;                 // also the AcquireStreams decompress base
};

// anim_key_block — packed key region; node in the global LRU stream cache
// (AnimKeyData.cpp). Global accounting lives in static DAT_007670b8/bc/c0/c4
// (head/tail/count/bytes) and DAT_00737ad8 (byte budget).
struct anim_key_block_layout {
    /* 0x00 */ anim_key_block* pNext;  // LRU next
    /* 0x04 */ anim_key_block* pPrev;  // LRU prev
    /* 0x08 */ void* pData;            // decompressed stream (null = not resident)
    /* 0x0c */ std::int32_t offset;    // source offset (added to anim_group+0x84)
    /* 0x10 */ std::int32_t size;      // resident byte size
};

// char_anim_player — the 0x14c-byte character player (CharAnimPlayer.cpp).
// 8 track layers + cached L2W / bone-position buffers + dirty-flag invalidation.
struct char_anim_player_layout {
    /* 0x000 */ std::uint32_t animHandle;       // 0x7fffffff = invalid sentinel
    /* 0x004 */ std::uint8_t  _pad004[0x0c];
    /* 0x010 */ vector3       cachedPosition;
    /* 0x01c */ std::uint32_t _pad01c;
    /* 0x020 */ std::int32_t  cachedOrientation;
    /* 0x024 */ std::uint8_t  _pad024[0xe8];
    /* 0x10c */ void*         layers[8];         // anim_track_controller* slots
    /* 0x12c */ std::int32_t  bL2WCacheDirty;
    /* 0x130 */ matrix4*      pL2WCache;         // nBones * 0x40 (matrix4 per bone)
    /* 0x134 */ std::int32_t  L2WRecomputeCount;
    /* 0x138 */ std::int32_t  transformVersion;
    /* 0x13c */ std::int32_t  bBonePosCacheDirty;
    /* 0x140 */ vector3*      pBonePosCache;     // nBones * 0x0c (vector3 per bone)
    /* 0x144 */ std::int32_t  bonePosRecomputeCount;
    /* 0x148 */ std::int32_t  stateWriteCount;
};

// =============================================================================
// Function-pointer wrappers, grouped by class
// =============================================================================

// ----------------------------- rawanim --------------------------------------
namespace rawanim_api {
    // rawanim::Load — parse a text RawAnim file (Hierarchy block + per-bone TRS).
    // 0x006abf10
    using Load_t = int(__thiscall*)(rawanim* self, const char* filename);
    inline int Load(rawanim* self, const char* filename) {
        return reinterpret_cast<Load_t>(meridian::rebase(0x006abf10))(self, filename);
    }

    // rawanim::~rawanim — free bone array + 5 aux key/child buffers.
    // 0x006abe70
    using Dtor_t = void(__thiscall*)(rawanim* self);
    inline void Destroy(rawanim* self) {
        reinterpret_cast<Dtor_t>(meridian::rebase(0x006abe70))(self);
    }

    // rawanim::DeleteBone — remove/collapse one bone, rebuild bone + key arrays.
    // 0x006ae220  (proposed name, conf 0.6)
    using DeleteBone_t = void(__thiscall*)(rawanim* self, int boneIndex);
    inline void DeleteBone(rawanim* self, int boneIndex) {
        reinterpret_cast<DeleteBone_t>(meridian::rebase(0x006ae220))(self, boneIndex);
    }
} // namespace rawanim_api

// ----------------------------- anim_group -----------------------------------
namespace anim_group_api {
    // anim_group::Load — init from an in-memory parsed source struct.
    // 0x0053dba0
    using Load_t = int(__thiscall*)(anim_group* self, std::uint32_t* src, const char* name);
    inline int Load(anim_group* self, std::uint32_t* src, const char* name) {
        return reinterpret_cast<Load_t>(meridian::rebase(0x0053dba0))(self, src, name);
    }

    // anim_group::LoadFile — open a file and parse it (installs IO hooks).
    // 0x0053d6c0  (proposed name, conf 0.62)
    using LoadFile_t = int(__thiscall*)(anim_group* self, const char* filename);
    inline int LoadFile(anim_group* self, const char* filename) {
        return reinterpret_cast<LoadFile_t>(meridian::rebase(0x0053d6c0))(self, filename);
    }

    // anim_group::LoadBinary — parse the binary AnimGroup payload (version 0x7d1).
    // 0x0053d8a0  (proposed name, conf 0.6)
    using LoadBinary_t = int(__thiscall*)(anim_group* self, int fileHandle);
    inline int LoadBinary(anim_group* self, int fileHandle) {
        return reinterpret_cast<LoadBinary_t>(meridian::rebase(0x0053d8a0))(self, fileHandle);
    }

    // anim_group::Relocate — pack/unpack internal pointers (toRelative: 0=absolute, !0=relative).
    // 0x0053dd20  (proposed name, conf 0.6)
    using Relocate_t = void(__thiscall*)(anim_group* self, int toRelative);
    inline void Relocate(anim_group* self, int toRelative) {
        reinterpret_cast<Relocate_t>(meridian::rebase(0x0053dd20))(self, toRelative);
    }

    // anim_group::EvalAnim — sample anim[animIdx] at time t into outPose.
    // 0x0053cbe0  (behavioral inference, low confidence — verify args before use)
    using EvalAnim_t = void(__thiscall*)(anim_group* self, float t, int animIdx, void* outPose);
    inline void EvalAnim(anim_group* self, float t, int animIdx, void* outPose) {
        reinterpret_cast<EvalAnim_t>(meridian::rebase(0x0053cbe0))(self, t, animIdx, outPose);
    }

    // anim_group::Clear — teardown: release streams, free buffers, zero the object.
    // 0x0053caa0  (recovered symbol was anim_loader::Load; body is teardown — see docs)
    using Clear_t = void(__thiscall*)(anim_group* self);
    inline void Clear(anim_group* self) {
        reinterpret_cast<Clear_t>(meridian::rebase(0x0053caa0))(self);
    }
} // namespace anim_group_api

// --------------------- anim_key_block (LRU stream cache) ---------------------
namespace anim_key_block_api {
    // anim_key_block::AcquireStreams — make the block resident (decompress on demand).
    // 0x0053f540  Returns the decompressed stream pointer.
    using AcquireStreams_t = void*(__thiscall*)(anim_key_block* self, const anim_group* grp);
    inline void* AcquireStreams(anim_key_block* self, const anim_group* grp) {
        return reinterpret_cast<AcquireStreams_t>(meridian::rebase(0x0053f540))(self, grp);
    }

    // anim_key_block::ReleaseStreams — evict the block from the LRU and free its buffer.
    // 0x0053f6f0
    using ReleaseStreams_t = void(__thiscall*)(anim_key_block* self);
    inline void ReleaseStreams(anim_key_block* self) {
        reinterpret_cast<ReleaseStreams_t>(meridian::rebase(0x0053f6f0))(self);
    }
} // namespace anim_key_block_api

// --------------------------- AnimationDecompress -----------------------------
namespace anim_decompress_api {
    // AnimationDecompress — decode one packed key-stream block into outStream.
    // 0x00545450  __cdecl
    using AnimationDecompress_t =
        void(__cdecl*)(const anim_group* grp, const unsigned char* src, void* outStream, int param);
    inline void AnimationDecompress(const anim_group* grp, const unsigned char* src,
                                    void* outStream, int param) {
        reinterpret_cast<AnimationDecompress_t>(meridian::rebase(0x00545450))(grp, src, outStream, param);
    }
} // namespace anim_decompress_api

// ----------------------------- char_anim_player ------------------------------
namespace char_anim_player_api {
    // char_anim_player::char_anim_player — ctor (sentinel handle, 8 layers, identity mats).
    // 0x00540450
    using Ctor_t = void(__thiscall*)(char_anim_player* self);
    inline void Construct(char_anim_player* self) {
        reinterpret_cast<Ctor_t>(meridian::rebase(0x00540450))(self);
    }

    // char_anim_player::ReleaseCachedData — free both caches, release handle, reset sentinel.
    // 0x005405d0  (analysis called it Free; maps to ReleaseCachedData in the API)
    using ReleaseCachedData_t = void(__thiscall*)(char_anim_player* self);
    inline void ReleaseCachedData(char_anim_player* self) {
        reinterpret_cast<ReleaseCachedData_t>(meridian::rebase(0x005405d0))(self);
    }

    // char_anim_player::SetAnim — bind a new animation handle (single-arg form).
    // 0x00540670  (behavioral inference, conf 0.5 — the public API also has a 4-arg overload)
    using SetAnim_t = void(__thiscall*)(char_anim_player* self, std::uint32_t animHandle);
    inline void SetAnim(char_anim_player* self, std::uint32_t animHandle) {
        reinterpret_cast<SetAnim_t>(meridian::rebase(0x00540670))(self, animHandle);
    }

    // char_anim_player::UpdateCachedL2W — lazily (re)compute the per-bone L2W cache.
    // 0x00542230
    using UpdateCachedL2W_t = void(__thiscall*)(char_anim_player* self);
    inline void UpdateCachedL2W(char_anim_player* self) {
        reinterpret_cast<UpdateCachedL2W_t>(meridian::rebase(0x00542230))(self);
    }

    // char_anim_player::UpdateCachedBonePos — lazily (re)compute world bone positions.
    // 0x005423d0
    using UpdateCachedBonePos_t = void(__thiscall*)(char_anim_player* self);
    inline void UpdateCachedBonePos(char_anim_player* self) {
        reinterpret_cast<UpdateCachedBonePos_t>(meridian::rebase(0x005423d0))(self);
    }

    // char_anim_player::InvalidateCaches — mark caches dirty, free them, notify 8 layers.
    // 0x00542580
    using InvalidateCaches_t = void(__thiscall*)(char_anim_player* self);
    inline void InvalidateCaches(char_anim_player* self) {
        reinterpret_cast<InvalidateCaches_t>(meridian::rebase(0x00542580))(self);
    }

    // char_anim_player::EnsureAnimPlayer — lazily (re)construct the 0x14c sub-player.
    // 0x00592010  (behavioral inference, conf 0.55 — owner-side helper, verify before use)
    using EnsureAnimPlayer_t = void(__thiscall*)(void* owner);
    inline void EnsureAnimPlayer(void* owner) {
        reinterpret_cast<EnsureAnimPlayer_t>(meridian::rebase(0x00592010))(owner);
    }
} // namespace char_anim_player_api

// ----------------------------- simple_anim_player ----------------------------
namespace simple_anim_player_api {
    // simple_anim_player::ComputeBoneL2W — compose one bone's animated TRS into out.
    // 0x0053c3a0
    using ComputeBoneL2W_t = void(__thiscall*)(simple_anim_player* self, int boneIndex, matrix4* out);
    inline void ComputeBoneL2W(simple_anim_player* self, int boneIndex, matrix4* out) {
        reinterpret_cast<ComputeBoneL2W_t>(meridian::rebase(0x0053c3a0))(self, boneIndex, out);
    }
} // namespace simple_anim_player_api
