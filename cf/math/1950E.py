import sys
#idea is to iterate through all possible substr lengths (up to ceil(n/2), since beyond that the substr cannot repeat)
#then for each substr length, check if substr length can divide str length
#if can divide, means we can generate substr 
#note that the substr we consider must be "contiguous" i.e. we can consider (if 1-indexing)
#[1:i],[i+1:2i],[2i+1:3i],... as it is easy to show otherwise that a repeat of a non-contiguous substring
#will differ from original string by more than 1 character (in most cases)
#now for any substring we have generated, consider several cases
#case 1: this substring does not differ from all other substring -> answer found
#case 2: this substring differs by at most 1 from all other substring
#case 3: this substring differs by more than 1 for at least 1 other substring -> not valid answer
#case 4: this substring differs by at most 1 for more than 1 but less than all other substring -> not valid answer
#case 5: this substring differs by at most 1 for only 1 other substring -> answer found
#to see why case 3 is true, suppose in the worst case that the substring differs by more than 1 for only 1 other substring
#clearly a repeat of the substring will differ from the original string by at least more than 1 character
#reflexively, a repeat of the other substring will also differ from original by at least more than 1 character
#similar logic can be applied to show case 4 invalid
#in case 2, notice that it is possible that, since the substring differs by at most 1 from all other substring,
#there may exist one of the other substrings satisfying case 5
#thus we actually need to check just 2 distinct substring possibilities (the need to check more is negated by the fact
#that those would be in cases 3 and 4 already)
#so checking substring against all other substrings is clearly O(n//i * i) = O(n)
#iterating through substr lengths is O(n) also
#it seems like O(n^2) which should fail given constraints on str length
#but we can use number theory to show that majority of substr lengths we consider are not possible 
#in fact the number of substr lengths we consider is on the order of O(log n) only
#as an example consider multiplying the first few prime numbers
#notice 2*3*5*7*11*13*17>2*10e5 already, 2^18>2*10e5 already as well
#thus O(n log n) solution exists and suffices to pass given constraints
def strcmp(a,b):
    r=0
    for i in range(len(a)):
        if(a[i]!=b[i]):r+=1
    return r

def strlen(s,n):
    for i in range(1,n//2 + 1):
        if n%i!=0:
            continue
        sa,sb=0,i
        ea,eb=-i,n
        start=s[sa:sb]
        end=s[ea:eb]
        d1=0
        d2=0
        for j in range(n//i):
            dd1=strcmp(start,s[sa+j*i:sb+j*i])
            dd2=strcmp(end,s[ea-j*i:eb-j*i])
            #print(d1,d2,dd1,dd2)
            if dd1>=2 or dd2>=2:
                d1=-1;d2=-1
                break
            else:
                d1+=dd1;d2+=dd2
        #print(i,d1,d2)
        if 0<=d1<=1 or 0<=d2<=1:
            return i
    return n

t = int(sys.stdin.readline())  
for _ in range(t):
    n = int(sys.stdin.readline())
    s=sys.stdin.readline().strip()
    print(strlen(s,n))
