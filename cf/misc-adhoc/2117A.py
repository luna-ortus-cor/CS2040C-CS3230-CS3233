import sys

#The condition is to just check if x > the max number of closed doors = distance between first and last closed doors
#So check the index of the first and last closed doors, then check if x < difference

t=int(sys.stdin.readline())
for _ in range(t):
    n,x=map(int,sys.stdin.readline().split())
    a=list(map(int,sys.stdin.readline().split()))
    b=a[::-1]
    idx1=a.index(1)
    idx2=n-b.index(1)
    if idx2-idx1>x:print('NO')
    else:print('YES')
