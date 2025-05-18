import sys

#again, number theory
#by taking the digit sum of 9x twice, we can guarantee result of 9
#then just add n-9 to get n

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    print('mul 9')
    sys.stdout.flush()
    sys.stdin.readline()
    print('digit')
    sys.stdout.flush()
    sys.stdin.readline()
    print('digit')
    sys.stdout.flush()
    sys.stdin.readline()
    print(f'add {n-9}')
    sys.stdout.flush()
    sys.stdin.readline()
    print('!')
    sys.stdout.flush()
    sys.stdin.readline()
