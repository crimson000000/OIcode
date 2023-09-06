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

const int N = 1000 + 10;
char s[N][N], t[N];
bitset<N> f;
int n, m;

struct node
{
    int l, r, id;
    bool operator < (const node& a) 
    {
        if(l != a.l) return l < a.l;
        if(r != a.r) return r < a.r;
        return id < a.id;
    }
}pre[N];

map<int, node> mp;

int get(char *s, int l, int r)
{
    int res = 0;
    for(int i = l; i <= r; i ++ )
        res = res * 131 + s[i];
    return res;
}

void get(char *s, int id)
{
    int len = strlen(s + 1);
    for(int i = 1; i <= len; i ++ )
    {
        int l = i, r = i + 1;
        if(r <= len) 
        {
            mp[get(s, l, r)] = {l, r, id};
            // cout << get(s, l, r) << endl;
        }
        r = i + 2;
        if(r <= len) 
        {
            mp[get(s, l, r)] = {l, r, id};
            // cout << get(s, l, r) << endl;
        }
    }
}

stack<node> stk;
void dfs(int now)
{
    if(now == 0) return;
    stk.push(pre[now]);
    dfs(now - (pre[now].r - pre[now].l + 1));
}

void solve()
{
    n = read(), m = read();
    f.reset();
    mp.clear();

    for(int i = 1; i <= n; i ++ ) scanf("%s", s[i] + 1);
    scanf("%s", t + 1);

    for(int i = 1; i <= n; i ++ ) get(s[i], i);

    f[0] = true;
    for(int i = 2; i <= m; i ++ )
    {
        int x = get(t, i - 1, i);
        if(mp[x].id && f[i - 2]) 
        {
            f[i] = f[i - 2];
            // cout << x << endl;
            pre[i] = mp[x];
        }
        if(i >= 3)
        {
            x = get(t, i - 2, i);
            if(mp[x].id && f[i - 3])
            {
                f[i] = f[i - 3];
                pre[i] = mp[x];
            }
        }
    }

    if(!f[m]) puts("-1");
    else
    {
        dfs(m);
        printf("%d\n", (int)stk.size());
        while(stk.size())
        {
            printf("%d %d %d\n", stk.top().l, stk.top().r, stk.top().id);
            stk.pop();
        }
    }
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