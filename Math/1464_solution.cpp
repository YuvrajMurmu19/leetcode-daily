/*
    LeetCode Daily Challenge - Day 29

    Problem    : 1464. Maximum Product of Two Elements in an Array
    Difficulty : Easy

    Approach:
    - Traverse the array once.
    - Maintain the largest and second-largest
      numbers seen so far.
    - The required answer is simply:
        (largest - 1) * (secondLargest - 1)
    - Return the computed product.

    Complexity:
    Time  : O(n)
    Space : O(1)
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int first = INT_MIN;
        int second = INT_MIN;
        for(int num:nums){
            if(first<=num){
                second = first;
                first = num;
            }else if(second<num) second = num;
        }

        return (first-1)*(second-1);
    }
};