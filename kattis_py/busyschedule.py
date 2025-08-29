def to_minutes(time_str):
    h, rest = time_str.split(':')
    h = int(h)
    m, z = rest.split()
    m = int(m)
    if z == "a.m.":
        if h == 12: h = 0
    else:  # p.m.
        if h != 12: h += 12
    return h*60 + m

def from_minutes(h, m, z):
    return f"{h}:{m:02d} {z}"

while True:
    n = int(input())
    if n == 0: break
    times = [input().strip() for _ in range(n)]
    times.sort(key=to_minutes)
    for t in times: print(t)
    print()
