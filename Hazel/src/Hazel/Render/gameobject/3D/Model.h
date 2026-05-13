#pragma once


#include "Hazel/Render/Buffer.h"
#include "Hazel/Render/gameobject/GameObject.h"
#include "Hazel/Render/gameobject/Component/CMesh.h"

namespace Hazel {

	class Model : public GameObject
	{
	public:
		Model(const std::string& name);
		~Model();

		static std::vector<Ref<Model>> Creat(const std::string objPath);

	private:

		std::string m_Name;
	};
}

