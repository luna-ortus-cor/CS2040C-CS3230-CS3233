p1,p2=input().split()
for _ in[0]*int(input()):
 s=input().split();w1=w2=0;v=1
 for i,x in enumerate(s):
  a,b=map(int,x.split(':'))
  if a==b or(i<2 and {a,b}!={6,7}and(not 5<max(a,b)<8 or abs(a-b)<2))or(i==2 and(max(a,b)<6 or abs(a-b)<2 or {a,b}=={6,7})):v=0;break
  w1+=a>b;w2+=b>a
  if max(w1,w2)==2:break
 if w1+w2!=len(s)or max(w1,w2)!=2 or len(s)>3 or(p1=='federer'and w2)or(p2=='federer'and w1):v=0
 print('da'if v else'ne')
