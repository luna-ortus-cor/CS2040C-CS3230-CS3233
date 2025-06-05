import sys

#notice that the knights are as important as the players
#so if either the knight or the player has the minimum hp, then they will lose i.e. other player wins
#so just check if min of a,b,c,d is one of (b,d) or one of (a,c)

t=int(sys.stdin.readline())
for _ in range(t):
    a,b,c,d=map(int,sys.stdin.readline().split())
    if min([a,b,c,d])==b or min([a,b,c,d])==d:
        print('Gellyfish')
    else:
        print('Flower')
