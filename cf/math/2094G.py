import sys

from collections import deque

t=int(sys.stdin.readline().strip())
for _ in range(t):
    q=int(sys.stdin.readline().strip())
    d=deque()
    sums=[0,0]
    rev=0
    count=0
    s=0
    for __ in range(q):
        a=list(map(int,sys.stdin.readline().split()))
        if a[0]==1:
            if rev==0:
                ele=d.pop()
                sums[0]+=s-ele
                sums[0]-=ele*count
                sums[0]+=ele
                sums[1]-=ele
                sums[1]+=ele*count
                sums[1]-=s-ele
                d.appendleft(ele)
                print(sums[rev])
            else:
                ele=d.popleft()
                sums[0]-=ele
                sums[0]+=ele*count
                sums[0]-=s-ele
                sums[1]+=s-ele
                sums[1]-=ele*count
                sums[1]+=ele
                d.append(ele)
                print(sums[rev])
        if a[0]==2:
            rev=1-rev
            print(sums[rev])
        if a[0]==3:
            count+=1
            if rev==0:
                d.append(a[1])
                sums[0]+=a[1]*count
                sums[1]+=s+a[1]
                print(sums[rev])
                s+=a[1]
            else:
                d.appendleft(a[1])
                sums[1]+=a[1]*count
                sums[0]+=s+a[1]
                print(sums[rev])
                s+=a[1]
