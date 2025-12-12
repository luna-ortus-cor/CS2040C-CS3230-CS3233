gets;$><<gets.split.map(&:to_i).sort.slice_when{_1+1<_2}.map{|c|c[2]?[c[0],c[-1]]*?-:c}*' '
