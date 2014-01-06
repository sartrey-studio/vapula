#pragma once

#pragma warning(disable:4100)

#include "vf_base.h"

namespace vapula
{
	//�����ŷ�
	class VAPULA_API Envelope
	{
	private:
		Envelope(int32 total);
	public:
		~Envelope();

	public:
		//��XML�ַ����������ŷ����
		//Ҫ������params�ڵ�
		static Envelope* Parse(cstr8 xml);

		//��XML����������ŷ����
		//Ҫ������params�ڵ�
		static Envelope* Parse(object xml);

	private:
		int32 _Total; //��������
		int8* _Types; //��������
		int8* _Modes; //����ģʽ
		uint32* _Addrs; //�ڴ��ַ��
		uint32* _Lengths; //�������ȱ�

	private:
		bool _AssertId(int id, Envelope* env = null);
		object _Read(int idx, uint32 size, bool copy);
		void _Write(int idx, object value, uint32 size, bool clear, bool copy);

	public:
		//��ȡ��������
		int32 GetTotal();

		//��ȡָ��������ģʽ
		int8 GetMode(int id);

		//��ȡָ������������
		int8 GetType(int id);

		//��ȡָ�������ĳ���
		uint32 GetLength(int id);

	public:
		Envelope* Copy();

	public:
		//��ȡ�ڴ��
		//��ѡ�Ƿ��ƣ�Ĭ�ϲ�����
		object ReadObject(int id, uint32* size = null, bool copy = false);

		//д���ڴ��
		//��ѡ�Ƿ��ƣ�Ĭ�ϲ�����
		void WriteObject(int id, object value, uint32 size, bool copy = false);

	public:
		//������������
		//��ѡ�Ƿ��ƣ�Ĭ�ϲ�����
		template<typename T>
		T* ReadArray(int id, uint32* length = null, bool copy = false)
		{
			if(!_AssertId(id))
				throw invalid_argument(_vf_err_1);
			int idx = id - 1;
			if(length != null)
				*length = _Lengths[idx];
			T* data = (T*)_Read(idx, _Lengths[idx] * sizeof(T), copy);
			return data;
		}

		//��������ֵ
		template<typename T>
		T ReadValue(int id)
		{
			T* data = ReadArray<T>(id);
			return data[0];
		}

		//д���������
		template<typename T>
		void WriteArray(int id, T* value, uint32 length, bool copy = false)
		{
			if(!_AssertId(id))
				throw invalid_argument(_vf_err_1);
			int idx = id - 1;

			bool clear = (value != null && _Lengths[idx] != length);
			_Write(idx, value, length * sizeof(T), clear, copy);
			_Lengths[idx] = length;
		}

		//д�����ֵ
		template<typename T>
		void WriteValue(int id, T value)
		{
			T tmp_value = value;
			WriteArray(id, &tmp_value, 1, true);
		}

	public:
		//�ػ�8λ�ֽ��ַ�������������ֵ
		cstr8 ReadCh8(int id);

		//�ػ�16λ�ֽ��ַ�������������ֵ
		cstr16 ReadCh16(int id);

		//�ػ�8λ�ֽ��ַ�����д�����ֵ
		void WriteCh8(int id, cstr8 value);
		
		//�ػ�16λ�ֽ��ַ�����д�����ֵ
		void WriteCh16(int id, cstr16 value);

	public:
		//������ֵ���Զ�ת�͵��ַ���
		cstr8 CastReadValue(int id);

		//���ַ����Զ�ת�͵���ֵ��д��
		void CastWriteValue(int id, cstr8 value);

		//Ͷ�ݵ�ǰ�ŷ⵽Ŀ��
		void Deliver(Envelope* who, int from, int to);

		//����Ӧת��Ͷ�ݵ�ǰ�ŷ⵽Ŀ��
		void CastDeliver(Envelope* who, int from, int to);
	};
}