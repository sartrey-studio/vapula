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
		TCM_BRIDGE_API object Load(strw path, str& data);

		//����XML
		TCM_BRIDGE_API object Parse(str xml);

		//������ַ���
		TCM_BRIDGE_API str Print(object src);

		//ģ��XPath��ѯ����ڵ���ӽڵ�
		TCM_BRIDGE_API object Path(object src, int count, ...);

		//��ȡ�ڵ��ֵ�Ķ��ֽ��ַ���
		TCM_BRIDGE_API str ValueA(object src);

		//��ȡ�ڵ��ֵ�Ŀ��ֽ��ַ���
		TCM_BRIDGE_API strw ValueW(object src);

		//��ȡ�ڵ��ֵ��ת������
		TCM_BRIDGE_API int ValueInt(object src);

		//��ȡ�ڵ��ֵ��ת��ʵ��
		TCM_BRIDGE_API double ValueReal(object src);

		//��ȡ�ڵ��ֵ��ƥ���ַ���
		TCM_BRIDGE_API bool ValueBool(object src, str value);
	}
}