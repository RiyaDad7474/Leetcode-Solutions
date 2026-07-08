class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        static const int MOD = 1000000007;
        int n = s.size();

        // Precompute powers of 10
        vector<long long> pow10(n + 1);
        pow10[0] = 1;
        for (int i = 1; i <= n; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        // Prefix arrays
        vector<int> sumD(n + 1, 0);      // Sum of digits
        vector<int> cntN0(n + 1, 0);     // Count of non-zero digits
        vector<long long> pref(n + 1, 0); // Concatenated non-zero number (mod MOD)

        for (int i = 1; i <= n; i++) {
            int d = s[i - 1] - '0';
            sumD[i] = sumD[i - 1] + d;
            cntN0[i] = cntN0[i - 1] + (d > 0);

            if (d > 0)
                pref[i] = (pref[i - 1] * 10 + d) % MOD;
            else
                pref[i] = pref[i - 1];
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int nonZeroCnt = cntN0[r + 1] - cntN0[l];
            int digitSum = sumD[r + 1] - sumD[l];

            long long x = (pref[r + 1] -
                           pref[l] * pow10[nonZeroCnt] % MOD +
                           MOD) % MOD;

            ans.push_back((x * digitSum) % MOD);
        }

        return ans;
    }
};