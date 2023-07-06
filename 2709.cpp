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

const int N = 5e4 + 10;
int a[N], cnt[N];
int pos[N];
ll ans[N];
int n, m, k;
ll res;

void add(int pos)
{
    res -= (cnt[a[pos]] * cnt[a[pos]]);
    cnt[a[pos]] ++;
    res += (cnt[a[pos]] * cnt[a[pos]]);
}

void sub(int pos)
{
    res -= (cnt[a[pos]] * cnt[a[pos]]);
    cnt[a[pos]] --;
    res += (cnt[a[pos]] * cnt[a[pos]]);
}

struct Q
{
    int l, r, k;
    bool operator< (const Q &q) const
    {
        if(pos[l] == pos[q.l]) return pos[r] < pos[q.r];
        else return pos[l] < pos[q.l];
    }
}q[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();

    int siz = sqrt(n);

    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        pos[i] = i / siz;
    }

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
