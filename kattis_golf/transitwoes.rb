a,d,b,c=(1..4).map{gets.split.map &:to_i};s,t,n=a;n.times{|i|s+=d[i];s+=-s%c[i]%c[i];s+=b[i]};puts t>=s+d[n]?:yes: :no
