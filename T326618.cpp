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

const ll twelve = 100000000000;
ll x, y, z;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> y >> z;
    if(z < twelve)
    {
        cout << y + twelve - z << endl;
    }
    if(z > twelve * 10)
    {
        cout << z - 999999000000 + y << endl;
    }
    if(z >= twelve && z < twelve * 10)
    {
        z = z % 1000000;
        if(z > y)
        {
            cout << min(abs(1000000 + y - z), z - y) << endl;
        }
        else
        {
            cout << min(abs(1000000 + z - y), y - z) << endl;
        }
    }

    return 0;
}