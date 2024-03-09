import sys
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    [n,m,k,H] = [int(x) for x in sys.stdin.readline().strip().split()]
    h = [int(x) for x in sys.stdin.readline().strip().split()]
    diff = [abs(H-x) for x in h]
    s = [1 if (x%k==0 and x!=0 and x<=(m-1)*k) else 0 for x in diff]
    ans = sum(s)
    print(ans)
