#tbh there's better and cleaner ways to do this
months = ["JAN","FEB","MAR","APR","MAY","JUN",
          "JUL","AUG","SEP","OCT","NOV","DEC"]
days_in_month = [31,28,31,30,31,30,31,31,30,31,30,31]
weekdays = ["MON","TUE","WED","THU","FRI","SAT","SUN"]

# read inputs
d, mon = input().split()
d = int(d)
jan1 = input().strip()

# offset from Jan 1 (non-leap)
offset = sum(days_in_month[:months.index(mon)]) + (d-1)

# weekday in non-leap
w1 = (weekdays.index(jan1) + offset) % 7

possible = {w1}

# if date >= MAR 1 → also possible leap shift
if months.index(mon) >= 2:
    w2 = (w1 + 1) % 7
    possible.add(w2)

if all(weekdays[w] == "FRI" for w in possible):
    print("TGIF")
elif "FRI" in [weekdays[w] for w in possible]:
    print("not sure")
else:
    print(":(")
