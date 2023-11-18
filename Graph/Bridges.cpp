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

const int N = 100 * 1000 + 228;

int n;
vector<int> g[N];
vector< pair<int, int> > bridges;
bool used[N];
int h[N];

void addEdge(int u, int v) {
	g[u].emplace_back(v);
	g[v].emplace_back(u);
}

int up[N], tin[N], timer = 0;

void dfs(int v, int par = -1) {
	if (par == -1) h[v] = 0;
	else h[v] = h[par] + 1;

	used[v] = 1;

	up[v] = h[v];
	for (int to : g[v]) {
		if (to == par) continue;
		if (used[to]) {
			up[v] = min( up[v], h[to] );
		} else {
			dfs(to, v);
			up[v] = min( up[v], up[to] );
			
			if (up[to] > h[v]) {
				// our edge is bridge
				bridges.emplace_back( v, to );
			}
		}
	}
}

void find_bridges() {
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			dfs(i);
		}
	}
}

map< pair<int, int> , int > number;








signed main() {
	cin >> n;
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		number[make_pair( min(u, v), max(u, v) )] = i + 1;
		addEdge(u, v);
	}
	find_bridges();
	vector< int > numbers;
	cout << bridges.size() << '\n';
	for (auto e : bridges) {
		int u = e.first;
		int v = e.second;

		numbers.emplace_back( number[ make_pair( min(u, v), max(u, v) ) ] );
	}
	sort( numbers.begin(), numbers.end() );
	for (int x : numbers) {
		cout << x << ' ';
	}
	cout << '\n';
	return 0;
}
