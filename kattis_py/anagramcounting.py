import sys
import math

def anagram(word):
    s=math.factorial(len(word))
    result={}
    for i in word:
        if i in result:
            result[i]+=1
        else:
            result[i]=1
    for j in result:
        s//=math.factorial(result[j])
    return s

mat=[]    
for i in sys.stdin:
    mat.append(i.strip())
for j in mat:
    print(anagram(j))
        
