#ifndef _egl_display_manager_h
#define _egl_display_manager_h
#include <eglType.h>
#include <eglDisplayObject.h>
#include <eglDevice.h>
class EGLDisplayManager
{
public:
    static EGLPlatformType getPlatformType(EGLNativeDisplayType display_id);
    static EGLDisplayObject* getDisplay(EGLPlatformType platform, EGLNativeDisplayType display_id);
    static EGLDisplayObject* getDisplay(EGLDisplay display);
private:
    static cmVector<EGLDisplayObject*> _displayDB;
};
#endif
