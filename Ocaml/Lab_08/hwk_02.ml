(* Place part 1 functions 'take', 'drop', 'length', 'rev',
   'is_elem_by', 'is_elem', 'dedup', and 'split_by' here. *)

(*Zhongyi Sun, Jonathan Lipovetz, Xingzhe Xin*)
(* Talked three functions : split_by, is_elem_by, convert_to_non_blank_lines_of_words *)

let rec take n l = match l with
  | [] -> []
  | x::xs -> if n > 0 then [x] @ take (n-1) xs else []

let rec drop n l = match l with
  | [] -> []
  | x::xs -> if n > 0 then drop (n-1) xs else l


let length lst =
        let inc a b = a + 1
        in
        List.fold_left inc 0 lst

let rev lst =
        let f x y = [y] @ x in
        List.fold_left f [] lst


let is_elem_by f n l =
        match  List.filter (fun x ->  f x n ) l with
        | [] -> false
        | _ -> true
(* Different from Xingzhe Xin
 let f2 accu x = f arg [] accu in
List.fold_left f2 false lst
*)




let is_elem n = is_elem_by (=) n

(* This help func is to add elements if they are not in the accm list *)
let deduphelp n l =
        if is_elem_by (=)  n l  then l
        else l @ [n]
let dedup l =
        List.fold_right deduphelp l []


(* this split_by function which uses a turple, left n1 is to check the element whihch is in seperate list and right n2 is to keep the result
but the order is reverse and also in the n1 part, it will count one more time after the first [] shows up
*)
let split_by (f: 'a -> 'b -> bool) (l1: 'a list) (l2: 'b list) : 'a list list =
    let splithelper (n1, n2) x = if (is_elem_by f x l2) then ([], [n1]@n2) else (n1@[x], n2) in
    match List.fold_left splithelper ([],[]) l1 with
    |(n1,n2) -> let result = [n1] @ n2 in (* if last element is not in l2, should add it into result*)
    rev(result)
(*concise this function from Jonathan Lipovetz
 let split_by (f: 'a -> 'b -> bool) (l1: 'a list) (l2: 'b list) : 'a list list =
    let fold_fun x ( l1, l2 ) =
        if (is_elem_by f x s ) then ([],l1,l2)
        else(x::l1,l2)
    in
    let (a,b) = list.fold_right ( fold_fun ) l ([][])
    in a :: b
*)


(*part 2 *)
(* Some functions for reading files. *)
let read_file (filename:string) : char list option =
  let rec read_chars channel sofar =
    try
      let ch = input_char channel
      in read_chars channel ([ch] @ sofar)
    with
    | _ -> sofar
  in
  try
    let channel = open_in filename
    in
    let chars_in_reverse = read_chars channel []
    in Some (rev chars_in_reverse)
  with
    _ -> None

type word = char list
type line = word list

let convert_lowercase file =
  let f x = Char.lowercase x in
  List.map f file

let convert_file file =
  match read_file (file) with
  | Some p -> convert_lowercase p
  | None -> []

let to_newlines (pa:char list) :line = split_by (=) pa ['\n']

let to_words (line:line) :word list list=
    let  wordshelper word  =  split_by (=) word [' ';'.';',';'!';';';':';'?';'-';'/';'<';'>']
    in List.map wordshelper line

let remove_empty (line:line):line =
  let remove x y = if y = [] then x
                  else x @ y
  in
  List.map (List.fold_right remove [])line



let convert_to_non_blank_lines_of_words (tex:char list) :line list =

    let l  = List.filter (fun x -> (x=[[]])=false) (to_words (remove_empty (to_newlines tex)))
    in
    List.map (List.filter (fun x -> (x <> []))) l (* concise the condition after talking about it, also we learned different method and ideas from each*)
(* Part 3 *)
type result = OK
      | FileNotFound of string
      | IncorrectNumLines of int
      | IncorrectLines of (int * int) list
      | IncorrectLastStanza
let compare (line1:char list) (line2:char list) =
    if line1 = line2 then 0
    else if line1 > line2 then 1
    else -1

(*List.map (fun a->(Char.lowercase a)) *)


let concise poem = (convert_to_non_blank_lines_of_words poem)
(* check part of duplication and return the list of turple if somethings go wrong*)
let comparisonsOflines12 poem=
    if ((take 1 (concise poem)) <> (take 1 (drop 1 (concise poem)))) then [(1,2)] else []

