import sys

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    a=list(map(int,sys.stdin.readline().strip().split()))
    b=list(map(int,sys.stdin.readline().strip().split()))
    step1,step2=0,0
    for i in range(n):
        if a[i]>b[i]:step1+=a[i]-b[i]
        if a[i]<b[i]:step2+=b[i]-a[i]
    print(step1+1)
