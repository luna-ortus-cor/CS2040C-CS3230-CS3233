$<.map{_1=~/(\S+ \d+ \d+) (\d+):(\d+) (\d+):(\d+)/;t=($4.to_i-$2.to_i)*60+$5.to_i-$3.to_i;puts"#{$1} #{t/60} hours #{t%60} minutes"}
