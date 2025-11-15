a=$<.to_a;p (8-a.count{_1=~/R/})*(8-(0..7).count{|i|a.any?{_1[i]>?.}})
