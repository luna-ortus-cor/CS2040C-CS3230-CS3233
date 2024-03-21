import sys,math
#just math, number theory
#min ans is always two, which is when a,b, fire same time i.e. at a*b (or lcm(a,b))
#then just add the number of previously fired fireworks still visible with window lenght of m
#so +m//a +m//b
t=int(sys.stdin.readline())
for _ in range(t):
    [a,b,m]=[int(_) for _ in sys.stdin.readline().split()]
    ans=2
    ans+=(m//a + m//b)
    print(ans)
