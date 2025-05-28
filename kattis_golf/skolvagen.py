s=n=1
for c in input():s+=ord(c)%11;n+=s<4;s=s%5-s//4
print(~-n)
