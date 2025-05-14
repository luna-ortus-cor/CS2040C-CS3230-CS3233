import sys

#suppose there exists some sequence of length k consecutive integers
#a, a+1, ..., a+(k-1) such that a + (a+1) + ... + (a+k-1) = n
#then n = k(2a+k-1)/2 -> 2n=k(2a+k-1)
#considering parity, we see that when k is even, 2a+k-1 is odd, and when
#k is odd, 2a+k-1 is even
#thus, 2n always has an odd factor i.e. n cannot be a power of 2
#so we first check if n is a power of 2, n&(n-1)==0
#next (this is unnecessary) for all odd numbers we can simply let the sum be
#n=(n//2)+(1+n//2)
#otherwise, to choose the consecutive sequence with the smallest number of summands
#we want to minimize k i.e. maximize a
#so iterating from 2 to 1+n//2
#determine which factors k of 2n allow for an integer solution for a
#this can be done by simply checking parity, since 2a+k-1=2n/k is the opposite parity
#of k, so as long as k+2n/k has odd parity, an integer solution for a always exists
#then we can simply use n=k(2a+k-1)/2 -> a=(1-k+2n/k)/2 and the rest is just printing

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    if n&(n-1)==0:print("IMPOSSIBLE")
    elif n%2==1:print(f"{n} = {n//2} + {n//2+1}")
    else:
        for k in range(2,n//2+1):
            if (2*n)%k==0:
                if (k+(2*n)//k)%2==1:
                    a=(1-k+(2*n)//k)//2
                    b=[str(a+i) for i in range(k)]
                    print(f"{n} = {' + '.join(b)}")
                    break
