let circle_area_v1 = fun d -> 3.14*.(d/.2.0)*.(d/.2.0);;


let circle_area_v2 = fun d ->
	let pi = 3.1415 in pi*.(d/. 2.0)*.(d/. 2.0);;



 let rec product xs = 
            match xs with 
            | [ ] -> 1
            | x :: rest -> x * product rest;;

let rec sum_diffs l = 
           match l with
           |x1 :: (x2::[]) -> x1 - x2
           |x1::(x2 :: rest) ->(x1-x2) + sum_diffs(x2::rest);;
let distance (x1,y1) (x2,y2) = sqrt((x1-.x2)*.(x1-.x2)+.(y1-.y2)*.(y1-.y2));;


let triangle_perimeter (x1,y1)(x2,y2)(x3,y3) = distance(x1,y1)(x2,y2)+.distance(x2,y2)(x3,y3)+.distance(x3,y3)(x1,y1);;
