import sys

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n,k=map(int,sys.stdin.readline().split())
    awake=0
    ans=0
    for c in sys.stdin.readline().strip():
        if c=='1':
            awake=k
        elif c=='0' and awake:
            awake-=1
        else:
            ans+=1
    print(ans)
