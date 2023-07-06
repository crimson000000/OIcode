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

const int N = 510;

struct Int
{
    vector<int> a;
    inline void push_back(int x) {a.push_back(x);}
    inline int size() {return a.size();}
    inline void pop_back() {a.pop_back();}
    
    Int() {a.clear();}
    Int(int x)
    {
        while(x) a.push_back(x % 10), x /= 10;
    }

    int operator [] (int x) 
    {
        return a[x];
    }

    Int operator + (Int b) const
    {
        Int c;
        int t = 0;
        for(int i = 0; i < a.size() || i < b.size(); i ++ )
        {
            if(i < a.size()) t += a[i];
            if(i < b.size()) t += b[i];
            c.push_back(t % 10);
            t /= 10;
        }
        if(t) c.push_back(1);
        return c;
    }

    Int operator * (int x) const
    {
        Int c;
        int t = 0;
        for(int i = 0; i < a.size() || t; i ++ )
        {
            if(i < a.size()) t += a[i] * x;
            c.push_back(t % 10);
            t /= 10;
        }
        return c;
    }

    void print()
    {
        for(int i = a.size() - 1; i >= 0; i -- ) printf("%d", a[i]);
        puts("");
    }
};

Int f[N][N];
int n, k;
int m[N], w[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) m[i] = read();
    for(int i = 1; i <= n; i ++ ) w[i] = read();

    sort(m + 1, m + n + 1);
    sort(w + 1, w + n + 1);

    f[0][0].push_back(1);
    
    for(int i = 1; i <= n; i ++ )
    {
        if(m[i] >= w[i])
        {
            int K = 0;
            for(int j = 1; j <= i; j ++ )
                if(m[j] >= w[i])
                    K ++;
            for(int j = 0; j <= i; j ++ )
                f[i][j] = f[i][j] + f[i - 1][j] * (j + K);
            for(int j = 1; j <= i - K; j ++ )
                f[i][j] = f[i][j] + f[i - 1][j - 1] * (i - j - K + 1);
        }
        else
        {
            int K = 0;
            for(int j = 1; j < i; j ++ )
                if(m[i] < w[j])
                    K ++;
            for(int j = 1; j <= i; j ++ )
                f[i][j] = f[i][j] + f[i - 1][j - 1] * (i - j + K + 1);
            for(int j = K + 1; j <= i; j ++ )
                f[i][j] = f[i][j] + f[i - 1][j] * (j - K);
        }
    }

    Int ans(0);
    for(int i = 0; i <= k; i ++ )
        ans = ans + f[n][i];
    
    ans.print();

    return 0;
}
