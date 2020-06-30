#include "pch.h"
#include "StopWatch.h"

namespace Guava
{
	StopWatch::StopWatch()
	{
		Start();
	}

	void StopWatch::Start()
	{
		m_Start = hr_clock::now();
		m_Running = true;
	}

	void StopWatch::Stop()
	{
		m_End = hr_clock::now();
		m_Running = false;
	}

	double StopWatch::GetTime()
	{
		if (m_Running)
			m_Duration = hr_clock::now() - m_Start;
		else
			m_Duration = m_End - m_Start;

		return m_Duration.count();
	}
}
