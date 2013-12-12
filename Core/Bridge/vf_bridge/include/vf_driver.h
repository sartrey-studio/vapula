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
		virtual cstr
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
		int GetIndex(cstr id);
	public:
		//��������
		bool Link(cstr id);

		//�߳�����
		bool Kick(cstr id);

		//�߳���������
		void KickAll();
	public:
		//��ȡ����
		Driver* GetDriver(cstr id);

		//��ȡ�ѽӲ���������
		int GetCount();
	};
}