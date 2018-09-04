type pos = int*int

let rec is_not_elem set v =
  match set with
  | [] -> true
  | s::ss -> if s = v then false else is_not_elem ss v


let is_elem v l =
  List.fold_right (fun x in_rest -> if x = v then true else in_rest) l false
let final p = 
	p = (3,5) || p = (5,1)

let ok_move (p:pos) (moveto:pos): bool =
	match p with
	|(1,1) -> if moveto = (2,1) then true else false
	|(1,2) -> if (moveto = (1,1) || moveto = (0,2) )then false else true 
	|(1,3) -> if moveto = (0,3) then false else true
	|(1,4) -> if (moveto = (0,4) || moveto = (2,4)) then false else true
 	|(1,5) -> if (moveto = (0,5) || moveto = (1,6)) then false else true
	|(2,1) -> if (moveto = (1,1) || moveto = (3,1)) then true else false
	|(2,2) -> if (moveto = (1,2) || moveto = (3,2)) then true else false
	|(2,3) -> if moveto = (1,3) then true else false
	|(2,4) -> if (moveto = (2,3) || moveto = (1,4)) then false else true
	|(2,5) -> if (moveto = (2,4) || moveto = (1,5)) then true else false
	|(3,1) -> if (moveto = (3,0) || moveto = (4,1)) then false else true
	|(3,2) -> true
	|(3,3) -> if moveto = (2,3) then false else true
	|(3,4) -> if moveto = (3,5) then false else true
	|(3,5) -> if moveto = (4,5) then true else false (*??*)
	|(4,1) -> if moveto = (4,2) then true else false
	|(4,2) -> if (moveto = (4,1) || moveto = (3,2)) then true else false
	|(4,3) -> if (moveto = (4,2) || moveto = (4,4)) then false else true
	|(4,4) -> if (moveto = (4,3) || moveto = (5,4)) then false else true
	|(4,5) -> if moveto = (4,6) then false else true
	|(5,1) -> if moveto = (5,2) then true else false
	|(5,2) -> if (moveto = (5,1) || moveto = (5,3)) then true else false
	|(5,3) -> if (moveto = (5,2) || moveto = (4,3)) then true else false
	|(5,4) -> if moveto = (5,3) then true else false
	|(5,5) -> if moveto = (4,5) then true else false
	|_ -> false
	
exception KeepLooking

let maze_moves (p:pos) :pos list = 
	let goup (x,y)    = [(x-1, y)] in
	let godown (x,y)  = [(x+1, y)] in
	let goleft (x,y)  = [(x, y-1)] in
	let goright (x,y) = [(x, y+1)] in
	List.filter (ok_move p) (goup p @ godown p @ goleft p @ goright p)

let maze() = 
	let rec go_from pos path = 
		if final pos 
		then Some path
		else  match List.filter (is_not_elem path) (maze_moves pos) with
      		  | [] -> raise KeepLooking
      		  | [a] -> go_from a (path @ [a]) 
      		  | [a;b] -> 
         		(try go_from a (path @ [a]) with 
	  		  		| KeepLooking -> go_from b (path @ [b])
	 			)
	 		  | [a;b;c] ->
	 		  		(try go_from a (path @ [a]) with 
	  		  		| KeepLooking -> try go_from b (path @ [b]) with
	  		  						| KeepLooking -> go_from c (path @ [c])
	 			)
      		  | _ -> raise (Failure ("No way!"))
    in try go_from (2,3) [(2,3)] with
  	|KeepLooking -> None 