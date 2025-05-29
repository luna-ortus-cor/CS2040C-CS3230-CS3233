a,b,c,d,t=$<.read.split.map &:to_i;puts (t-=(a-c).abs+(b-d).abs)<0||t%2>0??N:?Y
