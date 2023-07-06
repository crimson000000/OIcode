#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

ll T;

ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while (k)
    {
        if (k & 1)
            res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

ll inv(ll a, ll p)
{
    return qmi(a, p - 2, p);
}

ll gcd(ll a, ll b)
{
    if(!b) return a;
    return gcd(b, a % b);
}

unordered_map<ll, ll> h;
ll bsgs(ll a, ll b, ll p)
{
    h.clear();
    b %= p;
    if (a % p == 0 && b)
    {
        return -114514;
    }

    ll t = ceil(sqrt(p));
    for (int i = 0, j = b; i <= t; i++)
    {
        if (h.find(j) == h.end())
            h[j] = i;
        j = j * a % p;
    }

    ll ak = qmi(a, t, p);

    for (int i = 1, j = ak; i <= t; i++)
    {
        if (h.find(j) != h.end())
        {
            return i * t - h[j];
        }
        j = j * ak % p;
    }
    return -114514;
}

/*ll BSGS(int a, int b, int p)
{
    if (b % p == 1 % p)
        return 0; // 先特判边界0
    int k = sqrt(p) + 1;
    unordered_map<ll, int> M;
    ll j = b % p;
    for (int i = 0; i <= k - 1; i++)
    {
        M[j] = i;
        j = j * a % p;
    }
    ll ak = quick_pow(a, k, p);
    j = ak;
    for (int i = 1; i <= k; i++)
    {
        if (M.count(j) != 0)
            return (ll)i * k - M[j];
        j = j * ak % p;
    }
    return -1;
}*/

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    T = read();
    while (T--)
    {
        ll p = read(), a = read(), b = read(), x1 = read(), t = read();
        if(x1 == t)
        {
            puts("1");
            continue;
        }
        if(a == 0)
        {
            if(b == t) puts("2");
            else puts("-1");
            continue;
        }
        if(a == 1)
        {
            t = ((t - x1) % p + p) % p;
            if(t % gcd(b, p))   
                puts("-1");
            else
            {
                if((t * inv(b, p) + 1) % p == 0)
                    cout << p << endl;
                else cout << (t * inv(b, p) + 1) % p << endl;
            }
            
            continue;
        }
        
        ll A = a, B = ((t - b * inv(1 - a, p) % p) % p + p) % p * qmi(((x1 - b * inv(1 - a, p) % p) % p + p) % p, p - 2, p) % p, P = p;

        ll res = bsgs(A, B, P);
        if (res == -114514)
            puts("-1");
        else
            printf("%lld\n", res + 1);
    }

    return 0;
}
