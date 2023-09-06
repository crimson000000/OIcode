#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 50;
ll a[N], b[N];
ll n, m, k, s;
map<PII, ll> f, g;
ll res;

ll fact(ll a)
{
    ll ret = 1;
    for(int i = 1; i <= a; i ++ )
    {
        if(ret > s / a) return -1;
        ret = ret * i;
    }
    return ret;
}

ll query(ll s, ll cnt)
{
    ll res = 0;
    for(int i = 0; i <= cnt; i ++ ) res += f[{s, i}];
    return res;
}

void check(int c)
{
    if(c == 1)
    {
        ll sum = 0, cnt = 0;
        for(int i = 1; i <= m; i ++ )
        {
            if(b[i] == 1)
            {
                sum += a[i];
            } 
            else if(b[i] == 2)
            {
                ll fac = fact(a[i]);
                if(fac == -1 || sum + fac > s || cnt + 1 > k) return;
                cnt ++;
                sum += fac;
            }
        }
        f[{sum, cnt}] ++, f[{sum, -1}] ++;
    }
    else
    {
        ll sum = 0, cnt = 0;
        for(int i = m + 1; i <= n; i ++ )
        {
            if(b[i] == 1)
            {
                sum += a[i];
            } 
            else if(b[i] == 2)
            {
                ll fac = fact(a[i]);
                if(fac == -1 || sum + fac > s || cnt + 1 > k) return;
                cnt ++;
                sum += fac;
            }
        }
        if(f.find({s - sum, -1}) != f.end())
            res += query(s - sum, k - cnt);
    }
}

void dfs(int now, int ed)
{
    if(now > ed)
    {
        if(ed == m) check(1);
        else check(2);
        return;
    }
    for(int i = 1; i <= 3; i ++ )
    {
        b[now] = i;
        dfs(now + 1, ed);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read(), s = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    m = n >> 1;

    dfs(1, m), dfs(m + 1, n);

    cout << res << endl;
    
    return 0;
}
