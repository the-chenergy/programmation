import array, bisect, calendar, cmath, collections, copy, fractions, functools, heapq, inspect, io, itertools, math, operator, os, random, re, string, sys, time, typing
from bisect import bisect_left, bisect_right, insort, insort_left, insort_right
from cmath import infj, nanj, phase, polar, rect
from collections import ChainMap, Counter, OrderedDict, abc, defaultdict, deque, namedtuple
from copy import deepcopy
from fractions import Fraction
from functools import cached_property, cmp_to_key, lru_cache, partial, partialmethod, reduce, singledispatch, singledispatchmethod, total_ordering, update_wrapper, wraps
from heapq import heapify, heappop, heappush, heappushpop, heapreplace, merge, nlargest, nsmallest
from itertools import accumulate, chain, combinations, combinations_with_replacement, compress, count, cycle, dropwhile, filterfalse, groupby, islice, permutations, product, repeat, starmap, takewhile, tee, zip_longest
from math import acos, acosh, asin, asinh, atan, atan2, atanh, ceil, comb, copysign, cos, cosh, degrees, dist, e, erf, erfc, exp, expm1, fabs, factorial, floor, fmod, frexp, fsum, gamma, gcd, hypot, inf, isclose, isfinite, isinf, isnan, isqrt, ldexp, lgamma, log, log10, log1p, log2, modf, nan, perm, pi, prod, radians, remainder, sin, sinh, sqrt, tan, tanh, tau, trunc
from random import betavariate, choice, choices, expovariate, gammavariate, gauss, getrandbits, getstate, lognormvariate, normalvariate, paretovariate, randint, randrange, sample, seed, setstate, shuffle, triangular, uniform, vonmisesvariate, weibullvariate
from typing import List
from sys import setrecursionlimit, stderr, stdin, stdout
try:
    from functools import cache  # type: ignore
except ImportError:
    pass
try:
    import json  # type: ignore
except ImportError:
    pass
try:
    import numpy  # type: ignore
except ImportError:
    pass
try:
    import sortedcontainers  # type: ignore
    from sortedcontainers import SortedDict, SortedItemsView, SortedKeyList, SortedKeysView, SortedList, SortedListWithKey, SortedSet, SortedValuesView  # type: ignore
except ImportError:
    pass
try:
    import sympy  # type: ignore
except ImportError:
    pass
