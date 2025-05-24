h=Hash.new 0;c=s=0;(t,p,v=$_.split;v>?s?h[p]+=20:(c+=1;s+=t.to_i+h[p]))while gets&&$_>?0;puts"#{c} #{s}"
