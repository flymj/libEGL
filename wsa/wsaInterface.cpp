#include <wsaInterface.h>
#include <wsaInstance.h>
EGLPlatformType wsaInterface::getPlatform(EGLNativeDisplayType display_id)
{
    // To Do.
    // detection based on env
    // detection based on id
    return EGL_PLATFORM_ANDROID;
}

wsaInstanceHandle wsaInterface::create(EGLPlatformType platform, EGLNativeDisplayType display_id)
{
    wsaInstance *instance = wsaInstanceFactory::create(platform, display_id);
    return reinterpret_cast<wsaInstanceHandle>(instance);
}
