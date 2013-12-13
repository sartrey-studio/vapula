#pragma once

#include "vf_const.h"

namespace vapula
{
	namespace str
	{
		//ת����ֵ���ַ���
		template<typename T>
		VAPULA_API cstr8 ValueTo(T value)
		{
			std::ostringstream oss;
			oss.imbue(std::locale("C"));
			oss<<value;
			return Copy(oss.str().c_str());
		}

		//ת��16λ�ֽ��ַ�����ָ������8λ�ֽ��ַ���
		//Դ����ΪUTF16��Ŀ�����Ĭ��ϵͳ����
		VAPULA_API cstr8 ToCh8(cstr16 src, cstr8 cp = null);

		//ת��ָ�������8λ�ֽ��ַ�����16λ�ֽ��ַ���
		//Դ����Ĭ��Ϊϵͳ���룬Ŀ�����ΪUTF16
		VAPULA_API cstr16 ToCh16(cstr8 src, cstr8 cp = null);

		//ת��ָ�������8λ�ֽ��ַ�������һָ������
		VAPULA_API cstr8 EncodeCh8(cstr8 src, cstr8 cp_from, cstr8 cp_to);

		//�����ַ��������ظ����ַ�����ַ
		VAPULA_API cstr8 Copy(cstr8 src);
		VAPULA_API cstr16 Copy(cstr16 src);

		//�������ַ���������ָ���Ӵ��滻ΪĿ��
		VAPULA_API cstr8 Replace(cstr8 src, cstr8 from, cstr8 to);
		VAPULA_API cstr16 Replace(cstr16 src, cstr16 from, cstr16 to);
	}
}