#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, INF = 1145141919;
int st[N], ed[N];
int sub = INF;
multiset<int> delta, f;
int n, m;

void update(int x)
{
    auto it = f.lower_bound(x);
    int now = *it - x;
    it --;
    now = min(now, x - *it);
    sub = min(sub, now);
    f.insert(x);
}

void insert(int pos, int x)
{
    delta.insert(abs(ed[pos] - x));
    if(pos != n)
    {
        delta.erase(delta.find(abs(st[pos + 1] - ed[pos])));
        delta.insert(abs(st[pos + 1] - x));
    }
    ed[pos] = x;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++ )
    {
        int a;
        scanf("%d", &a);
        st[i] = ed[i] = a;
    }

    f.insert(INF), f.insert(-INF);
    for(int i = 1; i < n; i ++ )
        delta.insert(abs(st[i + 1] - ed[i]));

    for(int i = 1; i < n; i ++ )
        update(st[i]);

    while(m -- )
    {
        char str[20];
        int pos, k;
        scanf("%s", str);
        if(str[0] == 'I')
        {
            scanf("%d%d", &pos, &k);
            insert(pos, k);
            update(k);
        }
        else if (str[4] == 'S')
        {
            cout << sub << endl;
        }
        else
        {
            cout << *delta.begin() << endl;
        }
    }
}