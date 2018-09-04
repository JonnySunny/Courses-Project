
type expr 
  = Add of expr * expr
  | Sub of expr * expr
  | Mul of expr * expr
  | Div of expr * expr
  
  | Lt of expr * expr
  | Eq of expr * expr
  | And of expr * expr

  | If of expr * expr * expr

  | Id of string
  
  | Let of string * expr * expr
  | LetRec of string * expr * expr

  | App of expr * expr
  | Lambda of string * expr

  | Value of value
and environment = (string * value) list

and value 
  = Int of int
  | Bool of bool
  | Closure of string * expr * environment
  | Ref of value ref

  (* You may need an extra constructor for this type. *)


 let rec freevars (e:expr):string list= 
    match e with
    | Add(e1,e2) -> (freevars e1) @ (freevars e2)
    | Sub (e1,e2) -> (freevars e1) @ (freevars e2)
    | Mul (e1,e2) -> (freevars e1) @ (freevars e2)
    | Div (e1,e2) -> (freevars e1) @ (freevars e2)
    | Lt (e1,e2) -> (freevars e1) @ (freevars e2)
    | Eq (e1,e2) -> (freevars e1) @ (freevars e2)
    | And (e1,e2) -> (freevars e1) @ (freevars e2)
    | If (e1,e2,e3) -> (freevars e1) @ (freevars e2) @ (freevars e3)
    | Id n -> [n]
    | Let (s,dexpr,body) -> (freevars dexpr) @  (List.filter (fun s1 -> (s1 = s )= false) (freevars body))
    | LetRec (s,dexpr,body) ->  (List.filter (fun s1 -> (s1 = s )= false) (freevars dexpr)) @   (List.filter (fun s1 -> (s1 = s )= false) (freevars body))
    | App (e1,e2) -> (freevars e1) @ (freevars e2)
    | Lambda (s,body) ->  (List.filter (fun s1 -> (s1 = s )= false) (freevars body))
    | Value v -> []



let rec lookup (n:string) (env: environment) : value =
  match env with
  | [] -> raise (Failure ("Identifier " ^ n ^ " not in scope"))
  | (n',v) :: rest when n = n' -> v
  | _ :: rest -> lookup n rest

let rec eval (env:environment) (e:expr) : value =
  match e with
  | Value v -> v 
  | Add (e1, e2) -> 
     ( match eval env e1, eval env e2 with
       | Int i1, Int i2 -> Int (i1 + i2) 
       | _ -> raise (Failure "Incompatible types on Add")
     )
  | Sub (e1, e2) -> 
     ( match eval env e1, eval env e2 with
       | Int i1, Int i2 -> Int (i1 - i2) 
       | _ -> raise (Failure "Incompatible types on Sub")
     )
  | Mul (e1, e2) -> 
     ( match eval env e1, eval env e2 with
       | Int i1, Int i2 -> Int (i1 * i2) 
       | _ -> raise (Failure "Incompatible types on Mul")
     )
  | Div (e1, e2) -> 
     ( match eval env e1, eval env e2 with
       | Int i1, Int i2 -> Int (i1 / i2) 
       | _ -> raise (Failure "Incompatible types on Div")
     )
   | Lt (e1, e2) -> 
     ( match eval env e1, eval env e2 with
       | Int i1, Int i2 -> Bool (i1 < i2) 
       | _ -> raise (Failure "Incompatible types on Lt")
     )
  | Eq (e1, e2) -> 
     ( match eval env e1, eval env e2 with
       | Int i1, Int i2 -> Bool (i1 = i2) 
       | _ -> raise (Failure "Incompatible types on Eq")
     )
  | And (e1, e2) -> 
     ( match eval env e1, eval env e2 with
       | Bool i1, Bool i2 -> Bool (i1 && i2) 
       | _ -> raise (Failure "Incompatible types on And")
     )



  | If(e1,e2,e3) -> 
      (match eval env e1 with
      |Bool true -> eval env e2
      |Bool false -> eval env e3
      |_-> raise (Failure "Incompatible types on If"))
    
  | Id n -> lookup n env

  | Let (s, dexpr , body) ->
     let dexpr_v = eval env dexpr in
     let body_v = eval ((s,dexpr_v)::env) body in
     body_v

  | App (f,v) -> 
      (match (eval env f) , (eval env v) with
      |Closure(s,e,l), Int v -> eval ((s,Int v) :: l) e
      |Ref clo, Int v2 -> 
        (match !clo with
            |Closure(s,e,l) -> eval ((s,Int v2) :: l) e
            |_ -> raise (Failure "Incompatible types on App")
        )
      |_ -> raise (Failure "Incompatible types on App"))

  | Lambda (s, body) -> Closure(s,body,env)

  | Value v -> v

  | LetRec (s, body, dexpr ) -> (match body with
        | Lambda (s_la, body) -> let recRef = ref (Int 999) in
                    let c =
                            Closure (s_la,
                                          body,
                                  [ (s, Ref recRef) ]) in
                    let () = recRef := c in
                        eval ((s,c)::env) dexpr
        | _ -> raise (Failure "Incompatible types on LetRec"))
let evaluate (e:expr) : value = eval [] e
 


(* Some sample expressions *)

let inc = Lambda ("n", Add(Id "n", Value (Int 1)))

let add = Lambda ("x",
                  Lambda ("y", Add (Id "x", Id "y"))
                 )

(* The 'sumToN' function *)
let sumToN_expr : expr =
    LetRec ("sumToN", 
            Lambda ("n", 
                    If (Eq (Id "n", Value (Int 0)),
                        Value (Int 0),
                        Add (Id "n", 
                             App (Id "sumToN", 
                                  Sub (Id "n", Value (Int 1))
                                 )
                            )
                       )
                   ),
            Id "sumToN"
           )


let twenty_one : value = evaluate (App (sumToN_expr, Value (Int 6)))

let not_twenty_one : value = evaluate (App (sumToN_expr, Value (Int 10)))




