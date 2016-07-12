/*
 * SipClient.cpp
 *
 *  Created on: 2015-9-28
 *      Author: Ken
 */

#include "SipClient.h"
#include <string.h>

#define THIS_FILE	"SipClient.cpp"
//#define SIP_DOMAIN	"14.146.226.97"
//#define SIP_USER	"2026603"
//#define SIP_PASSWD	"123456"
//#define SIP_REALM "asterisk"

#include <jni.h>
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, THIS_FILE, __VA_ARGS__))

SipClient* SipClient::instance=NULL;
Lock SipClient::lock;
SipClient*  SipClient::getInstance(){
	if(instance==NULL){
		lock.lock();
		SipClient* inst=instance;
		if(inst==NULL){
			inst=new SipClient();
		}

		lock.unlock();
		instance=inst;
	}

	return instance;
}


SipClient::SipClient() {
	this->isInit=false;
}

SipClient::~SipClient() {
}

/* Callback called by the library upon receiving incoming call */
static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,
			     pjsip_rx_data *rdata){
    pjsua_call_info ci;

    PJ_UNUSED_ARG(acc_id);
    PJ_UNUSED_ARG(rdata);

    pjsua_call_get_info(call_id, &ci);

    PJ_LOG(3,(THIS_FILE, "Incoming call from %.*s!!",
			 (int)ci.remote_info.slen,
			 ci.remote_info.ptr));
    LOGI("Incoming call from %.*s!!",
			 (int)ci.remote_info.slen,
			 ci.remote_info.ptr);
    /* Automatically answer incoming calls with 200/OK */
//    pjsua_call_answer(call_id, 200, NULL, NULL);
}

/* Callback called by the library when call's state has changed */
static void on_call_state(pjsua_call_id call_id, pjsip_event *e)
{
    pjsua_call_info ci;

    PJ_UNUSED_ARG(e);

    pjsua_call_get_info(call_id, &ci);
    PJ_LOG(3,(THIS_FILE, "Call %d state=%.*s", call_id,
			 (int)ci.state_text.slen,
			 ci.state_text.ptr));
    LOGI("Call %d state=%.*s", call_id,
			 (int)ci.state_text.slen,
			 ci.state_text.ptr);
    if(ci.state==PJSIP_INV_STATE_CALLING || ci.state==PJSIP_INV_STATE_CONNECTING || ci.state==PJSIP_INV_STATE_DISCONNECTED)
    	SipClient::getInstance()->msgStatus((int)(ci.state));

}

/* Callback called by the library when call's media state has changed */
static void on_call_media_state(pjsua_call_id call_id){
    pjsua_call_info ci;

    pjsua_call_get_info(call_id, &ci);

    if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE) {
	// When media is active, connect call to sound device.
		pjsua_conf_connect(ci.conf_slot, 0);
		pjsua_conf_connect(0, ci.conf_slot);
    }
}

/*
* DTMF callback.
*/
static void call_on_dtmf_callback(pjsua_call_id call_id, int dtmf){
	PJ_LOG(3,(THIS_FILE, (char*)"Incoming DTMF on call %d: %c", call_id, dtmf));
	LOGI("Incoming DTMF on call %d: %c", call_id, dtmf);
	if(dtmf==42) SipClient::getInstance()->msgStatus(dtmf);
}



int SipClient::exitReturn(const char *content, int status, int result){
	LOGI("%s, error=%d",content,status);
	pjsua_destroy();
	return result;
}

int SipClient::init(const char* ip, short port, const char* account, const char* password, const char* realm){
	memset(this->ip,0,33);
	memcpy(this->ip,ip,strlen(ip)>32?32:strlen(ip));
	memset(this->account,0,65);
	memcpy(this->account,account,strlen(account)>64?64:strlen(account));
	memset(this->password,0,65);
	memcpy(this->password,password,strlen(password)>64?64:strlen(password));
	memset(this->realm,0,33);
	memcpy(this->realm,realm,strlen(realm)>32?32:strlen(realm));
	this->port=port;

    pj_status_t status;
    /* Create pjsua first! */
    status = pjsua_create();
    if (status != PJ_SUCCESS) return exitReturn("Error in pjsua_create()",status, -1);

    /* Init pjsua */
    {
	pjsua_config cfg;
	pjsua_logging_config log_cfg;

	pjsua_config_default(&cfg);
	cfg.cb.on_incoming_call = &on_incoming_call;
	cfg.cb.on_call_media_state = &on_call_media_state;
	cfg.cb.on_call_state = &on_call_state;
	cfg.cb.on_dtmf_digit = &call_on_dtmf_callback;

	pjsua_logging_config_default(&log_cfg);
	log_cfg.console_level = 4;

	status = pjsua_init(&cfg, &log_cfg, NULL);
	if (status != PJ_SUCCESS) return exitReturn("Error in pjsua_init()",status, -2);
    }

    /* Add UDP transport. */
    {
	pjsua_transport_config cfg;

	pjsua_transport_config_default(&cfg);
	cfg.port = 5060;
	status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &cfg, NULL);
	if (status != PJ_SUCCESS) return exitReturn("Error creating transport",status, -3);
    }

    /* Initialization is done, now start pjsua */
    status = pjsua_start();
    if (status != PJ_SUCCESS) return exitReturn("Error starting pjsua",status, -4);

    /* Register to SIP server by creating SIP account. */
    {
	pjsua_acc_config cfg;

	pjsua_acc_config_default(&cfg);
	char id[255]={'\0'},url[50]={'\0'};
	sprintf(id,"sip:%s@%s",this->account,this->ip);
	sprintf(url,"sip:%s",this->ip);
	cfg.id = pj_str(id);
	cfg.reg_uri = pj_str(url);
	cfg.cred_count = 1;
	cfg.cred_info[0].realm = pj_str(this->realm);
	cfg.cred_info[0].scheme = pj_str((char*)"digest");
	cfg.cred_info[0].username = pj_str(this->account);
	cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
	cfg.cred_info[0].data = pj_str(this->password);
	cfg.allow_contact_rewrite=0;

	status = pjsua_acc_add(&cfg, PJ_TRUE, &acc_id);
	if (status != PJ_SUCCESS) return exitReturn("Error adding account",status, -5);
    }

    isInit=true;
    LOGI("init pjsip is ok");
	return 0;
}

void SipClient::destroy(){
    pjsua_destroy();
    isInit=false;
}

void SipClient::call(const char *called){
	if(!isInit) return;
	pj_status_t status;
	char uriString[255]={'\0'};
	sprintf(uriString,"sip:%s@%s:%d",called,this->ip,this->port);
	pj_str_t uri =pj_str(uriString);
	status = pjsua_call_make_call(acc_id, &uri, 0, NULL, NULL, NULL);
	if (status != PJ_SUCCESS) LOGI("fail to make call, error = %d", status);
}

void SipClient::hangup(){
	pjsua_call_hangup_all();
}
