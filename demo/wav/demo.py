import subprocess

cmd = "rec -q -t raw -c1 -e signed -b 16 -r16k - | ../build/kws_cli"

p1 = subprocess.Popen(["rec", "-q", "-t", "raw", "-c1", "-e", "signed", "-b", "16", "-r16k", "-"], stdout=subprocess.PIPE)
# p2 = subprocess.Popen(['../build/kws_cli'], 
#      stdin=p1.stdout, stdout=subprocess.PIPE)

