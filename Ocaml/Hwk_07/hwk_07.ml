module type Arithmetic_intf = sig
    type t
    val to_string : t -> string
    val add : t -> t -> t
    val mul : t -> t -> t
    val zero: t
  end



module type Vector_intf = sig
    type t
    type endpoint
    type somepoint
    val create : int -> somepoint -> t
    val from_list: somepoint list -> t
    val to_list: t -> somepoint list
    val scalar_add: somepoint -> t -> t
    val	scalar_mul: somepoint -> t -> t
    val scalar_prod: t -> t -> somepoint option
    val to_string : t -> string
    val size: t -> int
  end


  module Make_vector(Endpoint:Arithmetic_intf):
    (Vector_intf with type somepoint = Endpoint.t) = struct

   type somepoint = Endpoint.t
   type endpoint = somepoint list

   type t = | Vector of int * endpoint
           | Empty

  let create size ivalue =
  	let rec make_value s v =
  		if s = 0 then [] else v :: (make_value (s-1) v)
  	in
  	let valuelist = make_value size ivalue
  	in
    Vector(size, valuelist)


  let from_list l  =
  		let rec counter n l' =
  			match l' with
  			 | x::xs -> counter (n+1) xs
  			 | [] -> n
  		in
  		let count = counter 0 l
  		in
  		if count = 0 then Empty
  		else Vector(count,l)
  let to_list t =
  		match t with
  		|Vector(_, rest) -> rest
  		| _ -> []
  let scalar_add v t =
  		match t with
  		|Vector(s, rest) -> Vector(s, List.map (Endpoint.add v) rest)
  		| _ -> raise(Failure "Can't apply add")


  let scalar_mul v t =
  		match t with
  		|Vector(s, rest) -> Vector(s, List.map (Endpoint.mul v) rest)
  		| _ -> raise(Failure "Can't apply mul")


  let scalar_prod t1 t2=
  		let rec addup l l' =
  			match l , l' with
  			|x1 :: xs1 , x2 :: xs2 -> Endpoint.add (Endpoint.mul x1 x2) (addup xs1 xs2)
  			| _ -> Endpoint.zero
  		in
  		match t1, t2 with
  		|Vector(s1, l1) , Vector(s2, l2) ->
  			if s1 <> s2 then None
  			else Some (addup l1 l2)
  		|_ -> None


  let to_string t : string =
  	let rec concat l =
  		match l with
      |[x] -> Endpoint.to_string x ^""
  		|x :: xs -> Endpoint.to_string x ^", "^ concat xs
  		| _ -> ""
  	in
    match t with
    | Empty -> "Empty"
    | Vector (size, rest)
      -> "<< "^(string_of_int size) ^ " | " ^ (concat rest)^" >>"

   let size t =
   		match t with
   		| Vector(s,_) -> s
   		| _ -> 0

end

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

  let add x y =
  		match x , y with
  		|(x1, y1), (x2, y2) -> (x1 +. x2, y1 +. y2)

  let mul x y =
  		match x , y with
  		|(x1, y1), (x2, y2) -> (x1*.x2-.y1*.y2, x1*.y2+.x2*.y1)
  
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
