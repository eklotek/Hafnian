# Hafnian
Computes the hafnian of a symmetric matrix

First, set `S` to be `log2(# threads)` and `TYPE` to either `int`, `long`, `float`, or `double` as you prefer.

Second, compile with

    g++ hafnian.cpp -o hafnian -pthread -march=native -O2 -ftree-vectorize

Then, test it against the input file `sample.txt`

    ./hafnian < sample.txt

The outputs for when `TYPE` is `long` is

`TYPE`|result
---|---
`int`|-1221181918
`long`|-3634763514334
`float`|-1.95206e+12
`double`|-3.63476e+12

The result for `sample.txt` overflows with `int` and `float` types.
