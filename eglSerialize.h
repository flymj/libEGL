#ifndef _egl_serialize_h
#define _egl_serialize_h
#include <pthread.h>
#include <eglObject.h>

class EGLSerialize : public EGLObject
{
public:
    EGLSerialize(pthread_mutex_t *mutex)
    {
        pthread_mutex_lock(mutex);
        _mutex = mutex;
    }
    ~EGLSerialize()
    {
        pthread_mutex_unlock(_mutex);
    }
private:
    pthread_mutex_t *_mutex;
};
#endif
