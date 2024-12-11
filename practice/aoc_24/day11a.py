from ipython_startup.imports import *

# fmt: off

inp_o = """\
64599 31 674832 2659361 1 0 8867 321"""

inp_s = """\
125 17"""

# fmt: on

sam = 0
sam = 0x000000000000000
inp = inp_s if sam else inp_o

a = list(map(int, inp.split()))
for _ in range(25):
    b = []
    for x in a:
        if x == 0:
            b.append(1)
        elif len(str(x)) % 2 == 0:
            b.append(int(str(x)[: len(str(x)) // 2]))
            b.append(int(str(x)[len(str(x)) // 2 :]))
        else:
            b.append(x * 2024)
    a = b
print(len(a))
