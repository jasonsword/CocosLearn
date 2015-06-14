// LSLog.h

#ifndef LSLOG_H_
#define LSLOG_H_

#include "cocos2d.h"


/*
* Android log priority values, in ascending priority order.
*
* typedef enum android_LogPriority {
*	ANDROID_LOG_UNKNOWN = 0,
*	ANDROID_LOG_DEFAULT,    -- only for SetMinPriority() --
*	ANDROID_LOG_VERBOSE,
*	ANDROID_LOG_DEBUG,
*	ANDROID_LOG_INFO,
*	ANDROID_LOG_WARN,
*	ANDROID_LOG_ERROR,
*	ANDROID_LOG_FATAL,
*	ANDROID_LOG_SILENT,     -- only for SetMinPriority(); must be last --
* } android_LogPriority;
*/


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include <android/log.h>

#define LOG_TAG   "popstar"

#define LOG_VERBOSE(format, ...) __android_log_print(ANDROID_LOG_VERBOSE,  LOG_TAG, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) __android_log_print(ANDROID_LOG_DEBUG,  LOG_TAG, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) __android_log_print(ANDROID_LOG_WARN,  LOG_TAG, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) __android_log_print(ANDROID_LOG_ERROR,  LOG_TAG, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) __android_log_print(ANDROID_LOG_FATAL,  LOG_TAG, format, ##__VA_ARGS__)

#else

#define LOG_VERBOSE CCLOG
#define LOG_DEBUG CCLOG
#define LOG_INFO CCLOG
#define LOG_WARN CCLOG
#define LOG_ERROR CCLOG
#define LOG_FATAL CCLOG

#endif

#endif /* LSLOG_H_ */

