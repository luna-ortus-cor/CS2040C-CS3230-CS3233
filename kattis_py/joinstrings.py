import sys
sys.setrecursionlimit(10**6)


N = int(sys.stdin.readline().strip())

s = [sys.stdin.readline().strip() for x in range(N)]

def recursive_print(arr,idx):
    print(s[idx],end='')
    for i in arr[idx]:
        recursive_print(arr,i)
    

indices=[[] for _ in range(N)]
x=0
for o in range(N-1):
    [x,y]=[int(z)-1 for z in sys.stdin.readline().strip().split()]
    indices[x].append(y)
    
if N!=1:
    recursive_print(indices,x)
else:
    sys.stdout.write(s[0])
