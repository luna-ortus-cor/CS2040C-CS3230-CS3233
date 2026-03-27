import sys

def solve():
    line = sys.stdin.read().strip()
    left, res_word = line.split('=')
    w1, w2 = left.split('+')

    weights = {}
    for word, sign in [(w1, 1), (w2, 1), (res_word, -1)]:
        for i, char in enumerate(reversed(word)):
            weights[char] = weights.get(char, 0) + sign * (10**i)

    chars = sorted(weights.keys())
    leading = {w1[0], w2[0], res_word[0]}
    
    char_weights = [weights[c] for c in chars]
    is_leading = [c in leading for c in chars]
    
    n = len(chars)
    used = [False] * 10
    assignment = [0] * n

    def backtrack(idx, current_sum):
        if idx == n:
            return current_sum == 0

        for d in range(10):
            if not used[d]:
                if d == 0 and is_leading[idx]:
                    continue
                
                used[d] = True
                assignment[idx] = d
                if backtrack(idx + 1, current_sum + d * char_weights[idx]):
                    return True
                used[d] = False
        return False

    if backtrack(0, 0):
        mapping = {chars[i]: str(assignment[i]) for i in range(n)}
        def translate(w): return "".join(mapping[c] for c in w)
        print(f"{translate(w1)}+{translate(w2)}={translate(res_word)}")
    else:
        print("impossible")
solve()
