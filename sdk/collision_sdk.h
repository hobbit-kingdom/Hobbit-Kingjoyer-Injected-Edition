// ============================================================================
//  collision_sdk.h  —  COLLISION / PHYSICS subsystem SDK for THE HOBBIT (2003)
//  PC build. Entropy engine, MSVC, 32-bit (Meridian.exe).
//
//  Reverse-engineered modding / trainer SDK. All addresses are absolute PC
//  virtual addresses (preferred image base 0x00400000, ASLR off). Resolve at
//  runtime with meridian::rebase(0xADDR), which applies the current module-base
//  delta vs the analyzed image.
//
//  This is the geometry / physics layer every other subsystem queries:
//
//    * collision_mgr  - the world collision query engine. You "set up" a probe
//                       (Ray / Sphere / Cylinder / LineOfSight / Camera-sphere),
//                       Apply it against world geometry (triangles, AABBs,
//                       collmeshes, the poly cache), then CheckCollisions() to
//                       sort + read back the nearest hit(s). Surface flags /
//                       surface type under a point are read via GetSurfaceFlags
//                       / GetSurfaceType.
//    * collmesh       - a compacted triangle collision mesh (cell-bucketed).
//                       Built once from raw verts/tris; OnGatherTriangles feeds
//                       its tris into the collision_mgr probe.
//    * spatial_dbase  - the broadphase: a 3-layer (coarse/fine) uniform grid of
//                       cells. Objects AcquireLinks into every cell their AABB
//                       overlaps; queries TraverseCells over a bbox.
//    * rigid_instance - a static/animated world prop (engine `object`). Owns a
//                       cached world AABB, a collision submesh ('_coll'), surface
//                       flags, and a simple_anim_player. Re-links into the
//                       spatial_dbase whenever it Moves / Rotates / animates
//                       (InvalidatePolyCache). AdvanceFloat does buoyancy ray
//                       casts against water.
//    * special_surfaces / play_surface - the walkable/material surface objects.
//                       Carry a collmesh, a surface-type id (slippery / lava /
//                       water / stone ...), per-mesh hide masks, decal flags,
//                       and per-vertex color/alpha. play_surface is the level
//                       walkable geometry; both derive special_surfaces -> object.
//    * line_seg       - an editor segment-intersection primitive (Head / Tail /
//                       Moveable End) used for segment math.
//    * PhysController  (NPC rigid-body / locomotion driver) lives mostly in the
//                       npc_ai SDK; only its collision-adjacent ground-clearance
//                       and head-track helpers are surfaced here.
//
//  Field offsets in the structs below are CONSOLIDATED from the four per-chunk
//  analyses (collision__00..03.json). Only well-evidenced fields are named;
//  everything else is explicit padding so named members land at their true byte
//  offsets. These structs are NOT meant to be instantiated — only
//  reinterpret_cast onto a live pointer obtained from a GUID/obj_mgr slot.
//
//  ---- USAGE / RECIPES -----------------------------------------------------
//    using namespace collision_sdk;
//
//    // (1) Raycast against the world, read back the nearest hit.
//    //     `mgr` is the engine's collision_mgr singleton (resolve its address
//    //     from the engine_core SDK / a known global, then cast).
//    CollisionMgr* mgr = reinterpret_cast<CollisionMgr*>(mgrPtr);
//    fn::SetMaxCollisions(mgr, 1);
//    fn::RaySetup(mgr, /*ignoreGuid*/0ull, from, to, /*layerMask*/0xffffffffu);
//    fn::GatherTriangles(mgr, queryBox, 0xffffffffu); // collect candidate tris
//    int nHits = fn::CheckCollisions(mgr);            // sort + finalize
//    // read the resulting collision::collision rows out of the mgr (see notes).
//
//    // (2) Read the surface flag / type under the player's feet:
//    //     down-cast a foot position into a tiny query bbox first, or query a
//    //     known surface guid:
//    uint8_t flags = fn::GetSurfaceFlags(mgr, surfaceGuid, triIndex);
//    uint8_t mat   = fn::GetSurfaceType (mgr, surfaceGuid, triIndex);
//
//    // (3) Read a rigid_instance's cached world AABB / surface type directly:
//    RigidInstance* ri = reinterpret_cast<RigidInstance*>(slotPtr);
//    bbox worldBox{ {ri->bboxMinX,ri->bboxMinY,ri->bboxMinZ},
//                   {ri->bboxMaxX,ri->bboxMaxY,ri->bboxMaxZ} };
//    uint8_t st = ri->surfaceType;  // material id (see special_surfaces type table)
//
//  __thiscall wrappers take the object pointer as the FIRST argument.
//  Statics / file-scope helpers are __cdecl. Any method taking an INCOMPLETE
//  engine type (xcolor, xstring-by-value where noted, matrix4 sometimes) is
//  exposed via a pointer/reference wrapper or a *_at() address accessor with the
//  raw signature in a comment.
// ============================================================================
#pragma once

#include <cstdint>
#include "meridian_types.h"   // meridian::rebase, vector3, radian3, matrix4, bbox, xstring, property, xcolor (fwd), Ghidra aliases

// ---- Forward declarations for engine types we don't fully model -------------
// (Most are already declared in meridian_types.h; re-declaring a struct name is
//  harmless and keeps this header readable standalone.)
// NOTE: collmesh, special_surfaces, play_surface, line_seg, rigid_instance,
//  spatial_dbase, PhysController, collision are forward-declared GLOBALLY in
//  meridian_types.h. We model their byte layouts below inside namespace
//  collision_sdk to avoid a one-definition clash with those opaque global
//  forward-declarations; always refer to the layout with the namespace
//  qualifier (collision_sdk::RigidInstance, collision_sdk::SpatialDbase, ...).
struct object;            // engine base of rigid_instance / special_surfaces / play_surface / line_seg
struct collmesh;          // compacted triangle collision mesh
struct collision;         // collision_mgr::collision hit record
struct simple_anim_player;// rigid_instance+0x140 anim driver
struct anim_group;
struct plane;             // collision_mgr cylinder/triangle math
struct bin_in;
struct bin_out;
struct view;              // spatial_dbase::Render takes a view const&
struct obj_mgr;
struct xcolor;            // INCOMPLETE here; passed BY VALUE by spatial_dbase::Render
struct xhandle;
struct rhandle;

