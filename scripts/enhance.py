import sys

if len(sys.argv) != 2:
    print(f"Usage: python {argv[0]} filename")
    sys.exit(1)
filename = sys.argv[1]
lines = open(filename).read().strip().split("\n")
width, height, n_colors, cpp = map(int, lines[2][1:-2].split())
garbage = lines[:n_colors+3]
xpm = lines[n_colors+3:]

enhanced_filename = filename[:-4] + "_enhanced.xpm"
fp = open(enhanced_filename, "w")
print(enhanced_filename, file=fp)
for i, line in enumerate(garbage):
    print(line.replace("32", "64") if i==2 else line, file=fp)
for i, line in enumerate(xpm):
    for _ in range(2):
        print('"'+"".join(line[1+cpp*i:1+cpp*i+cpp]*2 for i in range(width))+'",', file=fp)
print("};", file=fp)
fp.close()