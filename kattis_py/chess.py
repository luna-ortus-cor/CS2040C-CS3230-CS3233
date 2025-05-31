def to_index(col,row):
    return ord(col)-ord('A'),int(row)-1

def to_pos(x,y):
    return f"{chr(x+ord('A'))} {y+1}"

def bishop_moves(start,end):
    x1,y1=to_index(*start)
    x2,y2=to_index(*end)

    if (x1+y1)%2!=(x2+y2)%2:
        return "Impossible"

    if x1==x2 and y1==y2:
        return f"0 {to_pos(x1,y1)}"

    if abs(x1-x2)==abs(y1-y2):
        return f"1 {to_pos(x1,y1)} {to_pos(x2,y2)}"

    # Try all possible intersections for 2-move bishop path
    for i in range(8):
        for j in range(8):
            if abs(x1 -i)==abs(y1-j) and abs(x2-i)==abs(y2-j):
                return f"2 {to_pos(x1,y1)} {to_pos(i,j)} {to_pos(x2,y2)}"
    return "Impossible"

# Main
t=int(input())
for _ in range(t):
    parts=input().split()
    start=(parts[0],parts[1])
    end=(parts[2],parts[3])
    print(bishop_moves(start,end))
