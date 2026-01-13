import sys
 
t=int(sys.stdin.readline().strip())
for _ in range(t):
    n,m,l,r=map(int,sys.stdin.readline().split())
    if r>=n-m:
        r-=n-m
        n-=n-m
    else:
        n-=r
        r-=r
    if abs(l)>=n-m:
        l+=n-m
    print(l,r)
