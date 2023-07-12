'''
//we make some simple observations
// * = 6
// *L = 12
// *R = 15
//that is, *R = *L + 3
// ** = 33
// **L = 66
// **R = 75
//that is, **R = **L + 9 = **L + 3^2
//similarly for ***R = ***L + 27 = ***L + 3^3
//we can conclude that suppose we have some group
//of characters C with sum S, and including X *
//then CR = CL + 3^X
//this gives us C* = S + 2S + 2S + 3^X
//we also notice similar for R, that is
//CR = 2S + 3^X, due to the +1 that is compounded
//and CL = 2S
//use python instead of c++ due to very large numbers
'''

import sys

s = sys.stdin.readline().strip()
add = 1;
ans = 1;
for c in s:
    if c=='*':
        ans = 5*ans + add
        add*=3
    elif c=='R':
        ans = 2*ans + add
    elif c=='L':
        ans = 2*ans
    else:
        continue
print(ans)
