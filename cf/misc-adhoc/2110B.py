import sys

#note that the anaswer is NO if there is only one top level bracket pairing (it is guaranteed at least one exists)
#i.e. (), (()()), ((((())()(()((())))))) etc.
#and the answer is YES if there is more than one top level bracket pairing
#i.e. ()(), ()()(), ((()()))(()((()))) etc.
#so iterate through, inc balance when '(', dec balance when ')'
#whenever balance reaches 0 we have one top level bracket pairing, inc count
#then just check that count >1 or ==1

t=int(sys.stdin.readline())
for _ in range(t):
    s=sys.stdin.readline().strip()
    balance = 0
    count = 0
    for c in s:
        if c=='(':
            balance+=1
        else:
            balance-=1
            if balance==0:
                count+=1
    if count>1:print("YES")
    else:print("NO")
    
