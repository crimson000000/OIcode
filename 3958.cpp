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
int n, h, r;
int s, t;
int p[N];

struct poi
{
    double x, y, z;
}q[N];

inline double dist(poi a, poi b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline void solve()
{
    n = read(), h = read(), r = read();
    s = n + 1, t = n + 2;
    for(int i = 1; i <= n + 2; i ++ ) p[i] = i;

    for(int i = 1; i <= n; i ++ )
    {
        q[i].x = read(), q[i].y = read(), q[i].z = read();
        if(q[i].z <= r) p[find(i)] = find(s);
        if(q[i].z >= (h - r)) p[find(i)] = find(t);
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = i + 1; j <= n; j ++ )
            if(dist(q[i], q[j]) <= 2 * r)
                p[find(i)] = find(j);
    
    if(find(s) == find(t)) puts("Yes");
    else puts("No");
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