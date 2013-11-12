#pragma once

#include "tcm_base.h"

namespace tcm
{
	class Envelope;
	class Invoker;
	class Driver;

	//���ܿ����
	class TCM_BRIDGE_API Library
	{
	protected:
		Library();
	public:
		virtual ~Library();
	protected:
		strw _Dir; //��Ŀ¼
		strw _LibId; //���ʶ
	protected:
		static int _Count;
	public:
		//�������ü��ؿ�
		static Library* Load(strw path);
		
		//��ȡ��װ�ؿ�����
		static int GetCount();
	public:
		//��ȡ��ǰ���ʶ
		strw GetLibraryId();

		//����ָ�����ܵĲ����ŷ�
		Envelope* CreateEnvelope(int fid);

		//��ȡָ�����ܵĵ�����
		Invoker* CreateInvoker(int fid);
	public:
		//��ȡ������ʶ
		virtual str GetRuntimeId() = 0;

		//��ȡ�������չ��
		virtual strw GetBinExt() = 0;

		//װ�ؿ�
		virtual bool Mount();

		//ж�ؿ�
		virtual void Unmount();
	};
}