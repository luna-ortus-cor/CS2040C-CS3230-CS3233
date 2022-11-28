import sys

def shift(mat, sign):
    if sign == 2 or sign == 3:
        for i in range(3, -1, -1):
            j = i-1
            while j >-1:
                if mat[i] == 0:
                    if mat[j] == 0:
                        j-=1
                    else:
                        mat[i] = mat[j]
                        mat[j] = 0
                        j-=1
                elif mat[i]==mat[j]:
                    mat[i]*=2
                    mat[j]=0
                    break
                elif mat[j] == 0:
                    j-=1
                else: 
                    #non zero different
                    break
    else:
        for i in range(3):
            j=i+1
            while j<4:
                if mat[i]==0:
                    if mat[j] == 0:
                        j+=1
                    else:
                        mat[i]=mat[j]
                        mat[j]=0
                        j+=1
                elif mat[i]==mat[j]:
                    mat[i]*=2
                    mat[j]=0
                    break
                elif mat[j]==0:
                    j+=1
                else:
                    #non zero different
                    break
    return mat

matrix = []
move = -1
for i in sys.stdin:
    ii=i.split()
    if len(ii)>1:
        matrix.append([int(iii) for iii in ii])
    else:
        move = int(ii[0])
        break

if move==0:
    newmatrix=[shift(mat,0) for mat in matrix]
elif move==1:
    T = [list(x) for x in zip(*matrix)]
    newT=[shift(mat,1) for mat in T]
    newmatrix=[list(x) for x in zip(*newT)]
elif move==2:
    newmatrix=[shift(mat,2) for mat in matrix]
else:
    T = [list(x) for x in zip(*matrix)]
    newT=[shift(mat,3) for mat in T]
    newmatrix=[list(x) for x in zip(*newT)]

for i in newmatrix:
    print(*i)
