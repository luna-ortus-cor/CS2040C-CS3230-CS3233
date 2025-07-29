n,m,k,*z=$<.read.split.map &:to_i;a=Array.new(n){?.*m};k.times{a[z[2*_1]-1][z[2*_1+1]-1]=?*};puts a
