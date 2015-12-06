#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include "CClan.h"
#include "CNotificationManager.h"
#include "CUserManager.h"
using CloudBuilder::eErrorCode;
using CotCHelpers::CHJSON;

#define LOGV(TAG,...) __android_log_print(ANDROID_LOG_VERBOSE, TAG,__VA_ARGS__)
#define LOGD(TAG,...) __android_log_print(ANDROID_LOG_DEBUG  , TAG,__VA_ARGS__)
#define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO   , TAG,__VA_ARGS__)
#define LOGW(TAG,...) __android_log_print(ANDROID_LOG_WARN   , TAG,__VA_ARGS__)
#define LOGE(TAG,...) __android_log_print(ANDROID_LOG_ERROR  , TAG,__VA_ARGS__)

extern "C" {
	JNIEXPORT void JNICALL Java_com_cotc_sdktestandroidapplication_Engine_startup(JNIEnv * env, jclass cls);
	JNIEXPORT void JNICALL Java_com_cotc_sdktestandroidapplication_Engine_update(JNIEnv * env, jclass cls);
}

class MyNotificationManager: public CloudBuilder::CNotificationManager {
public:
	MyNotificationManager() : CNotificationManager(true) {}
	~MyNotificationManager() { LOGV("MyNotificationManager", "Finished\n"); }

	virtual void didRegisterDevice(eErrorCode error) {
		LOGV("MyNotificationManager", "Registered device\n");
	}
};

class MyUserManager: public CloudBuilder::CUserManager {
	virtual void didRegisterAndLogin(eErrorCode aError) {
	}

	virtual void didLogin(eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile) {
		LOGV("MyUserManager", "Did login!");
	}

	virtual void didLogout(eErrorCode aError) {
	}
};

class MyClan: public CloudBuilder::CClan {
	MyUserManager *userManager;

public:
	MyClan() : CClan(new MyNotificationManager) {
		userManager = new MyUserManager;
	}
	~MyClan() {
		delete userManager;
	}
	MyUserManager *getUserManager() {
		return userManager;
	}

	virtual void didFinishSetup(eErrorCode aError) {
		LOGV("MyClan", "Finished setup");
	}
};

MyClan *myClan;

JNIEXPORT void JNICALL Java_com_cotc_sdktestandroidapplication_Engine_startup(JNIEnv * env, jclass cls) {
	LOGV("Engine", "Hello!");
	fflush(stdout);
	myClan = new MyClan;
	CHJSON json;

	json.Put("key", "cloudbuilder-key");
	json.Put("secret", "azerty");
	json.Put("env", "https://sandbox-api01.clanofthecloud.mobi");
	json.Put("appVersion", "1.0");
	myClan->Setup(&json);
}

JNIEXPORT void JNICALL Java_com_cotc_sdktestandroidapplication_Engine_update(JNIEnv * env, jclass cls) {
	CloudBuilder::CNotificationManager::popNextCallback();
}

JNIEXPORT void JNICALL Java_com_cotc_sdktestandroidapplication_Engine_terminate(JNIEnv * env, jclass cls) {
	delete myClan;
}

