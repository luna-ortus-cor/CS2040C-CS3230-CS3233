puts ([*1..gets.to_i]-$<.map(&:to_i))[0]||"too late"
