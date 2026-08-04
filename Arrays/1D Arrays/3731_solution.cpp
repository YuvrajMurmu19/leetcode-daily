/*
    Approach 1: Sorting + Linear Scan

    Idea:
    - Sort the array so that all numbers are in increasing order.
    - Let 's' be the smallest element and 'e' be the largest.
    - Maintain a pointer 'i' over the sorted array.
    - Iterate through every expected value from s to e:
        * If nums[i] == current value, move the pointer.
        * Otherwise, the current value is missing, so add it to the answer.

    Time Complexity: O(n log n + range)
        - O(n log n) for sorting.
        - O(range) for scanning from min to max.

    Space Complexity: O(1)
        - Excluding the output array.
        - Sorting is performed in-place.
*/

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        sort(nums.begin(),nums.end());
        int s = nums[0];
        int e = nums[n-1];
        int i = 0;
        while(i<n && s<=e){
            if(nums[i] == s) i++;
            else ans.push_back(s);

            s++;
        }
        return ans;
    }
};


