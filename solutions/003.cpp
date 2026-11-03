// Problem 3: Largest Prime Factor
// https://projecteuler.net/problem=3
// What is the largest prime factor of the number 600851475143?
#include "euler.h"

ll n = 600851475143;
// ll n = 35;

int main() {
    ll lpf = 0; // largest prime factor

    // 1, n = 35, i = 1
    // 5, n = 35, i = 5, lpf = 5, n -> 7
    // 6, n = 7, i = 6
    for (ll i = 1; i <= n; i++) {
        if ((n % i) == 0) {
            lpf = i;
            n = n / i;
        }
    }

    cout << lpf << endl;
}
