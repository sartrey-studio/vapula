#pragma once

#include "tcm_base.h"

namespace tcm
{
	using std::runtime_error;

	const PCSTR _tcm_env_err_1 = "try to access null param";
	const PCSTR _tcm_env_err_2 = "try to write null value";
	const PCSTR _tcm_env_err_3 = "try to deliver between different types";

	//�����ŷ�
	class TCM_BRIDGE_API Envelope
	{
	private:
		Envelope(int total, int* types, bool* ins);
	public:
		~Envelope();
	public:
		//��XML�ļ��������ŷ����
		static Envelope* Load(PCWSTR path, int fid);
		
		//��XML�ַ����������ŷ����
		//Ҫ������params�ڵ�
		static Envelope* Parse(PCSTR xml);
	private:
		//��XML����������ŷ����
		//Ҫ������params�ڵ�
		static Envelope* Parse(LPVOID xml);
	private:
		int _Length;
		int _Total;
		LPVOID _Memory;
		int*	_Types;
		bool* _InStates;
		int* _Offsets;
	public:
		//��ȡ��������
		int GetParamTotal();

		//��ȡ��������
		//true - ���� | false - ���
		bool GetInState(int id);
	public:
		//��������
		template<typename T>
		T Read(int id)
		{
			if(id >= _Total) throw runtime_error(_tcm_env_err_1);
			T* param = (T*)((UINT)_Memory + _Offsets[id]);
			return param[0];
		}

		//�����������ػ�bool
		template<>
		bool Read<bool>(int id)
		{
			char ret = Read<char>(id);
			return (ret == TRUE);
		}

		//д�����
		template<typename T>
		void Write(int id, T value)
		{
			if(id >= _Total) throw runtime_error(_tcm_env_err_1);
			T* param = (T*)((UINT)_Memory + _Offsets[id]);
			param[0] = value;
		}

		//д��������ػ�bool
		template<>
		void Write<bool>(int id, bool value)
		{
			Write<char>(id,value ? TRUE : FALSE);
		}

		//д�����
		//size>0ʱǳ������������
		void Write(int id, LPVOID value, int size = 0)
		{
			if(id >= _Total) throw runtime_error(_tcm_env_err_1);
			LPVOID* param = (LPVOID*)((UINT)_Memory + _Offsets[id]);
			if(size > 0)
			{
				//ǳ����
				param[0] = (LPVOID)(new BYTE[size]);
				memcpy(param[0], value, size);
			}
			else
			{
				//���ø���
				param[0] = value;
			}
		}

		//д���ַ������Զ�����
		void Write(int id, PCSTR value)
		{
			Write(id, (LPVOID)value, strlen(value) + 1);
		}

		//д����ַ������Զ�����
		void Write(int id, PCWSTR value)
		{
			Write(id, (LPVOID)value, wcslen(value) * 2 + 2);
		}

		//������ֵ���Զ�ת�͵��ַ���
		PCSTR  CastReadA(int id);
		PCWSTR CastReadW(int id);

		//���ַ����Զ�ת�͵���ֵ��д��
		void CastWriteA(int id, PCSTR value);
		void CastWriteW(int id, PCWSTR value);

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