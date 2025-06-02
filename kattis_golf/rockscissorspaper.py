p,a=input,range;b='RSPR';d=(-1,0),(1,0),(0,-1),(0,1)
for _ in range(t:=int(p())):
 r,c,n=map(int,p().split());g=[list(p())for _ in a(r)];h=[l[:]for l in g]
 for _ in a(n):
  for i in a(r):
   for j in a(c):
    h[i][j]=g[i][j]
    for x,y in d:
     u,v=i+x,j+y
     if r>u>=0and c>v>=0and g[u][v]+g[i][j]in b:h[i][j]=g[u][v]
  g,h=h,g
 for r in g:print(''.join(r))
 if _<t-1:print()
