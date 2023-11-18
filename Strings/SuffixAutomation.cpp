#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <cstring>
#include <iomanip>
#include <functional>

using namespace std;


const int N = 400 * 1000 + 228;

int p[N], suff[N], go[N][26];
int last = 0, ptr = 0;

void init() {
    p[0] = suff[0] = -1;
    last = ptr = 0;
}

int add(char CC) {
    int c = CC - 'a';
    int A = last;
    int B = ++ptr;
    p[B] = A;
    suff[B] = 0;
    while (A != -1) {
        if (!go[A][c]) {
            go[A][c] = B;
            A = suff[A];
            continue;
        }
        int C = go[A][c];
        if (p[C] == A) {
            suff[B] = C;
            break;
        }
        int D = ++ptr;
        p[D] = A;
        suff[D] = suff[C];
        suff[C] = D;
        suff[B] = D;
        for (int i = 0; i < 26; ++i) {
            go[D][i] = go[C][i];
        }
        while (A != -1 && go[A][c] == C) {
            go[A][c] = D;
            A = suff[A];
        }
        break;
    }
    return go[p[B]][c];
}

long long dp[N];
bool used[N];

long long dfs(int v) {
    if (used[v]) return dp[v];
    used[v] = 1;
    dp[v] = 1;
    for (int i = 0; i < 26; ++i) {
        if (go[v][i]) {
            dp[v] += dfs(go[v][i]);
        }
    }
    return dp[v];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    init();
    for (char c : s) {
        last = add(c);
    }
    cout << dfs(0) - 1 << '\n';
    return 0;
}
