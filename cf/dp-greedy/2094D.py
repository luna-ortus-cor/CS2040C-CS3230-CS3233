import sys, re
 
t=int(sys.stdin.readline().strip())
for _ in range(t):
    p=sys.stdin.readline().strip()
    q=[m[0] for m in re.finditer(r"(.)\1*",p)]
    s=sys.stdin.readline().strip()
    r=[m[0] for m in re.finditer(r"(.)\1*",s)]
    possible=True
    if len(q)!=len(r):possible=False
    else:
        for __ in range(len(q)):
            if q[__][0]!=r[__][0] or len(r[__])>2*len(q[__]) or len(r[__])<len(q[__]):
                possible=False
                break
    if possible:print("YES")
    else:print("NO")
