/*
 * SimplePjsua.h
 *
 *  Created on: 2015-9-24
 *      Author: Ken
 */

#ifndef SIMPLEPJSUA_H_
#define SIMPLEPJSUA_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT int JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_initPjsip
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_destroyPjsip
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_call
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_hangup
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif

#endif /* SIMPLEPJSUA_H_ */
