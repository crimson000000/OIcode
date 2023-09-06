#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
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
const double PI = acos(-1);
struct Complex
{
    double a, b;
    Complex() {a = 0, b = 0;}
    Complex(double real, double imag): a(real), b(imag) {}

    Complex operator + (const Complex& x) const
    {
        return Complex(a + x.a, b + x.b);
    }

    Complex operator - (const Complex& x) const
    {
        return Complex(a - x.a, b - x.b);
    }

    Complex operator * (const Complex& x) const
    {
        return Complex(a * x.a - b * x.b, a * x.b + b * x.a);
    }
}A[N], B[N], C[N];

int n;
int lim = 1, len;
int rev[N];

void FFT(Complex a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        Complex wn = Complex(cos(2.0 * PI / m), opt * sin(2.0 * PI / m));
        for(int k = 0; k < lim; k += m)
        {
            Complex w = Complex(1, 0);
            for(int j = 0; j < m / 2; j ++ )
            {
                Complex t = w * a[k + j + m / 2];
                Complex u = a[k + j];
                a[k + j] = u + t;
                a[k + j + m / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if(opt == -1)
    {
        for(int i = 0; i < lim; i ++ ) a[i].a /= lim;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        cin >> A[i].a;
        C[n - i].a = A[i].a;
        B[i].a = (double)(1.0 / i / i);
    }

    while(lim <= n + n) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    
    FFT(A, 1), FFT(B, 1), FFT(C, 1);
    for(int i = 0; i < lim; i ++ ) 
        A[i] = A[i] * B[i], C[i] = C[i] * B[i];
    
    FFT(A, -1), FFT(C, -1);
    for(int i = 1; i <= n; i ++ )
        printf("%.3lf\n", A[i].a - C[n - i].a);

    return 0;
}
