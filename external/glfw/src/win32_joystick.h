// Copyright (c) 2006-2023. Minh Nguyen
// All rights reserved.

#define _GLFW_PLATFORM_JOYSTICK_STATE         _GLFWjoystickWin32 win32
#define _GLFW_PLATFORM_LIBRARY_JOYSTICK_STATE struct { int dummyLibraryJoystick; }

#define _GLFW_PLATFORM_MAPPING_NAME "Windows"
#define GLFW_BUILD_WIN32_MAPPINGS

// Joystick element (axis, button or slider)
//
typedef struct _GLFWjoyobjectWin32
{
    int                     offset;
    int                     type;
} _GLFWjoyobjectWin32;

// Win32-specific per-joystick data
//
typedef struct _GLFWjoystickWin32
{
    _GLFWjoyobjectWin32*    objects;
    int                     objectCount;
    IDirectInputDevice8W*   device;
    DWORD                   index;
    GUID                    guid;
} _GLFWjoystickWin32;


void _glfwInitJoysticksWin32(void);
void _glfwTerminateJoysticksWin32(void);
void _glfwDetectJoystickConnectionWin32(void);
void _glfwDetectJoystickDisconnectionWin32(void);

