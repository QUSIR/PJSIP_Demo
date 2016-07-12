/*
 * Client.h
 *
 *  Created on: 2015-10-21
 *      Author: ken
 */

#pragma once

#include "Observer.h"

class Client : public Observer {
public:
	Client();
	~Client();

	int init();
	void destroy();
	void call();
	void hangup();
	virtual void onMsgStatus(int status);
};
