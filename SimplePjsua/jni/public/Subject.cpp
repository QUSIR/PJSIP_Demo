#include "subject.h"

#include <algorithm>

Subject::Subject(){
}

Subject::~Subject(){
}

void Subject::attach(Observer* pObserver){
	list<Observer*>::iterator iter;
	iter = std::find(m_lst.begin(),m_lst.end(),pObserver);
	if(iter == m_lst.end()){
		this->m_lst.push_back(pObserver);
	}
}

void Subject::detach(Observer* pObserver){
	list<Observer*>::iterator iter;
	iter = std::find(m_lst.begin(),m_lst.end(),pObserver);
	if(iter != m_lst.end()){
		this->m_lst.erase(iter);
	}
}

void Subject::msgStatus(int status){
	list<Observer*>::iterator iter = this->m_lst.begin();
	for(;iter != m_lst.end();iter++){
		(*iter)->onMsgStatus(status);
	}
}

