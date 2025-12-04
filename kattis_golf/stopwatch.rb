puts gets.to_i%2>0?"still running":-$<.sum{_1.to_i*(-1)**$.}
