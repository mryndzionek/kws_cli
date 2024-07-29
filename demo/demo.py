import subprocess

p1 = subprocess.Popen(
    ["rec", "-q", "-t", "raw", "-c1", "-e", "signed", "-b", "16", "-r16k", "-"],
    stdout=subprocess.PIPE,
)
p2 = subprocess.Popen(["../build/kws_cli"], stdin=p1.stdout, stderr=subprocess.PIPE)
p1.stdout.close()

while True:
    line = p2.stderr.readline()
    if not line:
        break
    else:
        line = line.decode("utf-8")
        if len(str(line).split(",")) > 1:
            label = int(str(line).split(",")[1].split(":")[1].strip())
            print(label)
            i = label - 1
            subprocess.run(["play", f"wav/demo_{i}.wav", "-t", "alsa", "tempo", "0.7"])
