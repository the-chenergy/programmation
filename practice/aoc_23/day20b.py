from ipython_startup.imports import *

inp_o = '''\
&zq -> fd, gk, pp, ph, ss, dr, pl
%qg -> jh, nk
%lm -> lg, qm
%fk -> lr
%pp -> hh
%bf -> sj, qm
&qm -> kb, jl, bs, kx, bl, cz, dd
%db -> dc, jn
%kl -> dc, qv
%xm -> jh
%ss -> zq, nd
%vq -> bh, dc
%bl -> bs
%fd -> gk
&dc -> tx, vq, ct, df, fx
%dj -> zq, pp
%fv -> vj, zq
%pv -> lm, qm
%dg -> zz, jh
%fc -> fk
%qv -> dc, db
&ls -> rx
&tx -> ls
%vl -> fc
%dr -> fd
&dd -> ls
%kx -> jl
%sj -> qm, bl
%vj -> zq
%nk -> jh, vl
%xr -> kr, jh
&nz -> ls
%cz -> bf
%ms -> qm
%ct -> fx
%lg -> qm, ms
%lr -> dg
%pl -> dr
%rt -> zq, dj
%jn -> dc
%zz -> zm
%kf -> kl, dc
%jl -> cz
%hh -> fv, zq
%df -> mr
&jh -> zz, lr, vl, fc, nz, fk, qg
%fx -> hq
%hq -> df, dc
%kb -> qm, kx
&ph -> ls
broadcaster -> kb, vq, ss, qg
%nd -> pl, zq
%gk -> rt
%mr -> dc, kf
%bs -> pv
%bh -> dc, ct
%kr -> jh, xm
%zm -> xr, jh'''

inp_s = '''\
broadcaster -> a, b, c
%a -> b
%b -> c
%c -> inv
&inv -> a'''

inp_s2 = '''\
broadcaster -> a
%a -> inv, con
&inv -> b
%b -> con
&con -> output'''

sam = 0
# sam = 0x0000000000000001
inp = inp_s if sam else inp_o
inp = inp_s2 if sam else inp_o

M = {}
S = {}
C = defaultdict(dict)
I = defaultdict(list)
for line in inp.split('\n'):
    l, r = line.split(' -> ')
    r = r.split(', ')
    op = '/'
    if not l[0].isalpha():
        op, l = l[0], l[1:]
    # print(op, l, r)
    M[l] = [op, r]
    if op == '%':
        S[l] = 0
    # elif op == '&':
    #     # C[l] = 0
    #     S[l] = 0

for l, (op, r) in M.items():
    for y in r:
        I[y].append(l)
        if y in M and M[y][0] == '&':
            C[y][l] = 0

q = deque()
out = []
ans = [0, 0]
t = 0

assert len(I['rx']) == 1
i_rx = I[I['rx'][0]]
got = {}
last = {}


def push():
    global ans, t
    t += 1
    q.append(['broadcaster', 0])
    while q:
        l, x = q.popleft()
        ans[x] += 1
        if l == 'output':
            out.append(x)
            continue
        if l not in M:
            continue
        op, r = M[l]
        # print(l, x, op, r)
        sends = []
        if op == '/':
            for y in r:
                sends.append([y, x])
        elif op == '%':
            if not x:
                S[l] ^= 1
                for y in r:
                    sends.append([y, S[l]])
        elif op == '&':
            # C[l] = x
            # S[l] = x
            s = all(C[l].values()) ^ 1
            # s = S[l] ^ 1
            for y in r:
                sends.append([y, s])
        for y, s in sends:
            if y in M and M[y][0] == '&':
                C[y][l] = s
                # S[y] = s

            if not s:
                if y in i_rx:
                    if y in last and y not in got:
                        got[y] = t - last[y]
                    last[y] = t
                if len(got) == len(i_rx):
                    print(math.lcm(*got.values()))
                    exit(0)
        # print('\tsends', sends)
        q.extend(sends)


def my_test():
    global out
    out = []
    push()
    # print(out, end='\n----\n')
    out = []
    push()
    # print(out, end='\n----\n')
    out = []
    push()
    # print(out, end='\n----\n')
    out = []
    push()
    # print(out, end='\n----\n')

    exit(0)


# my_test()

for _ in range(1000 << 30):
    push()
print(ans, prod(ans))
