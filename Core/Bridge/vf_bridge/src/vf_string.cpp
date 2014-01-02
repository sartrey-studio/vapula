#include "vf_string.h"
#include "unicode/ucnv.h"

namespace vapula
{
	namespace str
	{
		cstr8 ToCh8(cstr16 src, cstr8 cp)
		{
			if(src == null) 
				return null;
			UErrorCode err = U_ZERO_ERROR;
			UConverter* conv = ucnv_open(cp, &err);
			if(conv == null) 
				return null;
			int len = ucnv_fromUChars(conv, null, 0, src, -1, &err) + 1;
			char* dst = new char[len];
			memset(dst, 0, len);
			err = U_ZERO_ERROR;
			len = ucnv_fromUChars(conv, dst, len, src, -1, &err);
			ucnv_close(conv);
			return dst;
		}

		cstr16 ToCh16(cstr8 src, cstr8 cp)
		{
			if(src == null) 
				return null;
			UErrorCode err = U_ZERO_ERROR;
			UConverter* conv = ucnv_open(cp, &err);
			if(conv == null) 
				return null;
			int len = ucnv_toUChars(conv, null, 0, src, -1, &err) + 1;
			wchar_t* dst = new wchar_t[len];
			memset(dst, 0, len * 2);
			err = U_ZERO_ERROR;
			ucnv_toUChars(conv, dst, len, src, -1, &err);
			ucnv_close(conv);
			return dst;
		}

		cstr8 EncodeCh8(cstr8 src, cstr8 cp_from, cstr8 cp_to)
		{
			cstr16 s16 = ToCh16(src, cp_from);
			cstr8 s8 = ToCh8(s16, cp_to);
			delete s16;
			return s8;
		}

		cstr8 Copy(cstr8 src)
		{
			if(src == null)
				return null;
			size_t len = strlen(src);
			str8 dst = new char[len + 1];
			memcpy(dst, src, len);
			dst[len] = 0;
			return const_cast<cstr8>(dst);
		}

		cstr16 Copy(cstr16 src)
		{
			if(src == null) 
				return null;
			size_t len = wcslen(src);
			wchar_t* dst = new wchar_t[len + 1];
			memcpy(dst, src, len * 2);
			dst[len] = 0;
			return const_cast<cstr16>(dst);
		}

		cstr8 Replace(cstr8 src, cstr8 from, cstr8 to)
		{
			cstr16 src16 = ToCh16(src, _vf_msg_cp);
			cstr16 from16 = ToCh16(from, _vf_msg_cp);
			cstr16 to16 = ToCh16(to, _vf_msg_cp);
			cstr16 ret16 = Replace(src16, from16, to16);
			cstr8 ret = ToCh8(ret16, _vf_msg_cp);
			delete src16;
			delete from16;
			delete to16;
			delete ret16;
			return ret;
		}

		cstr16 Replace(cstr16 src, cstr16 from, cstr16 to)
		{
			if(src == null || from == null)
				return null;
			int len_from = wcslen(from);
			if(len_from < 1) 
				return Copy(src);
			wstring str_src = src;
			wstring str_dst = L"";
			for(;;)
			{
				uint32 p1 = str_src.find(from);
				if(p1 != wstring::npos) 
				{
					str_dst += str_src.substr(0, p1);
					str_dst += to;
					str_src = str_src.substr(p1 + len_from);
				}
				else
				{
					str_dst += str_src;
					break;
				}
			}
			return Copy(str_dst.c_str());
		}
	}
}