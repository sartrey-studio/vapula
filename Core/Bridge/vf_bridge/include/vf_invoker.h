#pragma once

#include "vf_context.h"
#include "vf_envelope.h"

namespace vf
{
	class Token;
	class Library;

	//���ܵ�����
	class TCM_BRIDGE_API Invoker
	{
	protected:
		Invoker();
	public:
		virtual ~Invoker();
	protected:
		int _FuncId;
		Envelope* _Envelope;
		Context* _Context;
		Token* _ContextToken;
	protected:
		object _Thread;
		bool _IsSuspend;
		virtual uint32 WINAPI _ThreadProc();
	public:
		//��ȡ���ܱ�ʶ
		int GetFunctionId();

		//��ȡ�ŷ�
		Envelope* GetEnvelope();

		//��ȡ������
		Context* GetContext();

		//��ȡ����������
		Token* GetContextToken();
	public:
		//����
		bool Start();

		//ֹͣ
		void Stop(uint32 wait = 0);

		//��ͣ
		void Pause(uint32 wait = 0);

		//�ָ�
		void Resume();

		//����
		void Restart(uint32 wait = 0);
	public:
		//��ʼ��������
		virtual bool Initialize(Library* lib, int fid); 
	};
}