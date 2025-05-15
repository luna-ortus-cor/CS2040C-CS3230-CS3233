import sys

#the idea is to compare the two strings lexicographically and "in" base-62
#then check if the smaller string is the same in both cases
#since lexicographical is easily done by <
#for comparing the actual value, first compare by length (shorter is smaller)
#else compare individual characters, if different use a predefined
#hashmap to ensure correct "conversion" of values i.e. a-z < A-Z since
#lexicographically A-Z < a-z

def cmp(a,b):
    if len(a)!=len(b):
        return 0 if len(a)<len(b) else 1
    for c1,c2 in zip(a,b):
        if vals[c1]!=vals[c2]:
            return 0 if vals[c1]<vals[c2] else 1
    return -1

t=int(sys.stdin.readline())
vals={c:i for i,c in enumerate('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')}
for _ in range(t):
    a=sys.stdin.readline().strip()
    b=sys.stdin.readline().strip()
    lex=0 if a<b else 1
    real=cmp(a,b)
    assert real>-1
    if lex==real:print('YES')
    else:print('NO')
