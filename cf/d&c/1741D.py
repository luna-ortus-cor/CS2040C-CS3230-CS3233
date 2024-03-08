import sys
#notice that any tree with 1 leaf is automatically beautiful
#now consider a general tree
#it is beautiful if its left and right subtrees are also beautiful (or can be made beautiful)
#so we just have to check this condition: if all the elements contained in a subtree of size 2^n
#contain 2^n consecutive integers
#if yes, then check if need to swap (this is +1)
#swap subtrees if smallest element in right subtree < smallest element in left subtree
def solve(arr):
    if len(arr)==1:return (True,0)
    (a,b)=solve(arr[:len(arr)//2])
    (c,d)=solve(arr[len(arr)//2:])
    if a and c:
        if min(arr)+len(arr)-1!=max(arr):
            return (False,-1)
        else:
            if min(arr[:len(arr)//2])<min(arr[len(arr)//2:]):
                return (True,b+d)
            else:
                return (True,1+b+d)
    else:
        return (False,-1)
 
tc=int(sys.stdin.readline())
for t in range(tc):
    m=int(sys.stdin.readline())
    arr=[int(x) for x in sys.stdin.readline().split()]
    print(solve(arr)[1])
