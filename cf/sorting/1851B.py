import sys
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    a = [int(x) for x in sys.stdin.readline().strip().split()]
    odd = []
    even = []
    for j in range(len(a)):
        if a[j]%2==0:
            even.append(j)
        else:
            odd.append(j)
    a.sort()
    oddsort = []
    evensort = []
    for j in range(len(a)):
        if a[j]%2==0:
            evensort.append(j)
        else:
            oddsort.append(j)
    if set(odd)==set(oddsort) and set(even)==set(evensort):
        print("YES")
    else:
        print("NO")
