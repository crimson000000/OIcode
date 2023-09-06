#include <bits/stdc++.h>
using namespace std;
bool st[100000000];

int zip(int x[])
{
    int ans = 0;
    for(int i = 1; i <= 8; i ++ )
        ans = ans * 10 + x[i];
    return ans;
}

struct point
{
    int dist;
    int state[10];
    int pre;
}q[1000010];

void dfs(int cur)
{
    if(cur != 1) dfs(q[cur].pre);
    printf("%d %d %d\n%d %d %d\n%d %d %d\n\n", q[cur].state[1]
        , q[cur].state[2], q[cur].state[3], q[cur].state[4]
        , q[cur].state[5], q[cur].state[6], q[cur].state[7]
        , q[cur].state[8], q[cur].state[9]);
}

int main()
{
    for(int i = 1; i <= 9; i ++ )
        cin >> q[1].state[i];
    q[1].dist = 0;
    int hh = 1, tt = 1;
    while(hh <= tt)
    {
        if(zip(q[hh].state) == 1234567) 
        {
            cout << q[hh].dist << endl;
            dfs(hh);
            return 0;
        }

        auto t = q[hh];
        q[++ tt] = t;
        q[tt].pre = hh;
        q[tt].dist ++; 
        swap(q[tt].state[7], q[tt].state[4]);
        swap(q[tt].state[8], q[tt].state[7]);
        swap(q[tt].state[9], q[tt].state[8]);
        swap(q[tt].state[6], q[tt].state[9]);
        swap(q[tt].state[3], q[tt].state[6]);
        swap(q[tt].state[2], q[tt].state[3]);
        swap(q[tt].state[1], q[tt].state[2]);
        int sta = zip(q[tt].state);
        if(st[sta])
            tt --;
        st[sta] = true;

        q[++ tt] = t;
        q[tt].pre = hh;
        q[tt].dist ++;
        swap(q[tt].state[6], q[tt].state[5]);
        swap(q[tt].state[5], q[tt].state[4]);
        sta = zip(q[tt].state);
        if(st[sta])
            tt --;
        st[sta] = true;

        hh ++;
    }
    puts("UNSOLVABLE");

    return 0;
}
