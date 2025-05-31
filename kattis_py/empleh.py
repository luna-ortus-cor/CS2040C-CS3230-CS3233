import sys

# Initialize empty 8x8 board
board = [['' for _ in range(8)] for _ in range(8)]

# Parse input
lines = [input().strip() for _ in range(2)]

for line in lines:
    color = 'white' if line.startswith('White') else 'black'
    if len(line)<7: continue
    parts = line.split(': ')[1].split(',')
    for p in parts:
        if p[0].isupper() and p[0] in 'KQRBN':
            piece, pos = p[0], p[1:]
        else:
            piece, pos = 'P', p  # Pawn
        col = ord(pos[0]) - ord('a')
        row = 8 - int(pos[1])
        board[row][col] = piece if color == 'white' else piece.lower()

# Build board output
for i in range(8):
    print('+---' * 8 + '+')
    row = ''
    for j in range(8):
        bg = '.' if (i+j)%2==0 else ':'
        cell = board[i][j]
        row += f'|{bg}{cell if cell else bg}{bg}'
    print(row + '|')
print('+---' * 8 + '+')
