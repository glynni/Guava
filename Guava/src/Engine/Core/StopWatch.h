#pragma once
namespace Guava
{
	class StopWatch
	{

	public:

		StopWatch();

		void Start();
		void Stop();

		double GetTime();

	private:

		time_point	m_Start, m_End;
		duration	m_Duration;
		bool		m_Running;
	};
}

