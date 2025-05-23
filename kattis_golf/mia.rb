g=->(x,y){x*y==2?777:x==y ?x<<7:[10*x+y,10*y+x].max};while gets[0]!=?0;a,b,c,d=$_.split.map &:to_i;puts (e=g[a,b])==(f=g[c,d])?:'tie.':"Player #{e>f ?1:2} wins."end
