import sys

from collections import defaultdict

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    a=list(map(int,sys.stdin.readline().split()))
    d=defaultdict(int)
    for i in a:
        e=0
        while i:
            if i%2==1:d[e]+=1
            i=i>>1
            e+=1
    max_e=max(d.keys()) if d else 0
    m=0
    for i in a:
        e=1
        s=0
        for j in range(max_e+1):
            if i%2==1:s+=e*(n-d[j])
            else:s+=e*d[j]
            e*=2
            i=i>>1
        m=max(s,m)
    print(m)
