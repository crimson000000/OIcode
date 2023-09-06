#define LOCAL
#include <bits/stdc++.h>
#define x first
#define y second
#define y1 yyy1
#define y2 yyy2

using namespace std;
typedef pair<double, double> PDD;

const int N = 1010, M = 1e5 + 10;
const double eps = 1e-8;

PDD p[N];
int n, m;
int path[N][N];
int a[100010][N];

int l[M], r[M], d[M], u[M], col[M], row[M], s[M], idx;
int ans[M], top;

bool cmp(double a, double b)
{
    if(fabs(a - b) < eps) return true;
    return false;
}

int _hash(int a, int b)
{
    return (a - 1) * n + b;
}

inline void init()
{
    m = n * n;
    for(int i = 0; i <= m; i ++ )
    {
        l[i] = i - 1, r[i] = i + 1; 
        u[i] = i, d[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}

inline void add(int &hh, int &tt, int x, int y)
{
    s[y] ++;
    col[idx] = y, row[idx] = x;
    l[idx] = hh, r[idx] = tt, r[hh] = idx, l[tt] = idx;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    tt = idx ++;
}

inline void remove(int p)
{
    l[r[p]] = l[p], r[l[p]] = r[p];
    for(int i = d[p]; i != p; i = d[i])
    {   
        for(int j = r[i]; j != i; j = r[j])
        {
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
    }
}

inline void resume(int p)
{
    for(int i = u[p]; i != p; i = u[i])
        for(int j = l[i]; j != i; j = l[j])
        {
            d[u[j]] = j, u[d[j]] = j;
            s[col[j]] ++;
        }
    l[r[p]] = p, r[l[p]] = p;
}

bool dfs()
{
    if(!r[0]) return true;
    int p = r[0];
    for(int i = r[0]; i; i = r[i])
        if(s[i] < s[p])
            p = i;
    remove(p);
    for(int i = d[p]; i != p; i = d[i])
    {
        ans[++ top] = row[i];
        for(int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if(dfs()) return true;
        for(int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top --;
    }
    resume(p);
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
  
    int T;
    cin >> T;

    while(T -- )
    {
        cin >> n >> m;
        for(int i = 1; i <= n; i ++ ) cin >> p[i].x >> p[i].y;
        
        memset(path, 0, sizeof path);
        for(int i = 1; i <= n; i ++ )
        {
            a[i][_hash(i, i)] = 1;
            for(int j = 1; j <= n; j ++ )
            {
                double x1 = p[i].x, y1 = p[i].y;
                double x2 = p[j].x, y2 = p[j].y;
                if(cmp(x1, x2)) continue;
                double aa = (y1 / x1 - y2 / x2) / (x1 - x2);
                double b = y1 / x1 - aa * x1;
                if(aa >= 0) continue;
                for(int k = 1; k <= n; k ++ )
                {
                    double x = p[k].x, y = p[k].y;
                    if(!cmp(aa * x * x + b * x, y)) continue;
                    a[k][_hash(i, j)] = 1;
                }
            }
        }

        init();
        for(int i = 1; i <= n; i ++ )
        {
            int hh = idx, tt = idx;
            for(int j = 1; j <= m; j ++ )
            {
                cout << a[i][j] << ' ';
                if(a[i][j]) add(hh, tt, i, j);
            }
            puts("");
        }

        dfs();
        cout << top << endl;
    }
    
    return 0;
}