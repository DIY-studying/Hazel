workspace "Hazel"
   architecture "x64"
   startproject "Sandbox"
   
   configurations
   {
    "Debug",
    "Release",
    "Dist",
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories ralative to root folder(solution directory)
IncludeDir={}
IncludeDir["GLFW"]="Hazel/vendor/GLFW/include"
IncludeDir["Glad"]="Hazel/vendor/glad/include"
IncludeDir["ImGui"]="Hazel/vendor/imgui"
IncludeDir["glm"]="Hazel/vendor/glm"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"

project "Hazel"
   location "Hazel"
   kind "StaticLib"
   language "c++"
   staticruntime "on"
   cppdialect "c++17"
   buildoptions { "/utf-8" }

   targetdir ("%{prj.name}/bin/"..outputdir.."/%{prj.name}")
   objdir ("%{prj.name}/bin-int/"..outputdir.."/%{prj.name}")

   pchheader "hzpch.h"
   pchsource "Hazel/src/hzpch.cpp"

   files
   {
     "%{prj.name}/src/**.h",
     "%{prj.name}/src/**.cpp",
     -- include glm source file
     "%{prj.name}/vendor/glm/glm/**.hpp",
     "%{prj.name}/vendor/glm/glm/**.inl",
   }

   defines
   {
     -- trust deprecated CRT funs disable warnings --
     "_CRT_SECURE_NO_WARNINGS",
     -- spdlog warnings solved --
     "FMT_USE_CONSTEXPR",
   }

   includedirs
   {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}",
    "%{IncludeDir.ImGui}/backends",
    "%{IncludeDir.glm}"
   }
   links
   {
    "GLFW",
    "Glad",
    "ImGui",
    "opengl32.lib",
   }

   filter "system:windows"
        systemversion "latest"

   defines
   {
    "HZ_PLATFORM_WINDOWS",
    "HZ_BUILD_DLL",
    -- diable GLFW OpneGL header
    "GLFW_INCLUDE_NONE",
    -- tell ImGui use custom loader(glad)
    "IMGUI_IMPL_OPENGL_LOADER_CUSTOM", 
   }

   filter "configurations:Debug"
        defines {"HZ_DEBUG"}
        runtime "Debug"
        symbols "on"

    defines
    {
        "HZ_DEBUG"
    }

   filter "configurations:Release"
        defines {"HZ_REALEASE"}
        runtime "Release"
        optimize "on"

   filter "configurations:Dist"
        defines {"HZ_DIST"}        
        runtime "Release"
        optimize "on"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "c++"
   staticruntime "on"
   cppdialect "c++17"
   buildoptions { "/utf-8" }


   filter "system:windows"
        systemversion "latest"

   files
   {
    "%{prj.name}/src/**.h",
     "%{prj.name}/src/**.cpp"
   }

   targetdir ("Hazel/bin/"..outputdir.."/%{prj.name}")
   objdir ("Hazel/bin-int/"..outputdir.."/%{prj.name}")

   includedirs
   {
    "Hazel/vendor/spdlog/include",
    "Hazel/src",
    "%{IncludeDir.glm}",
    "Hazel/vendor"
   }


   links
   {
    "Hazel",
   }
 
   defines
   {
    "HZ_PLATFORM_WINDOWS",
   }

    filter "configurations:Debug"
        defines {"HZ_DEBUG"}
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines {"HZ_REALEASE"}
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines {"HZ_DIST"}        
        runtime "Release"
        optimize "on"


   