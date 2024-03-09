import sys
#just "undo" the prefix sum and compare against a 1..n range to find missing (if exists)
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
        
    keys = [x for x in range(1,n+1)]
    values = [1 for x in range(1,n+1)]
    a = [0]+[int(x) for x in sys.stdin.readline().strip().split()]
    
    d = {k:v for (k,v) in zip(keys,values)}
    missing = -1
    b = [a[x+1]-a[x] for x in range(n-1)]
    valid = True
    for j in b:
        if j in d:
            d.pop(j)
        else:
            if missing == -1:
                missing = j
            else:
                valid = False
                print("NO")
                break
    if not valid:
        continue
    leftover = [k for i,(k,v) in enumerate(d.items())]
    if missing==-1 or sum(leftover)==missing:
        print("YES")
    else:
        print("NO")
