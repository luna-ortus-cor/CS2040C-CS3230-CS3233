import sys,math
dp=[-1 for _ in range(100001)]

def isbin(n):
    for d in str(n):
        if d not in ['0','1']:
            return False
    return True

def repr(n):
    if dp[n]!=-1:return dp[n]
    if isbin(n):
        dp[n]=1
        return dp[n]
    for i in range(2,math.ceil((n+1)**0.5)):
        if n%i==0 and repr(i) and repr(n//i):
            dp[n]=1
            return dp[n]
    dp[n]=0
    return dp[n]


t = int(sys.stdin.readline())  
for _ in range(t):
    n = int(sys.stdin.readline())
    print('YES' if repr(n) else 'NO')
