c,a,b=$<.map{_1.split.map(&:to_i).max};puts (a==b)?:possible:'impossible'
