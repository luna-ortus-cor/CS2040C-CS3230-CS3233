import sys

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    seq=[]
    for i in range(n):
        if i%2==0:seq.append("-1")
        else:
            if i==n-1:seq.append("2")
            else:seq.append("3")
    print(" ".join(seq))
