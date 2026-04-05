gets;h=Hash.new 0;$<.map{h[_1.split.sort]+=1};p h.select{_2==h.values.max}.values.sum
