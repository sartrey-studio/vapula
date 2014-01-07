#pragma once

#include "vf_utility.h"

namespace vapula
{
	//���������
	class VAPULA_API Context
	{
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
	public:
		//��ȫ���ã�����״̬
		void SetState(int state);

		//��ȡ״̬
		int GetState();

		//��ȫ���ã����÷���ֵ
		void SetReturnCode(int return_code);

		//��ȡ����ֵ
		int GetReturnCode();

		//��ȫ���ã����ÿ�����
		void SetCtrlCode(int ctrl_code);

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