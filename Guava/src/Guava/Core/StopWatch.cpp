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
		m_Start = Clock::now();
		m_Running = true;
	}

	void StopWatch::Stop()
	{
		m_End = Clock::now();
		m_Running = false;
	}

	StopWatch::time_type StopWatch::GetTime()
	{
		if (m_Running)
			m_Duration = Clock::now() - m_Start;
		else
			m_Duration = m_End - m_Start;

		return m_Duration.count();
	}
}
