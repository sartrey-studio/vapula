#pragma once

#include "tcm_log.h"
#include "tcm_time.h"
#include "tcm_token.h"

namespace tcm
{
	//���������
	class TCM_BRIDGE_API Context
		: public Stampable
	{
	public:
		Context();
		~Context();
	private:
		VarAOO* _TokenKey;
		Lock* _Lock;
	private:
		int	_State;
		int _ReturnCode;
		int _CtrlCode;
		float _ProgValue; //0 - 100
	private:
		Dictionary* _Extend;
	private:
		bool ValidToken(Token* token);
	public:
		//��ǩ������
		void Seal(USHORT key);

		//����Ƿ�ɷ�ǩ
		bool CanSeal();
	public:
		//��ȡ��ȷ��ʱ��
		Stopwatch* GetStopwatch();

		//��ȡ��־��
		Logger* GetLogger();
	public:
		//��ȫ���ã�����״̬
		void SetState(Token* token, int state);

		//��ȡ״̬
		int GetState();

		//��ȫ���ã����÷���ֵ
		void SetReturnCode(Token* token, int return_code);

		//��ȡ����ֵ
		int GetReturnCode();

		//��ȫ���ã����ÿ�����
		void SetCtrlCode(Token* token, int ctrl_code);

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