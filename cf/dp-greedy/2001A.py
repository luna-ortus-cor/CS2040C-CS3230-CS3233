import sys
n=int(sys.stdin.readline().strip())
for i in range(n):
    m=int(sys.stdin.readline().strip())
    a=[int(x) for x in sys.stdin.readline().split()]
    b=[0 for x in range(100)]
    for j in a:
        b[j-1]+=1
    s=sum(b)
    print(sum(b)-max(b))
