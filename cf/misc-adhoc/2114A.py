import sys

#this problem is trivial by first checking that n is a perfect square, otherwise it is not possible
#if n is a paerfect square, then just output 0 sqrt(n) since 0**2 + sqrt(n)**2 = n

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=n**0.5
    if int(a)**2!=n:
        print(-1)
    else:
        print(f'0 {int(a)}')
