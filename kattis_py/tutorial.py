import math
m,n,t=map(int,input().split())
fac=[1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800]
if t==1:print("TLE"if n>12or fac[n]>m else"AC")
elif t==2:print("TLE"if n>math.log2(m)else"AC")
elif t==3:print("TLE"if n*n*n*n>m else"AC")
elif t==4:print("TLE"if n*n*n>m else"AC")
elif t==5:print("TLE"if n*n>m else"AC")
elif t==6:print("TLE"if n*math.log2(n)>m else"AC")
else:print("TLE"if m<n else"AC")
