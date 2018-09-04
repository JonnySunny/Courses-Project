### Manual Assessment for Hwk 07

#### Total score: _15_ / _15_

Run on May 10, 14:00:18 PM.

+ Pass: Change into directory "Hwk_07".

+ Pass: Check that file "hwk_07.ml" exists.

+  _5_ / _5_ : Pass: Signatures for Integer and Complex numbers conform to the rubric's requirements.

    

+  _5_ / _5_ : Pass: Naming for signatures, modules, functors, and functor args are appropriate. See rubric.

    

If the comment above refers to numbered issues, they follow:

 - (1). the functor for constructing vector modules must not have an argument whose name is "vec" or "vector" or anything like that.  It should be something like "element" or even "value".  It should not be "endpoint" or something more appropriate for an interval. (1 points)
- (2). the signature for the module constructed by this functor must be something that indicates that it is producing a vector. (1 point)
- (3). the name for the type in this signature for the vector type must be "t" (1 point)
- (4). the signature for the arithmetic modules that are components of vectors must have a name indicating that modules that implement it can perform arithmetic operators.  "Endpoint" should not be used, neither should "Element". (2 points)

+  _5_ / _5_ : Pass: Type for implementing vector is reasonable

    

#### Total score: _15_ / _15_

