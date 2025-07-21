import sys

#consider each vertex separately, the sign in the alternating sum path depends on its parity in the path
#so for each vertex we need to maintain both a max threat f(v) and a min threat g(v)
#then for each vertex, the threat is the max of the danger of the vertex itself and the danger of the vertex - the min threat of the parent
#this is due to the alternating sum sequence
#thus define f(v)=max(av,av-g(pv)), g(v)=min(av,av-f(pv)) recursively and greedily where av is the vertex and pv is the parent
#at the root we have f(1)=g(1)=a1
#then starting from the root do a dfs recursively calculating the threat values along the way
#this will "dp-memoize" the threat values of vertex parents as well
#unable to use recursive bfs method (some error who knows why)
#so use iterative bfs (and dont need visited set if we avoid revisiting parent only)

def solve(root):
    stack = [(root, -1, 0, 0)]  # (v, parent, f, g)

    while stack:
        v, p, f, g = stack.pop()
        res[v] = max(a[v], a[v] - g)
        g = min(a[v], a[v] - f)

        for u in graph[v]:
            if u == p:
                continue
            stack.append((u, v, res[v], g))

#cannot use recursive, some errors
'''
def solve(v, p, f, g):
    global res
    res[v] = max(a[v], a[v]-g) #this is f(v) (need to be stored to return)
    g = min(a[v], a[v]-f) #this is g(v) (which does not need to be stored)
    for u in graph[v]:
        if u == p: #dont expand if parent
            continue
        solve(u, v, res[v], g)
'''

#sys.setrecursionlimit(300000) #max depth of recursion is max depth of tree is number of vertices is 2e5
t = int(sys.stdin.readline())
for _ in range(t):
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))
    graph = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = map(int, sys.stdin.readline().split())
        graph[u-1].append(v-1)
        graph[v-1].append(u-1)
    res = [0]*n
    solve(0)
    print(*res)
