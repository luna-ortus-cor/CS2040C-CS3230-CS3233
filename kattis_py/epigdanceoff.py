import sys

#idea is to count the number of columns with all _ and add 1 
#convert each $->1,_->0 to form binary string, read as binary integer
#or each number with a (initialized as 0)
#then clearly any column with all _ will have 0 or 0 or 0 ... = 0
#so just return 1 + num bits - num 1 bits

n,m=map(int,sys.stdin.readline().split())
a=0
for _ in range(n):
    a|=int(''.join(['1'if __=='$'else'0'for __ in sys.stdin.readline().strip()]),2)
print(1+m-a.bit_count())
