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

const int N = 1e6 + 10;

int n, m;
int a[N];
int pos[N];
int ans[N];
int cnt[N];
int res;

struct Q
{
    int l, r, k;
    bool operator < (const Q& w) const 
    {
        if(pos[l] == pos[w.l]) return pos[r] < pos[w.r];
        else return pos[l] < pos[w.l];
    }
}q[N];

void add(int p)
{
    int t = a[p];
    if(!cnt[t]) res ++;
    cnt[t] ++;
}

void sub(int p)
{
    int t = a[p];
    cnt[t] --;
    if(!cnt[t]) res --;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    int siz = sqrt(n);
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        pos[i] = i / siz;
    } 

    m = read();

    for(int i = 0; i < m; i ++ )
    {
        q[i].l = read(), q[i].r = read();
        q[i].k = i;
    }

    sort(q, q + m);

    int l = 1, r = 0;
    for(int i = 0; i < m; i ++ )
    {
        while(q[i].l < l) add(-- l);
        while(q[i].r > r) add(++ r);
        while(q[i].l > l) sub(l ++);
        while(q[i].r < r) sub(r --);
        ans[q[i].k] = res;
    }

    for(int i = 0; i < m; i ++ )
        cout << ans[i] << endl;
    
    return 0;
}
