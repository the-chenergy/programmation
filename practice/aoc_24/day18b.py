from ipython_startup.imports import *

# fmt: off

inp_o = """\
27,6
24,29
5,42
3,7
34,63
45,53
50,25
27,14
25,16
51,69
45,65
13,1
36,67
3,3
37,4
4,17
23,23
6,23
44,53
30,59
48,67
49,57
48,21
37,15
10,15
36,53
29,2
1,23
67,63
55,57
35,29
21,23
43,51
45,20
25,17
41,63
29,1
43,10
7,3
13,9
31,68
27,3
7,14
9,21
31,6
27,23
57,66
40,17
21,9
47,66
35,5
70,55
5,14
41,1
49,60
36,33
55,58
30,23
24,27
57,65
21,21
26,19
39,15
51,22
37,25
37,11
66,39
68,57
63,62
29,69
39,19
3,24
43,19
43,55
15,31
63,58
17,1
19,25
69,51
5,20
41,53
27,25
26,5
21,11
34,5
39,21
45,64
13,7
9,5
31,15
34,3
2,21
1,12
51,68
31,29
40,57
8,7
9,13
5,29
53,61
7,1
67,47
61,64
33,20
59,56
51,20
67,57
40,55
39,13
13,15
36,21
39,24
61,67
39,27
2,25
42,61
47,51
37,20
34,11
35,27
53,60
4,27
51,17
48,59
32,25
37,29
33,32
11,20
45,9
9,25
38,19
15,20
45,61
30,3
41,64
32,7
39,10
54,61
41,9
29,12
45,17
51,57
24,13
1,15
37,7
31,7
42,65
22,17
50,63
46,17
7,11
29,8
42,17
49,65
33,61
37,55
61,65
25,13
40,19
27,24
12,7
55,67
35,55
7,27
65,68
44,23
35,57
47,56
37,63
66,69
35,60
6,9
17,18
40,67
38,11
3,23
9,11
43,57
25,21
18,27
19,18
56,59
66,65
19,4
5,9
29,36
23,20
38,63
44,55
27,1
1,29
33,60
23,7
13,4
60,65
31,66
41,8
28,9
7,6
7,19
5,17
5,10
45,21
59,50
25,11
31,11
41,13
39,23
51,19
10,19
67,60
69,57
2,23
33,33
19,5
19,1
47,52
46,51
27,31
35,62
7,28
20,13
55,63
66,55
9,9
31,65
58,61
8,9
31,3
33,35
3,0
58,57
28,15
19,19
49,19
42,29
7,29
47,54
48,61
27,17
36,23
15,9
43,49
36,65
34,23
11,24
19,9
29,11
10,1
59,55
41,65
24,9
30,29
1,3
63,69
47,19
38,35
43,65
49,61
9,17
32,53
27,16
49,18
34,7
29,35
43,1
8,11
35,7
68,65
19,24
7,22
33,7
43,61
30,11
14,13
13,16
50,61
32,41
35,18
7,13
25,18
23,1
33,55
37,23
47,21
16,25
58,63
39,11
16,9
36,13
3,21
13,0
44,19
63,65
41,51
3,15
49,64
11,26
55,59
17,15
69,59
11,11
37,13
0,19
65,67
39,69
42,21
51,67
63,59
17,7
22,5
62,53
61,62
33,64
3,11
43,9
13,23
29,24
1,7
14,21
11,29
25,23
67,55
37,9
41,23
27,29
13,18
21,33
9,19
31,36
12,13
23,15
41,15
33,31
29,4
47,68
62,67
60,55
33,69
54,57
57,69
7,25
38,57
36,11
33,67
29,22
41,55
24,5
15,7
69,44
41,68
23,12
31,41
56,63
13,22
45,49
29,37
69,50
46,63
9,28
33,53
41,67
19,7
29,20
49,69
1,10
20,3
7,12
33,37
11,3
3,25
31,69
58,51
67,61
37,8
11,9
2,29
39,20
57,63
43,56
37,2
5,21
3,17
47,69
4,11
19,17
3,5
34,37
17,28
39,67
59,64
17,21
47,58
55,61
23,10
37,65
42,19
25,5
9,2
30,67
60,67
41,24
38,13
33,27
35,63
37,69
65,63
40,53
44,51
39,66
64,55
30,9
31,61
34,65
61,58
41,69
47,70
41,58
42,25
10,7
24,3
10,11
23,3
69,61
11,23
25,27
15,3
37,62
53,66
48,63
37,57
2,1
65,57
27,27
11,1
7,23
54,69
41,3
2,17
25,24
69,67
69,65
11,17
59,61
26,31
21,7
5,3
35,67
61,51
39,25
69,63
25,7
4,23
9,31
67,62
46,55
26,11
26,25
33,13
57,60
13,27
28,17
18,1
30,15
31,0
0,13
23,5
29,5
19,16
41,59
3,20
39,57
35,68
59,65
10,23
63,64
24,15
40,61
15,2
19,23
37,32
21,22
31,37
45,55
15,5
41,19
51,63
41,11
29,18
41,25
15,17
63,43
33,9
5,15
31,63
25,9
20,21
5,8
9,3
54,63
47,23
31,28
7,15
25,25
1,6
28,31
17,3
35,16
14,3
30,17
55,69
29,3
41,0
18,13
33,57
43,13
35,1
60,59
33,63
41,14
33,44
45,58
41,57
14,5
34,55
43,8
15,21
59,57
35,17
4,33
65,51
43,12
33,41
41,12
61,69
20,19
67,69
17,17
52,63
39,29
47,63
5,23
5,6
32,39
33,38
37,68
33,65
48,19
69,55
8,17
35,23
45,69
37,21
34,13
11,21
41,56
54,37
61,60
41,21
65,40
47,22
25,22
56,69
26,33
45,11
11,15
16,7
31,1
49,67
13,11
11,19
31,25
9,1
38,29
53,55
65,69
45,51
16,19
36,17
61,68
21,1
15,13
57,68
36,39
65,59
47,49
23,13
33,23
25,0
33,1
3,1
33,28
40,9
43,60
35,21
35,26
27,26
6,1
35,6
20,7
33,3
63,57
3,18
17,25
21,24
43,69
29,19
43,59
21,25
63,61
34,21
3,10
22,11
5,5
47,59
52,17
35,19
7,7
61,50
31,70
29,17
44,47
43,67
12,17
17,5
9,4
37,54
30,37
35,13
31,9
2,27
31,17
12,29
31,13
1,1
39,9
9,30
67,58
40,15
44,63
38,17
32,47
33,10
7,16
35,36
23,33
63,63
13,8
28,29
25,29
37,59
45,67
5,13
43,16
21,19
37,1
23,0
33,45
29,27
69,70
32,21
3,9
57,57
9,15
13,10
36,37
65,66
29,13
14,23
57,59
30,13
33,66
9,7
37,58
36,27
21,5
50,65
37,17
17,14
64,59
53,53
31,26
32,31
4,21
37,5
44,17
33,56
33,43
19,21
46,19
2,15
69,69
1,11
27,15
45,19
45,8
41,62
9,12
57,62
35,65
37,67
47,61
27,10
31,23
55,55
29,30
49,21
31,64
12,3
16,15
42,41
34,27
53,59
3,33
21,6
25,1
67,68
21,13
3,4
34,43
65,65
1,35
39,28
4,29
35,59
29,21
29,25
43,54
46,49
13,19
53,63
47,17
68,53
39,17
45,68
14,17
68,55
35,35
17,9
36,59
2,7
39,5
1,9
47,53
42,31
63,54
38,53
31,34
25,31
58,67
66,51
10,9
16,1
65,56
43,11
22,9
63,60
41,52
15,15
15,23
32,15
37,27
33,5
3,8
35,31
7,9
37,61
35,14
67,53
28,7
25,6
33,58
29,15
15,11
4,15
37,14
44,69
17,19
29,33
17,16
33,34
40,23
35,56
57,61
31,19
29,23
41,17
35,9
53,57
37,30
20,1
39,4
1,39
27,7
44,49
5,1
2,13
27,13
27,12
17,12
47,55
15,1
1,17
6,17
49,17
63,66
11,7
33,11
39,68
53,70
66,63
34,1
39,59
32,3
5,12
18,23
57,47
43,58
18,5
37,36
37,3
35,61
32,13
8,21
63,47
5,7
2,33
21,14
27,2
42,51
29,31
61,63
47,57
25,19
23,11
7,4
39,63
33,8
67,65
50,57
69,49
49,63
1,19
27,5
39,64
67,67
32,61
36,5
15,19
50,17
27,9
29,7
17,20
1,5
60,69
7,5
19,12
39,61
29,32
64,69
0,3
56,57
63,51
52,53
11,6
3,19
35,69
18,7
16,11
56,65
55,65
37,19
31,31
40,27
53,65
13,14
10,17
42,15
3,27
35,25
43,4
24,21
33,21
27,22
36,45
70,47
35,3
25,2
66,59
32,1
11,14
61,61
31,5
49,59
70,65
1,33
25,33
59,63
43,2
33,15
48,55
38,25
10,27
40,1
5,26
35,54
27,28
0,23
30,33
32,43
51,65
19,11
1,21
51,21
2,31
39,55
47,65
23,8
13,13
31,33
12,11
6,31
33,19
12,21
43,66
18,9
37,35
43,15
22,19
45,62
27,4
29,29
3,2
31,62
39,3
22,3
27,20
33,59
33,68
45,57
52,61
16,5
68,67
5,4
29,26
61,57
61,45
25,14
27,19
43,63
11,5
14,7
23,17
15,10
21,17
38,1
69,60
59,59
39,22
39,65
13,3
53,69
48,51
1,40
44,13
29,65
39,60
43,53
31,39
40,3
34,41
21,3
36,25
68,63
35,40
45,60
14,27
7,20
33,46
64,51
37,53
13,5
63,67
31,27
25,3
33,24
1,25
65,53
59,67
35,11
1,13
54,67
33,16
7,21
67,41
45,59
45,66
7,2
10,3
65,61
3,13
51,66
47,48
61,54
27,21
17,23
39,53
33,25
7,32
41,10
35,70
62,51
33,30
65,62
33,29
37,60
39,1
52,67
42,69
70,59
8,19
20,9
23,29
4,3
3,45
24,51
60,43
27,40
69,3
59,40
3,43
55,13
49,68
68,31
21,28
61,25
49,27
53,54
67,4
44,37
8,39
45,7
1,63
39,7
61,36
50,35
29,62
58,29
13,25
6,51
66,25
63,11
46,1
67,13
11,56
41,37
28,51
53,38
6,67
49,46
7,59
41,47
53,48
56,51
43,45
54,41
47,7
45,41
68,49
15,32
34,51
19,33
46,41
24,47
47,5
12,33
38,45
59,13
57,67
0,57
11,57
11,65
59,11
59,44
9,32
66,37
55,38
55,5
38,7
13,58
27,42
62,39
20,57
21,65
63,15
63,55
25,49
53,5
1,49
25,55
22,37
13,69
67,37
20,35
41,38
56,23
1,53
4,43
57,21
20,55
4,35
21,48
52,1
47,42
43,27
22,65
31,57
15,52
59,35
8,25
63,19
49,30
68,41
61,13
69,36
49,51
46,45
35,34
7,37
59,19
31,54
23,39
62,23
56,19
27,41
6,41
27,45
20,69
30,5
6,25
65,25
41,33
65,23
46,35
5,41
29,60
54,27
47,41
49,41
25,69
24,67
1,31
45,13
69,13
11,25
23,51
3,29
3,55
9,53
24,55
57,10
43,29
13,60
63,17
43,23
57,1
15,24
66,27
6,37
13,21
1,64
19,50
29,55
49,33
23,53
53,13
27,37
21,16
5,62
1,34
25,66
41,43
21,27
6,65
49,44
9,35
56,45
56,11
61,29
57,55
61,21
15,56
65,15
65,5
1,43
59,28
56,39
64,41
44,43
7,61
31,67
23,65
4,47
17,33
17,69
19,54
48,11
50,15
53,36
27,55
27,34
31,58
61,59
17,43
45,32
65,49
15,48
63,31
55,35
69,6
62,7
69,1
40,37
60,49
67,22
11,40
13,34
66,47
25,50
69,21
13,39
11,53
3,69
33,17
0,29
53,29
8,45
13,33
61,22
11,69
39,41
27,66
24,69
55,16
41,45
15,37
57,7
29,48
8,61
7,63
13,63
31,50
43,44
51,39
61,3
11,48
5,19
23,55
45,47
39,31
19,34
62,47
57,9
51,51
19,67
15,64
5,27
24,61
44,1
21,69
19,3
49,48
57,54
43,34
18,37
60,7
65,9
45,63
53,12
44,5
16,41
21,46
49,45
14,45
49,26
15,29
49,13
66,31
55,46
9,66
1,42
66,43
61,11
69,17
9,63
1,46
51,2
25,57
5,56
29,45
21,57
51,31
50,41
66,13
43,40
7,26
60,17
5,53
1,69
50,21
29,51
27,44
57,16
22,53
3,44
9,48
38,51
7,33
65,26
0,43
53,20
66,3
29,42
7,44
33,52
9,29
23,21
57,23
5,35
31,20
9,64
69,32
15,63
39,47
4,39
49,29
5,61
13,47
53,21
20,41
65,12
55,1
15,35
47,35
47,39
7,51
23,43
8,63
69,43
29,41
14,39
70,3
45,37
61,9
27,67
57,3
67,25
25,53
9,33
47,47
53,42
55,34
26,47
27,43
43,37
11,61
57,29
50,29
60,31
46,3
13,62
46,31
17,45
33,47
69,9
2,67
23,59
1,47
24,41
28,37
21,67
3,57
43,47
69,39
47,31
25,51
61,17
45,26
65,37
65,19
27,53
41,32
55,32
57,14
64,15
8,41
59,43
57,11
2,47
17,36
39,44
63,53
31,43
53,25
19,46
30,51
6,57
54,17
19,59
65,1
11,38
17,46
5,48
55,11
22,43
60,25
28,69
51,8
51,32
3,62
0,69
5,45
62,3
63,33
68,23
47,13
67,44
39,39
3,63
49,36
67,21
57,24
65,3
66,33
44,39
13,65
38,39
53,33
1,65
7,65
55,27
11,45
57,13
45,45
27,63
63,28
24,45
67,27
15,67
11,50
17,67
43,3
50,43
41,31
51,6
49,43
66,21
51,9
27,60
19,44
27,49
69,11
7,43
9,50
58,53
42,45
18,33
62,1
51,5
12,67
29,46
23,41
62,21
11,28
63,40
14,31
67,3
67,59
45,43
19,45
8,35
12,31
9,45
61,19
25,59
63,1
14,53
53,9
4,67
2,49
10,55
55,43
51,61
5,67
25,62
53,47
13,57
53,14
43,43
29,47
7,47
52,11
5,33
52,3
15,65
40,41
68,7
59,37
7,60
63,42
44,45
21,68
51,45
17,61
25,67
22,31
52,5
70,17
49,39
51,48
61,37
59,27
43,26
53,3
57,48
55,3
13,51
11,43
41,49
59,52
34,31
8,47
67,1
62,15
19,53
35,33
69,23
65,20
49,9
9,58
21,52
63,27
15,39
66,49
65,24
22,23
63,45
7,57
47,16
31,55
30,39
53,39
26,39
43,28
39,37
13,53
66,9
69,34
63,21
49,35
21,39
65,35
7,17
30,53
11,64
25,37
49,55
69,24
65,18
59,4
61,35
68,27
55,24
52,43
51,30
0,51
21,62
11,33
69,28
15,55
4,31
11,46
55,9
67,43
58,41
19,26
47,67
59,39
62,11
59,10
23,63
65,6
21,45
9,41
36,9
39,40
37,43
64,45
51,13
68,47
13,43
11,37
25,48
9,49
10,59
27,59
69,38
15,33
10,35
5,43
9,65
1,37
12,25
52,27
57,53
67,49
67,52
49,37
20,51
15,45
58,3
42,3
21,47
55,47
41,46
51,35
10,53
23,27
53,26
69,42
19,61
19,35
25,63
11,27
39,35
59,25
68,17
67,7
21,60
69,47
41,35
1,62
26,51
45,39
59,20
15,61
58,39
48,45
19,43
53,34
57,28
69,53
9,61
51,49
22,49
65,7
2,53
52,37
63,46
57,6
54,51
17,13
17,49
26,57
11,59
13,29
13,37
11,67
5,47
8,69
51,50
65,31
7,45
1,51
26,53
17,65
19,55
16,59
9,55
47,15
45,14
65,55
58,31
26,43
3,51
17,47
5,54
27,39
51,11
56,3
17,39
51,56
23,42
22,55
13,17
39,6
3,50
30,45
13,45
69,27
35,30
63,5
57,12
14,61
33,39
13,61
69,29
7,58
64,29
53,28
13,35
26,59
3,59
56,27
17,42
17,35
21,35
63,25
55,14
27,65
15,53
69,45
26,63
7,48
24,31
20,65
5,38
23,31
23,69
63,36
6,63
8,53
1,45
54,7
54,53
53,67
65,34
19,65
66,17
21,53
49,47
51,1
42,49
59,31
18,53
59,23
17,2
12,35
15,40
25,41
48,1
28,49
29,49
49,34
67,23
55,49
53,45
62,43
9,69
47,33
59,47
49,28
57,19
19,70
35,45
62,19
51,7
23,61
16,35
47,3
46,5
47,9
17,55
3,67
37,48
28,57
68,39
59,9
4,59
13,49
29,44
9,59
19,47
21,37
59,26
57,44
21,31
61,49
53,17
40,35
51,10
36,51
69,2
25,38
42,37
63,3
55,0
50,53
59,34
22,69
61,44
47,27
35,46
65,14
29,43
55,21
57,39
23,24
7,30
25,39
22,63
45,12
61,1
23,25
61,28
18,55
27,68
63,12
22,39
16,31
67,5
43,7
27,58
65,8
61,4
67,45
59,22
59,2
63,16
15,41
64,21
63,37
17,58
51,27
5,60
51,40
35,39
31,59
25,65
15,49
42,35
9,23
17,27
19,15
67,33
9,68
39,49
21,49
25,36
65,39
33,50
55,25
55,37
19,30
20,39
21,43
53,23
40,49
21,36
45,5
54,13
43,33
31,51
48,33
37,31
64,25
24,57
51,47
46,33
13,31
10,67
17,48
57,37
12,57
63,48
23,60
56,55
4,65
65,2
45,15
31,45
50,5
67,9
3,35
59,3
41,5
31,35
65,43
60,47
59,32
51,37
7,35
45,33
7,55
61,5
59,1
58,25
45,36
43,41
21,51
5,39
23,36
28,63
51,3
61,31
41,7
17,37
29,9
58,21
9,67
47,25
13,42
46,29
31,47
11,60
17,62
47,26
25,15
25,35
29,59
59,49
59,18
41,42
17,22
17,57
21,29
55,19
55,39
19,29
3,58
69,37
17,66
55,15
51,55
1,57
24,33
57,45
29,61
65,16
55,53
66,29
57,51
1,55
25,47
51,29
56,33
69,12
27,33
21,66
8,55
49,5
41,39
19,38
56,35
9,52
46,27
65,33
33,48
24,53
57,41
11,62
13,50
18,57
65,45
57,49
21,59
53,11
49,6
59,41
3,40
17,52
19,49
7,69
46,39
15,44
57,31
13,46
17,68
61,41
35,41
23,45
69,31
62,31
47,38
69,25
61,27
23,40
67,19
49,31
61,14
1,59
28,53
61,33
50,3
43,21
15,26
23,67
69,15
67,11
22,27
36,47
43,6
43,35
11,39
67,31
9,51
55,33
45,31
7,67
16,61
4,53
47,29
9,37
57,35
27,51
37,47
55,41
6,69
63,32
18,43
56,49
37,39
53,40
51,54
68,11
39,45
19,57
16,69
49,53
61,30
46,47
2,43
7,41
33,49
9,57
11,47
6,45
25,56
7,66
59,33
27,61
49,24
55,7
51,34
37,41
29,53
65,27
41,27
38,47
55,6
54,49
21,63
44,41
41,29
59,5
39,33
35,51
5,51
63,9
27,11
11,31
23,50
58,17
60,37
52,45
23,49
70,21
18,49
8,57
57,36
61,15
41,61
3,47
69,19
49,23
0,49
14,55
19,31
43,31
57,43
35,15
48,41
8,43
21,58
1,67
7,50
3,65
4,51
64,9
65,36
61,7
61,38
64,3
46,9
9,27
59,46
36,43
65,47
48,37
13,36
9,38
67,46
21,61
67,30
55,4
61,18
52,19
63,29
55,29
49,3
23,9
19,32
53,49
49,12
3,53
17,63
23,26
45,24
15,47
19,37
15,57
37,45
3,64
11,41
59,45
60,41
0,33
53,37
59,14
17,41
57,25
43,22
53,24
19,42
11,63
18,67
5,49
51,23
54,21
54,3
26,35
5,37
38,41
63,49
27,46
37,37
53,7
19,27
43,39
9,36
45,25
3,61
31,21
47,10
51,15
27,69
11,66
59,51
51,14
70,29
15,34
44,31
48,3
65,0
53,43
17,64
5,69
65,29
53,19
3,68
55,44
12,69
1,41
19,51
67,6
1,56
53,1
17,30
5,25
69,7
13,67
47,11
69,20
53,35
64,33
17,29
55,17
13,41
62,25
1,36
51,41
49,25
49,8
61,23
62,27
68,35
16,51
40,33
43,17
49,7
48,29
19,63
61,47
53,31
49,15
11,35
17,31
58,7
40,47
39,50
27,35
67,15
67,51
3,31
65,41
17,53
14,59
21,41
28,65
63,7
54,45
61,34
69,8
16,37
19,69
59,53
13,64
47,14
3,39
56,1
15,43
22,59
65,13
59,21
3,49
2,37
6,53
57,42
55,31
15,51
53,56
47,12
30,47
59,17
69,14
53,27
30,41
67,17
19,64
49,50
13,38
11,55
1,61
61,43
40,5
5,63
55,51
65,21
59,29
57,15
63,41
63,35
28,39
46,7
47,43
57,5
45,35
51,43
31,49
19,13
29,57
61,55
59,6
53,51
31,53
51,53
26,67
63,23
17,51
20,33
7,34
51,58
14,67
47,1
22,33
57,27
31,56
27,47
58,37
5,46
47,37
52,23
55,23
37,33
12,53
69,41
15,66
7,39
59,7
44,29
5,31
35,50
39,51
63,13
6,35
7,53
67,35
15,59
49,1
13,55
5,59
58,47
9,40
64,49
35,53
38,33
66,53
4,37
1,27
20,47
59,15
16,55
25,64
3,41
9,47
33,18
51,25
23,37
65,17
67,39
47,24
15,25
53,15
27,57
7,49
56,21
54,31
51,59
37,49
23,19
61,8
25,43
5,11
25,45
49,49
14,69
21,55
19,39
45,29
11,42
63,39
65,11
29,63
55,30
21,15
52,31
11,49
67,42
64,5
1,60
23,47
55,10
5,65
17,11
61,53
52,51
39,30
3,70
10,45
15,69
13,59
55,18
57,17
15,27
11,13
10,31
54,9
49,11
69,35
63,10
68,19
9,39
5,55
33,51
62,35
29,67
48,5
67,10
23,35
55,45
37,51
51,46
14,49
25,61
60,11
23,44
35,37
53,8
53,41
29,56
16,45
11,51
60,1
2,59
23,30
20,29
14,43
19,41
9,43
59,69
18,59
23,57
43,5
19,62
60,13
10,43
45,3
61,39
45,23
43,25
45,27
18,39
50,13
67,29
5,57
68,15
35,49
50,39
27,54
39,43
51,33
67,2
7,31
63,6
57,33
69,33
12,51
35,43
2,55
41,41
29,39
47,45
44,35
15,28
3,37
35,47
12,41
69,5
17,59
45,1
14,64
6,32
20,10
14,62
31,42
14,68
46,40
4,24
52,50
40,43
3,52
2,42
59,24
24,39
22,51
32,46
18,20
0,25
24,24
60,36
70,42
66,38
22,54
22,40
68,25
41,40
18,34
0,70
28,55
46,42
14,18
58,15
24,58
8,66
11,52
52,54
58,32
62,42
22,10
29,0
28,26
62,29
8,58
60,23
4,20
58,5
18,58
26,22
61,10
1,50
14,47
12,42
8,49
8,51
32,42
2,24
61,40
23,34
2,45
11,70
58,10
66,34
14,34
14,56
26,41
22,24
19,40
32,48
30,35
66,61
36,24
36,69
46,52
56,25
36,32
30,43
57,70
24,50
23,38
65,22
30,19
16,42
36,49
62,9
55,8
27,50
32,23
44,38
16,28
68,6
36,4
6,56
56,6
18,47
5,70
53,32
6,28
25,8
18,46
2,56
44,12
56,0
4,30
35,64
58,46
54,46
16,58
0,45
67,8
28,66
37,22
62,46
22,28
67,14
17,56
17,0
57,32
2,22
22,13
28,43
2,20
59,16
14,30
42,43
1,18
14,35
40,16
64,34
70,15
30,0
39,42
2,62
14,20
28,27
10,12
27,62
0,53
4,62
10,63
6,68
26,69
31,52
37,38
13,32
22,58
12,38
40,29
68,8
63,50
0,32
62,34
42,39
58,42
25,12
12,43
18,69
28,47
58,52
30,49
53,2
56,4
20,46
36,26
45,48
30,60
63,24
12,19
2,48
24,32
30,58
19,66
0,22
27,32
54,70
30,24
32,22
23,18
68,42
33,54
12,48
5,28
63,20
12,12
24,52
38,14
30,26
26,13
5,64
21,30
35,44
32,54
22,56
4,9
24,42
44,46
26,50
9,14
22,2
70,14
10,39
17,24
10,21
20,40
32,59
53,46
52,57
64,1
2,68
68,36
32,52
60,19
13,48
1,52
21,64
10,49
46,23
42,52
41,36
62,5
2,32
10,22
50,42
40,40
0,34
16,54
60,21
59,68
68,20
20,28
62,38
30,25
5,36
2,30
62,16
68,50
5,24
20,32
10,28
28,70
34,64
17,70
19,36
22,46
58,62
54,16
36,22
42,44
63,18
6,36
12,40
3,28
34,57
24,14
24,65
8,30
58,45
40,10
12,64
45,46
62,45
69,10
25,20
43,30
65,52
38,20
7,40
6,64
16,32
13,68
20,12
30,56
4,46
28,38
34,42
30,63
26,27
24,6
39,0
23,16
37,40
12,54
19,52
64,62
18,63
63,34
60,48
30,57
42,16
23,62
4,49
2,65
12,2
18,15
2,36
10,60
59,36
12,1
10,0
60,46
0,46
20,42
26,18
58,38
48,68
46,30
6,34
52,55
36,29
68,37
11,22
14,48
22,20
2,35
13,26
21,18
66,52
31,40
26,55
54,44
22,44
32,19
7,62
9,18
30,1
38,44
20,15
12,32
20,52
3,38
18,61
50,47
43,46
26,45
38,16
1,68
8,59
60,24
56,38
60,10
39,16
7,68
30,52
0,50
6,33
12,28
6,52
0,27
54,23
63,8
40,42
52,56
40,32
34,2
0,42
70,10
3,46
56,70
4,22
0,59
12,50
44,40
36,38
20,8
42,5
16,8
48,30
69,4
0,67
34,53
51,0
32,26
70,66
29,50
22,50
29,64
62,54
10,65
34,35
63,38
40,50
47,40
56,8
41,30
25,60
40,30
6,49
23,52
15,0
15,22
44,36
34,25
36,28
18,32
11,16
68,51
56,24
60,0
67,12
67,36
18,38
23,6
23,58
22,41
24,49
38,31
30,28
5,66
19,20
2,0
2,58
32,4
6,54
45,38
2,52
3,32
36,62
23,46
58,22
50,23
0,2
12,70
55,60
36,6
47,20
18,65
38,68
59,8
10,33
14,58
28,64
28,12
42,18
56,68
58,34
22,14
60,70
60,6
40,70
32,10
48,17
2,9
70,37
10,69
33,0
16,49
33,4
68,54
64,56
34,47
42,30
14,57
26,54
24,60
15,46
12,10
60,18
18,68
57,52
32,36
12,49
38,55
64,36
0,5
44,54
49,4
56,40
38,64
32,49
64,19
68,34
36,16
6,59
27,0
20,62
2,39
30,10
40,14
40,2
66,19
58,8
32,70
46,59
0,8
16,2
28,14
48,70
36,44
18,51
4,60
50,12
16,40
46,36
30,38
32,32
26,29
2,60
6,60
0,12
16,67
32,63
39,36
38,65
24,18
10,29
62,28
30,40
64,70
64,12
58,70
26,49
14,26
13,28
59,12
50,48
28,46
24,12
17,10
20,30
32,65
49,10
26,16
44,64
3,36
45,18
69,58
55,64
41,16
58,65
44,32
10,36
59,38
21,2
23,64
48,56
42,63
54,66
20,36
54,15
31,10
57,26
42,58
48,38
68,12
54,42
43,70
70,4
64,30
54,55
64,63
8,10
62,62
38,59
66,70
46,24
70,27
29,70
39,62
60,64
34,30
32,8
60,27
61,56
48,23
52,30
62,44
68,10
53,52
3,66
4,58
48,4
45,50
27,56
24,63
66,45
16,34
54,10
64,67
66,23
0,26
22,60
27,52
44,33
65,38
20,25
48,27
45,54
26,14
9,60
38,27
32,40
62,65
54,0
47,8
65,46
43,0
21,20
32,28
4,42
32,68
4,63
38,48
60,2
9,34
52,2
48,22
16,23
54,20
22,35
50,60
37,42
7,18
44,34
6,50
54,50
22,1
45,30
26,70
50,46
68,56
48,39
2,34
18,31
46,34
64,50
40,7
42,8
28,36
45,70
29,54
11,54
16,29
11,58
15,60
18,40
22,66
1,32
58,24
46,25
51,36
28,48
10,30
66,16
70,32
10,26
19,48
34,4
1,16
58,50
25,30
38,69
56,60
56,10
44,11
53,4
48,32
52,44
36,63
48,0
23,56
2,44
24,34
16,24
59,48
0,38
46,70
5,34
31,46
52,46
36,48
36,0
17,34
58,12
12,62
56,62
6,6
48,12
45,4
3,48
51,26
12,9
41,44
2,70
14,11
0,20
8,36
42,62
0,68
10,16
57,8
18,24
16,12
40,0
32,67
59,62
52,25
8,6
16,3
12,34
69,30
38,9
61,12
34,70
23,4
67,48
19,2
18,29
54,14
66,54
64,65
70,13
48,69
24,0
56,44
22,64
40,8
52,36
4,19
32,35
66,62
52,28
32,56
8,50
21,54
38,26
18,22
51,28
41,60
68,28
47,2
34,12
60,68
44,18
11,34
50,58
36,41
60,39
46,32
44,24
24,43
12,65
2,40
49,58
33,26
61,26
6,24
48,66
37,52
48,48
64,7
8,60
56,30
12,15
32,38
33,62
47,34
14,24
66,64
68,40
56,52
65,42
32,5
56,46
9,54
28,19
18,45
56,34
62,22
70,40
19,10
70,18
8,52
0,65
40,48
34,62
68,60
21,0
30,69
32,34
10,18
54,11
4,41
14,1
62,66
54,8
12,0
46,6
58,18
5,18
43,68
3,60
53,44
62,64
53,62
50,59
28,1
69,0
44,3
14,10
13,44
56,64
54,30
22,32
23,2
22,45
24,1
0,9
4,66
42,55
10,66
63,30
23,66
39,52
62,26
26,3
50,45
12,56
14,42
38,32
45,2
54,65
47,36
29,58
58,11
22,26
64,2
15,54
11,12
34,20
42,4
52,33
47,6
3,56
10,44
41,20
5,44
40,51
17,54
38,36
68,5
69,48
39,12
70,43
46,68
1,66
4,44
52,47
15,18
11,32
68,46
20,11
66,24
56,37
32,55
26,4
34,29
28,5
44,22
30,22
42,12
6,11
6,66
0,41
62,58
20,50
42,23
34,67
62,59
47,18
30,14
42,9
52,8
34,22
66,60
29,66
38,6
24,16
34,18
68,24
39,58
9,16
36,1
34,39
58,28
56,32
34,52
60,50
55,70
36,7
68,66
6,15
26,61
54,25
6,16
55,2
64,22
62,52
22,61
46,16
16,48
18,21
38,12
24,8
28,35
21,38
34,46
7,46
7,42
30,8
52,10
40,68
1,44
46,54
11,8
28,2
56,9
59,54
28,58
24,38
43,50
66,1
69,66
34,26
48,24
33,14
6,29
2,14
12,47
6,10
15,58
61,6
42,48
21,4
30,66
54,12
19,14
14,2
42,67
48,13
45,22
28,40
12,66
54,29
70,45
4,54
16,60
8,13
52,18
24,23
37,28
62,57
32,60
44,61
12,26
49,56
38,30
33,36
8,34
44,21
13,52
56,20
36,60
62,55
2,18
18,28
25,28
57,50
70,50
34,32
10,58
50,38
28,8
49,70
66,48
52,68
18,0
60,3
45,34
6,30
6,22
29,68
15,6
11,4
22,22
22,67
34,59
18,42
25,58
66,67
48,14
67,28
48,10
27,48
68,14
54,56
39,56
70,60
37,64
61,2
3,30
38,40"""

