import sys
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    a = [int(x) for x in sys.stdin.readline().strip().split()]
    b = [a[i]-a[i-1] for i in range(1,len(a))]
    c = min(b)
    if c<0:
        print(0)
    else:
        print(c//2 +1)
