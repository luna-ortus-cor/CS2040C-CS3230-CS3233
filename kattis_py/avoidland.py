import sys

n = int(sys.stdin.readline().strip())
rows,cols=[0]*n,[0]*n
for x in range(n):
    y=sys.stdin.readline().strip().split()
    i,j=int(y[0]),int(y[1])
    rows[i-1]+=1
    cols[j-1]+=1
zerorow,zerocol=[],[]
xrow,xcol=[],[]

for a in range(n):
    if rows[a]==0:
        zerorow.append(a)
    elif rows[a]>1:
        xrow.extend([a]*(rows[a]-1))
    else:
        continue

for b in range(n):
    if cols[b]==0:
        zerocol.append(b)
    elif cols[b]>1:
        xcol.extend([b]*(cols[b]-1))
    else:
        continue
    
moves=0
for c in range(len(zerorow)):
    moves+=abs(zerorow[c]-xrow[c])
for d in range(len(zerocol)):
    moves+=abs(zerocol[d]-xcol[d])
    
print(moves)
