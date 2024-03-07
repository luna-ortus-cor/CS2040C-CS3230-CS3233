import sys
 
n=int(sys.stdin.readline())
b=[100,20,10,5,1]
ans=0
for i in b:
    ans+=n//i
    n-=(n//i)*i
print(ans)
