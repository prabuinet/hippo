# cli build
# cli run
# cli version
import sys
import subprocess

TOOLS_DIR = "tools"

def run_command(cmd):
  subprocess.call(["python", "./{}/{}.py".format(TOOLS_DIR, cmd)])

if __name__ == '__main__':
  for i in range(1, len(sys.argv)):
    cmd = sys.argv[i]

    print("\n-----------------------")
    print("Executing: ", cmd)

    run_command(cmd)