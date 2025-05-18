import sys

#the key idea here is first since n-1 matches are played, total number of victories
#claimed cannot be more than n-1, and that between any two adjacent players both
#cannot claim to have 0 victories (since that is not possible)

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=[int(x) for x in sys.stdin.readline().split()]
    if sum(a)>=n:
        print("YES")
    elif sum(a)<n//2:
        print("YES")
    else:
        lie=False
        for i in range(n-1):
            if a[i]+a[i+1]==0:
                print("YES")
                lie=True
                break
        if not lie:
            print("NO")
