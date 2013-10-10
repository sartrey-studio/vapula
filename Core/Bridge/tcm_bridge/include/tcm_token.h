#pragma once

#include "tcm_candy.h"

namespace tcm
{
	//֧�����Ʒ�ǩ����
	class TCM_BRIDGE_API Stampable
	{
	public:
		Stampable();
		virtual ~Stampable();
	public:
		virtual bool CanSeal() = 0;
		virtual void Seal(USHORT key) = 0;
	};

	//��������
	class TCM_BRIDGE_API Token : Uncopiable
	{
	private:
		Token();
	public:
		~Token();
	public:
		static Token* Stamp(Stampable* target);
	private:
		LPVOID _A;
		USHORT _B;
	public:
		bool Match(USHORT key);
	};
}