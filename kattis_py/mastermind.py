from collections import defaultdict
n,code,guess=input().split()
n=int(n)
r,s=0,0
d,e=defaultdict(int),defaultdict(int)
for i in range(n):
    if code[i]==guess[i]:r+=1
    else:
        d[code[i]]+=1
        e[guess[i]]+=1
for c in d.keys():
    s+=min(d[c],e.get(c,0))
print(r,s)
