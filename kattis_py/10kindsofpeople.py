import sys
sys.setrecursionlimit(1000000)

[CONST_R, CONST_C] = [int(x) for x in sys.stdin.readline().split()]
original = [[int(i) for i in sys.stdin.readline().strip()] for x in range(CONST_R)]

idx=0
new = [[0 for i in range(CONST_C)] for j in range(CONST_R)]

R=[1,-1,0,0]
C=[0,0,1,-1]

def fill(orginal, new, next,idx):
    while len(next)!=0:
        (r,c)=next[0]
        
        if new[r][c]==0:
            new[r][c]=idx
            value=original[r][c]
            
            for i in range(4):
                tryR, tryC = r+R[i], c+C[i]
                if 0 <= tryR and tryR<CONST_R and 0<=tryC and tryC<CONST_C:
                    if original[tryR][tryC]==value and new[tryR][tryC]==0:
                        next.append((tryR,tryC))
        if len(next)==1:
            break
        else:
            next=next[1:]
    return new
    

n = int(sys.stdin.readline())
for i in range(n):
    [r1,c1,r2,c2]=[int(x)-1 for x in sys.stdin.readline().strip().split()]
    if new[r1][c1] == 0:
        idx+=1
        new=fill(original, new, [(r1,c1)], idx)
    if new[r2][c2] == 0:
        idx+=1
        new=fill(original, new, [(r2,c2)], idx)
        
    if new[r1][c1] == new[r2][c2]:
        if original[r1][c1] == 1:
            print('decimal')
        else:
            print('binary')
    else:
        print('neither')
