class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
         
         int size = m*n;
         vector<int> arr;
         for(int i = 0;i<n;i++){
            for(int j = 0;j<m;j++){
                arr.push_back( grid[i][j]);
            }
         }

         vector<int> extraArr(size);
         for(int i = 0;i<size;i++){
            extraArr[(i+k)%size] = arr[i];
         }

         int idx= 0;
         for(int i = 0;i<n;i++){
            for(int j = 0;j<m;j++){
                grid[i][j] = extraArr[idx++];
            }
         }


return grid;
    }
};