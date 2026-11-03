// Problem 0: Registration
// https://projecteuler.net/register
// Among the first 433 thousand square numbers, what is the sum of all the odd squares?
#include "euler.h"

int main() {

    ll answer = 0;
    for (ll i = 0; i < 433000; i++) {
        ll square = i * i;
        if ((square % 2) != 0) {
            answer += square;
        }
    }

    cout << answer << endl;
}
