from datetime import datetime, timedelta

#just note the optimal day is the day at the end of the longest gap
#(not including the day of another colleagues bday)
#handle wraparound by adding 365 to first date and mod 12 for months

days_in_month=[31,28,31,30,31,30,31,31,30,31,30,31]
def to_day(mmdd):
    m,d=map(int,mmdd.split('-'))
    return sum(days_in_month[:m-1])+d
def to_mmdd(day):
    m=0
    while day>days_in_month[m]:
        day-=days_in_month[m]
        m+=1
        m%=12
    return f"{(m+1):02d}-{day:02d}"

n=int(input())
b=set()
for _ in range(n):_,d=input().split();b.add(to_day(d))
b=sorted(b)
b.append(b[0]+365)
gaps=[]
for i in range(len(b)-1):
    start,end=b[i],b[i+1]
    gap=end-start-1
    if gap>0:gaps.append((gap,end-1))
mx=max(gaps)[0]
candidates=[d for g,d in gaps if g==mx]

ref=to_day("10-27")
cands=[d if d>ref else d+365 for d in candidates]
chosen=candidates[cands.index(min(cands))]
print(to_mmdd(chosen))
