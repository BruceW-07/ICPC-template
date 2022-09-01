#include <cstdio>
#include <iostream>

using namespace std;


const int N = 1e6, M = (N - 1) / 64 + 1;

struct BITSET {
#define ull unsigned long long

    ull a[M];

    bool operator [] (int x) {
        return (a[x >> 6] >> (x & 63)) & 1;
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
        BITSET C; bool lst = 0, cur;
        for (int i = 0; i < M; ++i) {
            cur = (a[i] < B.a[i] + lst);   // Notice that the expression of "a[i] - lst < B.a[i]" is WRONG
                                           // because "a[i] - lst" might overflow (they are both ull).
            C.a[i] = a[i] - lst - B.a[i];
            lst = cur;
        }
        return C;
    }
    
    BITSET operator + (const BITSET &B) const {
        BITSET C; bool lst = 0, cur;
        for (int i = 0; i < M; ++i) {
            cur = (a[i] + lst > -1 - B.a[i]);
            C.a[i] = a[i] + lst + B.a[i];
            lst = cur;
        }
        return C;
    }

#undef ull
};

int main() {
    return 0;
}
