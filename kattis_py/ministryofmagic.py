import heapq

C,P=map(int,input().split())
p_vote,p_pref=[],[]
total_vote=0
for _ in range(P):
    v,*r=list(map(int,input().split()))
    p_vote.append(v)
    p_pref.append(r)
    total_vote+=v
c_score=[0 for _ in range(C)]
elim=[False for _ in range(C)]
p_ptr=[0 for _ in range(P)]
c2p=[[]for _ in range(C)]

for p in range(P):
    c_score[p_pref[p][0]-1]+=p_vote[p]
    c2p[p_pref[p][0]-1].append(p)
    
h=[]
for c in range(C):
    heapq.heappush(h,(c_score[c],c))
    
threshold=total_vote//2
active=C
while active>0:
    found=False
    for c in range(C):
        if not elim[c] and c_score[c]>threshold:
            print(c+1)
            found=True
            break
    if found:break
    loser=-1
    while True:
        votes,id=heapq.heappop(h)
        if not elim[id] and votes==c_score[id]:
            loser=id
            elim[id]=True
            active-=1
            break
    for p in c2p[loser]:
        while p_ptr[p]<C:
            c=p_pref[p][p_ptr[p]]-1
            if not elim[c]:
                c_score[c]+=p_vote[p]
                c2p[c].append(p)
                heapq.heappush(h,(c_score[c],c))
                break
            p_ptr[p]+=1
    c2p[loser]=[]
