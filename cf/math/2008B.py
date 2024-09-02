import sys

t=int(sys.stdin.readline().strip())
for _ in range(t):
    n=int(sys.stdin.readline().strip())
    s=sys.stdin.readline().strip()
    zero=s.count('0')
    one=s.count('1')
    d=zero**0.5
    if int(d)==d and one==4*(int(d)+1):print("Yes")
    else:print("No")
