GCC=gcc
LD=ld
CXXFILES= eglDispatchTable.cpp  \
          eglDisplayManager.cpp \
          eglDisplayObject.cpp \
          eglDevice.cpp 

OBJECTS=${patsubst %.cpp, %.o, ${CXXFILES}}

Headfiles= eglDisplayObject.h  \
           eglType.h           \
           cmVector.h          \
           eglDisplayManager.h \
           eglSurfaceObject.h  \
           eglContextObject.h  \
           eglObject.h         \
           eglSyncObject.h     \
           eglConfigObject.h   \
           eglDevice.h         \
           eglThreadMgr.h

CXXFLAGS = -O2 -fPIC -I./ -I/usr/include -o 
LDFLAGS  = -fPIC -shared -o
TARGET = libEGL.so
all: $(OBJECTS)
	$(GCC) $^  $(LDFLAGS) $(TARGET)

$(OBJECTS):%.o:%.cpp
	$(GCC) -c $< $(CXXFLAGS) $@

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGET) 
