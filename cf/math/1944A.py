import sys
#obviously there are n-1 bridges from island 1 to the other islands, if all are destroyed
#answer is 1, else there exists a path to any other island
#so optimal bridge destroying, if k>=n-1 then 1 else n
t=int(sys.stdin.readline())
for _ in range(t):
    [n,k]=[int(_) for _ in sys.stdin.readline().split()]
    if k>=n-1:
        print(1)
    else:
        print(n)
