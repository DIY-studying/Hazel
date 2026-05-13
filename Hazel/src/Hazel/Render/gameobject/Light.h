#pragma once
#include "Hazel/Render/gameobject/GameObject.h"


namespace Hazel
{
	class Light : public GameObject
	{
	public:
		Light();
		~Light();

		void Submit(const Ref<Shader>& shader) override;

		const Eigen::Vector3f& GetKa()	const { return m_ka; };
		const Eigen::Vector3f& GetKs()	const { return m_ks; };
		const Eigen::Vector3f& GetKd()	const { return m_kd; };


		const Eigen::Vector3f& GetAmbLightIntensity()	const	{ return m_amb_light_Intensity; };
		const Eigen::Vector3f& GetLightIntensity()	const	{ return m_light_Intensity; }

		Eigen::Vector3f& GetKa() { return m_ka; };
		Eigen::Vector3f& GetKs() { return m_ks; };
		Eigen::Vector3f& GetKd() { return m_kd; };

		Eigen::Vector3f& GetAmbLightIntensity() { return m_amb_light_Intensity; };
		Eigen::Vector3f& GetLightIntensity() { return m_light_Intensity; };

	private:
		Eigen::Vector3f m_amb_light_Intensity,m_light_Intensity;
		Eigen::Vector3f m_ka, m_ks, m_kd;
	};
}
