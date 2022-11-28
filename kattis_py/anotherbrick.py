import sys

height,width,n=sys.stdin.readline().split()
h,w=0,0

bricks=sys.stdin.readline().split()

for i in bricks:
    if h==int(height):
        break
    elif w+int(i)>int(width):
        break
    elif w+int(i)==int(width):
        h+=1
        w=0
    else:
        w+=int(i)

if h==int(height):
    print("YES")
else:
    print("NO")
