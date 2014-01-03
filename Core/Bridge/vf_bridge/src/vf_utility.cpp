#include "vf_utility.h"
#include "vf_setting.h"

namespace vapula
{
	void ShowMsgbox(cstr8 value, cstr8 caption)
	{
		Settings* settings = Settings::GetInstance();
		if(!settings->IsSilent())
			MessageBoxA(null, value, 
			caption == null ? _vf_bridge : caption, 0);
	}

	void ShowMsgbox(cstr16 value, cstr16 caption)
	{
		Settings* settings = Settings::GetInstance();
		if(!settings->IsSilent())
			MessageBoxW(null, value,
			caption == null ? str::ToCh16(_vf_bridge) : caption, 0);
	}

	cstr8 GetRuntimeDir()
	{
		HMODULE mod = GetModuleHandle(L"vf_bridge");
		wchar_t path[MAX_PATH];
		GetModuleFileName(mod, path, MAX_PATH);
		cstr8 path8 = str::ToCh8(path);
		string str_full = path8;
		string str_ret = str_full.substr(0, str_full.rfind(L'\\') + 1);
		cstr8 ret = str::Copy(str_ret.c_str());
		delete path8;
		return ret;
	}

	cstr8 GetAppName()
	{
		wchar_t path[MAX_PATH];
		GetModuleFileName(null, path, MAX_PATH);
		cstr8 path8 = str::ToCh8(path);
		string str_full = path8;
		string str_ret = str_full.substr(str_full.rfind(L'\\') + 1);
		cstr8 ret = str::Copy(str_ret.c_str());
		delete path8;
		return ret;
	}

	cstr8 GetAppDir()
	{
		wchar_t path[MAX_PATH];
		GetModuleFileName(null, path, MAX_PATH);
		cstr8 path8 = str::ToCh8(path);
		string str_full = path8;
		string str_ret = str_full.substr(0, str_full.rfind(L'\\') + 1);
		cstr8 ret = str::Copy(str_ret.c_str());
		delete path8;
		return ret;
	}

	cstr8 GetDirPath(cstr8 path, bool isfile)
	{
		uint32 len = strlen(path);
		if(len < 1) 
			return str::Copy("\\");
		cstr8 s8_fix = str::Replace(path, "/", "\\");
		string s = s8_fix;
		uint32 pos = s.rfind('\\');
		if(!isfile)
		{
			if(pos == string::npos || len != pos + 1)
				s += L'\\';
		}
		else
		{
			if(pos == string::npos)
				s = "\\";
			else if(pos != s.size() - 1) 
				s = s.substr(0, pos + 1);
		}
		cstr8 s8_ret = str::Copy(s.c_str());
		delete s8_fix;
		return s8_ret;
	}

	bool CanOpenRead(cstr8 file)
	{
		cstr16 file16 = str::ToCh16(file);
		HANDLE handle = 
			CreateFile(file16, 0, 
			FILE_SHARE_READ, null, 
			OPEN_EXISTING, null, null);
		delete file16;
		if(handle == INVALID_HANDLE_VALUE) 
			return false;
		CloseHandle(handle);
		return true;
	}
}