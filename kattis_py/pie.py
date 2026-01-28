import math

def num_slice(r,sz):
    ans=0
    for pie in r:
        ans+=math.floor(math.pi*pie*pie/sz)
    return ans

t=int(input())
for _ in range(t):
    N,F=map(int,input().split())
    r=list(map(int,input().split()))
    lo,hi=1,3141592653590
    ans=0
    while(lo<=hi):
        mid=(lo+hi)//2
        if num_slice(r,mid/1000)>=F+1:
            ans=mid
            lo=mid+1
        else:
            hi=mid-1
    print(ans/1000)
