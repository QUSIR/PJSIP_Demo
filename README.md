# PJSIP_Demo
## android使用开发环境是eclipse 
工程目录是SimplePjsua
## PJSIP支持ALSA OOS音频驱动

## PJSIP总体介绍 ##

PJSIP是SIP协议的实现，其架构很不错，功能很丰富。

PJSIP主要包含以下几个部分/层次/架构：

`PJSIP`：Open Source SIP Stack，开源的SIP协议栈。

`PJMEDIA`：Open Source Media Stack，开源的媒体栈。

`PJNATH`：Open Source NAT Traversal Helper Library，开源的NAT-T辅助库。

`PJLIB-UTIL`：Auxiliary Library，辅助工具库。

`PJLIB`：Ultra Portable Base Framework Library，基础框架库。

# NDK编译PJSIP #
## 编译环境 ##
Ubuntu-14.04-LTS-i386

PJSIP-2.4.5

android-ndk-r10e

## 经验和教训 ##

简而言之就是以下几句话：

别用Windows编译

别用Ubuntu 64位，使用32位，包括ndk

别用ndk版本号高于r10，使用r9以下版本
## 编译安装 ##
1、修改pjsip的编译配置pjlib\include\pj\config_site.h，写入以下内容

	#define PJ_CONFIG_ANDROID 1
	#include <pj/config_site_sample.h>


2、如果要编译pjsip的静态库和测试执行程序，进入pjsip的根目录，设置ndk路径，编译
	
	$ export ANDROID_NDK_ROOT=/home/android-ndk-r8e/
	$ ./configure-android
	$ make dep && make clean && make