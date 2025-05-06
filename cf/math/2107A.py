import sys
t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=[int(x) for x in sys.stdin.readline().split()]
    if all(x==a[0] for x in a):
        print("No")
        continue
    print("Yes")
    m=max(a)
    b=['1' if ai==m else '2' for ai in a]
    print(' '.join(b))
    
