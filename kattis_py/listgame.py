import sys

for i in sys.stdin:
    x=int(i.strip())
k=0    
i=2
while i*i<=x:
    if x%i==0:
        k+=1
        x/=i
    else:
        i+=1

print(k+1)
