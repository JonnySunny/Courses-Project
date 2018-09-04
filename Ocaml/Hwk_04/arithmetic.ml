type expr 
  = Const of int
  | Add of  expr * expr
  | Mul of expr * expr
  | Sub of expr * expr
  | Div of expr * expr


let rec show_expr (e:expr) : string =
  match e with
  | Const x -> string_of_int(x)
  | Add (e1, e2) -> "("^(show_expr e1 )^ "+" ^(show_expr e2)^")"
  | Sub (e1, e2) -> "("^(show_expr e1 )^ "-" ^(show_expr e2)^")"
  | Mul (e1, e2) -> "("^(show_expr e1 )^ "*" ^(show_expr e2)^")"
  | Div (e1, e2) -> "("^(show_expr e1 )^ "/" ^(show_expr e2)^")"

 let rec show_pretty_expr (e:expr) : string =
  match e with
  |Const x -> string_of_int(x)
  (*Add Sub have parenthesis only some add sub behind them *)
  |Add (e1, e2) -> (show_pretty_expr e1 )^ "+" ^(match e2 with 
  					|Const x -> string_of_int(x)
  					|Add (e1, e2) -> "("^(show_pretty_expr e1 )^ "+" ^(show_pretty_expr e2)^")"
  					|Sub (e1, e2) -> "("^(show_pretty_expr e1 )^ "-" ^(show_pretty_expr e2)^")"
  					|Mul (e1, e2) -> (show_pretty_expr e1 )^ "*" ^(show_pretty_expr e2)
  					|Div (e1, e2) -> (show_pretty_expr e1 )^ "/" ^(show_pretty_expr e2))
  |Sub (e1, e2) -> (show_pretty_expr e1 )^ "-" ^(match e2 with 
  					|Const x -> string_of_int(x)
  					|Add (e1, e2) -> "("^(show_pretty_expr e1 )^ "+" ^(show_pretty_expr e2)^")"
  					|Sub (e1, e2) -> "("^(show_pretty_expr e1 )^ "-" ^(show_pretty_expr e2)^")"
  					|Mul (e1, e2) -> (show_pretty_expr e1 )^ "*" ^(show_pretty_expr e2)
  					|Div (e1, e2) -> (show_pretty_expr e1 )^ "/" ^(show_pretty_expr e2))

  (*mul div have parenthesis whatever any things behind them *)
  |Mul (e1, e2) -> (show_pretty_expr e1 )^ "*" ^ (match e2 with 
  					  |Const x -> string_of_int(x)
  					  | Add (e1, e2) -> "("^(show_pretty_expr e1 )^ "+" ^(show_pretty_expr e2)^")"
  					  | Sub (e1, e2) -> "("^(show_pretty_expr e1 )^ "-" ^(show_pretty_expr e2)^")"
  					  | Mul (e1, e2) -> "("^(show_pretty_expr e1 )^ "*" ^(show_pretty_expr e2)^")"
  					  | Div (e1, e2) -> "("^(show_pretty_expr e1 )^ "/" ^(show_pretty_expr e2)^")")
  |Div (e1, e2) -> (show_pretty_expr e1 )^ "/" ^(match e2 with 
  					  |Const x -> string_of_int(x)
  					  | Add (e1, e2) -> "("^(show_pretty_expr e1 )^ "+" ^(show_pretty_expr e2)^")"
  					  | Sub (e1, e2) -> "("^(show_pretty_expr e1 )^ "-" ^(show_pretty_expr e2)^")"
  					  | Mul (e1, e2) -> "("^(show_pretty_expr e1 )^ "*" ^(show_pretty_expr e2)^")"
  					  | Div (e1, e2) -> "("^(show_pretty_expr e1 )^ "/" ^(show_pretty_expr e2)^")")



