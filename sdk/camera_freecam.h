// ============================================================================
//  camera_freecam.h  —  CAMERA CONTROL for THE HOBBIT (2003) PC
//  Meridian.exe, Entropy engine, MSVC, 32-bit, image base 0x00400000, ASLR OFF.
//
//  Header-only (namespace hobbit_cam). Include it, install ONE hook on
//  camera::SetupView, then call any of the three features at runtime:
//
//     1. ShoulderView(lateral)  — over-the-shoulder offset (slide the camera
//                                 left/right while keeping the normal follow cam).
//     2. Freecam()              — detached 6-DOF fly camera (WASD + look).
//     3. PCCamera()             — keyboard-driven orbit around Bilbo (the engine's
//                                 "controller camera", but you drive it from the
//                                 keyboard: any key -> Look()/Move() rotates it).
//     Off()                     — restore the normal game camera.
//
//  ---- HOW IT WORKS (all verified from the binary) --------------------------
//  Every frame the engine commits the camera to the renderer via
//     camera::SetupView(camera* this, view* out)   @ 0x0045c360  (__thiscall)
//  (the ONLY caller is camera_mgr::UpdateView). It copies the camera's stored
//  frame into the view. We hook it and edit the camera object just before the
//  copy, so our changes reach the renderer in ANY camera mode / on ANY level,
//  without needing the camera_mgr singleton.
//
//  Camera object fields (camera extends object):
//     +0x14  position  (float x,y,z)
//     +0x68  PITCH   (radians)   +0x6c  YAW (radians)   +0xec ROLL (radians)
//     +0xc4  FOV (radians)       +0xc8  near clip       +0xcc far clip
//  Orientation convention (decoded from the view-matrix builder FUN_006716a0,
//  world up = +Y):
//     forward = ( cos(pitch)*sin(yaw), -sin(pitch), cos(pitch)*cos(yaw) )
//     right   = ( cos(yaw),            0,            -sin(yaw)           )
//  Bilbo (orbit centre for PCCamera): GetBilbo() = *(bilbo**)0x0075ba3c, and its
//  world position comes from bilbo vtable slot +0x28 -> float[3].
//
//  BUILD: 32-bit MSVC injected DLL. Header-only. Install the hook once (MinHook).
// ============================================================================
#pragma once
#include <cstdint>
#include <cmath>

namespace hobbit_cam {

namespace addr {
    constexpr uintptr_t SetupView    = 0x0045c360;  // camera::SetupView(camera*, view*) __thiscall
    constexpr uintptr_t GetBilboPtr  = 0x0075ba3c;  // *(bilbo**) — the live Bilbo object

    // camera-instance field offsets
    constexpr int CAM_POS   = 0x14;   // float[3] x,y,z
    constexpr int CAM_PITCH = 0x68;   // radians
    constexpr int CAM_YAW   = 0x6c;   // radians
    constexpr int CAM_ROLL  = 0xec;   // radians
    constexpr int CAM_FOV   = 0xc4;   // radians
    constexpr int CAM_NEAR  = 0xc8;
    constexpr int CAM_FAR   = 0xcc;

