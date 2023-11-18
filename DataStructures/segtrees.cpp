

const int INF = 2e9;
template<class T>
struct segtree_min {
    vector<T> t;
    int n;
    void build() {  // build the tree
        for (int i = n - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
    }
    segtree_min(vector<T> a) {
        n = a.size();
        t.resize(n * 2);
        rep(i, 0, n) t[i + n] = a[i];
        build();
    }
    void modify(int p, T value) {  // set value at position p
        for (t[p += n] = value; p > 1; p >>= 1) {
            if (t[p] < t[p^1]) t[p>>1] = t[p];
            else t[p>>1] = t[p^1];
        }
    }

    int query(int l, int r) {  // min on interval [l, r)
        T res = INF;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) chkmin(res, t[l++]);
            if (r&1) chkmin(res, t[--r]);
        }
        return res;
    }
};
struct segtree_max {
    vector<int> t;
    int n;
    void build() {  // build the tree
        for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
    }
    segtree_max(vector<int> a) {
        n = a.size();
        t.resize(n * 2);
        for (int i = 0; i < n; ++i) t[i + n] = a[i];
        build();
    }
    void upd(int p, int value) {  // set value at position p
        for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
    }

    int get(int l, int r) {  // sum on interval [l, r)
        int res = -INF;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) chkmax(res, t[l++]);
            if (r&1) chkmax(res, t[--r]);
        }
        return res;
    }
};
struct fenwick {
    vi tree;
    fenwick(vi a) {
        tree.resize(a.size(), 0);
        rep(i, 0, a.size()) incr(i, a[i]);
    }
    fenwick(int n) : tree(n) {}
    void incr(int i, int x) {
        for (;i < tree.size(); i |= i + 1)tree[i] += x;
    }
    int sum(int r) {
        int res = 0;
        while (r >= 0) {
            res += tree[r];
            r = (r&(r + 1)) - 1;
        }
        return res;
    }
    int get(int l, int r) { // [l, r)
        --r;
        return sum(r) - sum(l - 1);
    }
    int descend(int s) { // first index from which sum >= s
        int cur = 0;
        for (int log = 14; log >= 0; --log) {
            if ((cur + (1 << log) - 1 >= len(tree))) continue;
            if (tree[cur + (1 << log) - 1] < s) {
                s -= tree[(cur += (1 << log)) - 1];
            }
        }
        return cur;
    }
};

const int INF = 1e9;

struct segtree_min_mass_add {
    vpii tree;
    vi add;
    int n;

    void init(int v, int lv, int rv) {
        if (rv - lv == 1) {
            tree[v] = {0, lv};
            return;
        }
        int mv = (rv + lv) / 2;
        init(v * 2, lv, mv);
        init(v * 2 + 1, mv, rv);
        tree[v] = tree[v * 2];
    }

    segtree(int n) : tree(n * 4, {INF, -1}), add(n * 4), n(n) { init(1, 0, n); }

    pii get_min(int v) {
        return {tree[v].first + add[v], tree[v].second};
    }

    void push(int v) {
        add[v * 2] += add[v];
        add[v * 2 + 1] += add[v];
        add[v] = 0;
    }

    void add_on_seg(int v, int lv, int rv, int l, int r, int x) {
        if (lv >= l && rv <= r) {
            add[v] += x;
            return;
        }
        if (lv >= r || rv <= l) return;
        int mv = (rv + lv) / 2;
        push(v);
        add_on_seg(v * 2, lv, mv, l, r, x);
        add_on_seg(v * 2 + 1, mv, rv, l, r, x);
        tree[v] = min(get_min(v * 2), get_min(v * 2 + 1));
    }

    pii get_min(int v, int lv, int rv, int l, int r) {
        if (lv >= l && rv <= r) {
            return get_min(v);
        }
        if (lv >= r || rv <= l) return {INF, -1};
        int mv = (rv + lv) / 2;
        push(v);
        pii ans = get_min(v * 2, lv, mv, l, r);
        chkmin(ans, get_min(v * 2 + 1, mv, rv, l, r));
        tree[v] = min(get_min(v * 2), get_min(v * 2 + 1));
        return ans;
    }

    void add_on_seg(int l, int r, int x) {
        add_on_seg(1, 0, n, l, r, x);
    }

    pii get_min(int l, int r) {
        return get_min(1, 0, n, l, r);
    }
};

template<typename T>
struct binary_indexed_tree {
    std::vector<T> bit;

    // Fills the array with default values.
    binary_indexed_tree(int n = 0) : bit(n + 1) {}

    int size() const {
        return int(bit.size()) - 1;
    }

    // Adds delta at the position pos.
    void add(int pos, T delta) {
        for (pos++; pos < int(bit.size()); pos += pos & -pos)
            bit[pos] += delta;
    }

    // Returns sum on the interval [0, pref].
    T query(int pref) {
        T sum = T();
        for (pref++; pref > 0; pref -= pref & -pref)
            sum += bit[pref];

        return sum;
    }

    // Returns sum on the interval [l, r).
    T query(int l, int r) {
        if (r <= l)
            return T();

        T res = query(r - 1);
        res -= query(l - 1);
        return res;
    }
};

/*
 * Zero based.
 * Type T must have same restriction as for binary_indexed_tree.
 * Type T must have operator -T.
*/

template<typename T>
struct segment_adding_binary_indexed_tree {
    binary_indexed_tree<T> values;

    segment_adding_binary_indexed_tree(int n = 0) : values(n) {}

    int size() const {
        return values.size();
    }

    // Adding value on the interval [l, r).
    void add(int l, int r, T value) {
        values.add(l, value);
        values.add(r, -value);
    }

    // Returns the element on the position pos.
    T at(int pos) {
        return values.query(pos);
    }
};

/*
 * Zero based.
 * Works for signed integer types.
*/

template<typename T>
struct segment_adding_segment_query_binary_indexed_tree {
    segment_adding_binary_indexed_tree<T> k, b;

    segment_adding_segment_query_binary_indexed_tree(int n = 0) : k(n), b(n) {}

    int size() const {
        return k.size();
    }

    // Adding val on the interval [l, r).
    void upd(int l, int r, T val) {
        if (r <= l)
            return;

        b.add(l, r, -(l - 1) * val);
        b.add(r, size(), (r - l) * val);
        k.add(l, r, val);
    }

    // Returns the sum on the interval [0, pref].
    T query(int pref) {
        return b.at(pref) + pref * k.at(pref);
    }

    // Returns the sum on the interval [l, r).
    T get(int l, int r) {
        if (r <= l)
            return T();

        return query(r - 1) - query(l - 1);
    }
};
