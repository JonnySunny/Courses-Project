### Feedback for Lab 11

Run on April 23, 10:24:27 AM.

#### Total score: _0_ / _20_

+ Pass: Change into directory "Lab_11".

+ Pass: Check that file "interpreter.ml" exists.

+ Fail: Check that an OCaml file "interpreter.ml" has no syntax or type errors.

    OCaml file interpreter.ml has errors.

    Run "ocaml interpreter.ml" to see them.

    Make sure that you are using ocaml version 4.02.3.  Run "ocaml -version" to check the version number.  Check the specification from Lab 5 again if you are still having problems with this.

+ Skip: 
Check that the result of evaluating
   ```
   num_sums
   ```
   matches the pattern `11`.

   


  This test was not run because of an earlier failing test.

+ Skip: 
Check that the result of evaluating
   ```
   val_sum_evens
   ```
   matches the pattern `56`.

   


  This test was not run because of an earlier failing test.

+ Skip: 
Check that the result of evaluating
   ```
   val_sum_odds
   ```
   matches the pattern `49`.

   


  This test was not run because of an earlier failing test.

+ Skip: 
Check that the result of evaluating
   ```
   num_sum_evens
   ```
   matches the pattern `9`.

   


  This test was not run because of an earlier failing test.

+ Skip: 
Check that the result of evaluating
   ```
   num_sum_odds
   ```
   matches the pattern `8`.

   


  This test was not run because of an earlier failing test.

+ Skip: 
Check that the result of evaluating
   ```
   lookup "sum_evens" (exec program_3_test [])
   ```
   matches the pattern `Int 30`.

   


  This test was not run because of an earlier failing test.

+ Skip: 
Check that the result of evaluating
   ```
   lookup "y" (exec program_4 [("x",Int 4)])
   ```
   matches the pattern `Int 6`.

   


  This test was not run because of an earlier failing test.

