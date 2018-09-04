(* Part A *)
type 'a tree = Leaf of 'a
             | Fork of 'a * 'a tree * 'a tree

let rec t_size (t:'a tree) :int =
  match t with
  | Leaf _ -> 1
  | Fork(_, ta, tb) -> 1 + t_size ta + t_size tb


let rec t_sum (t : int tree) :int =
  match t with
  | Leaf v -> v
  | Fork(v , ta, tb) -> v + t_sum ta + t_sum tb

let rec t_charcount (t: string tree) :int =
  match t with
  |Leaf v -> String.length (v)
  | Fork (v , ta, tb) -> String.length(v) + t_charcount ta + t_charcount tb

let rec t_concat (t:string tree ) :string =
  match t with
  |Leaf v -> v
  |Fork(v, ta, tb) -> v ^ t_concat ta ^ t_concat tb



(* Part B*)

let rec t_opt_size (t:'a option tree): int =
  match t with
  | Leaf None -> 0
  | Leaf Some _ -> 1
  | Fork (None,_,_) -> 0
  | Fork (Some _,ta, tb) -> 1 + t_opt_size ta + t_opt_size tb

let rec t_opt_sum (t:int option tree) : int =
  match t with
  | Leaf None -> 0
  | Leaf Some v -> v
  | Fork (None,_,_) -> 0
  | Fork (Some v,ta, tb) -> v + t_opt_sum ta + t_opt_sum tb

let rec t_opt_charcount (t:string option tree): int =
  match t with
  | Leaf None -> 0
  | Leaf Some v -> String.length(v)
  | Fork (None,_,_) -> 0
  | Fork (Some v,ta, tb) -> String.length(v) + t_opt_charcount ta + t_opt_charcount tb

let rec t_opt_concat (t:string option tree):string =
  match t with
  | Leaf None -> ""
  | Leaf Some v -> v
  | Fork (None,_,_) -> ""
  | Fork (Some v,ta, tb) -> v ^ t_opt_concat ta ^ t_opt_concat tb


(*Part C *)
let rec tfold (l:'a -> 'b) (f:'a -> 'b -> 'b -> 'b)  (t:'a tree) : 'b =
         match t with
         | Leaf v -> l v
         | Fork (v, t1, t2) -> f v (tfold l f t1) (tfold l f t2)


let tf_size  (t: 'a tree):int = 
  tfold (fun v -> 1) (fun v tl tr -> 1 + tl + tr) t
  
let tf_sum (t:int tree):int = 
  tfold (fun v -> v) (fun v tl tr -> v + tl + tr) t

let tf_char_count (t:string tree) :int =
  tfold (fun v -> String.length(v)) (fun v tl tr -> String.length(v) + tl + tr) t

let tf_concat (t: string tree):string = 
  tfold(fun v -> v) (fun v tl tr -> v^tl^tr) t

let tf_opt_size (t: 'a option tree) :int = 
  tfold(fun x -> if x = None then 0 else 1) (fun x tl tr -> if x = None then 0+tl+tr else 1 + tl + tr) t

let tf_opt_sum (t: int option tree) :int =
  tfold(fun x -> match  x with 
                 |None -> 0
                 |Some x -> x) (fun x tl tr -> match x with
                                              |None ->  0+tl+tr 
                                              |Some x -> x + tl + tr) t

let tf_opt_char_count (t: string option tree) :int = 
  tfold(fun x -> match x with
                  | None -> 0
                  | Some x -> String.length(x)) (fun x tl tr -> match x with
                                                                | None -> 0 + tl + tr
                                                                | Some x ->  String.length(x) + tl + tr) t

let tf_opt_concat (t: string option tree):string = 
  tfold (fun x -> match x with
                  | None -> ""
                  | Some x -> x) (fun x tl tr -> match x with
                                                | None -> ""^ tl^tr 
                                                | Some x -> x ^ tl^tr) t



(*Part D *)

type 'a btree = Empty
              | Node of 'a btree * 'a * 'a btree

let rec bt_elem_by (f:'a -> 'b -> bool) (num: 'b) (t: 'a btree) :bool =
  match t with
  | Empty -> false
  | Node(l,v,r) -> if ( f v num ) = true then true else ((bt_elem_by f num l) || (bt_elem_by f num r))
let rec bt_insert_by  (f:'a -> 'a -> int) (num:'a) (t:'a btree) :'a btree = 
  match t with
  |Empty -> Node(Empty, num, Empty)
  |Node(l, v, r) -> if ((f num v) <= 0 ) then Node(bt_insert_by f num l,v,r) else Node (l,v,bt_insert_by f num r)
let rec bt_to_list (t: 'a btree) :'a list = 
  match t with
 |Empty -> []
 |Node(l, v, r) -> (bt_to_list l) @ [v]  @ (bt_to_list r)
let rec btfold (ac: 'b) (f: 'b -> 'a -> 'b -> 'b) (t: 'a btree) :'b =
  match t with 
  |Empty -> ac
  |Node(l,v,r) -> f (btfold ac f l) v (btfold ac f r)



let btf_elem_by (f:'a -> 'b -> bool) (num :'b) (t: 'a btree) :bool = 
  btfold (false) (fun l v r -> l || (f v num) || r ) t

let btf_to_list (t: 'a btree) :'a list = 
  btfold ([]) (fun l v r -> l @ ([v]) @ r) t


(*
when we do insert_by in the binary search tree, we look for the smaller root ( or number ) 
and just want to go down by this direction. But the fold funiton is used to map a function both two sides 
until to the bottom, so we can't control it. we can't make fold function go only one direaction
*)


