from collections import deque

n=int(input())
a=list(map(int,input().split()))
d={}
c=[]
stack=deque()
possible=True
for i in range(n):
    e=a[i]
    if e in d:
        d[e][2]=i
        while len(stack)>0:
            ee=stack.pop()
            if ee==e:
                stack.append(ee)
                break
        if len(stack)==0:possible=False
    else:
        d[e]=[len(c),i,i]
        c.append(e)
        stack.append(e)
if possible:
    print(len(c))
    for i in c:
        print(d[i][1]+1,d[i][2]+1,i)
else:print("IMPOSSIBLE")
