#include "worker_pipe.h"

#include "vf_task.h"
#include "vf_invoker.h"
#include "vf_xml.h"
#include "vf_config.h"

using std::ostringstream;

Worker_PIPE::Worker_PIPE()
{
	_Pipe = new Pipe();
}

Worker_PIPE::~Worker_PIPE()
{
	Clear(_Pipe);
}

bool Worker_PIPE::RunStageA()
{
	Task* task = dynamic_cast<Task*>(_Task);
	xml_node<>* cfg = (xml_node<>*)xml::Parse(task->GetCtrlConfig());
	std::locale::global(std::locale(""));
	cstr pid = xml::ValueA(cfg->first_node("pid"));
	if(!_Pipe->Connect(pid))
		return false;
	_Pipe->Write(L"A");
	//TODO: wait for permission
	return true;
}

bool Worker_PIPE::RunStageB()
{
	Config* config = Config::GetInstance();
	Flag* flag = config->GetFlag();

	Task* task = dynamic_cast<Task*>(_Task);
	Invoker* inv = task->GetInvoker();

	_Pipe->Write(L"B");
	//TODO: wait for permission

	int freq_monitor = flag->Valid(VF_CONFIG_RTMON) ? 5 : 50;
	inv->Start();
	Context* ctx = inv->GetContext();
	while(ctx->GetState() != VF_STATE_IDLE)
	{
		ostringstream oss;
		oss<<ctx->GetState()<<",";
		oss<<ctx->GetProgress();
		_Pipe->WriteA(oss.str().c_str());
		cstr data = _Pipe->ReadA();
		int ctrl = atoi(data);
		switch(ctrl)
		{
		case VF_CTRL_CANCEL:
			inv->Stop(30000);
			break;
		case VF_CTRL_PAUSE:
			inv->Pause();
		case VF_CTRL_RESUME:
			inv->Resume();
			break;
		}
		Sleep(freq_monitor);
	}
	ostringstream oss;
	oss<<VF_STATE_IDLE<<","<<100.0f;
	_Pipe->WriteA(oss.str().c_str());
	return true;
}

bool Worker_PIPE::RunStageC()
{
	Task* task = dynamic_cast<Task*>(_Task);
	Invoker* inv = task->GetInvoker();
	Envelope* env = inv->GetEnvelope();

	string resp = "C<response><params>";
	for(int i=0;i<env->GetTotal();i++) 
	{
		if(!env->GetInState(i))
		{
			resp += "<param id=\"";
			resp += ValueToStr(i);
			resp += "\">";
			resp += env->CastReadA(i);
			resp += "</param>";
		}
	}
	resp += "</params><debug>";
	resp += "<exception>";
	resp += "</exception>";
	resp += "</debug></response>";

	//if(_Pipe->GetDataVol() >= xml.size())
	//{
	cstr str = CopyStrA(resp.c_str());
	_Pipe->WriteA(str);
	delete str;
	//}
	return false;
}