import sys
#2 subset sums have same parity => sum of array is even
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    a = [int(x) for x in sys.stdin.readline().strip().split()]
    if sum(a)%2==0:
        print("YES")
    else:
        print("NO")
