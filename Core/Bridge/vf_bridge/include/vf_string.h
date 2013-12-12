#pragma once

#include "vf_const.h"

namespace vapula
{
	//ת��ָ������ĵ��ֽ��ַ��������ֽ��ַ���
	//Դ����Ĭ��ϵͳ���룬Ŀ�����ΪUTF16
	VAPULA_API cstrw MbToWc(cstr src, cstr code = null);

	//ת�����ֽ��ַ�����ָ�����뵥�ֽ��ַ���
	//Դ����ΪUTF16��Ŀ�����Ĭ��ϵͳ����
	VAPULA_API cstr WcToMb(cstrw src, cstr code = null);

	//�����ַ��������ظ����ַ�����ַ
	VAPULA_API cstr CopyStrA(cstr src);
	VAPULA_API cstrw CopyStrW(cstrw src);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	VAPULA_API cstr ReplaceStrA(cstr src, cstr from, cstr to);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	VAPULA_API cstrw ReplaceStrW(cstrw src, cstrw from, cstrw to);
}