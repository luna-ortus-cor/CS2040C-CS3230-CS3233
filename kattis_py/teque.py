import sys

N = int(sys.stdin.readline().strip())

t=[0 for i in range(4*10**6)]
front=1*10**6+1
mid1=front
back=3*10**6-1
mid2=back
numfront=0
numback=0

for j in range(N):
    [a,b]=sys.stdin.readline().strip().split()
    if a=='push_front':
        if numfront>numback:
            numback+=1
            t[front]=int(b)
            t[mid2-1]=t[mid1]
            t[mid1]=0
            mid1-=1
            front-=1
            mid2-=1
        else:
            numfront+=1
            t[front]=int(b)
            front-=1
        
    elif a=='push_middle':
        if numfront==numback:
            t[mid1+1]=int(b)
            numfront+=1
            mid1+=1
        else:
            t[mid2-1]=int(b)
            numback+=1
            mid2-=1
            
    elif a=='push_back':
        if numback+1>numfront:
            numfront+=1
            t[back]=int(b)
            t[mid1+1]=t[mid2]
            t[mid2]=0
            mid1+=1
            back+=1
            mid2+=1
        else:
            numback+=1
            t[back]=int(b)
            back+=1
    else:
        if int(b)>=numfront:
            print(t[mid2+int(b)-numfront])
        else:
            print(t[front+int(b)+1])
