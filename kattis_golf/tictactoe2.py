L=[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6];i,w=input,lambda b,c:any(all(b[i]==c for i in l)for l in L)
for _ in range(N:=int(i())):
 l=''.join([i().strip()for _ in[0]*3]);x,o,u,v=l.count('X'),l.count('O'),w(l,'X'),w(l,'O');print('yes'if(0<=x-o<2)and not(u and v)and(not u or x==o+1)and(not v or x==o)else'no')
 if _<N-1:i()
