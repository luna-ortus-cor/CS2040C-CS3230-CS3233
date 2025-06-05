while 1:
 f=t=0;c=[9,4,4,4,7]
 while(s:=input())!='-':x=[(int(i[:-1]),i[-1])for i in s.split()];p=sum(v for v,u in x if u=='%');k=sum(v*c[i]if u=='g'else v if u=='C'else 0 for i,(v,u)in enumerate(x));T=k*100/(100-p);v,u=x[0];f+=v*c[0]if u=='g'else v if u=='C'else T*v/100;t+=T
 if t<1:break
 print(f'{round(f*100/t)}%')
