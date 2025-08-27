h1,m1,s1=map(int,input().split(':'))
h2,m2,s2=map(int,input().split(':'))
t1=h1*3600+m1*60+s1
t2=h2*3600+m2*60+s2
d=(t2-t1)%(24*3600)
d+=24*3600 if d==0 else 0
print(f"{d//3600:02}:{d%3600//60:02}:{d%60:02}")
