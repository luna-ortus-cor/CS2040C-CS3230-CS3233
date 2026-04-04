input();m=input().split();a='GFEDCBAgfedcba';s={c:''for c in a}
for p,*d in[(l[0],int(l[1:])if len(l)>1else 1)for l in m]:
 for c in s:x='-'if c in'FDBgea'else' ';s[c]+='*'*d[0]if c==p else x*d[0];s[c]+=x
for c in a:print(f'{c}: {s[c][:-1]}')
