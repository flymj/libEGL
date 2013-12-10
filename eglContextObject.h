#ifndef _egl_context_object_h
#define _egl_context_object_h
#include <eglObject.h>
#include <eglSurfaceObject.h>
#include <eglType.h>

class EGLContextObject : public EGLObject
{
public:
    EGLContextObject(EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
    {
    }
    bool makeCurrent(EGLSurfaceObject *draw, EGLSurfaceObject *read)
    {
        return false;
    }
    void *getNativeObject()
    {
        return NULL;
    }
    EGLApiType getAPI()
    {
        return _api;
    }
private:
    EGLApiType _api;
};

class EGLContextFactory : public EGLObject
{
public:
    static EGLContextObject* create(EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
    {
        return new EGLContextObject(config, share_context, attrib_list);
    }
};
#endif
