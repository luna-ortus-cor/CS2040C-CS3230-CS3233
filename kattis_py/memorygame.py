import sys
from collections import Counter

N,K=map(int,sys.stdin.readline().split())
a=list(map(int,sys.stdin.readline().split()))

if K==2*N or K==2*N-1:
    print(N)
else:
    freq=Counter(a)
    matched=sum(1 for v in freq.values()if v==2)
    if matched==N-1 and K==2*N-2:
        print(N)
    else:
        print(matched)
