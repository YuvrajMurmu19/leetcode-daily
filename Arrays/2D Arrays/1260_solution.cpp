/*
Approach:
- Instead of simulating each of the k shifts, directly compute the final
  position of every element.
- For each cell (i, j), calculate its new column after shifting by k.
- The number of times the column overflows determines how many rows the
  element moves down.
- Compute the new row using modular arithmetic and place the element in
  its final position in the answer grid.

Time Complexity: O(m * n)
Space Complexity: O(m * n)
*/

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> ans (row,vector<int>(col,-1));

        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                int new_j = (j + k)% col;
                int jumps = (j+k)/col;
                int new_i = (i+jumps)%row;
                ans[new_i][new_j] = grid[i][j];
            }
        }
        return ans;
    }
};
