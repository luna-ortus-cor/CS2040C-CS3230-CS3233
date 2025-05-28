import sys
from collections import deque

#we use binary search on the answer for this
#first note that the minimum number of batteries is equal to the max weight of any edge in a valid path
#so we binary search on the answer, more specifically let x in 1,1e9 be the answer
#i.e. x is the minimum of all the max edge weight among all valid paths
#then let us fix x, and that for some x, we use graph search (here bfs) to determine if a path exists
#by only using edges with weight less than or equal to x
#we make two checks, the first being the weight is less than or equal x
#the second is the constraint in the problem, the weight is less than the batteries we have
#we can also "greedy" for the batteries at each node because we can show that at the end
#if a valid path exists and we have more batteries than the theoretical minimum we can always take
#less batteries at some nodes along the path and still have it be valid
#this works because bfs/dfs are useful at determining if a path exists
#but not useful to determine the best possible path among all valid paths
#so then we binary search on the value of x, i.e. if for some x a valid path exists using only
#edges with weight less than or equal to x then we will search again in [1,x) else we search in (x,1e9]
#note also that we cannot use a visited array to keep track of nodes explored
#this is because there exists the possibility where two nodes share a child with one node having more
#batteries than the other node, then when we visit the first node (with less batteries) and
#assuming we have enough to access its child, we will mark it as visited, which will result in 
#the second node (with more batteries) not exploring this child and this can lead to incorrect answer
#as subsequently the exploration by the first node may not have a valid path due to insufficient batteries
#while the second node (if it continued exploring) would have sufficient batteries for a valid path

t = int(sys.stdin.readline())
for _ in range(t):
    n,m=list(map(int,sys.stdin.readline().split()))
    b=[0]+list(map(int,sys.stdin.readline().split()))
    adj=[[] for i in range(n+1)]
    for j in range(m):
        u,v,w=list(map(int,sys.stdin.readline().split()))
        adj[u].append((v,w))
    
    def reachable(x):
        #visited=[0 for i in range(n+1)]
        q=deque([(1,b[1])])
        #visited[1]=1
        while q:
            curr,currb=q.pop()
            if curr==n:return True
            for node in adj[curr]:
                #if visited[node[0]]==0 and node[1]<=x and currb>=node[1]:
                if node[1]<=x and node[1]<=currb:
                    #visited[node[0]]=1
                    q.append((node[0],currb+b[node[0]]))
        return False
    
    lo=1
    hi=1000000000
    ans=-1
    while lo<=hi:
        mid=(lo+hi)//2
        if reachable(mid):
            ans=mid
            hi=mid-1
        else:
            lo=mid+1
    print(ans)
        
