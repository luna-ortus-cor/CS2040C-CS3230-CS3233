import sys,math

#this is just a greedy problem
#note that after M makes the first cut, F will move to the center of the remaining board
#to minimize the number of cells that can be cut in subsequent cuts by M
#thus thereafter, every (F,M) series of move+cut will only remove at most half of the
#remaining board in one dimension
#thus the number of turns to reduce the board to a 1x1 is ceil(log2(row))+ceil(log2(col))
#then include also the initial cut made by adding 1
#then all that is left is to greedy over the 4 possible initial cuts
#this is necessary as two initial cuts may remove the same number of cells, but the differing
#sizes of the remaining board may not have the same number of cuts required to reduce to 1x1

def turns(rows,cols):
    return math.ceil(math.log2(rows))+math.ceil(math.log2(cols))

t = int(sys.stdin.readline())
for _ in range(t):
    n, m, a, b = map(int, sys.stdin.readline().split())
    #4 ways to slice:
    option1=(n-a+1,m) #cut rows 1 to a
    option2=(a,m)     #cut rows a+1 to n
    option3=(n,m-b+1) #cut cols 1 to b
    option4=(n,b)     #cut cols b+1 to m
    result = min([turns(*option1),turns(*option2),turns(*option3),turns(*option4)])
    print(1+result)
