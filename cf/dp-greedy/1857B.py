import sys
#putting this in greedy instead of math since theres not much math...
#just greedying whenever rounding up is possible
t = int(sys.stdin.readline().strip())
for i in range(t):
    n = [int(x) for x in sys.stdin.readline().strip()]
    new = []
    found = False
    idx = -1
    for j in range(len(n)):
        if found:
            new.append(0)
            continue
        if n[j]<5:
            new.append(n[j])
        else:
            found = True
            new.append(0)
            idx = j
    if idx==-1:
        print(''.join(str(x) for x in new))
        continue
    if idx==0:
        print(''.join(str(x) for x in ([1]+new)))
        continue
    for j in range(idx-1,-1,-1):
        if j==idx-1:
            new[j]+=1
        else:
            if new[j+1]>=5:
                new[j]+=1
                new[j+1]=0
    if new[0]>=5 and new[0]!=10:
        new[0]=10
    print(''.join(str(x) for x in new))
