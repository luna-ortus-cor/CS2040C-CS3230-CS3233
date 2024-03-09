import sys
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    xs = [int(x) for x in sys.stdin.readline().strip().split()]
    a = sorted(xs)
    d={}
    start = 0
    for j in a:
        start+=(j-a[0]+1)
    d[a[0]]=start
    for j in range(len(a)):
        if a[j] in d:
            continue
        diff = a[j]-a[j-1]
        s = d[a[j-1]]
        s+=(j*diff)
        s-=((n-j)*diff)
        d[a[j]] = s
    for j in xs:
        print(d[j],end=' ')
    print('')
