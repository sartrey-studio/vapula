#pragma once

#include "vf_base.h"

namespace vapula
{
	class Envelope;
	class Invoker;
	class Driver;

	//组件基类
	class VAPULA_API Library
	{
	protected:
		Library();
	public:
		virtual ~Library();
	protected:
		cstr8 _Dir; //组件目录
		cstr8 _LibId; //组件标识
	protected:
		static int _Count;
	public:
		//加载指定组件
		static Library* Load(cstr8 path);
		
		//获取已装载库数量
		static int GetCount();
	public:
		//获取当前库标识
		cstr8 GetLibraryId();

		//创建指定功能的参数信封
		Envelope* CreateEnvelope(int fid);

		//获取指定功能的调用器
		Invoker* CreateInvoker(int fid);
	public:
		//获取环境标识
		virtual cstr8 GetRuntimeId() = 0;

		//获取物理库扩展名
		virtual cstr8 GetBinExt() = 0;

		//装载库
		virtual bool Mount();

		//卸载库
		virtual void Unmount();
	};
}