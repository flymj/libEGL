#include <eglThreadMgr.h>
#include <eglDisplayObject.h>
EGLDisplayObject::EGLDisplayObject(EGLNativeDisplayType display, EGLPlatformType platform)
{
    _nativeDisplay = display;
    _platform = platform;
    pthread_mutex_create(&_mutex, NULL);
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

    cmVector<EGLConfigObject*>::iterate iter;
    uint64  *ref = reinterpret_cast<uint64*> configs;
    *num_config = 0;
    for( iter = _configDB.begin(); iter != _configDB.end(); iter ++ )
    {
         *ref++ = iter->_configID;
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
            ret = _surfaceDB.findIndex(obj) != -1;
            break;
        case EGL_RESOURCE_CONTEXT:
            ret = _contextDB.findIndex(obj) != -1;
            break;
        case EGL_RESOURCE_IMAGE:
            ret = _imageDB.findIndex(obj) != -1;
            break;
        case EGL_RESOURCE_SYNC:
            ret = _syncDB.findIndex(obj) != -1;
            break;
        case EGL_RESOURCE_CONFIG:
            ret = _configDB.findIndex(obj) != -1;
            break;
        default:
            assert(0);
            ret = false;
            break;
    }
    return ret;
}

bool EGLDisplayObject::created(void *obj, EGLResourceType type)
{
    cmVector<EGLObject*>::iterate iter;
    cmVector<EGLObject*>::iterate iterEnd;
    if( type == EGL_RESOURCE_SURFACE )
    {
        iter = _surfaceDB.begin();
        iterEnd = _surfaceDB.end();
    }
    else if( type == EGL_RESOURCE_CONTEXT )
    {
        iter = _contextDB.begin();
        iterEnd = _contextDB.end();
    }
    else if( type == EGL_RESOURCE_IMAGE )
    {
        iter = _imageDB.begin();
        iterEnd = _imageDB.end();
    }
    else if( type == EGL_RESOURCE_SYNC )
    {
        iter = _syncDB.begin();
        iterEnd = _syncDB.end();
    }
    else if( type == EGL_RESOURCE_CONFIG )
    {
        iter = _configDB.begin();
        iterEnd = _configDB.end();
    }
    else
    {
        assert(!"error");
        iter = NULL;
    }
    if( iter != NULL )
    {
        for(; iter != iterEnd; iter++ )
        {
            if( iter->getNativeObject() == obj )
            {
                return true;
            }
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

EGLSurfaceObject *EGLSurfaceObject::createSurfaceObject(EGLConfig config, EGLNativeWindowType win, const int *attrib_list)
{
    EGLSurfaceObject *surface = new EGLSurfaceObject(config, win, attrib_list);
    _surfaceDB.push_back(surface);
    return surface;
}

bool EGLDisplayObject::makeCurrent(EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    EGLSurfaceObject *drawSurf = reinterpret_cast<EGLSurfaceObject*>draw;
    EGLSurfaceObject *readSurf = reinterpret_cast<EGLSurfaceObject*>read;
    EGLContextObject *context  = reinterpret_cast<EGLContextObject*>ctx;
    
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

