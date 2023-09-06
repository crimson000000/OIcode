#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N];
int n, p, q, r, s;

int main()
{
    scanf("%d%d%d%d%d", &n, &p, &q, &r, &s);
    
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
    }

    for(int i = p, j = r; i <= q && j <= s; i ++, j ++ )
    {
        swap(a[i], a[j]);
    }
    for(int i = 1; i <= n; i ++ ) cout << a[i] << " ";
    return 0;
}