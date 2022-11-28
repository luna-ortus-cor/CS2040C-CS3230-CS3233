import sys
import math

def factorsum(n):
    s=1
    i=2
    while i*i<=n:
        if n%i==0:
            if i!=n//i:
                s+=i
                s+=n//i
            else:
                s+=i
        i+=1
    if n-s==0:
        return 'perfect'
    elif abs(n-s)<=2:
        return 'almost perfect'
    else:
        return 'not perfect'

mat=[]
for i in sys.stdin:
    mat.append(int(i.strip()))

for j in mat:
    print(str(j), ' ', str(factorsum(j)))
