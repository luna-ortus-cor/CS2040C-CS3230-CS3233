import sys

#partition is cool if for all partitition bk, all elements in b_k-1 appear in bk
#guaranteed each element ai satisfies 1<=ai<=n for n elements
#we make use of a greedy strategy
#start with just the first element a1 in the first partition
#then iterate through the elements of the array
#at each element, if the element is not in the previous partition, add it to the current partition and mark it as currently seen
#if the element is in the previous partition, decrease the number of elements required by 1 and mark it as previously seen and satisfied
#when the number of elements required reaches 0, make a cut, this defines the end of the new partition
#then update the previous partition with the current partition, and the previous seen with the current seen
#increment num partition by 1, and retun num partition at the end, this works since any incomplete partition at the end can be 
#merged with the next-to-last partition to form the actual last partition without destroying the cool partition propety

t = int(sys.stdin.readline())
for _ in range(t):
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))

    partition = 1
    prev_seen = [0] * (n + 1)
    curr_seen = [0] * (n + 1)

    prev_partition = []
    curr_partition = []
    need = 0

    prev_seen[a[0]] = 1
    prev_partition.append(a[0])
    need = 1

    for i in range(1, n):
        val = a[i]
        if curr_seen[val] == 0:
            curr_partition.append(val)
        curr_seen[val] = 1

        if prev_seen[val] == 1:
            need -= 1
            prev_seen[val] = 0  # mark as satisfied

        if need == 0:
            partition += 1
            prev_partition = curr_partition
            curr_partition = []
            # transfer curr_seen to prev_seen
            for x in prev_partition:
                prev_seen[x] = 1
                curr_seen[x] = 0  # reset for next
            need = len(prev_partition)

    print(partition)
