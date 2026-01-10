import math

#first note that at time T with M computers
#we can do MT units of work
#then at time T, all other finished work at t<T
#must also have been completed
#i.e. the invariant is that \sum_i=1^T t_i <= MT
#and so M >= 1/T \sum_i=1^T t_i
#this is basically the running sum of all work
#finished prior to T, divided by the finish time T
#so we remove all unsolved problems with -1
#sort the remaining problems by s (the finish time)
#maintain a running sum of t as we iterate through
#and divide this running sum by each s in the iteration
#find the max over all ceil(total/s) as the ans

n=int(input())
t=list(map(int,input().split()))
s=list(map(int,input().split()))

q=[(s[i],t[i]) for i in range(n)]
q=[(x,y) for x,y in q if x!=-1]
q=sorted(q)

total=0
m=0
for x,y in q:
    total+=y
    m=max(math.ceil(total/x),m)
print(m)
