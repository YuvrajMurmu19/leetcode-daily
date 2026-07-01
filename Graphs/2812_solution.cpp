/*
Approach:

1. My first idea was a greedy approach.
   I computed the safeness factor of every cell by finding its minimum
   Manhattan distance from all thief cells. Then, starting from the top-left,
   I always moved to the neighboring cell (right or down) with the higher
   safeness value, hoping to maximize the minimum safeness along the path.

2. This approach passed 859/1036 test cases but eventually failed because
   making the locally optimal choice does not always lead to the globally
   safest path.

3. After reviewing the LeetCode hints, I learned a better strategy.
   First, I used Multi-Source BFS by pushing all thief cells into the queue
   simultaneously. This computes the minimum distance of every cell from its
   nearest thief in O(n²).

4. The answer was then binary searched. For each candidate safeness factor,
   I performed a BFS from the start cell, moving only through cells whose
   safeness was at least the candidate value. If the destination was reachable,
   I tried a larger safeness factor; otherwise, I searched smaller values.

Time Complexity:
- Multi-Source BFS : O(n²)
- Binary Search + BFS Validation : O(n² log n)
- Overall : O(n² log n)

Space Complexity:
- O(n²)
*/

class Solution {
public:
    // for traversing in all directions
    vector<vector<int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1)
            return 0; // there will be atleast one thief
        queue<pair<int, int>> q;
        vector<vector<int>> safeness_matrix(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                     safeness_matrix[i][j] = 0;
                }
            }
        }

        // i have list of thieves in queue now i will do bfs
        // doing bfs from all the thieves will lead to thieves reaching thier
        // closest cells saare thieves apne apne closest cell ko phle visit
        // krenge visited track --- safeness_matrix --- not visited then -1

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (auto& dir : directions) {
                int i = x + dir[0];
                int j = y + dir[1];

                if (i < n && j < n && i >= 0 && j >= 0 &&
                    safeness_matrix[i][j] == -1) {
                    // not visited yet
                    //  current wale me 1 add kiya kyuki abb 1 step dur h thief
                    //  se
                    safeness_matrix[i][j] = safeness_matrix[x][y] + 1;
                    q.push({i, j});
                }
            }
        }

        // now the value of safeness factor can lie btw min of start and end
        // cell and 0
        int low = 0;
        int high = min(safeness_matrix[0][0], safeness_matrix[n - 1][n - 1]);
        int max_safeness_factor = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (valid(safeness_matrix, mid)) {
                max_safeness_factor = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return max_safeness_factor;
    }

    bool valid(vector<vector<int>>& safeness_matrix, int mid) {
        int n = safeness_matrix.size();
        vector<vector<bool>> visited(n,vector<bool>(n,false));
        // will use bfs for traversal
        queue<pair<int, int>> q;
        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto [x,y] = q.front();
            q.pop();

            if(x==n-1 && y==n-1) return true;
            for (auto& dir : directions) {
                int i = x + dir[0];
                int j = y + dir[1];
                if(i<n && j<n && i>=0&& j>=0 && !visited[i][j] && safeness_matrix[i][j]>=mid){
                    visited[i][j] = true;
                    q.push({i,j});
                }
            }
        }
        return false;
    }
};