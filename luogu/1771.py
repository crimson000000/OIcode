import math

def C(n, m):
    return math.factorial(n) // math.factorial(m) // math.factorial(n - m)

def qmi(a, k, p):
    res = 1
    while(k):
        if k & 1:
            res = res * a % p
        a = a * a % p
        k >>= 1
    return res

if __name__ == '__main__':
    k, x = map(int, input().split())
    x = qmi(x, x, 1000)

    print(C(x - 1, k - 1))