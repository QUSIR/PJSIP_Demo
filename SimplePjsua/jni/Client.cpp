/*
 * Client.cpp
 *
 *  Created on: 2015-10-21
 *      Author: ken
 */

#include "Client.h"

#include "Logger.h"

#include "SipClient.h"

Client::Client() {
	SipClient::getInstance()->attach(this);
}

Client::~Client() {
	SipClient::getInstance()->detach(this);
}

int Client::init(){
	const char* ip="14.146.226.97";
	short port=5060;
	const char* account="2026603";
	const char* password="123456";
	const char* realm="asterisk";
	log_debug("Client::init call Appclient->init");
	return SipClient::getInstance()->init(ip,port,account,password,realm);
}

void Client::destroy(){
	SipClient::getInstance()->destroy();
}

void Client::call(){
	const char* called="823";
	SipClient::getInstance()->call(called);
}

void Client::hangup(){
	SipClient::getInstance()->hangup();
}

void Client::onMsgStatus(int status){
	LOGI("Client::onStatus, recv msg, status=%d",status);
}
