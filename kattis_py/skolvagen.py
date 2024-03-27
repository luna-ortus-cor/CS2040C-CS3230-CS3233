import sys
a=sys.stdin.readline().strip()
n=0;s=1
for c in a:
    if c=='N':n+=1
    elif c=='S':s+=1
    else:n+=1;s+=1
    t=n;n=min(n,s+1);s=min(s,t+1)
print(n)
