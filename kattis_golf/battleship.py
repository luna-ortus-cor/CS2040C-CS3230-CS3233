i,l=input,lambda:map(int,i().split())
for _ in range(int(i())):
 w,h,n=l();p=[[list(i())for _ in[0]*h][::-1]for _ in[0,1]];s,m=[sum(r.count('#')for r in x)for x in p],[t:=0,j:=0]
 while n:
  x,y=l();n-=1;c=p[1-t][y];h=c[x]<'$'
  if m[0]-m[1]or min(s):
   if h:c[x]='x';s[1-t]-=h
   if t==s[1]<1or not h:m[t]+=1;t^=1
 print(["player one wins","player two wins","draw"][~-(s[0]>0)+(s[1]>0)*2])
