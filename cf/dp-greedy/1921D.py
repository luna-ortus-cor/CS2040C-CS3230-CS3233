import sys
#greedy with 2 pointers
t = int(sys.stdin.readline().strip())
for i in range(t):
    [n,m]=[int(x) for x in sys.stdin.readline().strip().split()]
    ns = [int(x) for x in sys.stdin.readline().strip().split()]
    ms = [int(x) for x in sys.stdin.readline().strip().split()]
    ns.sort()
    ms.sort()
    ns_start = 0
    ns_end = n-1
    ms_start = 0
    ms_end = m-1
    total_diff = 0
    while ns_start<=ns_end:
        max_case=0
        max_diff=0
        if abs(ns[ns_start]-ms[ms_start]) >= max_diff:
            max_diff = abs(ns[ns_start]-ms[ms_start])
            max_case=1
        if abs(ns[ns_start]-ms[ms_end]) >= max_diff:
            max_diff = abs(ns[ns_start]-ms[ms_end])
            max_case=2
        if abs(ns[ns_end]-ms[ms_start]) >= max_diff:
            max_diff = abs(ns[ns_end]-ms[ms_start])
            max_case=3
        if abs(ns[ns_end]-ms[ms_end]) >= max_diff:
            max_diff = abs(ns[ns_end]-ms[ms_end])
            max_case=4
        #print(max_case)
        total_diff += max_diff
        if max_case == 1:
            ns_start+=1
            ms_start+=1   
        if max_case == 2:
            ns_start+=1
            ms_end-=1   
        if max_case == 3:
            ns_end-=1
            ms_start+=1   
        if max_case == 4:
            ns_end-=1
            ms_end-=1   
    print(total_diff)
