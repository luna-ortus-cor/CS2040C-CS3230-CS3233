import sys

#the key is to note that the height of drone is monotonic non-decreasing and we greedy at each obstacle
#we do this in two passes
#first, we make a forward pass where we track the possible height range at each obstacle i
#then possible[i] stores this possible height range (that we can reach)
#d stores the (known and unknown) values of the drone program
#so if it is a 0, then newlow=max(low, li) (since we must find smallest bounds for low for successful program)
#similar for newhigh=min(high,ri) (since we must find smallest boudns for high for successful program)
#then if it is a 1, same thing except we add 1 to low and high, i.e.
#newlow=max(low+1, li) and newhigh=min(high+1, ri)
#if it is -1 (unknown) then we compare the two cases of 0 and 1
#i.e. low0 high0 low1 high1 with the above defn of newlow, newhigh
#first check that low0<=high0 or/and low1<=high1 (since lo<=hi necessarily else program fails)
#if none of these are true then no such program can exist, set valid to false, break
#else, we take newlow to be the min of all the valid ranges and newhigh to be the max of all the valid ranges
#since when we have the option to decide the program we should pick the one that gives us the largest range
#after that, if valid soln exists, backtrack in one pass to find out the program
#we begin with any possible value in the last range
#for each obstacle we work out the last possible low,high value (at that obstacle)
#then if the program is a 0 or 1 (i.e. d[i] is 0 or 1) we just keep it and we change h accordingly
#else if h-1 ("new" height of drone) is within the prev low and prev high bounds and 
#h is within the bounds of the obstacle, we set d[i] from -1 to 1 (in res[i]) and decrease h
#else if h is within the prev low and prev high bounds and
#h is within the bounds of the obstacle, we set d[i] from -1 to 0 (in res[i])
#else there is actually no valid solution by backtracking and we break
#finally print -1 if no valid solution else print res

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    d=list(map(int,sys.stdin.readline().split()))
    l,r=[],[]
    for _ in range(n):
        li,ri=map(int,sys.stdin.readline().split())
        l.append(li)
        r.append(ri)
    low=high=0 
    possible=[(0,0)]

    valid=True
    for i in range(n):
        new_low=new_high=-1
        di=d[i]
        li=l[i]
        ri=r[i]
        if di==0:
            new_low=max(low,li)
            new_high=min(high,ri)
        elif di==1:
            new_low=max(low+1,li)
            new_high=min(high+1,ri)
        else:
            low0=max(low,li)
            high0=min(high,ri)
            low1=max(low+1,li)
            high1=min(high+1,ri)

            candidates=[]
            if low0<=high0:
                candidates.append((low0,high0))
            if low1<=high1:
                candidates.append((low1,high1))

            if not candidates:
                valid=False
                break
            new_low=min(c[0] for c in candidates)
            new_high=max(c[1] for c in candidates)

        if new_low>new_high:
            valid=False
            break
        low,high=new_low,new_high
        possible.append((low,high))

    if not valid:
        print(-1)
        continue
    
    res=[0]*n
    h=possible[-1][0]
    for i in reversed(range(n)):
        prev_low,prev_high=possible[i]
        li,ri=l[i],r[i]
        if d[i]!=-1:
            res[i]=d[i]
            h-=d[i]
        else:
            if prev_low<=h-1<=prev_high and li<=h<=ri:
                res[i]=1
                h-=1
            elif prev_low<=h<=prev_high and li<=h<=ri:
                res[i]=0
            else:
                valid=False
                break
    if not valid:
        print(-1)
    else:
        print(' '.join(map(str,res)))
