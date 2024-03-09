import sys
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    a = sys.stdin.readline().strip()
    b = sys.stdin.readline().strip()
    c = sys.stdin.readline().strip()
    possible=False
    for j in range(n):
        if c[j]!=a[j] and c[j]!=b[j]:
            print("YES")
            possible=True
            break
    if not possible:
        print("NO")
