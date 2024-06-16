L,D,X=$<.map &:to_i
f=->a{a+=1 while a.abs.digits.sum!=X;a}
p f[L],-f[-D]
