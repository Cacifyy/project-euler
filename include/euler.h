// Shared header for Project Euler solutions.
// Include with: #include "euler.h"
#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i128 = __int128;

// ---------- Primes ----------

// Sieve of Eratosthenes: is_prime[i] for 0..n.
inline vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    if (n >= 1) is_prime[1] = false;
    for (ll i = 2; i * i <= n; i++)
        if (is_prime[i])
            for (ll j = i * i; j <= n; j += i) is_prime[j] = false;
    return is_prime;
}

// List of all primes <= n.
inline vector<int> primes_up_to(int n) {
    vector<bool> s = sieve(n);
    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (s[i]) primes.push_back(i);
    return primes;
}

// Trial-division primality test.
inline bool is_prime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

// Prime factorization as {prime, exponent} pairs.
inline vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> f;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p) continue;
        int e = 0;
        while (n % p == 0) n /= p, e++;
        f.push_back({p, e});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}

// ---------- Divisors ----------

inline vector<ll> divisors(ll n) {
    vector<ll> small, large;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i) continue;
        small.push_back(i);
        if (i != n / i) large.push_back(n / i);
    }
    small.insert(small.end(), large.rbegin(), large.rend());
    return small;
}

inline ll num_divisors(ll n) {
    ll count = 1;
    for (auto [p, e] : factorize(n)) count *= e + 1;
    return count;
}

// Sum of proper divisors (excludes n itself).
inline ll sum_proper_divisors(ll n) {
    if (n <= 1) return 0;
    ll sum = 1;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i) continue;
        sum += i;
        if (i != n / i) sum += n / i;
    }
    return sum;
}

// ---------- Number theory ----------

inline ll lcm_ll(ll a, ll b) { return a / gcd(a, b) * b; }

inline ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (i128)result * base % mod;
        base = (i128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

// ---------- Digits / strings ----------

inline vector<int> digits(ll n) {
    if (n == 0) return {0};
    vector<int> d;
    while (n > 0) d.push_back(n % 10), n /= 10;
    reverse(d.begin(), d.end());
    return d;
}

inline int digit_sum(ll n) {
    int s = 0;
    while (n > 0) s += n % 10, n /= 10;
    return s;
}

inline bool is_palindrome(const string& s) {
    return equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}
inline bool is_palindrome(ll n) { return is_palindrome(to_string(n)); }

// ---------- Big integers ----------

// Minimal non-negative arbitrary-precision integer (base 1e9).
struct BigInt {
    static constexpr uint32_t BASE = 1000000000;
    vector<uint32_t> d;  // little-endian chunks

    BigInt(ull n = 0) {
        do d.push_back(n % BASE), n /= BASE; while (n > 0);
    }
    BigInt(const string& s) {
        for (int i = (int)s.size(); i > 0; i -= 9) {
            int start = max(0, i - 9);
            d.push_back(stoul(s.substr(start, i - start)));
        }
        trim();
    }

    void trim() { while (d.size() > 1 && d.back() == 0) d.pop_back(); }

    BigInt& operator+=(const BigInt& o) {
        ull carry = 0;
        for (size_t i = 0; i < max(d.size(), o.d.size()) || carry; i++) {
            if (i == d.size()) d.push_back(0);
            ull cur = d[i] + carry + (i < o.d.size() ? o.d[i] : 0);
            d[i] = cur % BASE;
            carry = cur / BASE;
        }
        return *this;
    }
    friend BigInt operator+(BigInt a, const BigInt& b) { return a += b; }

    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        vector<ull> r(a.d.size() + b.d.size(), 0);
        for (size_t i = 0; i < a.d.size(); i++) {
            ull carry = 0;
            for (size_t j = 0; j < b.d.size() || carry; j++) {
                ull cur = r[i + j] + carry + (j < b.d.size() ? (ull)a.d[i] * b.d[j] : 0);
                r[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }
        BigInt res;
        res.d.assign(r.begin(), r.end());
        res.trim();
        return res;
    }
    BigInt& operator*=(const BigInt& o) { return *this = *this * o; }

    bool operator==(const BigInt& o) const { return d == o.d; }
    bool operator<(const BigInt& o) const {
        if (d.size() != o.d.size()) return d.size() < o.d.size();
        return lexicographical_compare(d.rbegin(), d.rend(), o.d.rbegin(), o.d.rend());
    }

    string str() const {
        string s = to_string(d.back());
        char buf[10];
        for (int i = (int)d.size() - 2; i >= 0; i--) {
            snprintf(buf, sizeof buf, "%09u", d[i]);
            s += buf;
        }
        return s;
    }
    friend ostream& operator<<(ostream& os, const BigInt& b) { return os << b.str(); }
};

inline BigInt big_pow(BigInt base, ull exp) {
    BigInt result = 1;
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

inline BigInt big_factorial(int n) {
    BigInt result = 1;
    for (int i = 2; i <= n; i++) result *= BigInt(i);
    return result;
}

// ---------- Input ----------

// Read every line of a file (e.g. problem data files stored in data/).
inline vector<string> read_lines(const string& path) {
    ifstream in(path);
    vector<string> lines;
    for (string line; getline(in, line);) lines.push_back(line);
    return lines;
}
