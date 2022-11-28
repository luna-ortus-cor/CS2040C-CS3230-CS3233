import sys

def count(A,t=47):
    S=0
    N=0
    H={}
    H[0]=1
    
    for a in A:
        S+=a
        if S-t in H:
            N+=H[S-t]
        if S not in H:
            H[S]=1
        else:
            H[S]+=1
    return N

T=int(sys.stdin.readline().strip())
for i in range(T):
    sys.stdin.readline()
    N=int(sys.stdin.readline().strip())
    A=[int(j) for j in sys.stdin.readline().split()]
    print(count(A))
