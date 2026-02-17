k=(2..9).flat_map{|d|(1..(d==7||d==9?4:3)).map{d.to_s*_1}};gets.to_i.times{|i|puts"Case ##{i+1}: "+gets.chop.chars.map{|c|c<?a?'0':k[c.ord-97]}.chunk{_1[0]}.map{|_,v|v*' '}*''}
