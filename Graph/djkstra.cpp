const int N = 1e5 + 20;
vector<pair<int, int>> g[N];
int le[N];
int ri[N];
int ans[N];
int dist[N];
int h[N];
int pos_in_heap[N];

auto dijkstra = [&](int st) {
        for (int i = l; i < r; ++i) dist[i] = INF;
        dbg(st, l);
        dist[st] = 0;
        h[1] = st;
        pos_in_heap[st] = 1;
        int pp = 1;
        pos_in_heap[st] = 1;
        for (int i = l; i < r; ++i) {
            if (i != st) {
                pos_in_heap[i] = pp + 1;
                h[pp + 1] = i;
                ++pp;
            }
        }
        for (int iter = 0; iter < r - l; ++iter) {
            int v = h[1];
            {
                int cur_v = 1;
                while ((cur_v << 1) <= pp) {
                    if ((cur_v << 1) + 1 > pp || dist[h[cur_v << 1]] < dist[h[(cur_v << 1) + 1]]) {
                        h[cur_v] = h[cur_v << 1];
                        pos_in_heap[h[cur_v]] = cur_v;
                        
                        cur_v <<= 1;
                    } else {
                        h[cur_v] = h[(cur_v << 1) + 1];
                        pos_in_heap[h[cur_v]] = cur_v;
                        cur_v = (cur_v << 1) + 1;
                    }
                }
                h[cur_v] = N - 1;
            }
            if (dist[v] == INF) break;
            for (auto [u, c] : g[v]) {
                if (u < l || u >= r) continue;
                if (dist[u] > dist[v] + c) {
                    dist[u] = dist[v] + c;
                    int cur_v = pos_in_heap[u];
                    while (cur_v > 1 && dist[h[cur_v >> 1]] > dist[h[cur_v]]) {
                        swap(h[cur_v >> 1], h[cur_v]);
                        pos_in_heap[h[cur_v]] = (cur_v);
                        pos_in_heap[h[cur_v >> 1]] = (cur_v >> 1);
                        cur_v >>= 1;
                    }
                }
            }
        }
    };
