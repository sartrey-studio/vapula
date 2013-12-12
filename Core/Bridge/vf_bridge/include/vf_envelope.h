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
		static Envelope* Load(cstrw path, int fid);
		
		//��XML�ַ����������ŷ����
		//Ҫ������params�ڵ�
		static Envelope* Parse(cstr xml);
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

		//�������Զ��ֽ��ַ�����ʽ��ȡ����
		template<>
		cstr Read<cstr>(int)
		{
			throw invalid_argument(_vf_err_4);
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
		//���ֽ��ַ�������ת���ɿ��ֽ��ַ���
		template<>
		void Write<cstr>(int id, cstr value)
		{
			cstrw strw = MbToWc(value);
			WriteEx(id, (object)strw, wcslen(strw) * 2 + 2);
			delete strw;
		}

		//д���ַ������Զ�����
		template<>
		void Write<cstrw>(int id, cstrw value)
		{
			WriteEx(id, (object)value, wcslen(value) * 2 + 2);
		}

		//������ֵ���Զ�ת�͵��ַ���
		cstr CastReadA(int id);
		cstrw CastReadW(int id);

		//���ַ����Զ�ת�͵���ֵ��д��
		void CastWriteA(int id, cstr value);
		void CastWriteW(int id, cstrw value);

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