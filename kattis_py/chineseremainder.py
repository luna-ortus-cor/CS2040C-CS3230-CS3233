import sys
#CRT, use extended euclidean algo to find values for bezout identity
#n1m1+n2m2=1, i.e. multiplicative modulo inverse, n1 for m1 mod m2, n2 for m2 mod m1
#from there use ans=a1n2m2+a2n1m1 mod m1m2
#for some reason cant work in c++ (suspect long long not large enough to hold answer)

def mod(a,b):return(a%b+b)%b #to handle negative modulo

def eea(a,b): #returns {x,y}, mult mod inv a mod b, b mod a
    if b==0: return(1,0)
    (f,s) = eea(b, a%b);
    return (s, f-a//b*s)
    
t=int(sys.stdin.readline())
for i in range(t):
    [a,n,b,m]=[int(x) for x in sys.stdin.readline().strip().split()]
    K=m*n
    f,s=eea(n,m)
    #print(f,s)
    ans=((((b*n)%K)*mod(f,m))%K + (((a*m)%K)*mod(s,n))%K) %K
    print(ans,K)
