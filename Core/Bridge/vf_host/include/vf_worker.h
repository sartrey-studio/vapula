#pragma once

namespace vapula
{
	class Task;

	//�����߻���
	class Worker
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