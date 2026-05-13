#pragma once

#include "hzpch.h"
#include "Component.h"

namespace Hazel
{
	class CTransform :public Component
	{
	public:
		CTransform() : pos(0, 0, 0), scale(1, 1, 1), rotate(0, 0, 0) {}
		~CTransform() {};

	public:
		Eigen::Vector3f pos;
		Eigen::Vector3f scale;
		Eigen::Vector3f rotate;
	};
}