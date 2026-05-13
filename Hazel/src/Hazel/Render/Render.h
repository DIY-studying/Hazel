#pragma once

#include "VertexArray.h"
#include "RenderAPI.h"
#include "Hazel/Render/gameobject/Camera.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Hazel/Render/gameobject/Light.h"
#include "gameobject/Component/Component.h"

namespace Hazel
{
	// global data
	struct  SceneData
	{
		std::vector<Ref<GameObject>> gameObjects;

		Eigen::Matrix4f projectMatrix;
		Eigen::Matrix4f viewMatrix;

	};


	class  Render
	{
	public:
		static void Init();

		static void BeginScene(const Ref<Camera>& camera, const Ref<Shader>& shader);
		static void EndScene();

		static void Submit(const std::vector<Ref<GameObject>>& gameObjes);

		static void Flush();

		static Ref<SceneData> GetSceneData() ;

		// events
		inline static void OnWindowResize(uint32_t width, uint32_t height)
		{
			RenderCommand::SetViewPort(0, 0, width, height);
		};

		inline static RenderAPI::API GetAPI() { return RenderCommand::GetAPI(); }

	private:
		static  Ref<SceneData> m_SceneData;
		
	};

}