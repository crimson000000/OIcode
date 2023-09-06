#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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

const int N = 1e6 + 10, M = 1e9 + 7, P = 13331, M2 = 19260817;
const int P2 = 5119;
char s[N];
ll h1[2][N], p1[N], cnt[N];
ll h2[2][N], p2[N];
int n, q;

ll gethash1(int type, int l, int r)
{
    return ((h1[type][r] - h1[type][l - 1] * p1[cnt[r] - cnt[l - 1]]) % M + M) % M;
}

ll gethash2(int type, int l, int r)
{
    return ((h2[type][r] - h2[type][l - 1] * p2[cnt[r] - cnt[l - 1]])% M2 + M2) % M2;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    scanf("%s", s + 1);
    q = read();

    for(int i = 1; i <= n; i ++ )
    {
        h1[0][i] = h1[0][i - 1], h1[1][i] = h1[1][i - 1], cnt[i] = cnt[i - 1];
        h2[0][i] = h2[0][i - 1], h2[1][i] = h2[1][i - 1];
        
        if(s[i] == '0') 
        {
            h1[0][i] = (h1[0][i - 1] * P + 1 + (i & 1)) % M;
            h1[1][i] = (h1[1][i - 1] * P + 1 + ((i & 1) ^ 1)) % M;
            h2[0][i] = (h2[0][i - 1] * P2 + 1 + (i & 1)) % M2;
            h2[1][i] = (h2[1][i - 1] * P2 + 1 + ((i & 1) ^ 1)) % M2;
            cnt[i] ++;
        }
    }

    p1[0] = 1; p2[0] = 1;
    for(int i = 1; i <= n; i ++ ) 
    {
        p1[i] = p1[i - 1] * P % M;
        p2[i] = p2[i - 1] * P2 % M2;
    }

    while(q -- )
    {
        int l1 = read(), l2 = read(), len = read();
        ll h11 = gethash2(l1 & 1, l1, l1 + len - 1), h22 = gethash2(l2 & 1, l2, l2 + len - 1);
        ll h2 = gethash1(l2 & 1, l2, l2 + len - 1), h1 = gethash1(l1 & 1, l1, l1 + len - 1);
//        cout << h1 << " " << h2 << endl << h11 << " " << h22 << endl;
        if(h1 == h2 && h11 == h22) puts("Yes");
        else puts("No");
    }
   
    return 0;
}
