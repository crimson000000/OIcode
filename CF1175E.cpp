#include <bits/stdc++.h>
using namespace std;
const int N = 6e5 + 10;
int f[N][23], a[N];
int n, m;
int rmax;

int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; i ++ )
    {
        int l, r;
        cin >> l >> r;
        rmax = max(r, rmax);
        a[l] = max(a[l], r);
    }
    for(int i = 0; i <= rmax; i ++ ) a[i] = max(a[i], a[i - 1]);
    for(int i = 0; i <= rmax; i ++ ) f[i][0] = a[i];

    for(int t = 1; t < 21; t ++ )
        for(int i = 0; i <= rmax; i ++ )
            f[i][t] = f[f[i][t - 1]][t - 1];

    while(m -- )
    {
        int x, y;
        int ans = 0;
        cin >> x >> y;
        for(int t = 20; t >= 0; t -- )
            if(f[x][t] < y)
                x = f[x][t], ans += (1 << t);
        
        if(f[x][0] >= y) cout << ans + 1 << endl;
        else puts("-1");
    }
    return 0;
}