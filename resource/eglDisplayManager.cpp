#include <eglDisplayManager.h>
#include <wsaInterface.h>
EGLPlatformType EGLDisplayManager::getPlatformType(EGLNativeDisplayType display_id)
{
    for( int i = 0 ; i < _displayDB.size() ; i ++ )
    {
        if( _displayDB[i]->getNativeDisplay() == display_id )
        {
            return _displayDB[i]->getPlatform();
        }
    }
    return wsaInterface::getPlatform(display_id);
}

EGLDisplayObject *EGLDisplayManager::getDisplay(EGLDisplay display)
{
    if( _displayDB.findIndex(reinterpret_cast<EGLDisplayObject*>(display)) != -1 )
    {
        return reinterpret_cast<EGLDisplayObject*>(display);
    }
    else
    {
        return NULL;;
    }
}

EGLDisplayObject *EGLDisplayManager::getDisplay(EGLPlatformType platform, EGLNativeDisplayType display_id)
{
    for( int i=0; i<_displayDB.size(); i++ )
    {
        if( (_displayDB[i]->getNativeDisplay()== display_id) && (_displayDB[i]->getPlatform() == platform) )
        {
            return _displayDB[i];
        }
    }
    EGLDisplayObject *display = new EGLDisplayObject(display_id, platform);
    EGLDevice *device = EGLDeviceManager::getDevice(display);
    display->setDevice(device);

    _displayDB.push_back(display);

    return display;
}
