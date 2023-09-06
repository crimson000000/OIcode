#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
namespace Maker
{
    unsigned int x0, seed;
    void init() { scanf("%u%u", &x0, &seed); }
    inline unsigned int getnum()
    {
        x0 = (x0 << 3) ^ x0;
        x0 = ((x0 >> 5) + seed) ^ x0;
        return x0;
    }
}
int n, m;
const int N = 1e5 + 10;
unsigned int f[N][21];

void ST_pre()
{
    for(int i = 20; i; i -- )
        for(int j = 1; j + (1 << i) - 1 <= n; j ++ )
        {
            f[j][i - 1] = max(f[j][i - 1], f[j][i]);
            f[j + (1 << (i - 1))][i - 1] = max(f[j + (1 << (i - 1))][i - 1], f[j][i]);
        }
}

int main()
{
    int typ;
    scanf("%d%d%d", &n, &m, &typ);
    for(int i = 1; i <= n; i ++ ) cin >> f[i][0];
    Maker::init();
    for (int i = 1; i <= m; ++i)
    {
        int l = Maker::getnum() % n + 1, r = Maker::getnum() % n + 1;
        unsigned int v = Maker::getnum();
        if (l > r)
            swap(l, r);
        if (typ == 1)
            l = 1;
        
        int k = log2(r - l + 1);
        f[l][k] = max(f[l][k], v);
        f[r - (1 << k) + 1][k] = max(f[r - (1 << k) + 1][k], v);
    }
    
    cout << "yeah" << endl;
    ST_pre();

    for(int i = 1; i <= n; i ++ ) cout << f[i][0] << ' ';
    return 0;
}
