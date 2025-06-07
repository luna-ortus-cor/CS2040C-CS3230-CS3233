gets;n=%w[A A# B C C# D D# E F F# G G#];s=gets.split;r=n.select{|x|s-[0,2,4,5,7,9,11].map{n[(n.index(x)+_1)%12]}==[]};puts r==[]?:none:r*' '
