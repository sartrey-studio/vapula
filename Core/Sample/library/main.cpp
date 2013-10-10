#include "stdafx.h"
#include "main.h"
#include <iostream>

int Run(int function, Envelope* envelope, Context* context)
{
	Context* ctx = (context == NULL ? new Context() : context);
	DWORD ret = 0;
	switch(function)
	{
	case 0:
		ret = Function_Math(envelope, ctx);
		break;
	case 1:
		ret = Function_Out(envelope, ctx);
		break;
	case 2:
		ret = Function_TestArray(envelope,ctx);
		break;
	case 3:
		ret = Function_TestObject(envelope,ctx);
		break;
	case 4:
		ret = Function_TestContext(envelope,ctx);
		break;
	default:
		ret = TCM_RETURN_NULLENTRY;
	}
	return ret;
}

//��һ������
int Function_Math(Envelope* envelope, Context* context)
{
	int a = envelope->Read<int>(0);
	int b = envelope->Read<int>(1);

	int c = a + b;

	context->SetProgress(100);
	envelope->Write(2, c);
	return TCM_RETURN_NORMAL;
}

//�ڶ�������
int Function_Out(Envelope* envelope,Context* context)
{
	PCSTR str1 = "Hello World!";
	PCWSTR str2 = L"����Engligh�ձ��Z�ƥ���";
	context->SetProgress(100);
	envelope->Write(0, str1);
	envelope->Write(1, str2);
	return TCM_RETURN_NORMAL;
}

//����������
int Function_TestArray(Envelope* envelope,Context* context)
{
	int count = envelope->Read<int>(0);
	int* data = (int*)envelope->Read<LPVOID>(1);

	int result = 0;
	for(int i=0;i<count;i++)
		result += data[i];

	envelope->Write(2,result);
	return TCM_RETURN_NORMAL;
}

//���ĸ�����
int Function_TestObject(Envelope* envelope,Context* context)
{
	TestClassA* obj = (TestClassA*)envelope->Read<LPVOID>(0);
	bool ifinc = envelope->Read<bool>(1);

	if(ifinc) obj->Inc();
	else obj->Dec();

	envelope->Write(2,(LPVOID)obj);
	return TCM_RETURN_NORMAL;
}

//���������
int Function_TestContext(Envelope* envelope,Context* context)
{
	for(int i=0;i<1000;i++)
	{
		int ctrl = context->GetCtrlCode();
		if(ctrl == TCM_CTRL_CANCEL) return TCM_RETURN_CANCELBYMSG;
		if(ctrl == TCM_CTRL_PAUSE)
		{
			context->ReplyCtrlCode();
			while(true)
			{
				int ctrl = context->GetCtrlCode();
				if(ctrl == TCM_CTRL_RESUME)
				{
					context->ReplyCtrlCode();
					break;
				}
				Sleep(25);
			}
		}
		context->SetProgress(i/10.0);
		Sleep(25);
	}
	return TCM_RETURN_NORMAL;
}