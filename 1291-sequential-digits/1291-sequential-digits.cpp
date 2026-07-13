class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {

        vector<int> ans;

        int lowLen = to_string(low).size();
        int highLen = to_string(high).size();

        // Try all possible lengths
        for (int len = lowLen; len <= highLen; len++) {

            // Possible starting digits
            for (int start = 1; start <= 10 - len; start++) {

                int num = 0;

                // Build the sequential number
                for (int digit = start; digit < start + len; digit++) {
                    num = num * 10 + digit;
                }

                if (num >= low && num <= high) {
                    ans.push_back(num);
                }
            }
        }

        return ans;
    }
};