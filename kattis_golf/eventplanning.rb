n,b,h,w=gets.split.map &:to_i;m=b+1;h.times{c=n*gets.to_i;gets.split.map{_1.to_i>=n&&m=[m,c].min}};puts m<b+1?m:"stay home"
