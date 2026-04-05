$<.map{|l|n,s=l.split;(a=[*?A..?Z]*""+'_.';puts s.reverse.gsub(/./){a[(a.index(_1)+n.to_i)%28]})if n>?0}
