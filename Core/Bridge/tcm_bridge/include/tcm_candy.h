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
		BYTE _A; //Max Decay Times
		UINT16 _B; //Blank Time (ms)
		BYTE _C; //Max Blank Times
	};

	//һ���Ը�ֵ��Assignable Only Once
	class VarAOO : Uncopiable
	{
	public:
		VarAOO();
		~VarAOO();
	private:
		LPVOID _Value;
		LPVOID _Token;
	private:
		void _Set(LPVOID data, UINT len);
	public:
		bool CanSet();

		template<typename T>
		void Set(T* value)
		{
			if(_Token == NULL) return;
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
		typedef vector<PCWSTR>::iterator iter;
		Lock* _Lock;
		vector<PCWSTR> _Keys;
		vector<PCWSTR> _Values;
	public:
		//��ȡ��¼��
		int GetCount();

		//����¼�Ƿ����
		bool Contain(PCWSTR key);

		//��Ӽ�¼
		bool Add(PCWSTR key, PCWSTR value);

		//�Ƴ���¼
		bool Remove(PCWSTR key);

		//��ȡָ�������ļ�
		PCWSTR GetKey(UINT id);

		//��ȡָ��������ֵ
		PCWSTR GetValue(UINT id);

		//����ֵ�
		void Clear();

		//����Key��ѯ��¼��Value
		PCWSTR Find(PCWSTR key);
	};
}