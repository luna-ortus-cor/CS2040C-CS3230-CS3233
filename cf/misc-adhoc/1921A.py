import sys
 
n = int(sys.stdin.readline().strip())
for i in range(n):
    coords = []
    for j in range(4):
        [x,y]=[int(x) for x in sys.stdin.readline().strip().split()]
        coords.append([x,y])
    a=0
    b=0
    for j in range(3):
        if coords[j+1][0]==coords[0][0]:
            b = coords[j+1][1]-coords[0][1]
        elif coords[j+1][1]==coords[0][1]:
            a = coords[j+1][0]-coords[0][0]
        else:
            continue
    print(abs(a*b))
