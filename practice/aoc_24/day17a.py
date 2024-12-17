from ipython_startup.imports import *

# fmt: off

inp_o = """\
Register A: 21539243
Register B: 0
Register C: 0

Program: 2,4,1,3,7,5,1,5,0,3,4,1,5,5,3,0"""

inp_s = """\
Register A: 729
Register B: 0
Register C: 0

Program: 0,1,5,4,3,0"""

# fmt: on

sam = 0
sam = 0x000000000000000
inp = inp_s if sam else inp_o

a = list[int]()
for s in inp.split("\n\n")[0].splitlines():
    a.append(int(s.split(": ")[1]))
p = list(map(int, inp.splitlines()[-1].split(": ")[1].split(",")))


def combo(x: int) -> int:
    if x <= 3:
        return x
    if x <= 6:
        return a[x - 4]
    assert 0, x
    return 0


c = 0
out = list[int]()
t = 0
while 1:
    t += 1
    # if t == 20:
    #     exit(1)
    if c >= len(p):
        break
    print(c, p, p[c], a)
    match p[c]:
        case 0:
            a[0] //= 2 ** combo(p[c + 1])
            c += 2
        case 1:
            a[1] ^= p[c + 1]
            c += 2
        case 2:
            a[1] = combo(p[c + 1]) % 8
            c += 2
        case 3:
            if a[0] == 0:
                c += 2
            else:
                c = p[c + 1]
        case 4:
            a[1] = a[1] ^ a[2]
            c += 2
        case 5:
            out.append(combo(p[c + 1]) % 8)
            c += 2
        case 6:
            a[1] = a[0] // 2 ** combo(p[c + 1])
            c += 2
        case 7:
            a[2] = a[0] // 2 ** combo(p[c + 1])
            c += 2


print(",".join(map(str, out)))
