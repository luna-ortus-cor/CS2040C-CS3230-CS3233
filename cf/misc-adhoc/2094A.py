import sys
 
t=int(sys.stdin.readline().strip())
for _ in range(t):
    w=sys.stdin.readline().strip().split()
    for ww in w:
        print(ww[0],end='')
    print()
