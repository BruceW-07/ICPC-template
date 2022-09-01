#include <cstdio>
#include <iostream>

using namespace std;

class NUMBER {
#define ll long long

private:

    const int test_time = 9;

    ll qPow(ll a, ll x, ll P) {
        ll res = 1;
        while (x) {
            if (x & 1) res = (__int128)res * a % P;
            a = (__int128)a * a % P, x >>= 1;
        }
        return res;
    }

    ll gcd(ll a, ll b) {
        ll c;
        while (b) c = a, a = b, b = c % b;
        return a;
    }

public:

    bool millerRabin(ll n) {
        if (n < 3 or n % 2 == 0) return n == 2;
        ll a = n - 1; int b = 0;
        while (!(a & 1)) a >>= 1, ++b;
        for (int i = 1, j; i <= test_time; ++i) {
            ll x = rand() % (n - 2) + 2, v = qPow(x, a, n);
            if (v == 1) continue;
            for (j = 1; j <= b; ++j) {
                if (v == n - 1) break;
                v = (__int128)v * v % n;
            }
            if (j > b) return 0;
        }
        return 1;
    }

    ll pollardRho(ll x) {
        ll res = x;
        while (res == x) {
            ll s = 0, t = 0;
            ll c = (ll)rand() % (x - 1) + 1, val = 1;
            for (int goal = 1; ; goal <<= 1, s = t, val = 1) {
                for (int step = 1; step <= goal; ++step) {
                    t = ((__int128)t * t + c) % x;
                    val = (__int128)val * abs(t - s) % x;
                    if ((step % 127) == 0) {
                        ll d = gcd(val, x);
                        if (d > 1) { res = d; break; }
                    }
                }
                ll d = gcd(val, x);
                if (d > 1) { res = d; break; }
            }
        }
        return res;
    }

#undef ll 
} NUM;

#define ll long long

int T;
ll n, maxfac;

void maxFactor(ll n) {
    if (n <= maxfac or n < 2) return;
    if (NUM.millerRabin(n)) {
        maxfac = n;
        return;
    }
    ll x = NUM.pollardRho(n);
    while (n % x == 0) n /= x;
    maxFactor(n), maxFactor(x);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n, maxfac = 0;
        if (NUM.millerRabin(n)) cout << "Prime" << endl;
        else {
            maxFactor(n);
            cout << maxfac << endl;
        }
    }
    return 0;
}