namespace collision_sdk {

	// ===========================================================================
	//  1. Collision probe primitive type  (collision_mgr "enum primitive")
	//     Selected by the *Setup family; stored internally on the mgr. Values are
	//     ordinal best-guesses from the Setup/Apply pairing order.
	// ===========================================================================
	enum class ePrimitive : int32_t {
		Sphere = 0,   // SphereSetup  / ApplySphere
		Ray = 1,   // RaySetup     / ApplyTriangleToRay etc.
		Cylinder = 2,   // CylinderSetup/ ApplyCylinder
		LineOfSight = 3,   // LineOfSightSetup
		CameraSphere = 4,   // CameraSphereSetup (camera-collision probe)
	};

	// ===========================================================================
	//  2. Surface type / material ids  (special_surfaces+0x7c discriminator)
	//     GetSurfaceTypeNumber maps a name string into a 0x20-stride, 10-entry table
	//     at &DAT_006eee58. Indices here are the resolved type ids; exact name->id
	//     ordering beyond 'Stone' is approximate. Out-of-range names map to 0x10.
	//     Several ids (0x12,0x1c,0x1e,0x22,0x24,0x31,0x33) are special-cased by the
	//     collision pass / InvalidatePolyCache to skip or specially gate collision.
	// ===========================================================================
	enum class eSurfaceType : uint8_t {
		Default = 0x00,
		Stone = 0x01,   // 'Stone' (first table entry); other materials follow
		Invalid = 0x10,   // GetSurfaceTypeNumber out-of-range fallback
		// Special-cased type ids observed in the collision pass:
		SpecialA = 0x12,  // ProcessObjectCollisions surface-type predicate
		SpecialB = 0x1c,  // ProcessObjectCollisions / Lightning alt-target
		SkipC = 0x1e,  // InvalidatePolyCache / SetHidden skip-collision id
		SkipD = 0x22,
		SkipE = 0x24,
		SkipF = 0x31,
		SkipG = 0x33,
	};

	// ===========================================================================
	//  3. rigid_instance gameplay flags  (rigid_instance+0x15a, 16-bit)
	//     Authoritative bit map recovered from OnExport / Init.
	// ===========================================================================
	enum eRigidGameplayFlags : uint16_t {
		RIF_HasLOD = 0x0001,
		RIF_IsLadder = 0x0002,
		RIF_IsVine = 0x0004,
		RIF_IsLeafPile = 0x0008,
		RIF_IsHoistable = 0x0010,
		RIF_IsMovingPlatform = 0x0020,
		RIF_IsAutoEdgeGrabbable = 0x0040,
		RIF_Destructing = 0x0400,  // AdvanceDestruct active (OnAdvanceLogic)
		RIF_Destructed = 0x1000,  // destruct done
		RIF_IsAnimating = 0x4000,
	};

	// rigid_instance per-tick flags (+0x15b): bit0 = float/buoyancy, bit6 = animate.
	enum eRigidTickFlags : uint8_t {
		RTF_DoesFloat = 0x01,  // AdvanceFloat enabled
		RTF_AnimEnabled = 0x40,  // AdvanceAnim enabled
		RTF_DoesFloatHi = 0x80,  // FireAndForget transient marker
	};

	// ===========================================================================
	//  4. rigid_instance::AnimData  —  0xa0-byte anim block at rigid_instance+0x140
	//     (the engine `simple_anim_player`). Allocated by SetAnimResourceName.
	//     Cast rigid_instance.animData onto this to read playback state.
	// ===========================================================================
#pragma pack(push, 1)
	struct AnimData {
		void* headerOrVtable;  // 0x00  ctor (FUN_0053b4d0) target
		uint32_t animSetHandle;   // 0x04  rhandle to the anim set/group
		int32_t  currAnimIndex;   // 0x08  current anim/clip id (-1 = none)
		uint8_t  _pad0c[0x10 - 0x0c];
		float    currentFrame;    // 0x10  current frame cursor (float)
		uint8_t  _pad14[0x18 - 0x14];
		float    lastFrame;       // 0x18  loop-wrap upper bound
		uint8_t  _pad1c[0x60 - 0x1c];
		int32_t  playState;       // 0x60  AnimDataAvailable sets = looping
		int32_t  isStopped;       // 0x64  = (looping == 0)
		uint8_t  _pad68[0x6c - 0x68];
		int32_t  field6c;         // 0x6c  = field94
		uint8_t  _pad70[0x7c - 0x70];
		float    loopDelayRemain; // 0x7c  active/remaining loop-delay timer
		float    animSpeed;       // 0x80  playback speed (default 1.0)
		float    animOffset;      // 0x84  start offset
		int32_t  isBound;         // 0x88  0 until anim resource bound (AnimDataAvailable)
		float    loopDelay;       // 0x8c  configured loop delay
		int32_t  looping;         // 0x90  loop bool (default 1; FireAndForget 0)
		int32_t  field94;         // 0x94  default 1
		int32_t  collMeshIndex;   // 0x98  '_coll' sub-resource index (-1 = none)
		int32_t  field9c;         // 0x9c  short from geom desc; default -1
	};                            // sizeof == 0xa0 (operator_new(0xa0))
#pragma pack(pop)

