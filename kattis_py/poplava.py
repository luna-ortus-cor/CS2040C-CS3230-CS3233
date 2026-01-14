import sys

N,X=map(int,sys.stdin.readline().split())
if X<=((N-1)*(N-2))//2:
    k=((N-1)*(N-2))//2-X
    subset1,subset2=[],[N]
    for i in range(N-2,0,-1):
        if i<=k:
            subset1.append(N-1-i)
            k-=i
        else:
            subset2.append(N-1-i)
    ans=subset1+subset2+[N-1]
    print(' '.join([str(_)for _ in ans]))
else:print(-1)
