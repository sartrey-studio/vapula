#pragma once

#include "vf_host.h"

namespace vapula
{
	class Worker;

	//����
	class Task
	{
	private:
		Task();
	public:
		~Task();

	private:
		Library* _Lib;
		int _FuncId;
		Invoker* _Invoker;
		float* _StageTime;

	private:
		Dict* _Tags;
		int _CtrlMode;
		cstr _CtrlConfig;

	public:
		//��ָ��XML�ļ���������
		static Task* Parse(cstrw path);

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
		//��ȡ��չ��ǩ
		Dict* GetTags();

		//��ȡ����ģʽ
		int GetCtrlMode();

		//��ȡ��������
		cstr GetCtrlConfig();

	public:
		//ָ����������������
		bool RunAs(Worker* worker);
	};

}