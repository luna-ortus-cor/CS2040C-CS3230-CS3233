a,b,c=gets.split.map(&:to_i).sort;p 3*a+6*[c-b,b-a].min-b-c
