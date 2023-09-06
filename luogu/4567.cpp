/*#define LOCAL
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

const int N = 3e6 + 10;
struct node
{
    int l, r;
    char ch;
    int key, siz;
    bool rev;
}t[N];
int root, cnt, cur;

inline int New(char ch)
{
    t[++ cnt].ch = ch;
    t[cnt].key = rand();
    t[cnt].siz = 1;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

inline void reverse(int p)
{
    swap(t[p].l, t[p].r);
    t[p].rev ^= 1;
}

inline void pushdown(int p)
{
    if(t[p].rev)
    {
        if(t[p].l) reverse(t[p].l);
        if(t[p].r) reverse(t[p].r);
        t[p].rev = 0;
    }
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key > t[y].key)
    {
        pushdown(x);
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        pushdown(y);
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

void split(int p, int siz, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        pushdown(p);
        if(t[t[p].l].siz + 1 <= siz)
        {
            x = p;
            split(t[p].r, siz - t[t[p].l].siz - 1, t[x].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, siz, x, t[y].l);
        }
        pushup(p);
    }
}

char ins[N];
int build(int l, int r)
{
    if(l == r) return New(ins[l]);
    int mid = l + r >> 1;
    int x = merge(build(l, mid), build(mid + 1, r));
    return x;
}

int x, y, z;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int n = read();
    while(n -- )
    {
        char op[50];
        scanf("%s", op);
        if(op[0] == 'M')
        {
            int k = read();
            cur = k;
        }
        else if(op[0] == 'I')
        {
            int len = read();
            if(len == 0) continue;
            for(int i = 1; i <= len; i ++ )
            {
                char ch = getchar();
                if(ch < 32 || ch > 126) 
                {
                    i --;
                    continue;
                }
                ins[i] = ch;
            }
            split(root, cur, x, y);
            root = merge(merge(x, build(1, len)), y);
        }
        else if(op[0] == 'D')
        {
            int len = read();
            split(root, cur, x, y);
            split(y, len, y, z);
            root = merge(x, z);
        }
        else if(op[0] == 'R')
        {
            int len = read();
            split(root, cur, x, y);
            split(y, len, y, z);
            reverse(y);
            root = merge(merge(x, y), z);
        }
        else if(op[0] == 'G')
        {
            split(root, cur, x, y);
            split(y, 1, y, z);
            putchar(t[y].ch);
            puts("");
            root = merge(merge(x, y), z);
        }
        else if(op[0] == 'P')
        {
            cur --;
        }
        else
        {
            cur ++;
        }
    }
    
    return 0;
}
*/

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

vector<char> t;
int cur;
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    while(n -- )
    {
        char op[50];
        scanf("%s", op);
        if(op[0] == 'M')
        {
            int k = read();
            cur = k;
        }
        else if(op[0] == 'I')
        {
            int len = read();
            vector<char> tmp;
            tmp.clear();
            tmp.resize(len);
            for(int i = 0; i < len; i ++ )
            {
                tmp[i] = getchar();
            }
            t.insert(t.begin() + cur, tmp.begin(), tmp.end());
        }
        else if(op[0] == 'D')
        {
            int len = read();
            t.erase(t.begin() + cur, t.begin() + cur + len);
        }
        else if(op[0] == 'R')
        {
            int len = read();
            reverse(t.begin() + cur, t.begin() + cur + len);
        }
        else if(op[0] == 'G')
        {
            putchar(t[cur]);
            if(t[cur] != '\n') 
                puts("");
        }
        else if(op[0] == 'P')
        {
            cur --;
        }
        else
        {
            cur ++;
        }
    }
    
    return 0;
}
