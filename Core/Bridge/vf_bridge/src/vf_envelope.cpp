#include "vf_envelope.h"
#include "vf_xml.h"
#include "rapidxml/rapidxml.hpp"

namespace vapula
{
	using rapidxml::xml_document;
	using rapidxml::xml_node;

	Envelope::Envelope(int total, int* types, bool* ins)
	{
		_Total = total;
		_Types = types;
		_InStates = ins;
		if(total > 0)
		{
			_Offsets = new int[total];
			int len = 0;
			for(int i=0; i<total; i++)
			{
				_Offsets[i] = len;
				len += GetTypeUnit(_Types[i]);
			}
			_Length = len;
			_Memory = new byte[len];
			memset(_Memory, 0, len);
		}
		else
		{
			_Offsets = null;
			_Memory = null;
		}
	}

	Envelope::~Envelope()
	{
		Clear(_InStates, true);
		Clear(_Types, true);
		Clear(_Offsets, true);
		Clear(_Memory);
	}

	uint64 Envelope::_AddrOf(int id)
	{
		uint64 addr = (uint64)_Memory + _Offsets[id - 1];
		return addr;
	}

	void Envelope::WriteEx(int id, object value, int size)
	{
		object* param = (object*)_AddrOf(id);
		if(size > 0)
		{
			//ǳ����
			param[0] = new byte[size];
			memcpy(param[0], value, size);
		}
		else
		{
			//���ø���
			param[0] = value;
		}
	}

	Envelope* Envelope::Parse(object xml)
	{
		if(xml == null) return null;

		vector<int> v_id;
		vector<int> v_type;
		vector<bool> v_in;

		xml_node<>* node = (xml_node<>*)xml;
		node = node->first_node();
		int total = 0;
		while(node)
		{
			v_id.push_back(xml::ValueInt(node->first_attribute("id")));
			v_type.push_back(xml::ValueInt(node->first_attribute("type")));
			v_in.push_back(xml::ValueBool(node->first_attribute("in"), "true"));
			node = node->next_sibling();
			total++;
		}

		if(total > 0)
		{
			int* arr_type = new int[total];
			bool* arr_in = new bool[v_id.size()];
			for(int i=0; i<total; i++)
			{
				int id = v_id[i] - 1;
				arr_type[id] = v_type[i];
				arr_in[id] = v_in[i];
			}
			Envelope* env = new Envelope(v_id.size(), arr_type, arr_in);
			return env;
		}
		else
		{
			Envelope* env = new Envelope(0, null, null);
			return env;
		}
	}

	Envelope* Envelope::Parse(cstr8 xml)
	{
		xml_document<>* xdoc = (xml_document<>*)xml::Parse(xml);
		Envelope* env = Parse(xdoc->first_node());
		delete xdoc;
		return env;
	}

	Envelope* Envelope::Load(cstr8 path, int fid)
	{
		cstr8 data = null;
		xml_document<>* xdoc = (xml_document<>*)xml::Load(path, data);
		xml_node<>* xe = (xml_node<>*)xml::Path(
			xdoc, 3, "library", "functions", "function");
		while (xe)
		{
			int tmpv = xml::ValueInt(xe->first_attribute("id"));
			if(tmpv == fid) break;
			xe = xe->next_sibling();
		}
		xe = xe->first_node("params");
		Envelope* env = Envelope::Parse(xe);
		delete data;
		return env;
	}

	int Envelope::GetType(int id)
	{
		return _Types[id - 1];
	}

	int Envelope::GetTotal()
	{
		return _Total;
	}

	bool Envelope::GetInState(int id)
	{
		if(!AssertId(id)) throw invalid_argument(_vf_err_1);
		return _InStates[id - 1];
	}

	cstr8 Envelope::CastRead(int id)
	{
		if(!AssertId(id))
			throw invalid_argument(_vf_err_1);
		int type = GetType(id);
		switch(type)
		{
		case VF_DATA_POINTER:
			return str::ValueTo((uint64)Read<object>(id));
		case VF_DATA_INT8:	
			return str::ValueTo(Read<int8>(id));
		case VF_DATA_UINT8:
			return str::ValueTo(Read<uint8>(id));
		case VF_DATA_INT16:
			return str::ValueTo(Read<int16>(id));
		case VF_DATA_UINT16:
			return str::ValueTo(Read<uint16>(id));
		case VF_DATA_INT32:
			return str::ValueTo(Read<int32>(id));
		case VF_DATA_UINT32:
			return str::ValueTo(Read<uint32>(id));
		case VF_DATA_INT64:
			return str::ValueTo(Read<int64>(id));
		case VF_DATA_UINT64:
			return str::ValueTo(Read<uint64>(id));
		case VF_DATA_REAL32:
			return str::ValueTo(Read<real32>(id));
		case VF_DATA_REAL64:
			return str::ValueTo(Read<real64>(id));
		case VF_DATA_BOOL:	
			return Read<bool>(id) ? "true" : "false";
		case VF_DATA_STRING:
			return str::Copy(Read<cstr8>(id));
		default:
			return null;
		}
	}

