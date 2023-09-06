#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
struct node
{
    int l, r;
    int key, size, val;
}t[N];
int cnt, root, n, m, last, sum;
inline int New(int val)
{
    t[++ cnt].val = val;
    t[cnt].key = rand();
    t[cnt].size = 1;
    return cnt; 
}

inline void update(int p)
{
    t[p].size = t[t[p].l].size + t[t[p].r].size + 1;
}

void split(int p, int val, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(t[p].val <= val)
        {
            x = p;
            split(t[p].r, val, t[p].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, val, x, t[p].l);
        }
        update(p);
    }
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key < t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        update(x);
        return x;
    }
    else
    {
        t[y].l = merge(x, t[y].l);
        update(y);
        return y;
    }
}

int x, y, z;
inline void insert(int val)
{
    split(root, val, x, y);
    root = merge(merge(x, New(val)), y);
}

inline void del(int val)
{
    split(root, val, x, z);
    split(x, val - 1, x, y);
    y = merge(t[y].l, t[y].r);
    root = merge(merge(x, y), z);
}

inline int getrank(int val)
{
    split(root, val - 1, x, y);
	int res = t[x].size + 1;
    root = merge(x, y);
    return res;
}

inline int getval(int rank)
{
    int now = root;
    while(now)
    {
        if(t[t[now].l].size + 1 == rank) break;
        else if(t[t[now].l].size >= rank)
        {
            now = t[now].l;
        }
        else
        {
            rank -= t[t[now].l].size + 1;
            now = t[now].r;
        }
    }
	int res = t[now].val;
    return res;
}

inline int getpre(int val)
{
    split(root, val - 1, x, y);
    int now = x;
    while(t[now].r)
        now = t[now].r;
	int res = t[now].val;
    root = merge(x, y);
    return res;
}

inline int getnxt(int val)
{
    split(root, val, x, y);
    int now = y;
    while(t[now].l)
        now = t[now].l;
	int res = t[now].val;
    root = merge(x, y);
    return res;
}

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main()
{
    n = read(), m = read();
	for(int i = 0; i < n; i ++ ){
		int a = read();
		insert(a);
	}

    while(m -- )
    {
        int op, val;
        op = read(), val = read();
        switch(op)
        {
            case 1:
                insert(val ^ last);
                break;
            case 2:
                del(val ^ last);
                break;
            case 3:
                last = getrank(val ^ last);
                sum ^= last;
                break;
            case 4:
                last = getval(val ^ last);
                sum ^= last;
                break;
            case 5:
                last = getpre(val ^ last);
                sum ^= last;
                break;
            case 6:
                last = getnxt(val ^ last);
                sum ^= last;
                break;
        }
    }
	cout << sum << endl;
}