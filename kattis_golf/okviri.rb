s=gets;n=s.size-1;(0..4).map{|y|puts (0..4*n).map{|x|i=x/4;k=(i+1)%3<1||x%4<1&&i>0&&i%3<1;f=k ??*:?#;d=(x%4-2).abs+(y-2).abs;d==0&&y==2?s[i]:i<n&&d==2?f:d==2?n%3>0??#:?*:?.}.join}
