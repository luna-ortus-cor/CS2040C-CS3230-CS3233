import sys

#convert all to cents and handle from there
#note the difference between calling int() and round()
#also convert R to decimal directly instead of %

t=int(sys.stdin.readline())
for _ in range(t):
    R,B,M=map(float,sys.stdin.readline().split())
    B=round(100*B);M=round(100*M);R/=100
    found=False
    for i in range(1200):
        B+=round(R*B)
        B-=M
        if B<=0:print(i+1);found=True;break
    if not found:print('impossible')
