
open hwk_07

module Int_arithmetic : (Arithmetic_intf with type t = int) = struct
  type t = int
  let to_string t = string_of_int t
  let add x y = x + y
  let mul x y = x * y
  let zero = 0

end

module Complex_arithmetic : (Arithmetic_intf with type t = float * float) = struct
  type t = float * float
  let  to_string t = 
  		match t with
  		|(x, y) -> "("^ string_of_float x ^"+"^string_of_float y^ "i)"
  		|_ -> raise (Failure "Can't apply to_string")
  let add x y = 
  		match x , y with
  		|(x1, y1), (x2, y2) -> (x1 +. x2, y1 +. y2)
  		|_ -> raise (Failure "Can't apply add")
  let mul x y = 
  		match x , y with
  		|(x1, y1), (x2, y2) -> (x1*.x2-.y1*.y2, x1*.y2+.x2*.y1)
  		|_ -> raise (Failure "Can't apply mul")
  let zero = (0.0, 0.0)

end

module Int_vector = Make_vector(Int_arithmetic)


module Complex_vector = Make_vector (Complex_arithmetic)
(* The following line now works. *)
let i = Int_vector.create 3 4

let v1 = Int_vector.create 10 1

let v2 = Int_vector.from_list [1;2;3;4;5]

let v3 = Int_vector.scalar_add 3 v2

let v4 = Int_vector.scalar_mul 10 v2

let i1 = Int_vector.scalar_prod v3 v4

let l1 = Int_vector.to_list v3 

let i2 = Int_vector.size v4

let s1 = Int_vector.to_string v1

let s2 = Int_vector.to_string v2

let s3 = Int_vector.to_string v3

let s4 = Int_vector.to_string v4

let v5 = Complex_vector.from_list [ (1.0, 2.0); (3.0, 4.0); (5.0, 6.0) ]

let v6 = Complex_vector.scalar_add (5.0, 5.0) v5

let c1 = Complex_vector.scalar_prod v5 v6

let s5 = Complex_vector.to_string v5

let s6 = Complex_vector.to_string v6