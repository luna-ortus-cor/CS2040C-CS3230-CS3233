import sys

T = int(sys.stdin.readline().strip())
ans=[]
for i in range(T):
    sys.stdin.readline()
    N=int(sys.stdin.readline().strip())
    s=0
    for j in range(N):
        s+=int(sys.stdin.readline().strip())
    if s%N==0:
        ans.append("YES")
    else:
        ans.append("NO")

for a in ans:
    print(a)
