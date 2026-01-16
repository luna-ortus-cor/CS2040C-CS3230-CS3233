import sys

def eval_simple(line,tokens=''):
    if not tokens:tokens=line.split()
    stack=[int(tokens[0])]
    i=1
    while i<len(tokens):
        if tokens[i]=='*':
            stack[-1]*=int(tokens[i+1])
        else:
            stack.append(tokens[i])
            stack.append(int(tokens[i+1]))
        i+=2

    res=stack[0]
    i=1
    while i<len(stack):
        if stack[i]=='+':
            res+=stack[i+1]
        else:
            res-=stack[i+1]
        i+=2
    return res

def eval_region(grid, top, bottom, left, right):
    h=bottom-top+1
    mid=-1
    if h==3:mid=1
    elif h==2:mid=1
    else:mid=0
    line=grid[mid]
    tokens=['']
    num,den,sqrt='','',''
    for i in range(len(line)):
        e=line[i]
        if e!=' ' and e!='=' and e!='_' and e!='\\' and e!='/' and e!='\n':
            if grid[top][i]=='_':
                sqrt+=e
            else:
                tokens[-1]+=e
        elif e==' ' or e=='\n':
            if grid[top][i]=='_':
                sqrt+=e
            else:
                if num!='' and den!='':
                    tokens[-1]=str(eval_simple(num)//eval_simple(den))
                    num,den='',''
                if sqrt!='':
                    tokens[-1]=str(int(eval_simple(sqrt)**0.5))
                    sqrt=''
                if tokens[-1]!='':
                    tokens.append('')
        elif e=='=':
            num+=grid[top][i]
            den+=grid[bottom][i]
        else:
            pass
    if tokens[-1]=='':tokens=tokens[:-1]
    return eval_simple('',tokens)

R,C=map(int,sys.stdin.readline().split())
grid=sys.stdin.readlines()
print(eval_region(grid,0,R-1,0,C-1))
