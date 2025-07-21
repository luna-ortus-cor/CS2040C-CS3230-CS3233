import sys

#array sorted in non-decreasing order
#a_i+1 written to diff array than ai if a_i+1>ai+1
#so we can greedy and remove all a_i+1 that would have been written to same array as ai
#effectively, keep track of last element, then for each next element in array
#increment array count if next>last+1 (then set last=next)

def max_num_array(a):
    count=0
    last=-2
    for num in a:
        if num>last+1:
            count+=1
            last=num
    return count

t = int(sys.stdin.readline())
for _ in range(t):
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))
    print(max_num_array(a))
