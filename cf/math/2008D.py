import sys
#permutations all can be expressed as product of cycles
t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    p=[int(x)-1 for x in sys.stdin.readline().split()]
    c=[1-int(x) for x in sys.stdin.readline().strip()]
    ans=[0 for x in range(n)]
    visited=[0 for x in range(n)]
    for i in range(n):
        if visited[i]:continue
        j=i
        b=0
        q=[]
        while not visited[j]:
            #print(j)
            visited[j]=1
            j=p[j]
            q.append(j)
            b+=c[j]
        for k in q:
            ans[k]+=b
    for i in ans:
        print(i,end=' ')
    print()
