s,k=input().split()
s,k=list(s),int(k)
print('Yes'if s[len(s)-k:k]==sorted(s)[len(s)-k:k]else'No')
