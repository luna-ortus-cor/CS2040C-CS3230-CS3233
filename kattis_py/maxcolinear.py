from math import gcd
from collections import defaultdict

n=int(input())
while(n>0):
    a=[]
    for i in range(n):
        x,y=map(int,input().split())
        a.append([x,y])
    if n==1:print(1)
    elif n==2:print(2)
    else:
        ans=0
        for i in range(n):
            d=defaultdict(int)
            for j in range(i+1,n):
                x1,y1=a[i]
                x2,y2=a[j]
                dx=x1-x2
                dy=y1-y2
                g=gcd(dx,dy)
                dx//=g
                dy//=g
                pos=(dx>0)^(dy>0)
                d[(abs(dx),abs(dy),pos)]+=1
                ans=max(ans,d[(abs(dx),abs(dy),pos)])
        print(ans+1)
    n=int(input())
