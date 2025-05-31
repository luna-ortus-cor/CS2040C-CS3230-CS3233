d = lambda a, b: abs(a - b)
a, b = map(int, input().split())
A, B = map(int, input().split())
ta, tb = map(int, input().split())

ok = False

# Try all valid cow movement orders, considering crane can drop and return
# 1. Take a to A, then b to B
ok |= d(0,a)+d(a,A)<=ta and d(0,a)+d(a,A)+d(A,b)+d(b,B)<=tb

# 2. Take b to B, then a to A
ok |= d(0,b)+d(b,B)<=tb and d(0,b)+d(b,B)+d(B,a)+d(a,A)<=ta

# 3. Take a to b, then b to B, then a to A
ok |= d(0,a)+d(a,b)+d(b,B)<=tb and d(0,a)+d(a,b)+d(b,B)+d(B,b)+d(b,A)<=ta

# 4. Take b to a, then a to A, then b to B
ok |= d(0,b)+d(b,a)+d(a,A)<=ta and d(0,b)+d(b,a)+d(a,A)+d(A,a)+d(a,B)<=tb

print("possible" if ok else "impossible")
