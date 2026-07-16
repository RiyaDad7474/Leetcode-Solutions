class Solution {
public:
    long long gcdSum(vector<int>& nums) {

        vector<int> prefixGcd;
        int mx = 0;

        for(int i = 0;i<nums.size();i++){
          mx = max(nums[i],mx);
           prefixGcd.push_back(gcd(nums[i], mx));
        }

        sort(prefixGcd.begin(),prefixGcd.end());
        int n = prefixGcd.size();
        long long ans = 0;

       int i = 0, j = n-1;
       while(i<j){
        ans += gcd(prefixGcd[i],prefixGcd[j]);
        i++;
        j--;
       }
       return ans;
    }
};