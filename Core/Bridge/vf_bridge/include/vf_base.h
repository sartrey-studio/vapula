#pragma once

#pragma warning(disable:4251) //����DLLģ�徯��

#include "vf_const.h"
#include "vf_string.h"

namespace vapula
{
	//��ȫ����Ŀ��
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

	//ת����ֵ��խ�ַ���
	template<typename T>
	VAPULA_API cstr ValueToStr(T value)
	{
		std::ostringstream oss;
		oss.imbue(std::locale("C"));
		oss<<value;
		return CopyStrA(oss.str().c_str());
	}

	//ת��Vector��������������
	template<typename T>
	VAPULA_API T* VectorToArray(vector<T>& src)
	{
		if(src.size() == 0)
			return null;
		T* dst = new T[src.size()];
		int i=0;
		for(vector<T>::iterator iter = src.begin(); iter != src.end(); iter++)
			dst[i++] = *iter;
		return dst;
	}

	//���ָ��VF���͵��ֽڳ���
	VAPULA_API int GetTypeUnit(int type);

	//���ɱ���Ψһ��ʶ�ַ���
	VAPULA_API cstr GetLuidA();
	VAPULA_API cstrw GetLuidW();

	//��ʾ���׵���Ϣ��ֵ����
	template<typename T>
	VAPULA_API void ShowMsgValue(T value, cstrw caption = null)
	{
		ShowMsgStr(MbToWc(ValueToStr(value)), caption);
	}

	//��ʾ���׵���Ϣ���ַ�������
	VAPULA_API void ShowMsgStr(cstr value, cstr caption = null);
	VAPULA_API void ShowMsgStr(cstrw value, cstrw caption = null);

	//��ȡ����ʱ����Ŀ¼
	VAPULA_API cstrw GetRuntimeDir();

	//��ȡ��ǰӦ�ó���Ŀ¼
	VAPULA_API cstrw GetAppDir();

	//��ȡ��ǰӦ�ó�������
	VAPULA_API cstrw GetAppName();

	//��ȡ·���Ĺ淶Ŀ¼
	VAPULA_API cstrw GetDirPath(cstrw path, bool isfile = false);

	//����ָ���ļ��Ƿ����Զ��ķ�ʽ��
	VAPULA_API bool CanOpenRead(cstrw file);
}