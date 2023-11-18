/*
▄███████▀▀▀▀▀▀███████▄
░▐████▀▒ЗАПУСКАЕМ▒▀██████▄
░███▀▒▒▒▒▒ДЯДЮ▒▒▒▒▒▒▀█████
░▐██▒▒▒▒▒▒БОГДАНА▒▒▒▒▒████▌
░▐█▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▌
░░█▒▄▀▀▀▀▀▄▒▒▄▀▀▀▀▀▄▒▐███▌
░░░▐░░░▄▄░░▌▐░░░▄▄░░▌▐███▌
░▄▀▌░░░▀▀░░▌▐░░░▀▀░░▌▒▀▒█▌
░▌▒▀▄░░░░▄▀▒▒▀▄░░░▄▀▒▒▄▀▒▌
░▀▄▐▒▀▀▀▀▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒█
░░░▀▌▒▄██▄▄▄▄████▄▒▒▒▒█▀
░░░░▄██████████████▒▒▐▌
░░░▀███▀▀████▀█████▀▒▌
░░░░░▌▒▒▒▄▒▒▒▄▒▒▒▒▒▒▐
░░░░░▌▒▒▒▒▀▀▀▒▒▒▒▒▒▒▐
 
*/
#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <cmath>
#include <bitset>
#include <cassert>
#include <queue>
#include <stack>
#include <deque>
#include <cassert>
#include <iomanip>
#include <random>


using namespace std;

#define ll long long
#define ld double
#define null NULL
#define prev prev228
#define index index228
#define left left228
#define right right228
#define hash hash228
#define y1 y1228
#define y0 y0228
#define firn(i, n) for (int i = 0; i < (int)n; ++i)
#define forn(i, n) for (int i = 1; i <= (int)n; ++i)
#define double long double
#define time time228
#define int long long

template<typename T> inline void uin(T &a, T b) {
    if (b < a) a = b;
}

template<typename T> inline void uax(T &a, T b) {
    if (b > a) a = b;
}


const int inf = 1e9 + 228;


struct line
{
    int k, b;
    line() {}
    line(int _k, int _b) {
        k = _k;
        b = _b;
    }

    int get(int x) {
        return k * x + b;
    }
};


line null_line = line(0, 0);



struct LiChaoTree
{
    struct node
    {
        line ln;
        int l, r;
        node() {
            l = r = 0;
        }
    };

    vector< node > d;

    void build(int l, int r, int v = 1) {
        d[v].l = l;
        d[v].r = r;
        d[v].ln = null_line;
        if (l == r) return ;
        int m = (l + r) >> 1;
        build(l, m, v << 1);
        build(m + 1, r, v << 1 | 1);
    }

    LiChaoTree(int low, int hig) {
        d.resize(4 * (hig - low + 1) + 7);
        build(low, hig);
    }

    void add(line l, int v = 1) {
        int m = (d[v].l + d[v].r) >> 1;
        if (l.get(m) > d[v].ln.get(m)) {
            swap(d[v].ln, l);
        }
        if (d[v].l == d[v].r) return ;
        if (l.get(d[v].l) > d[v].ln.get(d[v].l)) {
            add(l, v << 1);
        } else {
            add(l, v << 1 | 1);
        }
    }

    int get(int x, int v = 1) {
        if (d[v].l == d[v].r) {
            return d[v].ln.get(x);
        }
        int cur = d[v].ln.get(x);
        int m = (d[v].l + d[v].r) >> 1;
        if (x <= m) {
            uax(cur, get(x, v << 1));
        } else {
            uax(cur, get(x, v << 1 | 1));
        }
        return cur;
    }
};




// dp[i] = dp[j] + (sum[j+1...i]) * i - t;

signed main() {
    ios_base::sync_with_stdio(false);
    return 0;
}



// kek








