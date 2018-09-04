### Assessment for Lab 15

#### Total score: _10_ / _15_

Run on May 10, 14:47:38 PM.

+ Pass: Change into directory "Lab_15".

+ Pass: Check that file "src/translate.ml" exists.

+  _5_ / _5_ : Pass: Check that the result of executing build.sh on `examples/mapseq.src.txt` matches the pattern `Returned \[2, 4, 6, 8\]`.

   



+  _5_ / _5_ : Pass: Check that the result of executing build.sh on `examples/map.src.txt` matches the pattern `Returned \[2, 4, 6, 8\]`.

   



+  _0_ / _5_ : Fail: Check that the result of executing build.sh on `examples/fold.src.txt` matches the pattern `Returned 16`.

   

   Your solution evaluated incorrectly and produced some part of the following:

 
   ```
[1;36mBuilding OCaml code...[0m
Finished, 0 targets (0 cached) in 00:00:00.[K
00:00:00 1    (1   ) src/main.ml.depends                           * O----D-- |[K00:00:00 10   (10  ) src/src_lang.cmo                              * O-B--D-- |[KFinished, 28 targets (28 cached) in 00:00:00.[K
[1;36mCompiling...[0m
[1;34mfunction add(x : int, y : int) =
	(x + y);
function sum_array(arr : int[]) =
	fold(add, arr);
function process(arr : int[]) =
	sum_array(arr);
process([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1])[0m
[1;32mCompiled![0m
[1;36mBuilding C code...[0m
[1;36mRunning C code...[0m
[1;32mReturned 0.[0m

real	0m0.002s
user	0m0.000s
sys	0m0.000s

   ```



