import sys

#this is just number theory
#to get to some n from unknown x
#first notice that by the bounds of the question, 1<=x<=1e9
#then the digit sum is at most 81>79
#which itself has digit sum at most 16
#then one more digit sum will bring it to the range of 1-9
#from there, multiplying by 9 and taking digit sum results in 9 always
#then just add n-9 to get n

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    print('digit')
    sys.stdout.flush()
    sys.stdin.readline()
    print('digit')
    sys.stdout.flush()
    sys.stdin.readline()
    print('digit')
    sys.stdout.flush()
    sys.stdin.readline()
    print('mul 9')
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
