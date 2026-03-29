c,k=$<.read.split;puts c.bytes.map.with_index{k<<(x=((_1-k[_2].ord)%26+65).chr);x}*''
