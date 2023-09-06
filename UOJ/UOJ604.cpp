#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using ld = long double;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
struct point
{
    ld x, y;
    int id;
}q[N], tmp1[N], tmp2[N];
int n;

mt19937 rnd(time(0));

inline int rand(int l, int r)
{
    return rnd() % (r - l + 1) + l;
}

inline bool down(point a, ld k, ld b)
{
    return k * a.x + b <= a.y;
}

inline vector<int> solve(int l, int r)
{
    // if(l == r)
    // {
    //     vector<int> res;
    //     res.clear();
    //     res.push_back(q[l].id);
    //     return res;
    // }
    if(l == r - 1)
    {
        vector<int> res;
        res.clear();
        res.push_back(q[l].id);
        res.push_back(q[r].id);
        return res;
    }
    
    int p = rand(l + 1, r - 1);
    int id = q[p].id;
    ld k = (q[l].y - q[p].y) / (q[l].x - q[p].x + 1e-20);
    // cout << id << endl;
    ld b = q[l].y - k * q[l].x;
    // cout << k << ' ' << b << endl;

    int tt1 = 0, tt2 = 0;
    tmp1[++ tt1] = q[l];

    if(down(q[r], k, b))
    {
        for(int i = l + 1; i < r; i ++ )
            if(!down(q[i], k, b) && i != p) tmp1[++ tt1] = q[i];
            else if(i != p) tmp2[++ tt2] = q[i];
    }
    else
    {
        for(int i = l + 1; i < r; i ++ )
            if(down(q[i], k, b) && i != p) tmp1[++ tt1] = q[i];
            else if(i != p) tmp2[++ tt2] = q[i];
    }
    
    tmp1[++ tt1] = q[p];
    tmp2[++ tt2] = q[r];

    // for(int i = 1; i <= tt1; i ++ ) cout << tmp1[i].x << "----" << tmp1[i].y << endl;
    // for(int i = 1; i <= tt2; i ++ ) cout << tmp2[i].x << "????" << tmp2[i].y << endl;
    
    int nxt = 0;
    for(int i = 1; i <= tt1; i ++ )
    {
        if(tmp1[i].id == id) nxt = l + i - 1;
        q[i + l - 1] = tmp1[i];
    }
    
    for(int i = 1; i <= tt2; i ++ )
    {
        if(tmp2[i].id == id) nxt = l + tt1 + i - 1;
        q[i + l + tt1 - 1] = tmp2[i];
    }

    // for(int i = l; i <= r; i ++ )
    //     cout << q[i].x << ' ' << q[i].y << endl;
    
    auto a = solve(l, nxt);
    auto bb = solve(nxt, r);
    
    vector<int> res;
    res.clear();
    for(int i = 0; i < int(a.size()) - 1; i ++ ) res.emplace_back(a[i]);
    for(auto v : bb) res.emplace_back(v);
    
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        n = read();
        for(int i = 1; i <= n; i ++ )
        {
            scanf("%Lf%Lf", &q[i].x, &q[i].y);
            q[i].id = i;
        }

        auto c = solve(1, n);

        for(auto u : c) printf("%d ", u);
        puts("");
    }

    return 0;
}
