import sys

#we are asked, for given permutation of 0,1,...,n-1, say p0,p1,...,pn-1 and q0,q1,...,qn-1
#to find an array r0,r1,...,rn-1 s.t. ri=max_j=0^i (2^pj+2^qi-j)
#initially realise that the maximum such value is evidently the one with the largest pj/qi-j
#since with the contraints of 2^n+2^n<2^n+1+2^anything we want to pick the exponent with the largest value
#this can be done efficiently by iterating through 0<=i<=n-1 and maintaining the maximum exponent seen till then
#let max_p[i] store the INDEX of the largest exponent visited thus far in p, and likewise max_q[i] for q
#this can be calcuated in one pass in O(n)
#then we iteratively fill in the array r, at each index i, we find the maximum exponent up to that point
#and then we figure out which of the arrays p or q has this maximum exponent
#there are edge cases where both p and q have the maximum exponent, in which case we need to compare the 
#remaining exponents to determine which sum is larger; and also the edge case where all exponents are equal

MOD=998244353
t=int(sys.stdin.readline())

for _ in range(t):
    n=int(sys.stdin.readline())
    p=list(map(int, sys.stdin.readline().split()))
    q=list(map(int, sys.stdin.readline().split()))
    max_p=[0]*n
    max_q=[0]*n

    for i in range(1, n):
        max_p[i] = i if p[i]>p[max_p[i-1]] else max_p[i-1]
        max_q[i] = i if q[i]>q[max_q[i-1]] else max_q[i-1]
        
    res = [0] * n
    for i in range(n):
        m=max(p[max_p[i]],q[i-max_p[i]],q[max_q[i]],p[i-max_q[i]])
        if p[max_p[i]]==m and q[i-max_p[i]]<m and q[max_q[i]]<m and p[i-max_q[i]]<m:
            res[i]=(pow(2,p[max_p[i]],MOD)+pow(2,q[i-max_p[i]],MOD))%MOD
        elif p[max_p[i]]<m and q[i-max_p[i]]==m and q[max_q[i]]<m and p[i-max_q[i]]<m:
            res[i]=(pow(2,p[max_p[i]],MOD)+pow(2,q[i-max_p[i]],MOD))%MOD
        elif p[max_p[i]]<m and q[i-max_p[i]]<m and q[max_q[i]]==m and p[i-max_q[i]]<m:
            res[i]=(pow(2,q[max_q[i]],MOD)+pow(2,p[i-max_q[i]],MOD))%MOD
        elif p[max_p[i]]<m and q[i-max_p[i]]<m and q[max_q[i]]<m and p[i-max_q[i]]==m:
            res[i]=(pow(2,q[max_q[i]],MOD)+pow(2,p[i-max_q[i]],MOD))%MOD
        elif p[max_p[i]]==m and q[max_q[i]]==m:
            if q[i-max_p[i]]>p[i-max_q[i]]:
                res[i]=(pow(2,p[max_p[i]],MOD)+pow(2,q[i-max_p[i]],MOD))%MOD
            else:
                res[i]=(pow(2,q[max_q[i]],MOD)+pow(2,p[i-max_q[i]],MOD))%MOD
        elif p[max_p[i]]==m and p[i-max_q[i]]==m:
            if q[i-max_p[i]]>q[max_q[i]]:
                res[i]=(pow(2,p[max_p[i]],MOD)+pow(2,q[i-max_p[i]],MOD))%MOD
            else:
                res[i]=(pow(2,q[max_q[i]],MOD)+pow(2,p[i-max_q[i]],MOD))%MOD
        elif q[i-max_p[i]]==m and q[max_q[i]]==m:
            if p[max_p[i]]>p[i-max_q[i]]:
                res[i]=(pow(2,p[max_p[i]],MOD)+pow(2,q[i-max_p[i]],MOD))%MOD
            else:
                res[i]=(pow(2,q[max_q[i]],MOD)+pow(2,p[i-max_q[i]],MOD))%MOD
        else:
            if p[max_p[i]]>q[max_q[i]]:
                res[i]=(pow(2,p[max_p[i]],MOD)+pow(2,q[i-max_p[i]],MOD))%MOD
            else:
                res[i]=(pow(2,q[max_q[i]],MOD)+pow(2,p[i-max_q[i]],MOD))%MOD

    print(" ".join(map(str, res)))
