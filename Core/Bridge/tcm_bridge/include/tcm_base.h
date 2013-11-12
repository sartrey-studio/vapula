#pragma once

#pragma warning(disable:4251) //����DLLģ�徯��

#ifdef TCM_BRIDGE_EXPORTS
#define TCM_BRIDGE_API __declspec(dllexport)
#else
#define TCM_BRIDGE_API
#endif

#include "tcm_const.h"

namespace tcm
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

	//���ָ��TCM���͵��ֽڳ���
	TCM_BRIDGE_API int GetTypeUnit(int type);

	//ת�����ֽڵ����ֽ�
	//ת�������ֽ�Ĭ��ʹ��UTF8����
	TCM_BRIDGE_API strw MbToWc(str src, uint32 cp = 65001);

	//ת�����ֽڵ����ֽ�
	//ת�������ֽ�Ĭ��ʹ��UTF8����
	TCM_BRIDGE_API str WcToMb(strw src, uint32 cp = 65001);

	//��������
	//�����ֽھ���ָ���м����ת����ָ�����ձ���
	TCM_BRIDGE_API str FixEncoding(str src, uint32 cp_by = 65001, uint32 cp_to = 1);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	TCM_BRIDGE_API str ReplaceStrA(str src, str from, str to);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	TCM_BRIDGE_API strw ReplaceStrW(strw src, strw from, strw to);

	//�����ַ��������ظ����ַ�����ַ
	TCM_BRIDGE_API str CopyStrA(str src);
	TCM_BRIDGE_API strw CopyStrW(strw src);

	//ת����ֵ�����ֽ��ַ���
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
	
	//����һ�����HEX�ַ���
	TCM_BRIDGE_API str GetRandomHexA(int len);
	TCM_BRIDGE_API strw GetRandomHexW(int len);

	//����ʱ���ַ���
	TCM_BRIDGE_API str GetTimeStrA();
	TCM_BRIDGE_API strw GetTimeStrW();

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