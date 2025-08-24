#include "hzpch.h"
#include "Light.h"

namespace Hazel
{
	Light::Light(const glm::vec3 pos)
		:m_Pos(pos), m_ka(0.005,0.005,0.005), m_kd(0.60,0.5,0.4),m_ks(0.7937, 0.7937, 0.7937),
		m_amb_light_Intensity(10,10,10),m_light_Intensity(500,500,500)
	{
		
	}

	Light::~Light()
	{

	}

}

