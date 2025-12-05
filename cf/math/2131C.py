import sys

from collections import defaultdict
from random import getrandbits
RD = getrandbits(31)

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n,k=map(int,sys.stdin.readline().split())
    d=defaultdict(int)
    for _ in sys.stdin.readline().split():
        idx=min(int(_)%k,(-int(_))%k)
        d[idx^RD]+=1
    for _ in sys.stdin.readline().split():
        idx=min(int(_)%k,(-int(_))%k)
        d[idx^RD]-=1
    if all(v==0 for v in d.values()):print("YES")
    else:print("NO")
