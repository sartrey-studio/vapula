#pragma once

#include "vf_base.h"
#include "vf_library.h"
#include "vf_invoker.h"

#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;
using namespace vapula;
using std::ostringstream;

//宿主控制注入模式
enum CtrlInjectMode
{
	VF_HOST_CJ_NULL = 0,
	VF_HOST_CJ_PIPE = 1
};

//宿主返回值
enum HostReturnCode
{
	VF_HOST_RETURN_NORMAL = 0,
	VF_HOST_RETURN_INVALIDCMD = 1,
	VF_HOST_RETURN_INVALIDTASK = 2,
	VF_HOST_RETURN_FAILEXEC = 3
};

cstr8 const _vf_host = "Vapula Host";
cstr8 const _vf_host_err_0 = "invalid invoke";