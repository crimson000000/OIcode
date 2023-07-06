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
int fa[N], son[N], fval[N], sval[N];
int n;

inline bool update(int u)
{
    if(fval[fa[u]] < son[u])
    {
        sval[fa[u]] = fval[fa[u]];
        fval[fa[u]] = son[u];
    }
    else if(sval[fa[u]] < son[u])
    {
        sval[fa[u]] = son[u];
    }

    int ans = max(fval[fa[u]], sval[fa[u]] + 1);
    if(ans == son[fa[u]]) return false;
    son[fa[u]] = ans;
    return 1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read() + 1;
    son[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        fa[i] = read();
        son[i] = 1;
        for(int j = i; fa[j]; j = fa[j])
            if(!update(j))
                break;
        printf("%d ", fval[1]);
    }

    return 0;
}