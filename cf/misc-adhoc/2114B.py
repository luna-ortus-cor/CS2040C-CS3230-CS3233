import sys

#first we just count the number of 1 and 0s
#then now note that if there are k good pairs, then this uses up k spots on each half of the array and the other n//2 - k are non-good
#so we can subtract n//2 - k from each count to get the count of each of 0 and 1 used in forming good pairs
#this works since the non-good pairs in each half can be moved to form all 0 or all 1s in each half
#i.e. for n=10,k=3, something like (011)(00)(11)(110), that is, there is equal number of 0 and 1s in the non-good pairs
#otherwise, by pigeonhole principle, there will be at least one good pair which violates assumption
#then it just remains to check that this remaining count of each is non-negatve and divisible by 2 (to form a pair)

#alternatively, the min number of good pairs formable is max(num0, num1) - n//2 (all 0s then followed by all 1s)
#and the max is num0//2 + num1//2
#now note that any move changes the number of good pairs by 0 or 2, this can be brute forced, e.g.
#(00)(00) <-> (00)(00): 0
#(11)(11) <-> (11)(11): 0
#(00)(10) <-> (00)(01) <-> (10)(00) <-> (01)(00): 0
#(00)(11) <-> (10)(10) <-> (01)(01): 0
#(00)(11) <-> (01)(10) <-> (10)(01): 2
#(01)(11) <-> (10)(11) <-> (11)(10) <-> (11)(01): 0
#so we just need to check min_pair<=k<=max_pair and 2|(k-min_pair) and 2|(max_pair-k) (the last two conditions are equivalent)

t=int(sys.stdin.readline())
for _ in range(t):
    n,k=list(map(int,sys.stdin.readline().split()))
    s=sys.stdin.readline()
    num0=s.count('0')
    num1=s.count('1')
    num0-=(n//2-k)
    num1-=(n//2-k)
    if num0>=0 and num1>=0 and num0%2==0 and num1%2==0:
        print('YES')
    else:
        print('NO')
