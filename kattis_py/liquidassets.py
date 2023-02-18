import sys

n = int(sys.stdin.readline().strip())
s = sys.stdin.readline().strip().split()
vowels=['a','e','i','o','u']
for i in s:
    j=''
    prev=''
    for k in range(len(i)):
        if i[k]==prev:
            prev=i[k]
            continue
        else:
            j+=i[k]
            prev=i[k]
    m=''
    for l in range(len(j)):
        if j[l] in vowels and not (l==0 or l==len(j)-1):
            continue
        m+=j[l]
    print(m,end=' ')
