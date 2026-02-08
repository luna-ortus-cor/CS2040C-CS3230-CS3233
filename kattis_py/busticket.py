from bisect import bisect_left
s,p,m,n=map(int,input().split())
t=list(map(int,input().split()))
dp=[0]*(n+1)
# dp[n] = 0, and we fill dp from n-1 down to 0
for i in range(n-1,-1,-1):
    single=s+dp[i+1]
    j=bisect_left(t,t[i]+m)
    period=p+dp[j]
    dp[i]=min(single,period)
print(dp[0])
