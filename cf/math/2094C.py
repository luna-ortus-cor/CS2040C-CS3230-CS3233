import sys
 
t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    a=[]
    for __ in range(n):
        if __==0:a+=sys.stdin.readline().strip().split()
        elif __==n-1:a+=sys.stdin.readline().strip().split()[1:]
        else:sys.stdin.readline()
    b=[0 for _ in range(2*n)]
    for aa in a:b[int(aa)-1]=1
    a=[str(b.index(0)+1)]+a
    print(' '.join(a))
