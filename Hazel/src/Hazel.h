#pragma once

// For use by Hazel applications

#include "Hazel/Application.h"
#include "Hazel/Layer.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/OrthoCameraController.h"

//---Input----------------------------
#include "Hazel/Input/Input.h"
#include "Hazel/Input/KeyCode.h"
#include "Hazel/Input/MouseButtonCode.h"

//---Render--------------------------
#include "Hazel/Render/Shader.h"
#include "Hazel/Render/Texture.h"
#include "Hazel/Render/Buffer.h"
#include "Hazel/Render/VertexArray.h"
#include "Hazel/Render/gameobject/Camera.h"
#include "Hazel/Render/gameobject/Light.h"
#include "Hazel/Render/Render.h"
#include "Hazel/Render/RenderCommand.h"
//------------------------------------------

//---component----------------------
#include "Hazel/Render/gameobject/Component/CMesh.h"
#include "Hazel/Render/gameobject/Component/CTransform.h"

//---component----------------------

//---profile--------------------------
#include "Hazel/Debug/Instrumentor.h"


//---entry point-------------------
#include"Hazel/EntryPoint.h"
//------------------------------------------