import sys
 
n=int(sys.stdin.readline())
a=[int(x) for x in sys.stdin.readline().split()]
odd=0
zero=0
ans=0
for i in a:
    if i>0:
        ans+=abs(i-1)
    elif i<0:
        ans+=abs(i+1)
        odd+=1
    else:
        zero+=1
if zero==0:
    if odd%2==0:
        print(ans)
    else:
        print(ans+2)
else:
    print(ans+zero)
