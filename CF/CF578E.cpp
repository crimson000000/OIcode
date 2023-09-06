#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
char s[N];
int n;
vector<int> v[N], a[2][2], id[2];
int idcnt;

inline void change()
{
    if(!a[1][1].empty() || !a[1][0].empty()) return;
    if(a[0][0].empty() || a[0][1].empty()) return;
    int x = a[0][0].back(), y = a[0][1].back();
    if(v[x].back() > v[y].back())
    {
        v[y].push_back(v[x].back()), v[x].pop_back();
    }
    else
    {
        v[x].push_back(v[y].back()), v[y].pop_back();
    }

    a[0][0].pop_back(), a[0][1].pop_back();
    a[1][0].push_back(y), a[1][1].push_back(x);
}

inline void print(int x)
{
    for(auto a : v[x]) printf("%d ", a);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    for(int i = 1; i <= n; i ++ )
    {
        int c = s[i] == 'R';
        if(id[c ^ 1].empty()) id[c ^ 1].push_back(++ idcnt);
        int t = id[c ^ 1].back();
        v[t].push_back(i), id[c ^ 1].pop_back(), id[c].push_back(t);
    }

    printf("%d\n", idcnt - 1);

    for(int i = 1; i <= idcnt; i ++ )
        a[v[i].size() & 1][s[v[i].back()] == 'R'].push_back(i);
    
    change();

    int t = (a[1][0].size() != a[1][1].size()) ? 
        a[1][0].size() < a[1][1].size() : a[0][1].size() < a[0][0].size();

    while(!a[0][t ^ 1].empty())
        print(a[0][t ^ 1].back()), a[0][t ^ 1].pop_back();

    while(a[1][t].size())
    {
        print(a[1][t].back()), a[1][t].pop_back();
        while(!a[0][t].empty()) print(a[0][t].back()), a[0][t].pop_back();
        t ^= 1;
    }
    
    return 0;
}