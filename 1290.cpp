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

bool find(int a, int b, int p)
{
    if(a == b) return p;
    if(b / a >= 2) return p;
    return find(b - a, a, p ^ 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int c;
    cin >> c;
    while(c -- )
    {
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        if(!find(a, b, 0)) puts("Stan wins");
        else puts("Ollie wins");
    }
    
    return 0;
}
