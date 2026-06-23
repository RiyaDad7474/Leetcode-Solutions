class Solution {
public:
    static constexpr int MOD = 1e9 + 7;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<long long> up(m + 1), down(m + 1);

        for (int j = 1; j <= m; j++) {
            up[j] = m - j;      // length 2 ending at j, last move was up
            down[j] = j - 1;    // length 2 ending at j, last move was down
        }

        for (int len = 3; len <= n; len++) {
            vector<long long> nup(m + 1), ndown(m + 1);

            long long pref = 0;
            for (int j = 1; j <= m; j++) {
                ndown[j] = pref;
                pref = (pref + up[j]) % MOD;
            }

            long long suff = 0;
            for (int j = m; j >= 1; j--) {
                nup[j] = suff;
                suff = (suff + down[j]) % MOD;
            }

            up.swap(nup);
            down.swap(ndown);
        }

        long long ans = 0;
        for (int j = 1; j <= m; j++) {
            ans = (ans + up[j] + down[j]) % MOD;
        }

        return (int)ans;
    }
};