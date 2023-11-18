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

// not checked yet

namespace SCC
{
	const int N = 100;

	int n, m;
	vector<int> g[N], gt[N];
	vector<int> gr[N];
	int comp[N];
	bool used[N];

	vector< pair<int, int> > edges;

	void AddEdge(int u, int v) {
		g[u].emplace_back(v);
		gt[v].emplace_back(u);

		edges.emplace_back( u, v );
	}

	vector<int> order;

	void dfs1(int v) {
		used[v] = 1;
		for (int to : g[v]) {
			if (!used[to]) {
				dfs1(to);
			}
		}
		order.emplace_back(v);
	}

	void dfs2(int v, int num_comp) {
		comp[v] = num_comp;
		for (int to : gt[v]) {
			if (!comp[to]) {
				dfs2(to, num_comp);
			}
		}
	}

	void GET_SCC() {
		for (int i = 1; i <= n; ++i) used[i] = 0;
		for (int i = 1; i <= n; ++i) {
			if (!used[i]) {
				dfs1(i);
			}
		}
		reverse(order.begin(), order.end());
		int num_comp = 0;
		for (int v : order) {
			if (!comp[v]) {
				dfs2(v, ++num_comp);
			}
		}
		map< pair<int, int> , bool > was;
		for (auto e : edges) {
			int u = e.first;
			int v = e.second;
			if (comp[u] != comp[v]) {
				if (!was.count({comp[u], comp[v]})) {
					gr[comp[u]].emplace_back(comp[v]);
				}
			}
		}
	}
};


signed main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
	}
	return 0;
}

