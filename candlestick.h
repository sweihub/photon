#pragma once

#include <stdio.h>
#ifdef _MSC_VER
#include <Windows.h>
#endif

template <typename... T>
void debug(const char * fmt, T& ...args) {
#ifdef _MSC_VER	
	char buf[512] = {};
	snprintf(buf, sizeof(buf) - 1, fmt, args...);
	OutputDebugString(buf);
#else
	fprintf(stderr, fmt, args...);
#endif
}

void ShowCandlestick();