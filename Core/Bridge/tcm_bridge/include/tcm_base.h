#pragma once

#pragma warning(disable:4251) //����DLLģ�徯��

#ifdef TCM_BRIDGE_EXPORTS
#define TCM_BRIDGE_API __declspec(dllexport)
#else
#define TCM_BRIDGE_API
#endif

#include <windows.h>
#include <sstream>
#include <vector>

namespace tcm
{
	using std::vector;

	//TCM֧�ֵ���������
	enum DataType
	{
		TCM_DATA_POINTER = 0,
		TCM_DATA_INT8 = 1,
		TCM_DATA_INT16 = 2,
		TCM_DATA_INT32 = 3,
		TCM_DATA_INT64 = 4,
		TCM_DATA_UINT8 = 5,
		TCM_DATA_UINT16 = 6,
		TCM_DATA_UINT32 = 7,
		TCM_DATA_UINT64 = 8,
		TCM_DATA_REAL32 = 10,
		TCM_DATA_REAL64 = 11,
		TCM_DATA_BOOL = 20,
		TCM_DATA_CSTRA = 21,
		TCM_DATA_CSTRW = 22
	};

	//TCM֧�ֵ�����״̬
	enum State
	{
		TCM_STATE_IDLE = 0,
		TCM_STATE_BUSY = 1,
		TCM_STATE_PAUSE = 2
	};

	//TCM֧�ֵĿ�����
	enum CtrlCode
	{
		TCM_CTRL_NULL = 0,
		TCM_CTRL_PAUSE = 1,
		TCM_CTRL_RESUME = 2,
		TCM_CTRL_CANCEL = 3,
		TCM_CTRL_RESTART = 4
	};

	//TCMԤ�õķ���ֵ
	enum ReturnCode
	{
		TCM_RETURN_ERROR = 0,
		TCM_RETURN_NORMAL = 1,
		TCM_RETURN_CANCELBYMSG = 2,
		TCM_RETURN_CANCELBYFORCE = 3,
		TCM_RETURN_NULLENTRY = 4,
		TCM_RETURN_NULLTASK = 5,
	};

	//��ȫ����Ŀ��
	template<typename T>
	TCM_BRIDGE_API void Clear(T target, bool isarr = false)
	{
		if(target != NULL)
		{
			if(isarr) delete [] target;
			else delete target;
			target = NULL;
		}
	}

	//���ָ��TCM���͵��ֽڳ���
	TCM_BRIDGE_API int GetTypeUnit(int type);

	//ת�����ֽڵ����ֽ�
	//ת�������ֽ�Ĭ��ʹ��UTF8����
	TCM_BRIDGE_API PCWSTR MbToWc(PCSTR src, UINT cp = CP_UTF8);

	//ת�����ֽڵ����ֽ�
	//ת�������ֽ�Ĭ��ʹ��UTF8����
	TCM_BRIDGE_API PCSTR WcToMb(PCWSTR src, UINT cp = CP_UTF8);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	TCM_BRIDGE_API PCSTR ReplaceStrA(PCSTR src, PCSTR from, PCSTR to);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	TCM_BRIDGE_API PCWSTR ReplaceStrW(PCWSTR src, PCWSTR from, PCWSTR to);

	//��������
	//�����ֽھ���ָ���м����ת����ָ�����ձ���
	TCM_BRIDGE_API PCSTR FixEncoding(PCSTR src, UINT cpMid = CP_UTF8, UINT cpAim = CP_OEMCP);

	//�����ַ��������ظ����ַ�����ַ
	TCM_BRIDGE_API PCSTR  CopyStrA(PCSTR src);
	TCM_BRIDGE_API PCWSTR CopyStrW(PCWSTR src);

	//ת����ֵ�����ֽ��ַ���
	template<typename T>
	TCM_BRIDGE_API PCSTR ValueToStrA(T value)
	{
		std::ostringstream oss;
		oss.imbue(std::locale("C"));
		oss<<value;
		return CopyStrA(oss.str().c_str());
	}

	//ת����ֵ�����ֽ��ַ���
	template<typename T>
	TCM_BRIDGE_API PCWSTR ValueToStrW(T value)
	{
		std::ostringstream oss;
		oss.imbue(std::locale("C"));
		oss<<value;
		return MbToWc(oss.str().c_str());
	}

	//ת��Vector��������������
	template<typename T>
	TCM_BRIDGE_API T* VectorToArray(vector<T>& src)
	{
		if(src.size() == 0) return NULL;
		T* dst = new T[src.size()];
		int i=0;
		for(vector<T>::iterator iter=src.begin();iter!=src.end();iter++) dst[i++] = *iter;
		return dst;
	}
	
	//����һ�����HEX�ַ���
	TCM_BRIDGE_API PCSTR GetRandomHexA(int len);
	TCM_BRIDGE_API PCWSTR GetRandomHexW(int len);

	//����ʱ���ַ���
	TCM_BRIDGE_API PCSTR GetTimeStrA();
	TCM_BRIDGE_API PCWSTR GetTimeStrW();

	//��ʾ���׵���Ϣ��
	TCM_BRIDGE_API void ShowMsgbox(PCWSTR value = NULL, PCWSTR caption = NULL);
	TCM_BRIDGE_API void ShowMsgbox(PCSTR value = NULL, PCSTR caption = NULL);

	template<typename T>
	TCM_BRIDGE_API void ShowMsgbox(T value, PCWSTR caption = NULL)
	{
		ShowMsgbox(ValueToStrW(value), caption);
	}

	//��ȡ����ʱ����Ŀ¼
	TCM_BRIDGE_API PCWSTR GetRuntimeDir();

	//��ȡ��ǰӦ�ó���Ŀ¼
	//NEED REWRITE
	TCM_BRIDGE_API PCWSTR GetAppDir();

	//��ȡ��ǰӦ�ó�������
	//NEED REWRITE
	TCM_BRIDGE_API PCWSTR GetAppName();

	//��ȡ·���Ĺ淶Ŀ¼
	TCM_BRIDGE_API PCWSTR GetDirPath(PCWSTR path, bool isfile = false);

	//����ָ���ļ��Ƿ����Զ��ķ�ʽ��
	TCM_BRIDGE_API bool CanOpenRead(PCWSTR file);
}