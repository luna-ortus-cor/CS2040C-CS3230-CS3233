import sys
s,n,m=map(int,sys.stdin.readline().split())
p=[]
for line in sys.stdin:
    p+=list(map(int,line.split()))
prev=-1
inc_len,dec_len,last_inc,last_dec,peak,valley=1,1,0,0,0,0

for i in range(1,s):
    if p[i]>p[i-1]:
        inc_len+=1
        if dec_len>1:
            last_dec=dec_len
            dec_len=1 
        if last_dec>=m and inc_len==m:
            valley+=1
    else:
        dec_len+=1
        if inc_len>1:
            last_inc=inc_len
            inc_len=1
        if last_inc>=n and dec_len==n:
            peak+=1
print(peak,valley)