    constexpr int BILBO_GETPOS_VSLOT = 0x28; // bilbo vtable -> float* world position
}

using SetupView_t = void (__thiscall*)(void* cam, void* view);

struct Vec3 { float x, y, z; };

// ---- engine-convention math --------------------------------------------------
inline Vec3 Forward(float yaw, float pitch) {
    float cp = std::cos(pitch);
    return { cp * std::sin(yaw), -std::sin(pitch), cp * std::cos(yaw) };
}
inline Vec3 Right(float yaw) { return { std::cos(yaw), 0.0f, -std::sin(yaw) }; }
inline float Deg(float d)    { return d * 0.01745329252f; } // degrees -> radians helper

// ---- modes / state -----------------------------------------------------------
enum Mode { CAM_OFF = 0, CAM_SHOULDER, CAM_FREE, CAM_PC };

inline Mode&  ModeRef()      { static Mode  m = CAM_OFF; return m; }
inline float& ShoulderRef()  { static float s = 60.0f;   return s; } // +right, flip sign for left
inline float& FovOverride()  { static float f = 0.0f;    return f; } // 0 = leave engine FOV

// freecam state
inline Vec3&  FreePos()      { static Vec3  p{0,0,0};    return p; }
inline float& FreeYaw()      { static float y = 0.0f;    return y; }
inline float& FreePitch()    { static float p = 0.0f;    return p; }
inline bool&  FreeSeeded()   { static bool  b = false;   return b; }

// PC-orbit state
inline float& OrbitYaw()     { static float y = 0.0f;    return y; }
inline float& OrbitPitch()   { static float p = 0.0f;    return p; }
inline float& OrbitDist()    { static float d = 0.0f;    return d; }
inline float& FocusHeight()  { static float h = 0.0f;    return h; } // raise orbit centre off Bilbo's origin
inline bool&  OrbitSeeded()  { static bool  b = false;   return b; }

inline SetupView_t& Orig()   { static SetupView_t f = nullptr; return f; }

// ---- Bilbo world position (orbit centre) -------------------------------------
inline bool BilboPos(Vec3& out) {
    void* b = *reinterpret_cast<void**>(addr::GetBilboPtr);
    if (!b) return false;
    void** vt = *reinterpret_cast<void***>(b);
    using GetPos_t = float* (__thiscall*)(void*);
    float* p = reinterpret_cast<GetPos_t>(vt[addr::BILBO_GETPOS_VSLOT / 4])(b);
    if (!p) return false;
    out = { p[0], p[1], p[2] };
    return true;
}

inline float ClampPitch(float p) {                 // avoid gimbal flip at the poles
    const float lim = 1.55334f;                     // ~89 degrees
    return p < -lim ? -lim : (p > lim ? lim : p);
}

// ---- the per-frame hook ------------------------------------------------------
inline void __fastcall SetupViewHook(void* cam, void* /*edx*/, void* view) {
    if (cam && ModeRef() != CAM_OFF) {
        float* pos   = reinterpret_cast<float*>(reinterpret_cast<char*>(cam) + addr::CAM_POS);
        float* pitch = reinterpret_cast<float*>(reinterpret_cast<char*>(cam) + addr::CAM_PITCH);
        float* yaw   = reinterpret_cast<float*>(reinterpret_cast<char*>(cam) + addr::CAM_YAW);
        float* roll  = reinterpret_cast<float*>(reinterpret_cast<char*>(cam) + addr::CAM_ROLL);

        if (ModeRef() == CAM_SHOULDER) {
            // Slide the engine's follow camera sideways along its right vector.
            // Orientation is left untouched, so Bilbo shifts to one side of frame.
            Vec3 r = Right(*yaw);
            pos[0] += r.x * ShoulderRef();
            pos[2] += r.z * ShoulderRef();
        }
        else if (ModeRef() == CAM_FREE) {
            if (!FreeSeeded()) {                    // start exactly where the game cam is
                FreePos()   = { pos[0], pos[1], pos[2] };
                FreeYaw()   = *yaw;
                FreePitch() = *pitch;
                FreeSeeded() = true;
            }
            pos[0] = FreePos().x; pos[1] = FreePos().y; pos[2] = FreePos().z;
            *pitch = FreePitch(); *yaw = FreeYaw(); *roll = 0.0f;
        }
        else if (ModeRef() == CAM_PC) {
            Vec3 c;
            if (BilboPos(c)) {
                c.y += FocusHeight();
                if (!OrbitSeeded()) {               // seed orbit from current cam -> seamless
                    float dx = pos[0] - c.x, dy = pos[1] - c.y, dz = pos[2] - c.z;
                    OrbitDist() = std::sqrt(dx*dx + dy*dy + dz*dz);
                    if (OrbitDist() < 1.0f) OrbitDist() = 300.0f;
                    // look direction = from camera toward centre
                    float fx = -dx, fy = -dy, fz = -dz;
                    OrbitYaw()   = std::atan2(fx, fz);
                    OrbitPitch() = ClampPitch(std::atan2(-fy, std::sqrt(fx*fx + fz*fz)));
                    OrbitSeeded() = true;
                }
                Vec3 f = Forward(OrbitYaw(), OrbitPitch());
                pos[0] = c.x - f.x * OrbitDist();   // camera sits behind the centre, looking at it
                pos[1] = c.y - f.y * OrbitDist();
                pos[2] = c.z - f.z * OrbitDist();
                *pitch = OrbitPitch(); *yaw = OrbitYaw(); *roll = 0.0f;
            }
        }

        if (FovOverride() > 0.0f)
            *reinterpret_cast<float*>(reinterpret_cast<char*>(cam) + addr::CAM_FOV) = FovOverride();
    }
    Orig()(cam, view);
}

// ============================================================================
//  PUBLIC API
// ============================================================================

// 1) Over-the-shoulder. lateral > 0 = camera's right (Bilbo to the left of frame);
//    negate for the left shoulder. Call once; adjust freely.
inline void ShoulderView(float lateral = 60.0f) { ShoulderRef() = lateral; ModeRef() = CAM_SHOULDER; }

// 2) Detached freecam. Re-seeds from the current camera each time you enable it.
inline void Freecam() { FreeSeeded() = false; ModeRef() = CAM_FREE; }

// 3) Keyboard-driven orbit around Bilbo (the "PC camera"). Re-seeds on enable so it
//    starts from wherever the game camera was.
inline void PCCamera() { OrbitSeeded() = false; ModeRef() = CAM_PC; }

// Restore the normal game camera.
inline void Off() { ModeRef() = CAM_OFF; FovOverride() = 0.0f; }

inline Mode Current() { return ModeRef(); }

// ---- per-frame input (call from your input loop while a mode is active) ------

// Look: yaw/pitch deltas in radians. Drives Freecam AND PCCamera. This is your
// "as soon as a key is pressed, the camera responds" hook — feed keyboard deltas.
inline void Look(float dYaw, float dPitch) {
    if (ModeRef() == CAM_FREE) {
        FreeYaw()   += dYaw;
        FreePitch()  = ClampPitch(FreePitch() + dPitch);
    } else if (ModeRef() == CAM_PC) {
        OrbitYaw()   += dYaw;
        OrbitPitch()  = ClampPitch(OrbitPitch() + dPitch);
    }
}

// Freecam translation: units along forward / right / world-up (per frame).
inline void MoveFreecam(float forward, float strafe, float up) {
    if (ModeRef() != CAM_FREE) return;
    Vec3 f = Forward(FreeYaw(), FreePitch());
    Vec3 r = Right(FreeYaw());
    FreePos().x += f.x * forward + r.x * strafe;
    FreePos().y += f.y * forward + up;
    FreePos().z += f.z * forward + r.z * strafe;
}

// PCCamera zoom: change orbit distance (units). Positive = pull back.
inline void Zoom(float dDist) {
    if (ModeRef() != CAM_PC) return;
    OrbitDist() += dDist;
    if (OrbitDist() < 20.0f) OrbitDist() = 20.0f;
}

// FOV control (radians). SetFov(0) clears the override. Works in any mode.
inline void SetFov(float radians) { FovOverride() = radians; }
inline void AddFov(float dRadians) { if (FovOverride() <= 0.0f) FovOverride() = 1.0f; FovOverride() += dRadians; }

// Raise the orbit centre off Bilbo's origin (e.g. to his torso/head). PC mode only.
inline void SetFocusHeight(float h) { FocusHeight() = h; }

// ============================================================================
//  INSTALL (once, e.g. at DLL init — uses MinHook like the rest of your project)
//
//     static hobbit_cam::SetupView_t o_SetupView = nullptr;
//     MH_Initialize();
//     MH_CreateHook((void*)hobbit_cam::addr::SetupView,
//                   &hobbit_cam::SetupViewHook,
//                   (void**)&hobbit_cam::Orig());        // stores the original
//     MH_EnableHook((void*)hobbit_cam::addr::SetupView);
//
//  Then, somewhere you have keyboard state (your ImGui / WndProc / poll loop):
//
//     // toggle modes on hotkeys
//     if (pressed(VK_F1)) hobbit_cam::ShoulderView(60.f);   // over-the-shoulder
//     if (pressed(VK_F2)) hobbit_cam::Freecam();            // free fly
//     if (pressed(VK_F3)) hobbit_cam::PCCamera();           // keyboard orbit
//     if (pressed(VK_F4)) hobbit_cam::Off();                // back to normal
//
//     // feed input each frame for Freecam / PCCamera:
//     float look = hobbit_cam::Deg(2.0f);                    // ~2 deg/key/frame
//     if (down(VK_LEFT))  hobbit_cam::Look(-look, 0);
//     if (down(VK_RIGHT)) hobbit_cam::Look( look, 0);
//     if (down(VK_UP))    hobbit_cam::Look(0, -look);
//     if (down(VK_DOWN))  hobbit_cam::Look(0,  look);
//     // freecam movement (units/frame):
//     if (down('W')) hobbit_cam::MoveFreecam( 25, 0, 0);
//     if (down('S')) hobbit_cam::MoveFreecam(-25, 0, 0);
//     if (down('D')) hobbit_cam::MoveFreecam(0,  25, 0);
//     if (down('A')) hobbit_cam::MoveFreecam(0, -25, 0);
//     if (down('E')) hobbit_cam::MoveFreecam(0, 0,  25);
//     if (down('Q')) hobbit_cam::MoveFreecam(0, 0, -25);
//     // PC orbit zoom:
//     if (down(VK_OEM_PLUS))  hobbit_cam::Zoom(-15);
//     if (down(VK_OEM_MINUS)) hobbit_cam::Zoom( 15);
//
//  Notes / tuning:
//   * If the shoulder slides the WRONG way, negate the lateral value.
//   * If freecam/orbit looks mirrored on your build, the yaw sign is the only
//     thing to flip — negate dYaw in Look() (engine handedness is fixed, but this
//     is the one knob if a rebuild differs).
//   * Units: the game world is large; 25/frame is a brisk freecam, 60 is a
//     reasonable shoulder offset, orbit distance is whatever the follow cam used.
//   * PCCamera needs Bilbo to exist (in-level). It no-ops on menus/loading.
// ============================================================================

} // namespace hobbit_cam
