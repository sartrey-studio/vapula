#pragma once

#include "tcm_base.h"

#define TCM_MMF_DATASIZE 4096
#define TCM_MMF_PRTCSIZE 32

namespace tcm
{
	//�ŵ���־��ʼ����
	enum PipeFlag
	{
		TCM_PIPE_GLOBAL = 0,
		TCM_PIPE_S2C = 12,
		TCM_PIPE_C2S = 22
	};

	//ȫ˫��������ŵ�
	class TCM_BRIDGE_API Pipe
	{
	public:
		Pipe();
		~Pipe();
	private:
		int _DataVol;
		PCWSTR _Id;
		HANDLE _Mapping;
		LPVOID _Data;
 		bool _IsServer;
	private:
		bool CreateMMF(UINT vol);
		void CloseMMF();
		bool BeginUpdate();
		void EndUpdate();
	public:
		//��ȡ�ŵ���ʶ;
		PCWSTR GetPipeId();

		//��ȡ��������
		int GetDataVol();
		
		//��������������ָ���ŵ�����
		bool Listen(UINT vol = TCM_MMF_DATASIZE);

		//����ָ�����ŵ�
		bool Connect(PCWSTR pid);

		//��ȡ���ݱ�־
		BYTE GetFlag(int action);

		//�������ݱ�־
		void SetFlag(int action, int value = 0);

		//д������
		//��ָ��λ�õ�ָ�����ȵ�����д�����ݶ�
		//�������ݲ�����Ƿ��Ѷ�
		void Write(LPVOID value, UINT size);

		//��ȡ����
		//�����ݸ��Ƶ�ָ����λ��
		//��ȡ���ݲ�����Ƿ���
		void Read(LPVOID data);

		//��ȡ�ɶ���Ч���ݵĴ�С
		UINT GetReadSize();

		//�ȴ���ȡ����
		LPVOID WaitRead(int time = 0);

		//�ȴ������Ѷ�
		bool BeenRead(int time = 0);
	};
}