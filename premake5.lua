workspace "Hazel"
   architecture "x64"
   
   configurations
   {
    "Debug",
    "Release",
    "Dist",
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
   location "Hazel"
   kind "SharedLib"
   language "c++"
   buildoptions { "/utf-8" }

   targetdir ("%{prj.name}/bin/"..outputdir.."/%{prj.name}")
   objdir ("%{prj.name}/bin-int/"..outputdir.."/%{prj.name}")

   pchheader "hzpch.h"
   pchsource "Hazel/src/hzpch.cpp"

   files
   {
     "%{prj.name}/src/**.h",
     "%{prj.name}/src/**.cpp"
   }

   includedirs
   {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include"
   }

   filter "system:windows"
		cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

   defines
   {
    "HZ_PLATFORM_WINDOWS",
    "HZ_BUILD_DLL"
   }

   postbuildcommands
   {
    ("{COPYFILE} %{cfg.buildtarget.relpath} bin/"..outputdir.. "/Sandbox/"),
   }
   filter "configurations:Debug"
        defines {"HZ_DEBUG"}
        symbols "On"

   filter "configurations:Release"
        defines {"HZ_REALEASE"}
        optimize "On"

   filter "configurations:Dist"
        defines {"HZ_DIST"}        
        optimize "On"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "c++"
   buildoptions { "/utf-8" }

   filter "system:windows"
		cppdialect "c++17"
        staticruntime "On"
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
    "Hazel/src"
   }


   links
   {
    "Hazel"
   }
 
   defines
   {
    "HZ_PLATFORM_WINDOWS"
   }

    filter "configurations:Debug"
        defines {"HZ_DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"HZ_REALEASE"}
        optimize "On"

    filter "configurations:Dist"
        defines {"HZ_DIST"}        
        optimize "On"


   