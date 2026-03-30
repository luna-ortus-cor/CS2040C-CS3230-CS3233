d={'0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'[i]:i for i in range(62)}
def base2dec(s,b):
    val=0
    for c in s:val=val*b+d[c]
    return val

for n in range(int(input())):
    A,B=input().split()
    A_min=max([d[c] for c in A])+1
    B_min=max([d[c] for c in B])+1
    found=False
    A_val={}
    for i in range(A_min,7501):
        A_val[base2dec(A,i)]=i
    for i in range(B_min,7501):
        temp=base2dec(B,i)
        if temp in A_val:
            found=True
            print(temp,A_val[temp],i)
            break
    if not found:print("CANNOT MAKE EQUAL")
