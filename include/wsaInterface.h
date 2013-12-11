#ifndef _wsa_interface_h
#define _wsa_interface_h
#include <eglType.h>
typedef struct tagwsaInstance{}*wsaInstanceHandle; 
class wsaInterface
{
public:
    static EGLPlatformType getPlatform(EGLNativeDisplayType display_id);
    static wsaInstanceHandle create(EGLPlatformType platform, EGLNativeDisplayType display_id);
private:
};
#endif
