g,s,c=gets.split.map &:to_i;t=3*g+2*s+c;$><<(%w[Estate Duchy Province][t>8?2:(t-2)/3]+' or 'if t>1)<<%w[Copper Silver Gold][t>8?2:t/3]
