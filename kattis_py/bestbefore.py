from itertools import permutations
s=input().strip()
p=s.split('/')
def leap(y):return y%400==0 or(y%4==0 and y%100)
def ok(y,m,d):
    if not(2000<=y<=2999 and 1<=m<=12):return 0
    md=[31,29 if leap(y) else 28,31,30,31,30,31,31,30,31,30,31]
    return 1<=d<=md[m-1]
c=[]
for x in permutations(p):
    y,m,d=x
    y=int(y) if len(y)==4 else 2000+int(y)
    m,d=int(m),int(d)
    if ok(y,m,d):c+=[f"{y:04d}-{m:02d}-{d:02d}"]
print(min(c) if c else s+" is illegal")
