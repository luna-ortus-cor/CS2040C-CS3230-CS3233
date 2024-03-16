import sys
#not really dp, but wtv
#idea is to notice that to get from (1,1) to (2,n), the transition states are of the form
#(2,2k) or (1,2k+1), and in order to reach these transition states, there must exist an accessible
#path to these states i.e. '>' character on (2,2k-1) or (1,2k)
#so just check for every column, 
#if even column, at least one of (1,2k), (2,2k-1) is a '>' 
#if odd column, at least one of (2,2k+1), (1,2k) is a '>'
#if this is satisfied then it is possible to reach (2,n) from (1,1), else not possible
t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    g=[sys.stdin.readline().strip(),sys.stdin.readline().strip()]
    pos=True
    for i in range(1,n+1):
        if i%2==0 and g[0][i-1]=='<' and g[1][i-2]=='<':
            pos=False
            break
        elif i%2==1 and g[1][i-1]=='<' and g[0][i-2]=='<':
            pos=False
            break
    if pos:
        print('YES')
    else:
        print('NO')
