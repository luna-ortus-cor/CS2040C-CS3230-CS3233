import sys

#notice that any solution must consist of a repeating p-cycle such that each p-cycle sums to q
#and total sum of all elements n sums to m
#so, if p does not divide n, then we can arbitrarily choose the "leftover" from the p-cycle in the
#n elements and so a solution is always possible
#if p divides n, then we must check that the total sum of the p-cycles (of which there are n//p many)
#each having sum q, sums to m i.e. sum of all n elements is m
#if yes then a solution exists, else no solution exists

t=int(sys.stdin.readline())
for _ in range(t):
    n,m,p,q=[int(x) for x in sys.stdin.readline().split()]
    if n%p!=0:
        print("YES")
    else:
        if q*(n//p)==m:
            print("YES")
        else:
            print("NO")
