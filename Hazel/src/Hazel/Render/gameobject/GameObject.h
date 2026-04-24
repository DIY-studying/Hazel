#pragma once

#include "hzpch.h"
#include <Hazel/Render/Shader.h>


namespace Hazel {
	class GameObject
	{
	public:
		virtual void Submit(const Ref<Shader>& shader) {};

	protected:
		GameObject(const glm::vec3& pos) :m_pos(pos){};
		~GameObject() {};
	protected:
		glm::vec3 m_pos = glm::vec3();
	};
}



