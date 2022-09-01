// 算法用途：求字符串 s、t 的 LCS（最长公共子序列）
// 时间复杂度： O(nm/w)
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 3000;
const int M = (N - 1) / 64 + 7;

struct BITSET {
#define ull unsigned long long

    ull a[M];

    BITSET() { memset(a, 0, sizeof a); }

    bool operator [] (int x) {
        return (a[x >> 6] >> (x & 63)) & 1ull;
    }

    void set(int x = -1) {
        if (x == -1) fill(a, a + M, -1ull);
        else a[x >> 6] |= 1ull << (x & 63);
    }

    void reset(int x = -1) {
        if (x == -1) fill(a, a + M, 0);
        else a[x >> 6] &= a[x >> 6] ^ (1ull << (x & 63));
    }
 
    int count() {
        int cnt = 0;
        for (int i = 0; i < M; ++i)
            cnt += __builtin_popcountll(a[i]);
        return cnt;
    }
 
    BITSET operator & (const BITSET &B) const {
        BITSET C;
        for (int i = 0; i < M; ++i) C.a[i] = a[i] & B.a[i];
        return C;
    }

    BITSET operator ^ (const BITSET &B) const {
        BITSET C;
        for (int i = 0; i < M; ++i) C.a[i] = a[i] ^ B.a[i];
        return C;
    }
    
    BITSET operator | (const BITSET &B) const {
        BITSET C;
        for (int i = 0; i < M; ++i) C.a[i] = a[i] | B.a[i];
        return C;
    }

    BITSET operator << (const int x) const {
        BITSET C; ull lst = 0; int b = x >> 6, c = x & 63; 
        for (int i = 0; i + b < M; ++i) {
            C.a[i + b] = lst | (a[i] << c);
            if (c) lst = a[i] >> (64 - c);
        }
        return C;
    }

    BITSET operator >> (const int x) const {
        BITSET C; ull lst = 0; int b = x >> 6, c = x & 63; 
        for (int i = M - 1; i >= b; --i) {
            C.a[i - b] = lst | (a[i] >> c);
            if (c) lst = a[i] << (64 - c);
        }
        return C;
    }

    BITSET operator - (const BITSET &B) const {
        BITSET C; ull lst = 0, cur;
        for (int i = 0; i < M; ++i) {
            cur = (a[i] < B.a[i] + lst);
            C.a[i] = a[i] - lst - B.a[i];
            lst = cur;
        }
        return C;
    }
    
    BITSET operator + (const BITSET &B) const {
        BITSET C; ull lst = 0, cur;
        for (int i = 0; i < M; ++i) {
            cur = (a[i] + lst > -1 - B.a[i]);
            C.a[i] = a[i] + lst + B.a[i];
            lst = cur;
        }
        return C;
    }

#undef ull
} pos[26];

BITSET work(string s, string t) {
    int n = s.size(), m = t.size();
    BITSET f, g, h;
    for (int i = 0; i < 26; ++i) pos[i].reset();
    for (int i = 0; i < m; ++i) pos[t[i] - 'a'].set(i);
    for (int i = 0; i < n; ++i) {
        if (!pos[s[i] - 'a'].count()) continue;
        g = (f | pos[s[i] - 'a']);
        h = f << 1, h.a[0] |= 1;
        f = (((g - h) ^ g) & g);
    }
    return f;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> s >> t;
    cout << work(s, t) << endl;
}
