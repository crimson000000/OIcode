#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
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

const int N = 1e6 + 10;
struct peo
{
    ll a, b, d;
    bool operator < (const peo& t) const
    {
        if(d != t.d) return d < t.d;
        if(d < 0) return a < t.a;
        else return b > t.b;
    }
}p[N];
ll c[N], sum;
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        n = read();
        memset(p, 0, sizeof p);
        memset(c, 0, sizeof c);
        sum = 0;
        for(int i = 1; i <= n; i ++ )
        {
            p[i].a = read(), p[i].b = read();
            if(p[i].a < p[i].b) p[i].d = -1;
            else if(p[i].a == p[i].b) p[i].d = 0;
            else p[i].d = 1;
        }

        sort(p + 1, p + 1 + n);
        c[1] = p[1].a + p[1].b;
        sum += p[1].a;
        for(int i = 2; i <= n; i ++ )
        {
            sum += p[i].a;
            c[i] = max(c[i - 1], sum) + p[i].b;
        }
        cout << c[n] << endl;
    }

    return 0;
}