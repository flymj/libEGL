#ifndef _egl_config_object_h
#define _egl_config_object_h
#include <eglType.h>
#include <eglObject.h>
#include <eglDisplayObject.h>
#include <cmVector.h>
class EGLDisplayObject;
class EGLConfigObject : public EGLObject
{
public:
    EGLConfigObject(EGLDisplayObject *disp){}
    EGLConfigObject(EGLDisplayObject *disp, EGLAttribPair *attr){}
    ~EGLConfigObject(){}
    static void sort(cmVector<EGLConfigObject*> config){}
private:
    
    
};
#endif
