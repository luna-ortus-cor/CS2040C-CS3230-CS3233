gets.to_i.times{a=gets.to_i.times.map{gets.to_i};puts a.count(m=a.max)>1?"no winner":"#{a.sum<m*2?:majority: :minority} winner #{a.index(m)+1}"}
