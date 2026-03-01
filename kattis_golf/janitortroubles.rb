a=gets.split.map &:to_f;p a.map{a.sum/2-_1}.reduce(:*)**0.5
