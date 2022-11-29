import sys
n=int(sys.stdin.readline().strip())
nums=[0,1,2,3,4,5,6,7,8,9]
curr=[1,2,3,4,5,6,7,8,9]
temp=[]
for i in range(2,n+1):
    temp=[]
    if len(curr)==0:
        break
    for j in curr:
        for k in nums:
            if (10*j+k)%i==0:
                temp.append(10*j+k)
    curr=temp
sys.stdout.write(str(len(curr)))
