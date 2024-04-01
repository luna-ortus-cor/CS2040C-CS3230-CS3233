import sys
#this is just implementation and minor logic, could actually be 
#shorter/more efficient/simpler
t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    for i in range(n):
        s=''
        if i%2==0:
            s='##..'*(n//2)+'##'*(n%2)
            print(s)
            print(s)
        else:
            s='..##'*(n//2)+'..'*(n%2)
            print(s)
            print(s)
