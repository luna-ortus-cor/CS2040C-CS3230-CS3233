import sys

#just sort array, if sum of first and last divisible by 2 print 0, continue
#then calculate if removing elements from left, how many to remove for sum of first and last to be divisible by 2
#similarly calculate the same if removing elements from right
#print min of these
#only tricky part is the handling of indexes and num ele removed when removing from right
#could also sort twice, once normally once in reverse and do remove from left for both if easier

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=list(map(int,sys.stdin.readline().split()))
    a.sort()
    if (a[0]+a[-1]) % 2 == 0:
        print(0)
    else:
        left=0
        while (a[left]+a[-1])%2!=0:
            left+=1
        right=n-1
        while (a[0]+a[right])%2!=0:
            right-=1
        print(min(left,n-right-1))
        
