#pragma once

#include "tcm_task.h"

using namespace tcm;

//����
class TaskEx : public Task
{
public:
	TaskEx();
	~TaskEx();
public:
	static Task* Parse(PCWSTR path);
private:
	Dictionary* _Tags;
	int _CtrlMode;
	PCSTR _CtrlConfig;
public:
	//��ȡ��չ��ǩ
	Dictionary* GetTags();

	//��ȡ����ģʽ
	int GetCtrlMode();

	//��ȡ��������
	PCSTR GetCtrlConfig();
public:
	bool RunAs(Worker* worker);
};