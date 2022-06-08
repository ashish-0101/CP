struct segmentTree {

        ll N;
        vll tree;


        ll neutral = 0;   // base (dont forget to change)

        ll change(ll a, ll b) {

                return gcd(abs(a), abs(b));
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