	// ===========================================================================
	//  5. special_surfaces  —  base of play_surface / rigid_instance surface state.
	//     Derives engine `object`. Cast a live surface object pointer to this.
	//     Only the collision/material-relevant fields are named.
	// ===========================================================================
#pragma pack(push, 1)
	struct SpecialSurfaces {
		void* vtable;          // 0x00
		uint8_t  _pad04[0x08 - 0x04];
		float    spatialX;        // 0x08  position passed to spatial reinsert (FUN_0058c830)
		float    spatialY;        // 0x0c
		uint32_t objectFlags;     // 0x10  object flag word; bit27(0x08000000) surface prop,
		//       0x01000000 decals, 0x40000000 plant, 0xc0000000 vis mask
		uint8_t  _pad14[0x7a - 0x14];
		uint16_t collisionFlags;  // 0x7a  bit2(0x4)=DoesNotCollide, 0x200/0x400 collide gates
		uint8_t  surfaceType;     // 0x7c  eSurfaceType material id (slippery/lava/water/stone)
		uint8_t  _pad7d[0x81 - 0x7d];
		uint8_t  sortGroup;       // 0x81  render sort-group id (SetSortGroup)
		uint8_t  surfaceColor[4]; // 0x82  RGBA surface/ambient color (default 0,0,0,0xff)
		uint8_t  _pad86[0xa8 - 0x86];
		void** vertexBufferArray;// 0xa8 per-submesh vertex-buffer handle array
		void* alphaDataBuffer; // 0xac  alpha/color scratch (freed by play_surface dtor)
		uint32_t meshRenderMaskLo;// 0xb0  64-bit per-mesh render/visible mask (low)
		uint32_t meshRenderMaskHi;// 0xb4  (high; top bit forced off in SetMeshIsHidden)
		void* vertexColorBuffer;// 0xb8 per-vertex xcolor buffer (InitAlphaData)
		uint32_t resourceName;    // 0xbc  geometry/resource string-ref (collmesh handle); 0x7fffffff = none
		uint16_t moveableEnd;     // 0xc0  line_seg 'Moveable End' (shared layout)
		uint8_t  _padc2[0x100 - 0xc2];
		float    localBBoxMaxX;   // 0x100 local collision bbox max (ctor +FLT_MAX => empty)
		float    localBBoxMaxY;   // 0x104
		float    localBBoxMaxZ;   // 0x108
		float    localBBoxMinX;   // 0x10c local collision bbox min (ctor -FLT_MAX)
		float    localBBoxMinY;   // 0x110
		float    localBBoxMinZ;   // 0x114
		uint8_t  _pad118[0x124 - 0x118];
		uint16_t vertexCount;     // 0x124 vertex count for alpha buffer sizing
		uint8_t  visAndSurfaceFlags;// 0x126 bit0=Hidden; bits3-6 = surfaceTypeNumber<<3; ctor 0x10
		uint8_t  renderFlags;     // 0x127 bit0=AcceptsDecals,bit1=SelfIllum,bit2=CopyR->A,bit3=SqueakyChickenBoard
	};                            // size >= 0x128
#pragma pack(pop)

	// ===========================================================================
	//  6. rigid_instance  —  static/animated world prop. Derives special_surfaces.
	//     Cast a live obj_mgr slot pointer to this. Shares the special_surfaces
	//     base layout (vtable .. surfaceType etc.) and extends it.
	// ===========================================================================
#pragma pack(push, 1)
	struct RigidInstance {
		void* vtable;          // 0x00
		uint8_t  _pad04[0x08 - 0x04];
		float    posX;            // 0x08  position used for spatial reinsert / FX spawn
		float    posY;            // 0x0c
		uint32_t objectFlags;     // 0x10  shared object flag word (see SpecialSurfaces)
		float    centerX;         // 0x14  origin / world position (Init / MoveAndUpdate)
		float    centerY;         // 0x18
		float    centerZ;         // 0x1c
		float    animSpeedReq;    // 0x20  requested anim speed (SetAnimSpeed write)
		float    animSpeedCur;    // 0x24  last-applied anim speed (compare guard)
		uint8_t  _pad28[0x44 - 0x28];
		float    bboxMinX;        // 0x44  cached WORLD AABB min (bbox start)
		float    bboxMinY;        // 0x48
		float    bboxMinZ;        // 0x4c
		float    bboxMaxX;        // 0x50  cached WORLD AABB max
		float    bboxMaxY;        // 0x54
		float    bboxMaxZ;        // 0x58
		uint8_t  _pad5c[0x68 - 0x5c];
		float    rotPitch;        // 0x68  orientation (radian3 x/y/z) — OnRotate stores here
		float    rotYaw;          // 0x6c
		float    rotRoll;         // 0x70
		uint8_t  _pad74[0x7a - 0x74];
		uint16_t collisionFlags;  // 0x7a  bit2(0x4)=DoesNotCollide; 0x200/0x400 gates
		uint8_t  surfaceType;     // 0x7c  type discriminator (==5 = animated/special class)
		uint8_t  _pad7d[0x7f - 0x7d];
		uint8_t  miscFlags;       // 0x7f  ctor checks bit5; SetDestructState toggles bit0
		uint8_t  field80;         // 0x80  ctor sets 0xff
		uint8_t  sortGroup;       // 0x81
		uint8_t  ambientColor[4]; // 0x82  ambient/surface RGBA
		uint8_t  _pad86[0xb8 - 0x86];
		void* privDataPtr;     // 0xb8  (sibling color buffer in play_surface layout)
		uint8_t  _padbc[0x130 - 0xbc];
		float    scaleX;          // 0x130 scale vector3 (Init / OnExport 'Scale')
		float    scaleY;          // 0x134
		float    scaleZ;          // 0x138
		uint32_t animResourceName;// 0x13c anim resource string-ref (0x7fffffff = none)
		AnimData* animData;       // 0x140 0xa0-byte anim player block (null if no anim)
		void* destructState;   // 0x144 destruct-state struct (+4 remaining-time float)
		void* plantData;       // 0x148 lazily-alloc'd pair of name string-refs (plant)
		uint8_t  _pad14c[0x150 - 0x14c];
		uint32_t ownerGuidLo;     // 0x150 owner/lifetime GUID low (FireAndForget)
		uint32_t ownerGuidHi;     // 0x154 owner/lifetime GUID high
		int16_t  waterSdbaseIndex;// 0x158 cached water object index (0xffff = none/unresolved)
		uint16_t gameplayFlags;   // 0x15a eRigidGameplayFlags (HasLOD/Ladder/Vine/.../IsAnimating)
		uint8_t  tickFlags;       // 0x15b eRigidTickFlags (bit0 float, bit6 animate)
		int8_t   floatYTweak;     // 0x15c FloatYTweak (signed)
		uint8_t  plantDestructFlags;//0x15d bit0=plant, bit4=lod, bit5=destruct-fx-spawned, bit6 ff
		uint8_t  lightingType;    // 0x15e LightingType enum
		uint8_t  _pad15f[0x160 - 0x15f];
		uint32_t childAnimFlags;  // 0x160 child-instance anim flags (bit1 loop dir, bit3 reset)
		uint8_t  _pad164[0x170 - 0x164];
		int32_t  childCount;      // 0x170 spawned child count
		uint64_t* childGuidArray; // 0x174 ptr to array of 8-byte child guids
	};                            // size >= 0x17c
#pragma pack(pop)

