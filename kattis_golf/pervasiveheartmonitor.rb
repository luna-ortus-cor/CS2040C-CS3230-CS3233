(t=$_.split;n=t.grep(/[A-Z]/i)*' ';h=t-n.split;puts"#{h.sum(&:to_f)/h.size} #{n}")while gets
