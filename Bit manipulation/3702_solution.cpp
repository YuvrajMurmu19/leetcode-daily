/*
    LeetCode 3702 - Longest Subsequence With Non-Zero Bitwise XOR

    Approach:
    Use the XOR of the entire array and check whether at least one
    element is non-zero.

    - If all elements are 0, every subsequence has XOR = 0 -> return 0.
    - If total XOR != 0, the entire array is a valid subsequence -> return n.
    - If total XOR == 0 but there is a non-zero element, remove any one
      non-zero element. The remaining XOR becomes that non-zero value,
      so the answer is n - 1.

    Key Observation:
    0 ^ x = x, so removing one non-zero element from a zero-XOR array
    guarantees a non-zero XOR.

    Time: O(n)
    Space: O(1)
*/

class Solution {
public:
    int longestSubsequence(vector<int>& nums){
        int xor_val = 0;
        bool allZero = true;
        int n = nums.size();
        for(int num:nums){
            if(num !=0) allZero = false;
            xor_val ^= num;
        }

        if(allZero){
            return 0;
        }else{
           //some elements are non zero
           if(xor_val != 0) return n;
           else return n-1;
        }

        
    }
};
