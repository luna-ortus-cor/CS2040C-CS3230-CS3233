import sys
import math

f=[1]*10001
for i in range(1,10000):
    f[i]=f[i-1]*i

q=int(sys.stdin.readline().strip())
for i in range(q):
    n=int(sys.stdin.readline().strip())
    print(math.factorial(2*n)//math.factorial(n)**2//(n+1))
