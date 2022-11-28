import sys

while True:
    [N,M]=[int(x) for x in sys.stdin.readline().strip().split()]
    if N==0 and M== 0:
        break
    jack={}
    for i in range(N):
        j = int(sys.stdin.readline().strip())
        jack[j]='.'
    count=0
    for i in range(M):
        j = int(sys.stdin.readline().strip())
        if j in jack:
            count+=1
    print(count)
