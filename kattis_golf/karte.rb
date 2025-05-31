puts (c=gets.scan /.../).uniq!=c ?:GRESKA:%w(P K H T).map{13-$_.count(_1)}*' '
