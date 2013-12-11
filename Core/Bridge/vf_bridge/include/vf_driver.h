#pragma once

#include "vf_base.h"

namespace vf
{
	class Library;
	class Invoker;

	//��������
	class TCM_BRIDGE_API Driver
	{
	public:
		Driver();
		virtual ~Driver();
	public:
		//��ȡ���л�����ʶ
		virtual str
			GetRuntimeId() = 0;

		//�������
		virtual Library*
			CreateLibrary() = 0;

		//����������
		virtual Invoker*
			CreateInvoker() = 0;
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
		vector<object> _Modules;
	private:
		int GetIndex(str id);
	public:
		//��������
		bool Link(str id);

		//�߳�����
		bool Kick(str id);

		//�߳���������
		void KickAll();
	public:
		//��ȡ����
		Driver* GetDriver(str id);

		//��ȡ�ѽӲ���������
		int GetCount();
	};
}