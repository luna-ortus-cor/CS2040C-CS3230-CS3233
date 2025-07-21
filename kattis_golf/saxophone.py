for _ in[0]*int(input()):
 r=[p:=0]*10
 for c in input():
  q=[974,462,206,78,14,6,2,4,463,207,79,15,7,3]['cdefgabCDEFGAB'.index(c)]
  for i in range(10):r[i]+=q>>i&1>p>>i&1
  p=q
 print(*r)
