#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
struct node
{
    int l, r;
    int val, key, size;
}tr[N];
int root, idx;
int n, minn;
int le, cnt;
int delta;

void update(int p)
{
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

int  New(int val)
{
    tr[++ idx].val = val;
    tr[idx].key = rand();
    tr[idx].size = 1;
    return idx;
}

void split(int p, int val, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(tr[p].val <= val)
        {
            x = p;
            split(tr[p].r, val, tr[p].r, y);
        }
        else
        {
            y = p;
            split(tr[p].l, val, x, tr[p].l);
        }
        update(p);
    }
    
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(tr[x].key < tr[y].key)
    {
        tr[x].r = merge(tr[x].r, y);
        update(x);
        return x;
    }
    else
    {
        tr[y].l = merge(x, tr[y].l);
        update(y);
        return y;
    }
}

int x, y, z;
void insert(int val)
{
    split(root, val, x, y);
    root = merge(merge(x, New(val)), y);
}

int getmin()
{
    int p = root;
    while(tr[p].l) p = tr[p].l;
    return tr[p].val;
}

void del(int val)
{
    split(root, val - 1, x, y);
    split(y, val, y, z);
    y = merge(tr[y].l, tr[y].r);
    root = merge(merge(x, y), z);
}

inline int getval(int rank)
{
    int now = root;
    while(now)
    {
        if(tr[tr[now].l].size + 1 == rank) break;
        else if(tr[tr[now].l].size >= rank)
        {
            now = tr[now].l;
        }
        else
        {
            rank -= tr[tr[now].l].size + 1;
            now = tr[now].r;
        }
    }
    return tr[now].val;
}

void print()
{
    for(int i = 1; i <= idx; i ++ ) cout << tr[i].val << " ";
    puts("");
}

int main()
{
    scanf("%d%d", &n, &minn);

    while(n -- )
    {
        char op[2];
        int k;
        scanf("%s%d", op, &k);
        if(op[0] == 'I')
        {
            if(k < minn) continue;
            else k -= delta, insert(k), cnt ++;
        }
        else if(op[0] == 'A')
        {
            delta += k;
        }
        else if(op[0] == 'S')
        {
            delta -= k;
            split(root, minn - delta - 1, x, y);
            root = y;
            le += tr[x].size;
            cnt -= tr[x].size;
        }
        else
        {
            if(k > cnt) puts("-1");
            else
            {
//                cout << " delta: " << delta << endl;
//                cout << "rank: " << getval(cnt - k + 1) << endl;
//                cout << "??? " << cnt << endl;
                cout << getval(cnt - k + 1) + delta << endl;
            }
        }
//        print();
    }
    cout << le << endl;
    return 0;
}