class SparseTable {
public:
    vector<vector<int>> table;
    int n;

    SparseTable() {}

    SparseTable(vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;

        int k = 32 - __builtin_clz(n);
        table.push_back(nums);

        for (int j = 1; j <= k; j++) {
            vector<int> row;
            int width = 1 << j;
            if (width > n) break;

            for (int i = 0; i + width <= n; i++) {
                row.push_back(max(table[j - 1][i],
                                  table[j - 1][i + (width >> 1)]));
            }
            table.push_back(row);
        }
    }

    int queryMax(int l, int r) {
        int len = r - l + 1;
        int j = 31 - __builtin_clz(len);
        return max(table[j][l], table[j][r - (1 << j) + 1]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {

        int n = s.size();
        int ones = 0;

        for (char c : s)
            if (c == '1') ones++;

        vector<int> gapStart;
        vector<int> gapLen;
        vector<int> gapId(n, -1);

        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    gapLen.back()++;
                } else {
                    gapStart.push_back(i);
                    gapLen.push_back(1);
                }
            }
            gapId[i] = (int)gapStart.size() - 1;
        }

        if (gapStart.empty())
            return vector<int>(queries.size(), ones);

        vector<int> pairGain;
        for (int i = 0; i + 1 < gapLen.size(); i++)
            pairGain.push_back(gapLen[i] + gapLen[i + 1]);

        SparseTable sparse(pairGain);

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int leftPart = -1;
            if (gapId[l] != -1) {
                leftPart = gapLen[gapId[l]] -
                           (l - gapStart[gapId[l]]);
            }

            int rightPart = -1;
            if (gapId[r] != -1) {
                rightPart = r - gapStart[gapId[r]] + 1;
            }

            int firstFull = gapId[l] + 1;

            int lastFull;
            if (s[r] == '1')
                lastFull = gapId[r] - 1;
            else
                lastFull = gapId[r] - 2;

            int best = ones;

            // Case A
            if (s[l] == '0' && s[r] == '0' &&
                gapId[l] + 1 == gapId[r]) {
                best = max(best, ones + leftPart + rightPart);
            }
            // Case B
            else if (firstFull <= lastFull && !pairGain.empty()) {
                best = max(best,
                           ones + sparse.queryMax(firstFull, lastFull));
            }

            // Case C
            if (s[l] == '0' &&
                gapId[l] + 1 <=
                    (s[r] == '1' ? gapId[r] : gapId[r] - 1)) {

                best = max(best,
                           ones + leftPart +
                               gapLen[gapId[l] + 1]);
            }

            // Case D
            if (s[r] == '0' &&
                gapId[l] < gapId[r] - 1) {

                best = max(best,
                           ones + rightPart +
                               gapLen[gapId[r] - 1]);
            }

            ans.push_back(best);
        }

        return ans;
    }
};