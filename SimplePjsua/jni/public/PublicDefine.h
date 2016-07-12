#pragma once

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <unistd.h>

	#define MUTEX_TYPE CRITICAL_SECTION
	#define MUTEX_INIT(mutex) InitializeCriticalSection(mutex)
	#define MUTEX_DESTROY DeleteCriticalSection
	#define MUTEX_LOCK EnterCriticalSection
	#define MUTEX_UNLOCK LeaveCriticalSection
	#define THREAD_ID DWORD
	#define CREATE_THREAD(id,thread,argv) (CreateThread(NULL,0,thread,argv,0,id)!=0)
	#define THREAD_TYPE DWORD WINAPI
	#define GET_PROGRAM_PATH_NAME(path) GetModuleFileName(NULL,path,sizeof(path))
	#define PATH_SEPARATOR '\\'
	#define CLOSESOCKET closesocket
	#define GET_ERROR_CODE WSAGetLastError()
	#define SLEEP(n) Sleep(n*1000)
#else

	#include <cstdio>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <errno.h>
	#include <pthread.h>

	#define MUTEX_TYPE pthread_mutex_t
	#define MUTEX_INIT(mutex) pthread_mutex_init(mutex,NULL)
	#define MUTEX_DESTROY pthread_mutex_destroy
	#define MUTEX_LOCK pthread_mutex_lock
	#define MUTEX_UNLOCK pthread_mutex_unlock
	#define THREAD_ID pthread_t
	#define CREATE_THREAD(id,thread,argv) (pthread_create(id,NULL,thread,argv)==0)
	#define THREAD_TYPE void*
	#define GET_PROGRAM_PATH_NAME(path) readlink("/proc/self/exe",path,sizeof(path))
	#define PATH_SEPARATOR '/'
	#define CLOSESOCKET(sockfd) close(sockfd)
	#define GET_ERROR_CODE errno
	#define SLEEP(n) sleep(n)
#endif

#ifdef _SYSTEM64
	#define LONG int
	#define LONGLONG long
#else
	#define LONG long
	#define LONGLONG long long
#endif
