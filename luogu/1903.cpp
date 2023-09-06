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
int a[N], pos[N];
int n, m;
struct query
{
    int op, l, r, time;
    bool operator < (const query& Q)
    {
        if(pos[l] == pos[Q.l])
        {
            if(pos[r] == pos[Q.r])
                return time < Q.time;
            return pos[r] < pos[Q.r];
        }
        return pos[l] < pos[Q.l];
    }
}q[N];

int qtt;
struct change
{
    int p, v;
}c[N];

int num[N], ans[N];
int cnt, now;
inline void add(int p)
{
    if(!num[a[p]]) cnt ++;
    num[a[p]] ++;
}

inline void sub(int p)
{
    num[a[p]] --;
    if(!num[a[p]]) cnt --;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    int _ = pow(n, 2.0 / 3.0);
    for(int i = 1; i <= n; i ++ ) 
    {
        pos[i] = (i - 1) / _;
        a[i] = read();
    }

    for(int i = 1; i <= m; i ++ )
    {
        char op[5];
        scanf("%s", op);
        if(op[0] == 'Q')
        {
            int l = read(), r = read();
            qtt ++;
            q[qtt] = {qtt, l, r, i};
        }
        else
        {
            int p = read(), v = read();
            c[i] = {p, v};
        }
    }

    sort(q + 1, q + qtt + 1);

    int L = 1, R = 0;
    for(int i = 1; i <= qtt; i ++ )
    {
        while(now < q[i].time)
        {
            now ++;
            if(c[now].p >= L && c[now].p <= R)
            {
                sub(c[now].p);
                swap(c[now].v, a[c[now].p]);
                add(c[now].p);
            }
            else if(c[now].p) swap(c[now].v, a[c[now].p]);
        }
        while(now > q[i].time)
        {
            if(c[now].p >= L && c[now].p <= R)
            {
                sub(c[now].p);
                swap(c[now].v, a[c[now].p]);
                add(c[now].p);
            }
            else if(c[now].p) swap(c[now].v, a[c[now].p]);
            now --;
        }

        while(R < q[i].r) add(++ R);
        while(L > q[i].l) add(-- L);
        while(R > q[i].r) sub(R --);
        while(L < q[i].l) sub(L ++);
        ans[q[i].op] = cnt;
    }

    for(int i = 1; i <= qtt; i ++ ) 
        printf("%d\n", ans[i]);
    
    return 0;
}