	void Envelope::CastWrite(int id, cstr8 value)
	{
		if(value == null)
			throw invalid_argument(_vf_err_2);
		if(!AssertId(id))
			throw invalid_argument(_vf_err_1);
		int type = GetType(id);
		switch(type)
		{
		case VF_DATA_POINTER:
			WriteEx(id, (object)abs(atoi(value)),0); break;
		case VF_DATA_INT8:	
			Write(id, (int8)atoi(value)); break;
		case VF_DATA_UINT8:
			Write(id, (uint8)atoi(value)); break;
		case VF_DATA_INT16:
			Write(id, (int16)atoi(value)); break;
		case VF_DATA_UINT16:
			Write(id, (uint16)atoi(value)); break;
		case VF_DATA_INT32:
			Write(id, atoi(value)); break;
		case VF_DATA_UINT32:
			Write(id, (uint32)atoi(value)); break;
		case VF_DATA_INT64:
			Write(id, _atoi64(value)); break;
		case VF_DATA_UINT64:
			Write(id, (uint64)_atoi64(value)); break;
		case VF_DATA_REAL32:
			Write(id, atof(value)); break;
		case VF_DATA_REAL64:
			Write(id, atof(value)); break;
		case VF_DATA_BOOL:	
			Write(id, (strcmp(value,"true") == 0) ? 1 : 0); break;
		case VF_DATA_STRING:
			Write(id, value); break;
		default:
			break;
		}
	}

	void Envelope::Deliver(Envelope* who, int from, int to)
	{
		if(!AssertId(from) || !AssertId(to, who))
			throw invalid_argument(_vf_err_1);
		int type = GetType(from);
		if(type != who->GetType(to))
			throw invalid_argument(_vf_err_3);

		object ptr = null;
		switch(type)
		{
		case VF_DATA_POINTER:
			ptr = new object[1];
			*((object*)ptr) = Read<object>(from);
			who->Write(to, ptr);
			break;
		case VF_DATA_INT8:
			ptr = new int8[1];
			*((int8*)ptr) = Read<int8>(from);
			who->Write(to, *((int8*)ptr));
			break;
		case VF_DATA_UINT8:
			ptr = new uint8[1];
			*((uint8*)ptr) = Read<uint8>(from);
			who->Write(to, *((uint8*)ptr));
			break;
		case VF_DATA_INT16:
			ptr = new int16[1];
			*((int16*)ptr) = Read<int16>(from);
			who->Write(to, *((int16*)ptr));
			break;
		case VF_DATA_UINT16:
			ptr = new uint16[1];
			*((uint16*)ptr) = Read<uint16>(from);
			who->Write(to, *((uint16*)ptr));
			break;
		case VF_DATA_INT32:
			ptr = new int32[1];
			*((int32*)ptr) = Read<int32>(from);
			who->Write(to, *((int32*)ptr));
			break;
		case VF_DATA_UINT32:
			ptr = new uint32[1];
			*((uint32*)ptr) = Read<uint32>(from);
			who->Write(to, *((uint32*)ptr));
			break;
		case VF_DATA_INT64:
			ptr = new int64[1];
			*((int64*)ptr) = Read<int64>(from);
			who->Write(to, *((int64*)ptr));
			break;
		case VF_DATA_UINT64:
			ptr = new uint64[1];
			*((uint64*)ptr) = Read<uint64>(from);
			who->Write(to, *((uint64*)ptr));
			break;
		case VF_DATA_REAL32:
			ptr = new real32[1];
			*((real32*)ptr) = Read<real32>(from);
			who->Write(to, *((real32*)ptr));
			break;
		case VF_DATA_REAL64:
			ptr = new real64[1];
			*((real64*)ptr) = Read<real64>(from);
			who->Write(to, *((real64*)ptr));
			break;
		case VF_DATA_BOOL:
			ptr = new int8[1];
			*((int8*)ptr) = Read<int8>(from);
			who->Write(to, *((int8*)ptr));
			break;
		case VF_DATA_STRING:
			ptr = new cstr16[1];
			*((cstr16*)ptr) = Read<cstr16>(from);
			who->Write(to, *((cstr16*)ptr));
			break;
		default:
			return;
		}
		delete [] ptr;
	}

	void Envelope::CastDeliver(Envelope* who, int from, int to)
	{
		if(!AssertId(from) || !AssertId(to, who))
			throw invalid_argument(_vf_err_1);
		int type = GetType(from);
		if(type == VF_DATA_POINTER)
		{
			object* ptr = new object[1];
			ptr[0] = Read<object>(from);
			return who->Write(to, ptr[0]);
		}
		else
		{
			cstr8 value = CastRead(from);
			return who->CastWrite(to, value);
		}
	}
}