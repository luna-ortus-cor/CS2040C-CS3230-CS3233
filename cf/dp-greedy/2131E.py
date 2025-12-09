import sys

#we can use 2 pointer to solve this
#first note that for some index i,
#if a[i]!=b[i] but a[i]^a[i+1]^...^a[i+k]=b[i]
#then naturally a[i] can be transformed into b[i]
#at the same time, this uniquely determines all of a[i+1],a[i+1],...,a[i+k-1]
#since the xor operations must be done on these indexes prior to xor with a[i]
#thus using 2 pointers and a variable to track the "current xor value"
#if d!=e and f^a[d]==b[e] then there exist a sequence of xor that will transform a[e] to b[e]
#ending at a[d] (note a[d] is not changed)
#so move the pointer e up to d and store the value f in c[e]
#we can calculate the xor of a[i], e<i<d  without back tracking from d by using the property of xor
#if c[e]=f=b[e] then the value that must be in c[e+1] is f^a[e], since f=a[e]^c[e+1]
#else if d!=e and f^a[d]!=b[e] then we have not found any xorable sequence, so xor f with a[d] and increment d
#if d==e (either initially or after moving e up to d) then check if a[d]==b[e]
#if equal, increment d,e, and reset f to 1, and set c[d]=b[e]
#if not equal, set f to a[d] and increment d
#finally check if all c[i]==b[i], if so then print "YES" else "NO"

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    a=[int(__)for __ in sys.stdin.readline().split()]
    b=[int(__)for __ in sys.stdin.readline().split()]
    c=[-1 for __ in range(n)]
    d=0
    e=0
    f=1
    while d<n:
        if d!=e and f^a[d]==b[e]:
            f^=a[d]
            while e<d:
                c[e]=f
                f^=a[e]
                e+=1
            f=1
        elif d!=e and f^a[d]!=b[e]:
            f^=a[d]
            d+=1
            continue
        else:
            pass
        
        if d==e and a[d]==b[e]:
            c[d]=b[e]
            d+=1
            e+=1
            f=1
        elif d==e and a[d]!=b[e]:
            f=a[d]
            d+=1
        else:
            pass
    
    if all(c[i]==b[i] for i in range(n)):print("YES")
    else:print("NO")
