#include "hzpch.h"
#include "Light.h"
#include <Hazel/Render/Shader.h>

namespace Hazel
{
	Light::Light()
		:GameObject(), m_ka(0.005,0.005,0.005), m_kd(0.60,0.5,0.4),m_ks(0.7937, 0.7937, 0.7937),
		m_amb_light_Intensity(10,10,10),m_light_Intensity(500,500,500)
	{
		
	}

	Light::~Light()
	{

	}

	void Light::Submit(const Ref<Shader>& shader)
	{
		shader->SetFloat3("u_light_pos", GetPos());
		shader->SetFloat3("u_light_ka", m_ka);
		shader->SetFloat3("u_light_kd", m_kd);
		shader->SetFloat3("u_light_ks", m_ks);
		shader->SetFloat3("u_light_Instensity", m_light_Intensity);
		shader->SetFloat3("u_light_amb_instensity", m_amb_light_Intensity);
	}
}

