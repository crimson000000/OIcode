#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#define A "Ashishgup"
#define F "FastestFinger"
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

ll n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) 
    {
        cin >> n;
        if(n == 1) puts("FastestFinger");
        else if(n == 2) puts("Ashishgup");
        else if(n & 1) puts("Ashishgup");
        else
        {
            vector<int> div;
            div.clear();
            int cnt2 = 0, pcnt = 0;
            for(int i = 2; i <= n / i; i ++ )
            {
                if(n % i == 0)
                {
                    while(n % i == 0)
                    {
                        if(i == 2) cnt2 ++;
                        else pcnt ++;
                        n /= i;
                    }
                }
            }
            
            if(n != 1 && n != 2) pcnt ++;
            else if(n != 1) cnt2 ++;
            // printf("%d: 2 %d  p %d\n", res, cnt2, pcnt);

            if(pcnt == 0) puts(F);
            else if(pcnt == 1)
                if(cnt2 == 1)
                    puts(F);
                else puts(A);
            else
            {
                puts(A);
            }
        }
    }
    
    return 0;
}
