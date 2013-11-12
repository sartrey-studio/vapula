#include "stdafx.h"
#include "tcm_bridge_c.h"
#include "tcm_driver.h"
#include "tcm_library.h"
#include "tcm_invoker.h"
#include "tcm_pipe.h"

using namespace tcm;

void tcmTestBridge()
{
}

void tcmDeleteObject(object obj)
{
	delete obj;
}

int tcmGetDriverCount()
{
	DriverHub* obj = DriverHub::GetInstance();
	return obj->GetCount();
}

int tcmLinkDriver(str id)
{
	tcm::DriverHub* obj = tcm::DriverHub::GetInstance();
	return obj->Link(id) ? 1 : 0;
}

int tcmKickDriver(str id)
{
	tcm::DriverHub* obj = tcm::DriverHub::GetInstance();
	return obj->Kick(id) ? 1 : 0;
}

void tcmKickAllDrivers()
{
	tcm::DriverHub* obj = tcm::DriverHub::GetInstance();
	obj->KickAll();
}

int tcmGetLibraryCount()
{
	return tcm::Library::GetCount();
}

object tcmLoadLibraryW(strw path)
{
	return tcm::Library::Load(path);
}

object tcmLoadLibraryA(str path)
{
	strw path_w = tcm::MbToWc(path);
	object ret = tcm::Library::Load(path_w);
	delete path_w;
	return ret;
}

str tcmGetLibraryRuntime(object lib)
{
	tcm::Library* obj = (tcm::Library*)lib;
	return obj->GetRuntimeId();
}

strw tcmGetLibraryId(object lib)
{
	tcm::Library* obj = (tcm::Library*)lib;
	return obj->GetLibraryId();
}

int tcmMountLibrary(object lib)
{
	tcm::Library* obj = (tcm::Library*)lib;
	return obj->Mount() ? TRUE : FALSE;
}

void tcmUnmountLibrary(object lib)
{
	tcm::Library* obj = (tcm::Library*)lib;
	obj->Unmount();
}

object tcmCreateInvoker(object lib, int fid)
{
	tcm::Library* obj = (tcm::Library*)lib;
	return obj->CreateInvoker(fid);
}

int tcmGetFunctionId(object inv)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	return obj->GetFunctionId();
}

int tcmStartInvoker(object inv)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	return obj->Start() ? TRUE : FALSE;
}

void tcmStopInvoker(object inv, uint32 wait)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	obj->Stop(wait);
}

void tcmPauseInvoker(object inv, uint32 wait)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	obj->Pause(wait);
}

void tcmResumeInvoker(object inv)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	obj->Resume();
}

void tcmRestartInvoker(object inv, uint32 wait)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	obj->Restart(wait);
}

object tcmGetContextToken(object inv)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	return obj->GetContextToken();
}

object tcmStampContext(object ctx)
{
	tcm::Context* obj = (tcm::Context*)ctx;
	return tcm::Token::Stamp(obj);
}

object tcmGetContext(object inv)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	return obj->GetContext();
}

object tcmCreateContext()
{
	return new tcm::Context();
}

int tcmGetCtrlCode(object ctx)
{
	tcm::Context* obj = (tcm::Context*)ctx;
	return obj->GetCtrlCode();
}

void tcmSetCtrlCode(object ctx, int ctrl_code, object token)
{
	tcm::Context* obj1 = (tcm::Context*)ctx;
	tcm::Token* obj2 = (tcm::Token*)token;
	obj1->SetCtrlCode(obj2, ctrl_code);
}

float tcmGetProgress(object ctx)
{
	tcm::Context* obj = (tcm::Context*)ctx;
	return obj->GetProgress();
}

void tcmSetProgress(object ctx, float prog)
{
	tcm::Context* obj = (tcm::Context*)ctx;
	obj->SetProgress(prog);
}

int tcmGetState(object ctx)
{
	tcm::Context* obj = (tcm::Context*)ctx;
	return obj->GetState();
}

