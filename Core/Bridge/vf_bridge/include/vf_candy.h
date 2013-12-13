#pragma once
#pragma warning(disable:4275)

#include "vf_base.h"

namespace vapula
{
	//���ɸ���
	class Uncopiable
	{
	protected:
		Uncopiable();
		~Uncopiable();
	private:
		Uncopiable(const Uncopiable&);
		Uncopiable& operator=(const Uncopiable&);
	};

	//������
	class VAPULA_API Lock : Uncopiable
	{
	public:
		Lock();
		~Lock();
	private:
		long* _Core; //TRUE - Lock , FALSE - Unlock
		int _A; //Max Decay Times
		int _B; //Blank Time (ms)
		int _C; //Max Blank Times
	public:
		//�����
		//�ʺ�����������
		bool Enter();

		//�����
		//�ʺ�����������
		bool EnterEx();

		//�ͷ���
		void Leave();

		//���ò���
		void Set(int a, int b, int c);
	};

	//һ���Ը�ֵ
	class VarAO : Uncopiable
	{
	public:
		VarAO();
		~VarAO();
	private:
		object _Value;
		object _Seal;
	public:
		bool CanSet();

		void Set(object value, uint32 size);

		object Get();
	};

	//��־
	class VAPULA_API Flag : Uncopiable
	{
	public:
		Flag();
		~Flag();
	private:
		Lock* _Lock;
		int _Value;
	public:
		//ʹ�ܱ�־
		void Enable(int flag);

		//ʧ�ܱ�־
		void Disable(int flag);

		//У���־λ
		bool Valid(int flag);
	};

	//�ֵ�
	class VAPULA_API Dict : Uncopiable
	{
	public:
		Dict();
		~Dict();
	private:
		typedef vector<cstr8>::iterator iter;
		Lock* _Lock;
		vector<cstr8> _Keys;
		vector<cstr8> _Values;
	public:
		//��ȡ��¼��
		int GetCount();

		//����¼�Ƿ����
		bool Contain(cstr8 key);

		//��Ӽ�¼
		bool Add(cstr8 key, cstr8 value);

		//�Ƴ���¼
		bool Remove(cstr8 key);

		//��ȡָ�������ļ�
		cstr8 GetKey(uint32 id);

		//��ȡָ��������ֵ
		cstr8 GetValue(uint32 id);

		//����ֵ�
		void Clear();

		//����Key��ѯ��¼��Value
		cstr8 Find(cstr8 key);
	};
}