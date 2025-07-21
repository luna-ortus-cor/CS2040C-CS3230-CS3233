import sys

#we can replace ai with b_i+1 or replace bi with a_i+1, aim for max pairs where ai=bi
#starting from the seq end, iterate to seq front for seqs a,b
#if ai=bi, then the answer is just i (all earlier pairs can be made into ai=bi)
#if ai!=bi but ai or bi have been previously seen in seq b or a (respectively), then the answer is just i
#if ai has been seen in seq a, then the answer is just i
#if bi has been seen in seq b, then the answer is just i
#else update the seen dict to store the last seen occurence of the element (overwrites dont matter)

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=list(map(int,sys.stdin.readline().split()))
    b=list(map(int,sys.stdin.readline().split()))
    i=n-1
    ans=0
    seen_a={}
    seen_b={}
    while i>=0:
        if a[i]==b[i]:
            ans=i+1
            break
        elif a[i] in seen_b and seen_b[a[i]]-i>1:
            ans=i+1
            break
        elif b[i] in seen_a and seen_a[b[i]]-i>1:
            ans=i+1
            break
        elif a[i] in seen_a:
            ans=i+1
            break
        elif b[i] in seen_b:
            ans=i+1
            break
        else: #overwrites, but overwrites only if same parity, so no issue
            seen_a[a[i]]=i
            seen_b[b[i]]=i
        i-=1
    print(ans)