let comparisonsOflines34 poem =
    if (take 1 (drop 2 (concise poem))) <>  (take 1 (drop 3 (concise poem))) then [(3,4)] else []

let comparisonsOflines78 poem =
    if (take 1 (drop 6 (concise poem))) <>  (take 1 (drop 7 (concise poem))) then [(7,8)] else []

let comparisonsOflines910 poem =
    if (take 1 (drop 8 (concise poem))) <>  (take 1 (drop 9 (concise poem))) then [(9,10)] else []

let comparisonsOflines1314 poem=
    if (take 1 (drop 12 (concise poem))) <> (take 1 (drop 13 (concise poem))) then [(13,14)] else []

let comparisonsOflines1516 poem=
    if (take 1 (drop 14 (concise poem))) <> (take 1 (drop 15 (concise poem))) then [(15,16)] else []

(* check part of NOT duplication but in the same pagraph the frenquence should be same *)
let comparisonsIIOflines1356_firstparagraph  poem =  (* should compare between 123 and 56 *)
    let fir = List.sort compare (List.concat(dedup (take 4 (concise poem))))
    in
    let sec = List.sort compare ((List.concat(take 2 (drop 4 (concise poem)))))
    in
    if fir <> sec then [(5,6)] else []
let comparisonsIIOflines791112_secondpagraph poem   =
    let fir = List.sort compare ((List.concat(dedup (take 4 (drop 6 (concise poem))))))
    in
    let sec = List.sort compare ((List.concat(take 2 (drop 10 (concise poem)))))
    in  if fir <>  sec then [(11,12)] else []
let comparisonsIIOflines13151718  poem =
    let fir = List.sort compare ((List.concat(dedup (take 4 (drop 12 (concise poem))))))
    in
    let sec = List.sort compare ((List.concat(take 2 (drop 16 (concise poem)))))
    in
    if fir <>  sec then [(17,18)] else []
(*Last Part *)
let comparisonsIIIOfLast_pragraph poem =
    let fir = List.sort compare ((List.concat((take 2 ( drop 4 (concise poem))) @ (take 2 ( drop 10 (concise poem))) @ (take 2 (drop 16 (concise poem))))))
    in
    let sec = List.sort compare ((List.concat(take 6 (drop 18 (concise poem)))))
    in
    if dedup (fir)  = dedup (sec) then true   else false


let check_FileNotFound (filename:string) :bool =
    if read_file filename = None then true
    else false

let check_IncorrectNumLines (tex:char list) :int =
    let len = length (concise tex) in
    match  len with
    | 24 -> 24
    | _ -> len

let check_IncorrectLines poem  =

    let l12 = comparisonsOflines12 poem in

    let l34  = comparisonsOflines34 poem  in

    let l1356 =  comparisonsIIOflines1356_firstparagraph  poem in

    let l78 = comparisonsOflines78 poem in

    let l910 =  comparisonsOflines910 poem in

    let l791112 = comparisonsIIOflines791112_secondpagraph  poem in

    let l1314 =  comparisonsOflines1314 poem in

    let l1516 = comparisonsOflines1516 poem in

    let l13151718 =  comparisonsIIOflines13151718 poem in

    if (l12 = [(1,2)]) then l12 @ l78 @ l910 @ l791112 @ l1314 @ l1516 @ l13151718
    else if (l34 = [(3,4)]) then l34 @ l78 @ l910 @ l791112 @ l1314 @ l1516 @ l13151718
    else if (l78 = [(7,8)]) then l78 @ l1314 @ l1516 @ l13151718
    else if  (l910 = [(9,10)] ) then l910@ l1314 @ l1516 @ l13151718
    else if (l1314 = [(13,14)]) then l1314 @  l13151718
    else if (l1516 = [(15,16)]) then l1516 @  l13151718
    else
    l12 @ l34 @ l1356 @ l78 @ l910 @ l791112 @ l1314 @ l1516 @ l13151718

  let check_IncorrectLastStanza poem :bool=
      comparisonsIIIOfLast_pragraph poem


let paradelle (filename:string) :result =
    let txt = convert_file filename in
    if check_FileNotFound filename = true then FileNotFound (filename)
    else if (check_IncorrectNumLines txt) != 24 then IncorrectNumLines (check_IncorrectNumLines txt )
    else if check_IncorrectLines txt != [] then IncorrectLines (check_IncorrectLines txt)
    else if check_IncorrectLastStanza txt = false  then IncorrectLastStanza
    else OK
