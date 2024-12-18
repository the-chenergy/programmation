from ipython_startup.imports import *

# fmt: off

inp_o = """\
12,28,0,63,26,38,64,17,74,67,51,44,77,32,6,10,52,47,61,46,50,29,15,1,39,37,13,66,45,8,68,96,53,40,76,72,21,93,16,83,62,48,11,9,20,36,91,19,5,42,99,84,4,95,92,89,7,71,34,35,55,22,59,18,49,14,54,85,82,58,24,73,31,97,69,43,65,27,81,56,87,70,33,88,60,2,75,90,57,94,23,30,78,80,41,3,98,25,79,86

50 79 88 34  0
56 46  5 17 31
29  6 38 78 68
75 57 15 44 83
89 45 43 85 72

29  8 56 15 33
 7 14 51 88 67
91 32 62 18 73
53 63 49 34 46
70 25 77 87 31

38 92 26 65 77
59 39  4 57 16
91 45 35 36  2
34 40 89  8 62
96 28 31 88 33

93 96 73 40 13
57 59 88 32 78
48 72 23 42 62
41  7 85 84 44
95 91 52 61  8

23 42 58 38 46
41 91 92 81 68
12 51 50 64 71
32 13 55 44 35
74  4 40 15 77

19 79  7 65 77
56 98 93 86 87
 5 68  8  2 49
83 45 74 92  6
46 88 33 58 28

79 82 12 77 30
68  6 70 23 80
24 85 69 91 90
57 15  1 52  8
43 26 44 17 53

73 88 70 31 44
58 86 16 11 97
36 13 40 79 83
78 25  2  5 91
62  4 29 71 95

51 96 81 78 86
49 77 12 21 26
66  2 52 31 68
56 74 84 91 45
19  0  8 87 92

 3 13 58 50 17
 4 78 69 16 38
91  2 23 21 51
49 79 31 97 90
37 46 12 80 28

61 11 73 50 39
30 29  0  4 59
18 78  6 27 22
38 14 75 48 43
 3 65 82 56 92

69 11 32 30  1
59 27  4 10 61
28 92 26  6 36
25 76 70 33 97
16 49 84 31 73

43 77 14 33 87
40 32 97  9 76
59 54  6 73 84
86 44 42 52 38
57  3 16 24 83

16 55 45 39  1
94 25 75 22 32
 3 60 13 91 26
93 86 18 77  8
 4 67  5 54 14

18 87 33 79 26
77 73 95 67 82
70 92 91 43 29
55 71 97 28 59
 5 84 81 15 22

49 29 48 69 83
56 70 39 71 72
68 74  9 94 88
77 96 38 98 14
55  7 16 80 31

63 51 88 50  9
48 89 75 43 11
27 77 22 80 53
56  4  1 36 52
87 85 30 35 54

53 39 34 88 51
56 43 19 10  0
85 22 26 25 54
98 62 31 66 48
 1  6 58 21 17

34 47 43  4 16
10  0  1 21 54
 3 84 83 51 12
67 35 62 72 11
93 13 30  9 22

 2 67 51 17 36
77 25 73 80 16
33 31 61 41 72
71 98 45 29 15
60 97 69 58 87

88 46 55 19 68
13 53 71 95 60
75  3 58 82 41
28 16 15 57 81
39  9 34  4 54

72 38  5 25 57
45 30 33 70 15
43 12  8  1 96
29 52  3 73 78
76 35 40 90 77

30 18 10 81 74
89 28 32 70 87
 1 71 73 36 12
16 78 48 98 53
 9 37 49 52 22

88 21 69 78 59
81  5  6 46 72
76 93 96 50 36
83 19 51 22 68
34 20 39 53 63

87 64 61 38 28
21 14 11  6 12
51 70 78 40 57
 5 37 66 49 85
99 41 81 88 19

93  9 44 90 49
56 34 83 79 84
38 63 53 78 29
 1 94 37 24 86
57  4 52 82  6

64 31 24 42 33
78 85 95 38 30
43 40 23 52 12
39 84 79 53 57
73 29 56 69 22

30 31 61 15 22
45  9 43 23 59
34 87 70 52 28
47 86  1 49 39
94 76 98 78 41

46 71 30 50 45
47  9 56 81  8
60 92 16  6 76
42  4 77 40 54
 7 43 32 72 55

74 26 50 79 38
64 72 49 82 21
93 81 24 45 55
94 22 20 68 71
37 36  3 67  1

 9 76 18 42 14
36 45 48  1 28
94 72 56  7 61
25 82 50 89 99
20 29  3 51 46

79 56 41 34 18
98 71 75 74 61
10 52 28 29  8
55 84  1  5  2
80 35 40 42  4

71 54 81 23 80
87 27 98 65 91
 2 75  4 99 60
11 17 70 59 50
67 97 77 12 22

11 72 38 57 17
60 93 16 48 90
73  9 89 68 18
71 59  0 94 12
54 70 96 33 49

68 40 21 50 17
79 25 76  8  1
72 71 13 39 73
91 98 28 92 53
27 23 62 74 35

42 97 40 55 69
87 83 21 94 89
28  9  1 13 31
45  4 35 74 25
85 23 80 70 26

36 22  7 63 87
25 24 60 21 44
84  6  3 31 46
 2 32 74 72 96
75 43 50 35 81

49 56 18 58 94
 7 43 45  2 53
75 91 30 81 37
25 50 31 74 82
24 26 98 80 10

45 33 18 66  7
14 71 60 34  6
23  3 42 22 38
41 88 86 77 30
12 15 70  0 97

87 41 96 97 15
11 88 64 52 62
26 72 68 18  6
42 35 90  8 14
10  3  0 66 28

83 46 54 65 96
 2 78 43 52 47
77 89 81 53 73
72 91  7 87 56
45 14 21 16 59

34 62 67 38 58
95 31 43 88 22
40 45 98 80 19
77 94 53 61 14
68 42 47 65 16

54 13 64 24 73
46  6 91 94 29
55 12 16 65 89
31 28 76 87  2
 5  4 83 43 93

81 89 16 67  5
65 64 70  1 40
 3 21 52 53 17
36 19 58  8  0
31  9 79 93 56

58 98 52 71 56
 4 97 48 91 38
43 95 92 85  2
70 10 73 17 26
60 25 20 45 13

42 53 26 14 20
66 18 28 10 77
23 96 22 25 21
95 52 50 70 94
41 81 45 84 83

46 80  4 62 97
23 85 47 61 12
 9  8 87 72 69
 3 30 55  1 54
52 56  7 22 36

30  7 83 63 47
 0 75 20 76 57
98 89 69 22 25
53 66 24 39 33
43  2 19 35 85

40 11  2 57 54
93 58 37 82 32
24 97  8 49 17
14 89 91 41 79
65  6 55 72 99

66 14  7 69 98
97 81 80 43 45
11 17 60 89 59
23 58 63 15 84
62 91 33 46 77

97  1 96 14 31
62  3 69 80  9
11 91 94 85 63
20 30 40 53 64
34 45 18  4 52

65 75 81 69 53
40 63 98 67 46
 1 49 38 73  2
33 99 91 77 90
94 14 21 34 22

 5 37 91 44 57
20 72 27 93 45
86  3 29 84 22
83 73 90 68 21
 1 98 40 25 58

39 22  2 41 91
18 96 21  4 95
75 77 64 85 19
35 83 87 20 93
54 56 81 50 74

84 91 16 55 14
85 67 18 19  3
17 15 79 82 20
97 47 58 80 28
48 53 89 73 87

36 91 46 89 22
10 47 58 85 43
20 54 45 57 84
33 51 71 35 29
80 93 24 98 50

42 10 65 99 61
87 19 58 48 66
36 68  7 63 57
72 20 81 21 96
80 13 15 60 90

61 37 87 98 69
21 80  7 74 40
93 94 60 39 22
28  8 81 19 42
12 59 34 72 20

 2 40 42  5 74
82 58 93  9 73
38 69 51 33 85
76 26 46 55 70
39 41 89 84  8

36 99  7 90  3
50  9 71 85 67
92 23 79 28 87
63 56 44 31 52
65 55 62 58 64

23 28 33  0  2
14 69 92  9 31
77 81 74 71 24
53 19 57 85 61
20 41 21 56 99

57 68 87 13 80
21  4 95 59 46
29 26 55 89 70
64 66 90 31 34
 3 28 12 16 47

75 20 85 31 82
28 67 83 73 91
19 92 33 96 86
61 39 59 50 74
94 36 69  5 79

89 63 97 48 51
26  2 31 17 60
47 33 27  3 42
20 88 61 46 68
41 66 90 32 92

34 46 50 33 28
43 70  3 42 31
10 74 68 80 37
51 58 48  7 75
47 53 35 86 22

52 17 41 92 58
90 84 65 15 35
24 12 95 70 26
47 29 73 32  8
83 74 56 67 33

20 86 99 92 28
31 44 68 32  1
87 47 78 98 83
 6 50 54 30 93
60  4 58 24 51

95 59  2 29 75
32 42 30 48  5
37 11 82 66 96
45 28 69 52  0
36 57 46 12 55

31 65 46 59 27
85 70 75 13 48
42  0 51  1 88
40  6 34  8 71
 7 22 11 98 25

 5 14 10 19  8
87 35 92 18 82
73 81 36  4 47
57 16 15 79 60
11 90 75 31 28

21 61  3 56 41
13  8 29 92 31
35 46 30 26 57
11 66 58 47 43
50 70 40 68 69

71 27 86 78 58
98  7 26 66 17
77 85 62 39 42
88 29 40 48 49
83 89 20 10  0

 5 17 40 55 28
48 19 83 10 97
58 69  9 91 94
80 50  8 43 86
84 21 27 75 67

36 46 31 75 40
77 34 24 72 93
 3 12 65 70 64
28 10 63 59 51
56 25 67  2 80

75 96 15 26 53
42  0 48 56 85
95  4 12 49 57
 9 79 38 93 54
98 82 99 66  8

93 33 31 41 49
83 96 63 46  8
51 97 47 79 56
43 69 54 38  2
20 21 84 17 70

84 28 48  9 56
18 22 34 46  1
31 61 87 62 27
13 96 58 95 20
45 10 57 17  0

63 26 57 96 64
52  9 77  4 44
56 88 76 55 71
33 99 16  7 72
54 27 78 61 24

98 48 75 24 15
26 27  6 79  5
95 47 56 18 69
37 57  8 61  9
51 91 31 74 36

84 49  7 90 95
41 27 15  2 87
71  8 34 39 37
57  5 46 40 56
38 65  6 48  4

92  3 77 66 10
71 83 86 34 18
16 76 54 38 26
 8 17 67 30 88
37 50 11 69 62

77 18 60 80 39
12 66 51 13 14
85 84 57 91 30
46 98 74 71 56
19 62 54  2 65

68 27 58 13 64
35 16 75 86 90
24 28 38 31 59
21 43 12 84 29
32 51 40 77 39

99 19 74  0  9
59 92 67 82 69
72 46 63 51 77
 2 45 66 28 12
93 38 15 64 27

96 41 34 58 25
46 91  9 57 72
67 24 68 36 15
 0 30 78 63 49
87 50 82 32 75

10  3 82 73 51
94 21 43 45 11
65 83 92 37 86
60 90 32 52  8
87 97 53 99 81

33 77 21 68 53
67 95 99 17 69
50 62 94 24 34
72 56 63 66 57
15 10 42 84 80

69 16 75 53 15
18 85  2  5 83
 0 33 23 24 89
80 92 74 79 38
31 11 26 84 97

34 37 93 50 87
31 79  3 39 64
81 22 66 40 85
15 69 42 88 91
68 33 57 60 14

30 99 47 23  4
71  3 74 22 49
44 76 50 38 88
59 21 27 32 35
46 41 65 24 48

 5 14 81 45 20
91 18 28  7 51
29 24 76 79 84
22 58 27  9 99
67 47 60 85 41

34 29 50  9 58
87 68 70 72 63
85 10  3 14 18
59 48 19 93 39
61 25 16 26 54

 0  4 94 42 12
64 41 96 85 44
89 61 74 47 97
54 63 33 51 93
 3 18 79 86 99

49 55 24 85 26
50 38  6 87 45
64 44 16 92 72
12 81 90 51 60
 0 37 47 54 70

45 31 27 17 41
10 72  0 76 66
24 32 86 87 97
54 75 62 33 79
92 47 26 11  9

11 94  1  2  8
38 31 61 48 13
74 85 24 19 78
97 69 20 14 59
26  5 66  4 58

 5 89 53 19 34
50 59 13  9 48
29 94 96 85 10
52 91 17 78 31
63 55 27 66 16

78 13 16 37 54
17 69 42  6 80
66 87 51 43 21
33 50 44 74 41
36 40 75 22  0

11 98 86 83 46
32  0 60 31 15
62 96 29 77 22
84  7 36 25 13
34 91 14 92 49

51 98 64 95 75
88  8 49 89 25
37 53 39 47 18
60 84 77 22 92
52 42 85 21 45"""

inp_s = """\
7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7"""

# fmt: on

sam = 0
sam = 0x000000000000000
inp = inp_s if sam else inp_o

g = list(map(int, inp.splitlines()[0].split(",")))
b = [[list(map(int, t.split())) for t in s.splitlines()] for s in inp.split("\n\n")[1:]]
m = [set() for _ in range(len(b))]

for val in g:
    for i, a in enumerate(b):
        for y in range(5):
            for x in range(5):
                if a[y][x] == val:
                    m[i].add((y, x))
                    ok = 1
                    for k in range(5):
                        ok &= (y, k) in m[i]
                    if not ok:
                        ok = 1
                        for k in range(5):
                            ok &= (k, x) in m[i]
                    if ok:
                        s = 0
                        for y in range(5):
                            for x in range(5):
                                if (y, x) not in m[i]:
                                    s += a[y][x]
                        print(s * val)
                        exit(0)
