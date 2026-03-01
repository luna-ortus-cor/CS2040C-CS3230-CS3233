t=[];gets;gets.chars{|c|'[({'[c]?t<<c:t.pop!={')'=>?(,']'=>?[,'}'=>?{}[c]&&(puts'Invalid';exit)};puts t[0]?'Invalid':'Valid'
