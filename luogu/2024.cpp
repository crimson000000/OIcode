#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
int p[N], d[N];
int n, k, cnt;

int find(int x)
{
    if(p[x] != x)
    {
        int root = find(p[x]);
        d[x] = (d[x] + d[p[x]]) % 3;
        p[x] = root;
    }
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i ++ ) p[i] = i;
    while(k -- )
    {
        int op, a, b;
        scanf("%d%d%d", &op, &a, &b);

        if(a > n || b > n || (op == 2 && a == b))
        {
            cnt ++;
            continue;
        }

        if(op == 1)
        {
            int pa = find(a), pb = find(b);
            if(pa == pb && d[a] != d[b])
            {
                cnt ++;
                continue;
            }
            if(pa != pb)
            {
                p[pa] = pb;
                d[pa] = (3 - d[a] + d[b]) % 3;
            }
        }
        else
        {
            int pa = find(a), pb = find(b);
            if(pa == pb)
            {
                int relative = (d[a] - d[b] + 3) % 3;
                if(relative != 1)
                {
                    cnt ++;
                    continue;
                }
            }
            else
            {
                p[pa] = find(b);
                d[pa] = (1 - d[a] + d[b] + 3) % 3;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}