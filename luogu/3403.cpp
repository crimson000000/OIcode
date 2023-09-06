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

const int N = 2e5 + 10;
int f[N];
int h[N], e[N], ne[N], w[N], idx;
bool st[N];
ll ans;
ll he, x, y, z;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void SPFA()
{
    memset(f, 0x3f, sizeof f);
    queue<int> q;
    q.push(1);
    f[1] = 1;
    st[1] = true;

    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(f[j] > f[t] + w[i])
            {
                f[j] = f[t] + w[i];
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    cin >> he >> x >> y >> z;

    if(x == 1 || y == 1 || z == 1) 
    {
        cout << he << endl;
        return 0;
    }

    for(int i = 0; i < x; i ++ )
    {
        add(i, (i + y) % x, y);
        add(i, (i + z) % x, z);
    }

    SPFA();

    for(int i = 0; i < x; i ++ )
        if(he >= f[i])
            ans += (he - f[i]) / x + 1;

    cout << ans << endl;
    
    return 0;
}
