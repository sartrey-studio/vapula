#pragma once

#include "tcm_context.h"
#include "tcm_envelope.h"

namespace tcm
{
	class Token;
	class Library;

	//����ִ����
	class TCM_BRIDGE_API Executor
	{
	protected:
		Executor();
	public:
		virtual ~Executor();
	protected:
		int _FuncId;
		Envelope* _Envelope;
		Context* _Context;
		Token* _ContextToken;
	protected:
		HANDLE _Thread;
		bool _IsSuspend;
		virtual UINT WINAPI _ThreadProc();
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
		void Stop(UINT wait = 0);

		//��ͣ
		void Pause(UINT wait = 0);

		//�ָ�
		void Resume();

		//����
		void Restart(UINT wait = 0);
	public:
		//��ʼ��ִ����
		virtual bool Initialize(Library* lib, int fid); 
	};
}