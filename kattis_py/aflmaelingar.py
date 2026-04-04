K,q=map(int,input().split())
ans=['0' for _ in range(300)]
if K==2:
    for i in range(300):
        s='0 '*i+'1 '+'0 '*(300-i-1)
        print(s,flush=True)
        res=int(input())
        ans[i]=str(res)
    print(' '.join(ans))
elif K==4:
    for i in range(150):
        s='0 '*(2*i)+'1 100 '+'0 '*(2*(150-i-1))
        print(s,flush=True)
        res=int(input())
        ans[2*i]=str(res%100)
        ans[2*i+1]=str(res//100)
    print(' '.join(ans))
else:
    for i in range(100):
        s='0 '*i+'1 '+'0 '*(100-i-1)+'0 '*100+'0 '*i+'100 '+'0 '*(100-i-1)
        print(s,flush=True)
        res=int(input())
        ans[i]=str(res%100)
        ans[i+200]=res//100
    for i in range(100):
        s='0 '*100+'0 '*i+'1 '+'0 '*(100-i-1)+'0 '*i+'10 '+'0 '*(100-i-1)
        print(s,flush=True)
        res=int(input())
        if res<10*ans[i+200]:res+=1000
        res-=10*ans[i+200]
        ans[i+100]=str(res%100)
        ans[i+200]=str((res//100)*10+ans[i+200])
    print(' '.join(ans))
