import sys

#first observe the effect of the two operations
#first operation does ai -> ai - i
#second operation does ai -> ai - (n-i+1)
#consider doing x first operations and y second operations
#then we will have ai -> ai - xi - y(n-i+1) = ai - (x-y)i - y(n+1) = 0 (if exploded)
#so, each ai is (x-y)i + y(n+1)
#this is an AP with first term a1 = (x-y) + y(n+1) and common difference (x-y)
#thus we just have to check if the sequence is an AP satisfying these constraints (x and y are arbitrary)
#furthermore, check that c=a1-d is divisible by n+1 and non-negative and that x,y>=0

t = int(sys.stdin.readline())
for _ in range(t):
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))

    if n == 1:
        # Single element must be zero (no ops needed) or can't be exploded
        print("YES" if a[0] == 0 else "NO")
        continue

    d = a[1] - a[0]
    is_arith = True
    for i in range(2, n):
        if a[i] - a[i-1] != d:
            is_arith = False
            break

    if not is_arith:
        print("NO")
        continue

    c = a[0] - d
    if c < 0 or c % (n + 1) != 0:
        print("NO")
        continue

    y = c // (n + 1)
    x = d + y
    if x < 0:
        print("NO")
        continue

    # Double check formula holds exactly (sanity check)
    # a_i should equal d * i + c
    valid = True
    for i in range(n):
        if a[i] != d * (i + 1) + c:
            valid = False
            break

    print("YES" if valid else "NO")
