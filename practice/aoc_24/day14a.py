from ipython_startup.imports import *

# fmt: off

inp_o = """\
p=82,15 v=-7,-48
p=39,5 v=28,65
p=32,82 v=-40,69
p=74,67 v=92,-85
p=58,76 v=30,86
p=31,64 v=-62,5
p=38,70 v=67,32
p=68,81 v=-45,61
p=32,42 v=-8,-34
p=18,79 v=60,40
p=55,36 v=93,26
p=63,52 v=-58,-44
p=9,35 v=86,-55
p=4,101 v=-64,40
p=10,47 v=-59,-25
p=25,73 v=-62,37
p=25,38 v=-23,52
p=27,70 v=88,-91
p=5,41 v=-59,-78
p=16,22 v=-14,61
p=18,29 v=88,26
p=86,82 v=-92,37
p=92,10 v=8,93
p=35,95 v=-16,-83
p=47,3 v=59,-34
p=42,23 v=80,-58
p=75,35 v=-66,-27
p=76,28 v=7,51
p=17,42 v=-27,-13
p=65,25 v=-61,87
p=6,39 v=-64,-79
p=65,29 v=64,-24
p=65,2 v=-76,41
p=2,91 v=81,-15
p=28,4 v=-75,44
p=39,82 v=-65,-66
p=43,26 v=70,-58
p=40,52 v=-96,83
p=58,94 v=30,-88
p=54,76 v=69,-38
p=25,70 v=-18,-96
p=91,60 v=45,-22
p=18,48 v=34,-50
p=25,7 v=83,-34
p=47,70 v=54,34
p=56,102 v=38,-24
p=5,75 v=24,-68
p=98,10 v=-95,-33
p=17,40 v=34,-26
p=40,93 v=-52,-40
p=68,11 v=-19,-33
p=46,9 v=-29,94
p=47,45 v=44,52
p=59,0 v=15,40
p=93,96 v=89,70
p=7,52 v=19,11
p=98,5 v=89,-59
p=36,26 v=-26,-78
p=1,98 v=-38,-86
p=52,28 v=-79,11
p=16,17 v=73,48
p=47,30 v=45,-68
p=46,96 v=80,-38
p=35,78 v=13,86
p=8,60 v=-90,-70
p=50,5 v=67,65
p=16,71 v=-36,38
p=58,93 v=-16,12
p=54,4 v=-76,-64
p=16,16 v=91,47
p=53,28 v=49,-8
p=88,85 v=84,11
p=82,78 v=75,-85
p=24,31 v=42,-25
p=25,14 v=-5,38
p=77,39 v=2,-45
p=80,88 v=-93,77
p=41,4 v=54,-62
p=13,43 v=-38,28
p=72,10 v=-40,4
p=68,87 v=-77,31
p=81,93 v=-27,-71
p=73,68 v=-32,58
p=93,68 v=19,-48
p=55,69 v=-6,6
p=75,86 v=-97,-66
p=22,14 v=-47,-55
p=4,51 v=-77,30
p=16,69 v=60,-96
p=24,53 v=-41,-24
p=86,41 v=-58,-47
p=23,68 v=96,-69
p=6,82 v=-31,88
p=26,48 v=21,78
p=1,5 v=55,-60
p=82,61 v=4,-47
p=86,84 v=-53,87
p=50,3 v=59,-60
p=74,76 v=96,-21
p=38,96 v=44,91
p=85,43 v=-92,29
p=56,57 v=-81,-20
p=14,7 v=-28,-9
p=86,14 v=-53,95
p=42,12 v=-78,-86
p=14,12 v=78,-59
p=86,94 v=-40,45
p=88,84 v=60,-24
p=91,78 v=17,-28
p=59,24 v=74,71
p=78,102 v=21,85
p=34,81 v=75,-65
p=17,70 v=-28,85
p=59,76 v=67,33
p=87,18 v=-7,-60
p=5,52 v=-33,-41
p=50,81 v=-78,-68
p=29,84 v=-80,-44
p=28,55 v=23,-95
p=82,29 v=4,99
p=31,30 v=47,23
p=52,60 v=59,59
p=55,62 v=97,90
p=81,100 v=-71,92
p=76,65 v=-53,59
p=61,83 v=-50,-38
p=13,7 v=86,88
p=81,41 v=-91,53
p=49,87 v=-42,-13
p=9,61 v=-59,81
p=72,76 v=55,-99
p=91,18 v=-17,71
p=22,36 v=-80,-51
p=80,34 v=66,-54
p=26,46 v=-93,-49
p=3,8 v=-34,-66
p=4,67 v=-95,-14
p=70,96 v=73,-66
p=53,17 v=46,-31
p=49,53 v=-78,85
p=3,22 v=90,-87
p=20,24 v=68,-58
p=86,66 v=71,-98
p=51,55 v=-86,-46
p=11,31 v=-51,-83
p=68,41 v=42,-90
p=40,96 v=67,-33
p=26,57 v=96,84
p=71,79 v=-45,-43
p=98,21 v=-28,77
p=94,97 v=-9,96
p=19,46 v=-51,44
p=76,77 v=-58,-68
p=0,93 v=19,-36
p=71,52 v=-4,1
p=19,49 v=-70,5
p=20,63 v=60,30
p=29,29 v=-88,22
p=74,47 v=-66,26
p=5,11 v=86,97
p=74,101 v=-94,51
p=25,80 v=79,-44
p=56,76 v=-65,-46
p=26,49 v=52,80
p=65,41 v=43,-77
p=37,25 v=-5,-25
p=17,21 v=52,20
p=83,68 v=99,85
p=74,40 v=-53,76
p=47,53 v=-37,-38
p=52,95 v=64,-48
p=80,61 v=9,58
p=28,94 v=13,-10
p=100,6 v=32,-12
p=36,72 v=51,69
p=72,53 v=-78,-74
p=56,14 v=7,54
p=100,21 v=-90,-32
p=12,44 v=-53,44
p=22,33 v=-88,23
p=4,91 v=-77,63
p=29,30 v=-40,-63
p=59,2 v=-34,-83
p=55,85 v=51,85
p=4,57 v=-46,-19
p=88,75 v=71,36
p=19,59 v=-88,-68
p=3,86 v=-14,-22
p=97,78 v=-38,37
p=34,10 v=-52,18
p=73,28 v=-44,-68
p=2,10 v=65,-27
p=41,35 v=-91,-77
p=39,35 v=5,-1
p=94,3 v=45,66
p=85,39 v=43,-81
p=86,87 v=-58,9
p=58,71 v=51,85
p=96,25 v=68,70
p=37,62 v=-81,-65
p=71,90 v=-96,-37
p=29,102 v=21,14
p=9,73 v=-71,-92
p=50,18 v=-55,98
p=5,23 v=62,58
p=50,82 v=-89,-5
p=48,48 v=-9,57
p=51,98 v=-16,-26
p=10,10 v=-5,-3
p=35,61 v=-99,49
p=82,95 v=14,-39
p=14,5 v=-88,93
p=56,15 v=-16,16
p=69,88 v=-2,-37
p=0,82 v=-72,-76
p=64,75 v=67,36
p=85,89 v=6,-42
p=46,51 v=52,53
p=36,70 v=-52,92
p=12,35 v=55,-7
p=37,92 v=-86,-91
p=58,47 v=97,-95
p=10,7 v=92,75
p=48,84 v=2,62
p=85,80 v=84,89
p=42,0 v=-65,38
p=67,100 v=-14,16
p=16,98 v=-49,39
p=15,67 v=98,-71
p=61,96 v=64,-13
p=5,64 v=-63,71
p=28,7 v=-26,-34
p=75,5 v=92,69
p=29,19 v=-21,3
p=26,22 v=-69,-95
p=90,46 v=-56,-75
p=96,92 v=71,-50
p=76,9 v=52,-39
p=60,15 v=25,45
p=47,47 v=-78,3
p=94,39 v=-82,-78
p=93,45 v=-36,-47
p=83,35 v=35,-52
p=38,32 v=-78,-79
p=39,66 v=75,-46
p=26,43 v=-31,79
p=34,44 v=-39,53
p=70,88 v=46,40
p=41,81 v=83,38
p=46,56 v=18,-51
p=93,6 v=-9,-4
p=87,86 v=-7,64
p=99,50 v=-33,28
p=16,60 v=34,-50
p=64,37 v=-81,75
p=76,0 v=23,-38
p=33,56 v=-60,53
p=54,63 v=2,-19
p=85,30 v=35,-6
p=23,65 v=89,-1
p=47,96 v=51,-52
p=72,65 v=-61,87
p=7,72 v=55,36
p=62,85 v=46,-92
p=28,98 v=-85,-85
p=53,14 v=-51,-10
p=46,39 v=-55,22
p=84,68 v=-61,7
p=85,25 v=9,49
p=9,87 v=42,-90
p=84,79 v=79,32
p=49,78 v=-86,-14
p=100,72 v=53,34
p=47,30 v=82,-48
p=5,77 v=48,-99
p=96,0 v=-15,-34
p=56,76 v=-78,-46
p=96,2 v=-5,31
p=89,58 v=-30,-72
p=3,45 v=-67,75
p=43,18 v=-10,76
p=77,54 v=92,80
p=55,1 v=88,-57
p=44,77 v=48,-14
p=75,5 v=40,-30
p=88,74 v=55,-84
p=48,65 v=72,57
p=27,75 v=-5,39
p=17,7 v=30,32
p=34,15 v=5,-4
p=72,28 v=56,74
p=42,21 v=36,23
p=36,24 v=-79,-51
p=95,69 v=-69,89
p=19,22 v=-44,43
p=50,9 v=-16,74
p=77,24 v=-29,66
p=24,73 v=-67,-69
p=24,83 v=-85,41
p=54,67 v=49,88
p=15,66 v=-27,97
p=22,59 v=-18,-76
p=30,5 v=5,-36
p=82,22 v=76,-30
p=100,88 v=97,45
p=44,16 v=-81,-57
p=69,13 v=86,-90
p=48,74 v=49,-56
p=43,88 v=-65,-91
p=51,100 v=49,-53
p=0,23 v=-25,-30
p=40,80 v=93,39
p=31,19 v=-88,-83
p=33,0 v=88,-88
p=53,17 v=5,-31
p=9,22 v=-64,-38
p=60,53 v=7,81
p=18,88 v=94,22
p=97,14 v=-24,62
p=88,59 v=-64,30
p=31,82 v=49,61
p=53,96 v=-71,21
p=9,75 v=-85,-43
p=3,35 v=86,29
p=80,92 v=-40,77
p=65,97 v=51,13
p=57,9 v=-14,72
p=12,97 v=19,38
p=14,43 v=-41,53
p=73,97 v=4,2
p=82,84 v=-61,36
p=83,76 v=43,-46
p=73,28 v=-31,-25
p=62,15 v=-19,72
p=75,74 v=36,11
p=84,15 v=56,44
p=40,4 v=-52,-87
p=76,59 v=-72,-82
p=23,51 v=-49,82
p=9,60 v=-46,-50
p=91,48 v=50,-51
p=1,87 v=94,-37
p=24,40 v=-52,29
p=67,77 v=64,60
p=90,53 v=1,79
p=25,20 v=-66,19
p=67,24 v=46,-51
p=0,73 v=-78,4
p=41,25 v=-78,-36
p=15,94 v=91,-91
p=81,50 v=30,53
p=34,24 v=85,-26
p=41,1 v=-34,-36
p=45,33 v=5,24
p=55,46 v=-36,45
p=55,89 v=72,-12
p=61,32 v=-99,74
p=6,36 v=58,-25
p=17,38 v=-57,-81
p=35,28 v=62,73
p=2,4 v=84,20
p=18,5 v=-84,-83
p=70,80 v=25,-41
p=70,96 v=-55,-9
p=25,34 v=12,-78
p=92,4 v=45,-84
p=74,55 v=61,-20
p=11,82 v=-72,-41
p=6,20 v=-33,-80
p=1,21 v=-38,-83
p=29,70 v=-70,-45
p=88,60 v=-4,55
p=24,47 v=7,-88
p=29,13 v=-30,95
p=60,65 v=64,-23
p=44,38 v=98,-69
p=31,15 v=-61,95
p=20,90 v=26,-14
p=58,99 v=64,92
p=21,30 v=18,24
p=95,65 v=-29,33
p=86,57 v=97,84
p=21,102 v=-44,-83
p=71,61 v=69,56
p=57,46 v=80,53
p=38,78 v=-86,-97
p=78,78 v=4,61
p=87,68 v=-7,31
p=100,67 v=-82,-43
p=50,60 v=75,-97
p=54,91 v=-99,66
p=93,83 v=-74,63
p=20,49 v=16,-19
p=1,71 v=73,-50
p=89,2 v=-4,43
p=31,79 v=-57,88
p=54,81 v=-91,-77
p=77,49 v=42,84
p=33,6 v=-57,-10
p=41,62 v=-83,6
p=71,16 v=85,-50
p=31,54 v=-70,-22
p=39,26 v=-5,-80
p=24,14 v=-36,98
p=50,100 v=-16,13
p=3,7 v=34,-6
p=59,84 v=64,-42
p=3,3 v=34,70
p=88,34 v=17,-94
p=86,16 v=45,42
p=68,1 v=-64,-67
p=77,64 v=53,83
p=17,36 v=21,26
p=80,83 v=-6,51
p=64,49 v=69,84
p=45,34 v=10,74
p=8,0 v=-36,38
p=94,3 v=92,-68
p=41,11 v=49,97
p=68,23 v=-1,72
p=88,101 v=30,32
p=74,94 v=-53,-12
p=25,45 v=97,99
p=78,76 v=17,59
p=97,24 v=-23,-58
p=89,19 v=91,-97
p=33,35 v=-88,-1
p=17,44 v=57,-45
p=67,11 v=12,-7
p=15,31 v=60,-56
p=32,9 v=-88,44
p=77,51 v=-9,-75
p=23,89 v=99,-15
p=60,82 v=-86,7
p=25,31 v=83,48
p=9,49 v=24,29
p=98,77 v=-82,-16
p=53,19 v=-2,79
p=64,29 v=-4,-52
p=76,97 v=17,-62
p=64,4 v=2,47
p=6,36 v=91,55
p=81,92 v=-22,69
p=94,74 v=-43,-42
p=92,55 v=71,83
p=9,33 v=-67,-98
p=6,66 v=68,-71
p=69,46 v=-99,-91
p=67,63 v=-86,-48
p=26,60 v=26,-50
p=99,55 v=45,55
p=20,39 v=-23,-50
p=85,67 v=-95,-19
p=71,100 v=-57,-67
p=100,5 v=-82,69
p=90,39 v=24,81
p=31,28 v=37,87
p=85,15 v=87,-63
p=44,96 v=49,-62
p=29,63 v=-38,-1
p=74,82 v=-4,-57
p=0,86 v=-4,-69
p=43,80 v=-65,-37
p=23,62 v=-80,5
p=20,71 v=-26,32
p=72,34 v=-32,-54
p=20,87 v=63,-21
p=78,6 v=87,-34
p=24,7 v=52,-31
p=95,29 v=-82,-32
p=67,36 v=-71,-79
p=8,81 v=-77,10
p=32,44 v=31,-48
p=36,102 v=-83,-10
p=66,90 v=-50,37
p=4,95 v=-49,-29
p=69,79 v=9,11
p=96,74 v=60,-83
p=75,74 v=-30,-18
p=81,19 v=-35,-54
p=93,23 v=63,-85
p=69,0 v=-37,-57
p=20,67 v=-23,-71
p=84,34 v=-46,14
p=94,81 v=76,10
p=43,99 v=98,-89
p=67,39 v=-86,-78
p=54,55 v=-62,-93
p=48,20 v=-43,-15
p=54,56 v=-74,64
p=67,50 v=-68,63
p=38,27 v=98,-82
p=35,45 v=-13,53
p=19,63 v=43,-9
p=33,63 v=-62,-67
p=22,73 v=27,66
p=5,57 v=-87,-74
p=50,65 v=10,-20
p=18,51 v=78,83
p=58,84 v=-55,-13"""

inp_s = """\
p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3"""

# fmt: on

sam = 0
sam = 0x000000000000000
inp = inp_s if sam else inp_o


h, w = (7, 11) if sam else (103, 101)
g = []
for s in inp.splitlines():
    p, v = s.split(" ")
    p = list(map(int, p.split("=")[1].split(",")))
    p = p[0] + p[1] * 1j
    v = list(map(int, v.split("=")[1].split(",")))
    v = v[0] + v[1] * 1j
    g.append([p, v])


def pr():
    G = []
    for y in range(h):
        G.append([])
        for x in range(w):
            G[-1].append(
                sum(g[i][0].real == x and g[i][0].imag == y for i in range(len(g)))
            )
    print(*G, sep="\n")


for _ in range(100):
    for i in range(len(g)):
        x, y = g[i][0].real, g[i][0].imag
        x = (x + g[i][1].real) % w
        y = (y + g[i][1].imag) % h
        g[i][0] = x + 1j * y

ans = Counter()
for x in g:
    x, y = x[0].real, x[0].imag
    if x == w // 2 or y == h // 2:
        continue
    ans[x // (w // 2 + 1), y // (h // 2 + 1)] += 1
print(ans)
print(prod(ans.values()))
