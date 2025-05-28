c,x,m=gets.split.map &:to_f;puts (a=$<.map(&:split).rindex{x*m/_1.to_f+m/_2.to_f<=c/2})?"YES #{55+5*a}":"NO"
