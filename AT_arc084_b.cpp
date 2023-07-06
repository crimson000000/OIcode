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

const int N = 1e6 + 10;
int dist[N];
bool st[N];
deque<int> q;
int k;

void SPFA()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 1;
    q.push_back(1);
    
    while(q.size())
    {
        int t = q.front();
        q.pop_front();

        if(st[t]) continue;
        st[t] = true;

        int j = t * 10 % k;
        if(dist[j] > dist[t])
        {
            dist[j] = dist[t];
            q.push_front(j);
        }

        j = (t + 1) % k;
        if(dist[j] > dist[t] + 1)
        {
            dist[j] = dist[t] + 1;
            q.push_back(j);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> k;

    SPFA();

    cout << dist[0] << endl;
    
    return 0;
}
