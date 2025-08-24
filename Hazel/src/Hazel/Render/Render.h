#pragma once

#include "VertexArray.h"
#include "RenderAPI.h"
#include "Hazel/Render/gameobject/Camera.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Hazel/Render/gameobject/Light.h"

namespace Hazel
{
	class  Render
	{
	public:
		static void Init();

		static void BeginScene(const Camera& camera);
		static void BeginScene(const Camera& camera,const Light& light);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray);

		// events
		inline static void OnWindowResize(uint32_t width,uint32_t height) 
		{
			RenderCommand::SetViewPort(0,0,width,height);
		}

		inline static RenderAPI::API GetAPI() { return RenderCommand::GetAPI(); }
	private:
		struct  SceneData
		{
			glm::mat4 ViewMatrix;
			glm::mat4 ProjectMatrix;
			glm::vec3 view_pos;

			//Light
			glm::vec3 light_Pos;
			glm::vec3 light_amb_Intensity, light_Intensity;
			glm::vec3 light_ka, light_ks, light_kd;
		};

		static SceneData* m_SceneData;
	};

}