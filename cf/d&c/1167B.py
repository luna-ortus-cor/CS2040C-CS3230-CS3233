import sys
 
nums=[4,8,15,16,23,42]
ans=[]
prev=0
for i in range(4):
    sys.stdout.write(f'? {i+1} {i+2}\n')
    sys.stdout.flush()
    mult = int(sys.stdin.readline())
    if prev==0:
        prev=mult
    else:
        for j in nums:
            if prev%j==0 and mult%j==0:
                a=prev//j
                b=mult//j
                if a!=b and b!=j and a!=j and a in nums and b in nums:
                    if ans==[]:
                        ans.append(a)
                    if ans[-1]!=j:
                        ans.append(j)
                    ans.append(b)
        prev=mult
for j in nums:
    if j not in ans:
        ans.append(j)
sys.stdout.write('! ')
for j in ans:
    sys.stdout.write(str(j)+' ')
sys.stdout.write('\n')
sys.stdout.flush()
exit()
