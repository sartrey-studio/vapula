#pragma once

#include "tcm_base.h"

namespace tcm
{
	class Library;
	class Executor;

	//��������
	class TCM_BRIDGE_API Driver
	{
	public:
		Driver();
		virtual ~Driver();
	public:
		//��ȡ���л�����ʶ
		virtual PCSTR
			GetRuntimeId() = 0;

		//�������
		virtual Library*
			CreateLibrary() = 0;

		//����ִ����
		virtual Executor*
			CreateExecutor() = 0;
	};

	//������
	class TCM_BRIDGE_API DriverHub
	{
	private:
		DriverHub();
	public:
		~DriverHub();
	private:
		static DriverHub* _Instance;
	public:
		//��ȡ������ʵ��
		static DriverHub* GetInstance();
	private:
		vector<Driver*> _Drivers;
		vector<HMODULE> _Modules;
	private:
		int GetIndex(PCSTR id);
	public:
		//��������
		bool Link(PCSTR id);

		//�߳�����
		bool Kick(PCSTR id);

		//�߳���������
		void KickAll();
	public:
		//��ȡ����
		Driver* GetDriver(PCSTR id);

		//��ȡ�ѽӲ���������
		int GetCount();
	};
}