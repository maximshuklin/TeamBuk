const double pi = acos(-1.0);

struct comp
{
    double r, i;
    comp() {}
    comp(double _r, double _i) {
        r = _r;
        i = _i;
    }
    comp(double x) {
        r = x;
        i = 0;

    }
};

comp operator+(const comp &a, const comp &b) {
    return comp(a.r + b.r, a.i + b.i);
}

comp operator-(const comp &a, const comp &b) {
    return comp(a.r - b.r, a.i - b.i);
}

comp operator*(const comp &a, const comp &b) {
    return comp(a.r * b.r - a.i * b.i, a.i * b.r + a.r * b.i);
}

comp operator/(const comp &a, double x) {
    return comp(a.r / x, a.i / x);
}

const int maxn = 1000 * 1000;

int rv[maxn];

void fft(vector<comp> &a, bool inv) {
    int n = (int)a.size();
    for (int i = 0; i < n; ++i) {
        if (i < rv[i]) {
            swap(a[i], a[rv[i]]);
        }
    }
    comp w, wn;
    double angle = 2.0 * pi;
    for (int len = 2; len <= n; len <<= 1) {
        angle /= 2.0;
        if (inv) angle = -angle;
        wn = comp(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            w = comp(1);
            for (int j = 0; j < (len >> 1); ++j) {
                comp u = a[i + j], v = a[i + j + (len >> 1)] * w;
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
                w = w * wn;
            }
        }
        if (inv) angle = -angle;
    }
    if (inv) {
        for (int i = 0; i < n; ++i) {
            a[i] = a[i] / (double)n;
        }
    }
}

void pre(int n) {
    int lg = 0;
    while ((1 << lg) < n) ++lg;
    for (int i = 0; i < n; ++i) {
        int x = 0;
        for (int j = 0; j < lg; ++j) {
            if ((i >> j) & 1) {
                x += 1 << (lg - j - 1);
            }
        }
        rv[i] = x;
    }
}

vector<int> mult(vector<int> A, vector<int> B) {

    vector< comp > a, b;
    for (int i : A) {
        a.push_back(comp(i));
    }
    for (int i : B) {
        b.push_back(comp(i));
    }
    int n = 1;
    while (n < max((int)a.size(), (int)b.size())) n <<= 1;
    n <<= 1;
    pre(n);
    a.resize(n);
    b.resize(n);
    fft(a, 0);
    fft(b, 0);
    vector< comp > c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] * b[i];
    }
    fft(c, 1);
    vector<int> C(n);
    for (int i = 0; i < n; ++i) {
        C[i] = (int)(c[i].r + 0.5);
    }
    return C;
}

