#pragma once

#pragma warning(disable:4251) //����DLLģ�徯��

#include "vf_const.h"
#include "vf_string.h"

namespace vf
{
	//��ȫ����Ŀ��
	template<typename T>
	TCM_BRIDGE_API void Clear(T target, bool isarr = false)
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
	TCM_BRIDGE_API str ValueToStr(T value)
	{
		std::ostringstream oss;
		oss.imbue(std::locale("C"));
		oss<<value;
		return CopyStrA(oss.str().c_str());
	}

	//ת��Vector��������������
	template<typename T>
	TCM_BRIDGE_API T* VectorToArray(vector<T>& src)
	{
		if(src.size() == 0)
			return null;
		T* dst = new T[src.size()];
		int i=0;
		for(vector<T>::iterator iter = src.begin(); iter != src.end(); iter++)
			dst[i++] = *iter;
		return dst;
	}

	//���ָ��TCM���͵��ֽڳ���
	TCM_BRIDGE_API int GetTypeUnit(int type);

	//���ɱ���Ψһ��ʶ�ַ���
	TCM_BRIDGE_API str GetLuidA();
	TCM_BRIDGE_API strw GetLuidW();

	//��ʾ���׵���Ϣ��ֵ����
	template<typename T>
	TCM_BRIDGE_API void ShowMsgValue(T value, strw caption = null)
	{
		ShowMsgStr(MbToWc(ValueToStr(value)), caption);
	}

	//��ʾ���׵���Ϣ���ַ�������
	TCM_BRIDGE_API void ShowMsgStr(str value, str caption = null);
	TCM_BRIDGE_API void ShowMsgStr(strw value, strw caption = null);

	//��ȡ����ʱ����Ŀ¼
	TCM_BRIDGE_API strw GetRuntimeDir();

	//��ȡ��ǰӦ�ó���Ŀ¼
	TCM_BRIDGE_API strw GetAppDir();

	//��ȡ��ǰӦ�ó�������
	TCM_BRIDGE_API strw GetAppName();

	//��ȡ·���Ĺ淶Ŀ¼
	TCM_BRIDGE_API strw GetDirPath(strw path, bool isfile = false);

	//����ָ���ļ��Ƿ����Զ��ķ�ʽ��
	TCM_BRIDGE_API bool CanOpenRead(strw file);
}