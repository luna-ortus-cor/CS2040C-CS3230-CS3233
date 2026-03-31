gets;$<.map{|l|n,*a=l.split.map &:to_f;puts"%.3f%%"%[100*a.count{_1>a.sum/n}/n]}
