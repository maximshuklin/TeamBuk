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

const int N = 1000;

int n;
vector<int> g[N];
int mt[N];
bool used[N];

void addEdge(int a, int b) {
	g[a].emplace_back( b );
}

bool kuhn(int v) {
	if (used[v]) return 0;
	used[v] = 1;
	for (int to : g[v]) {
		if (mt[to] == -1) {
			mt[to] = v;
			return 1;
		}
	}
	for (int to : g[v]) {
		if ( kuhn(mt[to]) ) {
			mt[to] = v;
			return 1;
		}
	}
	return 0;
}

int runKuhn() {
	int matching = 0;
	memset( mt, -1, sizeof mt);
	for (int i = 1; i <= n; ++i) {
		if (kuhn(i)) {
			memset(used, 0, sizeof used);
			++matching;
		}
	}
	return matching;
}




signed main() {
	scanf("%d", &n);
	string name;
	cin >> name;
	int name_size = (int)name.size();
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		int sz = (int)s.size();
		for (int fir = 0; fir < sz; ++fir) {
			for (int sec = 0; sec < name_size; ++sec) {
				if (s[fir] == name[sec]) {
					//g[i].push_back(sec + 1);
					addEdge(i, sec + 1);
				}
			}
		}
	}
	/*int mx = 0;
	for (int i = 1; i <= n; ++i) {
		if (dfs(i)) {
			memset(used, 0, sizeof(used));
			++mx;
		}
	}*/
	int mx = runKuhn();
	if (mx < name_size) {
		puts("NO");
		return 0;
	}
	puts("YES");
	for (int i = 1; i <= name_size; ++i) {
		printf("%d ", mt[i]);
	}
	printf("\n");
    return 0;
}



