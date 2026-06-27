class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;

        for (int x : nums)
            cnt[x]++;

        int ans = 0;

        // Handle 1 separately
        if (cnt.count(1)) {
            ans = cnt[1] - (cnt[1] % 2 == 0);
            cnt.erase(1);
        }

        for (auto &[num, _] : cnt) {
            long long x = num;
            int len = 0;

            while (cnt.count(x) && cnt[x] > 1) {
                len += 2;
                x = x * x;
            }

            if (cnt.count(x))
                len++;
            else
                len--;

            ans = max(ans, len);
        }

        return ans;
    }
};