h=['','C','CC','CCC','CD','D','DC','DCC','DCCC','CM']
t=['','X','XX','XXX','XL','L','LX','LXX','LXXX','XC']
o=['','I','II','III','IV','V','VI','VII','VIII','IX']

d={}
suffix=[]
for _ in range(10):
    for __ in range(10):
        for ___ in range(10):
            suffix.append(h[_]+t[__]+o[___])
            d[_*100+__*10+___*1]=h[_]+t[__]+o[___]
suffix=sorted(suffix)

t=int(input())
for _ in range(t):
    x=int(input())
    num_m=x//1000
    rem=x%1000
    
    if not rem or d[rem][0] not in ['X','V']:print(num_m*946+suffix.index(d[rem]))
    else:print(suffix.index(d[rem])-1000+num_m*(-54))
