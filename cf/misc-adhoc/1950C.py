import sys
#this is just simple implementation of the logic in time conversion and formatting
#only tricky part is handling midnight 0000->12am and noon 1200->12pm and similar times
t=int(sys.stdin.readline())
d={0:'12',1:'01',2:'02',3:'03',4:'04',5:'05',6:'06',7:'07',8:'08',9:'09',10:'10',11:'11',12:'12'}
for _ in range(t):
    s=sys.stdin.readline().strip().split(':')
    print(f'{d[int(s[0])%12]}:{s[1]}'+' '+f'{"AM" if int(s[0])<12 else "PM"}')
