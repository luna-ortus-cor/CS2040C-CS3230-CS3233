import sys

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n,m,k=map(int,sys.stdin.readline().split())
    if (n,k)==(2,3):
        print("1 2 3 "*(m//3))
        print("2 3 1 "*(m//3))
        continue
    ans=[[0 for _ in range(m)] for __ in range(n)]
    times,num=n*m//k,1
    for i in range(n*m):
        r,c=i//m,i%m
        if (r+c)%2==0:
            ans[r][c]=num
            times-=1
            if times==0:
                times=n*m//k
                num+=1
    if times==0:
        times=n*m//k
        num+=1
    for i in range(n*m):
        r,c=i//m,i%m
        if (r+c)%2==1:
            ans[r][c]=num
            times-=1
            if times==0:
                times=n*m//k
                num+=1
    for __ in ans:
        print(' '.join(map(str,__)))
