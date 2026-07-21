class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int left = m - 1;   // last valid element of nums1
        int right = 0;      // first element of nums2

        // Step 1: Swap if nums1[left] > nums2[right]
        while (left >= 0 && right < n) {
            if (nums1[left] > nums2[right]) {
                swap(nums1[left], nums2[right]);
                left--;
                right++;
            } else {
                break;
            }
        }

        // Step 2: Sort both parts
        sort(nums1.begin(), nums1.begin() + m);
        sort(nums2.begin(), nums2.end());

        // Step 3: Copy nums2 into nums1
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
    }
};
