b,*a=$<.map{_1.split.map &:to_i};puts (1..b[0]-2).any?{|i|(1..b[1]-2).any?{|j|a[i][j]<[a[i-1][j],a[i+1][j],a[i][j-1],a[i][j+1]].min}}?:Jebb:'Neibb'