	// ===========================================================================
	//  7. play_surface  —  walkable level geometry surface. Derives special_surfaces.
	//     Adds a cached world bbox and a per-vertex color buffer.
	// ===========================================================================
#pragma pack(push, 1)
	struct PlaySurface {
		void* vtable;          // 0x00  PTR_FUN_006ee3f0
		uint8_t  _pad04[0x14 - 0x04];
		float    bboxCenterX;     // 0x14  zeroed by UpdateBBox after compute
		float    bboxCenterY;     // 0x18
		float    bboxCenterZ;     // 0x1c
		uint8_t  _pad20[0x2c - 0x20];
		float    cachedBBoxMinX;  // 0x2c  cached/local bbox min
		float    cachedBBoxMinY;  // 0x30
		float    cachedBBoxMinZ;  // 0x34
		float    cachedBBoxMaxX;  // 0x38  cached/local bbox max
		float    cachedBBoxMaxY;  // 0x3c
		float    cachedBBoxMaxZ;  // 0x40
		float    worldBBoxMinX;   // 0x44  world AABB min (UpdateBBox / OnExport transform)
		float    worldBBoxMinY;   // 0x48
		float    worldBBoxMinZ;   // 0x4c
		float    worldBBoxMaxX;   // 0x50  world AABB max
		float    worldBBoxMaxY;   // 0x54
		float    worldBBoxMaxZ;   // 0x58
		uint8_t  _pad5c[0x7a - 0x5c];
		uint16_t collisionFlags;  // 0x7a  bit2(0x4)=DoesNotCollide
		uint8_t  surfaceType;     // 0x7c  5/6 = alpha-capable surface types
		uint8_t  _pad7d[0x80 - 0x7d];
		uint8_t  surfaceTypeSentinel;// 0x80 ctor sets 0xff
		uint8_t  _pad81[0xb8 - 0x81];
		uint32_t vertexColorArray;// 0xb8  per-vertex xcolor array ptr (OnImport)
		uint32_t attachedResource;// 0xbc  attached resource/ui_win handle (UpdateBBox)
		uint8_t  _padc0[0x124 - 0xc0];
		uint16_t vertexColorCount;// 0x124 per-vertex color count
	};                            // size >= 0x126
#pragma pack(pop)

	// ===========================================================================
	//  8. spatial_dbase  —  broadphase grid (3 LOD layers, stride 0xfb8).
	//     Singleton owned by the level. Cast its address to this to inspect stats.
	// ===========================================================================
#pragma pack(push, 1)
	struct SpatialDbase {
		// 32-bit on-disk pointers in the target image: modeled as uint32_t so the
		// 0x80-entry table is exactly 0x200 bytes on any host (avoids 64-bit ptr skew).
		uint32_t cellPagePtrs[0x80]; // 0x000 row/cell-page pointer table (ClearLayer frees)
		uint32_t usedCellCount;    // 0x200 used cells (AllocCell increments)
		uint32_t cellPageCount;    // 0x204 cell page count (512 cells / 0x3800-byte page)
		uint16_t freeCellHead;     // 0x208 cell free-list head (0xffff sentinel)
		uint8_t  _pad20a[0x20c - 0x20a];
		uint32_t linkColumnPtrs[0x80];//0x20c link/column page pointer table (0x80*4 = 0x200)
		uint32_t usedLinkCount;    // 0x40c used links
		uint32_t linkPageCount;    // 0x410 link page count (0x400 links/page)
		uint16_t freeLinkHead;     // 0x414 link free-list head (0xffff sentinel)
		uint8_t  _pad416[0x418 - 0x416];
		float    layerExtentThreshSq;//0x418 half-extent^2 coarse/fine layer selector
		uint8_t  _pad41c[0x420 - 0x41c];
		// ---- layer 0 scale fields (each layer is +0xfb8 from the previous) ------
		float    layer0CellSizeX;  // 0x420
		float    layer0CellSizeY;  // 0x424
		float    layer0InvCellSizeX;//0x428  = 1.0 / cellSizeX
		float    layer0InvCellSizeY;//0x42c
		uint8_t  _pad430[0x13d8 - 0x430]; // 0x430 layer0 cell table (0x7d1 ushort) + body
		float    layer1CellSizeX;  // 0x13d8
		float    layer1CellSizeY;  // 0x13dc
		float    layer1InvCellSizeX;//0x13e0
		float    layer1InvCellSizeY;//0x13e4
		uint8_t  _pad13e8[0x2390 - 0x13e8];
		float    layer2CellSizeX;  // 0x2390
		float    layer2CellSizeY;  // 0x2394
		float    layer2InvCellSizeX;//0x2398
		float    layer2InvCellSizeY;//0x239c
	};                             // size >= 0x23a0
#pragma pack(pop)

