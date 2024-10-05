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
    "%{prj.name}/src"
  }
  flags
  {
    "FatalWarnings"
  }

project "hippoeditor"
  location "hippoeditor"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir(target_dir)
  objdir(object_dir)  
  staticruntime "on"
  links "hippo"
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
  }