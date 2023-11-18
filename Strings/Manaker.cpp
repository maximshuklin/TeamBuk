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

const int N = 100;

int odd[N], even[N];

void manaker(string s) {
	int n = (int)s.size();

	int l = -1, r = -1;

	for (int i = 0; i < n; ++i) {
		int k = 0;
		if (i <= r) {
			k = min( odd[l + r - i], r - i + 1);
		}
		while ( i + k < n && i - k >= 0 && s[i + k] == s[i - k] ) ++k;
		
		odd[i] = k;

		if (i + odd[i] - 1 > r) {
			l = i - odd[i] + 1;
			r = i + odd[i] - 1;
		}
	}

	for (int i = 0; i < n; ++i) {
		int k = 0;
		if (i <= r) {
			k = min( even[l + r - i - 1], r - i );
		}
		while ( i + k + 1 < n && i - k >= 0 && s[i + k + 1] == s[i - k] ) ++k;

		even[i] = k;

		if (i + odd[i] > r) {
			l = i - odd[i] + 1;
			r = i + odd[i];
		}
	}
}

signed main() {
	string s;
	cin >> s;
	int n = (int)s.size();
	manaker(s);
	cout << "odd : ";
	for (int i = 0; i < n; ++i) {
		cout << odd[i] << ' ';
	}
	cout << '\n';
	cout << "even : ";
	for (int i = 0; i < n; ++i) {
		cout << even[i] << ' ';
	}
	cout << '\n';
	return 0;
}

// не проверенный
