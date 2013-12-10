#ifndef _egl_surface_object_h
#define _egl_surface_object_h
#include <eglObject.h>
#include <eglType.h>
class EGLSurfaceObject : public EGLObject
{
    public:
        bool validate(EGLApiType api)
        {
            return true;
        }
        bool realize(EGLApiType api)
        {
            return true;
        }

    private:
};
#endif
