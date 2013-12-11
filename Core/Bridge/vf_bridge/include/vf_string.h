#pragma once

#include "vf_const.h"

namespace vf
{
	//ת��ָ������ĵ��ֽ��ַ��������ֽ��ַ���
	//Դ����Ĭ��ϵͳ���룬Ŀ�����ΪUTF16
	TCM_BRIDGE_API strw MbToWc(str src, str code = null);

	//ת�����ֽ��ַ�����ָ�����뵥�ֽ��ַ���
	//Դ����ΪUTF16��Ŀ�����Ĭ��ϵͳ����
	TCM_BRIDGE_API str WcToMb(strw src, str code = null);

	//�����ַ��������ظ����ַ�����ַ
	TCM_BRIDGE_API str CopyStrA(str src);
	TCM_BRIDGE_API strw CopyStrW(strw src);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	TCM_BRIDGE_API str ReplaceStrA(str src, str from, str to);

	//���������ֽ��ַ���������ָ���Ӵ��滻ΪĿ��
	TCM_BRIDGE_API strw ReplaceStrW(strw src, strw from, strw to);
}