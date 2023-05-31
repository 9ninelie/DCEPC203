#include <cstdio>
#include <cstdlib>
#define MAX 10000000
typedef long long ll;

// a * p mod m
ll modmul(ll a, ll b, ll M) {
	ll ret = a * b - M * ll(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
 
// a ^ b mod M
ll modex(ll a, ll p, ll m) {
    ll res = 1;
 
    while(p)
    {
        if (p & 1) res = modmul(res, a, m);
        a = modmul(a, a, m);
        p >>= 1;
    }
    return res;
}
 
bool isQuadraticResidue(ll a, ll n) {
    return modex(a, (n - 1)/2, n) == 1;
}
 
ll tonelliShanks(ll n, ll p) {
    if (!isQuadraticResidue(n, p)) {
        return -1;
    }
    ll q = p - 1;
    ll s = 0;
    while (~q & 1) {
        q >>= 1;
        s += 1;
    }
    if (s == 1) {
        ll x = modex(n, (p + 1)/4, p);
        return x;
    }
    ll z = 0;
    for (ll k = 1; k < p; ++k) {
        if (!isQuadraticResidue(k, p)) {
            z = k;
            break;
        }
    }
 
    ll c = modex(z, q, p);
    ll r = modex(n, (q + 1)/2, p);
    ll t = modex(n, q, p);
    ll m = s;
 
    while (t != 1) {
        int i = 1;
        ll x = modmul(t, t, p);
        while (x != 1) {
            x = modmul(x, x, p);
            i += 1;
        }
        ll b = modex(c, (1ll << (m - i - 1)), p);
        r = modmul(r, b, p);
        c = modmul(b, b, p);
        t = modmul(t, c, p);
        m = i;
    }
    return r;
}

#define MX 1000000
bool mark[MX];
 
bool millerRabin(ll p) {
    if (p < MX) {
        return !mark[p];
    }
 
    ll a = rand() % (p - 4) + 2;
 
    ll s = p - 1;
    while (~s & 1) s >>= 1;
    ll mod = modex(a, s, p);
 
    if (mod == 1 || mod == p - 1) return 1;
 
    s <<= 1;
    while(s != p - 1)
    {
        mod = modmul(mod, mod, p);
        if (mod == p - 1) return 1;
        s <<= 1;
    }
    return 0;
}
 
int cum[MAX];
int vis[MAX];
 
int main() {
    for (int i = 2; i * i < MX; i++)
        if (!mark[i])
            for(int j = i * i; j < MX; j += i)
                mark[j] = 1;    

    for (int i = 2; i < MX; i++) {	
        if (!mark[i]) {
            if (i % 8 == 1 || i % 8 == 7){
                int a = tonelliShanks((i + 1)/2, i);
                for(int j = i + i; j + a < MAX; j += i){
                    vis[j + a] = vis[j - a] = i;
                }
            }
        }
    }
 
    for (int i = 2; i < MAX; i++) {
        if (vis[i]) {
            cum[i + 1] = cum[i];
            continue;
        }
        if (millerRabin(1ll * 2 * i * i - 1)) {
            cum[i + 1]++;
        }
        cum[i + 1] += cum[i];
    }
 
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", cum[n]);
    }
	return 0;
}
