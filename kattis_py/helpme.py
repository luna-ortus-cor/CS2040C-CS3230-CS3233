import sys
from collections import defaultdict

# Piece order
order = 'KQRBNP'
white = defaultdict(list)
black = defaultdict(list)

# Read 8 lines with pieces (skip borders)
board = [line.strip() for line in sys.stdin.readlines() if '|' in line]

for i, line in enumerate(board):
    row = 8 - i  # From top (row 8) to bottom (row 1)
    cells = line.split('|')[1:-1]
    for j, cell in enumerate(cells):
        piece = cell.strip()[1]
        if not piece.isalpha():
            continue
        col = chr(ord('a') + j)
        pos = f"{col}{row}"
        if piece.isupper():
            white[piece].append(pos)
        else:
            black[piece.upper()].append(pos)

def format_pieces(pieces, reverse=False):
    #print(pieces)
    result = []
    for k in order:
        ps = pieces[k]
        ps.sort(key=lambda x: (int(x[1])), reverse=reverse)
        for p in ps:
            result.append(f"{'' if k=='P' else k}{p}")
    return ','.join(result)

print("White:", format_pieces(white))
print("Black:", format_pieces(black, reverse=True))
