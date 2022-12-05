SYNC_IO = 0x0  #  Synchronize stdin and stdout
TRACE_SYS_OUT = 0x0  #  Use stdout for trace and eprint
LOCAL = 0x01  #  If 0 or not set, "comment" all trace and eprint

if True:
    import array, bisect, calendar, cmath, collections, functools, heapq, inspect, io, itertools, math, operator, os, random, re, sys, time
    from bisect import bisect_left, bisect_right, insort, insort_left, insort_right
    from cmath import infj, nanj, phase, polar, rect
    from collections import ChainMap, Counter, OrderedDict, abc, defaultdict, deque, namedtuple
    from functools import cached_property, cmp_to_key, lru_cache, partial, partialmethod, reduce, singledispatch, singledispatchmethod, total_ordering, update_wrapper, wraps
    from heapq import heapify, heappop, heappush, heappushpop, heapreplace, merge, nlargest, nsmallest
    from itertools import accumulate, chain, combinations, combinations_with_replacement, compress, count, cycle, dropwhile, filterfalse, groupby, islice, permutations, product, repeat, starmap, takewhile, tee, zip_longest
    from math import acos, acosh, asin, asinh, atan, atan2, atanh, ceil, comb, copysign, cos, cosh, degrees, dist, e, erf, erfc, exp, expm1, fabs, factorial, floor, fmod, frexp, fsum, gamma, gcd, hypot, inf, isclose, isfinite, isinf, isnan, isqrt, ldexp, lgamma, log, log10, log1p, log2, modf, nan, perm, pi, prod, radians, remainder, sin, sinh, sqrt, tan, tanh, tau, trunc
    from random import betavariate, choice, choices, expovariate, gammavariate, gauss, getrandbits, getstate, lognormvariate, normalvariate, paretovariate, randint, randrange, sample, seed, setstate, shuffle, triangular, uniform, vonmisesvariate, weibullvariate
    from sys import setrecursionlimit, stderr, stdin, stdout
    try:
        import json # type: ignore
    except ImportError:
        pass
    try:
        import numpy # type: ignore
    except ImportError:
        pass
    try:
        import sortedcontainers # type: ignore
        from sortedcontainers import SortedDict, SortedItemsView, SortedKeyList, SortedKeysView, SortedList, SortedListWithKey, SortedSet, SortedValuesView # type: ignore
    except ImportError:
        pass

    if not SYNC_IO:
        BUFFER_SIZE = 8192

        # Credit: https://github.com/cheran-senthil/PyRival
        class FastIO(io.IOBase):
            newlines = 0

            def __init__(self, f):
                self._file = f
                self._fd = f.fileno()
                self.buffer = io.BytesIO()
                self.writable = 'x' in f.mode or 'r' not in f.mode  # type: ignore
                self.write = self.buffer.write if self.writable else None  # type: ignore

            def read(self):
                while True:
                    b = os.read(self._fd,
                                max(os.fstat(self._fd).st_size, BUFFER_SIZE))
                    if not b:
                        break
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2)
                    self.buffer.write(b)
                    self.buffer.seek(ptr)
                self.newlines = 0
                return self.buffer.read()

            def readline(self):
                while self.newlines == 0:
                    b = os.read(self._fd,
                                max(os.fstat(self._fd).st_size, BUFFER_SIZE))
                    self.newlines = b.count(b'\n') + (not b)
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2)
                    self.buffer.write(b)
                    self.buffer.seek(ptr)
                self.newlines -= 1
                return self.buffer.readline()

            def flush(self):
                if self.writable:
                    os.write(self._fd, self.buffer.getvalue())
                    self.buffer.truncate(0)
                    self.buffer.seek(0)

        class IOWrapper(io.IOBase):

            def __init__(self, file):
                self.buffer = FastIO(file)
                self.flush = self.buffer.flush
                self.writable = self.buffer.writable
                self.write = lambda s: self.buffer.write(s.encode('ascii'))
                self.read = lambda: self.buffer.read().decode('ascii')
                self.readline = lambda: self.buffer.readline().decode(
                    'ascii')  # type: ignore

        sys.stdin = IOWrapper(sys.stdin)
        sys.stdout = IOWrapper(sys.stdout)
        sys.stderr = IOWrapper(sys.stderr)
        input = lambda: sys.stdin.readline().rstrip('\r\n')

    eprint = lambda *args, **kwargs: LOCAL and print(
        *args, **kwargs, file=sys.stdout if TRACE_SYS_OUT else sys.stderr)

    def trace(*args):
        if not LOCAL:
            return
        frame = inspect.currentframe()
        if frame is None or frame.f_back is None:
            return
        frame = frame.f_back
        for i, x in enumerate(args):
            if i:
                eprint(end=', ')
            try:
                eprint(f'{x}: {eval(x, frame.f_globals, frame.f_locals)}',
                       end='')
            except:
                eprint(x, end='')
        eprint()


def solve(case_id):
    0
    


def main(args):
    num_cases = 1 << 0
    # num_cases = int(input())
    for case_id in range(1, num_cases + 1):
        # print(f'Case #{case_id}: ', end='')
        solve(case_id)
        # print(end='\n')
    return 0


if __name__ == '__main__':
    exit(main(sys.argv[1:]))
