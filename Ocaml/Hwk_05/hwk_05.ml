let rec ands (l:bool list) :bool = 
	match l with 
	|(x :: xs) -> if x then (ands xs) 
					else false
	|_ -> true