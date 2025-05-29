puts (1..$_.to_i).map{gets}.max_by{_1.scan(/([aeiouy])\1/).size}while gets>?1
