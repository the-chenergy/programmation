from ipython_startup.imports import *

# fmt: off

inp_o = """\
4721224663
6875415276
2742448428
4878231556
5684643743
3553681866
4788183625
4255856532
1415818775
2326886125"""

inp_s = """\
5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526"""

# fmt: on

sam = 0
sam = 0x0000000000000001
inp = inp_s if sam else inp_o

g = [list(map(int, s)) for s in inp.splitlines()]
h, w = len(g), len(g[0])

for t in range(1, 1 << 30):
    q = deque()
    b = set()
    for y in range(h):
        for x in range(w):
            g[y][x] += 1
            if g[y][x] > 9:
                b.add((y, x))
                q.append((y, x))
    while q:
        y, x = q.popleft()
        g[y][x] = 0
        for dy in range(-1, 2):
            for dx in range(-1, 2):
                if dy or dx:
                    ay = y + dy
                    ax = x + dx
                    if 0 <= ay < h and 0 <= ax < w:
                        if (ay, ax) not in b:
                            g[ay][ax] += 1
                            if g[ay][ax] > 9:
                                b.add((ay, ax))
                                q.append((ay, ax))
    if len(b) == h * w:
        print(t)
        exit(0)
