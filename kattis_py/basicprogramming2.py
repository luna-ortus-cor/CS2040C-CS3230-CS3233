import sys
from collections import defaultdict

[N,t]=[int(x) for x in sys.stdin.readline().split()]
A = [int(x) for x in sys.stdin.readline().split()]

d=defaultdict(int)
for a in A:d[a]+=1
if t==1:
    for a in A:
        if 7777-a in d:
            print("Yes")
            exit()
    print("No")
elif t==2:
    print("Unique" if len(d)==len(A) else "Contains duplicate")
elif t==3:
    for i,(k,v) in enumerate(d.items()):
        if v>N/2:
            print(k)
            exit()
    print(-1)
elif t==4:
    B=sorted(A)
    if N%2==1:
        print(B[N//2])
    else:
        print(B[N//2-1],B[N//2],sep=' ')
else:
    B=sorted(A)
    for b in B:
        if 100<=b<=999:print(b,end=' ')
