type formula = And of formula * formula
	     | Or  of formula * formula
	     | Not of formula
	     | Prop of string
	     | True
	     | False

exception KeepLooking

type subst = (string * bool) list

let show_list show l =
  let rec sl l =
    match l with
    | [] -> ""
    | [x] -> show x
    | x::xs -> show x ^ "; " ^ sl xs
  in "[ " ^ sl l ^ " ]"

let show_string_bool_pair (s,b) =
  "(\"" ^ s ^ "\"," ^ (if b then "true" else "false") ^ ")"

let show_subst = show_list show_string_bool_pair

let is_elem v l =
  List.fold_right (fun x in_rest -> if x = v then true else in_rest) l false

let rec explode = function
  | "" -> []
  | s  -> String.get s 0 :: explode (String.sub s 1 ((String.length s) - 1))

let dedup lst =
  let f elem to_keep =
    if is_elem elem to_keep then to_keep else elem::to_keep
  in List.fold_right f lst []

let rec lookup name env =
  match env with
  | [ ] -> false
  | (k,v)::rest -> if name = k then v else lookup name rest



let rec eval (f:formula) (s:subst) :bool =
  	match f with
  	|And (f1, f2) -> (match eval f1 s, eval f2 s with
  						|true, true -> true
  						|true, false -> false
  						|false, false -> false
  						|false, true -> false
  						|_ -> raise (Failure "can't perform And")
  					  )
  	| Or  (f1, f2) -> (match eval f1 s, eval f2 s with
              |true, true -> true
              |true, false -> true
              |false, false -> false
              |false, true -> true
              |_ -> raise (Failure "can't perform Or")
              )
	  | Not f1 -> (match eval f1 s with
  						|true  -> false
  						|false -> true
  						|_ -> raise (Failure "can't perform Not")
  					  )
    | Prop s1 -> lookup s1 s
    | True    -> true
    | False 	-> false
let rec freevars (f:formula) :string list =
    match f with
    |And (f1, f2) ->  dedup (freevars f1 @ freevars f2)
    | Or  (f1, f2) ->  dedup (freevars f1 @ freevars f2)
    | Not f1 -> dedup (freevars f1)
    | Prop s1 -> [s1]
    | True -> []
    | False -> []

(*this process_solution is from the lecture notes *)
let rec process_solution show s =
  print_endline ( "Here is a solution:\n" ^ show s) ;
  print_endline ("Do you like it?") ;

  match is_elem 'Y' (explode (String.capitalize (read_line ()))) with
  | true  -> print_endline "Thanks for playing..." ; Some s
  | false -> raise KeepLooking


(*
let passenv =
	let rec helper f ac =
		match (freevars f) with
		| x :: xs -> [(x, true)] @ ac
		| x -> [(x,true)] @ ac
		| _ -> ac
	in helper f []
*)
let is_tautology (f:formula) (func):subst option = (*func is a funciton which type is (subst -> subst option) *)
   let rec try_subset partial_subset rest_of_the_set =
    if eval f partial_subset = false && partial_subset <> [] && rest_of_the_set = []
    then func partial_subset
    else (match rest_of_the_set with
	 | [] -> raise KeepLooking
	 | x::xs -> (try try_subset (partial_subset @ [(x, true)]) xs with
		    | KeepLooking -> try_subset (partial_subset @ [(x, false)]) xs))
  	in (try try_subset [] (freevars f) with
     | KeepLooking -> None)


let is_tautology_first f = is_tautology f (fun s -> Some s)

let is_tautology_print_all f =
  is_tautology
    f
    (fun s -> print_endline (show_subst s);
        raise KeepLooking)
