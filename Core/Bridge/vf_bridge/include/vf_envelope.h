#pragma once

#include "vf_base.h"

namespace vapula
{
	//�����ŷ�
	class VAPULA_API Envelope
	{
	private:
		Envelope(int total, int* types, bool* ins);
	public:
		~Envelope();
	public:
		//��XML�ļ��������ŷ����
		static Envelope* Load(cstr8 path, int fid);
		
		//��XML�ַ����������ŷ����
		//Ҫ������params�ڵ�
		static Envelope* Parse(cstr8 xml);
	private:
		//��XML����������ŷ����
		//Ҫ������params�ڵ�
		static Envelope* Parse(object xml);
	private:
		int _Length;
		int _Total;
		object _Memory;
		int*	_Types;
		bool* _InStates;
		int* _Offsets;
	private:
		inline bool AssertId(int id, Envelope* env = null)
		{
			if(id < 1)
				return false;
			return env == null ? id <= _Total : id <= env->_Total;
		}
	private:
		//��ȡ��ʶ��Ӧ�������ڴ��ַ
		uint64 _AddrOf(int id);
	public:
		//��ȡ��������
		int GetTotal();

		//��ȡ��������
		//true - ���� | false - ���
		bool GetInState(int id);

		//��ȡ��������
		int GetType(int id);
	public:
		//д�����
		//size>0ʱǳ������������
		void WriteEx(int id, object value, int size = 0);

		//��������
		template<typename T>
		T Read(int id)
		{
			if(!AssertId(id))
				throw invalid_argument(_vf_err_1);
			T* param = (T*)_AddrOf(id);
			return param[0];
		}

		//�����������ػ�bool
		template<>
		bool Read<bool>(int id)
		{
			char ret = Read<char>(id);
			return (ret == 1);
		}

		//�����������ػ�8λ�ֽ��ַ���
		template<>
		cstr8 Read<cstr8>(int id)
		{
			cstr8 tmp = (cstr8)Read<object>(id);
			cstr8 s8 = str::Copy(tmp);
			return s8;
		}

		//�����������ػ�16λ�ֽ��ַ���
		template<>
		cstr16 Read<cstr16>(int id)
		{
			cstr8 s8 = Read<cstr8>(id);
			cstr16 s16 = str::ToCh16(s8);
			delete s8;
			return s16;
		}

		//д�����
		template<typename T>
		void Write(int id, T value)
		{
			if(!AssertId(id))
				throw invalid_argument(_vf_err_1);
			T* param = (T*)_AddrOf(id);
			param[0] = value;
		}

		//д��������ػ�bool
		template<>
		void Write<bool>(int id, bool value)
		{
			Write<char>(id, value ? 1 : 0);
		}

		//д���ַ������Զ�����
		//���д��UTF8������ַ���
		template<>
		void Write<cstr8>(int id, cstr8 value)
		{
			WriteEx(id, (object)value, strlen(value) + 1);
		}

		//д���ַ������Զ�����
		template<>
		void Write<cstr16>(int id, cstr16 value)
		{
			cstr8 s8 = str::ToCh8(value, _vf_msg_cp);
			Write(id, s8);
			delete s8;
		}

		//������ֵ���Զ�ת�͵��ַ���
		cstr8 CastRead(int id);

		//���ַ����Զ�ת�͵���ֵ��д��
		void CastWrite(int id, cstr8 value);

		//Ͷ�ݵ�ǰ�ŷ⵽Ŀ��
		//Ҫ��������ȫһ��
		//Ͷ�ݲ��Ḵ�ƶ�������
		void Deliver(Envelope* who, int from, int to);

		//Ͷ�ݵ�ǰ�ŷ⵽Ŀ��
		//�߱��Զ�����ת����Ч�ʽϵ�
		//Ͷ�ݲ��Ḵ�ƶ�������
		void CastDeliver(Envelope* who, int from, int to);
	};
}