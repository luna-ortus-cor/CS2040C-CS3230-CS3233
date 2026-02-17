gets;g=$<.map &:chop;c=[0]*5;g.each_cons(2){|a,b|(a.size-1).times{|j|s=a[j,2]+b[j,2];s[?#]||c[s.count ?X]+=1}};p *c
