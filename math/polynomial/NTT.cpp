#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

using Poly = vector<int>;

const int _ = (1 << 21) + 7;
const int P = 998244353;

int mod(const int &x) { return x + (x >> 31 & P); }

int pw(int a, int p) {
    int res = 1;
    while (p) {
        if (p & 1) res = 1ll * res * a % P;
        a = 1ll * a * a % P; p >>= 1;
    }
    return res;
}

namespace POLY {
    int tot, invt, w[2][_], num[_];

    void Init(int n) {
        tot = 1; while (tot < n + n) tot <<= 1; invt = pw(tot, P - 2);
        for (int i = 0; i < tot; ++i) num[i] = (num[i >> 1] >> 1) | (i & 1 ? tot >> 1 : 0);
        for (int i = 1, g, ig; i < tot; i <<= 1) {
            w[0][i] = w[1][i] = 1, g = pw(3, (P - 1) / (i << 1)), ig = pw(g, P - 2);
            for (int j = 1; j < i; ++j) {
                w[0][i + j] = 1ll * w[0][i + j - 1] * g % P;
                w[1][i + j] = 1ll * w[1][i + j - 1] * ig % P;
            }
        }
    }

    void NTT(Poly &f, bool ty) {
        f.resize(tot);
        for (int i = 0; i < tot; ++i) if (i < num[i]) swap(f[i], f[num[i]]);
        for (int i = 1, tmp; i < tot; i <<= 1)
            for (int j = 0; j < tot; j += i << 1)
                for (int k = 0; k < i; ++k) {
                    tmp = 1ll * w[ty][k + i] * f[j + k + i] % P;
                    f[j + k + i] = mod(f[j + k] - tmp), f[j + k] = mod(f[j + k] + tmp - P);
                }
        if (ty) for (int i = 0; i < tot; ++i) f[i] = 1ll * f[i] * invt % P;
    }
}

int n, m;
Poly f, g;

int gi() {
    int x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + c - '0', c = getchar();
    return x;
}

int main() {
    n = gi(), m = gi(); ++n, ++m; POLY::Init(max(n, m)); f.resize(n), g.resize(m);
    for (int i = 0; i < n; ++i) f[i] = gi();
    for (int i = 0; i < m; ++i) g[i] = gi();
    POLY::NTT(f, 0), POLY::NTT(g, 0);
    for (int i = 0; i < POLY::tot; ++i) f[i] = 1ll * f[i] * g[i] % P;
    POLY::NTT(f, 1);
    for (int i = 0; i < n + m - 1; ++i) printf("%d ", f[i]);
    putchar('\n');
    return 0;
}
