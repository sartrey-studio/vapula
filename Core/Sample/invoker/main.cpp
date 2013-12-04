#include "windows.h"

#include "tcm_driver.h"
#include "tcm_library.h"
#include "tcm_invoker.h"
#include "tcm_config.h"

using std::cin;
using std::cout;
using std::endl;

using namespace tcm;

void Assert(bool condition)
{
	if(condition) cout<<"[OK]"<<endl;
	else
	{
		cout<<"[Fail]"<<endl;
		system("pause");
		exit(0);
	}
}

void Test1(Library* lib)
{
	cout<<"[get Invoker] ... ";
	Invoker* inv = lib->CreateInvoker(5);
	Assert(inv != NULL);

	cout<<"[Invoke function 5] ... ";
	Assert(inv->Start());

	Context* ctx = inv->GetContext();
	while(ctx->GetState() != TCM_STATE_IDLE)
	{
		float prog = ctx->GetProgress();
		if(prog > 10)
		{
			cout<<"[pause] progress:"<<prog<<endl;
			inv->Pause(50);
			break;
		}
		Sleep(50);
	}
	int step = 0;
	cout<<"has paused, wait for a moment"<<endl;
	while(step < 20)
	{
		step++;
		Sleep(50);
	}
	inv->Resume();
	float prog = ctx->GetProgress();
	cout<<"[resume] progress:"<<prog<<endl;
	while(ctx->GetState() != TCM_STATE_IDLE) Sleep(50);
	cout<<"finished"<<endl;
}

void Test2(Library* lib)
{
	cout<<"[get Invoker] ... ";
	Invoker* inv = lib->CreateInvoker(1);
	Assert(inv != NULL);

	cout<<"[get envelope] ... ";
	Envelope* env = inv->GetEnvelope();
	Assert(env != NULL);

	cout<<"[set params]"<<endl;
	env->Write(1, 12);
	env->Write(2, 23);

	cout<<"[Invoke function 0] ... ";
	Assert(inv->Start());

	Context* ctx = inv->GetContext();
	while(ctx->GetState() != TCM_STATE_IDLE) Sleep(50);
	
	int result = env->Read<int>(3);
	cout<<"<valid> - out:"<<result<<endl;

	LARGE_INTEGER freq, t1, t2;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&t1);
	for (int i=0;i<2000;i++)
	{
		env->Write(1, 12);
		env->Write(2, 23);
		inv->Start();
		Context* ctx = inv->GetContext();
		while(ctx->GetState() != TCM_STATE_IDLE) Sleep(0);
		int result = env->Read<int>(3);
	}
	QueryPerformanceCounter(&t2);
	cout<<"PerfC time:"<<(t2.QuadPart - t1.QuadPart) * 1000.0 / (float)freq.QuadPart<<" (ms)"<<endl;
}

void Test3(Library* lib)
{
	Invoker* inv = lib->CreateInvoker(2);
	inv->Start();
	Context* ctx = inv->GetContext();
	Envelope* env = inv->GetEnvelope();
	while(ctx->GetState() != TCM_STATE_IDLE) Sleep(50);
	ShowMsgStr(env->Read<PCWSTR>(1));
}

int main()
{
	DriverHub* drv_hub = DriverHub::GetInstance();
	cout<<"[register driver crt] ... ";
	Assert(drv_hub->Link("crt"));
	//cout<<"[register driver clr] ... ";
	//Assert(drv_hub->Link("clr"));

	cout<<"[load library] ... ";
	Library* lib = Library::Load(L"E:\\Projects\\vapula\\Core\\OutDir\\Debug\\sample_lib.tcm.xml");
	Assert(lib != NULL);

	cout<<"[mount library] ... ";
	Assert(lib->Mount());

	//Test1(lib);
	Test2(lib);
	Test3(lib);

	cout<<"[unmount component]"<<endl;
	lib->Unmount();

	cout<<"[kick all driver]"<<endl;
	drv_hub->KickAll();

	system("pause");
	return 0;
}