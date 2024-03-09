import sys
 
t = int(sys.stdin.readline().strip())
for i in range(t):
    [b,c,h] = [int(x) for x in sys.stdin.readline().strip().split()]
    if c+h>b-1:
        print(b+b-1)
    else:
        print(c+h+c+h+1)
