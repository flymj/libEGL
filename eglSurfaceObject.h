#ifndef _egl_surface_object_h
#define _egl_surface_object_h
#include <eglObject.h>
#include <eglType.h>
class EGLSurfaceObject : public EGLObject
{
public:
    EGLSurfaceObject(EGLConfig config, EGLNativeWindowType win, const int *attrib_list)
    {}
    bool validate(EGLApiType api)
    {
        return true;
    }
    bool realize(EGLApiType api)
    {
        return true;
    }
    void *getNativeObject()
    {
        return NULL;
    }
private:
};
#endif
