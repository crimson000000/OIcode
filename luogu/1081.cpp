#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int long long

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

const int N = 1e5 + 10, INF = 1e10;
int f[20][N][2], da[20][N][2], db[20][N][2];
int h[N];
int s[N], x[N];
int n, m;
int x0, anss, ansl, ansr;

struct city
{
    int h, id;
    bool operator < (const city& a) const
    {
        return h < a.h;
    }
};

multiset<city> t;

void init()
{
    h[0] = INF, h[n + 1] = -INF;
    city st, ed;
    st.h = INF, st.id = 0;
    ed.h = -INF, ed.id = 0;
    t.insert(st), t.insert(st);
    t.insert(ed), t.insert(ed);

    for(int i = n; i >= 1; i -- )
    {
        int ga, gb;
        city now;
        now.h = h[i], now.id = i;
        t.insert(now);
        auto it = t.lower_bound(now);
        it --;
        int lh = (*it).h, le = (*it).id;
        it ++; it ++;
        int nh = (*it).h, ne = (*it).id;
        it --;
        if(abs(h[i] - lh) <= abs(nh - h[i]))
        {
            gb = le;
            it --, it --;
            if(abs(nh - h[i]) >= abs(h[i] - (*it).h))
                ga = (*it).id;
            else ga = ne;
        }
        else
        {
            gb = ne;
            it ++, it ++;
            if(abs((*it).h - h[i]) >= abs(h[i] - lh))
                ga = le;
            else ga = (*it).id;
        }        
        f[0][i][0] = ga, f[0][i][1] = gb;
        da[0][i][0] = abs(h[i] - h[ga]);
        db[0][i][1] = abs(h[i] - h[gb]);
    }
}

int la, lb;
inline void calc(int s, int x)
{
    la = lb = 0;
    int p = s;
    for(int i = 18; i >= 0; i -- )
    {   
        if(f[i][p][0] && la + lb + da[i][p][0] + db[i][p][0] <= x)
        {
            la += da[i][p][0];
            lb += db[i][p][0];
            p = f[i][p][0];
        }
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) h[i] = read();

    x0 = read();
    m = read();
    for(int i = 1; i <= m; i ++ ) s[i] = read(), x[i] = read();
    
    init();

    // for(int i = 1; i <= n; i ++ )
    // {
    //     printf("%d: %d %d\n", i, gb[i], ga[i]);
    // }

    for(int i = 1; i <= 18; i ++ )
        for(int j = 1; j <= n; j ++ )
            for(int k = 0; k < 2; k ++ )
            {
                if(i == 1)
                {
                    f[1][j][k] = f[0][f[0][j][k]][1 - k];
                    da[1][j][k] = da[0][j][k] + da[0][f[0][j][k]][1 - k];
                    db[1][j][k] = db[0][j][k] + db[0][f[0][j][k]][1 - k];
                }
                else
                {
                    f[i][j][k] = f[i - 1][f[i - 1][j][k]][k];
                    da[i][j][k] = da[i - 1][j][k] + da[i - 1][f[i - 1][j][k]][k];
                    db[i][j][k] = db[i - 1][j][k] + db[i - 1][f[i - 1][j][k]][k];
                }
            }

    double ans = INF * 1.0;
    int anss;
    for(int i = 1; i <= n; i ++ )
    {
        calc(i, x0);
        double nowans = (double)la / (double)lb;
        if(nowans < ans)
        {
            ans = nowans;
            anss = i;
        }
        else if(fabs(ans - nowans) < 1e-12 && h[anss] < h[i])
            anss = i;
    }

    cout << anss << endl;

    for(int i = 1; i <= m; i ++ )
    {
        calc(s[i], x[i]);
        printf("%lld %lld\n", la, lb);
    }

    return 0;
}