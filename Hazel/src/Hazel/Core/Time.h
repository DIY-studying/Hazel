#pragma once
#include "Hazel/Log.h"
#include "chrono"

namespace Hazel
{
	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f) :m_Time(time) { }
		
		operator float() { return m_Time; }

		float GetScend() const { return m_Time; }
		float GetMillSecond() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

	template <typename fn>
	class Timer
	{
	public:
		Timer(const char* name,fn&& fuc):m_name(name),m_fuc(fuc)
		{
			m_Stop = false;
			start = std::chrono::high_resolution_clock::now();
		}
		~Timer()
		{
			if (!m_Stop)
				Stop();
		}

		inline void Stop() const
		{
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = start - end;
			m_fuc({ m_name,duration });
		}
	private:
		std::chrono::time_point<std::chrono::steady_clock> start;
		bool m_Stop;
		fn m_fuc;
		const char* m_name;
	};
}
