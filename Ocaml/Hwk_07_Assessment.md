### Assessment for Homework 07

This is the automated grading for homework 7. More grading will be done for the written components of this assignment.

Run on May 11, 11:14:46 AM.

+ Pass: Change into directory "Hwk_07".

+ Pass: Check that file "hwk_07.ml" exists.

+  _30_ / _30_ : Pass: Check that it's possible to build and execute an ocaml script using your code.
- 1/1: `Int_vector.size (Int_vector.create 10 1)` equivalent to `10`
- 3/3: `Int_vector.to_list (Int_vector.create 10 1)` equivalent to `[1;1;1;1;1;1;1;1;1;1]`
- 2/2: `Int_vector.size (Int_vector.from_list [1;2;3;4;5])` equivalent to `5`
- 3/3: `Int_vector.to_list (Int_vector.scalar_add 3 (Int_vector.from_list [1;2;3;4;5]))` equivalent to `[4; 5; 6; 7; 8]`
- 3/3: `Int_vector.to_list (Int_vector.scalar_mul 10 (Int_vector.from_list [1;2;3;4;5]))` equivalent to `[10; 20; 30; 40; 50]`
- 3/3: `Int_vector.scalar_prod (Int_vector.scalar_add 3 (Int_vector.from_list [1;2;3;4;5])) (Int_vector.scalar_mul 10 (Int_vector.from_list [1;2;3;4;5]))` equivalent to `Some 1000`
- 3/3: `(let 
                regex = (Str.regexp "^ *<< *10 *\| *1 *, *1 *, *1 *, *1 *, *1 *, *1 *, *1 *, *1 *, *1 *, *1 *,? *>> *") and 
                resu = (Int_vector.to_string (Int_vector.create 10 1)) in 
                Str.string_match regex resu 0)` equivalent to `true`
- 2/2: `(Complex_vector.size (Complex_vector.from_list [ (1.0, 2.0); (3.0, 4.0); (5.0, 6.0) ]))` equivalent to `3`
- 2/2: `(Complex_vector.to_list (Complex_vector.create 5 (1., 0.)))` equivalent to `[(1., 0.); (1., 0.); (1., 0.); (1., 0.); (1., 0.)]`
- 3/3: `(Complex_vector.to_list (Complex_vector.scalar_add (0., 4.) (Complex_vector.from_list [ (1.0, 2.0); (3.0, 4.0); (5.0, 6.0) ])))` equivalent to `[(1., 6.); (3., 8.); (5., 10.)]`
- 2/2: `(Complex_vector.scalar_prod (Complex_vector.create 3 (1.0, 0.0)) (Complex_vector.create 5 (0., 1.)))` equivalent to `None`
- 3/3: `(Complex_vector.to_list (Complex_vector.scalar_mul (3., 5.) (Complex_vector.from_list [ (1.0, 2.0); (3.0, 4.0); (5.0, 6.0) ])))` equivalent to `[(-7., 11.); (-11., 27.); (-15., 43.)]`

**Total: 30 / 30**




