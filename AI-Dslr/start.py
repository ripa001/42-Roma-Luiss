import subprocess
import sys
import os

def init_library(file: str):
	subprocess.check_call([sys.executable,"-m", "pip", "install", "-r", file, "--upgrade"])

def create_venv(env: str):
	subprocess.check_call([sys.executable,"venv", env])

#def activate_venv(env: str):
#	subprocess.Popen([env, "main.py"])
	#subprocess.check_call(["source", "./", env, "/bin/activate"])



if __name__ == "__main__":
	if (len(sys.argv) != 2):
		file = "requirements.txt"
	else:
		file = str(sys.argv[1])
	init_library(file)
	if (os.path.exists('dslr/bin/activate')):
		print("Environment pronto per attivare: source dslr/bin/activate\nPer deattivare: deactivate")
	else:
		create_venv('dslr')
		print("Environment pronto per attivare: source dslr/bin/activate\nPer deattivare: deactivate")
	
	

