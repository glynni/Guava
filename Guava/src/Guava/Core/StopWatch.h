#pragma once
namespace Guava
{
	class StopWatch
	{
		using time_type = double;

	public:

		StopWatch();

		void Start();
		void Stop();

		time_type GetTime();

	private:

		using Clock = std::chrono::high_resolution_clock;

		Clock::time_point					m_Start, m_End;
		std::chrono::duration<time_type>	m_Duration;
		bool								m_Running;
	};
}

