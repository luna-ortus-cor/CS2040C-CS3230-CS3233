import sys
from math import gcd
from functools import reduce

#supposedly this is solvable using dfs/dp but i dont believe my solution can be described as either so
#first notice that the entire array will only have all elements equal if every element is the gcd of all elements
#so first we calculate the gcd of all elements in the array, which is approximately O(n log n)
#next we notice, if the gcd already exists in the array, then all other elements can be immediately reduced
#to the gcd by taking gcd with that element, in which case the answer is then n-num of gcd elements already existing
#suppose otherwise, then the answer is n-1+ops, where ops is the number of operations to obtain the gcd as an element
#in the array, and determining ops can be done in about O(n^2 log n)
#this is based on the observation that we can quickly arrive at the correct gcd of the entire array
#by simply taking the minimum gcd between pairs of elements and repeating this process (i.e. we "force" the "min" gcd
#of the array to quickly to converge to the actual gcd of the array)
#while the gcd does not exist in the array, iterate through every pair of elements and calculate the gcd of these elements
#then if it is the min over all pairs, replace the element at that index with the new "best" gcd
#keep track of how many times this process is done to determine ops

t=int(sys.stdin.readline())
for _ in range(t):
    n=int(sys.stdin.readline())
    a=list(map(int,sys.stdin.readline().split()))
    g=reduce(gcd,a)
    #print(g)
    if g in a:
        print(n-a.count(g))
    else:
        ops=0
        found=False
        while not found:
            ops+=1
            new_a=a[:]
            best_gcd=1e9
            best_idx=-1
            for i in range(n):
                for j in range(i):
                    x=gcd(a[i],a[j])
                    if x<best_gcd:
                        best_idx=i
                        best_gcd=x
                        changed=True
                        if x==g:
                            found=True
                            break
                if found:
                    break
            if not changed:
                break  # prevent infinite loop
            new_a[best_idx]=best_gcd
            a=new_a

        print(ops+(n-1))
