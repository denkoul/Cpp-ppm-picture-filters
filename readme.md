# C++ .ppm picture filters
University C++ project. The assignment is in Greek and can be found [here](CPP2017_Assignment2_GR.pdf).

## Supported filters
|Filter Name (class name)|Filter ID|Parameters|
|--|--|--|
|FilterLinear|linear|aR aG aB cR cG cB|
|FilterGamma|gamma|g|
|FilterBlur|blur|N|
|FilterLaplace|laplace|NULL|

## How to run the program
1. Run cmd on the folder the .exe is located (Release folder).
2. On cmd enter the following: filter -f [Filter ID #1][Parameters] ... -f[Filter ID #k][Parameters][filename]  
(example: > filter -f gamma 2.0 -f gamma 0.5 image01.ppm)

*Notice: This is a Visual Studio Project. I recommend opening it using the .sln file.*
