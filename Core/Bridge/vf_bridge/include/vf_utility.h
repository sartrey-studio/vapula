#pragma once
#pragma warning(disable:4275)

#include "vf_base.h"

namespace vapula
{
	//ͨ�����׵���Ϣ����ʾ��ֵ
	template<typename T>
	VAPULA_API void ShowMsgbox(T value)
	{
		ShowMsgbox(str::ValueTo(value), _vf_bridge);
	}

	//ͨ�����׵���Ϣ����ʾ�ַ���
	VAPULA_API void ShowMsgbox(cstr8 value, cstr8 caption = null);
	VAPULA_API void ShowMsgbox(cstr16 value, cstr16 caption = null);

	//��ȡ����ʱ����Ŀ¼
	VAPULA_API cstr8 GetRuntimeDir();

	//��ȡ��ǰӦ�ó���Ŀ¼
	VAPULA_API cstr8 GetAppDir();

	//��ȡ��ǰӦ�ó�������
	VAPULA_API cstr8 GetAppName();

	//��ȡ·���Ĺ淶Ŀ¼
	VAPULA_API cstr8 GetDirPath(cstr8 path, bool isfile = false);

	//����ָ���ļ��Ƿ����Զ��ķ�ʽ��
	VAPULA_API bool CanOpenRead(cstr8 file);
}