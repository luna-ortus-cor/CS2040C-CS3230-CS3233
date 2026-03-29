import sys;m=".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. ..-- ---. .-.- ----".split();d=dict(zip("ABCDEFGHIJKLMNOPQRSTUVWXYZ_.,?",m));r={v:k for k,v in d.items()}
for s in sys.stdin:
 s=s.strip();a="".join(d[c]for c in s);l=[len(d[c])for c in s][::-1];i=0
 for x in l:print(end=r[a[i:i+x]]);i+=x
 print()
