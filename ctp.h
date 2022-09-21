#pragma once

#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4100 )
#include "ctp/api_v6.6.8_win32/ThostFtdcMdApi.h"
#include "ctp/api_v6.6.8_win32/ThostFtdcTraderApi.h"
#include "ctp/api_v6.6.8_win32/ThostFtdcUserApiDataType.h"
#include "ctp/api_v6.6.8_win32/ThostFtdcUserApiStruct.h"
#pragma warning( pop )
#pragma comment(lib, "ctp/api_v6.6.8_win32/thostmduserapi_se.lib")
#pragma comment(lib, "ctp/api_v6.6.8_win32/thosttraderapi_se.lib")
#endif

#ifdef _WIN64
#pragma warning( push )
#pragma warning( disable : 4100 )
#include "ctp/api_v6.6.8_win64/ThostFtdcMdApi.h"
#include "ctp/api_v6.6.8_win64/ThostFtdcTraderApi.h"
#include "ctp/api_v6.6.8_win64/ThostFtdcUserApiDataType.h"
#include "ctp/api_v6.6.8_win64/ThostFtdcUserApiStruct.h"
#pragma warning( pop )
#pragma comment(lib, "ctp/api_v6.6.8_win64/thostmduserapi_se.lib")
#pragma comment(lib, "ctp/api_v6.6.8_win64/thosttraderapi_se.lib")
#endif

#ifdef __APPLE__
#include "ctp/api_v6.6.7_mac/include/ThostFtdcMdApi.h"
#include "ctp/api_v6.6.7_mac/include/ThostFtdcTraderApi.h"
#include "ctp/api_v6.6.7_mac/include/ThostFtdcUserApiDataType.h"
#include "ctp/api_v6.6.7_mac/include/ThostFtdcUserApiStruct.h"
#endif