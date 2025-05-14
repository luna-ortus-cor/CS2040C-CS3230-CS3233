import sys

#this is simply just the binary exponentiation algorithm
#however due to the constraints of the inputs (<=10e18) we cannot
#use C++ as multiplying two <=10e18 numbers will lead to overflow
#the idea is just represent e in binary, then from LSB, if 1, multiply
#res by a; at each bit square a and integer divide e by 2
#then res will become a^e by virtue of a^(sum 2^i)=a^(2^0)*...*a(2^k)
#and a^(2i)=a^i*a^i=(a^i)^2 i.e. a^(2^i)=(a^(2^(i-1)))^2
#and ab congruent (a mod m)(b mod m) (mod m) i.e. multiplication doesnt affect mod
#proof: a=pm+q,b=rm+s, then ab=prm^2+(p+r)m+qs (mod m)=qs (mod m)=(a mod m)(b mod m) (mod m)

def exp(a,e,m):
    a%=m
    res=1
    while e:
        if e&1:res=res*a%m
        a=a*a%m
        e>>=1
    return res

a,e,m=map(int,sys.stdin.readline().split())
print(exp(a,e,m))
