import sys

#again, NT
#since limit is 1<=x<=1e9, use 1e9-1=999999999
#then take digit sum of 999999999x to get 81 always
#then add n-81 if n is not 81, else we are done

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    print('mul 999999999')
    sys.stdout.flush()
    sys.stdin.readline()
    print('digit')
    sys.stdout.flush()
    sys.stdin.readline()
    if n!=81:
        print(f'add {n-81}')
        sys.stdout.flush()
        sys.stdin.readline()
    print('!')
    sys.stdout.flush()
    sys.stdin.readline()
