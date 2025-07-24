import sys

#just handle different cases for the current time, keeping track of the "start time" of each of the other users
#need to be careful with handling the updating of the users "start time"

j=list(map(int,sys.stdin.readline().split()))
m=[list(map(int,sys.stdin.readline().split())) for _ in range(10)]

cur_time=0
for cycle in range(3):
    for mach in range(10):
        if cur_time+j[2*mach]<=m[mach][2]:
            cur_time+=j[2*mach]+j[2*mach+1]
        elif cur_time<m[mach][2]<=cur_time+j[2*mach]:
            m[mach][2]=cur_time+j[2*mach]
            cur_time+=j[2*mach]+j[2*mach+1]
        elif m[mach][2]<=cur_time:
            times=(cur_time-m[mach][2])//(m[mach][0]+m[mach][1])
            m[mach][2]+=times*(m[mach][0]+m[mach][1])
            if m[mach][2]==cur_time:
                cur_time+=m[mach][0]
                if cur_time+m[mach][1]<cur_time+j[2*mach]:
                    m[mach][2]=cur_time+j[2*mach]
                cur_time+=j[2*mach]+j[2*mach+1]
            else:
                if m[mach][2]+m[mach][0]<=cur_time<m[mach][2]+m[mach][0]+m[mach][1]:
                    if cur_time+j[2*mach]>m[mach][2]+m[mach][0]+m[mach][1]:
                        m[mach][2]=cur_time+j[2*mach]
                else:
                    cur_time=m[mach][2]+m[mach][0]
                    if cur_time+j[2*mach]>m[mach][2]+m[mach][0]+m[mach][1]:
                        m[mach][2]=cur_time+j[2*mach]
                cur_time+=j[2*mach]+j[2*mach+1]

print(cur_time-j[-1])
