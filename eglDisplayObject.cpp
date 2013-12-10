#include <eglThreadMgr.h>
#include <eglDisplayObject.h>
EGLDisplayObject::EGLDisplayObject(EGLNativeDisplayType display, EGLPlatformType platform)
{
    _nativeDisplay = display;
    _platform = platform;
    pthread_mutex_init(&_mutex, NULL);
}

bool EGLDisplayObject::init()
{
    initConfig();
    _device->initRuntimeConfig();
    _initialized = true;
    _version.major = 1;
    _version.minor = 4;
    return true;
}

void EGLDisplayObject::initConfig()
{
}

bool EGLDisplayObject::getConfigs(EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    if( !_configDB.size() )
    {
        return false;
    }

    unsigned long *ref = reinterpret_cast<unsigned long*>(configs);
    *num_config = 0;
    for( int i = 0; i<_configDB.size(); i++ )
    {
         *ref++ = _configDB[i]->getConfigID();
         *num_config ++;
         if( *num_config > config_size )
         {
            break;
         }
    }
    return true;
}

bool EGLDisplayObject::getConfigs(EGLint *num_config)
{
    *num_config = _configDB.size();
    if( *num_config > 0  )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool EGLDisplayObject::validateResource(EGLObject *obj, EGLResourceType type)
{
    bool ret = true;
    switch(type)
    {
        case EGL_RESOURCE_SURFACE:
            ret = _surfaceDB.findIndex(static_cast<EGLSurfaceObject*>(obj)) != -1;
            break;
        case EGL_RESOURCE_CONTEXT:
            ret = _contextDB.findIndex(static_cast<EGLContextObject*>(obj)) != -1;
            break;
        case EGL_RESOURCE_IMAGE:
            ret = _imageDB.findIndex(static_cast<EGLImageObject*>(obj)) != -1;
            break;
        case EGL_RESOURCE_SYNC:
            ret = _syncDB.findIndex(static_cast<EGLSyncObject*>(obj)) != -1;
            break;
        case EGL_RESOURCE_CONFIG:
            ret = _configDB.findIndex(static_cast<EGLConfigObject*>(obj)) != -1;
            break;
        default:
            assert(0);
            ret = false;
            break;
    }
    return ret;
}

bool EGLDisplayObject::imageCreated(void *obj)
{
    for(int i=0; i<_imageDB.size(); i++)
    {
        if( _imageDB[i]->getNativeObject() == obj )
        {
            return true;
        }
    }
    return false;
}

bool EGLDisplayObject::surfaceCreated(void *obj)
{
    for(int i=0; i<_surfaceDB.size(); i++)
    {
        if( _surfaceDB[i]->getNativeObject() == obj )
        {
            return true;
        }
    }
    return false;
}
bool EGLDisplayObject::contextCreated(void *obj)
{
    for(int i=0; i<_contextDB.size(); i++)
    {
        if( _contextDB[i]->getNativeObject() == obj )
        {
            return true;
        }
    }
    return false;
}

EGLContextObject *EGLDisplayObject::createContextObject(EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    EGLContextObject *context = EGLContextFactory::create(config, share_context, attrib_list);
    _contextDB.push_back(context);
    EGLApiType api = context->getAPI();

    return context;
}

EGLSurfaceObject *EGLDisplayObject::createSurfaceObject(EGLConfig config, EGLNativeWindowType win, const int *attrib_list)
{
    EGLSurfaceObject *surface = new EGLSurfaceObject(config, win, attrib_list);
    _surfaceDB.push_back(surface);
    return surface;
}

bool EGLDisplayObject::makeCurrent(EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    EGLSurfaceObject *drawSurf = reinterpret_cast<EGLSurfaceObject*>(draw);
    EGLSurfaceObject *readSurf = reinterpret_cast<EGLSurfaceObject*>(read);
    EGLContextObject *context  = reinterpret_cast<EGLContextObject*>(ctx);
    
    EGLApiType api = context->getAPI();
    bool ret = true;

    if( !drawSurf->validate(api) )
    {
        ret = drawSurf->realize(api);
    }
    if( !readSurf->validate(api) )
    {
        ret = ret && readSurf->realize(api);
    } 

    if( ret )
    {
        ret = context->makeCurrent(drawSurf, readSurf);
    }

    return ret;
}

