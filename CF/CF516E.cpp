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
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, b, g;
int B[N], G[N];
int d;
vector<int> by[N], gl[N];
ll ans;

struct node
{
    ll pos, v, num;
    node() {}
    node(int _p, int _v, int _n): pos(_p), v(_v), num(_n) {};

    bool operator < (const node& a) const
    {
        if(pos != a.pos) return pos < a.pos;
        return num < a.num;
    }
}p[N];

inline ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(!b)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - y * (a / b);
    return d;
}

inline ll solve(vector<int> a, vector<int> b, ll inv, int n, int m)
{
    int cnt = 0, lim = a.size();
    if(lim == n) return -1;
    for(auto v : a) 
    {
        cnt ++;
        p[cnt] = {(ll)v * inv % n, v, cnt};
    }
    for(auto v : b)
    {
        cnt ++;
        p[cnt] = {v * inv % n, v, cnt};
    }

    sort(p + 1, p + cnt + 1);
    p[cnt + 1].pos = p[1].pos + n, p[0].pos = p[cnt].pos - n;
    ll cur = INF, res = 0;
    for(int i = 1; i <= cnt; i ++ )
        cur = min(cur + (p[i].pos - p[i - 1].pos) * m, p[i].v);
    for(int i = 1; i <= cnt; i ++ )
    {
        cur = min(cur + (p[i].pos - p[i - 1].pos) * m, p[i].v);
        if(p[i].pos == p[i + 1].pos) continue;
        if(p[i].pos + 1 == p[i + 1].pos && p[i].num <= lim) continue;
        res = max(res, cur + (p[i + 1].pos - p[i].pos - 1) * m);
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    ll X, Y;
    d = exgcd(n, m, X, Y);
    X = (X + m) % m, Y = (Y + n) % n;

    b = read();
    for(int i = 1; i <= b; i ++ ) B[i] = read();
    g = read();
    for(int i = 1; i <= g; i ++ ) G[i] = read();

    // if(n < m) 
    // {
    //     swap(n, m);
    //     swap(b, g);
    //     swap(B, G);
    // }

    if(d > b + g)
    {
        puts("-1");
        return 0;
    }

    for(int i = 1; i <= b; i ++ ) by[B[i] % d].push_back(B[i] / d);
    for(int i = 1; i <= g; i ++ ) gl[G[i] % d].push_back(G[i] / d);

    for(int i = 0; i < d; i ++ )
    {
        if(!by[i].size() && !gl[i].size()) 
        {
            puts("-1");
            return 0;
        }
        ans = max(ans, solve(by[i], gl[i], Y, n / d, m / d) * d + i);
        ans = max(ans, solve(gl[i], by[i], X, m / d, n / d) * d + i);
    }

    cout << ans << endl;

    return 0;
}
