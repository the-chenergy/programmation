from ipython_startup.imports import *

p = [2, 4, 1, 3, 7, 5, 1, 5, 0, 3, 4, 1, 5, 5, 3, 0]


def f(a):
    o = []
    while 1:
        b = a & 0b111  # 2,4
        b = b ^ 0b011  # 1,3
        c = a >> b  # 7,5
        b = b ^ 0b101  # 1,5
        a = a >> 3  # 0,3
        b = b ^ c  # 4,1
        o.append(b & 0b111)  # 5,5
        if not a:  # 3,0
            break
    return o


q = [(-1, 0)]
b = defaultdict(lambda: inf)
ans = 216549846240959
while q:
    # a, t = heappop(q)
    t, a = heappop(q)
    t *= -1
    if a >= ans:
        continue
    print(t, a.bit_length(), ans, ans.bit_length(), len(q), sep="\t")
    s = defaultdict(lambda: inf)
    for x in range(1, 1 << 13):
        x = x << max(a.bit_length() - 8, 0) | a
        o = f(x)
        if len(o) >= t and o[:t] == p[:t]:
            if t == len(p):
                ans = min(ans, x)
            else:
                if x >= ans or x >= s[x.bit_length()] or b[x] <= t + 1:
                    continue
                b[x] = t + 1
                s[x.bit_length()] = x
                # heappush(q, (x, t + 1))
                heappush(q, (-(t + 1), x))
print(ans)

"""
too high:
216549846240959
"""