inp_s = """\
5,4
4,2
4,5
3,0
2,1
6,3
2,4
1,5
0,6
3,3
2,6
5,1
1,2
5,5
2,5
6,5
1,4
0,4
6,4
1,1
6,1
1,0
0,5
1,6
2,0"""

# fmt: on

sam = 0
sam = 0x000000000000000
inp = inp_s if sam else inp_o

h, w = (71, 71) if not sam else (7, 7)
g = [[0] * w for _ in range(h)]


i = -1
a = []
for x in inp.splitlines():
    i += 1
    x, y = map(int, x.split(","))
    g[y][x] = 1
    a.append((y, x))


def f(z):
    global g
    g = [[0] * w for _ in range(h)]

    i = -1
    for x in inp.splitlines():
        i += 1
        x, y = map(int, x.split(","))
        g[y][x] = 1
        if i == z:
            break

    q = deque([(0, 0, 0)])
    b = {(0, 0): 0}
    while q:
        d, y, x = q.popleft()
        for ny, nx in ((0, 1), (1, 0), (0, -1), (-1, 0)):
            ny += y
            nx += x
            if 0 <= ny < h and 0 <= nx < w and g[ny][nx] == 0 and (ny, nx) not in b:
                if (ny, nx) == (h - 1, w - 1):
                    return 1
                    break
                b[ny, nx] = d + 1
                q.append((d + 1, ny, nx))
    return 0


l = -1
r = len(inp.splitlines())
while r - l > 1:
    m = (l + r) // 2
    if f(m):
        l = m
    else:
        r = m
print(l, a[l], a[l - 1], a[l + 1])
print(f(l - 1), f(l), f(l + 1))
