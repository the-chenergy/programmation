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
def f(k, s, t, raw=0):
    if s == t:
        return ["A"] if not raw else 0
    sy, sx = loc(k, s)
    ty, tx = loc(k, t)
    if raw:
        return abs(sy - ty) + abs(sx - tx)
    a = []
    for K, V in d.items():
        c = ((ty - sy) // V[0] if V[0] else 0) + ((tx - sx) // V[1] if V[1] else 0)
        if c > 0:
            a.append((K, V, c))
    assert len(a) <= 2
    ans = []
    for p in permutations(a):
        if g[k][sy + p[0][1][0] * p[0][2]][sx + p[0][1][1] * p[0][2]] == "#":
            continue
        ans.append("".join(P[0] * P[2] for P in p) + "A")
    return ans


ans = 0
for line in inp.split():

    def f2(i, x, t, a, k, just_one=0):
        if i == len(t):
            a.append(x)
        else:
            for p in f(k, t[i - 1] if i else "A", t[i]):
                f2(i + 1, x + p, t, a, k)
                if just_one:
                    break

    a = []
    f2(0, "", line, a, 0)
    b = []
    for p in a:
        f2(0, "", p, b, 1)
    c = []
    for p in b:
        f2(0, "", p, c, 1)
    res = min(map(len, c))
    ans += res * int(line[:-1])
print(ans)
