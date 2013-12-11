#pragma once

#include "tcm_candy.h"

namespace tcm
{
	//���������񷵻�ֵ
	enum TaskReturnCode
	{
		TCM_TASK_RETURN_NORMAL = 0,
		TCM_TASK_RETURN_ERROR_A = 1,
		TCM_TASK_RETURN_ERROR_B = 2,
		TCM_TASK_RETURN_ERROR_C = 3
	};

	class Library;
	class Invoker;
	class Worker;

	//�������
	class TCM_BRIDGE_API Task
	{
	protected:
		Task();
	public:
		~Task();
	public:
		//��ָ��XML�ļ���������
		static Task* Parse(strw path);
	protected:
		Library* _Lib;
		int _FuncId;
		Invoker* _Invoker;
	protected	:
		float* _StageTime;
	public:
		//���ý׶κ�ʱ������Ϊ��λ
		void SetStageTime(int stage, float time);

		//��ȡ�׶κ�ʱ������Ϊ��λ
		float GetStageTime(int stage);

		//��ȡ�����ָ�����ܿ�
		Library* GetLibrary();

		//��ȡ�����ָ������
		int GetFunctionId();

		//��ȡ������
		Invoker* GetInvoker();
	public:
		//ָ����������������
		virtual bool RunAs(Worker* worker) = 0;
	};

	//�����߻���
	class TCM_BRIDGE_API Worker
	{
	public:
		Worker();
		~Worker();
	protected:
		Task* _Task;
	public:
		//��������
		int Run(Task* task);

		//��ȡ����
		Task* GetTask();
	protected:
		//��������׶�A
		virtual bool RunStageA() = 0;

		//��������׶�B
		virtual bool RunStageB() = 0;

		//��������׶�C
		virtual bool RunStageC() = 0;
	};
}