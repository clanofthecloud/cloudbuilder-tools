LOCAL_PATH := $(call my-dir)

CLOUDBUILDER_PATH	= ../../delivery/CloudBuilder
SOURCES_PATH		= ./

include $(CLEAR_VARS)

LOCAL_MODULE	:= CloudBuilder
LOCAL_SRC_FILES	:= ../$(CLOUDBUILDER_PATH)/Android/Cloudbuilder_native/CloudBuilder.so

include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE	:= CppApplication
LOCAL_CFLAGS	:= -D__ANDROID__ -w
LOCAL_C_INCLUDES	:=	$(CLOUDBUILDER_PATH)/headers	\
						$(RABBITFACTORY_PATH)/Headers $(RABBITFACTORY_PATH)/Headers/Android	\
						$(SOURCES_PATH)
						
LOCAL_SRC_FILES	:= 	$(SOURCES_PATH)/App.cpp

LOCAL_LDLIBS	:= -lm -llog -ldl
LOCAL_SHARED_LIBRARIES	:= CloudBuilder

include $(BUILD_SHARED_LIBRARY)
