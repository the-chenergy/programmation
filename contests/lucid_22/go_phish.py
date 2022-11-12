if True:
    SYNC_IO = 0x0
    TRACE_SYS_OUT = 0x0
    LOCAL = 0x01

    import array, bisect, cmath, collections, functools, heapq, inspect, io, itertools, math, operator, os, random, re, sys, time
    from collections import ChainMap, Counter, OrderedDict, defaultdict, deque, namedtuple

    try:
        import numpy
    except ImportError:
        pass
    try:
        import sortedcontainers
        from sortedcontainers import SortedDict, SortedKeyList, SortedSet
    except ImportError:
        pass

    BUFFER_SIZE = 8192

    # Credit: https://github.com/cheran-senthil/PyRival
    class FastIO(io.IOBase):
        newlines = 0

        def __init__(self, file):
            self._file = file
            self._fd = file.fileno()
            self.buffer = io.BytesIO()
            self.writable = 'x' in file.mode or 'r' not in file.mode
            self.write = self.buffer.write if self.writable else None

        def read(self):
            while True:
                b = os.read(self._fd,
                            max(os.fstat(self._fd).st_size, BUFFER_SIZE))
                if not b:
                    break
                ptr = self.buffer.tell()
                self.buffer.seek(0,
                                 2), self.buffer.write(b), self.buffer.seek(ptr)
            self.newlines = 0
            return self.buffer.read()

        def readline(self):
            while self.newlines == 0:
                b = os.read(self._fd,
                            max(os.fstat(self._fd).st_size, BUFFER_SIZE))
                self.newlines = b.count(b'\n') + (not b)
                ptr = self.buffer.tell()
                self.buffer.seek(0,
                                 2), self.buffer.write(b), self.buffer.seek(ptr)
            self.newlines -= 1
            return self.buffer.readline()

        def flush(self):
            if self.writable:
                os.write(self._fd, self.buffer.getvalue())
                self.buffer.truncate(0), self.buffer.seek(0)

    class IOWrapper(io.IOBase):

        def __init__(self, file):
            self.buffer = FastIO(file)
            self.flush = self.buffer.flush
            self.writable = self.buffer.writable
            self.write = lambda s: self.buffer.write(s.encode('ascii'))
            self.read = lambda: self.buffer.read().decode('ascii')
            self.readline = lambda: self.buffer.readline().decode('ascii')

    if not SYNC_IO:
        sys.stdin = IOWrapper(sys.stdin)
        sys.stdout = IOWrapper(sys.stdout)
        sys.stderr = IOWrapper(sys.stderr)
        input = lambda: sys.stdin.readline().rstrip('\r\n')

    eprint = lambda *args, **kwargs: LOCAL and print(
        *args, **kwargs, file=sys.stdout if TRACE_SYS_OUT else sys.stderr)

    def trace(*args):
        if not LOCAL:
            return
        frame = inspect.currentframe().f_back
        for i, x in enumerate(args):
            if i:
                eprint(end=', ')
            try:
                eprint(f'{x}: {eval(x, frame.f_globals, frame.f_locals)}',
                       end='')
            except:
                eprint(x, end='')
        eprint()


def rem(x: str):
    for i in range(len(x)):
        yield x[:i] + x[i + 1:]


def dot(x):
    for i in range(len(x)):
        yield x[:i] + '.' + x[i + 1:]


# https://www.hackerrank.com/contests/lpc-2022/challenges/lpc2022-go-phish
def solve(case_id):
    ne = int(input())
    es = set()
    bs = set()
    for _ in range(ne):
        e = input().replace(' ', '').lower()
        es.add(e)
        for x in dot(e):
            bs.add(x)
    nc = int(input())
    ci = defaultdict(list)
    ans = ['c'] * nc
    for i in range(nc):
        c = input().replace(' ', '').lower()
        if c in es:
            ans[i] = 'e'
        else:
            for x in rem(c):
                if x in es:
                    ans[i] = 'b'
                    break
            else:
                for x in dot(c):
                    if x in bs:
                        ans[i] = 'b'
                        break
                else:
                    ci[c].append(i)
    for e in es:
        for x in rem(e):
            if x in ci:
                for i in ci[x]:
                    ans[i] = 'b'
                ci.pop(x)
    pr = {'e': 'EMPLOYEE', 'b': 'BOT', 'c': 'CUSTOMER'}
    print(*(pr[x] for x in ans), sep='\n')


def main(args):
    num_cases = 1
    # num_cases = int(input())
    for case_id in range(num_cases):
        # print(f'Case #{case_id + 1}: ', end='')
        solve(case_id)
        # print(end='\n')
    return 0


if __name__ == '__main__':
    exit(main(sys.argv[1:]))
