/*
Approach:
----------
1. Sort the nodes while preserving their original indices.
2. For every sorted position, compute the farthest position reachable in one jump
(difference <= maxDiff) using a two-pointer technique.
3. Build a Binary Lifting (Doubling) table where up[i][j] stores the farthest
position reachable from i in 2^j jumps.
4. For each query:
- Convert the original indices to their positions in the sorted array.
- Use Binary Lifting to greedily make the largest possible jumps without
crossing the destination.
- If one final jump reaches the destination, return the minimum number of
jumps; otherwise, return -1.

```
Time Complexity:
----------------
Sorting:                O(n log n)
Building jump table:    O(n log n)
Each query:             O(log n)

Overall: O(n log n + q log n)

Space Complexity:
-----------------
O(n log n)   // Binary Lifting table
```

*/


class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {
        // first sort the array but first store the pairs
        vector<vector<int>> sorted_nums;
        for (int i = 0; i < n; i++) {
            sorted_nums.push_back({nums[i], i});
        }

        sort(sorted_nums.begin(), sorted_nums.end());
        // i have to store the sorted indices
        vector<int> new_pos(n);
        for (int i = 0; i < n; i++) {
            // new node position  --> i
            // old node position --> sorted_nums[i][1]
            new_pos[sorted_nums[i][1]] = i;
        }

        // build the binary jumping table
        int maxjumps = log2(n) + 2; // for skew tree cases
        vector<vector<int>> up(
            n, vector<int>(maxjumps, -1)); // -1 for jumping out of graph

        // initial 1 jump store
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j < n && sorted_nums[j][0] - sorted_nums[i][0] <= maxDiff) {
                j++;
            }
            up[i][0] = j - 1; // 2^0 i.e. 1 jump
        }

        // build the binary jumping table until max jumps possible
        for (int j = 1; j < maxjumps; j++) {
            for (int i = 0; i < n; i++) {
                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }
        vector<int> ans;
        for (auto& query : queries) {
            int u = query[0];
            int v = query[1];

            int x = new_pos[u];
            int y = new_pos[v];

           
            if (x == y) {
                ans.push_back(0);
                continue;
            }

           
            if (x > y)
                swap(x, y);

            int curr = x;
            int jumps = 0;

           
            for (int j = maxjumps - 1; j >= 0; j--) {
                if (up[curr][j] != -1 && up[curr][j] < y) {
                    curr = up[curr][j];
                    jumps += (1 << j);
                }
            }

            
            if (up[curr][0] != -1 && up[curr][0] >= y)
                ans.push_back(jumps + 1);
            else
                ans.push_back(-1); 
        }
        
        return ans;
    }
};