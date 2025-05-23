puts$<.map{a,b,c,d,e=*_1.split.map(&:to_i),40;1080+9*((a-b+e)%e+(c-b+e)%e+(c-d+e)%e)}[..-2]
