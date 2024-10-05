import sys
import subprocess
import os

TOOLS_DIR = "tools"

def run_command(cmd):
  script = "{}/{}/{}.py".format(os.getcwd(), TOOLS_DIR, cmd)
  if os.path.exists(script):
    print("Executing: ", cmd)
    return subprocess.call(["python", script])
  else:
    print("invalid command: {}", script)
    return -1

if __name__ == '__main__':
  for i in range(1, len(sys.argv)):
    cmd = sys.argv[i]
    if run_command(cmd) != 0:
      break