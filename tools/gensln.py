import subprocess
import globals

if globals.IsWindows():
  subprocess.call(["cmd.exe", "/c", "premake5", "vs2022"])

if globals.IsLinux():
  subprocess.call(["premake5", "gmake2"])

if globals.IsMac():
  subprocess.call(["premake5", "gmake2"])
  subprocess.call(["premake5", "xcode4"])
