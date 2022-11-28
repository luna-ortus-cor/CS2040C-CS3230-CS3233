import sys
    
def binomial(n,k):
    res=1
    if k>n-k:
        k=n-k
    for i in range(k):
        res*=(n-i)
        res//=(i+1)
    return res

def S(n):
    return int(binomial(2*(n+1),n+1)//(n+2))

n = int(sys.stdin.readline().strip())
print(S(n))
