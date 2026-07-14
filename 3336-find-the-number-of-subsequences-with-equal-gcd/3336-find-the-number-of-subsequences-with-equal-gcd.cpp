class Solution {
public:
    static const int MOD = 1e9 + 7;
    int dp[205][201][201];
    int n;

    int solve(int idx, int g1, int g2, vector<int>& nums) {
        if (idx == n) {
            return (g1 > 0 && g1 == g2) ? 1 : 0;
        }

        int &ans = dp[idx][g1][g2];
        if (ans != -1) return ans;

        ans = solve(idx + 1, g1, g2, nums); // skip

        // Put in first subsequence
        int ng1 = (g1 == 0) ? nums[idx] : gcd(g1, nums[idx]);
        ans = (ans + solve(idx + 1, ng1, g2, nums)) % MOD;

        // Put in second subsequence
        int ng2 = (g2 == 0) ? nums[idx] : gcd(g2, nums[idx]);
        ans = (ans + solve(idx + 1, g1, ng2, nums)) % MOD;

        return ans;
    }

    int subsequencePairCount(vector<int>& nums) {
        n = nums.size();
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, 0, nums);
    }
};