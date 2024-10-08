workspace "hippo"
  startproject "hippoeditor"
  architecture "x64"
  configurations
  {
    "Debug",
    "Release"
  }

target_dir = "bin/%{cfg.buildcfg}/%{prj.name}"
object_dir = "obj/%{cfg.buildcfg}/%{prj.name}"

externals = {}
externals["sdl2"] = "external/sdl2"
externals["spdlog"] = "external/spdlog"
externals["glad"] = "external/glad"

-- process glad before anything else
include "external/glad"

project "hippo"
  location "hippo"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  targetdir(target_dir)
  objdir(object_dir)
  files 
  {
    "%{prj.name}/include/**.h",
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }
  externalincludedirs
  {
    "%{prj.name}/include",
    "%{prj.name}/include/hippo",
    "%{prj.name}/src",
    "%{externals.sdl2}/include",
    "%{externals.spdlog}/include",
    "%{externals.glad}/include"
  }
  flags
  {
    "FatalWarnings"
  }
  defines 
  {
    "GLFW_INCLUDE_NONE",  -- ensures glad doesn't include glfw
  }
  filter { "system:windows", "configurations:*" }
    systemversion "latest"
    defines 
    {
      "HIPPO_PLATFORM_WINDOWS"
    }
    libdirs 
    {
      "%{externals.sdl2}/lib"
    }
    links
    {
      "SDL2",
      "glad",
    }
  filter { "system:linux", "configurations:*" }
    defines 
    {
      "HIPPO_PLATFORM_LINUX"
    }
  filter { "configurations:Debug" }
    defines 
    {
      "HIPPO_CONFIG_DEBUG"
    }
    runtime "Debug"
    symbols "on"
  filter { "configurations:Release" }
    defines 
    {
      "HIPPO_CONFIG_RELEASE"
    }
    runtime "Release"
    symbols "off"
    optimize "on"

project "hippoeditor"
  location "hippoeditor"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir(target_dir)
  objdir(object_dir)  
  staticruntime "on"
  links {
    "hippo",
    "glad"
  }
  files 
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }
  flags
  {
    "FatalWarnings"
  }
  externalincludedirs
  {
    "hippo/include",
    "%{externals.spdlog}/include"
  }
  filter { "system:windows", "configurations:*" }
    systemversion "latest"
    defines 
    {
      "HIPPO_PLATFORM_WINDOWS"
    }
  filter { "system:linux", "configurations:*" }
    defines 
    {
      "HIPPO_PLATFORM_LINUX"
    }
  filter { "configurations:Debug" }
    defines 
    {
      "HIPPO_CONFIG_DEBUG"
    }
    runtime "Debug"
    symbols "on"
  filter { "configurations:Release" }
    defines 
    {
      "HIPPO_CONFIG_RELEASE"
    }
    runtime "Release"
    symbols "off"
    optimize "on"