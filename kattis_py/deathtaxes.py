import sys

shares=0
cost=0
for line in sys.stdin:
    op=line.split()
    if op[0]=='buy':
        total=shares*cost+int(op[1])*int(op[2])
        shares+=int(op[1])
        cost=total/shares
    elif op[0]=='sell':
        shares-=int(op[1])
    elif op[0]=='split':
        shares*=int(op[1])
        cost/=int(op[1])
    elif op[0]=='merge':
        shares//=int(op[1])
        cost*=int(op[1])
    else:
        profit=int(op[1])-cost
        if profit>0:print(shares*(int(op[1])-profit*0.3))
        else:print(shares*int(op[1]))
