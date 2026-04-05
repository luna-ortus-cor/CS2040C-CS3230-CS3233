m,t=gets.split;puts m>?D?t.gsub(/(.)\1*/){_1[0]+_1.size.to_s}:t.scan(/(.)(\d)/).map{_1*_2.to_i}*''
