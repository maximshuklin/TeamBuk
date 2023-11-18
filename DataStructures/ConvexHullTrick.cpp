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

// Convex Hull Trick on Maximum
// though not checked yet


struct ConvexHull
{
	struct Line
	{
		int k, b;
		Line() {}
		Line(int _k, int _b) {
			k = _k;
			b = _b;
		}
		
		int get(int x) {
			return k * x + b;
		}
	};

	double intersect(Line fir, Line sec) {
		if (fir.k == sec.k) return -228.0;
		return (sec.b - fir.b) / (fir.k - sec.k);
	}

	vector< Line > st;
	int sz;
	
	void AddLine(Line l) {
		while (sz > 0 && st[sz - 1].k == l.k) {
			if (st[sz - 1].b > l.b) return;
			st.pop_back();
			--sz;
		}
		while (sz > 1 && intersect(l, st[sz - 1]) <= intersect(st[sz - 1], st[sz - 2])) {
			st.pop_back();
			--sz;
		}
		st.emplace_back(l);
		++sz;
	}

	int get(int x) {
		int l = 0, r = sz - 1;
		while (r - l > 1) {
			int m = (l + r) >> 1;
			if (intersect(st[m], st[m + 1]) <= x) {
				l = m;
			} else {
				r = m;
			}
		}
		int mx = max(st[l].get(x), st[r].get(x));
		if (l - 1 >= 0) mx = max(mx, st[l - 1].get(x));
		if (r + 1 < sz) mx = max(mx, st[r + 1].get(x));
		return mx;
	}


	ConvexHull() {
		st.clear();
		sz = 0;
	}

	ConvexHull(vector< Line > v) {
		sort(v.begin(), v.end(), [&] (Line a, Line b) {
			return a.k < b.k || (a.k == b.k && a.b > b.b);
		});
		int i = 0;
		while (i < v.size()) {
			
			AddLine(v[i]);

			int j = i;
			while (j + 1 < v.size() && v[j + 1].k == v[i].k) {
				++j;
			}
			i = j + 1;
		}
	}

};

signed main() {

	return 0;
}
