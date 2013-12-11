#ifndef _egl_type_h
#define _egl_type_h
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <atitypes.h>
#include <cmVector.h>
typedef struct{
    int major;
    int minor;
}EGLVersionType;

typedef struct{
    unsigned long attrib;
    unsigned long value;
}EGLAttribPair;

typedef enum{
    EGL_PLATFORM_X11 = 0,
    EGL_PLATFORM_ANDROID = 1,
    AMD_WINDOW_SYSTEM_LAST = EGL_PLATFORM_ANDROID,
}EGLPlatformType;

typedef enum{
    EGL_RESOURCE_SURFACE = 0,
    EGL_RESOURCE_CONTEXT = 1,
    EGL_RESOURCE_IMAGE   = 2,
    EGL_RESOURCE_SYNC    = 3,
    EGL_RESOURCE_CONFIG  = 4,
    EGL_RESOURCE_DISPLAY = 5,
    EGL_RESOURCE_LAST    = EGL_RESOURCE_DISPLAY,
}EGLResourceType;

typedef enum{
    EGL_API_OPENGL      = 1,
    EGL_API_OPENGL_ES1  = 2,
    EGL_API_OPENGL_ESx  = 4,
    EGL_API_OPENGL_ES   = EGL_API_OPENGL_ES1 | EGL_API_OPENGL_ESx,
    EGL_API_OPENVG      = 8,
    EGL_API_TOTAL       = EGL_API_OPENGL_ES  // currently we don't support OpenVG
}EGLApiType;


typedef struct {} icdInterface;
// more definition need to put to here.

#endif