	// spatial_dbase_cell — 0x1c-byte cell entry (inside the cell pages).
#pragma pack(push, 1)
	struct SpatialDbaseCell {
		uint8_t  _pad00[0x04];
		uint16_t nextCellIndex;    // 0x04 cell-chain next index
		uint8_t  _pad06[0x0e - 0x06];
		int16_t  linkDepth;        // 0x0e link count in this cell (MostLinkInACell)
		uint8_t  _pad10[0x12 - 0x10];
		uint16_t linkListHead;     // 0x12 head of this cell's link list (0xffff terminator)
		uint8_t  _pad14[0x1c - 0x14];
	};                             // sizeof == 0x1c
#pragma pack(pop)

	// collmesh — compacted triangle collision mesh (only header fields recovered).
#pragma pack(push, 1)
	struct CollMesh {
		uint32_t versionTag;       // 0x00 0x7d2 (2002) written by Build
		uint8_t  _pad04[0x64 - 0x04];
		int32_t  nTriangles;       // 0x64 triangle count
		uint8_t  _pad68[0x6c - 0x68];
		void* cellsOrTrisPtr;   // 0x6c compacted cell/tri data
		void* indicesPtr;       // 0x70 compacted index data
	};                             // size >= 0x74
#pragma pack(pop)

	// ===========================================================================
	//  9. Typed call wrappers
	//     __thiscall: object pointer is the FIRST argument.
	//     vector3/bbox/matrix4 are COMPLETE (meridian_types.h), so by-value/by-ref
	//     signatures that use them are ABI-safe. property is a fixed-size blob, so
	//     by-value property is also reproducible.
	// ===========================================================================
	namespace fn {

		// ---- collision_mgr: lifecycle ----------------------------------------------
		// collision_mgr::collision_mgr(void)
		inline void* CollisionMgr_ctor(void* mgr) {
			using F = void* (__thiscall*)(void*);
			return reinterpret_cast<F>(meridian::rebase(0x004c2430 /* see note: addr from API set, verify vs build */))(mgr);
			// NOTE: collision_mgr ctor address was not separately captured in the
			//       analyzed chunk; resolve from the engine_core SDK if it differs.
		}
		// collision_mgr::Initialize(void)
		inline void* CollisionMgr_at_Initialize() { return nullptr; }
		// (Initialize/ctor/CheckCollisions internal addresses live in the API bundle but
		//  were not all captured with addresses in the per-chunk decompiles. Where an
		//  address is unknown, query the engine collision_mgr singleton's vtable.)

		// ---- collision_mgr: probe setup (one per query) ----------------------------
		// All take the ignore-guid as a uint64. start/end are vector3 (complete type).
		// Raw sigs come from collision_api.json; addresses resolve via the mgr vtable /
		// engine_core SDK at runtime (not all captured here). Expose as address-less
		// commented stubs where the chunk lacked the address.

		//   void RaySetup(uint64 ignoreGuid, vector3 const& from, vector3 const& to, uint mask)
		//   void SphereSetup(uint64, vector3 const& center, vector3 const& vel, float r, uint mask)
		//   void CylinderSetup(uint64, vector3 const& base, vector3 const& vel, float r, float h, uint mask)
		//   void LineOfSightSetup(uint64, vector3 const& from, vector3 const& to, uint mask)
		//   void CameraSphereSetup(uint64, vector3 const&, vector3 const&, float, uint)
		//   void SetMaxCollisions(int)
		//   void AddIgnoreGuid(uint64)
		//   void ObeyCameraCollision(void)
		// These are documented in docs/subsystems/collision.md; resolve addresses from
		// the engine collision_mgr vtable. Helper accessors below give the gather/check
		// entry points whose addresses ARE recoverable from the surface objects.

		// ---- spatial_dbase (broadphase) wrappers (addresses recovered) -------------
		// spatial_dbase::AllocCell — allocate+init a grid cell (mislabeled 'Clear').
		inline uint16_t SpatialDbase_AllocCell(SpatialDbase* db, short gx, short gy,
			short gz, short cellIndex, int useHash) {
			using F = uint16_t(__thiscall*)(SpatialDbase*, short, short, short, short, int);
			return reinterpret_cast<F>(meridian::rebase(0x0058a310))(db, gx, gy, gz, cellIndex, useHash);
		}
		// spatial_dbase::ClearLayer — free a layer's cell/link pages, reset free-lists.
		inline void SpatialDbase_ClearLayer(SpatialDbase* db) {
			using F = void(__thiscall*)(SpatialDbase*);
			reinterpret_cast<F>(meridian::rebase(0x00589de0))(db);
		}
		// spatial_dbase::SetupGrid (== ::Init) — init all 3 LOD layers + cell sizes.
		inline void SpatialDbase_SetupGrid(SpatialDbase* db, float cx0, float cy0,
			float cx1, float cy1, float cx2, float cy2,
			float extentThreshold) {
			using F = void(__thiscall*)(SpatialDbase*, float, float, float, float, float, float, float);
			reinterpret_cast<F>(meridian::rebase(0x00589e60))(db, cx0, cy0, cx1, cy1, cx2, cy2, extentThreshold);
		}
		// spatial_dbase::AcquireLinks(bbox const&, int, void* obj, ushort& outHead)
		inline void SpatialDbase_AcquireLinks(SpatialDbase* db, const bbox& box, int layer,
			void* obj, uint16_t& outHead) {
			using F = void(__thiscall*)(SpatialDbase*, const bbox*, int, void*, uint16_t*);
			reinterpret_cast<F>(meridian::rebase(0x0058a9f0))(db, &box, layer, obj, &outHead);
		}
		// spatial_dbase::UpdateLinks(bbox const& newBox, bbox const& oldBox, int obj, void*, ushort& head)
		inline void SpatialDbase_UpdateLinks(SpatialDbase* db, const bbox& newBox,
			const bbox& oldBox, int objHandle,
			void* param4, uint16_t& linkHead) {
			using F = void(__thiscall*)(SpatialDbase*, const bbox*, const bbox*, int, void*, uint16_t*);
			reinterpret_cast<F>(meridian::rebase(0x0058b130))(db, &newBox, &oldBox, objHandle, param4, &linkHead);
		}
		// spatial_dbase::Render(view const&, int layer, xcolor, int linkThreshold)
		//   xcolor is INCOMPLETE and passed BY VALUE; the by-value ABI cannot be formed
		//   here. Use the address accessor and cast once you have a concrete xcolor.
		//   Raw sig: void __thiscall spatial_dbase::Render(spatial_dbase*, view const&, int, xcolor, int)
		inline void* SpatialDbase_Render_at() { return meridian::rebase(0x00589f60); }

