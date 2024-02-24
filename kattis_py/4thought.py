import sys
tc=int(sys.stdin.readline())
op=[' + ',' - ',' * ',' / ']
def find(n):
    for i in op:
        for j in op:
            for k in op:
                s = '4'+i+'4'+j+'4'+k+'4'+' = '+str(n)
                if(eval(s.replace('/','//').replace('=','=='))):return s
for _ in range(tc):
    n=int(sys.stdin.readline())
    s=find(n)
    if s:print(s)
    else:print('no solution')
