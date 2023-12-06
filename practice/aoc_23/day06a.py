from ipython_startup.imports import *

inp_o = '''\
Time:        46     80     78     66
Distance:   214   1177   1402   1024'''

inp_s = '''\
Time:      7  15   30
Distance:  9  40  200'''

sam = 0
# sam = 0x0000000000000001
inp = inp_s if sam else inp_o

ans = 1
ts = list(map(int, inp.splitlines()[0].split()[1:]))
ds = list(map(int, inp.splitlines()[1].split()[1:]))
for t, d in zip(ts, ds):
    a = 0
    # print(t, d)
    for h in range(0, t + 1):
        r = (t - h) * h
        a += r > d
    #     print('\t', h, r, r >= d)
    # print(a)
    ans *= a

print(ans)
