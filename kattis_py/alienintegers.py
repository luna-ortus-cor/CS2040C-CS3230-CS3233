# stupid problem honestly
#first eliminate digits that cannot be used i.e. digits already in original number
#let LD leading digit of original number, N length of original number
#let DREM set of remaining digits, maxDREM and minDREM defined obviously
#if DREM is empty: print impossible
#separate into 2 case
#case 1: 0 not in DREM:
#for bigger number, if exists digit d in DREM larger than LD, then min(d)+minDREM*(N-1)
#else minDREM*(N+1)
#for smaller number, if exists digit d in DREM smaller than LD, then max(d)+maxnDREM*(N-1)
#else maxDREM*(N-1)
#case 2: 0 in DREM:
#handle side cases separately, particularly case of single digit inputs, case where only 0 in DREM, etc.
#0 cannot be leading digit, 0 is minDREM, 0 may be maxDREM
#replace minDREM=0 with next smallest i.e. min(DREM\{0}) where appropriate to avoid leading 0 and follow case 1
#for both cases, if cannot find suitable bigger and smaller alien number 
#i.e. bigger<original num and smaller>original num, print impossible
#else print according to specification (closest alien integer or both if equally close)

import sys
digits={'1','2','3','4','5','6','7','8','9','0'}
s=sys.stdin.readline().strip()
rm=set(s)
rem=digits-rm
if rem==set(): print('Impossible')
elif rem=={'0'}: print(0)
else:
    if '0' not in rem:
        first=int(s[0])
        irem=[int(x) for x in rem]
        small=max(irem)
        big=min(irem)
        below=str(small)*(len(s)-1)
        above=str(big)*(len(s)-1)
        newsmall=first
        newbig=first
        for d in irem:
            if d>first and d!=0:newbig=min(newbig,d) if newbig!=first else d
            elif d!=0:newsmall=max(newsmall,d) if newsmall!=first else d
        newsmall=str(newsmall)
        newbig=str(newbig)
        if newsmall!=str(first):below=newsmall+below
        if newbig!=str(first):above=newbig+above
        else:above=str(big)*2+above
        if above=='':above=0
        if below=='':below=0
        if int(above)<int(s) and int(below)>int(s):print('Impossible')
        elif int(s)-int(below)<int(above)-int(s):print(int(below))
        elif int(s)-int(below)>int(above)-int(s):print(int(above))
        else:print(int(below),int(above),sep=' ')
    else:
        first=int(s[0])
        irem=[int(x) for x in rem]
        small=max(irem)
        big=min(irem)
        below=str(small)*(len(s)-1)
        above=str(big)*(len(s)-1) 
        newsmall=first
        newbig=first
        for d in irem:
            if d>first and d!=0:newbig=min(newbig,d) if newbig!=first else d
            elif d<first and d!=0:newsmall=max(newsmall,d) if newsmall!=first else d
        newsmall=str(newsmall)
        newbig=str(newbig)
        if newsmall!=str(first):below=newsmall+below
        if newbig!=str(first):above=newbig+above
        else:
            if big!=0:
                above=str(big)*2+above
            else:
                above=str(min(set(irem)-{0}))+str(big)+above
        if above=='':above=0
        if below=='':below=0
        if int(above)<int(s) and int(below)>int(s):print('Impossible')
        elif int(s)-int(below)<int(above)-int(s):print(int(below))
        elif int(s)-int(below)>int(above)-int(s):print(int(above))
        else:print(int(below),int(above),sep=' ')
