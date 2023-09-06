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

const int N = 3e5 + 10;
const int f[] = {1, 1, 2, 2};
int n;
vector<int> d;
int mp[5];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        memset(mp, 0, sizeof mp);
        d.clear();
        n = read();

        for(int i = 0; i < n; i ++ )
        {
            int x = read();
            x --;
            if(i && f[d.back()] == f[x])
            {
                if(f[x] == x) d.back() = x;
            }
            else d.push_back(x);
        }

        if(f[d[0]] == f[d.back()]) 
        {
            if(f[d[0]] == d.back()) d[0] = d.back();
            d.pop_back();
        }

        for(auto i : d) mp[i] ++;
        if(mp[2] > mp[0] && mp[1] > mp[3]) puts("Yes");
        else puts("No");
    }

    return 0;
}