for _ in' '*int(input()):s=input();n=int(len(s)**.5);print("".join(s[i-1::n]for i in range(n,0,-1)))
