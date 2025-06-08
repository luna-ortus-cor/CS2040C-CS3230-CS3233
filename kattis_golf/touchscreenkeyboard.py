p,e,k=input,enumerate,["qwertyuiop","asdfghjkl","zxcvbnm"];d={c:(i,j)for j,r in e(k)for i,c in e(r)}
for _ in[0]*int(p()):
 w,n=p().split();a=[p()for _ in[0]*int(n)];b=[]
 for s in a:b+=[(sum(abs(d[x][0]-d[y][0])+abs(d[x][1]-d[y][1])for x,y in zip(w,s)),s)]
 for x,s in sorted(b):print(s,x)
