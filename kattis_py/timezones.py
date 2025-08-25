import sys

#just follow the mapping exactly, convert to minutes then add/subtract offset as required
#handle special cases of noon and midnight as well and wraparounds i.e. pm->am

offsets = {
    "UTC":0,"GMT":0,"BST":60,"IST":60,"WET":0,"WEST":60,
    "CET":60,"CEST":120,"EET":120,"EEST":180,"MSK":180,"MSD":240,
    "AST":-240,"ADT":-180,"NST":-210,"NDT":-150,"EST":-300,"EDT":-240,
    "CST":-360,"CDT":-300,"MST":-420,"MDT":-360,"PST":-480,"PDT":-420,
    "HST":-600,"AKST":-540,"AKDT":-480,"AEST":600,"AEDT":660,
    "ACST":570,"ACDT":630,"AWST":480
}

def parse_time(t):
    if t == "midnight": return 0
    if t == "noon": return 12*60
    hhmm,ampm = t.split()
    h,m = map(int,hhmm.split(":"))
    if ampm=="a.m.":
        if h==12: h=0
    else: # p.m.
        if h!=12: h+=12
    return h*60+m

def format_time(minutes):
    minutes %= 24*60
    if minutes==0: return "midnight"
    if minutes==12*60: return "noon"
    h, m = divmod(minutes,60)
    ampm = "a.m." if h<12 else "p.m."
    h = h%12
    if h==0: h=12
    return f"{h}:{m:02d} {ampm}"

input=sys.stdin.read().strip().splitlines()
n=int(input[0])
for line in input[1:]:
    parts=line.split()
    # time part may be "midnight"/"noon" (1 token) or "h:mm a.m." (2 tokens)
    if parts[0] in ("midnight","noon"):
        t=parts[0]
        src,dst=parts[1],parts[2]
    else:
        t=" ".join(parts[0:2])
        src,dst=parts[2],parts[3]
    mins=parse_time(t)
    utc=mins - offsets[src]
    dstmins=utc + offsets[dst]
    print(format_time(dstmins))
