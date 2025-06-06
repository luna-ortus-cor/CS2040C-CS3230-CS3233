a=gets.split.map &:to_i;t=Hash.new 0;$<.map{s,e=_1.split.map &:to_i;s.upto(e-1){|i|t[i]+=1}};p t.sum{_2*a[_2-1]}
