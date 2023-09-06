#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
struct ed
{
    int a, b, w;
}e[N];
int n, m;
int ans;

int fa[N];
int find(int x)
{
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

bool check(int s, int x)
{
    for(int i = 1; i <= n; i ++ ) fa[i] = i;
    for(int i = 1; i <= m; i ++ )
    {
        if((e[i].w | x) >= (x + (1ll << (s + 1)))) continue;
        if(e[i].w >> s & 1) continue;
        int a = find(e[i].a), b = find(e[i].b);
        if(a == b) continue;
        fa[a] = b;
    }

    int cnt = 0;
    for(int i = 1; i <= n; i ++ )
        if(find(i) == i)
            cnt ++;
    return cnt == 1;
}

void solve()
{
    n = read(), m = read();
    ans = 0;
    for(int i = 1; i <= m; i ++ )  
    {
        int a = read(), b = read(), c = read();
        e[i] = {a, b, c};
    }

    for(int i = 30; i >= 0; i -- )
        if(!check(i, ans))
            ans |= (1 << i);
    
    cout << ans << endl;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}