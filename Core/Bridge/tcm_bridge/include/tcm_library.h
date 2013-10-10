#pragma once

#include "tcm_base.h"

namespace tcm
{
	class Envelope;
	class Executor;
	class Driver;

	//���ܿ����
	class TCM_BRIDGE_API Library
	{
	protected:
		Library();
	public:
		virtual ~Library();
	protected:
		PCWSTR _Dir; //��Ŀ¼
		PCWSTR _LibId; //���ʶ
	protected:
		static int _Count;
	public:
		//�������ü��ؿ�
		static Library* Load(PCWSTR path);
		
		//��ȡ��װ�ؿ�����
		static int GetCount();
	public:
		//��ȡ��ǰ���ʶ
		PCWSTR GetLibraryId();

		//����ָ�����ܵĲ����ŷ�
		Envelope* CreateEnvelope(int fid);

		//��ȡָ�����ܵ�ִ����
		Executor* CreateExecutor(int fid);
	public:
		//��ȡ������ʶ
		virtual PCSTR GetRuntimeId() = 0;

		//��ȡ�������չ��
		virtual PCWSTR GetBinExt() = 0;

		//װ�ؿ�
		virtual bool Mount();

		//ж�ؿ�
		virtual void Unmount();
	};
}