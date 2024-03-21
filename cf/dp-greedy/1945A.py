import sys,math
#simple greedy, all a in single tent so +3
#then +b//3, then case depending on value of b%3
#add c//3 after handling b%3 cases
t=int(sys.stdin.readline())
for _ in range(t):
    [a,b,c]=[int(_) for _ in sys.stdin.readline().split()]
    ans=0
    ans+=a
    ans+=(b//3)
    if b%3==0:
        ans+=math.ceil(c/3)
    elif b%3==1:
        if c>=2:
            ans+=1
            c-=2
            ans+=math.ceil(c/3)
        else:
            ans=-1
    else:
        if c>=1:
            ans+=1
            c-=1
            ans+=math.ceil(c/3)
        else:
            ans=-1
    print(ans)
