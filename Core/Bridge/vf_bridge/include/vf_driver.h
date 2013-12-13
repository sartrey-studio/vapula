#pragma once

#include "vf_base.h"

namespace vapula
{
	class Library;
	class Invoker;

	//��������
	class VAPULA_API Driver
	{
	public:
		Driver();
		virtual ~Driver();
	public:
		//��ȡ���л�����ʶ
		virtual cstr8
			GetRuntimeId() = 0;

		//�������
		virtual Library*
			CreateLibrary() = 0;

		//����������
		virtual Invoker*
			CreateInvoker() = 0;
	};

	//������
	class VAPULA_API DriverHub
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
		int GetIndex(cstr8 id);
	public:
		//��������
		bool Link(cstr8 id);

		//�߳�����
		bool Kick(cstr8 id);

		//�߳���������
		void KickAll();
	public:
		//��ȡ����
		Driver* GetDriver(cstr8 id);

		//��ȡ�ѽӲ���������
		int GetCount();
	};
}