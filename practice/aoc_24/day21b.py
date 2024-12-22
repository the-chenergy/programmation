from ipython_startup.imports import *

# fmt: off

inp_o = """\
869A
170A
319A
349A
489A"""

inp_s = """\
029A
980A
179A
456A
379A"""

# fmt: on

sam = 0
sam = 0x000000000000000
inp = inp_s if sam else inp_o

g = [
    (
        "789",
        "456",
        "123",
        "#0A",
    ),
    (
        "#^A",
        "<v>",
    ),
]

d = {}
d2 = {}
for x, y in zip(">v<^", ((0, 1), (1, 0), (0, -1), (-1, 0))):
    d[x] = y
    d2[y] = x


@cache
def loc(k, c):
    for y, r in enumerate(g[k]):
        for x, d in enumerate(r):
            if d == c:
                return y, x
    return -1, -1


@cache
def f(k, s, t):
    if s == t:
        return 1
    sy, sx = loc(min(k, 1), s)
    ty, tx = loc(min(k, 1), t)
    if k == 25:
        return abs(sy - ty) + abs(sx - tx) + 1
    a = []
    for K, V in d.items():
        c = ((ty - sy) // V[0] if V[0] else 0) + ((tx - sx) // V[1] if V[1] else 0)
        if c > 0:
            a.append((K, V, c))
    assert len(a) <= 2
    ans = inf
    for p in permutations(a):
        if g[min(k, 1)][sy + p[0][1][0] * p[0][2]][sx + p[0][1][1] * p[0][2]] == "#":
            continue
        b = "".join(P[0] * P[2] for P in p) + "A"
        c = 0
        for i in range(len(b)):
            add = f(k + 1, b[i - 1] if i else "A", b[i])
            c += add
            # print(p, b, i, add, c)
        ans = min(ans, c)
    return ans


ans = 0
for line in inp.split():
    a = 0
    for i in range(len(line)):
        a += f(0, line[i - 1] if i else "A", line[i])
    print(line, a)
    ans += a * int(line[:-1])
    # break
print(ans)
