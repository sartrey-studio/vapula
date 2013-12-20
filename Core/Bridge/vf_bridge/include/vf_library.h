#pragma once

#include "vf_base.h"

namespace vapula
{
	class Envelope;
	class Invoker;
	class Driver;

	//�������
	class VAPULA_API Library
	{
	protected:
		Library();
	public:
		virtual ~Library();
	protected:
		cstr8 _LibId; //�����ʶ
		cstr8 _EntryDpt; //����������
		cstr8 _FuncDpt; //�����������
	protected:
		static int _Count;
	public:
		//����ָ�����
		static Library* Load(cstr8 path);
		
		//��ȡ��װ�ؿ�����
		static int GetCount();
	public:
		//��ȡ��ǰ���ʶ
		cstr8 GetLibraryId();

		//����ָ�����ܵĲ����ŷ�
		Envelope* CreateEnvelope(int fid);

		//��ȡָ�����ܵĵ�����
		Invoker* CreateInvoker(int fid);
	public:
		//��ȡ������ʶ
		virtual cstr8 GetRuntimeId() = 0;

		//��ȡ�������չ��
		//��"."��ʼ
		virtual cstr8 GetBinExt() = 0;

		//װ�ؿ�
		virtual bool Mount();

		//ж�ؿ�
		virtual void Unmount();
	};
}