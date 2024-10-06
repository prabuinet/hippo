project "glad"  
  kind "StaticLib"
  language "C"  
  staticruntime "on"
  targetdir(target_dir)
  objdir(object_dir)  
  files 
  {
    "include/**.h",
    "src/**.c"
  }
  flags
  {
    "FatalWarnings"
  }
  externalincludedirs
  {
    "include"
  }
  filter { "system:windows" }
    systemversion "latest"

  filter { "configurations:Debug" }
    runtime "Debug"
    symbols "on"

  filter { "configurations:Release" }
    runtime "Release"
    symbols "off"
    optimize "on"