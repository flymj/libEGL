GCC=gcc
LD=ld
CXXFILES= eglDispatchTable.cpp  \
          eglDisplayManager.cpp \
          eglDisplayObject.cpp \
          eglContextObject.cpp \
          eglSurfaceObject.cpp \
          eglConfigObject.cpp \
          eglImageObject.cpp \
          eglSyncObject.cpp \
          eglDevice.cpp \
          wsaInterface.cpp 

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
           eglThreadMgr.h      \
           wsaInterface.h

vpath %.cpp ./resource
vpath %.cpp ./dispatch
vpath %.cpp ./wsa
vpath %.h   ./include

CXXFLAGS = -O2 -fPIC -DATI_COMP_GCC -DATI_OS_LINUX -I./include -I./wsa -I/usr/include -o 
LDFLAGS  = -fPIC -shared -o
TARGET = libEGL.so
all: $(OBJECTS)
	$(GCC) $^  $(LDFLAGS) $(TARGET)

$(OBJECTS):%.o:%.cpp
	$(GCC) -c $< $(CXXFLAGS) $@

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGET) 
