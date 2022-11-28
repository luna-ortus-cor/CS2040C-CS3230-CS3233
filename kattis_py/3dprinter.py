import sys
import math

for i in sys.stdin:
    n=int(i.strip())

print(math.ceil(math.log(n,2)+1))
