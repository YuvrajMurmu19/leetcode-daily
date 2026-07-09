/*
Approach:
- My first idea was to build the graph explicitly by connecting every pair of indices
  whose values differ by at most maxDiff, then use DFS to find connected components.
- Although this approach was correct, it required O(n²) edges in the worst case,
  leading to Memory Limit Exceeded (MLE).

Observation:
- The array nums is sorted in non-decreasing order.
- Therefore, if two consecutive elements differ by more than maxDiff, they can never
  belong to the same connected component.
- A single linear pass is enough to assign component IDs.

Algorithm:
1. Start with component ID = 0.
2. Traverse nums from left to right.
3. If nums[i] - nums[i-1] <= maxDiff, assign the same component.
4. Otherwise, start a new component.
5. For each query, check whether both indices have the same component ID.

Time Complexity: O(n + q)
Space Complexity: O(n)
*/

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
       
         vector<int> component(n);
         
         int it = 0;
         component[0] = it; 
         for(int i = 1;i<n;i++){
            if(abs(nums[i]-nums[i-1]) <= maxDiff){
                component[i] = it;
            }else{
                it++;
                component[i] = it;
            }
         }

        int sz = queries.size();
        vector<bool> ans(sz);
        for(int i = 0;i<sz;i++){
            int u = queries[i][0];
            int v = queries[i][1];
            if(component[u]==component[v]){
               ans[i]= true;;
            }else{
                ans[i]= false;;
            }
        }
        return ans;

    }
};