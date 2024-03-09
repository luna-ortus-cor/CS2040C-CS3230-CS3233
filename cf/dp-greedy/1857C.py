import sys
#every min value in array of mins must be in original array
#so greedy, sort array of mins, smallest min must occur (n-1) times,
#next smallest min (n-2) times, etc. 
#at the end we have original array with n-1 ele, so just add inf to array
inf = 1000000000
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    a = [int(x) for x in sys.stdin.readline().strip().split()]
    a.sort()
    idx = 0
    ans = []
    for j in range(n-1,0,-1):
        ans.append(a[idx])
        idx+=j
    ans.append(inf)
    for j in ans:
        print(j,end=' ')
    print('')
