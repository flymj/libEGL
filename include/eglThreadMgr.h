#ifndef _egl_thread_mgr_h
#define _egl_thread_mgr_h
#include <eglObject.h>
#include <eglType.h>
#include <eglContextObject.h>

class EGLThreadMgr : public EGLObject
{
public:
    static void setError(int error)
    {
        _error = error;
    }
    static void bindApi(EGLApiType api)
    {
        _api = api;
    }
    static EGLApiType getBindApi()
    {
        return _api;
    }
    static void setCurrentContext(EGLContextObject* ctx)
    {
        _currentContext = ctx;
    }
private:
    static __thread int _error;
    static __thread EGLContextObject *_currentContext;
    static __thread EGLApiType _api;
};
#endif