void tcmSetState(object ctx, int state, object token)
{
	tcm::Context* obj1 = (tcm::Context*)ctx;
	tcm::Token* obj2 = (tcm::Token*)token;
	return obj1->SetState(obj2, state);
}

int tcmGetReturnCode(object ctx)
{
	tcm::Context* obj = (tcm::Context*)ctx;
	return obj->GetReturnCode();
}

void tcmSetReturnCode(object ctx, int return_code, object token)
{
	tcm::Context* obj1 = (tcm::Context*)ctx;
	tcm::Token* obj2 = (tcm::Token*)token;
	obj1->SetReturnCode(obj2, return_code);
}

void tcmReplyCtrlCode(object ctx)
{
	tcm::Context* obj = (tcm::Context*)ctx;
	obj->ReplyCtrlCode();
}

object tcmGetEnvelope(object inv)
{
	tcm::Invoker* obj = (tcm::Invoker*)inv;
	return obj->GetEnvelope();
}

object tcmLoadEnvelopeW(strw path, int fid)
{
	return tcm::Envelope::Load(path, fid);
}

object tcmLoadEnvelopeA(str path, int fid)
{
	strw path_w = tcm::MbToWc(path);
	object ret = tcm::Envelope::Load(path_w, fid);
	delete path_w;
	return ret;
}

object tcmParseEnvelopeW(strw xml)
{
	str str = tcm::WcToMb(xml);
	object ret = tcm::Envelope::Parse(str);
	delete str;
	return ret;
}

object tcmParseEnvelopeA(str xml)
{
	return tcm::Envelope::Parse(xml);
}

void tcmWriteEnvelopeW(object env, int id, strw value)
{
	tcm::Envelope* obj = (tcm::Envelope*)env;
	obj->CastWriteW(id, value);
}

void tcmWriteEnvelopeA(object env, int id, str value)
{
	tcm::Envelope* obj = (tcm::Envelope*)env;
	obj->CastWriteA(id, value);
}

strw tcmReadEnvelopeW(object env, int id)
{
	tcm::Envelope* obj = (tcm::Envelope*)env;
	return obj->CastReadW(id);
}

str tcmReadEnvelopeA(object env, int id)
{
	tcm::Envelope* obj = (tcm::Envelope*)env;
	return obj->CastReadA(id);
}

void tcmDeliverEnvelope(object src_env, object dst_env, int from, int to)
{
	tcm::Envelope* src = (tcm::Envelope*)src_env;
	tcm::Envelope* dst = (tcm::Envelope*)dst_env;
	src->Deliver(dst, from, to);
}

void tcmCastDeliverEnvelope(object src_env, object dst_env, int from, int to)
{
	tcm::Envelope* src = (tcm::Envelope*)src_env;
	tcm::Envelope* dst = (tcm::Envelope*)dst_env;
	src->CastDeliver(dst, from, to);
}

//Design the following

object tcmCreatePipe()
{
	tcm::Pipe* pipe = new tcm::Pipe();
	return pipe;
}

strw tcmListenPipe(object pipe)
{
	tcm::Pipe* obj = (tcm::Pipe*)pipe;
	if(!obj->Listen()) return null;
	return obj->GetPipeId();
}

int tcmGetPipeFlag(object pipe, int action)
{
	tcm::Pipe* obj = (tcm::Pipe*)pipe;
	return obj->GetFlag(action) ? TRUE : FALSE;
}

void tcmSetPipeFlag(object pipe, int action, int value)
{
	tcm::Pipe* obj = (tcm::Pipe*)pipe;
	obj->SetFlag(action, value == TRUE);
}

void tcmWritePipe(object pipe, object value, uint32 size)
{
	tcm::Pipe* obj = (tcm::Pipe*)pipe;
	obj->Write(value, size);
}

void tcmReadPipe(object pipe, object data)
{
	tcm::Pipe* obj = (tcm::Pipe*)pipe;
	obj->Read(data);
}