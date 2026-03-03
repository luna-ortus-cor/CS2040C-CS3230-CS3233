import random
n=int(input())
resp=-1
chars=['P','I','Z','A']
ans=''
while len(ans)!=n:
    random.shuffle(chars)
    add=chars[3]
    for i in range(3):
        print(ans+chars[i],flush=True)
        resp=int(input())
        if resp>0:
            add=chars[i]
            break
    ans+=add
if resp<2:print(ans,flush=True)
