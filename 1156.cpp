#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 110;
int f[N][N];
int d, n;

struct trash
{
    int t, life, h;
    bool operator < (const trash & T) const 
    {
        return t < T.t;
    }
}t[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d%d", &d, &n);

    for(int i = 1; i <= n; i ++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        t[i] = {a, b, c};
    }

    sort(t + 1, t + n + 1);
    t[0] = {0, 0, 0};

    memset(f, -0x3f, sizeof f);
    f[0][0] = 10;
    int res = 0;
    for(int i = 1; i <= n; i ++ )  
    { 
        for(int j = 0; j <= d; j ++ )
        {
            if(f[i - 1][j] < t[i].t - t[i - 1].t) continue;
            if(j + t[i].h >= d)
            {
                cout << t[i].t << endl;
                return 0;
            }
            f[i][j] = max(f[i][j], f[i - 1][j] + t[i].life - (t[i].t - t[i - 1].t));
            f[i][j + t[i].h] = max(f[i][j + t[i].h], f[i - 1][j] - (t[i].t - t[i - 1].t));
        }
        res = max(res, f[i][0] + t[i].t);
    }

    cout << res << endl;

    return 0;
}

