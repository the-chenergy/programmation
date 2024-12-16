from ipython_startup.imports import *

# fmt: off

inp_o = """\
..........M..........j.............y.....O........
...B...............q......m........lGO............
....................q......2.l.GQ...O.............
.....X.......................................4....
.....................q............................
....M......P...............xl.K.............2.....
....F.........L.......C.K..............m..........
..........FM......P....jy......m..........o...r...
..X.......P.....RL..............G..x..........4...
............L..........NC.....q...................
.....C.X...............K....y..........4..........
........S...R.............j.x.....V...4...........
.....................R..x.....V..i......m.........
...........................R.V......N.......X.....
.....F.........M......N......E....................
................v................T.......F......O.
.............................N...V.......Q........
...v.....................C.....i..................
......c.....W..n.w........................E.......
3...................c.....................Q..6....
...........h......................j...............
.......n.0......h.................E..............2
.v.............7.......120.....c..................
......n.0............w...........D.t.........E...r
....8..3......0.w.hP....z...D..T...............r..
.................f........T........G......eQ......
......f.n.....7..p................................
.....Y..7.......f......I......D......K............
............Uf....T..W.....D..r...i...............
......I...............................Z...........
....5....B.......b..............s..............Z..
..........d...W..Uwh.............c..........i.....
..I.3..Y......................e...................
.....p.b..........k......7........................
p...........k....I..b..........s..................
.....k.......o...........W........................
.A..Y..........U.................a........6.......
..A...Y.p...................................6.....
B......k..........................Z............u..
...3.....................s..............a.........
......A.........................g.....a...........
.......A....8...b.U......H....sS..................
.........................S1.............t.........
.....................9z..e.....5..1.g.u...........
.......................z....d....g....H.J....o.6..
........B................d.....u....9.J.H.........
.8........S.................u9.............J.....H
.....................Z5.............t1...........a
.....................e..v...................o..t..
.....8...............L.....z.............J........"""

inp_s = """\
............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............"""

# fmt: on

sam = 0
sam = 0x00000000000000
inp = inp_s if sam else inp_o

d = defaultdict(list)
g = inp.splitlines()
h = len(g)
w = len(g[0])
s = set()
for y in range(h):
    for x in range(w):
        if g[y][x] != ".":
            d[g[y][x]].append(y + x * 1j)
            s.add(y + x * 1j)
for a, b in d.items():
    for i in range(len(b)):
        for j in range(i + 1, len(b)):
            k = 1
            while 1:
                x = b[i] - (b[j] - b[i]) * k
                if x.real >= 0 and x.real < h and x.imag >= 0 and x.imag < w:
                    s.add(x)
                else:
                    break
                k += 1
            k = 1
            while 1:
                x = b[j] + (b[j] - b[i]) * k
                if x.real >= 0 and x.real < h and x.imag >= 0 and x.imag < w:
                    s.add(x)
                else:
                    break
                k += 1
print(len(s))