import sys
t=int(sys.stdin.readline())
for _ in range(t):
    n,k=[int(x) for x in sys.stdin.readline().split()]
    a=[int(x) for x in sys.stdin.readline().split()]
    min_a = min(a)
    max_a = max(a)
    
    if max_a-min_a>k+1:
        print("Jerry")
        continue
    
    count=0
    for ai in a:
        if ai-min_a>k:
            count+=1
            
    if count>1:
        print("Jerry")
        continue
    
    s=sum(a)
    if s%2==1:
        print("Tom")
    else:
        print("Jerry")
