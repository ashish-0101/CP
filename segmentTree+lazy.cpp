struct segmentTree {

        ll N;
        vll tree;


        ll neutral = 0;   // bass (dont forget to change)

        ll change(ll a, ll b) {

                return a+b;
        }

        void build(ll u, ll L, ll R, vll &v) {

                if(L == R) {

                        tree[u] =  v[L];
                } else {

                        ll M = (L + R) / 2;
                        build(u*2, L, M, v);
                        build(u*2 + 1, M+1, R, v);
                        tree[u] = change(tree[u*2], tree[u*2 + 1]);

                }
        }


        segmentTree(vll v) {

                N = v.size() - 1;
                tree.assign(4*N + 1, 0);
                build(1, 1, N, v);
        }


        ll query(ll lq, ll rq, ll u, ll L, ll R) {

                if(L > rq || R < lq) {

                        return neutral;
                } else if(L >= lq && R <= rq) {

                        return tree[u];
                } else {


                        ll M = (L + R) / 2;

                        return change(query(lq, rq, u*2, L, M), query(lq, rq, u*2 + 1, M+1, R));
                }
        }


        void update(ll idx, ll val, ll u, ll L, ll R) {

                if(L > idx || R < idx) {
                        return;
                } else if(L == R) {

                        tree[u] = val;
                        return;
                } else {

                        ll M = (L + R)/2;
                        update(idx, val, u*2, L, M);
                        update(idx, val, u*2 + 1, M+1, R);
                        tree[u] = change(tree[u*2], tree[u*2 + 1]);
                }
        }

};      


struct lazySeg {

        ll N;
        vll tree;
        vll lazy;


        ll neutral = INF;   // changeable

        ll change(ll a, ll b) {

                return min(a, b);
        }

        void build_tree(int index, int start, int end, vll &arr)
        {
                if (start == end)
                {
                        tree[index] = arr[start];
                        return;
                }
                int mid = (start + end) / 2;
                build_tree(2 * index, start, mid, arr);
                build_tree(2 * index + 1, mid + 1, end, arr);
                tree[index] = change(tree[2 * index], tree[2 * index + 1]);
        }


        lazySeg(vll v) {

                N = v.size() - 1;
                tree.assign(4*N + 1, 0);
                lazy.assign(4*N + 1, 0);
                build_tree(1, 1, N, v);
        }

        void update(int start_range, int end_range, ll value, int index, int start, int end)
        {
                if (start > end)
                        return;
                if (lazy[index] != 0)
                {
                        tree[index] += lazy[index];              // changeable
                        if (start != end)
                        {
                                lazy[2 * index] += lazy[index];
                                lazy[2 * index + 1] += lazy[index];
                        }
                        lazy[index] = 0;
                }
                if (start_range > end || end_range < start) 
                        return;
                if (start_range <= start && end_range >= end) 
                {
                        tree[index] += value;                   // changeable
                        lazy[index] += value;                   // changeable
                        if (start != end)
                        {
                                lazy[2 * index] += lazy[index];
                                lazy[2 * index + 1] += lazy[index];
                        }
                        lazy[index] = 0;
                        return;
                }
                int mid = (start + end) / 2;
                update(start_range, end_range, value, 2*index, start, mid);
                update(start_range, end_range, value, 2*index + 1, mid + 1, end);
                tree[index] = change(tree[2 * index], tree[2 * index + 1]);
        }
        ll query(int left, int right, int index, int start, int end)
        {
                if (start > end)
                        return neutral;
                if (lazy[index] != 0)
                {
                        tree[index] += lazy[index];                  // changeable
                        if (start != end)
                        {
                                lazy[2 * index] += lazy[index];
                                lazy[2 * index + 1] += lazy[index];
                        }
                        lazy[index] = 0;
                }
                if (start > right || end < left)
                        return neutral;
                if (start >= left && end <= right)
                        return tree[index];
                int mid = (start + end) / 2;
                return change(query(left, right, 2*index, start, mid), query(left, right, 2*index + 1, mid + 1, end));
        }

};
