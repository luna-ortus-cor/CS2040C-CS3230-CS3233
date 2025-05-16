a=$<.map{_1.split};b=a[3..].transpose.map{_1.sum &:to_i};$><<a[2][b.index b.max]
