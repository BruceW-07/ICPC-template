class EXGCD {

public:
    
    ll exgcd(ll a, ll b, ll &x, ll &y) {
        ll x1 = 1, x2 = 0, x3 = 0, x4 = 1, tmp;
        while (b) {
            tmp = a / b;
            tie(x1, x2, x3, x4, a, b)
                = make_tuple(x3, x4, x1 - tmp * x3, x2 - tmp * x4, b, a - tmp * b);
        }
        x = x1, y = x2;
        return a;
    }

};
