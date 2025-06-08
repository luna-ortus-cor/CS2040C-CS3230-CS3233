1.upto(gets.to_i){|z|r,p,d=gets.split.map &:to_f;a=(1..r.to_i).map{gets.split};m=a.find{_3=='100.0'}[1].to_f*d/p;puts"Recipe # #{z}";a.map{puts"#{_1} #{'%.1f'%[m*_3.to_f/100]}"};puts'-'*40}
