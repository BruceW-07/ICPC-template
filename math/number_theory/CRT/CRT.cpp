#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class CRT {
#define ll long long
#define ull unsigned long long
#define ld long double
public:
  
    static const int N = 2e6;
  
    int pri[N + 7], v[N + 7], phi[N + 7], cnt;
 
    inline ll mul(ll x, ll y, ll p) {
        ll z = (ld)x / p * y;
        ll res = (ull)x * y - (ull)z * p;
        return (res + p) % p;
    }

    ll pw(ll a, ll x, ll p) {
        ll res = 1;
        while (x) {
            if (x & 1) res = mul(res, a, p);
            a = mul(a, a, p), x >>= 1;
        }
        return res;
    }

public:

    void init(int W = N) {
        for (int i = 2; i <= W; ++i) {
            if (!v[i]) v[i] = i, pri[++cnt] = i, phi[i] = i - 1;
            for (int j = 1; j <= cnt and i * pri[j] <= W and pri[j] <= v[i]; ++j) {
                v[i * pri[j]] = pri[j];
                if (v[i] == pri[j]) phi[i * pri[j]] = phi[i] * pri[j];
                else phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            }
        }
    }
 
    ll solve(int n, vector<int> &a, vector<int> &p) {
        assert((int)a.size() >= n and (int)p.size() >= n);
        ll P = 1, res = 0; int maxp = 0;
        for (int i = 0; i < n; ++i) P *= p[i], maxp = max(maxp, p[i]);
        init(maxp);
        for (int i = 0; i < n; ++i) {
            if (p[i] == 1) continue;
            ll c = mul(P / p[i], pw(P / p[i], phi[p[i]] - 1, p[i]), P);
            res = (res + mul(a[i], c, P)) % P;
        }
        return res;
    }

#undef ll
#undef ull
#undef ld
} CRT;

int n;
vector<int> a, b;

int main() {
    ios::sync_with_stdio(0);
    cin >> n; a.resize(n), b.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    long long ans = CRT.solve(n, b, a);
    cout << ans << endl;
    return 0;
}
