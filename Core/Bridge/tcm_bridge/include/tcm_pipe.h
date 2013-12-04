#pragma once

#include "tcm_base.h"

#define TCM_MMF_DATASIZE 4096
#define TCM_MMF_PRTCSIZE 32

namespace tcm
{
	//ȫ˫��������ŵ�
	class TCM_BRIDGE_API Pipe
	{
	public:
		Pipe();
		~Pipe();
	private:
		int _DataVol;
		str _Id;
		HANDLE _Mapping;
		object _Data;
 		bool _IsServer;
	private:
		bool CreateMMF(UINT vol);
		void CloseMMF();
		bool BeginUpdate();
		void EndUpdate();
	public:
		//��ȡ�ŵ���ʶ;
		str GetPipeId();

		//��ȡ��������
		int GetDataVol();
		
		//��������������ָ���ŵ�����
		bool Listen(UINT vol = TCM_MMF_DATASIZE);

		//����ָ�����ŵ�
		bool Connect(str pid);

		//�������Ϣ
		bool HasNewData();

		//д������
		void Write(strw data);

		//��ȡ����
		//ͬʱ���Ի�ȡ���ݱ�ʶ
		strw Read(int* id);
	private:
		//��ȡ���ݱ�־
		BYTE GetFlag(int action);

		//�������ݱ�־
		void SetFlag(int action, int value = 0);

		//��ȡ�ɶ���Ч���ݵĴ�С
		UINT GetReadSize();

		//�ȴ���ȡ����
		LPVOID WaitRead(int time = 0);

		//�ȴ������Ѷ�
		bool BeenRead(int time = 0);
	};
}