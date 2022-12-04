import sys

factorial = [1]
for i in range(1,51):
    factorial.append(factorial[i-1]*i)
    
def find(n,k,d):
    ans=[]
    while len(ans)!=n:
        j=0
        for i in range(1,n+1):
            if d[i]==0:
                j+=1
            if (i-j)*factorial[n-len(ans)-1]>=k and d[i]==1:
                #print(i,j,(i-j),(i-j-1)*factorial[n-len(ans)-1])
                k-=(i-j-1)*factorial[n-len(ans)-1]
                d[i]=0
                ans.append(i)
                break
    return ans

for line in sys.stdin:
    n,k=0,0
    [n,k]=[int(x) for x in line.strip().split()]
    k+=1
    d={}
    for i in range(1,n+1):
        d[i]=1
    ans=find(n,k,d)
    for i in ans:
        print(i,end=' ')
    print('')
