class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();

        vector<int> arr1 = arr;
        sort(arr1.begin(), arr1.end());

        unordered_map<int, int> rank;
        int r = 1;

        for (int i = 0; i < n; i++) {
            if (rank.find(arr1[i]) == rank.end()) {
                rank[arr1[i]] = r;
                r++;
            }
        }

        for (int i = 0; i < n; i++) {
            arr[i] = rank[arr[i]];
        }

        return arr;
    }
};