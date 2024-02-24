import sys
tc=int(sys.stdin.readline())
def score(s):
    idx=9
    s=s.replace('lower','0').replace('middle','1').replace('upper','2')
    s=[int(x) for x in s.split('-')[::-1]]
    for i in range(idx+1):
        if i<len(s):
            s[i]*=3**(idx-i)
        else:
            s+=[3**(idx-i)]
    return sum(s)
for _ in range(tc):
    n=int(sys.stdin.readline())
    a=[]
    for __ in range(n):
        s = sys.stdin.readline().split(': ')
        a.append([score(s[1].split()[0]),s[0]])
    a = sorted(a,key=lambda x:(-x[0],x[1]))
    for b in a:
        print(b[1])
    print(30*'=')
