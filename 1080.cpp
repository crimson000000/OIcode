#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef __int128 ll;
typedef pair<int, int> PII;

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

void write(ll x)
{
    if(!x) return;
    write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 1e6 + 10;
const int P = 998244353, G = 3, Gi = 332748118;

int rev[N];
inline void calc(int lim, int len)
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

int qmi(int a, int k, int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (ll)res * a % p;
        a = (ll)a * a % p;
        k >>= 1;
    }
    return res;
}

struct Int
{
    vector<int> a;

    Int() 
    {
        a.clear();
    }

    Int(int x)
    {
        while(x) a.push_back(x % 10), x /= 10;
    }

    int operator [] (int x)
    {
        return a[x];
    }

    inline int size()
    {
        return a.size();
    }

    inline void push_back(int x)
    {
        a.push_back(x);
    }

    inline void print()
    {
        for(int i = a.size() - 1; i >= 0; i -- ) printf("%d", a[i]);
        puts("");
    }
};

Int operator + (Int a, Int b)
{
    Int c;
    c.a.clear();
    int t = 0;
    for(int i = 0; i < a.a.size() || i < b.a.size(); i ++ )
    {
        if(i < a.size()) t += a[i];
        if(i < b.size()) t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    if(t) c.push_back(t);
    return c;
}

Int operator * (Int a, int b)
{
    Int c;
    int t = 0;
    for(int i = 0; i < a.size() || t; i ++ )
    {
        if(i < a.size()) t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}

Int operator / (Int a, int b)
{
    Int c;
    c.a.clear();
    int t = 0;
    for(int i = a.size() - 1; i >= 0; i -- )
    {
        t = t * 10 + a[i];
        c.push_back(t / b);
        t %= b;
    }
    reverse(c.a.begin(), c.a.end());
    while(c.size() > 1 && c.a.back() == 0) c.a.pop_back();
    return c; 
}

bool operator < (Int a, Int b)
{
    if(a.size() != b.size()) return a.size() < b.size();
    for(int i = a.size() - 1; i >= 0; i -- )
        if(a[i] != b[i])
            return a[i] < b[i];
    return false;
}

Int ans, t;
int n;
struct peo
{
    int a, b;
    bool operator < (const peo &u) const
    {
        return a * b < u.a * u.b;
    }
}p[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 0; i <= n; i ++ )
    {
        cin >> p[i].a >> p[i].b;
    }

    sort(p + 1, p + 1 + n);
    t = Int(p[0].a);

    for(int i = 1; i <= n; i ++ )
    {
        ans = max(ans, t / p[i].b);
        t = t * p[i].a;
    }

    ans.print();

    return 0;
}
