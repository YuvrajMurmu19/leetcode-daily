/*
    LeetCode 2958 - Length of Longest Subarray With at Most K Frequency

    Approach: Two Pointers / Sliding Window

    Maintain a window [j, i] where every element appears at most k times.
    Expand the window by moving i and update the frequency.
    If nums[i] exceeds frequency k, move j forward until the window
    becomes valid again.

    Since both pointers only move forward, each element is added and
    removed at most once.

    Time Complexity: O(n) average
    Space Complexity: O(n)
*/

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();

        unordered_map<int,int> freq;

        int i = 0, j = 0;
        int maxLen = 0;

        while(i<n && j<n){
            freq[nums[i]]++;

            while(freq[nums[i]]>k && j<n){
                freq[nums[j]]--;
                j++;
            }

            //valid subarray
            int len = i-j+1;
            maxLen = max(len,maxLen);

            i++;
        }
        
        return maxLen;
    }
};