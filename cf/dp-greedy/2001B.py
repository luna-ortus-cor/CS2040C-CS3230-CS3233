import sys
n=int(sys.stdin.readline().strip())
for i in range(n):
    m=int(sys.stdin.readline().strip())
    if m%2==0:
        print(-1)
    else:
        a=[2*j+1 for j in range(m//2+1)]
        b=[2*j for j in range(1,m//2+1)]
        c=a+b[::-1]
        for j in c:print(j,end=' ');
        print('')
