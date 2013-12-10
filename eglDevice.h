#ifndef _egl_device_h
#define _egl_device_h
#include <eglType.h>
#include <eglDisplayObject.h>

class EGLDisplayObject;

class EGLDevice
{
public:
    EGLDevice(){}
    bool addDisplay(EGLDisplayObject *display);
    bool removeDisplay(EGLDisplayObject *display);
    bool init(EGLApiType api);
private:
    icdInterface *_interface[EGL_API_TOTAL];
    cmVector<EGLDisplayObject*> _display;
};

class EGLDeviceManager
{
public:
    static EGLDevice *getDevice(EGLDisplayObject *display);
private:
    static cmVector<EGLDevice*> _device;
};
#endif
