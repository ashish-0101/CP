struct Node1 {
      ll val; // store more info if required
      Node1() { // Identity Element
            val = 0;
      }
      Node1(ll v) {
            val = v;
      }
      void merge(Node1 &l, Node1 &r) {
            val = __gcd(l.val, r.val);
      }
};
vector<ll> logValues(2e5 + 1);
vector<vector<Node1>> table(2e5 + 1);
template<typename Node>
struct SparseTable {
      int n;
      int maxLog;
      vector<ll> a;
      SparseTable(int n1, vector<ll> &arr) {
            n = n1;
            a = arr;
            maxLog = log2(n);
            build();
      }
      void build() {
            for (int i = 0; i < n; i++) {
                  table[i][0] = Node(a[i]);
            }
            for (int i = 1; i <= maxLog; i++) {
                  for (int j = 0; (j + (1 << i)) <= n; j++) {
                        table[j][i].merge(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
                  }
            }
      }
      Node queryNormal(int left, int right) {
            Node ans = Node();
            for (int j = logValues[right - left + 1]; j >= 0; j--) {
                  if ((1 << j) <= right - left + 1) {
                        ans.merge(ans, table[left][j]);
                        left += (1 << j);
                  }
            }
            return ans;
      }
      Node queryIdempotent(int left, int right) {
            int j = logValues[right - left + 1];
            Node ans = Node();
            ans.merge(table[left][j], table[right - (1 << j) + 1][j]);
            return ans;
      }
};