gets;a=gets.split.map(&:to_i).each_cons(3).map{[_1,_3].max};puts"#{1+a.index(b=a.min)} #{b}"
