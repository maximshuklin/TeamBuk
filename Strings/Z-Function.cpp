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

vector<int> get_zfunction(string s) {
	int n = (int)s.size();
	vector<int> z(n);
	int l = -1, r = -1;
	for (int i = 1; i < n; ++i) {
		int k = 0;
		if (i <= r) {
			k = min(z[i - l], r - i + 1);
		}
		while (i + k < n && s[i + k] == s[k]) {
			++k;
		}
		z[i] = k;
		
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

signed main() {
	string s;
	cin >> s;
	vector<int> z = get_zfunction(s);
	for (int i : z) {
		cout << i << ' ';
	}
	cout << '\n';
	return 0;
}
