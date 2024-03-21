import sys,math
#this is brute force, i dont think a faster/easier solution exists that is as simple
#just iterate through all possible road divisions, evaluate sum on each side, check if satisfy condition
#update with value that brings road division closer to middle
#dont forget to return smaller value if there are 2 solutions equally close to middle
t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=[int(_) for _ in sys.stdin.readline().strip()]
    lsum=0
    rsum=sum(a)
    mid=n/2
    ans=-1
    for idx in range(n):
        if idx==0:
            if rsum>=(n-rsum):
                ans=0
        lsum+=a[idx]
        rsum-=a[idx]
        if lsum<=math.floor((idx+1)/2) and rsum>=math.ceil((n-idx-1)/2):
            temp=idx+1
            if temp<=mid:
                ans=temp
            else:
                if abs(mid-temp)<abs(mid-ans):
                    ans=temp
    print(ans)
