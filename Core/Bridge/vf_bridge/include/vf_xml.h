#pragma once

#include "vf_base.h"
#include <cstdarg>

namespace vapula
{
	//XML����ʵ�ú����� Ҫ������RapidXML
	namespace xml
	{
		//����XML
		//���ص��������������ڲ�ʹ��XML���ͷ��ڴ�
		VAPULA_API object Load(cstr8 path, cstr8& data);

		//����XML
		VAPULA_API object Parse(cstr8 xml);

		//������ַ���
		VAPULA_API cstr8 Print(object src);

		//ģ��XPath��ѯ����ڵ���ӽڵ�
		VAPULA_API object Path(object src, int count, ...);

		//��ȡ�ڵ��ֵ��8λ�ֽ��ַ���
		VAPULA_API cstr8 ValueCh8(object src);

		//��ȡ�ڵ��ֵ��16λ�ֽ��ַ���
		VAPULA_API cstr16 ValueCh16(object src);

		//��ȡ�ڵ��ֵ��ת������
		VAPULA_API int ValueInt(object src);

		//��ȡ�ڵ��ֵ��ת��ʵ��
		VAPULA_API double ValueReal(object src);

		//��ȡ�ڵ��ֵ��ƥ���ַ���
		VAPULA_API bool ValueBool(object src, cstr8 value);
	}
}