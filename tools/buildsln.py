import sys
import globals
import subprocess

VS_BUILD_PATH=R"C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/msbuild.exe"

CONFIG="debug"
PLATFORM="x64"
ret = 0

if globals.IsWindows():
  # subprocess.call(["cmd", "/c", VS_BUILD_PATH, globals.PROJECT_NAME, "/property:Configuration={}".format(CONFIG), "/property:Platform={}".format(PLATFORM) ])
  ret = subprocess.call(["cmd", "/c", VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(CONFIG), "/property:Platform={}".format(PLATFORM) ])

sys.exit(ret)
