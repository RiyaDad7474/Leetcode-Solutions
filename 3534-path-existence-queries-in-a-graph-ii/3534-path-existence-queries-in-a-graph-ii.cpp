class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // 1. Sort node indices by value
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });

        vector<int> sortedVal(n), pos(n);
        for (int p = 0; p < n; p++) {
            sortedVal[p] = nums[order[p]];
            pos[order[p]] = p;
        }

        // 2. Two-pointer: far[i] = farthest position reachable directly from i (moving right)
        vector<int> far(n);
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (r < i) r = i;
            while (r + 1 < n && sortedVal[r + 1] - sortedVal[i] <= maxDiff) r++;
            far[i] = r;
        }

        // 3. Component id: breaks whenever consecutive gap > maxDiff
        vector<int> comp(n);
        for (int i = 1; i < n; i++) {
            if (sortedVal[i] - sortedVal[i - 1] <= maxDiff) comp[i] = comp[i - 1];
            else comp[i] = comp[i - 1] + 1;
        }

        // 4. Binary lifting table
        int LOG = max(1, (int)ceil(log2(max(2, n))) + 1);
        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = far;
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        int q = queries.size();
        vector<int> ans(q);

        for (int idx = 0; idx < q; idx++) {
            int u = queries[idx][0], v = queries[idx][1];
            int pu = pos[u], pv = pos[v];

            if (pu == pv) {
                ans[idx] = 0;
                continue;
            }
            if (pu > pv) swap(pu, pv);

            if (comp[pu] != comp[pv]) {
                ans[idx] = -1;
                continue;
            }

            int cur = pu;
            long long steps = 0;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < pv) {
                    cur = up[k][cur];
                    steps += (1LL << k);
                }
            }
            steps += 1; // final hop guaranteed to reach >= pv
            ans[idx] = (int)steps;
        }

        return ans;
    }
};