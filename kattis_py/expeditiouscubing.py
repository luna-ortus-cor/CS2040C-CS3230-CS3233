def check(t1,t2,t3,t4,t5,t,eps=1e-9):
    tt=[t1,t2,t3,t4,t5]
    return True if (sum(tt)-max(tt)-min(tt))/3<=t+eps else False

t1,t2,t3,t4=map(float,input().split())
t=float(input().strip())
if check(t1,t2,t3,t4,100000,t):
    print('infinite')
elif not check(t1,t2,t3,t4,0.01,t):
    print('impossible')
else:
    ans,lo,hi=0,1,10000
    while lo<=hi:
        mid=(lo+hi)//2
        if check(t1,t2,t3,t4,mid/100,t):
            ans=mid/100
            lo=mid+1
        else:
            hi=mid-1
    print(f"{ans:.2f}")
