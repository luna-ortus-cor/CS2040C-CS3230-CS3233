from functools import lru_cache
from collections import Counter

drinks=[]
reconstruct=[]
eps=1e-9

#apparently this allows us to memoize without needing
#explicit dp table :o
#we use 3d dp, on the remaining money, remaining units, and drink index
#also use eps tolerance due to floating point errors
#if m,u are close enough to 0, then solution found
#elif m,u are <0 then no soln exists
#else either we pick more of current drink
#or pick next drink
#so take max of these
#topdown most logical, and helps in reconstruction
#thus dp[m][u][idx]=1 if we take drink idx at m,u
#and we dont take i.e. go to next idx if dp[m][u][idx]=0
@lru_cache(maxsize=None)
def dp(m,u,idx):
    if idx==d:
        if abs(m-0)<eps and abs(u-0)<eps:return 1
        else:return 0
    if u<-eps or m<-eps:return 0
    drink,amt,cost=drinks[idx]
    return max(dp(m-cost,u-amt,idx),dp(m,u,idx+1))

#reconstruct soln, just check where dp[m][u][idx]=1
def soln(m,u,idx):
    if idx==d:return
    drink,amt,cost=drinks[idx]
    #this will TLE
    '''
    if dp(m-cost,u-amt,idx)==1:
        reconstruct.append(drink)
        soln(m-cost,u-amt,idx)
    else:soln(m,u,idx+1)
    '''
    #but we can further prune it
    #since if there exists a solution at (m,u,idx+1)
    #then that solution will contain no drinks at idx
    #because drink indexes are visited in sequence always
    #and if none of these are true then no soln exists
    #for this subproblem
    if dp(m,u,idx+1)==1:soln(m,u,idx+1)
    elif dp(m-cost,u-amt,idx)==1:
        reconstruct.append(drink)
        soln(m-cost,u-amt,idx)
    else:return

#note since 1% of 100% strength of 1/1 size drink is 1 unit
#then unit=strength*size (factor of 1000 on each side)
M,U,d=map(float,input().split())
d=int(d)
for i in range(d):
    drink,strength,size,cost=input().split()
    drinks.append((drink,float(int(strength)*float(eval(size))),float(cost)))
    
#dp(M,U,0) #soln will compute dp alr
soln(M,U,0)
reconstruct=Counter(reconstruct)
if len(reconstruct)==0:print('IMPOSSIBLE')
else:print('\n'.join([f"{k} {v}" for k,v in reconstruct.items()]))
