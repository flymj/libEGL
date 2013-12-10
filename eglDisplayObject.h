#ifndef _EGL_DISPLAY_OBJECT_H
#define _EGL_DISPLAY_OBJECT_H
#include <eglType.h>
#include <eglDevice.h>
#include <eglObject.h>
#include <eglContextObject.h>
#include <eglSurfaceObject.h>
#include <eglImageObject.h>
#include <eglSyncObject.h>
#include <eglConfigObject.h>
#include <pthread.h>

class EGLDisplayObject : public EGLObject
{
public:
    EGLDisplayObject(EGLNativeDisplayType display, EGLPlatformType platform);
    ~EGLDisplayObject(){}
    bool init();
    bool initialized(){ return _initialized; }
    bool getConfigs(EGLConfig *configs, EGLint config_size, EGLint *num_config);
    bool getConfigs(EGLint *num_config);
    inline pthread_mutex_t *getMutex() { return &_mutex; }
    EGLNativeDisplayType getNativeDisplay(){ return _nativeDisplay; }
    EGLPlatformType getPlatform(){ return _platform; }
    bool validateResource(EGLObject *obj, EGLResourceType type);
    bool created(void *obj, EGLResourceType type);
    EGLContextObject *createContextObject(EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
    EGLSurfaceObject *createSurfaceObject(EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
    bool makeCurrent(EGLSurface draw, EGLSurface read, EGLContext ctx);
    int getMajorVersion(){ return _version.major; }
    int getMinorVersion(){ return _version.minor; }
    bool verifyNativeWindow(EGLNativeWindowType win){ return false;}
    bool setDevice(EGLDevice *device){ _device = device; }
private:
    void initConfig();
    EGLDevice *_device;
    pthread_mutex_t _mutex;
    cmVector<EGLContextObject*> _contextDB;
    cmVector<EGLSurfaceObject*> _surfaceDB;
    cmVector<EGLConfigObject*>  _configDB;
    cmVector<EGLImageObject*>   _imageDB;
    cmVector<EGLSyncObject*>    _syncDB;
    EGLNativeDisplayType      _nativeDisplay;
    EGLPlatformType           _platform;
    EGLVersionType            _version;
    bool _initialized;
     
};
#endif
