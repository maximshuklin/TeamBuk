/*

Geometry template by Maxim Shuklin

*/
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

// #define int long long     // <--- probably needed

const double eps = 1e-7;

struct point
{
	int x, y;
	point() {}
	point( int _x, int _y ) {
		x = _x;
		y = _y;
	}
};

point operator+( const point &a, const point &b ) {
	return point( a.x + b.x, a.y + b.y );
}

point operator-( const point &a, const point &b ) {
	return point( a.x - b.x, a.y - b.y );
}

int operator*( const point &a, const point &b ) { // cross product
	return a.x * b.y - a.y * b.x;
}

int operator%( const point &a, const point &b ) { // dot product
	return a.x * b.x + a.y * b.y;
}

// dist(a, b) ^ 2
int dist2(const point &a, const point &b) {
	return (a - b) % (a - b); 
}

double dist(const point &a, const point &b) {
	return sqrt( (a - b) % (a - b) );
}

double triangle_square( point A, point B, point C) {
	return (double)abs( (B - A) * (C - A) ) / 2.0;
}

int sign( int x ) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

int sign( double x ) {
	if (x > 0 + eps) return 1;
	if (x < 0 - eps) return -1;
	return 0;
}

bool point_belong_segment(point P, point A, point B) {
	if ((P - A) * (B - A) == 0) {
		if (min(A.x, B.x) <= P.x && P.x <= max(A.x, B.x)) {
			if (min(A.y, B.y) <= P.y && P.y <= max(A.y, B.y)) {
				return 1;
			}
		}
	}
	return 0;
}

bool point_in_triangle( point P, point A, point B, point C ) {
	int s1 = (P - A) * (P - B);
	int s2 = (P - B) * (P - C);
	int s3 = (P - C) * (P - A);
	if (s1 == s2 && s2 == s3) return 1;
	// check strictly or not
	if (point_belong_segment(P, A, B) || point_belong_segment(P, B, C) || point_belong_segment(P, A, C)) return 1;
	return 0;
}

vector< point > ConvexHull(vector< point > v) {
	if (v.size() <= 3) return v;

	point O = v[0];
	for (point P : v) {
		if (P.x < O.x || (P.x == O.x && P.y < O.y)) {
			O = P;
		}
	}

	sort( v.begin(), v.end(), [&] (point A, point B) {
		return (A - O) * (B - O) < 0 || ( (A - O) * (B - O) == 0 && (A - O) % (A - O) < (B - O) % (B - O) );
	} );
	
	v.emplace_back( v[0] );

	vector< point > st;
	int sz = 0;

	for (auto P : v) {
		while (sz > 1 && (P - st[sz - 1]) * (st[sz - 1] - st[sz - 2]) <= 0) {
			st.pop_back();
			--sz;
		}
		st.emplace_back( P );
		++sz;
	}
	st.pop_back(); // to delete st[0] = st.back();
	return st;
}




signed main() {

	// perimetr and area of convex hull
	int n;
	cin >> n;

	vector< point > p(n);
	for (int i = 0; i < n; ++i) {
		cin >> p[i].x >> p[i].y;
	}

	vector< point > convex_hull = ConvexHull(p);
	convex_hull.emplace_back( convex_hull[0] );

	double Perimetr = 0;
	double Square = 0;

	for (int i = 0; i < convex_hull.size() - 1; ++i) {
		Perimetr += dist( convex_hull[i], convex_hull[i + 1] );
		Square += (convex_hull[i] * convex_hull[i + 1]);
	}
	Square /= 2.0;
	Square = abs( Square );

	// print answer

	cout << setprecision(15);
	cout << "Polygon perimetr: " << Perimetr << '\n';
	cout << "Polygon square: " << Square << '\n';

	return 0;
}
