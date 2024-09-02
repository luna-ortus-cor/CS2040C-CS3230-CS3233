import sys

t=int(sys.stdin.readline().strip())
for _ in range(t):
    [l,r]=[int(x) for x in sys.stdin.readline().split()]
    d=2*(r-l)
    n=round(d**0.5)
    if (n+1)**2 - (n+1)<=d:print(n+1)
    elif n**2 - n<=d:print(n)
    elif (n-1)**2 - (n-2)<=d:print(n-1)
    else:
        while n**2 - n >d:
            n-=1
        print(n)
