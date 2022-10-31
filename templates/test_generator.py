LOCAL = 0x01

if True:
    import array, bisect, cmath, collections, functools, heapq, inspect, io, itertools, math, operator, os, random, re, sys, time
    from collections import ChainMap, Counter, OrderedDict, defaultdict, deque, namedtuple

    try:
        import numpy
    except ImportError:
        pass
    try:
        import sortedcontainers
    except ImportError:
        pass

    eprint = lambda *args, **kwargs: LOCAL and print(
        *args, **kwargs, file=sys.stderr)

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


def gen(n=2, *, case_id=-1):
    
    print(n,)
    


def main(args):
    random.seed(0)
    num_cases = 1
    # print(num_cases)
    for case_id in range(1, num_cases + 1):
        gen(case_id=case_id)
        # print(end='\n')
    return 0


if __name__ == '__main__':
    exit(main(sys.argv[1:]))
