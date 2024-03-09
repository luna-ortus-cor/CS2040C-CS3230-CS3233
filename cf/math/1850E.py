import sys
import math
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    [n,c]=[int(i) for i in sys.stdin.readline().strip().split()]
    ws = [int(x) for x in sys.stdin.readline().strip().split()]
    w2s = [x**2 for x in ws]
    c-=sum(w2s)
    c//=4
    a=n
    b=sum(ws)
    ans=(-b + math.sqrt(b**2 + 4*c*a))/(2*a)
    print(ans)
