import sys

#observe that for solution to be possible, 1st element a1 must lie within
#the first ceil(n/2) elements in the sorted absolute array
#this is so that we are able to swap elements with absolute value
#larger than a1 by multiplying by -1 to change the number of elements
#on each side of a1 (this is true regardless of the final sign on a1)
#furthermore, elements with absolute value less than a1 will not be able
#to change the position of a1 within the array
#so a1 can be median iff it is in the first half (ceil/uppe bound) of the
#sorted absolute array

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=[abs(int(x)) for x in sys.stdin.readline().split()]
    b=sorted(a)
    possible=False
    if n%2==1:
        for i in range((n+1)//2):
            if a[0]==b[i]:
                possible=True
                break
    else:
        for i in range(1+(n+1)//2):
            if a[0]==b[i]:
                possible=True
                break
    if possible:
        print("YES")
    else:
        print("NO")
