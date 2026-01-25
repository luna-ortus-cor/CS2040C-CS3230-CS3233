class UFDS:
    def __init__(self,n):
        self.parent=list(range(n))
        self.size=[1]*n
    
    def find(self,i):
        if self.parent[i]==i:return i
        self.parent[i]=self.find(self.parent[i])
        return self.parent[i]
        
    def union(self,i,j):
        root_i=self.find(i)
        root_j=self.find(j)
        if root_i!=root_j:
            if self.size[root_i]<self.size[root_j]:
                root_i,root_j=root_j,root_i
            self.parent[root_j]=root_i
            self.size[root_i]+=self.size[root_j]
        return self.size[root_i]
        
n=int(input())
d={}
ufds=UFDS(2*n)
curr=0
for _ in range(n):
    a,b=input().strip().split()
    if a not in d:
        d[a]=curr
        curr+=1
    if b not in d:
        d[b]=curr
        curr+=1
    print(ufds.union(d[a],d[b]))
