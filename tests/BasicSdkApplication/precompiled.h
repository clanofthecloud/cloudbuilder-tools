#pragma once

#include <SDKDDKVer.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <memory>
using std::shared_ptr;
using std::unique_ptr;

#define MAKE_UNIQUE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4)   \
	template<class T COMMA LIST(_CLASS_TYPE)>  \
	inline std::unique_ptr<T> unique_new(LIST(_TYPE_REFREF_ARG))  \
{  \
	return std::move(std::unique_ptr<T>(new T(LIST(_FORWARD_ARG))));  \
}
//_VARIADIC_EXPAND_0X(MAKE_UNIQUE, , , , )
#undef MAKE_UNIQUE
