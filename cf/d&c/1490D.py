import sys
#iterate through array, find max, save as distance d from root
#then divide into subproblem i.e. do same for left and right subarray of max
#recombine distance array
def solve(ds,nums,d):
    if ds==[]:
        return ds
    currmax=0
    curridx=0
    if len(nums)==1:
        ds[0]=d
        return ds
    for idx in range(len(nums)):
        if nums[idx]>currmax:
            currmax=nums[idx]
            curridx=idx
    ds[curridx]=d
    return solve(ds[:curridx],nums[:curridx],d+1)+[ds[curridx]]+solve(ds[curridx+1:],nums[curridx+1:],d+1)
 
tc=int(sys.stdin.readline())
for t in range(tc):
    n=int(sys.stdin.readline())
    nums=[int(x) for x in sys.stdin.readline().split()]
    ds=solve([-1 for x in range(n)],nums[0:n],0)
    for d in ds:
        print(d,end=' ')
    print()
