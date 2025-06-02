d='rspr'
while(e:=input())>'0':
 n,k=map(int,e.split());w=[0]*n;l=[0]*n
 for _ in range(k*n*(n-1)//2):
  a,x,b,y=input().split();a,b=int(a)-1,int(b)-1
  if(x[0]+y[0])in d:w[a]+=1;l[b]+=1
  if(y[0]+x[0])in d:w[b]+=1;l[a]+=1
 for i,j in zip(w,l):print(f'{i/(i+j):.3f}'if i+j else'-')
 print()
