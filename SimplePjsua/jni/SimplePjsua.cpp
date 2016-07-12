#include "SimplePjsua.h"

#include "Client.h"
#include "Logger.h"
//#define SIP_DOMAIN	"14.146.226.97"
//#define SIP_USER	"2026603"
//#define SIP_PASSWD	"123456"
//#define SIP_REALM "asterisk"

static Client client;

JNIEXPORT int JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_initPjsip
  (JNIEnv *, jobject){
	log_debug("Java_cn_gdiot_simplepjsua_PjsuaJni_initPjsip");
	return client.init();
}

JNIEXPORT void JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_destroyPjsip
  (JNIEnv *, jobject){
	client.destroy();
}


JNIEXPORT void JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_call
  (JNIEnv *, jobject){
	client.call();
}

JNIEXPORT void JNICALL Java_cn_gdiot_simplepjsua_PjsuaJni_hangup
  (JNIEnv *, jobject){
	client.hangup();
}
