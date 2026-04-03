#normal regex TLEs
'''
import re
pattern=input().strip()
N=int(input())
clean_pattern=re.sub(r'\*+', '*',pattern)
regex_pattern=re.escape(clean_pattern).replace(r'\*', '.*')
regex=re.compile(regex_pattern)
for _ in range(N):
    f=input().strip()
    if regex.fullmatch(f):print(f)
'''
import fnmatch
P=input().strip()
N=int(input())
for _ in range(N):
    f=input().strip()
    if fnmatch.fnmatch(f,P):print(f)
