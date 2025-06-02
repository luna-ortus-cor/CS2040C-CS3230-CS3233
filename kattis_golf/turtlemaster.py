g=[list(input())for _ in[0]*8];x,y,d,r=7,0,0,1;m=(0,1),(1,0),(0,-1),(-1,0);v=lambda a,b:0<=a<8and 0<=b<8
for c in input():
 a,b=x+m[d][0],y+m[d][1]
 if c<'G'and v(a,b)and g[a][b]in'.D':x,y=a,b
 elif'K'<c<'S':d+=(1,-1)[c<'R'];d%=4
 elif v(a,b)and g[a][b]=='I':g[a][b]='.'
 else:r=0
print('Diamond!'if g[x][y]=='D'and r else'Bug!')
