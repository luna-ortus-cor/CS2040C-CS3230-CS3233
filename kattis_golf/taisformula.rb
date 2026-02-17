gets;p $<.map{_1.split.map &:to_f}.each_cons(2).sum{(_2[0]-_1[0])*(_1[1]+_2[1])/2000}
