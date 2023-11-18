// ДД по неявному ключу (используется 1-нумерация)

const int MOD = 1e9 + 7;

mt19937 rnd(rand());

struct node
{
	int x, y;
	int sz;
	node *l, *r;
	node() {
		x = 0;
		y = rnd() % MOD;
		sz = 1;
		l = r = NULL;
	}
	node(int _x) {
		x = _x;
		y = rnd() % MOD;
		sz = 1;
		l = r = NULL;
	}
	node(node *v) {
		x = v->x;
		y = v->y;
		sz = v->sz;
		l = v->l;
		r = v->r;
	}
};

// get subtree size

int get_sz(node *v) {
	if (v == NULL) {
		return 0;
	}
	return v->sz;
}

// update node values

void update(node *v) {
	if (v != NULL) {
		v->sz = 1 + get_sz(v->l) + get_sz(v->r);
	}
}

void split(node *v, int x, node *&l, node *&r) {
	if (v == NULL) {
		l = r = NULL;
		return ;
	}
	if (1 + get_sz(v->l) <= x) {
		l = v;
		split(v->r, x - 1 - get_sz(v->l), l->r, r);
		update(l);
	} else {
		r = v;
		split(v->l, x, l, r->l);
		update(r);
	}
}

node* merge(node *l, node *r) {
	if (l == NULL) return r;
	if (r == NULL) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		update(l);
		return l;
	}
	r->l = merge(l, r->l);
	update(r);
	return r;
}
// insert element x after position pos
void insert(node *&v, int pos, int x) {
	node *L;
	node *R;
	split(v, pos, L, R);
	v = merge(L, merge(new node(x), R));
}
// erase element on position pos
void erase(node *&v, int pos) {
	node *L, *BAD, *R;
	split(v, pos, L, R);
	split(L, pos - 1, L, BAD);
	v = merge(L, R);
}
void print_tree(node *v) {
	if (v != NULL) {
		print_tree(v->l);
		cout << (v->x) << ' ';
		print_tree(v->r);
	}
}
void print(node *v) {
	print_tree(v);
	cout << '\n';
}
signed main() {
	int n, m;
	cin >> n >> m;
	
	node *T = NULL;

	for (int i = 1; i <= n; ++i) {
		T = merge(T, new node(i));
	}

	while(m--) {
		int l, r;
		cin >> l >> r;
		
		node *L, *M, *R;

		split(T, r, L, R);
		split(L, l - 1, L, M);
		T = merge(M, merge(L, R));

	}
	print(T);
	return 0;
}

