(k,m=$_.split;t=gets.split;o=!p;m.to_i.times{gets;o&=t.sum{$_[_1]?1:0}>=$_.split[1].to_i};puts o ?:yes: :no)while gets>?1
