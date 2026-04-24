#pragma once
#include "Hazel/Render/gameobject/GameObject.h"


namespace Hazel
{
	class Light : public GameObject
	{
	public:
		Light(const glm::vec3 pos);
		~Light();

		void Submit(const Ref<Shader>& shader) override;

		void SetPos(const glm::vec3& pos) { m_pos = pos; };

		const glm::vec3& GetKa()	const { return m_ka; };
		const glm::vec3& GetKs()	const { return m_ks; };
		const glm::vec3& GetKd()	const { return m_kd; };
		const glm::vec3& GetPos() const { return m_pos; };

		const glm::vec3& GetAmbLightIntensity()	const	{ return m_amb_light_Intensity; };
		const glm::vec3& GetLightIntensity()			const	{ return m_light_Intensity; }

		glm::vec3& GetKa() { return m_ka; };
		glm::vec3& GetKs() { return m_ks; };
		glm::vec3& GetKd() { return m_kd; };
		glm::vec3& GetPos() { return m_pos; };

		glm::vec3& GetAmbLightIntensity() { return m_amb_light_Intensity; };
		glm::vec3& GetLightIntensity() { return m_light_Intensity; };

	private:
		glm::vec3 m_amb_light_Intensity,m_light_Intensity;
		glm::vec3 m_ka, m_ks, m_kd;
	};
}
