#pragma once

#include "VertexArray.h"
#include "RenderAPI.h"
#include "OrthoCamera.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace Hazel
{
	class  Render
	{
	public:
		static void Init();
		static void BeginScene(OrthoCamera& orthoCamera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray);

		inline static RenderAPI::API GetAPI() { return RenderCommand::GetAPI(); }
	private:
		struct  SceneData
		{
			glm::mat4 ViewProjectMatrix;
		};

		static SceneData* m_SceneData;
	};

}