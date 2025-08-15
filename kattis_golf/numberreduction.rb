f=->n{n<2?0:1+f[n%2<1?n/2:3*n+1]};p f[gets.to_i]
