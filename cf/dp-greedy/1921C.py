import sys
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    [n,f,a,b]=[int(x) for x in sys.stdin.readline().strip().split()]
    ms = [0]+ [int(x) for x in sys.stdin.readline().strip().split()]
    ms.sort()
    possible = True
    for m in range(n):
        f -= min(b, a*(ms[m+1]-ms[m]))
        if f<=0:
            possible=False
            break
    if not possible:
        print("NO")
        continue
    print("YES")    
