#pragma once

#include "vf_base.h"
#include <cstdarg>

namespace vapula
{
	//TCM XML����ʵ�ú����� Ҫ������RapidXML
	namespace xml
	{
		//����XML
		//���ص��������������ڲ�ʹ��XML���ͷ��ڴ�
		VAPULA_API object Load(cstrw path, cstr& data);

		//����XML
		VAPULA_API object Parse(cstr xml);

		//������ַ���
		VAPULA_API cstr Print(object src);

		//ģ��XPath��ѯ����ڵ���ӽڵ�
		VAPULA_API object Path(object src, int count, ...);

		//��ȡ�ڵ��ֵ�Ķ��ֽ��ַ���
		VAPULA_API cstr ValueA(object src);

		//��ȡ�ڵ��ֵ�Ŀ��ֽ��ַ���
		VAPULA_API cstrw ValueW(object src);

		//��ȡ�ڵ��ֵ��ת������
		VAPULA_API int ValueInt(object src);

		//��ȡ�ڵ��ֵ��ת��ʵ��
		VAPULA_API double ValueReal(object src);

		//��ȡ�ڵ��ֵ��ƥ���ַ���
		VAPULA_API bool ValueBool(object src, cstr value);
	}
}