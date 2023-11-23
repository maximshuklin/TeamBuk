pair<long, long> ext_gcd(long long a, long long b) {
    if (b == 0) {
        return {1, 0};
    }
    int x, y, xx, yy;
    tie(x, y) = ext_gcd(b, a % b);
    return {y, x - (a / b) * y};
}

pair<long long, long long> diof(long long a, long long b, long long c) {
    long long t = gcd(a, b);
    if (c % t) {
        return {-1, -1};
    }
    c /= t;
    a /= t;
    b /= t;
    long long x, y;
    tie(x, y) = ext_gcd(a, b);
    x *= c;
    y *= c;
    x %= b;
    if (x < 0) x += b;
    y = (c - a * x) / b;
    return {x, y};
}