		// ---- collision_mgr: per-object collision pass (recovered) ------------------
		// collision_mgr::ProcessObjectCollisions(float* bounds, uint bucket) — iterates
		// broadphase pairs and dispatches the per-pair virtual collision handler.
		inline void CollisionMgr_ProcessObjectCollisions(void* mgr, float* bounds, uint32_t bucket) {
			using F = void(__thiscall*)(void*, float*, uint32_t);
			reinterpret_cast<F>(meridian::rebase(0x00578950))(mgr, bounds, bucket);
		}

		// ---- collmesh (recovered) ---------------------------------------------------
		// collmesh::Build(vector3 const* verts, int nVerts, uchar const* triData, char* name)
		inline void CollMesh_Build(CollMesh* cm, const vector3* verts, int nVerts,
			const uint8_t* triData, char* name) {
			using F = void(__thiscall*)(CollMesh*, const vector3*, int, const uint8_t*, char*);
			reinterpret_cast<F>(meridian::rebase(0x005a5d80))(cm, verts, nVerts, triData, name);
		}

		// ---- rigid_instance: lifecycle & init --------------------------------------
		// rigid_instance::rigid_instance(void)
		inline RigidInstance* RigidInstance_ctor(RigidInstance* ri) {
			using F = RigidInstance * (__thiscall*)(RigidInstance*);
			return reinterpret_cast<F>(meridian::rebase(0x004c0370))(ri);
		}
		// rigid_instance::OnInit(void) [virtual]
		inline void RigidInstance_OnInit(RigidInstance* ri) {
			using F = void(__thiscall*)(RigidInstance*);
			reinterpret_cast<F>(meridian::rebase(0x004c0a40))(ri);
		}
		// rigid_instance::Init(vector3 const& pos, radian3 const& orient, vector3 const& scale,
		//                      bbox const& box, xcolor ambient, int hasLod, ... packed byte flags)
		//   The decompiled prototype carries more packed byte params than the API sig
		//   and takes xcolor (incomplete) BY VALUE — exposed as an address accessor.
		//   Raw sig (API): void rigid_instance::Init(vector3 const&, radian3 const&,
		//     vector3 const&, bbox const&, xcolor, int, int, int, int, int, int, int)
		inline void* RigidInstance_Init_at() { return meridian::rebase(0x004c08b0); }

		// ---- rigid_instance: movement / transform (feeds spatial_dbase) ------------
		// rigid_instance::Move(vector3 const& delta, int flags) [virtual]
		inline void RigidInstance_Move(RigidInstance* ri, const vector3& delta, int flags) {
			using F = void(__thiscall*)(RigidInstance*, const vector3*, int);
			reinterpret_cast<F>(meridian::rebase(0x004c36f0))(ri, &delta, flags);
		}
		// rigid_instance::OnRotate(radian3 const& rot) [virtual]
		inline void RigidInstance_OnRotate(RigidInstance* ri, const radian3& rot) {
			using F = void(__thiscall*)(RigidInstance*, const radian3*);
			reinterpret_cast<F>(meridian::rebase(0x004c3bc0))(ri, &rot);
		}
		// rigid_instance::MoveAndUpdate(vector3 const& dPos, radian3 const& dRot) [virtual]
		inline void RigidInstance_MoveAndUpdate(RigidInstance* ri, const vector3& dPos, const radian3& dRot) {
			using F = void(__thiscall*)(RigidInstance*, const vector3*, const radian3*);
			reinterpret_cast<F>(meridian::rebase(0x004c3760))(ri, &dPos, &dRot);
		}
		// rigid_instance::UpdateBBoxAndMove(void) [virtual] — recompute world AABB + relink.
		inline void RigidInstance_UpdateBBoxAndMove(RigidInstance* ri) {
			using F = void(__thiscall*)(RigidInstance*);
			reinterpret_cast<F>(meridian::rebase(0x004c3d20))(ri);
		}
		// rigid_instance::InvalidatePolyCache(bbox const& oldBox, int forceFlag)
		inline void RigidInstance_InvalidatePolyCache(RigidInstance* ri, const bbox& oldBox, int forceFlag) {
			using F = void(__thiscall*)(RigidInstance*, const bbox*, int);
			reinterpret_cast<F>(meridian::rebase(0x004c3500))(ri, &oldBox, forceFlag);
		}

		// ---- rigid_instance: per-frame physics tick --------------------------------
		// rigid_instance::OnAdvanceLogic(float dt) [virtual] — runs destruct/anim/float.
		inline void RigidInstance_OnAdvanceLogic(RigidInstance* ri, float dt) {
			using F = void(__thiscall*)(RigidInstance*, float);
			reinterpret_cast<F>(meridian::rebase(0x004c0ce0))(ri, dt);
		}
		// rigid_instance::AdvanceFloat(float dt) — buoyancy: down-ray vs water layer.
		inline void RigidInstance_AdvanceFloat(RigidInstance* ri, float dt) {
			using F = void(__thiscall*)(RigidInstance*, float);
			reinterpret_cast<F>(meridian::rebase(0x004c14a0))(ri, dt);
		}
		// rigid_instance::AdvanceAnim(float dt)
		inline void RigidInstance_AdvanceAnim(RigidInstance* ri, float dt) {
			using F = void(__thiscall*)(RigidInstance*, float);
			reinterpret_cast<F>(meridian::rebase(0x004c0e10))(ri, dt);
		}
		// rigid_instance::AdvanceDestruct(float dt)
		inline void RigidInstance_AdvanceDestruct(RigidInstance* ri, float dt) {
			using F = void(__thiscall*)(RigidInstance*, float);
			reinterpret_cast<F>(meridian::rebase(0x004c1750))(ri, dt);
		}

