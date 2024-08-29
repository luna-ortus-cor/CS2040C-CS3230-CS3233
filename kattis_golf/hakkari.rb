n,m=gets.split.map &:to_i;a=($<.map &:strip)*'';p a.count'*';(n*m).times{puts"#{_1/m+1} #{_1%m+1}"if a[_1]==?*}
