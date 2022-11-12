nL, nP = map(int, input().split())

# For a peg i, E(i) = P(l)*E(l) + P(r)*E(r) + P(s)*M, M being E(j) where j is
# the best drop-point.
# Record each E(i) to be x + y*M and deal with M using a geometric sum
# later.
# Use complex numbers to simplify calculations; let E(i) = x + y*M*j.
# O(nL + nP)

E = [0] * (nL + nP)
for i in range(nL):
    E[i] = float(input())

is_drop_point = [True] * (nL + nP)
for i in range(nL, nL + nP):
    pl, pr, tl, tr = input().split()
    pl, pr = float(pl), float(pr)
    tl, tr = int(tl) - 1, int(tr) - 1
    E[i] = pl * E[tl] + pr * E[tr] + (1 - pl - pr) * 1j
    is_drop_point[tl] = is_drop_point[tr] = False

ans = 0
for i in range(nL + nP):
    if is_drop_point[i]:
        ans = max(ans, E[i].real / (1 - E[i].imag))

print(ans)
