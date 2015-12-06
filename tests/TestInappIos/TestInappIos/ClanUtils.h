#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <memory>
#include "CClan.h"
#include "CMatchManager.h"

#ifndef WIN32
#define stricmp strcasecmp
#endif
#pragma warning(disable:4355)

using namespace CloudBuilder;
using namespace CotCHelpers;
using std::function;
using std::shared_ptr;

static CResultHandler *MakeResultHandler(function<void(eErrorCode, const CCloudResult*)> func) {
	struct FunctionalResultHandler: CResultHandler {
		function<void(eErrorCode, const CCloudResult*)> func;
		FunctionalResultHandler(function<void(eErrorCode, const CCloudResult*)> func) : func(func), CResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result) {
			func(code, result);
		}
	};
	return new FunctionalResultHandler(func);
}

static CMatchResultHandler *MakeMatchResultHandler(function<void(eErrorCode, const CCloudResult*, CMatch *)> func) {
	typedef function<void (eErrorCode, const CCloudResult*, CMatch *)> func_t;
	struct FunctionalResultHandler: CMatchResultHandler {
		func_t func;
		FunctionalResultHandler(func_t func) : func(func), CMatchResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result, CMatch *match) {
			func(code, result, match);
		}
	};
	return new FunctionalResultHandler(func);
}

static CMatchEventListener *MakeMatchEventListener(function<void (const CCloudResult*)> func) {
	typedef function<void (const CCloudResult*)> func_t;
	struct EventListener: CMatchEventListener {
		func_t func;
		EventListener(func_t func) : func(func) {}
		virtual void onMatchEventReceived(const CCloudResult *event) {
			func(event);
		}
	};
	return new EventListener(func);
}

template<class T>
autoref<T> mkref(T *detachedRef) {
	return autoref<T>(detachedRef, false);
}

// Allows to create an object that is directly attached (only referenced by the returning autoref)
struct __MkrefHelper {
	template<class T>
	autoref<T> operator * (T *detachedRef) {
		return Autorelease(detachedRef);
	}
};
#define newref __MkrefHelper() * new 
#define thisref mkref(this)

template <class T, size_t S> size_t numberof(T (&dest)[S]) { return S; }

static bool IsEqual(const char *str1, const char *str2) {
	return str1 == str2 || (str1 && str2 && !strcmp(str1, str2));
}
