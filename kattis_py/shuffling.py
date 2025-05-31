import sys

#this is just simulation, technically there is a OEIS sequence
#https://oeis.org/A002326
#but this has no known closed form for 2^x=1 mod (2n+1)
#https://math.stackexchange.com/questions/886083/minimum-number-of-out-shuffles-required-to-get-back-to-the-start-in-a-pack-of-2
#so in each shuffle, increase count, determine the midpoint of deck based on if out or in shuffle
#out shuffle the left should have 1 more card than right, and vice versa for in shuffle
#then just alternate the adding of cards to the result array, with the starting (left or right)
#again depending on if outshuffle (left) or inshuffle (right)
#then check if new deck is same as original if yes then break and print count

n,w=sys.stdin.readline().split()
n=int(n)
original=list(range(n))
deck=original[:]
count=0

def shuffle(deck,w):
    res=[]
    if w=='out':
        mid=(n+1)//2
        left,right=deck[:mid],deck[mid:]
        for i in range(n):
            if i%2==0:
                res.append(left[i//2])
            else:
                res.append(right[i//2])
    else:
        mid=n//2
        left,right=deck[:mid],deck[mid:]
        for i in range(n):
            if i%2==0:
                res.append(right[i//2])
            else:
                res.append(left[i//2])
    return res
    
while True:
    count+=1
    deck=shuffle(deck,w)
    if deck==original:
        break
print(count)
