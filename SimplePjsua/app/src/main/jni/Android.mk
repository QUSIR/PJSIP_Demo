LOCAL_PATH := $(call my-dir)

PJSIP_PATH:=$(LOCAL_PATH)/pjsip

include $(CLEAR_VARS)
LOCAL_MODULE    := SimplePjsua
SRC_LIST :=$(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES += $(SRC_LIST:$(LOCAL_PATH)/%=%)
#LOCAL_SRC_FILES := Client.cpp SimplePjsua.cpp
LOCAL_CFLAGS += -DPJ_AUTOCONF=1 -DPJ_IS_BIG_ENDIAN=0 -DPJ_IS_LITTLE_ENDIAN=1
LOCAL_C_INCLUDES += $(LOCAL_PATH)/public
LOCAL_C_INCLUDES += $(LOCAL_PATH)/video
LOCAL_C_INCLUDES += $(PJSIP_PATH)
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjlib/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjlib-util/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjmedia/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjnath/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjsip/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/pjsip
LOCAL_LDLIBS += -L$(PJSIP_PATH) \
	-lpjsua-arm-unknown-linux-androideabi -lpjsip-ua-arm-unknown-linux-androideabi -lpjsip-simple-arm-unknown-linux-androideabi \
	-lpjsip-arm-unknown-linux-androideabi -lpjmedia-codec-arm-unknown-linux-androideabi -lpjmedia-arm-unknown-linux-androideabi \
	-lpjmedia-videodev-arm-unknown-linux-androideabi -lpjmedia-audiodev-arm-unknown-linux-androideabi -lpjmedia-arm-unknown-linux-androideabi \
	-lpjnath-arm-unknown-linux-androideabi -lpjlib-util-arm-unknown-linux-androideabi  -lsrtp-arm-unknown-linux-androideabi -lresample-arm-unknown-linux-androideabi \
	-lgsmcodec-arm-unknown-linux-androideabi -lspeex-arm-unknown-linux-androideabi -lilbccodec-arm-unknown-linux-androideabi -lg7221codec-arm-unknown-linux-androideabi \
	-lpj-arm-unknown-linux-androideabi -L/lib
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
LOCAL_STATIC_LIBRARIES+=PjsipGdiot
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := PjsipGdiot
PJSIP_CPP_LIST := $(wildcard $(LOCAL_PATH)/pjsip/*.cpp)
PJSIP_CPP_LIST += public/Lock.cpp public/Subject.cpp public/Observer.cpp
LOCAL_SRC_FILES := $(PJSIP_CPP_LIST:$(LOCAL_PATH)/%=%)
#LOCAL_SRC_FILES := public/Lock.cpp public/Subject.cpp public/Observer.cpp pjsip/SipClient.cpp
LOCAL_CFLAGS += -DPJ_AUTOCONF=1 -DPJ_IS_BIG_ENDIAN=0 -DPJ_IS_LITTLE_ENDIAN=1
LOCAL_C_INCLUDES += $(LOCAL_PATH)/public
LOCAL_C_INCLUDES += $(PJSIP_PATH)
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjlib/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjlib-util/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjmedia/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjnath/include
LOCAL_C_INCLUDES += $(PJSIP_PATH)/pjsip/include
LOCAL_ARM_MODE := arm
include $(BUILD_STATIC_LIBRARY)


