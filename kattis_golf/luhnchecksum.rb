gets;$<.map{i=0;puts _1.chop.reverse.chars.sum{|c|i^=1;c=c.to_i;i>0?c:c/5+2*(c%5)}%10<1?:PASS: :FAIL}
