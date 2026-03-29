P,T=gets.split.map &:to_i;p P.times.count{(1..T).map{!gets[1..][/[A-Z]/]}.all?}
