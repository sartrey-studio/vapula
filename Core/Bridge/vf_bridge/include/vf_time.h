#pragma once

#include "vf_candy.h"

namespace vapula
{
	//��ʱ��
	class VAPULA_API Stopwatch : Uncopiable
	{
	public:
		Stopwatch();
		~Stopwatch();
	private:
		LARGE_INTEGER _F, _T1, _T2;
	public:
		void Start();
		void Stop();
		double GetElapsedTime();
	};
}