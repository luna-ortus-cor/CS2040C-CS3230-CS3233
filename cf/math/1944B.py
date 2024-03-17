import sys
#consider any half of the array with n numbers each repeated twice
#for any 1..n, either it appears once in each half, or it appears twice in one half
#also note that the number of "appears twice in one half" is the same for both halfs of the array
#now we also have a XOR a = 0 and a XOR 0 = a, so clearly for any value of k, to form array of length 2k just
#in each half take all pairs (i.e. the "appears twice in one half") while number taken is <=2k
#after this both subarrays have XOR product 0
#then while number taken <=2k take the numbers in both halfs of the array
t=int(sys.stdin.readline())
for _ in range(t):
    [n,k]=[int(_) for _ in sys.stdin.readline().split()]
    a=[int(_) for _ in sys.stdin.readline().split()]
    l=a[:len(a)//2]
    r=a[len(a)//2:]
    lset=set(l)
    rset=set(r)
    lans=[]
    rans=[]
    lk,rk=2*k,2*k
    for i in lset:
        if i not in rset and lk>=2:
            lans+=[i]
            lans+=[i]
            lk-=2
    for i in rset:
        if i not in lset and rk>=2:
            rans+=[i]
            rans+=[i]
            rk-=2
    for i in lset:
        if i in rset and lk>=1:
            lans+=[i]
            rans+=[i]
            lk-=1
    print(*lans,sep=' ')
    print(*rans,sep=' ')