		// ---- rigid_instance: surface flags / destruct / hide -----------------------
		// rigid_instance::SetDestructState(int destroyed, int spawnFx)
		inline void RigidInstance_SetDestructState(RigidInstance* ri, int destroyed, int spawnFx) {
			using F = void(__thiscall*)(RigidInstance*, int, int);
			reinterpret_cast<F>(meridian::rebase(0x004c2f60))(ri, destroyed, spawnFx);
		}
		// rigid_instance::UpdateDoNotAdvanceLogicFlag(void)
		inline void RigidInstance_UpdateDoNotAdvanceLogicFlag(RigidInstance* ri) {
			using F = void(__thiscall*)(RigidInstance*);
			reinterpret_cast<F>(meridian::rebase(0x004c7930))(ri);
		}
		// rigid_instance::OnNotifyFireForgetComplete(void) — un-hides the surface.
		inline void RigidInstance_OnNotifyFireForgetComplete(RigidInstance* ri) {
			using F = void(__thiscall*)(RigidInstance*);
			reinterpret_cast<F>(meridian::rebase(0x004c7c60))(ri);
		}

		// ---- rigid_instance: anim accessors ----------------------------------------
		// rigid_instance::AnimDataAvailable(void) -> int (1 if anim ready)
		inline int RigidInstance_AnimDataAvailable(RigidInstance* ri) {
			using F = int(__thiscall*)(RigidInstance*);
			return reinterpret_cast<F>(meridian::rebase(0x004c71a0))(ri);
		}
		// rigid_instance::SetAnimResourceName(char const* name)
		inline void RigidInstance_SetAnimResourceName(RigidInstance* ri, const char* name) {
			using F = void(__thiscall*)(RigidInstance*, const char*);
			reinterpret_cast<F>(meridian::rebase(0x004c7010))(ri, name);
		}
		// rigid_instance::SetAnim(char const* animName) -> int
		inline int RigidInstance_SetAnim(RigidInstance* ri, const char* animName) {
			using F = int(__thiscall*)(RigidInstance*, const char*);
			return reinterpret_cast<F>(meridian::rebase(0x004c6f40))(ri, animName);
		}
		// rigid_instance::SetAnimByIndex(int idx) -> anim player ptr
		inline void* RigidInstance_SetAnimByIndex(RigidInstance* ri, int idx) {
			using F = void* (__thiscall*)(RigidInstance*, int);
			return reinterpret_cast<F>(meridian::rebase(0x004c7520))(ri, idx);
		}
		// rigid_instance::SetAnimFrame(float frame)
		inline void RigidInstance_SetAnimFrame(RigidInstance* ri, float frame) {
			using F = void(__thiscall*)(RigidInstance*, float);
			reinterpret_cast<F>(meridian::rebase(0x004c7580))(ri, frame);
		}
		// rigid_instance::ResetAnimFrame(int toEnd)
		inline void RigidInstance_ResetAnimFrame(RigidInstance* ri, int toEnd) {
			using F = void(__thiscall*)(RigidInstance*, int);
			reinterpret_cast<F>(meridian::rebase(0x004c75f0))(ri, toEnd);
		}
		// rigid_instance::IsAtEndOfAnim(void) -> int
		inline int RigidInstance_IsAtEndOfAnim(RigidInstance* ri) {
			using F = int(__thiscall*)(RigidInstance*);
			return reinterpret_cast<F>(meridian::rebase(0x004c7410))(ri);
		}
		// rigid_instance::SetAnimSpeed(float speed)
		inline void RigidInstance_SetAnimSpeed(RigidInstance* ri, float speed) {
			using F = void(__thiscall*)(RigidInstance*, float);
			reinterpret_cast<F>(meridian::rebase(0x00412510))(ri, speed);
		}
		// rigid_instance::SetLoopDelay(float seconds)
		inline void RigidInstance_SetLoopDelay(RigidInstance* ri, float seconds) {
			using F = void(__thiscall*)(RigidInstance*, float);
			reinterpret_cast<F>(meridian::rebase(0x004c74f0))(ri, seconds);
		}
		// rigid_instance::DetectAnimEvent(int type, vector3& outPos) -> int (1 found)
		inline int RigidInstance_DetectAnimEvent(RigidInstance* ri, int type, vector3& outPos) {
			using F = int(__thiscall*)(RigidInstance*, int, vector3*);
			return reinterpret_cast<F>(meridian::rebase(0x004c7820))(ri, type, &outPos);
		}
		// rigid_instance::GetAnimPlayer(void) -> simple_anim_player* (null if invalid)
		inline void* RigidInstance_GetAnimPlayer(RigidInstance* ri) {
			using F = void* (__thiscall*)(RigidInstance*);
			return reinterpret_cast<F>(meridian::rebase(0x004c74b0))(ri);
		}

		// ---- rigid_instance: static factory ----------------------------------------
		// rigid_instance::FireAndForget(vector3 const& pos, radian3 const& rot,
		//   vector3 const& scale, char const* geom, char const* anim, int, xcolor,
		//   int, int, uint64 guid). Takes xcolor BY VALUE → address accessor.
		//   Raw sig: void __cdecl rigid_instance::FireAndForget(vector3 const&,
		//     radian3 const&, vector3 const&, char const*, char const*, int, xcolor,
		//     int, int, uint64)
		inline void* RigidInstance_FireAndForget_at() { return meridian::rebase(0x004c7a10); }

