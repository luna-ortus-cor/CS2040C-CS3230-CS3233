s=gets.chop;puts [?_,'a-z','A-Z','^_a-zA-Z'].map{s.count(_1)/s.size.to_f}
