t=l=98*gets.to_i;$<.map{a,b,c,d=_1.bytes;t-=a+b;l-=c+d};$><<[s=[t,l].min/2,t-2*s,l-2*s]*' '
