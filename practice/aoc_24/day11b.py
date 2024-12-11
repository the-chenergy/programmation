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


@cache
def f(x):
    if x == 0:
        return (1,)
    elif len(str(x)) % 2 == 0:
        return (int(str(x)[: len(str(x)) // 2]), int(str(x)[len(str(x)) // 2 :]))
    else:
        return (x * 2024,)


a = Counter(a)
for _ in range(75):
    print(_)
    b = Counter()
    for x, y in a.items():
        for z in f(x):
            b[z] += y
    a = b
print(sum(y for x, y in a.items()))
