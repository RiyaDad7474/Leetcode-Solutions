class Solution {
public:
    int findGCD(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        int mx = gcd(nums[0],nums[n-1]);

        return mx;

      
    }
};