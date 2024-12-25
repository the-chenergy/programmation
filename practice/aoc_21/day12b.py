from ipython_startup.imports import *

# fmt: off

inp_o = """\
YW-end
DK-la
la-XG
end-gy
zq-ci
XG-gz
TF-la
xm-la
gy-gz
ci-start
YW-ci
TF-zq
ci-DK
la-TS
zq-YW
gz-YW
zq-gz
end-gz
ci-TF
DK-zq
gy-YW
start-DK
gz-DK
zq-la
start-TF"""

inp_s = """\
start-A
start-b
A-c
A-b
b-d
A-end
b-end"""

# fmt: on

sam = 0
sam = 0x000000000000000
inp = inp_s if sam else inp_o

g = defaultdict(list)
for s in inp.splitlines():
    u, v = s.split("-")
    g[u].append(v)
    g[v].append(u)


@cache
def f(u, b, t):
    if u == "end":
        return 1
    ans = 0
    if u[0].islower():
        b |= {u}
    for v in g[u]:
        t2 = t
        if v[0].islower():
            if v in b:
                if t or v == "start":
                    continue
                t2 = 1
        ans += f(v, b, t2)
    return ans


print(f("start", frozenset(), 0))
