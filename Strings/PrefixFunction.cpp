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

vector<int> get_prefix_function(string s) {
	int n = (int)s.size();
	vector<int> p(n);
	for (int i = 1; i < n; ++i) {
		int j = p[i - 1];
		while (s[i] != s[j] && j > 0) {
			j = p[j - 1];
		}
		if (s[i] == s[j]) {
			p[i] = j + 1;
		}
	}
	return p;
}

signed main() {
	string s;
	cin >> s;
	vector<int> p = get_prefix_function( s );
	for (int i : p) {
		cout << i << ' ';
	}
	cout << '\n';
	return 0;
}
