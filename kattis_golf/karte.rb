puts (c=gets.scan /.{3}/).uniq!=c ?:GRESKA:%w(P K H T).map{13-$_.count(_1)}.join(' ')
