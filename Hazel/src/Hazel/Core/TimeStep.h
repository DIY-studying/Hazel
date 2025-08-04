#pragma once
#include "Hazel/Log.h"

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

	
}
