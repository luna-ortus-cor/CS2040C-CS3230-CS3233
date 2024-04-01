import sys
#this is just implementation, compare input numbers and see if satisfy given condition
t=int(sys.stdin.readline())
for _ in range(t):
    [a,b,c]=[int(_) for _ in sys.stdin.readline().split()]
    if a<b<c:
        print('STAIR')
    elif a<b>c:
        print('PEAK')
    else:
        print('NONE')
