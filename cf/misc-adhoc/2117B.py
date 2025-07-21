import sys

#This constructs the sequence 1 3 5 7 ... 8 6 4 2 i.e. alternating the side which the integers are added to
#This works as the maximum element can be removed as long as it is between two other elements positionally
#Thus, avoid putting the larger elements at the sides
#More generally, any permutation with 1 and 2 at the sides satisfies this, as any element in between them
#Is guaranteed to be larger, and thus a maximum at some point in time

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=[0 for _ in range(n)]
    side=0
    idx1,idx2=0,n-1
    for i in range(1,n+1):
        if side==0:
            a[idx1]=str(i)
            idx1+=1
            side=1-side
        else:
            a[idx2]=str(i)
            idx2-=1
            side=1-side
    print(' '.join(a))
