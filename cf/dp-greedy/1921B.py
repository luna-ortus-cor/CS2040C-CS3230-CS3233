import sys
 
n = int(sys.stdin.readline().strip())
for i in range(n):
    l = int(sys.stdin.readline().strip())
    s1 = sys.stdin.readline().strip()
    s2 = sys.stdin.readline().strip()
    no1 = 0
    no0 = 0
    for c in range(l):
        if s1[c] != s2[c]:
            if s2[c]=='1':
                no1+=1
            if s2[c]=='0':
                no0+=1
    print(max(no1,no0))
