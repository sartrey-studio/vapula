#pragma once

#pragma warning(disable:4251)

#include "vf_const.h"
#include "vf_string.h"

namespace vapula
{
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

	//ת��Vector��������������
	template<typename T>
	VAPULA_API T* VectorToArray(vector<T>& src)
	{
		if(src.size() == 0)
			return null;
		T* dst = new T[src.size()];
		uint32 i=0;
		for(vector<T>::iterator iter = src.begin(); iter != src.end(); iter++)
			dst[i++] = *iter;
		return dst;
	}

	//���ָ��VF���͵��ֽڳ���
	VAPULA_API int GetTypeUnit(int type);

	//���ɱ���Ψһ��ʶ�ַ���
	VAPULA_API cstr8 GetLuid();

	//ͨ�����׵���Ϣ����ʾ��ֵ
	template<typename T>
	VAPULA_API void ShowMsgbox(T value)
	{
		ShowMsgStr(str::ValueTo(value), _vf_bridge);
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