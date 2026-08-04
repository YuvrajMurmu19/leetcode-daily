/*
    Approach 2: Hash Set

    Idea:
    - Store every element in an unordered_set for O(1) average lookup.
    - Find the minimum and maximum values in the array.
    - Traverse every integer from min to max:
        * If the current number is not present in the hash set,
          it is missing, so add it to the answer.

    Time Complexity: O(n + range)
        - O(n) to build the hash set and find min/max.
        - O(range) to check every value in the original range.

    Space Complexity: O(n)
        - For storing all elements in the unordered_set.
*/

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
       
        unordered_set<int> st(nums.begin(),nums.end());
        int s = INT_MAX;
        int e = INT_MIN;
        for(int num:nums){
            s = min(s,num);
            e = max(e,num);
        }
        
        for(int i = s;i<=e;i++){
            if(!st.count(i)) ans.push_back(i);
        }
        return ans;
    }
};