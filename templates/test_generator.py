from solution import *


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
