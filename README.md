# Project Euler

My solutions in C++.

```
include/euler.h   shared header: std includes + helpers (primes, divisors, digits, BigInt, ...)
template.cpp      starting point for a new problem
solutions/        one file per problem: 001.cpp, 002.cpp, ...
data/             input files some problems need (e.g. names.txt)
```

## Workflow

```sh
./new.sh 1    # create solutions/001.cpp from the template
./run.sh 1    # compile (C++20, -O2) and run it, with timing
```
