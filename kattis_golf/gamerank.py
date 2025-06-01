t=w=0;r,s=25,lambda r:min(5,7-(r+4)//5)
for c in input():
 if r<1:break
 if c<'W':
  w=0
  if r<21:
   t-=1
   if t<0 and r<20:r+=1;t=s(r)-1
 else:
  w+=1;t+=1+(r>5)*(w>2)
  if t>s(r):t-=s(r);r-=1
 t=max(t,0)
print(('legend',r)[r>0])
