import sys
#another greedy, first observe any 2-digit number is larger than a 1-digit number (duh)
#so starting from the back, if number is 2-digit, check if number is smaller than prev number appended,
#if yes do not split and just append
#else split and append in correct order
#note new array can just have the last ele in it at start (invariant: last inserted ele is largest among remaining ele)
#finally check new array is sorted (reverse first and check against sorted)
t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=[int(x) for x in sys.stdin.readline().split()]
    b=[a[-1]]
    for i in range(len(a)-2,-1,-1):
        if a[i]>=10 and a[i]<=b[-1]:
            b+=[a[i]]
        elif a[i]>=10:
            b+=[a[i]%10,a[i]//10]
        else:
            b+=[a[i]]
    if sorted(b)==b[::-1]:
        print('YES')
    else:
        print('NO')
