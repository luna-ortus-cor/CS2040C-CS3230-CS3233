k="1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";$<.map{puts _1.gsub(/./){|c|k[c]?k[k.index(c)-1]:c}}
