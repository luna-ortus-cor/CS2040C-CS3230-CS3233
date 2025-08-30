N,L,*a=$<.read.split.map &:to_i;t=d=0;N.times{D,R,G,*a=a;t-=d-(d=D);t+=[0,R-t%(R+G)].max};p t+L-d
