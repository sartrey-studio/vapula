#pragma once

#include "worker_null.h"
#include "worker_pipe.h"

//TCM Host����ע��ģʽ
enum CtrlInjectMode
{
	TCM_HOST_CJ_NULL = 0,
	TCM_HOST_CJ_PIPE = 1
};