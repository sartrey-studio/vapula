#pragma once

#include "vf_candy.h"

namespace vapula
{
	//���������
	class VAPULA_API Context
	{
	public:
		friend class Invoker;
	public:
		Context();
		~Context();
	private:
		Lock* _Lock;
	private:
		int	_State;
		int _ReturnCode;
		int _CtrlCode;
		float _ProgValue; //0 - 100
	private:
		//��ȫ���ã�����״̬
		void SetState(int state);

		//��ȫ���ã����÷���ֵ
		void SetReturnCode(int return_code);

		//��ȫ���ã����ÿ�����
		void SetCtrlCode(int ctrl_code);
	public:
		//��ȡ״̬
		int GetState();

		//��ȡ����ֵ
		int GetReturnCode();

		//��ȡ������
		int GetCtrlCode();

		//��Ӧ������
		void ReplyCtrlCode();

		//���ý���
		void SetProgress(float value);

		//��ȡ����
		float GetProgress();
	};
}