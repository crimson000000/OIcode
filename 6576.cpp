#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int ll

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, mod = 1e9 + 7;
struct point
{
    int x, y, op;
}q[N];
int n, m, k;
ll res;

inline bool cmp1(point a, point b)
{
    if(a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

inline bool cmp2(point a, point b)
{
    if(a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

inline int calc1()
{
    sort(q + 1, q + k + 1, cmp1);
    int lastx = 0, res = 0;
    for(int l = 1, r = 0; l <= k; l = r + 1)
    {
        while(r < k && q[r + 1].x == q[l].x) r ++;
        for(int i = l; i <= r; i ++ )
        {
            int x1 = (q[i].y ^ q[l].y) & 1, x2 = (q[i].op ^ q[l].op);
            if(x1 != x2) return 0;
        }
        res += q[l].x - lastx - 1;
        lastx = q[l].x;
    }
    res += n - lastx;
    return qmi(2, res, mod);
}

inline int calc2()
{
    sort(q + 1, q + k + 1, cmp2);
    int lastx = 0, res = 0;
    for(int l = 1, r = 0; l <= k; l = r + 1)
    {
        while(r < k && q[r + 1].y == q[l].y) r ++;
        for(int i = l; i <= r; i ++ )
        {
            int x1 = (q[i].x ^ q[l].x) & 1, x2 = (q[i].op ^ q[l].op);
            if(x1 != x2) return 0;
        }
        res += q[l].y - lastx - 1;
        lastx = q[l].y;
    }
    res += m - lastx;
    return qmi(2, res, mod);
}

inline int calc3()
{
    for(int i = 1; i <= k; i ++ )
    {
        int x1 = (q[i].x ^ q[i].y ^ q[1].x ^ q[1].y) & 1;
        int x2 = (q[i].op ^ q[1].op) & 1;
        if(x1 != x2) return 0;
    }
    return 1;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    for(int i = 1; i <= k; i ++ )
    {
        char op[4];
        scanf("%s", op);
        int x = read(), y = read();
        q[i] = {x, y, (op[0] == '+' ? 1 : 0)};
    }

    res = (res + calc1()) % mod;
    res = (res + calc2()) % mod;
    res = (res - calc3() + mod) % mod;
    if(k == 0) res --;
    cout << (res % mod + mod) % mod << endl;

    return 0;
}