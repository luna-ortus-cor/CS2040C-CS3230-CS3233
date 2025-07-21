import sys

#this is a brute force problem
#actually upon rereading my solution, more efficient to just store 2 max, 2 min for each axis rather than recompute
#first simulate removing max and min of each axis, then calculate new area to find min rectangle
#lastly check if the min area can store all n monsters (incl the one we rmeoved)
#if cannot, extend one of the axes by 1, calculate min area again

t = int(sys.stdin.readline())
for _ in range(t):
    n = int(sys.stdin.readline())
    points = [tuple(map(int, sys.stdin.readline().split())) for _ in range(n)]

    if n == 1:
        print(1)
        continue

    # Sort by x and y
    x_sorted = sorted(points, key=lambda p: p[0])
    y_sorted = sorted(points, key=lambda p: p[1])

    # Set of candidate points to remove: extremes in x and y
    candidates = set()
    candidates.add(x_sorted[0])
    candidates.add(x_sorted[-1])
    candidates.add(y_sorted[0])
    candidates.add(y_sorted[-1])

    min_cost = float('inf')

    for remove_point in candidates:
        remaining = [p for p in points if p != remove_point]

        # Get min/max x and y in O(n) for the remaining n-1 points
        min_x = min(p[0] for p in remaining)
        max_x = max(p[0] for p in remaining)
        min_y = min(p[1] for p in remaining)
        max_y = max(p[1] for p in remaining)

        width = max_x - min_x + 1
        height = max_y - min_y + 1
        area = width * height

        if area == n - 1:
            area = min((width + 1) * height, width * (height + 1))

        min_cost = min(min_cost, area)

    print(min_cost)
