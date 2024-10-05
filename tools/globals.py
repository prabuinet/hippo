import sys, platform

V_MAJOR = 1
V_MINOR = 0
ENGINE_NAME = "hippo"
PROJECT_NAME = "hippoeditor"
TOOLS_DIR = "tools"

PLATFORM = sys.platform
for x in platform.uname():
  if "microsoft" in x.lower():
    PLATFORM = "windows"
    break

def IsWindows():
  return PLATFORM == "windows" or PLATFORM == "win32"

def IsLinux():
  return PLATFORM == "linux"

def IsMac():
  return PLATFORM == "darwin"

