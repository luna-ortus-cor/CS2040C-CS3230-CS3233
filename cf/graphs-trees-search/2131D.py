import sys

from collections import deque

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    adj=[[]for __ in range(n+1)]
    for __ in range(n-1):
        u,v=map(int,sys.stdin.readline().split())
        adj[u].append(v)
        adj[v].append(u)
    
    leaf={}
    for u in range(1,n+1):
        if len(adj[u])==1:
            leaf[u]=1
    numleaf=len(leaf)
    
    minop=numleaf
    for u in range(1,n+1):
        count=0
        if u in leaf:count+=1
        for v in adj[u]:
            if v in leaf:count+=1
        minop=min(minop,numleaf-count)
    print(minop)
