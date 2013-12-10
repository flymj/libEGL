#ifndef _egl_context_object_h
#define _egl_context_object_h
#include <eglObject.h>
#include <eglSurfaceObject.h>
#include <eglType.h>

class EGLContextObject : public EGLObject
{
public:
    bool makeCurrent(EGLSurfaceObject draw, EGLSurfaceObject read)
    {
        return false;
    }
};

#endif
