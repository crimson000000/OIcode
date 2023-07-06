#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
int ans[1145141], now[1919810];
ll a, b;
int dep;

ll gcd(int a, int b)
{
    return b? gcd(b, a % b): a;
}

void yuefen(ll& a, ll &b)
{
    ll g = gcd(a, b);
    a /= g, b /= g;
}

bool dfs(ll depth, ll mol, ll den)
{
    if(depth == dep + 1)
    {
        if(mol != 0) return false;
        if(now[dep] < ans[dep])
        {
            for(int i = 1; i <= dep; i ++ )
                ans[i] = now[i];
        }
        return true;
    }   
    bool flag = false;
    for(int i = max(now[depth - 1] + 1, (int)ceil(den / mol));
        i <= ceil(den / mol * (dep - depth + 1)); i ++ )
    {
        now[depth] = i;
        ll dx = mol * i - den, dy = den * i;
        yuefen(dx, dy);
        if(dfs(depth + 1, dx, dy))
            flag = true;
    }
    return flag;
}

signed main()
{
    cin >> a >> b;
    yuefen(a, b);
    for(dep = 1;; dep ++ )
    {
        ans[dep] = 0x3f3f3f3f;
        if(dfs(1, a, b)) break;
    }
    for(int i = 1; i <= dep; i ++ )
        printf("%d ", ans[i]);
    return 0;
}