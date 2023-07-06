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

#define ls(u) ((u) << 1)
#define rs(u) (((u) << 1) + 1)

const int N = 1e6 + 10;
int p[N];
int n;
map<PII, int> mp;

int find(int u, int v, int pre)
{
    if(u > n) return pre;
    if(mp.find({u, v}) != mp.end()) return mp[{u, v}];
    int &b = p[ls(u)], &c = p[rs(u)], &w = mp[{u, v}];
    if(v < min(b, c))
    {
        w = u;
        return u;
    }
    if(b < c)
    {
        return w = find(ls(u), v, u);
    }
    else if(b < v)
    {
        int lans = find(ls(u), b, u);
        int rans = find(rs(u), b, u);
        if(lans > rans)
        {
            return w = find(ls(u), v, u);
        }
        else return w = find(rs(u), v, u);
    }
    else
    {
        return w = min(find(ls(u), v, u), find(rs(u), v, u));
    }
}

void solve(int u)
{
    if(u > n) return;
    int &a = p[u], &b = p[ls(u)], &c = p[rs(u)];
    if(a < min(b, c))
    {
        solve(ls(u));
        solve(rs(u));
        return;
    }
    if(b < c)
    {
        swap(a, b);
        solve(ls(u));
        solve(rs(u));
        return;
    }
    swap(a, c);
    if(b > c) swap(b, c);
    if(find(ls(u), b, ls(u)) > find(rs(u), b, rs(u))) swap(b, c);
    solve(ls(u));
    solve(rs(u));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) p[i] = read();

    for(int i = n + 1; i <= n * 2 + 1; i ++ ) p[i] = n + 1;

    solve(1);
    for(int i = 1; i <= n; i ++ ) printf("%d ", p[i]);

    return 0;
}