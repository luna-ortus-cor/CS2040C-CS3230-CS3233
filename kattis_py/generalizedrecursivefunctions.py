#straightforward dp question with memoization
#done in python due to very large answers 
#e.g. if x,y=99,99, ai,bi,c,d=(1,0),(0,1),(1,1),(1,0)
#ans is 177066519804632768423207758654609660282592752851464074092012262708936784671
#determine ai,bi,c,d first, then initialize dp table of 100x100 with -1, dp[0][0]=d
#for each x,y, calculate according to recursion given
#base case is if x<=0 or y<=0, then return d
#or if entry in dp table is not negative, return dp[x][y]
#else after determining value, update corresponding entry in dp table
#final ans at dp[x][y]. note we can reuse same dp table for within the same f for different x,y

import sys
sys.setrecursionlimit(100000)

def f(x,y,dp,v,m):
    if x<=0 or y<=0:return v[m-1][1]
    if dp[x][y]>-1:return dp[x][y]
    value=v[m-1][0]
    for i in range(m-1):value+=f(x-v[i][0],y-v[i][1],dp,v,m)
    dp[x][y]=value
    return value

n=int(sys.stdin.readline().strip())
for _ in range(n):
    line = [int(_) for _ in sys.stdin.readline().strip().split()]
    v=[(line[2*i],line[2*i+1]) for i in range(len(line)//2)]
    m=len(v)
    line = [int(_) for _ in sys.stdin.readline().strip().split()]
    q=[(line[2*i],line[2*i+1]) for i in range(len(line)//2)]
    dp=[[-1 for _ in range(100)] for _ in range(100)]
    dp[0][0]=v[m-1][1]

    for x, y in q:
        print(f(x,y,dp,v,m))
    print()
