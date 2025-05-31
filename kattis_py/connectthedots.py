import sys

# Dot order
dot_order = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'

# Read all lines
lines = [line.rstrip('\n') for line in sys.stdin]

images = []
image = []

# Separate input into multiple images
for line in lines:
    if line == "":
        if image:
            images.append(image)
            image = []
    else:
        image.append(list(line))

# Add last image if not empty
if image:
    images.append(image)

def connect_dots(grid):
    h, w = len(grid), len(grid[0])
    positions = {}

    # Record positions of all dots
    for i in range(h):
        for j in range(w):
            c = grid[i][j]
            if c in dot_order:
                positions[c] = (i, j)

    # Draw lines between consecutive dots
    for i in range(len(positions) - 1):
        a = dot_order[i]
        b = dot_order[i + 1]
        if a not in positions or b not in positions:
            break

        y1, x1 = positions[a]
        y2, x2 = positions[b]

        # Horizontal first
        if y1 == y2:
            for x in range(min(x1, x2) + 1, max(x1, x2)):
                if grid[y1][x] in dot_order:
                    continue
                elif grid[y1][x] == '|':
                    grid[y1][x] = '+'
                elif grid[y1][x] == '+':
                    continue
                else:
                    grid[y1][x] = '-'
        # Vertical
        elif x1 == x2:
            for y in range(min(y1, y2) + 1, max(y1, y2)):
                if grid[y][x1] in dot_order:
                    continue
                elif grid[y][x1] == '-':
                    grid[y][x1] = '+'
                elif grid[y][x1] == '+':
                    continue
                else:
                    grid[y][x1] = '|'

    return grid

# Process and output each image
for idx, img in enumerate(images):
    result = connect_dots([row.copy() for row in img])
    for row in result:
        print(''.join(row))
    if idx != len(images) - 1:
        print()