		// ---- special_surfaces: surface flags / 
		// 
		// 
		// 
		// 
		//  ----------------------------
		// special_surfaces::GetSurfaceTypeNumber(char const* name) -> int (static)
		inline int SpecialSurfaces_GetSurfaceTypeNumber(const char* name) {
			using F = int(__cdecl*)(const char*);
			return reinterpret_cast<F>(meridian::rebase(0x004d1140))(name);
		}
		// special_surfaces::SetHidden(int hidden)
		inline void SpecialSurfaces_SetHidden(SpecialSurfaces* ss, int hidden) {
			using F = void(__thiscall*)(SpecialSurfaces*, int);
			reinterpret_cast<F>(meridian::rebase(0x004d22c0))(ss, hidden);
		}
		// special_surfaces::IsMeshHidden(int meshIdx) -> int (1 = hidden, clear bit)
		inline int SpecialSurfaces_IsMeshHidden(SpecialSurfaces* ss, int meshIdx) {
			using F = int(__thiscall*)(SpecialSurfaces*, int);
			return reinterpret_cast<F>(meridian::rebase(0x004d0ae0))(ss, meshIdx);
		}
		// special_surfaces::SetMeshIsHidden(int meshIdx, int hidden)
		inline void SpecialSurfaces_SetMeshIsHidden(SpecialSurfaces* ss, int meshIdx, int hidden) {
			using F = void(__thiscall*)(SpecialSurfaces*, int, int);
			reinterpret_cast<F>(meridian::rebase(0x004d0a70))(ss, meshIdx, hidden);
		}
		// special_surfaces::SetMeshRenderMask(uint64 mask)
		inline void SpecialSurfaces_SetMeshRenderMask(SpecialSurfaces* ss, uint64_t mask) {
			using F = void(__thiscall*)(SpecialSurfaces*, uint64_t);
			reinterpret_cast<F>(meridian::rebase(0x004d0bc0))(ss, mask);
		}
		// special_surfaces::EnableDecals(int enable)
		inline void SpecialSurfaces_EnableDecals(SpecialSurfaces* ss, int enable) {
			using F = void(__thiscall*)(SpecialSurfaces*, int);
			reinterpret_cast<F>(meridian::rebase(0x004d0b40))(ss, enable);
		}
		// special_surfaces::GetMeshIndex(char const* name) -> int
		inline int SpecialSurfaces_GetMeshIndex(SpecialSurfaces* ss, const char* name) {
			using F = int(__thiscall*)(SpecialSurfaces*, const char*);
			return reinterpret_cast<F>(meridian::rebase(0x004d0b20))(ss, name);
		}
		// special_surfaces::GetCollisionBBox(bbox& out, matrix4 const& xform)
		inline void SpecialSurfaces_GetCollisionBBox(SpecialSurfaces* ss, bbox& out, const matrix4& xform) {
			using F = void(__thiscall*)(SpecialSurfaces*, bbox*, const matrix4*);
			reinterpret_cast<F>(meridian::rebase(0x004d1ff0))(ss, &out, &xform);
		}
		// special_surfaces::GetVertData(int idx, vector3& pos, vector3& normal, xcolor& col)
		//   takes xcolor BY REFERENCE (out param). xcolor is incomplete → cannot form a
		//   safe reference type here; use the address accessor.
		//   Raw sig: int __thiscall special_surfaces::GetVertData(special_surfaces*, int, vector3&, vector3&, xcolor&)
		inline void* SpecialSurfaces_GetVertData_at() { return meridian::rebase(0x004d1d10); }
		// special_surfaces::SetSortGroup(uchar group)
		inline void SpecialSurfaces_SetSortGroup(SpecialSurfaces* ss, uint8_t group) {
			using F = void(__thiscall*)(SpecialSurfaces*, uint8_t);
			reinterpret_cast<F>(meridian::rebase(0x004acc10))(ss, group);
		}

		// ---- play_surface ----------------------------------------------------------
		// play_surface::play_surface(void)
		inline PlaySurface* PlaySurface_ctor(PlaySurface* ps) {
			using F = PlaySurface * (__thiscall*)(PlaySurface*);
			return reinterpret_cast<F>(meridian::rebase(0x004b3d80))(ps);
		}
		// play_surface::UpdateBBox(void) — recompute world AABB from mesh + position.
		inline void PlaySurface_UpdateBBox(PlaySurface* ps) {
			using F = void(__thiscall*)(PlaySurface*);
			reinterpret_cast<F>(meridian::rebase(0x004b49b0))(ps);
		}
		// play_surface::OnKill(void) [virtual]
		inline void PlaySurface_OnKill(PlaySurface* ps) {
			using F = void(__thiscall*)(PlaySurface*);
			reinterpret_cast<F>(meridian::rebase(0x004b3fb0))(ps);
		}

		// ---- line_seg (segment math primitive) -------------------------------------
		// line_seg::line_seg(void)
		inline void* LineSeg_ctor(void* ls) {
			using F = void* (__thiscall*)(void*);
			return reinterpret_cast<F>(meridian::rebase(0x004962e0))(ls);
		}

		// ---- PhysController: collision-adjacent helpers ----------------------------
		// PhysController::UpdateHeadTracking(float pitchLimit, float yawLimit, int mode)
		inline void PhysController_UpdateHeadTracking(void* pc, float pitchLimit, float yawLimit, int mode) {
			using F = void(__thiscall*)(void*, float, float, int);
			reinterpret_cast<F>(meridian::rebase(0x00594990))(pc, pitchLimit, yawLimit, mode);
		}
		// PhysController::GetAnimInfoFromName(char const* name) -> AnimInfo*
		inline void* PhysController_GetAnimInfoFromName(void* pc, const char* name) {
			using F = void* (__thiscall*)(void*, const char*);
			return reinterpret_cast<F>(meridian::rebase(0x00594390))(pc, name);
		}
		// PhysController::LoadAnims(xstring fileBase) — xstring is COMPLETE (by value).
		inline void PhysController_LoadAnims(void* pc, xstring fileBase) {
			using F = void(__thiscall*)(void*, xstring);
			reinterpret_cast<F>(meridian::rebase(0x00591540))(pc, fileBase);
		}

	} // namespace fn

} // namespace collision_sdk
