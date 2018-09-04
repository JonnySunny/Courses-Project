(* Stream examples *)

type 'a stream = Cons of 'a * (unit -> 'a stream)

let rec ones = Cons (1, fun () -> ones)

(* So, where are all the ones?  We do not evaluate "under a lambda", 
   which means that the "ones" on the right hand side is not evaluated. *)

(* Note, "unit" is the only value of the type "()".  This is not too
   much unlike "void" in C.  We use the unit type as the output type
   for functions that perform some action like printing but return no
   meaningful result.
   Here the lambda expressions doesn't use the input unit value,
   we just use this technique to delay evaluation of "ones". 
   Sometimes lambda expressions that take a unit value with the
   intention of delaying evaluation are called "thunks".  *)

let head (s: 'a stream) : 'a = match s with
  | Cons (v, _) -> v

let tail (s: 'a stream) : 'a stream = match s with
  | Cons (_, tl) -> tl ()

let rec from n = 
  Cons ( n, 
         fun () -> print_endline ("step " ^ string_of_int (n+1)) ; 
                   from (n+1) )

let nats = from 1

(* what is
    head nats,   head (tail nats),     head (tail (tail nats))     ?
 *)

let rec take (n:int) (s : 'a stream) : ('a list) =
 if n = 0 then []
 else match s with
      | Cons (v, tl) -> v :: take (n-1) (tl ())


(* Can we write functions like map and filter for streams? *)

let rec filter (f: 'a -> bool) (s: 'a stream) : 'a stream =
  match s with
  | Cons (hd, tl) ->
     let rest = (fun () -> filter f (tl ()))
     in
     if f hd then Cons (hd, rest) else rest ()

let even x = x mod 2 = 0

let rec squares_from n : int stream = Cons (n*n, fun () -> squares_from (n+1) )

let t1 = take 10 (squares_from 1)

let squares = squares_from 1


let rec zip (f: 'a -> 'b -> 'c) (s1: 'a stream) (s2: 'b stream) : 'c stream =
  match s1, s2 with
  | Cons (hd1, tl1), Cons (hd2, tl2) ->
     Cons (f hd1 hd2, fun () -> zip f (tl1 ()) (tl2 ()) )

let rec nats2 = Cons ( 1, fun () -> zip (+) ones nats2)

(* Computing factorials
   nats       = 1   2   3   4    5     6 
                 \   \   \   \    \     \
                  *   *   *   *    *     *
                   \   \   \   \    \     \
   factorials = 1-*-1-*-2-*-6-*-24-*-120-*-720
   We can define factorials recursively.  Each element in the stream
   is the product of then "next" natural number and the previous
   factorial.
 *)

let rec factorials = Cons ( 1, fun () -> zip ( * ) nats factorials )


(* The Sieve of Eratosthenes
   We can compute prime numbers by starting with the sequence of
   natual numbers beginning at 2. 
   We take the first element in the sequence save it as a prime number
   and then cross of all multiples of that number in the rest of the
   sequence.
   Then repeat for the next number in the sequence.
   This process will find all the prime numbers.
 *)

let non f x = not (f x)
let multiple_of a b = b mod a = 0

let sift (a:int) (s:int stream) = filter (non (multiple_of a)) s

let rec sieve s = match s with
  | Cons (x, xs) -> Cons(x, fun () -> sieve (sift x (xs ()) ))

let primes = sieve (from 2)


(*my own work starts here Zhongyi Sun *)
let rec cubes_from n :int stream =  (*similiar to the square one*)
    Cons(n*n*n, fun() -> cubes_from (n+1))  

let rec drop (n:int) (s:'a stream) :'a stream =  
  (*similar to the drop in the list part, but pay attention to the Cons(_,tl) -> tl() *)
  (*drop the number n elemeents in the stream, and return the rest of this *)
  if n = 0 then s
  else match s with 
  |Cons(hd,tl) -> drop (n-1) (tl ())

let rec drop_until (f:'a -> bool) (s:'a stream) :'a stream = 
  (*if there exist just the first matches, then it'll give you a warning 8 *)
  (*this will drop number until it finds one which return true*)
  match s with
  |Cons(hd, tl) when ((f hd) = false) ->  drop_until f (tl())
  |Cons(hd, tl) when (f hd) = true -> Cons(hd, tl)
  |_ -> raise (Failure  "Error here!")

let rec map (f:'a ->'b) (s:'a stream) :'b stream = 
  (* map the f to every element in the stream and return the new stream *)
  (*pay attention when write (tl()) , it needs a parathesis here *)
  match s with 
  |Cons(hd, tl) -> Cons((f hd), fun() -> map f (tl()))


(* mapping a function take a number and return its square *)
let squares_again  = map (fun n -> n*n) nats

let sqrt_approximations (f:float) :float stream = (*similai function as before, but this time changed it output the stream *)
    let rec helper (lower,upper) =
    if(((lower+.upper)/.(2.0))*.((lower+.upper)/.(2.0)))> f
    then Cons((lower+.upper)/.(2.0), fun() -> helper (lower,(lower+.upper)/.(2.0)) )
    else Cons((lower+.upper)/.(2.0),fun() ->helper (((lower+.upper)/.(2.0)),upper))
  in helper(1.0,f)



let rec epsilon_diff (epsilon:float) (s:float stream) :float =  (*compare succssive number , and return the second one *)
    match s with
    |Cons(hd1, tl1) -> (match tl1() with
                      |Cons(hd2, tl2) -> if (abs_float(hd1 -. hd2) < epsilon) then hd2
                                         else (epsilon_diff epsilon (tl1())))



let diminishing = (*using a helper function to gernerate a stream*)
  let rec helper n = 
    Cons(n, fun() -> helper (n /. 2.0))
  in helper 16.0


let rough_guess = epsilon_diff 1.0 (sqrt_approximations 50.0) 


let precise_calculation = epsilon_diff 0.00001 (sqrt_approximations 50.0) 


(*when we write sqrt_threshold 50.0 3.0 in the ocaml , we'll get 7.125. Since the first get a sqrtroot stream of this value. and compare the difference definde below with t. For this example, take first 10 elements, we got [25.5; 13.25; 7.125; 4.0625; 5.59375; 6.359375; 6.7421875; 6.93359375; 7.029296875; 7.0771484375] the 7.125 * 7.125 - 50 < 3.0 is true, so it returns 7.125. Ohterwise, if we use differnet threshold, the progress is similar as this example*)
let sqrt_threshold (v:float) (t:float) :float =  (*using sqrt_appeoximations get the float stream and then using drop_until to set condition , then using head to get the value*)

    let a  = sqrt_approximations v in 
    let f v' s = if (s *. s) -. v' < t then true else false in
    let s' = (drop_until (f v) a) in 
    head(s')  (*head is defined before*)





