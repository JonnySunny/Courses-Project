(* 1/31/2017
* By Jason Gruenhagen Furqan Syed Zhongyi Sun
*)
let even num =
      if num mod 2 = 0 then true else false


let rec euclid m n =
 (* exception*)
 if(m <= 0 || n <= 0 ) then raise(Failure " Input Format incorrectly")
else 	if m = n then m
	else if m mod n = 0 then n
	else if m > n then euclid (m-n) n
	else euclid m (n - m)

let frac_add (x1,y1)(x2,y2) =
if(y1 = 0 || y2 = 0) then raise (Failure "denominator is zero")
((x1*y2)+(x2*y1),(y1*y2))

let frac_simplify(m,n) = (m/ euclid m n, n/euclid m n )

let square_approx n ac  =
	let rec helper (lower,upper) =
		if ((upper-.lower) < ac || (upper-.lower = ac)) then (lower,upper)
		else if(((lower+.upper)/.(2.0))*.((lower+.upper)/.(2.0)))> n
		then helper (lower,(lower+.upper)/.(2.0)
)
		else helper ((lower+.upper)/.(2.0)
 ,upper) in helper (1.0,n)

(*can make another version ,make a helper function and assume the first element is the max to compare with others)
 let rec max_list xl =
     match xl with
| [] -> raise(Failure "Empty List!")
| x1 :: x2 :: [] -> if x1 > x2 then x1 else x2
| x1 :: res -> if x1 > max_list res then x1 else max_list res



let rec drop n xl =
match xl with
|[ ] -> [ ]
|x1 :: rest when n = 1-> rest
|x1 :: rest when n > 1 -> drop (n-1) rest
| _ -> xl


let rec rev xl =
  match xl with
  | [ ] -> []
| x1 :: [] -> [x1]
| x1 :: rest ->(rev rest) @ [x1]



let distance (x1,y1) (x2,y2) = sqrt((x1-.x2)*.(x1-.x2)+.(y1-.y2)*.(y1-.y2));;

let head xl =
	 match xl with
	 | [] -> raise(Failure "Empty list empty !")
	 | hd :: _ -> hd

let perimeter xl =

  let hd = (head xl) in

    let rec sum xl =

match xl with

|[] -> raise (Failure "Empty !")
|x1 :: (x2::[]) -> distance x1 x2 +. distance x2 hd
|x1::(x2 :: rest) ->distance x1 x2 +.  sum(x2::rest)
| _ -> 0.0
in sum xl


let rec length xl =
match xl with
| [ ]-> 0
| x1 :: rest -> 1 + (length rest)

(* Jason *)
let is_matrix xl =
match xl with
|[]->true
| x1 :: [] -> true
| x1 :: x2 :: rest -> if length x1 =  length x2 then is_matrix x2::rest else false


let rec add xl n=
match xl with
|[] -> [n]
|x1 :: [] -> [x1+n]
|x1 :: rest -> [x1+n] @ (add rest n)

let rec matrix_scalar_add xl n =
match xl with
| [] -> raise (Failure "Empty")
| x1 :: [] -> add x1 n :: []
|x1 :: rest ->[add x1 n] @ []@( matrix_scalar_add rest n)
("change cons with @")
