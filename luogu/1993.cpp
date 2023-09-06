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

const int N = 1e4 + 10, M = 2 * N;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], cnt[N];
bool st[N];
int q[N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

bool spfa()
{
    int hh = 0, tt = 1;
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    st[0] = true;
    q[0] = 0;
    while(hh != tt)
    {
        int t = q[hh ++];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j] > n) return true;
                if(!st[j])
                {
                    st[j] = true;
                    q[tt ++ ] = j;
                    if(tt == N) tt = 0;
                }
            }
        }
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();

    while(m -- )
    {
        int op = read(), a = read(), b = read(), c;
        if(op == 1)
        {
            c = read();
            add(a, b, -c);
        }
        else if(op == 2)
        {
            c = read();
            add(b, a, c);
        }
        else
        {
            add(a, b, 0);
            add(b, a, 0);
        }
    }

    for(int i = 1; i <= n; i ++ ) add(0, i, 0);

    if(spfa()) puts("No");
    else puts("Yes");

    return 0;
}
