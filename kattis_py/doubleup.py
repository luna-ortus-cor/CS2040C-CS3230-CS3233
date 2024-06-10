import sys,math
#idea is iterate through numbers in v, use temp for store (new v)
#then replace v with temp, reset temp, iterate until v is 1 element
#at each iteration try to combine numbers, if cannot combine just store number
#at the same time remove numbers that are strictly valleys (incl start and end!)
#i.e. ai>aj<ak, remove aj
#use python instead of c++ due to large number 2^100
#also will store x for 2^x in array instead of 2^x
#careful of array indices, handle side cases also
#to avoid TLE force all combines in temp (earlier part only does 1 combine)
#e.g. 4 2 2 -A> 4 4 -B> 8, if/elif/else is A, while temp[-1]==temp[-2] is B

n=int(sys.stdin.readline().strip())
v=[int(math.log2(int(x))) for x in sys.stdin.readline().split()]
while len(v)!=1:
    temp=[];i=0;
    while(i<len(v)):
        #print(i,v,temp)
        if i==0 and v[i]<v[i+1]:pass
        elif i==len(v)-1 and v[i]<v[i-1]:pass
        elif i==0 and v[i]>v[i+1]:temp.append(v[i])
        elif i==len(v)-1 and v[i]>v[i-1]:temp.append(v[i])
        elif i==len(v)-1 and v[i]==v[i-1]:temp.append(v[i])
        elif v[i]==v[i+1]:
            temp.append(v[i]+1);i+=1
        elif v[i-1]>v[i]<v[i+1]:pass
        else:temp.append(v[i])
        i+=1
        while len(temp)>=2 and temp[-1]==temp[-2]:
           temp=temp[:-1];temp[-1]+=1
    v=temp
print(pow(2,v[0]))
