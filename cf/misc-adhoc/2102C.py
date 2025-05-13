import sys

#the intuition (not rigorous proof) is that we want to maximize the number of subgrids
#that smaller numbers like 0,1,2,3,... appear
#this can be done by ensuring that smaller solutions appear in larger solutions
#i.e. the solution to n=2 should appear in n=3 which should be in n=4 etc
#so one way of doing this (there are multiple) is to arrange the numbers from
#0 to n^2-1 in a spiral fashion (with 0 near the middle and n^2-1 at a corner)

def generate_spiral(n):
    grid = [[0] * n for _ in range(n)]
    x,y=0,0
    num=n**2-1
    grid[x][y]=num
    while num:
        while 0<=x+1<n and grid[x+1][y]==0:
            x+=1
            num-=1
            grid[x][y]=num
        while 0<=y+1<n and grid[x][y+1]==0:
            y+=1
            num-=1
            grid[x][y]=num
        while 0<=x-1<n and grid[x-1][y]==0:
            x-=1
            num-=1
            grid[x][y]=num
        while 0<=y-1<n and grid[x][y-1]==0:
            y-=1
            num-=1
            grid[x][y]=num
    return grid

t = int(sys.stdin.readline())
for _ in range(t):
    n = int(sys.stdin.readline())
    grid = generate_spiral(n)
    for row in grid:
        print(" ".join(map(str, row)))
