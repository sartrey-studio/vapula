#pragma once
#pragma warning(disable:4275) //���ü̳�δ��������

#include "tcm_base.h"

namespace tcm
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
	class TCM_BRIDGE_API Lock : Uncopiable
	{
	public:
		Lock();
		~Lock();
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
	private:
		long* _Core; //TRUE - Lock , FALSE - Unlock
		int _A; //Max Decay Times
		int _B; //Blank Time (ms)
		int _C; //Max Blank Times
	};

	//һ���Ը�ֵ��Assignable Only Once
	class VarAOO : Uncopiable
	{
	public:
		VarAOO();
		~VarAOO();
	private:
		object _Value;
		object _Token;
	private:
		void _Set(object data, uint32 len);
	public:
		bool CanSet();

		template<typename T>
		void Set(T* value)
		{
			if(_Token == null) return;
			_Set(value, sizeof(T));
		}

		template<typename T>
		T* Get()
		{
			return (T*)_Value;
		}
	};

	//��־
	class TCM_BRIDGE_API Flag : Uncopiable
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
	class TCM_BRIDGE_API Dictionary : Uncopiable
	{
	public:
		Dictionary();
		~Dictionary();
	private:
		typedef vector<strw>::iterator iter;
		Lock* _Lock;
		vector<strw> _Keys;
		vector<strw> _Values;
	public:
		//��ȡ��¼��
		int GetCount();

		//����¼�Ƿ����
		bool Contain(strw key);

		//��Ӽ�¼
		bool Add(strw key, strw value);

		//�Ƴ���¼
		bool Remove(strw key);

		//��ȡָ�������ļ�
		strw GetKey(uint32 id);

		//��ȡָ��������ֵ
		strw GetValue(uint32 id);

		//����ֵ�
		void Clear();

		//����Key��ѯ��¼��Value
		strw Find(strw key);
	};
}