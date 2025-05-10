import sys

#we use python to make use of the slice functionality
#this is still quite inefficient but works due to 
#small bounds of the problem
#more efficient would be to create node class
#with pointers to ahead and behind nodes
#store pointer to each node i in vector 
#then access nodes using the pointer in the vector
#and change the forward/backward pointers
#based on the Ti beating Tj

n,m=[int(_) for _ in sys.stdin.readline().strip().split()]
ts=[i+1 for i in range(n)]
for _ in range(m):
    ti, tj=sys.stdin.readline().strip().split()
    i,j=int(ti[1:]),int(tj[1:])
    posi,posj=ts.index(i),ts.index(j)
    if posi>posj:
        ts=ts[:posj]+ts[posj+1:posi+1]+[ts[posj]]+ts[posi+1:]
for _ in ts:
    print('T'+str(_),end=' ')
