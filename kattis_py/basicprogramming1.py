import sys

[N,t]=[int(x) for x in sys.stdin.readline().split()]
A = [int(x) for x in sys.stdin.readline().split()]

if t==1:
    print(7)
elif t==2:
    if A[0]>A[1]:
        print("bigger")
    elif A[0]==A[1]:
        print("Equal")
    else:
        print("Smaller")
elif t==3:
    print(sorted([A[0],A[1],A[2]])[1])
elif t==4:
    print(sum(A))
elif t==5:
    print(sum([x for x in A if x%2==0]))
elif t==6:
    print(''.join([chr((x%26)+97) for x in A]))
else:
    d={}
    i=0
    while True:
        if A[i] in d:
            print("Cyclic")
            break
        if A[i]>=N:
            print("Out")
            break
        if A[i]==N-1:
            print("Done")
            break
        d[i]=A[i]
        i=d[i]
