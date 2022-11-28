import sys

mykingx,mykingy=-1,-1
myrookx,myrooky=-1,-1
yourkingx,yourkingy=-1,-1

for i in range(8):
    line = sys.stdin.readline().strip()
    for j in range(8):
        if line[j]=='K':
            mykingx,mykingy=j,i
        elif line[j]=='k':
            yourkingx,yourkingy=j,i
        elif line[j]=='R':
            myrookx,myrooky=j,i
        else:
            pass

if 0<yourkingx<7 and 0<yourkingy<7:
    print("NO")
elif mykingx==yourkingx:
    if mykingy!=yourkingy+2 and mykingy!=yourkingy-2:
        print("NO")
    elif myrookx==mykingx or myrookx==mykingx+1 or myrookx==mykingx-1:
        print("NO")
    else:
        print("YES")
elif mykingy==yourkingy:
    if mykingx!=yourkingx+2 and mykingx!=yourkingx-2:
        print("NO")
    elif myrooky==mykingy or myrooky==mykingy+1 or myrooky==mykingy-1:
        print("NO")
    else:
        print("YES")
elif yourkingx==0 and yourkingy==0:
    if (mykingx==2 and mykingy==1):
        if myrooky>mykingy:
            print("YES")
        else:
            print("NO")
    elif (mykingx==1 and mykingy==2):
        if myrookx>mykingx:
            print("YES")
        else:
            print("NO")
    else:
        print("NO")
elif yourkingx==0 and yourkingy==7:
    if (mykingx==1 and mykingy==5):
        if myrookx>mykingx:
            print("YES")
        else:
            print("NO")
    elif(mykingx==2 and mykingy==6):
        if myrooky<mykingy:
            print("YES")
        else:
            print("NO")
    else:
        print("NO")
elif yourkingx==7 and yourkingy==0:
    if (mykingx==5 and mykingy==1):
        if myrooky>mykingy:
            print("YES")
        else:
            print("NO")
    elif (mykingx==6 and mykingy==2):
        if myrookx<mykingx:
            print("YES")
        else:
            print("NO")
    else:
        print("NO")
elif yourkingx==7 and yourkingy==7:
    if (mykingx==5 and mykingy==6):
        if myrooky<mykingy:
            print("YES")
        else:
            print("NO")
    elif (mykingx==6 and mykingy==5):
        if myrookx<mykingx:
            print("YES")
        else:
            print("NO")
    else:
        print("NO")
else:
    print("NO")
