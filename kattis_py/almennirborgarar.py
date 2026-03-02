#use python instead of c++ due to overflow
def check(S,X,times):
    return sum([S//t for t in times])>=X
    
n,m=map(int,input().split())
times=list(map(int,input().split()))
lo,hi=1,1000000000000000000000000000
ans=2*hi
while(lo<=hi):
    mid=(lo+hi)//2
    if check(mid,m+1,times):
        ans=mid
        hi=mid-1
    else:
        lo=mid+1
print(ans)
