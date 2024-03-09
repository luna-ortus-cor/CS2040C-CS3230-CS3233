import sys
#just greedy evaluate cost in both directions
#need to check direction of query!
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = int(sys.stdin.readline().strip())
    locs = [int(x) for x in sys.stdin.readline().strip().split()]
    left = [0, 1]
    for j in range(1,n-1):
        if abs(locs[j]-locs[j-1]) > abs(locs[j]-locs[j+1]):
            left.append(1)
        else:
            left.append(abs(locs[j]-locs[j+1]))
    right = [0, 1]
    for j in range(n-2,0,-1):
        if abs(locs[j]-locs[j-1]) > abs(locs[j]-locs[j+1]):
            right.append(abs(locs[j]-locs[j-1]))
        else:
            right.append(1)
    #print(left)
    #print(right)
    
    left_prefix = []
    left_sum = 0
    right_prefix = []
    right_sum = 0
    for j in range(n):
        left_sum += left[j]
        left_prefix.append(left_sum)
        right_sum += right[j]
        right_prefix.append(right_sum)
    #print(left_prefix)
    #print(right_prefix)
    m = int(sys.stdin.readline().strip())
    for j in range(m):
        [a,b]=[int(x) for x in sys.stdin.readline().strip().split()]
        if a < b: 
            print(abs(left_prefix[b-1]-left_prefix[a-1]))
        else:
            print(abs(right_prefix[n-a]-right_prefix[n-b]))
