#pragma once

#include <jni.h>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "JNIMsg", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "JNIMsg", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "JNIMsg", __VA_ARGS__))

#define log_debug LOGI
#define log_warning LOGW
#define log_error LOGE

