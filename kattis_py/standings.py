import sys
from collections import defaultdict

T=int(sys.stdin.readline().strip())
for _ in range(T):
    sys.stdin.readline()
    N=int(sys.stdin.readline().strip())
    d=defaultdict(int)
    for __ in range(N):
        name,p=sys.stdin.readline().split()
        d[int(p)]+=1
    taken=[0]*N
    for i in range(1,N+1):
        if i in d:
            d[i]-=1
            taken[i-1]=1
    rem=[]
    for k,v in d.items():
        if v>0:rem.extend([k]*v)
    rem=sorted(rem)
    idx=0
    ans=0
    for i in range(N):
        if taken[i]==0:
            ans+=abs(rem[idx]-(i+1))
            taken[i]=1
            idx+=1
    print(ans)
