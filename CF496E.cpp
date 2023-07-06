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
struct seg
{
    int l, r, id;
    bool operator < (const seg& a) const
    {
        return r < a.r;
    }
}a[N];

struct peo
{
    int l, r, id;
    bool operator < (const peo& a) const
    {
        if(r != a.r) return r < a.r;
        return id < a.id;
    }
}b[N];

struct node
{
    int l, id;
    bool operator < (const node& a) const
    {
        if(l != a.l) return l < a.l;
        return id < a.id;
    } 
};

int cnt[N], ans[N];
set<node> t;
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        int l = read(), r = read();
        a[i] = {l, r, i};
    }

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int l = read(), r = read();
        cnt[i] = read();
        b[i] = {l, r, i};
    }

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);

    for(int i = 1, p = 1; i <= m; i ++ )
    {
        while(p <= n && a[p].r <= b[i].r)
            t.insert({a[p].l, a[p].id}), p ++;
        while(cnt[b[i].id])
        {
            auto it = t.lower_bound({b[i].l, 0});
            if(it == t.end()) break;
            ans[it -> id] = b[i].id, cnt[b[i].id] --;
            t.erase(it);
        }
    }

    for(int i = 1; i <= n; i ++ )
        if(!ans[i])
        {
            puts("NO");
            return 0;
        }

    puts("YES");
    for(int i = 1; i <= n; i ++ ) 
        printf("%d ", ans[i]);

    return 0;
}