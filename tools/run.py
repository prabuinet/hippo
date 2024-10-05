import globals
import os, subprocess
import sys

config = "debug"
exepath = "{}/bin/{}/{}/".format(os.getcwd(), config, globals.PROJECT_NAME)

ret = 0

if globals.IsWindows():
  #subprocess.call("{}{}".format(exepath, globals.PROJECT_NAME), cwd=exepath)
  ret = subprocess.call(["cmd.exe", "/c", "{}\\run.bat".format(globals.TOOLS_DIR), config, globals.PROJECT_NAME])

sys.exit(ret)

