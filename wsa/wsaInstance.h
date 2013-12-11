#ifndef _wsa_instance_h
#define _wsa_instance_h

class wsaInstance
{
public:
    wsaInstance()
    {
    }
protected:
    EGLNativeDisplayType _display;
    EGLPlatformType _platform;
};

class wsaAndroidInstance : public wsaInstance
{
public:
    wsaAndroidInstance(EGLNativeDisplayType display)
    {
        _display = display;
        _platform = EGL_PLATFORM_ANDROID;
    }
};

class wsaInstanceFactory
{
public:
    static wsaInstance *create(EGLPlatformType platform, EGLNativeDisplayType display)
    {
        // To Do. 
        // we can create wsaX11Instance/wsaGBMInstance/wsaWaylandInstance according to the platform.
        return static_cast<wsaInstance*>(new wsaAndroidInstance(display));
    }
};

#endif
