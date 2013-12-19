#include "main.h"
#include <iostream>

int Run(int function, Envelope* envelope, Context* context)
{
	Context* ctx = context;
	int ret = 0;
	switch(function)
	{
	case 1:
		ret = Function_Math(envelope, ctx);
		break;
	case 2:
		ret = Function_Out(envelope, ctx);
		break;
	case 3:
		ret = Function_TestArray(envelope,ctx);
		break;
	case 4:
		ret = Function_TestObject(envelope,ctx);
		break;
	case 5:
		ret = Function_TestContext(envelope,ctx);
		break;
	default:
		ret = VF_RETURN_NULLENTRY;
	}
	return ret;
}

//��һ������
int Function_Math(Envelope* envelope, Context* context)
{
	int a = envelope->Read<int>(1);
	int b = envelope->Read<int>(2);

	int c = a + b;

	context->SetProgress(100);
	envelope->Write(3, c);
	return VF_RETURN_NORMAL;
}

//�ڶ�������
int Function_Out(Envelope* envelope,Context* context)
{
	cstr16 str = L"����Engligh�ձ��Z�ƥ���";
	context->SetProgress(100);
	envelope->Write(1, str);
	return VF_RETURN_NORMAL;
}

//����������
int Function_TestArray(Envelope* envelope,Context* context)
{
	int count = envelope->Read<int>(1);
	int* data = (int*)envelope->Read<object>(2);

	int result = 0;
	for(int i=0;i<count;i++)
		result += data[i];

	envelope->Write(3,result);
	return VF_RETURN_NORMAL;
}

//���ĸ�����
int Function_TestObject(Envelope* envelope,Context* context)
{
	TestClassA* obj = (TestClassA*)envelope->Read<LPVOID>(1);
	bool ifinc = envelope->Read<bool>(2);

	if(ifinc) obj->Inc();
	else obj->Dec();

	envelope->Write(3, (object)obj);
	return VF_RETURN_NORMAL;
}

//���������
int Function_TestContext(Envelope* envelope,Context* context)
{
	for(int i=0;i<1000;i++)
	{
		int ctrl = context->GetCtrlCode();
		if(ctrl == VF_CTRL_CANCEL)
			return VF_RETURN_CANCELBYMSG;
		if(ctrl == VF_CTRL_PAUSE)
		{
			context->ReplyCtrlCode();
			while(true)
			{
				int ctrl = context->GetCtrlCode();
				if(ctrl == VF_CTRL_RESUME)
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
	return VF_RETURN_NORMAL;
}