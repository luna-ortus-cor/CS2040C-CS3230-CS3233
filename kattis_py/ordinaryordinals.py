#done in python for ease of exponentiation and modulo with large numbers
#begin by observing some patterns
#consider the number of commas
#0, 0, 1, 3, 7, 15, if we add (N-1) 1s we get
#0, 1, 2, 4, 8, 16
#the number of commas for N is (N-1) + sum of commas of (1..N-1)
#thus number of commas for N is 2^(N-1)-1
#consider the number of { only (there are an equal number of })
#1, 2, 4, 8, 16
#the number of { for N is 1 + sum of { for (1..N-1)
#thus the number of { for N is 2^N
#then the total number of brackets and commas is
#2*2^N+2^(N-1)-1=5*2^(N-1)-1 (and 2 if N=0)
#so we take this modulo M
#use ~- for -1 and combine the N=0 case together

import sys
N,M=map(int,sys.stdin.readline().strip().split())
print(~-(5*pow(2,N-1,M) if N>0 else 3)%M)
