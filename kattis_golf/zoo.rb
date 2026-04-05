c=1;while(n=gets.to_i)>0;h=Hash.new 0;n.times{h[gets.split.last.downcase]+=1};puts"List #{c}:";h.sort.each{puts"#{_1} | #{_2}"};c+=1;end
