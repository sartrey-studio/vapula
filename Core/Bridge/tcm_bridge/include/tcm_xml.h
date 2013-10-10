#pragma once

#include "tcm_base.h"
#include <cstdarg>

namespace tcm
{
	//TCM XML����ʵ�ú����� Ҫ������RapidXML
	namespace xml
	{
		//����XML
		//���ص��������������ڲ�ʹ��XML���ͷ��ڴ�
		TCM_BRIDGE_API LPVOID Load(PCWSTR path, PCSTR& data);

		//����XML
		TCM_BRIDGE_API LPVOID Parse(PCSTR xml);

		//������ַ���
		TCM_BRIDGE_API PCSTR Print(LPVOID src);

		//ģ��XPath��ѯ����ڵ���ӽڵ�
		TCM_BRIDGE_API LPVOID Path(LPVOID src, int count, ...);

		//��ȡ�ڵ��ֵ�Ķ��ֽ��ַ���
		TCM_BRIDGE_API PCSTR ValueA(LPVOID src);

		//��ȡ�ڵ��ֵ�Ŀ��ֽ��ַ���
		TCM_BRIDGE_API PCWSTR ValueW(LPVOID src);

		//��ȡ�ڵ��ֵ��ת������
		TCM_BRIDGE_API int ValueInt(LPVOID src);

		//��ȡ�ڵ��ֵ��ת��ʵ��
		TCM_BRIDGE_API double ValueReal(LPVOID src);

		//��ȡ�ڵ��ֵ��ƥ���ַ���
		TCM_BRIDGE_API bool ValueBool(LPVOID src, PCSTR value);
	}
}