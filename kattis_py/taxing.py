B=int(input())
brackets=[]
for _ in range(B):
    s,p=map(float,input().split())
    brackets.append([s,p])
finaltax=float(input().strip())
F=int(input())
for _ in range(F):
    e,m=map(float,input().split())
    curr_e,net_need=e,m
    ans=0
    cum=0.0
    for s,p in brackets:
        start,end=cum,cum+s
        cum=end
        if curr_e>=end:continue
        pos=max(curr_e,start)
        avail_gross=end-pos
        tax=1.0-(p/100.0)
        avail_net=avail_gross*tax
        if avail_net>=net_need:
            ans+=net_need/tax
            net_need=0
            break
        else:
            ans+=avail_gross
            net_need-=avail_net
            curr_e=end
    if net_need>0:ans+=net_need/(1.0-finaltax/100.0)
    print(f"{ans:.6f}")
