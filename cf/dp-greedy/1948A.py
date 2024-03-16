import sys
#simple greedy, observe no odd number of special characters is valid, so must be even
#any contiguous sequence of same letters contributes 2 at most, so just alternate between 
#2 letters A,B and add 2 of same letter until number of special characters is met
t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    if n%2==1:
        print('NO')
        continue
    else:
        s=''
        c='A'
        while n:
            s+=c*2
            if c=='A':
                c='B'
            else:
                c='A'
            n-=2
        print('YES')
        print(s)
        continue
