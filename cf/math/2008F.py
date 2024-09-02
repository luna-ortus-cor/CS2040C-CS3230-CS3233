import sys
import math

m=1000000007
t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    a=[int(x) for x in sys.stdin.readline().split()]
    s=sum(a)
    w=(n*(n-1))//2
    c=0
    for i in a:
        c+=(s-i)*i
    c//=2
    #print((c*w)%m)
    g=math.gcd(c,w)
    p=c//g
    q=w//g
    #print(c,w,p,q)
    print((p*pow(q,-1,m))%m)
