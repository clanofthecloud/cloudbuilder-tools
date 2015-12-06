#pragma once

#include <functional>
#include "CClan.h"

static CloudBuilder::CResultHandler *MakeResultHandler(std::function<void(CloudBuilder::eErrorCode, const CloudBuilder::CCloudResult*)> func) {
	using CloudBuilder::eErrorCode;
	using CloudBuilder::CCloudResult;
	using CloudBuilder::CResultHandler;
	struct FunctionalResultHandler: CResultHandler {
		std::function<void(eErrorCode, const CCloudResult*)> func;
		FunctionalResultHandler(std::function<void(eErrorCode, const CCloudResult*)> func) : func(func), CResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result) {
			func(code, result);
		}
	};
	return new FunctionalResultHandler(func);
}

static CloudBuilder::CMatchResultHandler *MakeMatchResultHandler(std::function<void(CloudBuilder::eErrorCode, const CloudBuilder::CCloudResult*, CloudBuilder::CMatch *)> func) {
	using namespace CloudBuilder;
	typedef std::function<void (eErrorCode, const CCloudResult*, CMatch *)> func_t;
	struct FunctionalResultHandler: CMatchResultHandler {
		func_t func;
		FunctionalResultHandler(func_t func) : func(func), CMatchResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result, CMatch *match) {
			func(code, result, match);
		}
	};
	return new FunctionalResultHandler(func);
}

