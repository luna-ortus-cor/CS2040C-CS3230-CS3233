import sys
 
tc=int(sys.stdin.readline())
for t in range(tc):
    n=int(sys.stdin.readline())
    a=[int(x) for x in sys.stdin.readline().split()]
    odd,exist=-1,False
    for idx in range(len(a)):
        if a[idx]%2==0:print('1');print(-~idx);exist=True;break
        else:
            if odd==-1:odd=idx
            else:print('2');print(-~odd,-~idx,sep=' ');exist=True;break
    if not exist:print('-1')
