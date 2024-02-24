import sys
input=sys.stdin.readline
mapping={'at':'@','and':'&','one':'1','won':'1',
        'to':'2','too':'2','two':'2','for':'4',
        'four':'4','bea':'b','be':'b','bee':'b',
        'sea':'c','see':'c','eye':'i','oh':'o',
        'owe':'o','are':'r','you':'u','why':'y'}
n=int(input())
def mapto(s):
    ans=''
    idx=0
    while(idx<len(s)):
        if idx+3<len(s) and s[idx:idx+4].lower() in mapping:
            if s[idx].isupper():
                ans+=mapping[s[idx:idx+4].lower()][0].upper()+mapping[s[idx:idx+4].lower()][1:]
            else:
                ans+=mapping[s[idx:idx+4]]
            idx+=4
        elif idx+2<len(s) and s[idx:idx+3].lower() in mapping:
            if s[idx].isupper():
                ans+=mapping[s[idx:idx+3].lower()][0].upper()+mapping[s[idx:idx+3].lower()][1:]
            else:
                ans+=mapping[s[idx:idx+3]]
            idx+=3
        elif idx+1<len(s) and s[idx:idx+2].lower() in mapping:
            if s[idx].isupper():
                ans+=mapping[s[idx:idx+2].lower()][0].upper()+mapping[s[idx:idx+2].lower()][1:]
            else:
                ans+=mapping[s[idx:idx+2]]
            idx+=2
        else:
            ans+=s[idx]
            idx+=1
    return ans
[print(mapto(input().strip())) for _ in range(n)]
