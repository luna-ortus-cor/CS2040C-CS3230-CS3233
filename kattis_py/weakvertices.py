while True:
    n = int(input())
    if n == -1:
        break
    adj = [list(map(int, input().split())) for _ in range(n)]
    weak = []
    for i in range(n):
        found = False
        for j in range(n):
            for k in range(j+1, n):
                if adj[i][j] and adj[i][k] and adj[j][k]:
                    found = True
                    break
            if found:
                break
        if not found:
            weak.append(i)
    print(*weak)
