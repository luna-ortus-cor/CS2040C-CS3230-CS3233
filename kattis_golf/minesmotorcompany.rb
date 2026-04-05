gets;p $<.to_a.each_cons(2).sum{|i,j|(i.bytes.zip(j.bytes).sum{(_2-_1).abs})}
