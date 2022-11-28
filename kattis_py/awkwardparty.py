import sys

n = int(sys.stdin.readline().strip())
d = {}
g = sys.stdin.readline().strip().split()

for i in range(len(g)):
    if int(g[i]) not in d:
        d[int(g[i])] = (i,int(10e6))
    else:
        (a,b)=d[int(g[i])]
        d[int(g[i])] = (i, int(min(b,abs(i-a))))

m=int(10e6)
for key,value in d.items():
    a,b=value
    if b<m:
        m=b

if m==int(10e6):
    print(n)
else:
    print(m)
