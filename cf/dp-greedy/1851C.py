import sys
#just take k from start, k from end, to satisfy must have start<end 
#note if less than k elements, then start>=end always (start=n and/or end=0)
t = int(sys.stdin.readline().strip())
for i in range(t):
    [n,k] = [int(x) for x in sys.stdin.readline().strip().split()]
    a = [int(x) for x in sys.stdin.readline().strip().split()]
    startidx = 0
    endidx = n-1
    startcol = a[startidx]
    endcol = a[endidx]
    
    if startcol==endcol:
        b = [1 if a[x]==startcol else 0 for x in range(n)]
        if sum(b)>=k:
            print("YES")
        else:
            print("NO")
    else:
        temp = k-1
        while temp and startidx<n:
            startidx+=1
            if startidx<n and a[startidx]==startcol:
                temp-=1
        temp = k-1
        while temp and endidx>=0:
            endidx-=1
            if endidx>=0 and a[endidx]==endcol:
                temp-=1
        if startidx<endidx:
            print("YES")
        else:
            print("NO")
