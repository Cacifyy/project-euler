// Problem 2: Even Fibonacci Numbers
// https://projecteuler.net/problem=2
// By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
#include "euler.h"

int main() {
    ll answer = 2; // starting with 2 from beginning of sequence.
    ll n = 1;
    ll m = 2;
    ll i = 0;
    while (i < 4000000) {
        i = m + n;
        if ((i % 2) == 0) {
            answer += i;
        }
        n = m;
        m = i;
    }

    cout << answer << endl;
}
