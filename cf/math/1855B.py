import sys
#just greedy take smallest divisors to maximize interval length
#since any larger divisor will have one or more smaller prime factors...
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    ans = 1
    j = 2
    while n%j==0:
        ans+=1
        j+=1
    print(ans)
