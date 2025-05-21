$<.map{_1.split.map &:to_i}[..-2].map{puts _1+_2==13?"Never speak again.":%w[Undecided. To\ the\ convention. Left\ beehind.][_1<=>_2]}
