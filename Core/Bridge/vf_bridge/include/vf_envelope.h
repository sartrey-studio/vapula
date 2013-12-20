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
		inline bool _AssertId(int id, Envelope* env = null)
		{
			if(id < 1)
				return false;
			if(env == null)
				return id <= _Total;
			else
				return id <= env->_Total;
		}

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
		//��ȡ�ڴ��
		//��ѡ�Ƿ���
		object ReadObject(int id, uint32& size, bool copy = false);

		//д���ڴ��
		//���������ڴ���С����ѡ�Ƿ���
		void WriteObject(int id, object value, uint32 size, bool copy = false);

	public:
		//������������
		//��ѡ�Ƿ���
		template<typename T>
		T* Read(int id, uint32& length, bool copy = false)
		{
			if(!_AssertId(id))
				throw invalid_argument(_vf_err_1);
			int idx = id - 1;
			length = _Lengths[idx];
			if(!copy)
				return (T*)(_Addrs[idx]);
			T* data = new T[length];
			memcpy(data, (object)(_Addrs[idx]), length * sizeof(T));
			return data;
		}

		//��������ֵ
		template<typename T>
		T Read(int id)
		{
			if(!_AssertId(id))
				throw invalid_argument(_vf_err_1);
			int idx = id - 1;
			T* param = (T*)(_Addrs[idx]);
			return param[0];
		}

		//д���������
		template<typename T>
		void Write(int id, T* value, uint32 length)
		{
			if(!_AssertId(id))
				throw invalid_argument(_vf_err_1);
			int idx = id - 1;
			//��Դ���ݲ�����
			if(value == _Addrs[idx])
				return;
			//�������ʾ�������
			if(value == null)
			{
				delete (object)(_Addrs[idx]);
				return;
			}
			//��Դ���ݸ���
			if(_Lengths[idx] != length)
			{
				if(_Addrs[idx] != 0)
					delete (object)(_Addrs[idx]);
				_Addrs[idx] = new T[length];
				_Lengths[idx] = length;
			}
			memcpy(_Addrs[idx], value, length * sizeof(T));
		}

		//д�����ֵ
		template<typename T>
		void Write(int id, T value)
		{
			if(!_AssertId(id))
				throw invalid_argument(_vf_err_1);
			int idx = id - 1;
			object data = null;
			if(_Lengths[idx] != 1)
			{
				if(_Addrs[idx] != 0)
					delete (object)(_Addrs[idx]);
				data = new T[1];
				_Lengths[idx] = 1;
			}
			T* param = (T*)(data);
			param[0] = value;
			_Addrs[idx] = (uint32)data;
		}

	public:
		//�ýӿڲ������ڴ��
		template<>
		object Read<object>(int id)
		{
			throw new bad_exception(_vf_err_2);
		}

		//�ýӿڲ������ڴ��
		template<>
		object* Read<object>(int id, uint32& length, bool copy)
		{
			throw new bad_exception(_vf_err_2);
		}

		//�ýӿڲ������ڴ��
		template<>
		void Write<object>(int id, object* value, uint32 length)
		{
			throw new bad_exception(_vf_err_2);
		}

		//�ýӿڲ������ڴ��
		template<>
		void Write<object>(int id, object value)
		{
			throw new bad_exception(_vf_err_2);
		}

	public:
		//�ػ�8λ�ֽ��ַ�������������ֵ
		template<>
		cstr8 Read<cstr8>(int id)
		{
			uint32 size = 0;
			cstr8 tmp = (cstr8)ReadObject(id, size, true);
			return s8;
		}

		//�ػ�16λ�ֽ��ַ�������������ֵ
		template<>
		cstr16 Read<cstr16>(int id)
		{
			uint32 size = 0;
			cstr8 tmp = (cstr8)ReadObject(id, size, false);
			cstr16 s16 = str::ToCh16(s8, _vf_msg_cp);
			return s16;
		}

		//�ػ�8λ�ֽ��ַ�����д�����ֵ
		template<>
		void Write<cstr8>(int id, cstr8 value)
		{
			WriteObject(id, value, strlen(value) + 1, true);
		}

		//�ػ�16λ�ֽ��ַ�����д�����ֵ
		template<>
		void Write<cstr16>(int id, cstr16 value)
		{
			cstr8 s8 = str::ToCh8(value, _vf_msg_cp);
			Write(id, s8);
			delete s8;
		}

	public:
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