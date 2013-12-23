#pragma once

#pragma warning(disable:4251)

#include "vf_const.h"
#include "vf_string.h"

namespace vapula
{
	//��ȡ���͵ĵ�λ����
	VAPULA_API uint32 GetTypeUnit(int8 type);

	//����ָ��Ŀ��
	template<typename T>
	VAPULA_API void Clear(T target, bool isarr = false)
	{
		if(target != null)
		{
			if(isarr) delete [] target;
			else delete target;
			target = null;
		}
	}

	//���ɱ���Ψһ��ʶ�ַ���
	VAPULA_API cstr8 GetLuid();

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