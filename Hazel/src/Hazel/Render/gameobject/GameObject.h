#pragma once

#include "hzpch.h"
#include <Hazel/Render/Shader.h>
#include "Component/Component.h"
#include "Component/CMesh.h"
#include "Component/CTransform.h"

namespace Hazel {

	typedef std::tuple<
		CMesh,
		CTransform
	> ComponentTuple;

	class GameObject
	{
	public:
		virtual void Submit(const Ref<Shader>& shader) {};

		inline void SetPos(const Eigen::Vector3f& pos)
		{
			CTransform& transform = GetComponent<CTransform>();
			transform.pos = pos;
		}

		inline const Eigen::Vector3f& GetPos() const
		{
			const CTransform& transform = GetComponent<CTransform>();
			return transform.pos;
		}

		inline void SetAngle(const Eigen::Vector3f& angle)
		{
			CTransform& transform = GetComponent<CTransform>();
			transform.rotate = angle*PI/180.0f;
		}

		template<typename T>
		T& GetComponent() { return std::get<T>(m_components); };

		template<typename T>
		const T& GetComponent() const { return std::get<T>(m_components); };

		template<class T, typename... TArgs>
		T& AddComponent(TArgs &&... mArgs) {
			auto& component = GetComponent<T>();
			component = T(std::forward<TArgs>(mArgs) ...);
			component.has = true;
			return component;
		}

		template<typename T>
		const bool HasComponent() const { return GetComponent<T>().has; };

		template<typename T>
		const void RemoveComponent() const {
			auto& component = GetComponent<T>();
			component=T();
			component.has = false;
		};

		inline Eigen::Matrix4f GetModelMatrix() const
		{
			const CTransform& ctransform = GetComponent<CTransform>();
			Eigen::Matrix4f model, scale,rotate;

			Eigen::Affine3f transform = Eigen::Affine3f::Identity();

	
			transform.scale(ctransform.scale);

			transform.prerotate(Eigen::AngleAxisf(ctransform.rotate.x(), Eigen::Vector3f::UnitX()));
			transform.prerotate(Eigen::AngleAxisf(ctransform.rotate.y(), Eigen::Vector3f::UnitY()));
			transform.prerotate(Eigen::AngleAxisf(ctransform.rotate.z(), Eigen::Vector3f::UnitZ()));

			transform.translate(ctransform.pos); 
			
			return transform.matrix();
		}

		inline Eigen::Matrix4f GetRotationMatrix() const
		{
			const CTransform& ctransform = GetComponent<CTransform>();

			Eigen::Affine3f transform = Eigen::Affine3f::Identity();

			transform.prerotate(Eigen::AngleAxisf(ctransform.rotate.x(), Eigen::Vector3f::UnitX()));
			transform.prerotate(Eigen::AngleAxisf(ctransform.rotate.y(), Eigen::Vector3f::UnitY()));
			transform.prerotate(Eigen::AngleAxisf(ctransform.rotate.z(), Eigen::Vector3f::UnitZ()));

			return  transform.matrix();
		}

		inline Eigen::Matrix4f GetTranslateMatrix() const
		{
			const CTransform& ctransform = GetComponent<CTransform>();

			Eigen::Affine3f transform = Eigen::Affine3f::Identity();
			transform.translate(ctransform.pos);

			return transform.matrix();
		}

	protected:
		GameObject() { AddComponent<CTransform>(); };
		~GameObject() {};
	protected:
		ComponentTuple m_components;
	};
}



