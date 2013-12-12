#pragma once

#include "vf_base.h"

namespace vapula
{
	class Envelope;
	class Invoker;
	class Driver;

	//���ܿ����
	class VAPULA_API Library
	{
	protected:
		Library();
	public:
		virtual ~Library();
	protected:
		cstrw _Dir; //��Ŀ¼
		cstrw _LibId; //���ʶ
	protected:
		static int _Count;
	public:
		//�������ü��ؿ�
		static Library* Load(cstrw path);
		
		//��ȡ��װ�ؿ�����
		static int GetCount();
	public:
		//��ȡ��ǰ���ʶ
		cstrw GetLibraryId();

		//����ָ�����ܵĲ����ŷ�
		Envelope* CreateEnvelope(int fid);

		//��ȡָ�����ܵĵ�����
		Invoker* CreateInvoker(int fid);
	public:
		//��ȡ������ʶ
		virtual cstr GetRuntimeId() = 0;

		//��ȡ�������չ��
		virtual cstrw GetBinExt() = 0;

		//װ�ؿ�
		virtual bool Mount();

		//ж�ؿ�
		virtual void Unmount();
	};
}