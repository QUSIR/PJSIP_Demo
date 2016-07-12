/*
 * SipSipClient.h
 *
 *  Created on: 2015-9-28
 *      Author: Ken
 */

#ifndef SIPCLIENT_H_
#define SIPCLIENT_H_

#include <stddef.h>
#include "Lock.h"
#include "Subject.h"

#include <pjsua-lib/pjsua.h>

class SipClient : public Subject {
public:
	static SipClient* getInstance();
	int init(const char* ip, short port, const char* account, const char* password, const char* realm);
	void call(const char *called);
	void hangup();
	void destroy();

private:
	int exitReturn(const char *content,int status, int result);
    pjsua_acc_id acc_id;
    char ip[33],account[65],password[65],realm[33];
    short port;
    bool isInit;

    SipClient(void);
    ~SipClient(void);
    SipClient(const SipClient &obj);
    SipClient& operator=(const SipClient& obj);
    static SipClient* instance;
    class Garbo {
    public:
	    ~Garbo(){
		    if(NULL!=SipClient::instance){
			    delete SipClient::instance;
			    SipClient::instance=NULL;
		    }
	    }
    };
    static Garbo garbo;
    static Lock lock;
};

#endif /* SIPCLIENT_H_ */
