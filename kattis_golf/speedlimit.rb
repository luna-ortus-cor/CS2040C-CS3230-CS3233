while(n=gets.to_i)>0;d=c=0;n.times{a,b=gets.split.map &:to_i;d+=a.*b-c;c=b};puts"#{d} miles"end
