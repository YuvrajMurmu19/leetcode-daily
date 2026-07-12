/*
Approach:
1. Create a copy of the original array and sort it.
2. Assign ranks only to unique elements:
   - Start rank from 1.
   - If the current element is different from the previous one,
     increment the rank and store {value -> rank} in a hash map.
   - Duplicate values keep the same rank.
3. Traverse the original array and replace each element with its
   corresponding rank using the hash map.
4. Return the transformed array.

Time Complexity: O(n log n)
- Sorting the copied array takes O(n log n).
- Assigning ranks and transforming the original array each take O(n).

Space Complexity: O(n)
- O(n) for the sorted copy and hash map.
*/

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();
        if(n==0) return {};
        vector<int> sorted_arr(arr.begin(),arr.end());

        sort(sorted_arr.begin(),sorted_arr.end());

        unordered_map<int,int> val_rank;
        int rank = 1;
        val_rank[sorted_arr[0]] = rank;
        for(int i = 1;i<n;i++){
            if(sorted_arr[i] != sorted_arr[i-1]){
                rank++;
                val_rank[sorted_arr[i]] = rank;
            }
        }

        for(int i = 0;i<n;i++){
            arr[i] = val_rank[arr[i]];
        }

        return arr;
        
    }
};