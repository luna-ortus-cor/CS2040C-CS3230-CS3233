s=[];gets.split.map{|t|s<<(t[/\d/]?t:"(#{s.pop(2)*t})")};$><<s[0]
