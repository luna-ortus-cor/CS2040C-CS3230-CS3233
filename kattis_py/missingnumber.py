import sys
#idea is to just iterate through 1 to n,
#check if the first digit/first 2 digit is equal to current iterate
#if yes then its not missing
#if no then missing
#if string becomes empty means current number is missing
n=int(sys.stdin.readline())
s=sys.stdin.readline().strip()
for i in range(1,n+1):
    if i<10:
        if s=='' or i!=int(s[0]):
            print(i)
            exit()
        else:
            s=s[1:]
    elif i<100:
        if s=='' or i!=int(s[:2]):
            print(i)
            exit()
        else:
            s=s[2:]
    else:
        print(i)
