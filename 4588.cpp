#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct segment{
    int l, r;
    ll sum;
}t[N * 4];
int n, mod, T;

void pushup(int p){
    t[p].sum = t[p << 1].sum * t[p << 1 | 1].sum % mod;
}

void build(int p, int l, int r){
    t[p].l = l, t[p].r = r;
    if(l == r){
        t[p].sum = 1;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void change(int p, int x, ll val){
    if(t[p].l == x && t[p].r == x){
        t[p].sum = val;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(x <= mid) change(p << 1, x, val);
    else change(p << 1 | 1, x, val);
    pushup(p);
}

int main(){
    scanf("%d", &T);
    while(T -- ){
        memset(t, 0, sizeof t);
        scanf("%d%d", &n, &mod);
        int op, m;
        build(1, 1, n);
        for(int i = 1; i <= n; i ++ ){
            scanf("%d%d", &op, &m);
            if(op == 1){
                change(1, i, m);
                cout << t[1].sum % mod << endl;
            }else{
                change(1, m, 1);
                cout << t[1].sum % mod << endl;
        }
        }
        
    }
}

/*#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll x = 1;
int t, q;
vector<int> act;
ll mod;

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}

ll inv(ll x, ll mod){
    ll a, b;
    exgcd(x, mod, a, b);
    return (a % mod + mod) % mod;
}

int main(){
    scanf("%d", &t);
    while(t -- ){
        x = 1;
        scanf("%d%lld", &q, &mod);
        int op, m;
        for(int i = 0; i < q; i ++ ){
            scanf("%d%d", &op, &m);
            if(op == 1){
                x = x * m % mod;
                cout << x % mod << endl;
                act.push_back(m);
            }
            else{
                x = x * inv(act[m - 1], mod) % mod;
                cout << x % mod << endl;
                act.push_back(114514);
            }
        }
    }
}*/