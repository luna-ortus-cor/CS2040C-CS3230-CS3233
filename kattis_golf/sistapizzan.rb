puts (a=gets.to_i)%2*a-$<.sum{_1.to_i&1}!=0?:Ja:'Nej'

#trick is to observe:
#a=1 -> Ja if &1 sum is <1 Nej if sum is 1 b- a*(a%2) 0
#a=2 -> Ja if &1 sum is >0 Nej if sum is 0 b- a*(a%2) 0
#a=3 -> Ja if &1 sum is <3 Nej if sum is 3 b- a*(a%2) 0
#a=4 -> Ja if &1 sum is >0 Nej if sum is 0 b- a*(a%2) 0
#etc.
