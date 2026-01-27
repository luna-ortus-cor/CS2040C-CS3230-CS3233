T=int(input())
for _ in range(T):
    N=int(input())
    colors=input().split()
    coloridx={color:i for i,color in enumerate(colors)}
    adj=[[0]*N for __ in range(N)]
    M=int(input())
    for __ in range(M):
        c1,c2=input().split()
        adj[coloridx[c1]][coloridx[c2]]=adj[coloridx[c2]][coloridx[c1]]=1
    
    ans=[]
    total=0
    visited=[0]*N
    stack=[[0,0]]
    path=[]
    while stack:
        depth,c=stack[-1]
        if c==N:
            stack.pop()
            if path:visited[path.pop()]=0
            continue
        
        stack[-1][1]+=1
        if visited[c]==0:
            if not path or not adj[path[-1]][c]:
                visited[c]=1
                path.append(c)
                if len(path)==N:
                    total+=1
                    if not ans:ans=[colors[i] for i in path]
                    visited[path.pop()]=0
                else:
                    #we can prob optimize this by setting c to 
                    #first color not already in path (instead of 0)
                    #by tracking via bitset, since at most 12 bits
                    stack.append([len(path),0])

    print(total)
    print(' '.join(ans))
