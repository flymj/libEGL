#include <stdio.h>
#include <assert.h>
#include <eglType.h>
#include <eglDisplayObject.h>
#include <eglDisplayManager.h>
#include <eglThreadMgr.h>
#include <eglSerialize.h>

EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id)
{
    EGLPlatformType platform = EGLDisplayManager::getPlatformType(display_id);
    EGLDisplayObject *display = EGLDisplayManager::getDisplay(platform, display_id);
    assert(display);
    return reinterpret_cast<EGLDisplay>(display);
}

EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    EGLBoolean ret = EGL_TRUE;
    EGLDisplayObject *display = EGLDisplayManager::getDisplay(dpy);
    assert(display);
    EGLSerialize serialize(display->getMutex());

    if( !display->initialized() )
    {
        if( !display->init() )
        {
            ret = EGL_FALSE;
        }
    }
    
    if( ret == EGL_TRUE )
    {
        *major = display->getMajorVersion();
        *minor = display->getMinorVersion();
    }

    return ret;
}

EGLBoolean eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    EGLBoolean ret = EGL_TRUE;
    EGLDisplayObject *display = EGLDisplayManager::getDisplay(dpy);
    assert(display);
    EGLSerialize serialize(display->getMutex());

    if( !display->initialized() )
    {
        EGLThreadMgr::setError(EGL_NOT_INITIALIZED);
        ret = EGL_FALSE;
    }
    if( ret )
    {
        if( configs )
        {
            ret = display->getConfigs(configs, config_size, num_config);
        }
        else
        {
            ret = display->getConfigs(num_config);
        }
    }
    return ret;
}

EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
    EGLDisplayObject *display = EGLDisplayManager::getDisplay(dpy);
    assert(display);
    EGLSerialize serialize(display->getMutex());

    if( !display->initialized() )
    {
        EGLThreadMgr::setError(EGL_NOT_INITIALIZED);
        return EGL_NO_SURFACE;
    }
    if( display->surfaceCreated(reinterpret_cast<void *>(win)) )
    {
        EGLThreadMgr::setError(EGL_BAD_ALLOC);
        return EGL_NO_SURFACE;
    }
    if( !display->validateResource(reinterpret_cast<EGLObject*>(config), EGL_RESOURCE_CONFIG) )
    {
        EGLThreadMgr::setError(EGL_BAD_CONFIG);
        return EGL_NO_SURFACE;        
    }
    if( display->verifyNativeWindow(win) )
    {
        EGLThreadMgr::setError(EGL_BAD_NATIVE_WINDOW);
        return EGL_NO_SURFACE;
    }
    EGLSurfaceObject *surface = display->createSurfaceObject(config, win, attrib_list);
    if( !surface )
    {
        return EGL_NO_SURFACE;
    }
    else
    {
        return reinterpret_cast<EGLSurface>(surface);
    }
}

EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    EGLDisplayObject *display = EGLDisplayManager::getDisplay(dpy);
    assert(display);
    EGLSerialize serialize(display->getMutex());

    if( !display->initialized() )
    {
        EGLThreadMgr::setError(EGL_NOT_INITIALIZED);
        return EGL_NO_CONTEXT;
    }
    if( !display->validateResource(reinterpret_cast<EGLObject*>(config), EGL_RESOURCE_CONFIG) )
    {
        EGLThreadMgr::setError(EGL_BAD_CONFIG); 
        return EGL_NO_CONTEXT;       
    }
    if( !display->validateResource(reinterpret_cast<EGLObject*>(share_context), EGL_RESOURCE_CONTEXT) )
    {
        EGLThreadMgr::setError(EGL_BAD_MATCH);
        return EGL_NO_CONTEXT;
    }
    EGLContextObject *context = display->createContextObject(config, share_context, attrib_list);
    if( !context )
    {
        return EGL_NO_CONTEXT;
    }
    else
    {
        return reinterpret_cast<EGLContext>(context);
    }
}

EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    EGLDisplayObject *display = EGLDisplayManager::getDisplay(dpy);
    assert(display);
    EGLSerialize serialize(display->getMutex());

    if( !display->initialized() )
    {
        EGLThreadMgr::setError(EGL_NOT_INITIALIZED);
        return EGL_FALSE;
    }
    if( !(display->validateResource(reinterpret_cast<EGLObject*>(draw), EGL_RESOURCE_SURFACE) 
            && display->validateResource(reinterpret_cast<EGLObject*>(read), EGL_RESOURCE_SURFACE)
            && display->validateResource(reinterpret_cast<EGLObject*>(ctx), EGL_RESOURCE_CONTEXT)) )
    {
        EGLThreadMgr::setError(EGL_BAD_MATCH);
        return EGL_FALSE;
    }
    return display->makeCurrent(draw, read, ctx);
}

