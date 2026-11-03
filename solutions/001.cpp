// Problem 1: Multiples of 3 or 5
// https://projecteuler.net/problem=1
// Find the sum of all the multiples of 3 or 5 below 1000
#include "euler.h"

int main() {
    ll answer = 0;

    for (ll i = 0; i < 1000; i++) {
        if ((i % 3) == 0 || (i % 5) == 0) {
            answer += i;
        }
    }

    cout << answer << endl;
}
