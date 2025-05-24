n,*a=$<.read.split.map &:to_i;$><<[1,*[*2..n].sort_by{a[_1-2]}]*' '
