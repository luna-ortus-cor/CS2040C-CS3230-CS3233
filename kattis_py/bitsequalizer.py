import sys

#given the two strings S->T, count the number of 0,1,? in each, i.e. S1,S0,Snum,T1,T0
#clearly, since the transformations are 0->1, ?->0/1, 0<->1, then S->T is impossible
#iff S1>T1 (cannot reduce number of 1s) or S0+Snum<T0 (cannot make more 0s then initial + number of ?s)
#other than that, we will then greedy on the operations to minimize number of operations
#first count the number of 0->1 and 1->0 required, i.e. parity1,parity0
#we can minimize the number of operations required by pairing as many of these up as possible to use 0<->1
#increment count by the number of pairs, and decrease the parities by the number of pairs
#after that, we may be left with some unpaired transitions (all are guaranteed to be of one type)
#then we iterate through the ?s, for each ?,
#if ?->0 and 0->1 exist, then logically ?->1, 0<->1 is the most efficient set of operations, else ?->0 directly
#if ?->1 and 1->0 exist, then logically ?->0, 0<->1 is the most efficient set of operations, else ?->1 directly
#increment count and decrease parity as required

C=int(sys.stdin.readline())
for _ in range(C):
    S=sys.stdin.readline()
    T=sys.stdin.readline()
    S0=S.count('0')
    S1=S.count('1')
    Snum=S.count('?')
    T0=T.count('0')
    T1=T.count('1')
    if S1>T1 or S0+Snum<T0:
        print(f'Case {_+1}: -1')
    else:
        count=0
        parity0,parity1=0,0
        for i in range(len(S)):
            if S[i]!=T[i] and S[i]=='0':parity0+=1
            if S[i]!=T[i] and S[i]=='1':parity1+=1
        pairs=min(parity1,parity0)
        count+=pairs
        parity1-=pairs
        parity0-=pairs
        for i in range(len(S)):
            if S[i]=='?' and T[i]=='0':
                if parity0>0:parity0-=1;count+=2
                else:count+=1
            if S[i]=='?' and T[i]=='1':
                if parity1>0:parity1-=1;count+=2
                else:count+=1
        count+=parity1+parity0
        print(f'Case {_+1}: {count}')
