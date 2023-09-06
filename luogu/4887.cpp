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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e5 + 10, M = 20010;
int a[N], t[N], pos[N], pre[N];
ll ans[N];
int n, m, k;

struct query
{
    int op, l, r;
    ll ans;
    bool operator < (const query& q) const
    {
        if(pos[l] == pos[q.l]) return r < q.r;
        return l < q.l;
    }
}q[N];

struct query2
{
    int l, r, id;
};

vector<query2> v[N];
vector<int> buf;
int L = 1, R = 0;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();

    if(k > 14)
    {
        for(int i = 1; i <= m; i ++ ) puts("0");
        return 0;
    }

    int _ = sqrt(n);
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        pos[i] = (i - 1) / _ + 1;
    }

    for(int i = 1; i <= m; i ++ )
    {
        int l = read(), r = read();
        q[i] = {i, l, r, 0};
    }

    for(int i = 0; i < 16384; i ++ ) 
        if(__builtin_popcount(i) == k)
            buf.push_back(i);
    
    for(int i = 1; i <= n; i ++ )
    {
        for(auto x : buf) t[a[i] ^ x] ++;
        pre[i] = t[a[i + 1]];
    }

    sort(q + 1, q + 1 + m);

    memset(t, 0, sizeof t);

    for(int i = 1; i <= m; i ++ )
    {
        int l = q[i].l, r = q[i].r;
        if(R < r) v[L - 1].push_back({R + 1, r, -i});
        while(R < r) {q[i].ans += pre[R]; R ++ ;}
        if(L > l) v[R].push_back({l, L - 1, i});
        while(L > l) {q[i].ans -= pre[L - 2]; L --;}
        if(R > r) v[L - 1].push_back({r + 1, R, i});
        while(R > r) {q[i].ans -= pre[R - 1]; R --;}
        if(L < l) v[R].push_back({L, l - 1, -i});
        while(L < l) {q[i].ans += pre[L - 1]; L ++;}
    }

    for(int i = 1; i <= n; i ++ )
    {
        for(auto x : buf) t[x ^ a[i]] ++;
        for(auto x : v[i])
        {
            int l = x.l, r = x.r, id = x.id;
            for(int j = l; j <= r; j ++ )
            {
                int tmp = t[a[j]];
                if(j <= i && k == 0) tmp --;
                if(id < 0) q[-id].ans -= tmp;
                else q[id].ans += tmp;
            }
        }
    } 

    for(int i = 1; i <= m; i ++ ) q[i].ans += q[i - 1].ans;
    for(int i = 1; i <= m; i ++ ) ans[q[i].op] = q[i].ans;
    for(int i = 1; i <= m; i ++ ) printf("%lld\n", ans[i]);
    
    return 0;
}
