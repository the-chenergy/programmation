s = input().split('=')
t = eval(s[1])
s = s[0]
lo = 0
hi = 2**62
while lo < hi:
    x = lo + (hi - lo) / 2
    y = eval(s)
    if abs(y - t) < 1E-7:
        print(x)
        break
    if y > t:  # Might be < -- try both. M A G I C
        lo = x
    else:
        hi = x
